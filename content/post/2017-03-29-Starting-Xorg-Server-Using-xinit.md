+++
title = "Starting Xorg Server using xinit"
slug = "starting xorg server using xinit"
nick = "xinit"
date = "2017-03-29"
author = "Firas Khalil Khana"
imgsrc = "/img/xinit.png"
imgalt = "xinit"
+++
In this article I'll show you how to correctly setup xinit to start your xorg server. I'll also demonstrate how you can auto startx once logged in a tty.
<br/>
<br/>
<hr/>
<h3 id="Installation">1- Installation</h3>
<br/>
Gentoo Linux:
{{< highlight bash >}}emerge --ask --update --newuse  x11-apps/xinit{{< /highlight >}}
<br/>
Void Linux:
{{< highlight bash >}}xbps-install -S xinit{{< /highlight >}}
<br/>
Arch Linux:
{{< highlight bash >}}pacman -Syu xorg-xinit{{< /highlight >}}
<hr/>
<h3 id="xserverrc">2- xserverrc</h3>
<br/>
In order to correctly setup xinit, you need to copy the global xserverrc to your home directory and name it as .xserverrc:
<br/>
{{< highlight bash >}}cp /etc/X11/xinit/xserverrc ~/.xserverrc{{< /highlight >}}
<br/>
Now, in order to maintain an authenticated session and prevent xauth from complaining about a missing .serverauth file every time you startx, you may need to modify you .xserverrc file. If your .xserverrc file looks like this:
{{< highlight bash "linenos=inline,hl_lines=5" >}}#!/bin/sh
if [ -z "$XDG_VTNR" ]; then
  exec /usr/bin/X -nolisten tcp "$@"
else
  exec /usr/bin/X -nolisten tcp "$@" vt$XDG_VTNR
fi{{< /highlight >}}
<br/>
Then you don't need to worry about an unautheticated X session, however if it were like this:
{{< highlight bash "linenos=inline" >}}#!/bin/sh
exec /usr/bin/X -nolisten tcp "$@"{{< /highlight >}}
<br/>
Then you need to add vt$XDG_VTNR to the end of the command. This states that Xorg has to be started on the same virtual terminal where the login occurred.
{{< highlight bash "linenos=inline" >}}#!/bin/sh
exec /usr/bin/X -nolisten tcp "$@" vt$XDG_VTNR{{< /highlight >}}
<br/>
If the problem persists (xauth keeps complaining about missing file /home/user/serverauth), you can edit the startx script with your favorite editor:
{{< highlight bash >}}nano /usr/bin/startx{{< /highlight >}}
<br/>
Then change <mark>enable_xauth=1</mark> to <mark>enable_xauth=0</mark> (line 29 here):
{{< highlight bash "linenos=inline,hl_lines=29" >}}#!/bin/sh

#
# This is just a sample implementation of a slightly less primitive
# interface than xinit. It looks for user .xinitrc and .xserverrc
# files, then system xinitrc and xserverrc files, else lets xinit choose
# its default. The system xinitrc should probably do things like check
# for .Xresources files and merge them in, start up a window manager,
# and pop a clock and several xterms.
#
# Site administrators are STRONGLY urged to write nicer versions.
#

unset DBUS_SESSION_BUS_ADDRESS
unset SESSION_MANAGER
userclientrc=$HOME/.xinitrc
sysclientrc=/etc/X11/xinit/xinitrc

userserverrc=$HOME/.xserverrc
sysserverrc=/etc/X11/xinit/xserverrc
defaultclient=xterm
defaultserver=/usr/bin/X
defaultclientargs=""
defaultserverargs=""
defaultdisplay=":0"
clientargs=""
serverargs=""
vtarg=""
enable_xauth=0 # Change this from 1 to 0
...{{< /highlight >}}
<hr/>
<h3 id="xinitrc">3- xinitrc</h3>
<br/>
As we did with xserverrc, we need to copy the global xinitrc to our home directory and name it as .xinitrc:
{{< highlight bash >}}cp /etc/X11/xinit/xserverrc ~/.xserverrc{{< /highlight >}}
<br/>
The global xinitrc configuration file (which will be executed if you forgot to make your own in your home directory) has the following:
{{< highlight bash "linenos=inline,hl_lines=51 52 53 54 55" >}}#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

twm &
xclock -geometry 50x50-1+1 &
xterm -geometry 80x50+494+51 &
xterm -geometry 80x20+494-0 &
exec xterm -geometry 80x66+0+0 -name login{{< /highlight >}}
<br/>
Notice lines 51 to 55, these are the only lines that you should edit! These lines indicate that twm, xclock and 3 xterm instances will be started (if installed obviously) once an Xorg session starts.
<br/>
<br/>
Since these are very outdated versions of what we intend to use, delete lines 51 to 55 and replace them with your favored session. In our case we love dwm and openbox delete lines 51 to 55 and add this for dwm:
{{< highlight bash >}}exec dwm{{< /highlight >}}
<br/>
or this for openbox:
{{< highlight bash >}}exec openbox-session{{< /highlight >}}
<br/>
Please be noted that the program(s) that you intend to start must be installed!
<hr/>
<h3 id="startx">4- startx</h3>
<br/>
Once you've done configuring xinit, you can now start your X session simply by running:
{{< highlight bash >}}startx{{< /highlight >}}
<hr/>
<h3 id="Auto_startx_at_Login">(Optional) Auto startx at Login (BASH Users Only)</h3>
<br/>
If you're using BASH you can automate the process of startx after logging in by adding this line to your ~/.bash_profile (create this file if it doesn't exist):
{{< highlight bash >}}if [ -z "$DISPLAY" ] && [ -n "$XDG_VTNR" ] && [ "$XDG_VTNR" -eq 1 ]; then
  exec startx
fi{{< /highlight >}}
