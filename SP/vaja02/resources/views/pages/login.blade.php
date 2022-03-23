@extends('layout.app')
@section('content')
<form action="logic.php" method="post">
    Username: <input type="text" name="uname"><br>
    Password: <input type="password" name="pass"><br>
    <input type="hidden" name="type" value="login" />
    <input type="submit">
</form>
<a href="register.php">register HERE</a>
@endsection
