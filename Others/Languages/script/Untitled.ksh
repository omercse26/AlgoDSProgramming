#!/bin/ksh
if test -f echo.pl
then
echo echo.pl exists
fi

if [-f echo.pl]
then
echo echo.pl is a file
fi
