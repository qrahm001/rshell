#!/bin/sh

ls -a; echo hello; mkdir one
rm -r one || echo didnt work; ls
ls && ls -a
echo this || echo or that
