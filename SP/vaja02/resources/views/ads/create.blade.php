@extends('layouts.app')

@section('content')
    <h1>Create Ad</h1>
    {!! Form::open(['url' => '/ads', 'method' => 'POST', 'enctype' => 'multipart/form-data', 'files' => true]) !!}
    <div class="form-group">
        {{Form::label('title', 'Title')}}
        {{Form::text('title', '', ['class' => 'form-control', 'placeholder' => 'title...'])}}
    </div>
    <div class="form-group">
        {{Form::label('description', 'Description')}}
        {{Form::text('description', '', ['class' => 'form-control', 'placeholder' => 'description...'])}}
    </div>
    <div class="form-group">
        {{Form::label('images', 'Upload your image')}}
        {{Form::file('images', ['class' => 'form-control', 'type' => 'file', 'accept' => 'image/*', 'multiple' => true, 'name' => 'images[]'])}}
    </div>
    <div class="form-group">
        {{Form::label('categories', 'Select categories')}}
        <select name="categories[]" class="form-control " id="categories" multiple>
            @include('partials.categories', ['cats' => $cats, 'index' => 0])
        </select>
    </div>
    {{Form::submit('Submit', ['class' => 'btn btn-primary'])}}
    {!! Form::close() !!}
@endsection
