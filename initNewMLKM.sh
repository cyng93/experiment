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

cp -R my_mlkm_template $proj
sed -i "s/my_mlkm_template/$proj/g" $proj/Makefile
echo "# Experiment/$proj" > $proj/README.md
