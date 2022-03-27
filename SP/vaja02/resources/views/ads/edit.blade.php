@extends('layouts.app')

@section('content')
    <!--TODO https://www.youtube.com/watch?v=-QapNzUE4V0&list=PLillGF-RfqbYhQsN5WMXy6VsDMKGadrJ-&index=7-->
    <h1>Edit Ad</h1>
    {!! Form::open(['url' => "/ads/$ad->id", 'method' => 'POST']) !!}
    <div class="form-group">
        {{Form::label('title', 'Title')}}
        {{Form::text('title', $ad->title, ['class' => 'form-control', 'placeholder' => 'title...'])}}
    </div>
    <div class="form-group">
        {{Form::label('description', 'Description')}}
        {{Form::text('description', $ad->description, ['class' => 'form-control', 'placeholder' => 'description...'])}}
    </div>
    <div class="form-group">
        {{Form::label('images', 'Upload your image')}}
        {{Form::file('images', ['class' => 'form-control', 'type' => 'file', 'accept' => 'image/*', 'multiple' => true])}}
    </div>
    <div class="form-group">
        {{Form::label('categories', 'Select categories')}}
        <select name="categories[]" class="form-control " id="categories" multiple>
            @include('partials.categories', ['cats' => $cats, 'index' => 0])
        </select>
    </div>
    {{Form::hidden('_method', 'PUT')}}
    {{Form::submit('Submit', ['class' => 'btn btn-primary'])}}
    {!! Form::close() !!}
@endsection
