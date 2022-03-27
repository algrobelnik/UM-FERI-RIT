@extends('layouts.app')

@section('content')
    <h1>Ads</h1>
    @if(count($ads) > 0)
        @foreach($ads as $ad)
            <div class="well">
                <h3><a href="/ads/{{$ad->id}}">{{$ad->title}}</a></h3>
                <small>Written on {{$ad->date_s}} by {{$ad->user->name}}</small>
            </div>
        @endforeach
    @else
        <p>No ads found</p>
    @endif
@endsection
