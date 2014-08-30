#!/bin/sh

ASTYLE='astyle --suffix=none --style=knf --indent=spaces=4 --indent-namespaces --indent-modifiers'
for fn in `git diff --cached --name-only | egrep '\.(cc|hh)$'`; do
  echo "Fixing style for ${fn}"
  $ASTYLE $fn
done
