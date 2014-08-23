#!/bin/sh

mkdir -p m4 build-aux
aclocal
autoheader
autoconf
automake --add-missing
