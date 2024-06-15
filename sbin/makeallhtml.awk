BEGIN{
	print "<HTML>\n<BODY>\n<TABLE BORDER>\n";
	print "<TR><TH>Function Name</TH><TH>Source Object</TH><TH>" "</TH></TR>\n"
}

{
	printf ("<TR><TD><A HREF=\"%sproto.html\">%s</TD><TD>%s</TD><TD><A HREF=\"%s.html\">called from</TD></TR>\n",$1,$1,$2,$1);
}

END{
print "</TABLE>\n</BODY>\n</HTML>\n"
}
	






