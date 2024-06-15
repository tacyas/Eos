require "tk"
require "sdl"

class << SDL
	def run_on_tk(frame = TkFrame.new(nil, 'container'=>true))
		if frame.container == 0
			raise RuntimeError,"TkFrame is NOT a container widget."
		end
		@tk_frame = frame
	end

	alias original_SDL_init init
	def init(*args)
		Tk.update
		unless TkWinfo.mapped? @tk_frame
			raise RuntimeError,"Base window is NOT mapped on the display."
		end
		ENV['SDL_WINDOWID'] = TkWinfo.id(@tk_frame)
		original_SDL_init(*args)
	end

	alias original_SDL_setVideoMode setVideoMode
	def setVideoMode(width, height, depth, *param)
		@tk_frame.configure('width'=>width, 'height'=>height)
		Tk.update
		original_SDL_setVideoMode(width, height, depth, *param)
	end
end
