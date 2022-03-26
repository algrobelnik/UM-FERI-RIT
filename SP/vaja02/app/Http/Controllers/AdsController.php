<?php

namespace App\Http\Controllers;

use App\Models\AdCategory;
use App\Models\Image;
use Carbon\Carbon;
use Illuminate\Http\Request;
use App\Models\Ad;
use App\Models\Category;
use Illuminate\Support\Arr;

class AdsController extends Controller
{
    public array $complexCategories = [];
    /**
     * Display a listing of the resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function index()
    {
        $ads = Ad::orderBy('created_at', 'desc')->paginate();
        return view('ads.index')->with('ads', $ads);
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return \Illuminate\Http\Response
     */
    public function create()
    {
        $cats = Category::all()->toArray();
        $basicCategories = Arr::where($cats, function ($item, $key) {
            return empty($item['pid']);
        });
        $this->processCategoriesLevel($cats, $basicCategories);
        //dd(Category::all()->pluck('name'), $this->complexCategories);
        return view('ads.create')->with('cats', $this->complexCategories);
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
        $ad = new Ad;
        $this->extracted($request, $ad);
        return redirect('/ads')->with('success', 'Ad created');
    }

    /**
     * Display the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function show($id)
    {
        $ad = Ad::find($id);
        return view('ads.show')->with('ad', $ad);
    }

    /**
     * Show the form for editing the specified resource.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function edit($id)
    {
        $ad = Ad::find($id);
        $cats = Category::all()->toArray();
        $basicCategories = Arr::where($cats, function ($item, $key) {
            return empty($item['pid']);
        });
        $this->processCategoriesLevel($cats, $basicCategories);
        $ad_cats = AdCategory::where('aid', $ad->id)->get()->pluck('cid')->toArray();
        return view('ads.edit')->with('ad', $ad)->with('cats', $this->complexCategories)->with('ad_cats', $ad_cats);
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
        $ad = Ad::find($id);
        $this->extracted($request, $ad);
        return redirect('/ads')->with('success', 'Ad updated');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param  int  $id
     * @return \Illuminate\Http\Response
     */
    public function destroy($id)
    {
        Image::where('aid', $id)->get()->each->delete();
        AdCategory::where('aid', $id)->get()->each->delete();
        Ad::find($id)->delete();
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
            return $child['id'] == $value['pid'];
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
        $ad->uid = 1;
        $ad->save();
        foreach ($request->input('categories') as $cat) {
            $ac = new AdCategory();
            $ac->aid = $ad->id;
            $ac->cid = $cat;
            //dd($ac);
            $ac->save();
        }
        if ($request->hasFile('images')) {
            foreach ($request->file('images') as $i) {
                $img = new Image();
                $img->img = "data:" . $i->getMimeType() . ";base64," . base64_encode(file_get_contents($i->getRealPath()));
                $img->aid = $ad->id;
                //dd($img);
                $img->save();
            }
        }
    }
}
