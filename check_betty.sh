#!/bin/bash

files=$(ls *.c)

for file in $files
do
  betty $file
done

