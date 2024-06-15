#!/usr/bin/ruby

require 'tk'

label = TkLabel.new {
  text "Clustering"
  pack
}

TkButton.new {
	text "Init"
	command { 
		label.bg("green")
		exec(make, Init)
	}
	pack
}

TkButton.new {
	text "ALLROIS"
	command { label.bg("red") }
	pack
}

TkButton.new {
	text "Pad"
	command { label.bg("red") }
	pack
}

TkButton.new {
	text "Log"
	command { label.bg("red") }
	pack
}

TkButton.new {
	text "LogPS"
	command { 
		label.bg("red") 
	}
	pack
}

Tk.mainloop
