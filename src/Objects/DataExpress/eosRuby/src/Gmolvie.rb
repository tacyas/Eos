
#	init0(&info);
 #   argCheck(&info, argc, argv);
  #  init1(&info);
#!/usr/bin/ruby -I /home/people/risachan/Eos/lib/X86LINUX64
require 'molvieRuby'
require 'molvie'
require "tk"
#require ""

#	info.fptIn=fopen(info.In, "r");
#	if(NULL==info.fptIn){
#		fprintf(stderr, "FileNotOpend: %s\n", info.In);
#		exit(EXIT_FAILURE);
#	}
#
#	lmolviePDBread(info.fptIn);

#	fclose(info.fptIn);

class << Molvie
def run_on_tk(frame = TkFrame.new(nil,'container'=>true))
if frame.container == 0
raise RuntimeError,'TkFrame is NOT a container widget.'
end 
@tk_frame = frame
end
end

