<?php

namespace App\Http\Controllers;

use App\Models\AdCategory;
use App\Models\Comment;
use App\Models\Image;
use Carbon\Carbon;
use Illuminate\Contracts\Foundation\Application;
use Illuminate\Contracts\View\Factory;
use Illuminate\Contracts\View\View;
use Illuminate\Http\RedirectResponse;
use Illuminate\Http\Request;
use App\Models\Ad;
use App\Models\Category;
use Illuminate\Http\Response;
use Illuminate\Routing\Redirector;
use Illuminate\Support\Arr;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Http;

class AdsController extends Controller
{
    public array $complexCategories = [];

    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
        $this->middleware('auth')->except('index')->except('show');
    }

    /**
     * Display a listing of the resource.
     *
     * @return Application|Factory|View
     */
    public function index()
    {
        $ads = Ad::orderBy('created_at', 'desc')->paginate();
        //$comments = Http::get('http://127.0.0.1:8000/api/returnLastFive');
        $comments = Comment::orderBy('created_at', 'desc')->take(5)->get();
        return view('ads.index')->with('ads', $ads)->with('comments', $comments);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return Application|Factory|View
     */
    public function create()
    {
        $cats = Category::all()->toArray();
        $basicCategories = Arr::where($cats, function ($item, $key) {
            return empty($item['parent_id']);
        });
        $this->processCategoriesLevel($cats, $basicCategories);
        //dd(Category::all()->pluck('name'), $this->complexCategories);
        return view('ads.create')->with('cats', $this->complexCategories);
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param Request $request
     * @return Application|Redirector|RedirectResponse
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
        $ad = new Ad;
        $this->extracted($request, $ad);
        return redirect('/ads')->with('success', 'Ad created');
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return Application|Redirector|RedirectResponse
     */
    public function show($id)
    {
        $ad = Ad::find($id);
        if ($ad == null){
            return redirect('/ads')->with('error', 'Unauthorized page');
        }
        return view('ads.show')->with('ad', $ad);
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return Application|RedirectResponse|Redirector
     */
    public function edit($id)
    {
        $ad = Ad::find($id);
        if ($ad == null || auth()->user()->id !== $ad->user_id){
            return redirect('/ads')->with('error', 'Unauthorized page');
        }
        $cats = Category::all()->toArray();
        $basicCategories = Arr::where($cats, function ($item, $key) {
            return empty($item['parent_id']);
        });
        $this->processCategoriesLevel($cats, $basicCategories);
        $ad_cats = AdCategory::where('ad_id', $ad->id)->get()->pluck('category_id')->toArray();
        return view('ads.edit')->with('ad', $ad)->with('cats', $this->complexCategories)->with('ad_cats', $ad_cats);
    }

    /**
     * Update the specified resource in storage.
     *
     * @param Request $request
     * @param  int  $id
     * @return Application|Redirector|RedirectResponse
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
        $ad = Ad::find($id);
        $this->extracted($request, $ad);
        return redirect('/ads')->with('success', 'Ad updated');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return Application|Redirector|RedirectResponse
     */
    public function destroy($id)
    {
        $ad = Ad::find($id);
        if (Auth()->user()->id !== $ad->user_id){
            return redirect('/ads')->with('error', 'Unauthorized page');
        }
        Image::where('aid', $id)->get()->each->delete();
        AdCategory::where('aid', $id)->get()->each->delete();
        $ad->delete();
        return redirect('/ads')->with('success', 'Ad deleted');
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
     * @param $ad
     * @return void
     */
    public function extracted(Request $request, $ad): void
    {
        $ad->title = $request->input('title');
        $ad->description = $request->input('description');
        $ad->date_e = Carbon::now()->addDays(30);
        $ad->user_id = Auth::user()->id;
        //dd($ad);
        $ad->save();
        foreach ($request->input('categories') as $cat) {
            $ac = new AdCategory();
            $ac->ad_id = $ad->id;
            $ac->category_id = $cat;
            //dd($ac);
            $ac->save();
        }
        if ($request->hasFile('images')) {
            foreach ($request->file('images') as $i) {
                $img = new Image();
                $img->img = "data:" . $i->getMimeType() . ";base64," . base64_encode(file_get_contents($i->getRealPath()));
                $img->ad_id = $ad->id;
                //dd($img);
                $img->save();
            }
        }
    }
}
