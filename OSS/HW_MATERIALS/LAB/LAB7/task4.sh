#!/bin/bash

if [ $# -eq 0 ]
then
  echo "Usage: $0 <directory>"
  exit 1
fi

dir=$1
total=0

if [ ! -d $dir ]
then
  echo "$dir is not a directory"
  exit 1
fi

for file in $dir/*
do
  if [ -f $file ]
  then
    count=$(wc -l < $file)
    total=$((total + count))
  fi
done

echo $total

