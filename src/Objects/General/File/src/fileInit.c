#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/File.h"

void
fileInit(File* f)
{
	f->fpt = fileOpen(f->name, f->mode);
}
