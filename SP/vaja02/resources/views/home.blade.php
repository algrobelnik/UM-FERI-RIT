@extends('layouts.app')

@section('content')
    <div class="container">
        <div class="row justify-content-center text-dark">
            <div class="col-md-8">
                <div class="card">
                    <div class="card-header">{{ __('Dashboard') }}</div>

                    <div class="card-body">
                        @if (session('status'))
                            <div class="alert alert-success" role="alert">
                                {{ session('status') }}
                            </div>
                        @endif

                        <a href="/ads/create" class="btn btn-primary position-absolute top-0 end-0">Create Ad</a>
                        <h3>Your ads</h3>
                            @if(count($ads) > 0)
                                <table class="table text-dark">
                                    <tr>
                                        <th>Title</th>
                                        <th></th>
                                        <th></th>
                                    </tr>
                                    @foreach($ads as $ad)
                                        <tr>
                                            <td>{{$ad->title}}</td>
                                            <td><a href="/ads/{{$ad->id}}/edit" class="btn btn-secondary">Edit</a></td>
                                            <td>
                                                {!! Form::open(['url' => "/ads/$ad->id", "method" => "POST", "class" => "pull-right"]) !!}
                                                    {{Form::hidden('_method', 'DELETE')}}
                                                    {{Form::submit('Delete', ['class' => 'btn btn-danger'])}}
                                                {!! Form::close() !!}
                                            </td>
                                        </tr>
                                    @endforeach
                                </table>
                            @else
                                <p>You have no posts</p>
                            @endif
                    </div>
                </div>
            </div>
        </div>
    </div>
@endsection
