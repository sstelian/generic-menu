It implements the menu as a tree
using smart pointers and STL containers. It is suitable for use in robotics and
embedded systems where no proper user interface implementations are available.
Leaf nodes can have callbacks attached to them in order to interact with items
outside of the menu itself.

The example uses iostream, so it can be easily tested on a regular PC.

The Makefile builds the example using g++.

Copyright (c) 2018 Stelian Saracut
