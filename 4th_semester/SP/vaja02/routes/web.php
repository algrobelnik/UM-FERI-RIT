<?php

use App\Http\Controllers\AdsController;
use App\Http\Controllers\CommentsController;
use App\Http\Controllers\HomeController;
use App\Http\Controllers\PagesController;
use App\Http\Controllers\UsersController;
use Illuminate\Support\Facades\Auth;
use Illuminate\Support\Facades\Route;

/*
|--------------------------------------------------------------------------
| Web Routes
|--------------------------------------------------------------------------
|
| Here is where you can register web routes for your application. These
| routes are loaded by the RouteServiceProvider within a group which
| contains the "web" middleware group. Now create something great!
|
*/

/* TODO
    - RESTful API for comments(adding comments, reading one comment, reading all, deleting only to owner, json)
    - comment([foreign key ad_id, email, alias, content, dates, ip_addr], if user is not authenticated[guest] set alias and check email[validate using email verification])
    - counter ad views ads/index.blade.php
    - send via ajax/curl
    - show all comments under ad(sorted by timestamp desc, paginated, edit button to added comments user)
    - returnLastFive for comments shown on ads index page and country name from ip addr using https://ip-api.com/docs/api:json
    -
*/
Route::resource('ads', AdsController::class);
Route::get('/', [ AdsController::class, "index" ]);
Route::get('/login', [ PagesController::class, "login" ]);
Route::get('/register', [ PagesController::class, "register" ]);

Auth::routes();

Route::get('/home', [HomeController::class, 'index'])->name('home');
Route::resource('users', UsersController::class);
