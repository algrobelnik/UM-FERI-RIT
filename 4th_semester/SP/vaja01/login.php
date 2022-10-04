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
  <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">
  <meta charset="utf-8">
  <title>SP_vaja01</title>
  <link href="style.css" rel="stylesheet" type="text/css">
</head>
<body>
  <?php require_once('navbar.php'); ?>
  <form action="logic.php" method="post">
    Username: <input type="text" name="uname"><br>
    Password: <input type="password" name="pass"><br>
    <input type="hidden" name="type" value="login" />
    <input type="submit">
  </form>
  <a href="register.php">register HERE</a>
</body>

</html>

