#!/bin/ksh
myvar="hi thr"
echo $myvar
echo "$myvar"
echo '$myvar'
echo enter some text
read myvar
echo '$myvar' now equals $myvar
exit 0
