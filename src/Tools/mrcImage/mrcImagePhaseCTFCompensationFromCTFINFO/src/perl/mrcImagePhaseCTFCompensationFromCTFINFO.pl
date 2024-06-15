#!/usr/bin/perl

#print "mrcImagePhaseCTFCompensationFromCTFINFO start\n";

if (!$ARGV[0] || $ARGV[0] =~ /-h/) {
	print ">>>> Usage <<<< \n";
	print "mrcImagePhaseCTFCompensationFromCTFINFO input output ctfinfo\n";
	exit
} 

my @info;

open(CTFINFO, "$ARGV[2]") || die "I cannot open file: $ARGV[2]";

my $kV;
my $Cs;
my $AoverP;
my $Defocus;

while (<CTFINFO>) {
	#print "$_"; 
	chomp; 
	SWITCH: {
		/^kV/ && do {
			#print "$_\n";
			@info=split;
			$kV = $info[1];
			#print "kV===>  $kV\n";
			last SWITCH;
		};
		/^Cs/ && do {
			@info=split;
			$Cs = $info[1];
			last SWITCH;
		};
		/^AoverP/ && do {
			@info=split;	
			$AoverP = $info[1];
			last SWITCH;
		};
		/^defocus/ && do {
			@info=split;
			$Defocus = $info[1];
			last SWITCH;
		};
	}

}

print "mrcImageCTFCompensation -i $ARGV[0] -o $ARGV[1] -m 1 -kV $kV -Cs $Cs -A $AoverP -df $Defocus\n"; 
system "mrcImageCTFCompensation -i $ARGV[0] -o $ARGV[1] -m 1 -kV $kV -Cs $Cs -A $AoverP -df $Defocus"; 
