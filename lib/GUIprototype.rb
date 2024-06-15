#!/usr/bin/ruby

require 'tk'
#require './Gmolvie/Gmolvie.rb'
#require './rubygl.rb'

# テキストフレームの作成
TkFrame.new{|f|
pack( 'fill'=>'both', 'side'=>'bottom')
TkGrid.rowconfigure(f, 0, 'weight'=>1, 'minsize'=>0)
TkGrid.columnconfigure(f, 0, 'weight'=>1, 'minsize'=>0)
$txt = TkText.new(f,'wrap'=>'none').grid('row'=>0, 'column'=>0, 'sticky'=>'news')
xscr = TkScrollbar.new(f).grid('row'=>1, 'column'=>0, 'sticky'=>'ew')
yscr = TkScrollbar.new(f).grid('row'=>0, 'column'=>1, 'sticky'=>'ns')

$txt.xscrollbar(xscr)
$txt.yscrollbar(yscr)
}

# ファイルの基本
def new_file
fname= Tk.getSaveFile
return if fname == ''
$txt.delete('1.0','end')
open(fname, 'w')
$txt.title($current = fname)
$txt.focus
end

def load_file(fname)
$txt.value = IO.readlines(fname).join('')
$txt.set_insert('1.0')
print("ok\n")
end

def open_file
fname = Tk.getOpenFile
return if fname == ''
#load_file(fname)
Gmolvie.Molvie
end

def save_file
open($current,'w') {|f| f.write($txt.get('1.0', 'end'))}
$txt.focus
end

def save_as
fname = Tk.getSaveFile('initialfile'=>$current)
return if fname == ''
open(fname,'w') {|f| f.write($txt.get('1.0', 'end'))}
$root.title($current = fname)
$txt.focus
end

#メニューの作成
TkFrame.new{|f|
pack( 'fill'=>'x', 'side'=>'top')

TkMenubutton.new(f, 'text'=>'ファイル', 'underline'=>0){|btn|
pack('side'=> 'left')
btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
menu.add('command','label'=>'ファイルを開く','command'=>proc{open_file})
menu.add('separator')
menu.add('command','label'=>'保存','command'=>proc{save_file})
menu.add('command','label'=>'別名で保存','command'=>proc{save_as})
menu.add('separator')
menu.add('command', 'label'=>'人間をやめる', 'command'=>proc{exit})
}

TkMenubutton.new(f, 'text'=>'mode', 'underline'=>0){|btn|
pack('side'=> 'left')
btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))
menu.add('command','label'=>'molvieViewer','command'=>proc{new_file})
menu.add('command','label'=>'molvieProgection','command'=>proc{open_file})
menu.add('command','label'=>'molvieDock','command'=>proc{save_file})
menu.add('command','label'=>'molvieFlight','command'=>proc{save_as})
menu.add('command', 'label'=>'molvieMrcViewer', 'command'=>proc{exit})
}

TkMenubutton.new(f, 'text'=>'Display', 'underline'=>0){|btn|
pack('side'=> 'left')
btn.menu(menu = TkMenu.new(btn, 'tearoff'=>false))

menu.add('command','label'=>'新規のファイル作成','command'=>proc{new_file})
menu.add('command','label'=>'ファイルを開く','command'=>proc{open_file})
menu.add('separator')
menu.add('command','label'=>'保存','command'=>proc{save_file})
menu.add('command','label'=>'別名で保存','command'=>proc{save_as})
menu.add('separator')
menu.add('command', 'label'=>'人間をやめる', 'command'=>proc{exit})
}
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

