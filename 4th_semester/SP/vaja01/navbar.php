<!-- Navbar -->
<nav class="navbar navbar-expand-lg bg-light navbar-light">
  <div class="container">
    <a class="navbar-brand" href="index.php"
      ><img
        id="logo"
        src="https://pixabay.com/get/gf5999548cc45e816302a14a08de6a536c53876f312a82b9c3220ef78259a185d52b39f4864dab36dffc1475b3093f6d28b6ed331a1165eb6488315d330b776e9_640.png"
        alt="Logo"
        draggable="false"
        height="70"
        width="550"
    /></a>
    <button
      class="navbar-toggler"
      type="button"
      data-mdb-toggle="collapse"
      data-mdb-target="#navbarSupportedContent"
      aria-controls="navbarSupportedContent"
      aria-expanded="false"
      aria-label="Toggle navigation"
    >
      <i class="fas fa-bars"></i>
    </button>
    <div class="collapse navbar-collapse" id="navbarSupportedContent">
      <ul class="navbar-nav ms-auto align-items-center">
        <li class="nav-item">
          <a class="nav-link mx-2" href="ads.php"><i class="fas fa-plus-circle pe-2"></i>Ads</a>
        </li>
        <?php
          session_start();
          if(!isset($_SESSION["user"])){
            echo "<li class=\"nav-item ms-3\">
              <a class=\"btn btn-black btn-rounded\" href=\"login.php\">Sign in</a>
            </li>";
          } else {
            echo "<li class=\"nav-item ms-3\">
              <a class=\"btn btn-black btn-rounded\" href=\"sessionDestroy.php\">Log out</a>
            </li>";
          }
        ?>
      </ul>
    </div>
  </div>
</nav>
<!-- Navbar -->
