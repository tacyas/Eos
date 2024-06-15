require 'molvie_ver'
#require 'molvieRuby'
require 'keyboard_Func'
require 'molvie_keyboard'
class Event 
	def pushedKey_is_molvieVer(key,ver)
		
		if(key == 'd' )
		   Molvie_ver.new.molvie_Flight
		elsif(key == 'l') 
		   Molvie_ver.new.molvie_Projection
		elsif(key == 't')
		   Molvie_ver.new.molvie_MrcViewer
		elsif(key == 'm')
		   Molvie_ver.new.molvie_Dock
		end
	end

	def lmolvie_keyboard(pushkey,x,y)
		operation = Molvie_ver.new.molvie_ver
		key =Molvie_Keyboard.new
		if(operation==1)
			#key.lmolvie_keyboard_drive(pushkey, x, y);
		elsif(operation==2)
			#key.lmolvie_keyboard_parallel(pushkey, x, y);
		elsif(operation==3)
			#key.lmolvie_keyboard_surface(pushkey, x, y);
		elsif(operation==4)
			#key.lmolvie_keyboard_multi(pushkey, x, y);
		else
			key.molvie_keyboard_normal(pushkey, x, y);
		end
		SDL::Event2::VideoExpose
	end
end
