#!/bin/bash

fibonacci() {
  local n=$1
  local a=0
  local b=1

  if [ $n -eq 0 ]
  then
    echo $a
    return
  fi

  if [ $n -eq 1 ]
  then
    echo $b
    return
  fi

  for((i=2; i<=n; i++))
  do
    local c=$((a + b))
    a=$b
    b=$c
  done

  echo $b
}

if [ $# -eq 0 ]
then
  echo "Usage: $0 <n>"
  exit 1
fi

n=$1
result=$(fibonacci $n)
echo "fib($n) = $result"

