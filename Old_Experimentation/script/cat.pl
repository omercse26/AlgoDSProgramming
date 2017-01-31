#!/usr/bin/perl

sub print_file 
{
 my $file = shift;
 open FILE,$file;
 while (my $line = <FILE>)
 {
   print $line;
 }
}

sub cat
{
 # while (my $file = shift)
  foreach my $file (@_)
  {
   print_file $file;
  }
 # foreach (@_)
 # {
 #   print $_;
 # }  
   
}
cat @ARGV
