require 'molvieRuby'
$molvie_ver

class Molvie_ver
	def molvie_Viewer
	$molvie_ver = 0
	MolvieRuby::operationModeSet(0)
	end
	
	def molvie_Flight
	$molvie_ver = 1
	#return version 
	MolvieRuby::operationModeSet(1)
	end	
	
	def molvie_Projection
	$molvie_ver = 2
	#return version
	MolvieRuby::operationModeSet(2)
	end

	def molvie_MrcViewer
	$molvie_ver  = 3
	#3return version 
	MolvieRuby::operationModeSet(3)

	end
		
	def molvie_Dock
	$molvie_ver = 4	
	MolvieRuby::operationModeSet(4)
	#return version 
	end

	def molvie_ver
	molvie_ver =$molvie_ver
	return molvie_ver
	end
	
	def put_molviemode
	puts $molvie_ver 
	end
	
end
