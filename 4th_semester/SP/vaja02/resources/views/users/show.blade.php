@extends('layouts.app')

@section('content')
    <div class="well">
        <a href="/ads" class="btn btn-success">Go Back</a><br>
        {{--dd($ad->images)--}}
        @foreach($ad->images as $img)
            <img class="img-thumbnail" src="{{$img->img}}" alt="image{{$img->id}}">
        @endforeach
        <ul class="list-group">
            @foreach($ad->ad_categories as $ac)
                <li class="list-group-item">{{$ac->category->name}}</li>
            @endforeach
        </ul>
        @foreach($ad->comments as $comment)
            <textarea className="form-control">{{$comment->text}}</textarea>
        @endforeach
        <br>
        <small>Written on {{$ad->date_s}} by {{$ad->user->name}}</small>
        <a href="/comment" class="btn btn-success">Go Back</a><br>
    </div>
    @if(!Auth::guest() && Auth::user()->id == $ad->user_id)
        <a href="/ads/{{$ad->id}}/edit" class="btn btn-default">Edit</a>
        {!! Form::open(['url' => "/ads/$ad->id", "method" => "POST", "class" => "pull-right"]) !!}
            {{Form::hidden('_method', 'DELETE')}}
            {{Form::submit('Delete', ['class' => 'btn btn-danger'])}}
        {!! Form::close() !!}
    @endif
@endsection
