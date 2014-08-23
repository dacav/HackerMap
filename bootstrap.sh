#!/bin/sh

mkdir -p m4 build-aux
aclocal
autoconf
automake --add-missing
