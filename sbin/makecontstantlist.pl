#!/usr/bin/perl

use strict;
my $incdir=$ARGV[0];
my @headerlist=<$incdir/*.h $incdir/*.hh>;
my $header;
my $constantflag=0;
my $constant="";
my $constantline="";
my $commentflag=0;
my $bracketnumber=0;
my $headername;

foreach $header (@headerlist){
    open(READFILE,"$header");
    while (<READFILE>){
	if ($constantflag){
	    if (/constant end/){
		$constantflag=0;
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
		    if (!$bracketnumber){
			if (/\{/) {
			    $bracketnumber=1;
			    $constant .= $_;
			} else {    
			    $constant .= $_;
			    if (/;$/){
				$headername=$header;
				$headername=~s/$incdir\///;
				print "$headername $constant\n";
				$constant="";
			    }
			}
		    } else {
			if (/\{/) {
			    $bracketnumber++;
			} elsif (/\}/) {
			    $bracketnumber--;
			}
			$constant .= $_;
			if (!$bracketnumber){
			    s/[Ss]*\}//;
			    if (/;$/){
				$headername=$header;
				$headername=~s/$incdir\///;
				print "$headername $constant\n";
				$constant="";
			    }
			}
		    }				
		}
	    }
	} elsif (/constant begin/){
	    $constantflag=1;
	}
    }
}
