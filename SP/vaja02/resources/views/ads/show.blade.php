@extends('layout.app')

@section('content')
    <a href="/ads" class="btn btn-default">Go Back</a>
    <h1>{{$ad->title}}</h1>
    <div>
        {{$ad->description}}
    </div>
    <hr>
    <small>Written on</small>
    <hr>
    <a href="/ads/{{$ad->id}}/edit" class="btn btn-default">Edit</a>
    {!! Form::open(['url' => "/ads/$ad->id", "method" => "POST", "class" => "pull-right"]) !!}
        {{Form::hidden('_method', 'DELETE')}}
        {{Form::submit('Submit', ['class' => 'btn btn-danger'])}}
    {!! Form::close() !!}
@endsection
