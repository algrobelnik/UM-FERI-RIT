<!-- Navbar
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
        <php
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
Navbar -->
<nav class="navbar navbar-expand-md navbar-dark bg-dark shadow-sm">
    <div class="container">
        <a class="navbar-brand" href="{{ url('/') }}">
            <i class="fa fa-laptop"></i>
            {{ config('app.name', 'Laravel') }}
        </a>
        <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarSupportedContent"
                aria-controls="navbarSupportedContent" aria-expanded="false" aria-label="{{ __('Toggle navigation') }}">
            <span class="navbar-toggler-icon"></span>
        </button>

        <div class="collapse navbar-collapse" id="navbarSupportedContent">
            <!-- Left Side Of Navbar -->
            <ul class="navbar-nav me-auto">
                <li class="nav-item">
                    <a class="nav-link mx-2" href="/ads/create"><i class="fas fa-plus-circle pe-2"></i>Create ad</a>
                </li>
                @if (isset(\Illuminate\Support\Facades\Auth::user()->is_admin))
                    <li class="nav-item">
                        <a class="nav-link mx-2" href="/users/create"><i class="fas fa-plus-circle pe-2"></i>Create user</a>
                    </li>
                @endif
            </ul>

            <!-- Right Side Of Navbar -->
            <ul class="navbar-nav ms-auto">
                <!-- Authentication Links -->
                @guest
                    @if (Route::has('login'))
                        <li class="nav-item">
                            <a class="nav-link" href="{{ route('login') }}">{{ __('Login') }}</a>
                        </li>
                    @endif

                    @if (Route::has('register'))
                        <li class="nav-item">
                            <a class="nav-link" href="{{ route('register') }}">{{ __('Register') }}</a>
                        </li>
                    @endif
                @else
                    <li class="nav-item dropdown">
                        <a id="navbarDropdown" class="nav-link dropdown-toggle" href="#" role="button"
                           data-bs-toggle="dropdown" aria-haspopup="true" aria-expanded="false" v-pre>
                            {{ Auth::user()->name }}
                        </a>
                        <div class="dropdown-menu dropdown-menu-end" aria-labelledby="navbarDropdown">
                            <a class="dropdown-item" href="{{ route('home') }}">
                                <i class="fa fa-home"></i>
                                {{ __('Home') }}
                            </a>
                            @if (\Illuminate\Support\Facades\Auth::user()->is_admin)
                                <a class="dropdown-item" href="{{ route('users.index') }}">
                                    <i class="fa fa-user-circle"></i>
                                    {{ __('Users') }}
                                </a>
                            @endif
                            <a class="dropdown-item" href="{{ route('logout') }}"
                               onclick="event.preventDefault();
                                                     document.getElementById('logout-form').submit();">
                                <i class="fa fa-sign-out"></i>
                                {{ __('Logout') }}
                            </a>
                            <form id="logout-form" action="{{ route('logout') }}" method="POST" class="d-none">
                                @csrf
                            </form>
                        </div>
                    </li>
                @endguest
            </ul>
        </div>
    </div>
</nav>
