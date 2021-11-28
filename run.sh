#!/bin/sh
meson compile -C build
cp -r res build/res
./build/raylib-meson
