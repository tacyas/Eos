#!/usr/bin/env ruby

#require "mrcImage"

module Eos
	def headMessage
		print "Hello Eos World! "+ Eos::version+"\n"
	end
	module_function :headMessage
end

