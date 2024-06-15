
/\.ccm/ {
	filename=$0
	gsub(/\.ccm/, ".o", filename);
	printf("%s/%s:%s\n", HostType, filename, filename);
	next
}

/\.cc/ {
	filename=$0
	gsub(/\.cc/, ".o", filename);
	printf("%s/%s:%s\n", HostType, filename, filename);
	next
}

/\.c/ {
	filename=$0
	gsub(/\.c/, ".o", filename);
	printf("%s/%s:%s\n", HostType, filename, filename);
	next
}




