<!-- Navbar -->
<nav class="navbar navbar-expand-lg bg-dark navbar-dark">
  <div class="container">
    <a class="navbar-brand" href="/"
      ><img
        id="logo"
        src="/logo.png"
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
          <a class="nav-link mx-2" href="/ads/create"><i class="fas fa-plus-circle pe-2"></i>Create ad</a>
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
