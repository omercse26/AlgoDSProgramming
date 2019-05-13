#!/bin/ksh
echo "is it morning? Please answer yes or no"
read timeofday
if [ "$timeofday" = "yes" ]
then
  echo "good moring"
elif [ "$timeofday" = "no" ]; then
  echo good evening
else
  echo not valid
fi
exit 0
