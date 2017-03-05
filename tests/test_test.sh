#!/bin/sh

test src
test -e /src/3And.cpp && echo yes
test -e tests
test -f tests && echo no
test -f tests/exit.sh
test -d src
[ src/2Command.h ] && echo yes
[ -e /hello/no/hello ] && echo no
[ -f src/2Command.h ]
[ -d src ]
