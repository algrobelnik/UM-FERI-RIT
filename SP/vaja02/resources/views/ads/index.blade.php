@extends('layouts.app')

@section('content')
    <h1>Ads</h1>
    @if(count($ads) > 0)
        @foreach($ads as $ad)
            <div class="well">
                <h3><a href="/ads/{{$ad->id}}">{{$ad->title}}</a></h3>
                {{--dd($ad->images)--}}
                @foreach($ad->images as $img)
                    <img class="img-thumbnail" src="{{$img->img}}" alt="image{{$img->id}}">
                @endforeach
                <ul class="list-group">
                    @foreach($ad->ad_categories as $ac)
                        <li class="list-group-item">{{$ac->category->name}}</li>
                    @endforeach
                </ul>
                <br>
                <small>Written on {{$ad->date_s}} by {{$ad->user->name}}</small>
                <button href="/ads/"></button>
            </div>
        @endforeach
    @else
        <p>No ads found</p>
    @endif
@endsection
