require 'tk'

# Scrollbar for TkCanvas Widget 
scr_x = TkScrollbar.new().pack('fill'=>'x', 'side'=>'bottom')
scr_y = TkScrollbar.new().pack('fill'=>'y', 'side'=>'right')

# Prepare TkCancas Widget
c = Tk::Canvas.new {
	nil
	width 500	# for Canvas size
	height 800	# for Canvas size
	scrollregion [0, 0, 1000, 1600]
	xscrollbar(scr_x)
	yscrollbar(scr_y)
	bg 'white'
	pack('fill' => 'both', 'expand' => true, 'side'=>'right')
}
# Prepare Flame for GUItools left side
f2 = TkFrame.new('bg' => 'pink').pack('side' => 'right', 'fill' => 'both', 'expand' => true)

# Label Widget for Explanation GUI tools
TkLabel.new(f2, 'text' => 'Cluster Analysis', 'bg' => 'coral').pack

TkLabel.new(f2,
  'text' =>
'Button color shows that
processes are completed or not.

Red shows process not complete.
Green shows process completed.'
).pack('side'=>'top', 'fill'=>'both', 'expand'=>false)

# Button Widget for Make ( 1st operation of Cluster Makefile )
bm = TkButton.new(f2, 'text'=>'make', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	rp, wp = IO.pipe # parent process -> child process using
	pid = fork
	if pid
		# parent process
		rp.close # reading gate of pipe is do not need -> close
	else
		# child process
		wp.close # writing gate of pipe do not need -> close 
		exec( 'make' )
		print "\n make end \n"
	end
	bm.bg('green')	# for Confirmation of finish process by changing button color red to green
	}) .pack('side'=>'top')

# Button Widget for Init ( 2nd operation of Cluster makefile )
bi = TkButton.new(f2, 'text'=>'Init', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	rp, wp = IO.pipe # parent process -> child process using
	pid = fork
	if pid
		# parent process
		rp.close # reading gate of pipe is do not need -> close
	else
		# child process
		wp.close # writing gate of pipe do not need -> close 
		exec( 'make Init' )
		print "\n make Init end \n"
	end
	bi.bg('green')	# for Confirmation of finish process by changing button color red to green
	}) .pack('side'=>'top')

# Button Widget for ALLROIS ( 3rd operation of Cluster makefile )
ba = TkButton.new(f2, 'text'=>'ALLROIS', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	rp, wp = IO.pipe # parent process -> child process using
	pid = fork
	if pid
		# parent process
		rp.close # reading gate of pipe is do not need -> close
	else
		# child process
		wp.close # writing gate of pipe do not need -> close 
		exec( 'make ALLROIS' )
		print "\n make ALLROIS end \n"
	end
	ba.bg('green')	# for Confirmation of finish process by changing button color red to green
	}) .pack('side'=>'top')

# Button Widget for Pad ( 4th operation of Cluster makefile )
bp = TkButton.new(f2, 'text'=>'Pad', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	rp, wp = IO.pipe # parent process -> child process using
	pid = fork
	if pid
		# parent process
		rp.close # reading gate of pipe is do not need -> close
	else
		# child process
		wp.close # writing gate of pipe do not need -> close 
		exec( 'make Pad' )
		print "\n make Pad end \n"
	end
	bp.bg('green')	# for Confirmation of finish process by changing button color red to green
	}) .pack('side'=>'top')

# Button Widget for Log ( 5th operation of Cluster makefile )
bl = TkButton.new(f2, 'text'=>'Log', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	rp, wp = IO.pipe # parent process -> child process using
	pid = fork
	if pid
		# parent process
		rp.close # reading gate of pipe is do not need -> close
	else
		# child process
		wp.close # writing gate of pipe do not need -> close 
		exec( 'make Log' )
		print "\n make Log end \n"
	end
	bl.bg('green')	# for Confirmation of finish process by changing button color red to green
	}) .pack('side'=>'top')

# Button Widget for LogPS ( 6th operation of Cluster makefile )
blp = TkButton.new(f2, 'text'=>'LogPS', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	rp, wp = IO.pipe # parent process -> child process using
	pid = fork
	if pid
		# parent process
		rp.close # reading gate of pipe is do not need -> close
	else
		# child process
		wp.close # writing gate of pipe do not need -> close 
		exec( 'make LogPS' )
		print "\n make LogPS end \n"
	end
	blp.bg('green')	# for Confirmation of finish process by changing button color red to green
	}) .pack('side'=>'top')

# Button Widget for display Dendrogram result
bt = TkButton.new(f2, 'text'=>'Display Tree Diagram', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'red', 'fg' => 'white', 'command'=>proc{

	# Flame and Label Widget for Explanation operating Dendrogeam in GUI tools
	f5 = TkFrame.new(f2).pack('side' =>'top')
	TkLabel.new(f2,
	  'text' =>
'This Tree Diagram operation manual
---------------------------------------------------------------------
Left Button         : Particle Average Display
Right Button            : Addition Particle data to Listbox
		        for Particle List File
Ctrl + Left Button   : Tree Diagram Expanding
Ctrl + Right Button : Tree Diagram Shrinking
	'
	).pack('side'=>'top', 'fill'=>'both', 'expand'=>false)

	inf_t = TkVariable.new()	# Variable number for File reading
	h = Hash.new()		
	#r = Hash.new
	#hl = Hash.new
	cent = TkVariable.new()	# Variable number for y-axis transform 
	lx = TkVariable.new()
	ly = TkVariable.new()
	tag = TkcTag.new(c)

	inf_t = open("all.treeinfo","r")
	p "canvas begin"

	i=0
	while inf_t.gets	# File "all.treeinfo" Reading start

		# Determination of Dendrogram Center 
		if $_.to_s.split[1] == "0.000000"		# Searching for Dendrogram startpoint
			p "Centerget"
			cent = $_.to_s.split[2].to_i	# Setting Dendrogram Center

			p "Centerget completed"
			lx = $_.to_s.split[1].to_f + $_.to_s.split[5].to_f
			ly = cent.to_f*2 - $_.to_s.split[2].to_f - $_.to_s.split[3].to_f
			# attribution start list structure ( start of dendrogram )
			start = $_.to_s.split[0].to_i
		end

		# Determination of Dendrogram upper terminal for filename description 
		if ly > 800 - $_.to_s.split[2].to_f - $_.to_s.split[3].to_f	# Searching y-coordinate of upper terminal
			ly = cent.to_f*2 - $_.to_s.split[2].to_f - $_.to_s.split[3].to_f
			#p ly
		end

		if lx < ($_.to_s.split[1].to_f + $_.to_s.split[5].to_f)		#Searching x-coordinate of upper terminal
			lx = $_.to_s.split[1].to_f + $_.to_s.split[5].to_f + 100
			#p lx
		end

		# Storage of Data of Dendrogram from "all.treeinfo"
		pnum = $_.to_s.split[0].to_i
		h[pnum] = Hash.new
		h[pnum]["temp"] = $_.to_s.split[0]	# Particle Number
		h[pnum]["x"] = $_.to_s.split[1]		# particle file x-coordinate
		h[pnum]["y"] = $_.to_s.split[2]		# Particle file y-coordinate
		h[pnum]["shoulderN"] = $_.to_s.split[3]	# Data for Create Dendrogram
		h[pnum]["shoulderM"] = $_.to_s.split[4]
		h[pnum]["armN"] = $_.to_s.split[5]
		h[pnum]["armM"] = $_.to_s.split[6]

		# parameter storage for TkcLine in Canvas Widget

		h[pnum]["lposx1"] = (100 + h[pnum]["x"].to_f + h[pnum]["armN"].to_f)
		h[pnum]["lposy1"] = (cent.to_f*2 - h[pnum]["y"].to_f - h[pnum]["shoulderN"].to_f)
		h[pnum]["lposx2"] = (100 + h[pnum]["x"].to_f)
		h[pnum]["lposy2"] = (cent.to_i*2 - h[pnum]["y"].to_f - h[pnum]["shoulderN"].to_f)
		h[pnum]["lposx3"] = (100 + h[pnum]["x"].to_f)
		h[pnum]["lposy3"] = (cent.to_i*2 - h[pnum]["y"].to_f - h[pnum]["shoulderM"].to_f)
		h[pnum]["lposx4"] = (100 + h[pnum]["x"].to_f + h[pnum]["armM"].to_f)
		h[pnum]["lposy4"] = (cent.to_i*2 - h[pnum]["y"].to_f - h[pnum]["shoulderM"].to_f)

		# parameter storage for TkcOval in Canvas Widget

		h[pnum]["oposx1"] = (100 + h[pnum]["x"].to_f - 1)
		h[pnum]["oposy1"] = (cent.to_f*2 - h[pnum]["y"].to_f - 1)
		h[pnum]["oposx2"] = (100 + h[pnum]["x"].to_f + 1)
		h[pnum]["oposy2"] = (cent.to_f*2 - h[pnum]["y"].to_f + 1)


		# Creation Dendrogram Start

		# Lines Description from TkCanvas Widget 
		# TkcLine.new( canvas, x1, y1, x2, y2, x3, y3, x4, y4 )
		h[pnum]["lines"] = TkcLine.new(c, 
			(h[pnum]["lposx1"]), (h[pnum]["lposy1"]), 
			(h[pnum]["lposx2"]), (h[pnum]["lposy2"]), 
			(h[pnum]["lposx3"]), (h[pnum]["lposy3"]), 
			(h[pnum]["lposx4"]), (h[pnum]["lposy4"]), :tags=>tag
			)

		# Circle Description from TkCanvas Widget
		# TkcOval.new( canvas, x1, y1, x2, y2 )
		h[pnum]["ovals"] = TkcOval.new(c, 
			(h[pnum]["oposx1"]), 
			(h[pnum]["oposy1"]), 
			(h[pnum]["oposx2"]), 
			(h[pnum]["oposy2"]), :tags=>tag,
			'fill' => 'white'
			)

		i+=1

	end		# Creation Dendrogram End

	l = Hash.new()
	inf_l = TkVariable.new()  # Prepare Variable number for File "all.avgsortlst" Reading

	p "list reading"
	inf_l = open("all.avgsortlst","r") # File Open

	while inf_l.gets

		TkcText.new(c, lx, ly, 'text' => $_.to_s.split[0],  'anchor'=>'w', :tags => tag)
		ly += 10

		l[$_.to_s.split[1].to_i] = Hash.new
		l[$_.to_s.split[1].to_i]["filename"] = $_.to_s.split[0]
		l[$_.to_s.split[1].to_i]["particle"] = h[$_.to_s.split[1].to_i]
		#l[$_.to_s.split[1].to_i]["prev"] = $_.to_s.split[0]
		if start == $_.to_s.split[1].to_i
			p "particle number of dendrogram begining is " + start.to_s
		end
	end

	# Setting Dendrogram Operation of Scailing Dendrogram Size

	c.bind('Control-ButtonPress-1', :x, :y){|x,y| tag.scale(x, y, 1.25,  1.25);}
	c.bind('Control-ButtonPress-3', :x, :y){|x,y| tag.scale(x, y, 0.8,  0.8);}

	# Setting Button Binding for Each Particles to Display Particle Averages

	j = 1

	while j-1 != i
		h[j]["ovals"].bind('ButtonPress-1', proc {
			|w, x, y, j| p "circle: "+x.to_s+" "+y.to_s+" "+w.to_s+" "+j ;
			p h[j.to_i]["ovals"]; 
			h[j.to_i]["ovals"].configure("fill" => "red")	# Change Color to Red about Selected Particles
			p " Particle Average Display "
			cmd ="exec( 'Display2 -i "+l[j.to_i]["filename"]+"' )"
			rp, wp = IO.pipe # # parent process -> child process using
			pid = fork
			if pid
				# parent process
				rp.close # reading gate of pipe is do not need -> close
			else
				# child process
				wp.close # writing gate of pipe do not need -> close 
				eval cmd	# Execution "cmd" -> Average Display ( call Display2 )
				print "\n make end \n"
			end
			}, "%W %x %y "+j.to_s+" ")
		j+=1
	end

	# Explanation and Operation of Creation Filelist for Refinement

	f3 = TkFrame.new(f2).pack('side' =>'bottom')	# Base Frame and Listbox Frame for Refinement
	f4 = TkFrame.new(f3).pack('side' => 'top')	# Button Frame for Storage and Clear Filename to Listbox
	f6 = TkFrame.new(f3).pack('side' => 'top')	# Entry Frame for Filling in Output Filename 

	# Flame and Label Widget for Explanation Creating Filelist in GUI tools
	f7 = TkFrame.new(f2).pack('side' =>'top')
	f7.bg('black')
	TkLabel.new(f2,
	  'text' =>
	'Explanation Operating Listbox for Filelist using Refinement 
-----------------------------------------------------------------------------------
1. Storage Filename by Selecting Particle from Dendrogram
2. Select Particle Filename in Listbox by Mouse Drag
3. Input Filename in Entry Box as Output File
	 * File Extension is clstlst ( ex. ***.clstlst )
4. Click "output" Button
5. Clear Filename in Listbox by Click "Clear" or "ClearAll" Button             
6. Return 1
	'
	).pack('side'=>'top', 'fill'=>'both', 'expand'=>false)

	# Setting Button Binding to Each Operation of Button for Listbox
 
	bOut = TkButton.new(f4, 'text' => 'output file' ).pack( 'side' => 'left' )
	bClear = TkButton.new(f4, 'text' => 'clear' ).pack( 'side' => 'left' )
	bClearA = TkButton.new(f4, 'text' => 'clear All' ).pack( 'side' => 'left' )
	TkLabel.new(f6, 'text' => 'Output Filename').pack( 'side' => 'left' )
	filename = TkEntry.new(f6).pack('side'=>'left')
	outfile = TkVariable.new()
	scr1x = TkScrollbar.new(f3).pack('fill'=>'x', 'side'=>'bottom')
	list_f = TkListbox.new(f3).pack('side' => 'left', 'fill' => 'both', 'expand' => true)
	scr1y = TkScrollbar.new(f3).pack('fill'=>'y', 'side'=>'left')

	list_f.selectmode 'extended'	# Selection-Mode for Listbox

	list_f.xscrollbar( scr1x )
	list_f.yscrollbar( scr1y )

	# Setting Button Binding for Each Particles to Display Particle Averages

	k = 1
	while k-1 != i
		h[k]["ovals"].bind('ButtonPress-3', proc {
			|w, x, y, k| p "circle: "+x.to_s+" "+y.to_s+" "+w.to_s+" "+k ;
			p h[k.to_i]["ovals"];
			h[k.to_i]["ovals"].configure("fill" => "blue")	# Change Color to Blue about Selected Particles 
			p " Particle Selected for filelist "
			list_f.insert( "end", l[k.to_i]["filename"].sub(/.pad.avg/, ".roi" ))
			},"%W %x %y "+k.to_s+" " )
		k += 1
	end

	# Setting Button Binding to Create Filelist for Refinement
	bOut.command(proc{
		p filename.value
		outfile = open(filename.value,"w")
		list_f.curselection.each { |i| outfile.puts "#{list_f.get(i)}\n" }
		p "File encoded"
		}
	)

	# Setting Button Binding to Clear Filename of Selected Particle
	bClear.command(proc{
		list_f.delete(list_f.curselection)
		#r[list_f.curselection.to_i].configure("fill" => "white")
		}
	)

	# Setting Button Binding to Clear ALL Filename in Listbox
	bClearA.command(proc{
		list_f.delete(0, 'end')
		}
	)

	bt.bg('green')	# for Confirmation of finish process by changing button color red to green
	}).pack('side'=>'top')

# Button Widget for Exit GUI tools
TkButton.new(f2, 'text'=>'Quit', 'activeforeground'=>'white', 'activebackground'=>'green', 'bg' => 'blue', 'fg' => 'white', 'command'=>proc{exit}).pack('side'=>'top')


Tk.mainloop

