@extends('layout.app')
@section('content')
<form method="get" action="index.php">
    <input type="text" name="textFilter"><br>
    Show hidden: <input type="checkbox" name="checkBoxFilter"><br>
    <button type="submit">Filter</button>
</form>
@endsection
