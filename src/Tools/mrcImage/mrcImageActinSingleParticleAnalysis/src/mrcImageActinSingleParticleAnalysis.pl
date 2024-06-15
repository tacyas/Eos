#!/usr/bin/perl  
use strict;

if (!$ARGV[0] || $ARGV[0]=="-h"){
    print "mrcImageActinSingleParticleAnalysis iterationnumber selectionrule [threshold1] [low frequency for selection2] [high frequency for selection2] [threshold2]\n";
    exit;
}

my $PI=3.14159;
my $itern=$ARGV[0];
my $selection=$ARGV[1];
my $selectth1=$ARGV[2]/180*$PI;
my $selectL2=$ARGV[3];
my $selectH2=$ARGV[4];
my $selectth2=$ARGV[5]/180*$PI;

my $samplexy=3.4125;
my $samplephi=5;
my $templateN=10;
my $addv=0.01;
my ($th1,$th2,$lh1,$lh2)=(10,10,2,2);
my $numphi=360/$samplephi;
my $allfile="yp.inf";
my $backprojinffile="yp.proj.inf";
my $resultNx=41;
my $resultNy=41;
my $avN=14;
my $padr=16.5;
my $padw=1;
my $refx=36;
my $image3d;
my $selectH1=0.025;
my $selectL1=0.0033;

my $prevn=$itern-1;
my $rawn=".36.c.n";
my $raww=".80.c";
my $raw="*.hc";
my $model="yp.proj.inf.mrc3d.t.c.av$avN.newpad$padr.$padw.sc.d$samplephi"."11.w180.n.$prevn";
my $short="*.mrc*.y*.p*.n";
my @rawnlist=glob($rawn);
my @rawwlist=glob($raww);
my @rawlist=glob($raw);
my @shortlist;

my @peakx;
my @peaky;
my $filn;
my $filw;
my $fil;
my @filelist;
my $filename;
my $nr;
my $dz;
my $dp;
my $padv;

if ($selection == "613"){
    $nr=208;
    $dz=27.3;
    $dp=166.154;
} elsif ($selection == "1328"){
    $nr=224;
    $dz=27.3;
    $dp=167.143;
}



foreach $fil (@rawlist){
    $filn=$fil.$rawn;
    $filw=$fil.$raww;
    system "mrcRefImagepwzCorrelation -i $filn -r $model -o $filn.pwzcor -m 1";
    system "mrcRefImagepwzCorModify -i $filn.pwzcor -o $filn.pwzcor.m -nr $nr -m 1 -M 1";
    system "mrcRefImagepwzCorPeakFind -i $filn.pwzcor.m -o $filn.pwzcor.m.p -N $templateN -dN 1 -m 1 -dz $dz -dp $dp";
    system "mrc3DExtractZ -i $filn.pwzcor.m -o $filn.pwzcor.m.z1 -t 1 -b 1";
    system "mrcRefNormalizing -i $filn.pwzcor.m.z1 -o $filn.pwzcor.m.n -m 1";
    unlink ("$filn.pwzcor.m.z1");
    system "mrcImageMultiplying -i $filn.pwzcor.m.p -o $filn.pwzcor.m.p.v -v $addv";
    unlink ("$filn.pwzcor.m.p.v");
    unlink ("$filn.pwzcor.m");
    system "mrcImageAdd -i1 $filn.pwzcor.m.n -i2 $filn.pwzcor.m.p.v -o $filn.pwzcor.m.p.add";
    findgoodpeakfromarray("$filn.pwzcor.m.p.dat.good","$filn.pwzcor.m.p", $th1, $th2, $lh1, $lh2,  $dz, $dp, $samplexy, $samplephi);
    shortimageget($filw,"$filn.pwzcor.m.p.dat.good",$nr);
}

@filelist=glob($short);
open(Outfile,">$allfile");
foreach $filename ( @filelist ) { 
    print Outfile "$filename\n ";
}
close(Outfile);

print "start ";
if ($selectth1){
    shortimagegoodselect ("$allfile.good60", $allfile, $model, $selectH1, $selectL1, $selectth1, 0, $numphi, 7);
    if ($selectth2){
	shortimagegoodselect ("$allfile.good6085", "$allfile.good60", $model, $selectH2, $selectL2, $selectth2, 0, $numphi, 3);
	shortimageadd("$allfile.good6085",$numphi);
	createbackprojinf($backprojinffile,"$allfile.good6085",$numphi,$samplephi);
    } else {
	shortimageadd("$allfile.good60",$numphi);
	createbackprojinf($backprojinffile,"$allfile.good60",$numphi,$samplephi);
    }
} else {
    shortimageadd($allfile,$numphi);
    createbackprojinf($backprojinffile,$allfile,$numphi,$samplephi);
}    
system ("mrc2Dto3D -I $backprojinffile -o $backprojinffile.mrc3d -m 1 -single 1");
$image3d="$backprojinffile.mrc3d";
system ("mrcImageTranspose -i $image3d -o $image3d.t -m 2");
system ("mrcImageCenterGet -i $image3d.t -o $image3d.t.c -Nx $resultNx -Ny $resultNy -Nz $nr -m 2");
system ("mrcImageHelicalAveraging -i $image3d.t.c -o $image3d.t.c.av$avN -dp -$dp -dz $dz -N $avN");
system ("mrcImage3DPad -i $image3d.t.c.av$avN -o $image3d.t.c.av$avN.newpad$padr.$padw -r $padr -w $padw -m 2");
$padv=`mrcImage3DPad -i $image3d.t.c.av$avN -o $image3d.t.c.av$avN.newpad$padr.$padw -r $padr -w $padw -m 2 |awk '$1=="av:" {print $2}'`;
$padv *= -1;
system ("mrcImageScalarAdd -i $image3d.t.c.av$avN.newpad$padr.$padw -o $image3d.t.c.av$avN.newpad$padr.$padw.sc -v $padv"); 
print "mrcImageRefCreate -i $image3d.t.c.av$avN.newpad$padr.$padw.sc -o $image3d.t.c.av$avN.newpad$padr.$padw.sc.d$samplephi"."11.w180 -d 5 1 1 -w 180 0 0 -x $refx";
system ("mrcImageRefCreate -i $image3d.t.c.av$avN.newpad$padr.$padw.sc -o $image3d.t.c.av$avN.newpad$padr.$padw.sc.d$samplephi"."11.w180 -d 5 1 1 -w 180 0 0 -x $refx");
system ("mrcRefNormalizing -i $image3d.t.c.av$avN.newpad$padr.$padw.sc.d$samplephi11.w180 -o $image3d.t.c.av$avN.newpad$padr.$padw.sc.d$samplephi"."11.w180.n.$itern");



sub createbackprojinf{
    my($outfile,$inffile,$numphi,$samplephi)=@_;
    my $i;
    my $p;

    open(OUTFILE,">$outfile");
    for ($i=0 ;$i<$numphi ;$i++){
	$p = -$i*$samplephi;
	if (-e "$i.add.$inffile.n"){
	    print OUTFILE "$i.add.$inffile.n ,YEYS,$p,0,0\n";
	}
    }
    close (OUTFILE);
}


sub shortimageadd{
    my($inffile,$numphi)=@_;
    my $i;
    my $list;

    for ($i=0 ;$i<$numphi ;$i++){
	system("grep p$i.n $inffile >temp.$i.add.$inffile");
	unlink("$i.add.$inffile.n");
	if (-s "temp.$i.add.$inffile"){
	    system("mrcImageAdd -I temp.$i.add.$inffile -o $i.add.$inffile");
	    system("mrcRefNormalizing -i $i.add.$inffile -o $i.add.$inffile.n -m 1");
	}
	unlink("$i.add.$inffile");
	unlink("temp.$i.add.$inffile");
    }
}

sub findgoodpeakfromarray{
    my($outfile, $infile, $th1, $th2, $lh1, $lh2, $dz, $dp, $samplexy, $samplephi)=@_;
    my $pa2=0.4356;
    my @peakx;
    my @peaky;
    my @goodpeakx;
    my @goodpeaky;
    my @dx;
    my @dy;
    my ($x,$y,$z);
    my $nphi;
    my $i;
    my $dd;
    my $j;
    my $sj;
    my $ej;
    my $num=0;
    my $goodnum=0;
    my $flag=0;

    $th1 **= 2;
    $th2 **= 2;
    open(READDAT, "mrcImageMakeDump -i $infile |");
    open(OUTFILE, ">$outfile") || die "I cannot open file!";
    while (<READDAT>){
	chomp;
	($x,$y,$z)=split;
	if ($z>0 && $y!=0){
	    ($peakx[$num],$peaky[$num])=($x,$y);
	    $num++ ;
	}
    }
    $dz/=$samplexy;
    $dp/=$samplephi;
    $nphi=360/$samplephi;
    for ($i = 0; $i < $num - 1; $i++) {
	$dx[$i] = $peakx[$i + 1] - $peakx[$i];
	if ($dx[$i] < 0) {
	    $dx[$i] = $nphi + $dx[$i];
	}
	$dy[$i] = $peaky[$i + 1] - $peaky[$i];
	if ($dx[$i] < 0 || $dy[$i] < 0) {
	    print '??? dx or dy is negative!';
	    exit (1);
	}
    }
    for ($i = 0; $i < $num-1; $i++) {
	$flag = 0;
	$sj=$i-$lh1;
	$ej=$i+$lh1-1;
	if ($i < $lh1){
	    $sj=0;
	} elsif ($i >= $num - $lh1){
	    $ej=$num-1;
	}
	for ($j = $sj; $j <= $ej; $j++) {
	    $dd = (($dx[$j] - $dp) * $samplephi )**2 *$pa2 + (($dy[$j] - $dz) * $samplexy)**2 ;    
	    if (abs($i - $j) <= $lh2) {	  
		if ($dd > $th2) {	
		    $flag = 1;
		    last;
		}
	    } elsif ($dd > $th1) {	
		$flag = 1;
		last;
	    }
	}
	if ($flag == 0) {
	    $goodpeakx[$goodnum]=$peakx[$i];
	    $goodpeaky[$goodnum]=$peaky[$i];
	    print OUTFILE "$goodpeakx[$goodnum] $goodpeaky[$goodnum] \n";
	    $goodnum++;
	}
    }
    close (READDAT);
    close (OUTFILE);
}

    
sub abs{
    my($v) = @_;
    if ($v > 0) {
	return $v;
    }
    else {
	return -$v;
    }
}

sub shortimageget{
    my ($infile, $datfile, $nr) = @_;
    my ($p,$y);
    my $outfile;

    open (DATFILE,"$datfile");
    while (<DATFILE>){
	chomp;
	($p,$y)=split;
	$outfile="$infile.y$y.p$p";
	$y += 0.5;
 	system("mrcImageCenterGet -i $infile -o $outfile -Ny $nr -Cy $y");
	system("mrcRefNormalizing -i $outfile -o $outfile.n -m 1");
	unlink("$outfile");
	
   }  
}


sub shortimagegoodselect{
    my ($outfile, $inf, $ref, $H, $L, $hth, $lth, $numphi, $mode)=@_;
    my $i;
    my $file;
    my $z;
    my $dum1;
    my $dum2;
    my $cor;

    open(OUTFILE,">$outfile");
    for ($i=0 ;$i<$numphi ;$i++){
	$z=$i+1;
	open(TMPOUTFILE,">$i.$outfile");
	print TMPOUTFILE `grep .p$i.n $inf`;
	close TMPOUTFILE;
	print "mrcImageFourierShellCorrelation  -I1 $i.$outfile -i2 $ref -z $z -m $mode  -M 3  -L $L -H $H |\n";
	open(COR,"mrcImageFourierShellCorrelation  -I1 $i.$outfile -i2 $ref -z $z -m $mode  -M 3  -L $L -H $H |");
	while (<COR>){
	    chomp;
	    ($file,$dum1,$dum2,$cor)=split;
	    print "$file $dum1 $dum2 $cor\n";
	    if ($cor <= $hth && $cor >= $lth){
		print OUTFILE "$file\n";
	    }
	}
	close COR;
    }
}
