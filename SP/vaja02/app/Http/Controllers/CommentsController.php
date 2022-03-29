<?php

namespace App\Http\Controllers;

use App\Models\Ad;
use App\Models\AdCategory;
use App\Models\Category;
use App\Models\Image;
use Carbon\Carbon;
use Illuminate\Http\Request;
use Illuminate\Support\Arr;
use Illuminate\Support\Facades\Auth;

class CommentsController extends Controller
{
    public array $complexCategories = [];

    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth');
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        return view('comments.create');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @return \Illuminate\Http\Response
     */
    public function store(Request $request)
    {
        $this->validate($request,[
            'title' => 'required',
            'description' => 'required',
            'images' => 'required',
            'images.*' => 'mimes:jpeg,jpg,png,gif',
            'categories' => 'required',
        ]);
        $comment = new Ad;
        $this->extracted($request, $comment);
        return redirect('/comments')->with('success', 'Ad created');
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $comment = Ad::find($id);
        if ($comment == null){
            return redirect('/comments')->with('error', 'Unauthorized page');
        }
        return view('comments.show')->with('comment', $comment);
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        $comment = Ad::find($id);
        if ($comment == null || auth()->user()->id !== $comment->user_id){
            return redirect('/comments')->with('error', 'Unauthorized page');
        }
        $cats = Category::all()->toArray();
        $basicCategories = Arr::where($cats, function ($item, $key) {
            return empty($item['parent_id']);
        });
        $this->processCategoriesLevel($cats, $basicCategories);
        $comment_cats = AdCategory::where('comment_id', $comment->id)->get()->pluck('category_id')->toArray();
        return view('comments.edit')->with('comment', $comment)->with('cats', $this->complexCategories)->with('comment_cats', $comment_cats);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function update(Request $request, $id)
    {
        $this->validate($request,[
            'title' => 'required',
            'description' => 'required',
            'images' => 'required',
            'images.*' => 'mimes:jpeg,jpg,png,gif',
            'categories' => 'required',
        ]);
        $comment = Ad::find($id);
        $this->extracted($request, $comment);
        return redirect('/comments')->with('success', 'Ad updated');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        $comment = Ad::find($id);
        if (auth()->user()->id !== $comment->user_id){
            return redirect('/posts')->with('error', 'Unauthorized page');
        }
        Image::where('aid', $id)->get()->each->delete();
        AdCategory::where('aid', $id)->get()->each->delete();
        $comment->delete();
        return redirect('/comments')->with('success', 'Ad deleted');
    }

    private function processCategoriesLevel($org, $cats) {
        foreach ($cats as $cat) {
            $children = $this->fillChildren($org, $cat);
            $this->complexCategories[] = [
                'id' => $cat['id'],
                'name' => $cat['name'],
                'children' => $children
            ];
        }
    }

    private function fillChildren($org, $child) {
        $child_collector = [];
        $new_children = Arr::where($org, function ($value) use ($child) {
            return $child['id'] == $value['parent_id'];
        });
        if (!empty($new_children)) {
            foreach ($new_children as $nc) {
                $child_collector[] = [
                    'id' => $nc['id'],
                    'name' => $nc['name'],
                    'children' => $this->fillChildren($org, $nc)
                ];
            }
            return $child_collector;
        }
    }

    /**
     * @param Request $request
     * @param $comment
     * @return void
     */
    public function extracted(Request $request, $comment): void
    {
        $comment->title = $request->input('title');
        $comment->description = $request->input('description');
        $comment->date_e = Carbon::now()->commentdDays(30);
        $comment->user_id = Auth::user()->id;
        //dd($comment);
        $comment->save();
        foreach ($request->input('categories') as $cat) {
            $ac = new AdCategory();
            $ac->comment_id = $comment->id;
            $ac->category_id = $cat;
            //dd($ac);
            $ac->save();
        }
        if ($request->hasFile('images')) {
            foreach ($request->file('images') as $i) {
                $img = new Image();
                $img->img = "data:" . $i->getMimeType() . ";base64," . base64_encode(file_get_contents($i->getRealPath()));
                $img->comment_id = $comment->id;
                //dd($img);
                $img->save();
            }
        }
    }
}
