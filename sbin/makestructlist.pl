#!/usr/bin/perl

use strict;
my $incdir=$ARGV[0];
my @headerlist=<$incdir/*.h $incdir/*.hh>;
my $header;
my $headername;
my $structflag=0;
my $struct="";
my $structline="";
my $commentflag=0;
my $bracketnumber=0;
my $structname="";

foreach $header (@headerlist){
    $structflag=0;
    $struct="";
    $structline="";
    $commentflag=0;
    $bracketnumber=0;
    $structname="";
    open(READFILE,"$header");
    chomp;
    while (<READFILE>){
	if ($structflag){
	    if (/struct end/){
		$structflag=0;
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
			    $struct .= $_;
			} else {    
			    $struct .= $_;
			    if (/;\s*$/){
				$headername=$header;
				$headername=~s/$incdir\///;
				$struct=~s/\n/\\n/g;
				print "$headername $struct\n";
				$struct="";
			    }
			}
		    } else {
			if (/\{/) {
			    $bracketnumber++;
			} 
			if (/\}/) {
			    $bracketnumber--;
			}
			$struct .= $_;
			if (!$bracketnumber){
			    s/[Ss]*\}//;
			    if (/;$\s*/){
				$headername=$header;
				$headername=~s/$incdir\///;
				$struct=~s/\n/\\n/g;
				print "$headername $struct\n";
				$struct="";
			    }
			}
		    }				
		}
	    }
	} elsif (/struct begin/){
	    $structflag=1;
	}
    }
close (READFILE);
}
