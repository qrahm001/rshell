#!/bin/sh

ls # -a
mkdir test # && rmdir test
echo A && echo B; #nothing is here
execvp error #command should fail
git status || git log; git checkout master # ls
