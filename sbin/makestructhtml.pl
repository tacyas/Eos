#!/usr/bin/perl

use strict;
my $in=$ARGV[0];
my $structlist=$ARGV[1];
my $inline;
my $header;
my @structlist;
my $i=0;
my $inword;
my $outfile;
my $trimedword;
my $backtrimed;
my $foretrimed;
my $structname;
my @matchlist;
my $match;

open(STRUCTFILE,"$structlist");
while (<STRUCTFILE>){
    chomp;
    $structlist[$i]=$_;
    $i++;
}

open(READFILE,"$in");
while (<READFILE>){
    chomp;
    ($header)=/^(\S+)/;
    s/$header\s*//;
    if (/typedef/){
	($structname)=/(\S+);\\n$/;
	$structname=~s/(\S+)\}//;
    } else {
	($structname)=/struct (\S+) *\{/;
    }	
    if ($structname=~/\S+/){
	$outfile="$structname".".html";
	open(OUTFILE,">$outfile");
	print OUTFILE "<HTML>\n<BODY>\n";
	print OUTFILE "<H1>$structname</H1><BR>\n";
	print OUTFILE "<H3>in $header</H3><BR>\n";
	s/\\n/ <BR>\n/g;
	$inline=$_;
	if (@matchlist = grep $inline=~/ $_ /, @structlist){
	    for $match (@matchlist){
		$inline=~s/ $match / <A HREF=\"$match.html\">$match <\/A>/g;
	    }
	}
	print OUTFILE "<PRE>\n$inline \n</PRE>";
	print OUTFILE "</HTML>\n</BODY>\n";
	close(OUTFILE);
    }
}


