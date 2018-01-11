#!/usr/bin/env bash

die()
{
  echo "$1"
  exit 1
}

usage()
{
  prog=$(basename $0)
  echo "Usage: $prog {proj_name}"
  die ""
}


#
# Entry Point
#
proj=$1

if [ "$#" -lt 1 ]; then
  usage
fi


if [ -d "$proj" ]; then
  die "directory '$proj' existed, try a new name?"
fi

cp -R t_lkm $proj
mv $proj/t_lkm.c $proj/${proj}.c
sed -i "s/t_lkm/$proj/g" $proj/Makefile
echo "# Experiment/$proj" > $proj/README.md
