#!/usr/bin/perl

use strict;
my $in=$ARGV[0];
my $structlist=$ARGV[1];
my @inline;
my $header;
my $funcname;
my $inword;
my $outfile;
my @structlist;
my $i=0;
my @matchlist;
my $trimedword;
my $backtrimed;
my $foretrimed;

open(STRUCTFILE,"$structlist");
while (<STRUCTFILE>){
    chomp;
    $structlist[$i]=$_;
    $i++;
}

open(READFILE,"$in");
while (<READFILE>){
    chomp;
    @inline=split;
    $header=$inline[0];
    ($funcname)=/ (\S+) *\(/;
    $outfile="$funcname"."proto.html";
    open(OUTFILE,">$outfile");
    shift(@inline);
    print OUTFILE "<HTML>\n<BODY>\n";
    print OUTFILE "<H1>$funcname</H1><BR>\n";
    print OUTFILE "<H3>in $header</H3><BR>\n";
    print OUTFILE "<H3> ";
    foreach $inword (@inline){
	$_=$inword;
	($trimedword)=/(\w+)[\&\*]*$/;
	if (@matchlist = grep $trimedword=~$_, @structlist){
	    $_=$inword;
	    ($backtrimed)=/(\S+)$trimedword[\&\*]*$/;
	    ($foretrimed)=/$trimedword([\&\*]*)$/;
	    print OUTFILE "$backtrimed";
	    print OUTFILE "<A HREF=\"$trimedword.html\">$trimedword</A> ";
	    print OUTFILE "$foretrimed ";
	} else {
	    print OUTFILE "$inword ";
	}
    }
    print OUTFILE "</H3>\n";
    print OUTFILE "</HTML>\n</BODY>\n";
    close(OUTFILE);
}

