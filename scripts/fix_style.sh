#!/bin/sh

ASTYLE='astyle --suffix=none --style=linux --indent=spaces=4 --indent-namespaces --indent-classes'
if [ -z $1 ]; then
  for fn in `git diff --cached --name-only | egrep '\.(cc|hh)$'`; do
    save="$(dirname ${fn})/.$(basename ${fn}).non-staged"
    git diff $fn > $save
    git co $fn
    $ASTYLE $fn
    git add $fn
    [ `wc -c < $save` = 0 ] || git apply < $save
  done
else
  for fn in $@; do
    echo "Fixing style for ${fn}"
    $ASTYLE $fn
  done
fi
