<?php
  session_start();
  $servername = "localhost";
  $username = "school";
  $password = "school";
  $database = "school";
  $host = $_SERVER['HTTP_HOST'];
  $uri = rtrim(dirname($_SERVER['PHP_SELF']), '/\\');

  // Create connection
  $conn = new mysqli($servername, $username, $password, $database);

  // Check connection
  if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
  }
  $sql = "";
  if (!(isset($_POST["type"]) || isset($_GET["type"]))) { 
    header("Location: http://$host$uri/login.php"); 
  }
  if ($_POST["type"] == "register") {
    $uname = '"'.$_POST["uname"].'"';
    $pass = '"'.hash("sha256", $_POST["pass"]).'"';
    $email = '"'.$_POST["email"].'"';
    $name = '"'.$_POST["name"].'"';
    $surname = '"'.$_POST["surname"].'"';
    $address = ($_POST["address"] == "" ? 'NULL' : '"'.$_POST["address"].'"');
    $phone = ($_POST["phone"] == "" ? 'NULL' : '"'.$_POST["phone"].'"'); 
    $gender = ($_POST["gender"] == "" ? 'NULL' : '"'.$_POST["gender"].'"'); 
    $bday = ($_POST["bday"] == "" ? 'NULL' : '"'.$_POST["bday"].'"'); 
    $sql = "INSERT INTO user (uname, pass, email, name, surname, address, phone, gender, bday) VALUES (".$uname.", ".$pass.", ".$email.", ".$name.", ".$surname.", ".$address.", ".$phone.", ".$gender.", ".$bday.")";
    $conn->real_escape_string($sql);
    echo "$sql<br>";
    if (mysqli_query($conn, $sql)) {
      header("Location: http://$host$uri/login.php");
    } else {
      header("Location: http://$host$uri/register.php");
    }
  } else if ($_POST["type"] == "login") {
    $sql = "SELECT * FROM user WHERE uname='".$_POST["uname"]."' AND pass='".hash('sha256',$_POST["pass"])."'";
    $conn->real_escape_string($sql);
    $result = mysqli_query($conn, $sql); 
    if (mysqli_num_rows($result) > 0) {
      $_SESSION["user"] = mysqli_fetch_array($result);
      header("Location: http://$host$uri/index.php");
    } else {
      header("Location: http://$host$uri/login.php");
    }
  } else if ($_POST["type"] == "ads"){
    $title = '"'.$_POST["title"].'"';
    $description = '"'.$_POST["description"].'"';
    $sql = "INSERT INTO ad (title, description, userID) VALUES (".$title.", ".$description.", ".$_SESSION['user']['ID'].")";
    $imgsName = $_FILES["imgs"]["tmp_name"];
    $imgsType = $_FILES["imgs"]["type"];
    $conn->real_escape_string($sql);
    if(mysqli_query($conn, $sql)){
      $lastID = $conn->insert_id;
      $categories = $_POST["category"];
      foreach ($categories as $cats){
        $sql = "INSERT INTO ad_category (adID, categoryID) VALUES (".$lastID.", ".$cats.")";
        $conn->real_escape_string($sql);
        $result = mysqli_query($conn, $sql);
      };
      for ($i = 0; $i < count($imgsType); $i++){
        $contents = file_get_contents($imgsName[$i]);
        $base64 = base64_encode($contents);
        $blob = ('data:' . $imgsType[$i] . ';base64,' . $base64);
        $sql = "INSERT INTO image (img, adID) VALUES (\"".$blob."\", ".$lastID.")";
        $conn->real_escape_string($sql);
        $result = mysqli_query($conn, $sql);
      };
    }
    header("Location: http://$host$uri/index.php");
  } else if ($_POST["type"] == "update"){
    $title = '"'.$_POST["title"].'"';
    $description = '"'.$_POST["description"].'"';
    $sql = "UPDATE ad SET title=".$title.", description=".$description.", date_e=(UNIX_TIMESTAMP() + 2592000) WHERE ad.ID = ".$_POST["adID"];
    $imgsName = $_FILES["imgs"]["tmp_name"];
    $imgsType = $_FILES["imgs"]["type"];
    $conn->real_escape_string($sql);
    if(mysqli_query($conn, $sql)){
      $categories = $_POST["category"];
      foreach ($categories as $cats){
        $sql = "INSERT INTO ad_category (adID, categoryID) VALUES (".$_POST["adID"].", ".$cats.")";
        $conn->real_escape_string($sql);
        $result = mysqli_query($conn, $sql);
      };
      for ($i = 0; $i < count($imgsType); $i++){
        $contents = file_get_contents($imgsName[$i]);
        $base64 = base64_encode($contents);
        $blob = ('data:' . $imgsType[$i] . ';base64,' . $base64);
        $sql = "INSERT INTO image (img, adID) VALUES (\"".$blob."\", ".$lastID.")";
        $conn->real_escape_string($sql);
        $result = mysqli_query($conn, $sql);
      };
    }
    header("Location: http://$host$uri/index.php");
  } else if ($_POST["type"] == "delete" && isset($_POST["adID"])){
    $sql1 = "DELETE FROM ad_category WHERE adID = ".$_POST["adID"];
    $sql2 = "DELETE FROM image WHERE adID = ".$_POST["adID"];
    $sql3 = "DELETE FROM ad WHERE ID = ".$_POST["adID"];
    $conn->real_escape_string($sql1);
    $conn->real_escape_string($sql2);
    $conn->real_escape_string($sql3);
    $result = mysqli_query($conn, $sql1);
    $result = mysqli_query($conn, $sql2);
    $result = mysqli_query($conn, $sql3);
    header("Location: http://$host$uri/index.php");
  }
  $conn->close();
?>
