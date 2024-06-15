#!/usr/bin/perl

use strict;

my $incdir=$ARGV[0];
my @headerlist=<$incdir/*.h $incdir*.hh>;
my $header;
my $prototypeflag=0;
my $structflag=0;
my $prototype="";
my $prototypeline="";
my $commentflag=0;
my $headername;

foreach $header (@headerlist){
    open(READFILE,"$header");
    while (<READFILE>){
	s/\n/ /;
	if ($prototypeflag){
	    if (/prototype end/){
		$prototypeflag=0;
		$_="";
	    } else {
		if ($commentflag){
		    if (/\*\//){
			s/^[\S\s]*\*\///;
			$commentflag=0;
		    } else {
			$_="";
		    }
		} elsif (/\/\*/){
		    if (/\*\//){
			s/\/\*[\S\s]*\*\///;
		    } else {
			s/\/\*[\S\s]*//;
			$commentflag=1;
		    }
		}	
		if (/^\#/){
		    $_="";
		}
		if (!$commentflag && /\S/){
		    $prototype .= $_;
		    if (/;\s*$/){
			$_=$prototype;
			s/(\s)+/ /g;
			$headername=$header;
			$headername=~s/$incdir\///;
			print "$headername $_\n";
			$prototype="";
		    } 
		}
	    }
	} elsif (/prototype begin/){
	    $prototypeflag=1;
	}
    }
}
