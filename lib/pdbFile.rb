#!/usr/bin/ruby -I /home/people/risachan/Eos/lib/X86LINUX64
require 'molvieRuby'
require 'molvie'
require "tk"

class PdbFile
	def file_read
		puts"ok"
		info= MolvieRuby::MolvieInfo.new
		@@info = info
		puts"ok2"
		@@info.In = Tk.getOpenFile
		puts info.In
		@@info.fptIn =MolvieRuby.fopen(@@info.In,"r")
		puts "neko\n"
		if(info.fptIn == nil)
			puts("PDBFile Not Opend:",@@info.In)
		else 
			puts("Opened PDBFile:", @@info.In)
		end
		MolvieRuby::lmolviePDBread(info.fptIn)
	end
	
	def get_pdb
	puts @@info.In
	return @@info
	end


end
