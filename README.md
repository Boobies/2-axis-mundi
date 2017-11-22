Axis Mundi 2D
=============

*2 Axis Mundi* is part of the *Axis Mundi* collection of game engines. The name
is both a pun on the fact that this is an engine for 2D games and a skeptic's
pun on a part of the world where reality meets fantasy: video games.

*2 Axis Mundi* is fast, portable, flexible, and exposes a C API to C, C++, and
Objective-C programs; other languages may require a custom wrapper. Since there
is no proper documentation, programmers are encouraged to study the headers.

Source Code, Building, and Linking
----------------------------------

Below are the prerequisites for this engine:

* [SDL 2.0](http://libsdl.org/index.php)

The following command will clone the *2 Axis Mundi* repository:

    git clone --recursive https://github.com/Boobies/2-axis-mundi

In order to build and install the library, use the following command:

    make install

Finally, here is an example of how to link against it:

    c99 foo.c -l am2d_engine -l SDL2

License
-------

*2 Axis Mundi* is free software licensed under the terms and conditions of the
*GNU Lesser General Public License*. For more details, see the `COPYING` and
`COPYING.LESSER` files.
