<?php
  session_start();
  if(!isset($_SESSION["user"])){
    $host = $_SERVER['HTTP_HOST'];
    $uri = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');
    header("Location: http://$host$uri/login.php");
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
    <form action="logic.php" method="post" enctype='multipart/form-data'>
      Title: <input type="text" name="title" required><br>
      <textarea rows="4" cols="50" name="description" required>Description</textarea><br>
      <label>Upload Your Image
        <input type="file" name="imgs[]" accept="image/*" multiple required/>
      </label><br>
      <label for="category" required>Category: </label>
      <select name="category[]" id="category" multiple required>
        <?php
          $servername = "localhost";
          $username = "school";
          $password = "school";
          $database = "school";
          $conn = new mysqli($servername, $username, $password, $database);
          $sql = "SELECT * FROM category";
          $conn->real_escape_string($sql);
          $result = mysqli_query($conn, $sql);
          if (mysqli_num_rows($result) > 0) {
            while($row = mysqli_fetch_array($result)) {
              $rows[] = $row;
            };
            foreach($rows as $row){
              echo "<option value=\"".$row["ID"]."\">".$row["name"]."</option>";
            }
          }
          $conn->close();
        ?>
      </select>
      <input type="hidden" name="type" value="ads" />
      <input type="submit">
    </form>
  </body>
</html>
