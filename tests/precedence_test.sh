#!/bin/sh

(echo a)
(echo a && echo b) && (echo c && echo d)
(echo a || echo b) || (echo c || echo d)
([ -e /filepath ])
echo A || (echo B && echo C); echo D
test rshell.cpp; (echo A && echo B) || echo C
(echo A || (echo B))
(echo A || echo B) && (echo C || echo D)
