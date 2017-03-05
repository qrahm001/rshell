#!/bin/sh

(echo hi)
(echo bye); (echo hi && echo bye);
(echo hello && echo goodbye) || (ls && ls -a)
