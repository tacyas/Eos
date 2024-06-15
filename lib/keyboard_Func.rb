require 'molvie_ver'
require 'molvieRuby'
$push_key
$x
$y
class Keyboard_func

	def keyboard_func(push_key,x,y,molvie_ver)
		$push_key = push_key 
		$x = x
		$y = y
		puts $push_key,$x,$y
		push_key=$push_key
		MolvieRuby::lmolvieKeyboard(push_key[0],$x,$y)
	end
end

