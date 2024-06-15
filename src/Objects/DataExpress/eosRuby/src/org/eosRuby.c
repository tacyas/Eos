/*
# %M% %Y% %I%
# The latest update : %G% at %U%
#
#%Z% eosRuby ver %I%
#%Z% Created by 
#%Z%
#%Z% Usage : eosRuby 
#%Z% Attention
#%Z%
*/
static char __sccs_id[] = "%Z%eosRuby ver%I%; Date:%D% %Z%";

#include "Eos.h"
#include <ruby.h>
#include <string.h>

extern void Init_mrc();

static VALUE 
version(VALUE self)
{
	VALUE rb;
	char s[1024];
	char* ss;

	sprintf(s, "Eos: version %s", EOS_SYSTEM_VERSION); 
	ss = strdup(s);
	rb = rb_str_new2(ss);
	return rb;
}


void
Init_libeosRuby()
{
	VALUE mEos;

	mEos = rb_define_module("Eos");
	rb_define_module_function(mEos, "version", version, 0);

	Init_mrc();
}

