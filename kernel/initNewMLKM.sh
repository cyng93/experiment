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
Proj=`echo "$proj" | sed -r 's/(^|_)([a-z])/\U\2/g'  `
PROJ=`echo "$proj" | sed 's/\(.*\)/\U\1/'`

if [ "$#" -lt 1 ]; then
  usage
fi


if [ -d "$proj" ]; then
  die "directory '$proj' existed, try a new name?"
fi

cp -R my_mlkm_template $proj

cd $proj
echo "# Experiment/$proj" > README.md
sed -i "s/my_mlkm_template/$proj/g" Makefile
mv src/sample.c src/${proj}.c
mv include/sample.h include/${proj}.h

for f in `find . -type f`; do
    sed -i "s/sample/${proj}/g" $f
    sed -i "s/Sample/${Proj}/g" $f
    sed -i "s/SAMPLE/${PROJ}/g" $f
done
