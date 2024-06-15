################# ltlg plot
count <- scan("COUNT", list(count=0.0))
count2 <- seq(count$count) 
postscript(file="DSTDEFAULT",  horizontal=F)
par(new=F, mfcol=c(5,2), mai=c(0.5, 0.5, 0.3, 0.5))

for(i in count2) {
	
	Number <- as.character(i)
	FILENAME <- paste("SRCDEFAULT", ".", Number, sep="")

	init  <- scan(FILENAME, list(n=0.0, l=0.0), n=2)
	data  <- scan(FILENAME, list(r=0.0, Intensity=0.0, Phase=0.0), skip=1)

	#Irange <- range (   0, 100)
	Prange <- range (-180, 180)

	plot(data$r, data$Intensity, xaxt="n", type="l", lty = 1, xlab="R [A]" , ylab="", tck=0.02, axes=F) 
	axis(side=2, tck=0.02, exp=2)
	mtext("Intensity", side=2, line=2, outer=F)
	par(new=T)

	plot(data$r, data$Phase    , ylim=Prange, type="p", xaxt="n", type="l", lty = 2, xlab="" , ylab="", tck=0.02, axes=F) 
	axis(side=4, at=seq(-180, 180, len=5), tck=0.02)
	mtext("Phase", side=4, line=2, outer=F)

	axis(side=1, tck=0.02)
	axis(side=3, tck=0.00, labels=FALSE)

	mtext(text="MAINTITLE",lty=1, side=3, line=0, outer=F, at=0)

	n <- as.character(init$n)
	l <- as.character(init$l)
	NL <- paste("n=", n, "  l=", l, sep="")

	mtext(text=NL,lty=1, side=3, line=0, outer=F)
	par(new=F)
}

q()
