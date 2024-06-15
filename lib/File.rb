require "tk"
require 'molvie'

$root = TkRoot.new
class File


def initialize()
fname = @fname
root = @root

end

def open_file
@fname = Tk.getOpenFile
return if @fname ==''
put('please input a pdbfilename.\n')
root = TkRoot.new
end


end

