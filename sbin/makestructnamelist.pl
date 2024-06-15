#!/usr/bin/perl

use strict;
my $out=$ARGV[0];
my $in=$ARGV[1];
my @inline;
my $header;
my $structname;
my $inword;
my $outfile;
my $structflag=0;

open(READFILE,"$in");
open(STRUCTNAMELIST,">$out");
while (<READFILE>){
    chomp;
    ($header)=/^(\S+)/;
    if (/typedef/){
	($structname)=/(\S+);\\n$/;
	$structname=~s/(\S+)\}//;
    } else {
	($structname)=/struct (\S+) *\{/;
    }	
    if ($structname=~/\S+/){
	print STRUCTNAMELIST "$structname\n";
    }
}
