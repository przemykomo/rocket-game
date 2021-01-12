# Minimal raylib + Meson C/C++ template
Template project for C/C++ applications using [raylib](https://www.raylib.com/) built using [Meson](https://mesonbuild.com/).

## Setting up
Native builds:

    $ meson setup build
    # compile with
    $ meson compile -C build

Web builds:

    $ meson setup --cross-file cross-file/web.ini build/web
    # compile with
    $ meson compile -C build/web

Cross-compiled Windows 32 builds using [MinGW](http://mingw.org):

    $ meson setup --cross-file cross-file/windows32.ini build/win32
    # compile with
    $ meson compile -C build/win32