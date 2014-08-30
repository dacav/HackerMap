CHANGED=`git diff --cached --name-only`
echo "Fixing style for ${CHANGED}"

astyle --suffix=none --style=knf --indent=spaces=4 --indent-namespaces --indent-modifiers ${CHANGED}
