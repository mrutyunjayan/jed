#!/bin/bash

code="$PWD"
opts=-g
cd build > /dev/null
cc $opts $code/code/win32_main.c -o text_editor
cd $code > /dev/null
