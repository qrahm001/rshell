#!/bin/sh

test bin
test -e bin
test -e Makefile
test -d bin
test -d Makefile
test -f bin
test -f Makefile
[ bin] && ls
[ -d bin] || ls
[ -f bin]; ls
