#!/bin/sh

if [ -z $1 ]; then
  FILES=`git diff --cached --name-only | egrep '\.(cc|hh)$'`
else
  FILES=$@
fi

ASTYLE='astyle --suffix=none --style=knf --indent=spaces=4 --indent-namespaces --indent-modifiers'
for fn in $FILES; do
  echo "Fixing style for ${fn}"
  $ASTYLE $fn
done
