require 'molvie_ver'
require 'tk_sdl'
require 'molvieRuby'
class Molvie_Keyboard


def molvie_keyboard_normal(pushkey,x,y)
	#molvie = MolvieRuby
	#puts (pushkey,"nya")
	if(pushkey!='w' && pushkey!='e')
		#puts pushkey
	end

	case pushkey
	when 'q'
		puts "quit.\n"
		#SDL::Event2::Quit
		exit
	when 'd'
	molvie::molvie_Flight
	molvie::setDriveMyCamera();
	molvie::setCameraCentreTag(0);
	puts "(ModeChange) Flight mode\n"
	when 'l'
		#未完成
	#	molvie.resetMyCamera();
	#	molvie.molvie_Projection
	#	molvie.setCameraCentreTag(0);
	when 't'
		Molvie_ver.new.molvie_MrcViewer
		puts "インプットファイルを入力してください\n"
		puts"ぷろじぇくしょーん！！\n"
		mrcFileName = Tk.getOpenFile
		puts mrcFileName
		puts"\n"
		molvie::lmolvieMRCread(mrcFileName)
	when 'c'
		molvie.put_elementSwitch(0, pushkey);	
	when 'o'
		molvie.put_elementSwitch(0, pushkey);	
	when 'n'
		molvie.put_elementSwitch(0, pushkey);	
	when 's'
		molvie.put_elementSwitch(0, pushkey);	
	when 'p'
		molvie.put_elementSwitch(0, pushkey);	
	when 'h'
		molvie.put_elementSwitch(0, pushkey);	
	when 'f'
		molvie.put_elementSwitch(0, pushkey);	
	when '0'	
		molvie.displayModeSet(0,0)
		puts "(DisplayModeChange) NoneAtom mode\n"
	when '1'
		molvie.displayModeSet(0,1)
		puts "(DisplayModeChange) Atom mode\n"
	when '5'
		molvie.displayModeSet(0,2)
		puts "(DisplayModeChange) CStickNumber mode\n"
	when '2'	
		molvie.displayModeSet(0,3)
		puts "(DisplayModeChange) Number mode\n"
	when '3'
		molvie.displayModeSet(0,4)
		puts "(DisplayModeChange) AminoAcid mode\n"
	when '4'
		molvie.displayModeSet(0,5)
		puts "(DisplayModeChange) Temperature mode\n"
	when '7'
		molvie.displayModeSet(0,6)
		puts "(DisplayModeChange) CStickTemperature mode\n"
	when '6'
		molvie.displayModeSet(0,7)
		puts "(DisplayModeChange) CStickAminoAcid mode\n"
	when '8'
		molvie.displayModeSet(0,8)
		puts "(DisplayModeChange) DistanceFromTarget mode\n"
	when '9'
		molvie.displayModeSet(0,9)	
		puts "(DisplayModeChange) WireFrame mode\n"
	when '!'
		molvie.displayModeSet(0,10)
		puts "(DisplayModeChange) Chain mode\n"
	when 'v'
		#未完成
		#lmolvieVoice();
		#fprintf(stdout, "voice!\n");
	when 'r'
		molvie.resetMyCamera()
		puts "camera reset.\n"
	when 'w'
		molvie.moveMyCamera(1.0)
	when 'e'
		molvie.moveMyCamera(-1.0)
	when 'F'
		molvie.setCameraCentreTag(-1)
	else 
		#puts "\n"
	end

end

def lmolvie_keyboard_drive(pushkey,x,y)
MolvieRuby.lmolvieKeyboardDrive(pushkey,x,y)
end

def lmolvie_keyboard_parallel(pushkey,x,y)
#attantion!
end

def lmolvie_keyboard_surface(pushkey,x,y)
MolvieRuby.lmolvieKeyboardSurface(pushkey,x,y)
end

def lmolvie_keyboard_multi(pushedkey,keyx,keyy)
MolvieRuby.lmolvieKeyboardMulti(pushkey,x,y)
end


end

