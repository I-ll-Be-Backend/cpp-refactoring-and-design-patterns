#!/bin/sh
# Compiles every step of every lesson in gcc:14: the check each lesson passed before its video went out.
# Needs Docker. A step folder holding .nocheck does not compile on purpose and is skipped.
docker run --rm --entrypoint /bin/sh -v "$PWD:/w" gcc:14 -c '
true
cd /w; fail=0
for f in */step-*/*.cpp; do
  [ -e "$f" ] || continue
  [ -e "$(dirname "$f")/.nocheck" ] && continue
  d=$(mktemp -d)
  if ( g++ -std=c++20 -fsyntax-only $f ) >/tmp/log 2>&1; then echo "ok    $f"; else echo "FAIL  $f"; cat /tmp/log; fail=1; fi
done
exit $fail'
