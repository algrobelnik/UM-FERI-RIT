<?php
  session_start();
  if(isset($_SESSION["user"])){
    $host = $_SERVER['HTTP_HOST'];
    $uri = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');
    header("Location: http://$host$uri/index.php");
  }
?>
<!DOCTYPE html>
<html>
<head>
<meta charset="utf-8">
<title>SP_vaja01</title>
</head>
<body>
  
  <form action="logic.php" method="post">
    Username: <input type="text" name="uname" required><br>
    Password: <input type="password" name="pass" required><br>
    Email: <input type="email" name="email" required><br>
    Name: <input type="text" name="name" required><br>
    Surname: <input type="text" name="surname" required><br>
    Address: <input type="address" name="address"><br>
    Mobile: <input type="phone" name="phone"><br>
    Gender: <input type="radio" id="male" name="gender" value="male">
    <label for="male">Male</label>
    <input type="radio" id="female" name="gender" value="female">
    <label for="female">Female</label>
    <input type="radio" id="und/bin" name="gender" value="undefined/non binary">
    <label for="und/bin">Undefined/Non-binary</label><br>
    Day of birth: <input type="date" name="bday"><br> 
    <input type="submit">
    <input type="hidden" name="type" value="register" />
  </form>
</body>

</html>

