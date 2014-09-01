boil2d
======
Aims to become a boilerplate framework for creating custom 2D game engines in
C++. Not a game engine itself, but a launching point for one. The goal is to be
able to clone a repo and have a basic project ready to go for fast prototyping,
gamedev compos, etc., without resorting to using a full-blown engine.

Wrap libraries such as SFML and Box2D, and provide classes for a finite state
machine (or state stack), fixed timestep game loop w/variable FPS and 
interpolation, menus, resource loading, config files, etc.

An evolving/experimental work in progress; testing & learning only at this
point.


requirements
============
SFML >= 2.0
Box2D >= 2.3
