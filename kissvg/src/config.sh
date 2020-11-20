#!/bin/bash

#   osstring=`uname`
#
#   if [ "$osstring" = "Darwin" ]; then
#   	CC=gcc-10
#   elif [ "$osstring" = "Linux" ]; then
#   	CC=gcc
#   else
#       echo "Operating System not recognized"
#       echo "Only MacOSX and Linux supported"
#       echo "Exiting script"
#       exit 1
#   fi
CC=gcc

echo "Clearing older files..."
rm -f *.so
rm -f *.o

echo "Compiling KissVG..."
CompilerArgs1="-std=c89 -ansi -pedantic -pedantic-errors -Wall -Wextra"
CompilerArgs2="-Wpedantic -Wmisleading-indentation"
CompilerArgs3="-Wmissing-prototypes -Wold-style-definition"
CompilerArgs4="-Wstrict-prototypes -I../../ -DNDEBUG -g -fPIC -O2 -c"
CompilerArgs="$CompilerArgs1 $CompilerArgs2 $CompilerArgs3 $CompilerArgs4"

echo -e "\n\tCompiler Options:"
echo -e "\t\t$CompilerArgs1"
echo -e "\t\t$CompilerArgs2"
echo -e "\t\t$CompilerArgs3"
echo -e "\t\t$CompilerArgs4"


for filename in ./*.c; do
    echo -e "\t\tCompiling: $filename"
    $CC $CompilerArgs $filename
done

#   sharedobjectlist=""
#   for filename in ./*.o; do
#       sharedobjectlist="$sharedobjectlist $filename"
#   done

# echo "Moving to /usr/local/lib/libkissvg.so"
# sudo mv libkissvg.so /usr/local/lib/libkissvg.so

echo "Cleaning up..."
rm -f *.o

echo "Done"
