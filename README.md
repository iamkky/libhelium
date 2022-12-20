# Lib Helium

A small compact lib to represent a dom structure.

The main element of lib is the He (Html Element), that represents a minimalist Html Element.

With the help of HeAttr a minimalist Dom can be construted and rendered later.

Why name it LibHelium instead of simpler LibHe, hlib or something like it?

It's just to avoid poluting name space with too short names.

Build
--------

to build just use 'make'

if libabd is not in system locations (/usr/include and /usr/lib) add those lines before build

export CFLAG=-I<PATH TO LIBABD INCLUDE>
export LIBABD=<PATH TO LIBABD>



