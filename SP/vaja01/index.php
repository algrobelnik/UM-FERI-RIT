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
    <form method="get" action="index.php">
      <input type="text" name="textFilter"><br>
      Show hidden: <input type="checkbox" name="checkBoxFilter"><br>
      <button type="submit">Filter</button>
    </form>
    <div>
      <?php
        $servername = "localhost";
        $username = "school";
        $password = "school";
        $database = "school";
        // Create connection
        $conn = new mysqli($servername, $username, $password, $database);
        if ($conn->connect_error){
          die("Connection failed: ". $conn->connect_error);
        }
        $sql = "SELECT DISTINCT a.* FROM ad a JOIN ad_category ac ON a.ID = ac.adID JOIN category c ON ac.categoryID = c.ID";
        $sql2 = "SELECT DISTINCT i.img FROM ad a JOIN ad_category ac ON a.ID = ac.adID JOIN category c ON ac.categoryID = c.ID JOIN image i ON i.adID = a.ID";
        $edit = false;
        if(isset($_SESSION["user"])){
            $edit = true;
            $sql = "SELECT DISTINCT a.* FROM ad a JOIN ad_category ac ON a.ID = ac.adID JOIN category c ON ac.categoryID = c.ID WHERE a.userID =".$_SESSION["user"]["ID"];
            $sql2 = "SELECT DISTINCT i.img FROM ad a JOIN ad_category ac ON a.ID = ac.adID JOIN category c ON ac.categoryID = c.ID JOIN image i ON i.adID = a.ID WHERE a.userID =".$_SESSION["user"]["ID"];
        }
        if (!isset($_GET["checkBoxFilter"]) || $_GET["checkBoxFilter"] != "on"){
          $filter = " AND a.date_s < UNIX_TIMESTAMP(NOW()) AND a.date_e > UNIX_TIMESTAMP(NOW())";
          $sql .= $filter;
          $sql2 .= $filter;
        }
        if (isset($_GET["textFilter"])){
          $filter = " AND (a.title RLIKE \"".$_GET["textFilter"]."\" OR a.description RLIKE \"".$_GET["textFilter"]."\" OR c.name RLIKE \"".$_GET["textFilter"]."\")";
          $sql .= $filter;
          $sql2 .= $filter;
        }
        $sql .= " ORDER BY a.date_s DESC";
        $sql2 .= " ORDER BY a.date_s DESC";
        $conn->real_escape_string($sql);
        $result = mysqli_query($conn, $sql);
        $conn->real_escape_string($sql2);
        $result2 = mysqli_query($conn, $sql2);
        if (mysqli_num_rows($result) > 0) {
          while($res = mysqli_fetch_array($result)) {
            echo "<h3>".$res["title"]."</h3><h5>".$res["description"]."</h5>";
            if(mysqli_num_rows($result2) > 0){
              while($res2 = mysqli_fetch_array($result2)) {
                echo "<img src=\"".$res2["img"]."\" height=250></img>";
              }
            }
            $sql3 = "SELECT DISTINCT c.* FROM ad a JOIN ad_category ac ON a.ID = ac.adID JOIN category c ON ac.categoryID = c.ID WHERE a.ID = ".$res["ID"];
            $conn->real_escape_string($sql3);
            $result3 = mysqli_query($conn, $sql3);
            if (mysqli_num_rows($result3) > 0) {
              echo "<ul>";
              while($res3 = mysqli_fetch_array($result3)) {
                echo "<li>".$res3["name"]."</li>";
              }
              echo "</ul>";
            }
            if($edit){
              echo "<br><a href=\"edit.php?id=".$res["ID"]."\">EDIT</a>";
            }
          }
        }
        $conn->close();
      ?>
    </div>
  </body>
</html>
