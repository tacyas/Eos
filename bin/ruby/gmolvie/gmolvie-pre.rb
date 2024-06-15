#!/usr/bin/ruby -I /home/people/risachan/Eos/lib/X86LINUX64
require 'molvie'
require 'rubygl'
require "tk"




def open_file
fname = Tk.getOpenFile
print(fname + "1\n")
return if fname == ''
#load_file(fname)
#Teapot.new().start()
print(fname + "2\n")
#olvie.new().start()
end

window = TkcWindow.create($txt,Molvie.new().start())
TkMenubutton.new(window, 'text'=>'ファイル', 'underline'=>0){|btn|
pack('fill'=> 'x')
btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
#menu.add('command','label'=>'ファイルを開く','command'=>proc{open_file})
#menu.add('separator')
#menu.add('command','label'=>'保存','command'=>proc{save_file})
#menu.add('command','label'=>'別名で保存','command'=>proc{save_as})
#menu.add('separator')
menu.add('command', 'label'=>'人間をやめる', 'command'=>proc{exit})
}

#めいん
$root=TkRoot.new

if ARGV[0] == nil
$current = "temp#{$$}.txt"
print("にゃ\n")

else
$current = File.expand_path(ARGV[0])
load_file($current)
print("にゃにゅ#{$current}\n")
end
print("にゃにゅにょ#{$current}\n")
$root.title($current)
$txt.focus

Tk.mainloop

