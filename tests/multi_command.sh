#!/bin/sh

ls -a; echo hello; mkdir test
ls -a; echo hello && mkdir test || echo world; git status
echo A && echo B || echo C && echo D || echo E
git log; git checkout exec || echo Error
git branch; git status && git log || echo error; ls -a
cd .. || echo Expected result
mkdir test; cd test || rmdir test && echo cd unavailable
echo Look at result ; echo Can end with semicolon ;
ls -a; echo hello && mkdir test || echo world; git status
echo Program ; echo is ; echo running ;
