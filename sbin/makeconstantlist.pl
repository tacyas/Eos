#!/usr/bin/perl

use strict;
my $incdir=$ARGV[0];
my @headerlist=<$incdir/*.h $incdir/*.hh>;
my $header;
my $headername;
my $constantflag=0;
my $constant="";
my $constantline="";
my $commentflag=0;
my $bracketnumber=0;
my $constantname="";

foreach $header (@headerlist){
    $constantflag=0;
    $constant="";
    $constantline="";
    $commentflag=0;
    $bracketnumber=0;
    $constantname="";
    open(READFILE,"$header");
    chomp;
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
		if (!$commentflag && /\S/){
		    if (!$bracketnumber){
			if (/\{/) {
			    $bracketnumber=1;
			    $constant .= $_;
			} else {    
			    $constant .= $_;
			    if (/;\s*$/){
				$headername=$header;
				$headername=~s/$incdir\///;
				$constant=~s/\n/\\n/g;
				print "$headername $constant\n";
				$constant="";
			    }
			}
		    } else {
			if (/\{/) {
			    $bracketnumber++;
			} 
			if (/\}/) {
			    $bracketnumber--;
			}
			$constant .= $_;
			if (!$bracketnumber){
			    s/[Ss]*\}//;
			    if (/;$\s*/){
				$headername=$header;
				$headername=~s/$incdir\///;
				$constant=~s/\n/\\n/g;
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
close (READFILE);
}
