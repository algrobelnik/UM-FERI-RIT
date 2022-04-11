@if(Auth()->user()->is_admin)
    @extends('layouts.app')

    @section('content')
        <div class="container">
            <div class="row justify-content-center text-dark">
                <div class="col-md-12">
                    <div class="card">
                        <div class="card-header">{{ __('Users') }}</div>
                        <div class="card-body">
                            @if (session('status'))
                                <div class="alert alert-success" role="alert">
                                    {{ session('status') }}
                                </div>
                            @endif

                            <a href="/users/create" class="btn btn-primary position-absolute top-0 end-0">Create user</a>
                            @if(count($users) > 0)
                                <table class="table text-dark">
                                    <tr>
                                        <th>Email</th>
                                        <th>Name</th>
                                        <th>Surname</th>
                                        <th>Phone</th>
                                        <th>Gender</th>
                                        <th>Age</th>
                                        <th>Address</th>
                                        <th>Admin</th>
                                        <th></th>
                                    </tr>
                                    @foreach($users as $user)
                                        <tr>
                                            <td>{{$user->email}}</td>
                                            <td>{{$user->name}}</td>
                                            <td>{{$user->surname}}</td>
                                            <td>{{$user->phone}}</td>
                                            <td>{{$user->gender}}</td>
                                            <td>@if($user->bday < \Carbon\Carbon::now()){{\Carbon\Carbon::parse($user->bday)->age}} [{{$user->bday}}]@endif</td>
                                            <td>{{$user->address}}</td>
                                            <td>{{$user->is_admin?"YES":"NO"}}</td>
                                            <td><a href="/users/{{$user->id}}/edit" class="btn btn-secondary">Edit</a>
                                                @if(!$user->is_admin)
                                                    {!! Form::open(['url' => "/users/$user->id", "method" => "POST", "class" => "pull-right"]) !!}
                                                    {{Form::hidden('_method', 'DELETE')}}
                                                    {{Form::submit('Delete', ['class' => 'btn btn-danger'])}}
                                                    {!! Form::close() !!}
                                                @endif
                                            </td>
                                        </tr>
                                    @endforeach
                                </table>
                            @else
                                <p>You see no user outside yourself. Admins cannot be deleted.</p>
                            @endif
                        </div>
                    </div>
                </div>
            </div>
        </div>
    @endsection
@endif
