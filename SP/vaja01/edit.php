<?php 
  session_start();
  if(!isset($_SESSION["user"]) || !isset($_GET["id"])){
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
    <form action="logic.php" method="post">
        <?php
          $servername = "localhost";
          $username = "school";
          $password = "school";
          $database = "school";
          $conn = new mysqli($servername, $username, $password, $database);
          $sql = "SELECT DISTINCT * FROM category";
          $sql2 = "SELECT DISTINCT c.* FROM ad_category ac JOIN category c ON ac.categoryID = c.ID WHERE ac.adID = ".$_GET["id"];
          $sql3 = "SELECT * FROM ad WHERE ID = ".$_GET["id"];
          $conn->real_escape_string($sql);
          $conn->real_escape_string($sql2);
          $conn->real_escape_string($sql3);
          $result = mysqli_query($conn, $sql);
          $result2 = mysqli_query($conn, $sql2);
          $result3 = mysqli_query($conn, $sql3);
          if (mysqli_num_rows($result) > 0 && mysqli_num_rows($result2) > 0 && mysqli_num_rows($result3) > 0) {
            $ad = mysqli_fetch_array($result3);
            echo "Title: <input type=\"text\" name=\"title\" value=\"".$ad["title"]."\" required><br>";
            echo "<textarea rows=\"4\" cols=\"50\" name=\"description\" required>".$ad["description"]."</textarea><br>";
            echo "<label>Upload Your Image
              <input type=\"file\" name=\"imgs[]\" accept=\"image/*\" multiple required/>
            </label><br>";
            echo "<label for=\"category\" required >Category: </label>";
            echo "<select name=\"category[]\" id=\"category\" multiple required>";
            while($row = mysqli_fetch_array($result)) {
              $rows[] = $row;
            };
            while($row = mysqli_fetch_array($result2)) {
              $rows2[] = $row;
            };
            foreach($rows as $row){
              $check = false;
              foreach($rows2 as $row2){
                if($row["ID"] == $row2["ID"]){
                  $check = true;
                }
              }
              if ($check) {
                echo "<option value=\"".$row["ID"]."\" selected>".$row["name"]."</option>";
              } else {
                echo "<option value=\"".$row["ID"]."\">".$row["name"]."</option>";
              }
            } 
          }
          echo "<input type=\"hidden\" name=\"adID\" value=\"".$_GET["id"]."\" /><br>";

          $conn->close();
        ?>
      </select>
      <input type="hidden" name="type" value="update" />
      <input type="submit">
    </form>
    <form action="logic.php" method="post">
      <?php echo "<input type=\"hidden\" name=\"adID\" value=\"".$_GET["id"]."\" />"; ?>
      <input type="hidden" name="type" value="delete" />
      <input type="submit" value="DELETE">
    </form>
  </body>
</html>
