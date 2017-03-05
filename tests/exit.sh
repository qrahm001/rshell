#!/bin/sh

exit
echo A && exit
cd src || echo A && exit #exit should fail as that command is built into bash
exit || ls -a && mkdir side
echo Hello world; ls -a && mkdir secondshell; exit
