@extends('layouts.app')

@section('content')
    <div class="well">
        <a href="/ads" class="btn btn-success">Go Back</a>
        @if(!Auth::guest() && Auth::user()->id == $ad->user_id)
            {!! Form::open(['url' => "/ads/$ad->id", "method" => "POST", "class" => "pull-right"]) !!}
            {{Form::hidden('_method', 'DELETE')}}
            {{Form::submit('Delete', ['class' => 'btn btn-danger'])}}
            {!! Form::close() !!}
            <a href="/ads/{{$ad->id}}/edit" class="btn btn-light btn-primary pull-right">Edit</a><br>
        @endif
        <h3>{{$ad->title}}</h3>
        <label>{{$ad->description}}</label>
        {{--dd($ad->images)--}}
        @foreach($ad->images as $img)
            <img class="img-thumbnail" src="{{$img->img}}" alt="image{{$img->id}}">
        @endforeach
        <ul class="list-group">
            @foreach($ad->ad_categories as $ac)
                <li class="list-group-item">{{$ac->category->name}}</li>
            @endforeach
        </ul>
        <div class="container my-5">
            <h3>
                Comments:
            </h3>
            @foreach($ad->comments->sortBy('created_at')->reverse() as $comment)
                <div class="row d-flex justify-content-center">
                    <div class="col-md-12 col-lg-10 col-xl-8">
                        <div class="card">
                            <div class="card-body">
                                <div class="d-flex flex-start align-items-center">
                                    <div>
                                        <h6 class="fw-bold text-primary mb-1">{{$comment->alias}}</h6>
                                        <p class="text-muted small mb-0">
                                            {{$comment->created_at}}
                                        </p>
                                    </div>
                                </div>
                                <p class="mt-3 text-dark">
                                    {{$comment->content}}
                                    @if($comment->email == auth()->user()->email || auth()->user()->is_admin)
                                        {!! Form::open(['url' => "/comment/$ad->id", "method" => "POST", "class" => "pull-right"]) !!}
                                        {{Form::hidden('_method', 'DELETE')}}
                                        {{Form::submit('Delete', ['class' => 'btn btn-danger'])}}
                                        {!! Form::close() !!}
                                        <a href="/comment/{{$ad->id}}/edit" class="btn btn-secondary pull-right">Edit</a><br>
                                    @endif
                                </p>
                            </div>
                            <!--<div class="card-footer py-3 border-0" style="background-color: #f8f9fa;">
                                <div class="d-flex flex-start w-100">
                                    <img class="rounded-circle shadow-1-strong me-3"
                                         src="https://mdbcdn.b-cdn.net/img/Photos/Avatars/img%20(19).webp"
                                         alt="avatar" width="40"
                                         height="40"/>
                                    <div class="form-outline w-100">
            <textarea class="form-control" id="textAreaExample" rows="4"
                      style="background: #fff;"></textarea>
                                        <label class="form-label" for="textAreaExample">Message</label>
                                    </div>
                                </div>
                                <div class="float-end mt-2 pt-1">
                                    <button type="button" class="btn btn-primary btn-sm">Post comment</button>
                                    <button type="button" class="btn btn-outline-primary btn-sm">Cancel</button>
                                </div>
                            </div>-->
                        </div>
                    </div>
                </div>
            @endforeach
            {!! Form::open(['url' => "/api/comments", "method" => "POST"]) !!}
            <div class="form-group">
                {{Form::label('email', 'Email')}}
                {{Form::text('email', '', ['class' => 'form-control', 'placeholder' => 'email...'])}}
            </div>
            <div class="form-group">
                {{Form::label('alias', 'Alias')}}
                {{Form::text('alias', '', ['class' => 'form-control', 'placeholder' => 'alias...'])}}
            </div>
            <div class="form-group">
                {{Form::label('content', 'Content')}}
                {{Form::text('content', '', ['class' => 'form-control', 'placeholder' => 'content...'])}}
            </div>
            {{Form::hidden('ad_id', $ad->id)}}
            {{Form::submit('Add comment', ['class' => 'btn btn-dark btn-outline-info'])}}
            {!! Form::close() !!}
        </div>
        <br>
        <small>Written on {{$ad->date_s}} by {{$ad->user->name}}</small><br>
    </div>
@endsection
