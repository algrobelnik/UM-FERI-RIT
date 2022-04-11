<?php

namespace App\Http\Controllers;

use App\Models\Ad;
use App\Models\AdCategory;
use App\Models\Category;
use App\Models\Comment;
use App\Models\Image;
use Carbon\Carbon;
use Illuminate\Contracts\Foundation\Application;
use Illuminate\Http\Request;
use Illuminate\Http\Response;
use Illuminate\Support\Arr;
use Illuminate\Support\Facades\Auth;

class CommentsController extends Controller
{
    /**
     * Create a new controller instance.
     *
     * @return void
     */
    public function __construct()
    {
       //$this->middleware('auth');
    }

    /**
     * Display a listing of the resource.
     *
     * @return Response
     */
    public function index()
    {
        return Comment::all();
    }

    /**
     * Display a listing of the resource.
     *
     * @param Request $request
     * @return Response
     */
    public function lastFive()
    {
        return Comment::orderBy('created_at', 'desc')->take(5)->get();
    }

    /**
     * Show the form for creating a new resource.
     *
     * @return Response
     */
    public function create()
    {
        return view('comments.create');
    }

    /**
     * Store a newly created resource in storage.
     *
     * @param Request $request
     * @return Response
     */
    public function store(Request $request)
    {
        /*$this->validate($request,[
            'title' => 'required',
            'description' => 'required',
            'images' => 'required',
            'images.*' => 'mimes:jpeg,jpg,png,gif',
            'categories' => 'required',
        ]);*/
        $comment = new Comment();
        $comment->email = $request->input('email');
        $comment->alias = $request->input('alias');
        $comment->content = $request->input('content');
        $comment->ad_id = $request->input('ad_id');
        $comment->ip_address = $request->ip();
        $comment->save();
        return response()->json($comment, 201);
        return redirect('/comments')->with('success', 'Ad created');
    }

    /**
     * Display the specified resource.
     *
     * @param  Comment  $comment
     * @return Comment
     */
    public function show(Comment $comment)
    {
        return $comment;
    }

    /**
     * Update the specified resource in storage.
     *
     * @param Request $request
     * @param  Comment  $comment
     * @return \Illuminate\Http\JsonResponse
     */
    public function update(Request $request, Comment $comment)
    {
        /*$this->validate($request,[
            'title' => 'required',
            'description' => 'required',
            'images' => 'required',
            'images.*' => 'mimes:jpeg,jpg,png,gif',
            'categories' => 'required',
        ]);*/
        $comment->update($request->all());
        return response()->json($comment, 200);
        return redirect('/comments')->with('success', 'Ad updated');
    }

    /**
     * Remove the specified resource from storage.
     *
     * @param Comment $comment
     * @return Response
     */
    public function destroy(Comment $comment)
    {
        $comment->delete();
        return response()->json($comment, 204);
        return redirect('/comments')->with('success', 'Ad deleted');
    }
}
