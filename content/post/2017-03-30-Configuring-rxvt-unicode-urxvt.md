+++
title = "Configuring rxvt-unicode (urxvt)"
slug = "configuring rxvt-unicode rxvt"
nick = "urxvtc"
date = "2017-03-30"
author = "Firas Khalil Khana"
imgsrc = "/img/urxvtc.png"
imgalt = "urxvtc"
+++
In this article I'll show you how to get your urxvt daemon up and running, and give you a nice configuration file for urxvtc to use!
<br/>
<br/>
<hr/>
<h3 id="Installation">1- Installation</h3>
<br/>
Gentoo Linux:
```none
emerge --ask --update --newuse x11-terms/rxvt-unicode
```
Void Linux:
```none
xbps-install -S rxvt-unicode
```
Arch Linux:
```none
pacman -Syu rxvt-unicode
```
<hr/>
<h3 id="Starting_the_urxvt_daemon">2- Starting the urxvt daemon</h3>
<br/>
Once urxvt is installed, we should enable and start its daemon.Assuming you've read our xinit configuration guide, paste the following line of span in your ~/.xinitrc just before your dwm or openbox session:
```none
urxvtd --quiet --opendisplay --fork &
```
This will start the urxvt daemon every time the X server is started via startx.
<hr/>
<h3 id="Configuring_urxvtc">3- Configuring urxvtc</h3>
<br/>
Let's face it, urxvt looks hideous out of the box with that super small font and that scroll bar. Luckily, it supports xft fonts, which means we can do a whole lot to it.

Here's this useful piece of code:
<br/>
```bash
urxvtc -bg black -fg white -sr -fn "xft:DejaVu Sans Mono:pixelsize=15,style=Book"
```
This will start the urxvt client(s), with the following options (black background color, white text color, scrollbar to the right side, DejaVu Sans Book font with a size of 15 pixels).
<br/>
<br/>
You need to have dejavu fonts installed in order for this to work. You can always change these options to your liking.

Now keep in mind that whenever you need to launch urxvtc you need to use these options, so it's highly recommended that you map them to your prefered shortcut keys.

Another configuration made especially for use in dwm on gentoo (paste it in your ~/.Xresources):
```none,line-numbers
urxvt*font:                  xft:Terminus:size=10
urxvt*termName:              rxvt
urxvt*background:            #33393b
urxvt*foreground:            white
urxvt*scrollBar:             false
urxvt*perl-lib:              /usr/lib/urxvt/perl/
urxvt*perl-ext-common:       default,matcher
urxvt*urlLauncher:           /usr/bin/firefox
urxvt*matcher.button:        1

Xft*dpi:                     96
Xft*antialias:               true
Xft*hinting:                 true
Xft*hintstyle:		hintfull
Xft*rgba:		        rgb

URxvt.transparent:   	false
URxvt.tintColor:     	#54487a
URxvt.shading:       	100
URxvt.inheritPixmap:         false
URxvt.fading:   	        100
URxvt.saveLines: 	        50000

URxvt*scrollTtyOutput: 	false
URxvt*scrollWithBuffer:      true
URxvt*scrollTtyKeypress:     true

URxvt*color0:      	        #000000
URxvt*color1:       	        #9e1828
URxvt*color2:      	        #aece92
URxvt*color3:      	        #968a38
URxvt*color4:      	        #414171
URxvt*color5:      	        #963c59
URxvt*color6:      	        #418179
URxvt*color7:      	        #bebebe
URxvt*color8:      	        #666666
URxvt*color9:      	        #cf6171
URxvt*color10:     	        #c5f779
URxvt*color11:     	        #fff796
URxvt*color12:     	        #4186be
URxvt*color13:     	        #cf9ebe
URxvt*color14:     	        #71bebe
URxvt*color15:     	        #ffffff
```
<br/>
If these settings aren't being loaded (or are reset), then add the following to your .xinitrc file:
```none
[[ -f ~/.Xresources ]] && xrdb -merge ~/.Xresources
```
<hr/>
<h3 id="Mapping_urxvtc_to_a_shortcut_key_on_dwm">(Optional) Mapping urxvtc to a shortcut key on dwm</h3>
<br/>
Let's start by adding this to the commands section:
```c,line-numbers
/* commands */
static const char *termcmd[]  = { "urxvtc", NULL};
```
<br/>
Then let's add this entry to the modifiers section (In our case the shortcut keys will be ALT + x):
```c,line-numbers
/* modifier                     key        function        argument */
{ MODKEY,	                XK_x, 	   spawn,          {.v = termcmd } },
```
