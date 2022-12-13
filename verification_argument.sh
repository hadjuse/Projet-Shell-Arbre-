#!/bin/bash
#echo "$*"
#if [ $# != 5 ] || [ $# != 6 ]; then
#    echo "Il faut avoir 6 à 5 arguments"
#    exit 1
#fi 

for argument in $@ ; do
    case $argument in
    -w ) echo "moyenne de vent";;
    -t ) echo "jazel";;
esac
done


