+++
title="Starting Xorg Server using xinit"
date="2017-03-29"
author="Firas Khalil Khana"
imgsrc="/img/startx.png"
imgalt="startx"
nick="xinit"
+++
In this article I'll show you how to correctly setup xinit to start your xorg server. I'll also demonstrate how you can auto startx once logged in a tty.
<br/>
<br/>
<hr/>
<h3 id="Installation">1- Installation</h3>
<br/>
Gentoo Linux:

<pre><code class="language-bash">emerge --ask --update --newuse  x11-apps/xinit</code></pre>
<br/>
Void Linux:

<pre><code class="language-bash">xbps-install -S xinit</code></pre>
<br/>
Arch Linux:

<pre><code class="language-bash">pacman -Syu xorg-xinit</code></pre>
<hr/>
<h3 id="xserverrc">2- xserverrc</h3>
<br/>
In order to correctly setup xinit, you need to copy the global xserverrc to your home directory and name it as .xserverrc:
<br/>
<pre><code class="language-bash">cp /etc/X11/xinit/xserverrc ~/.xserverrc</code></pre>
<br/>
Now, in order to maintain an authenticated session and prevent xauth from complaining about a missing .serverauth file every time you startx, you may need to modify you .xserverrc file. If your .xserverrc file looks like this:
<pre class="line-numbers"><code class="language-bash">#!/bin/sh
if [ -z "$XDG_VTNR" ]; then
  exec /usr/bin/X -nolisten tcp "$@"
else
  exec /usr/bin/X -nolisten tcp "$@" vt$XDG_VTNR
fi</code></pre>
<br/>
Then you don't need to worry about an unautheticated X session, however if it were like this:
<pre class="line-numbers"><code class="language-bash">#!/bin/sh
exec /usr/bin/X -nolisten tcp "$@"</code></pre>
<br/>
Then you need to add vt$XDG_VTNR to the end of the command. This states that Xorg has to be started on the same virtual terminal where the login occurred.
<pre class="line-numbers"><code class="language-bash">#!/bin/sh
exec /usr/bin/X -nolisten tcp "$@" vt$XDG_VTNR</code></pre>
<br/>
If the problem persists (xauth keeps complaining about missing file /home/user/serverauth), you can edit the startx script with your favorite editor:
<pre><code class="language-bash">nano /usr/bin/startx</code></pre>
<br/>
Then change <mark>enable_xauth=1</mark> to <mark>enable_xauth=0</mark> (line 29 here):
<pre class="line-numbers" data-line="29"><code class="language-bash">#!/bin/sh

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
...</code></pre>
<hr/>
<h3 id="xinitrc">3- xinitrc</h3>
<br/>
As we did with xserverrc, we need to copy the global xinitrc to our home directory and name it as .xinitrc:
<pre><code class="language-bash">cp /etc/X11/xinit/xserverrc ~/.xserverrc</code></pre>
<br/>
The global xinitrc configuration file (which will be executed if you forgot to make your own in your home directory) has the following:
<pre class="line-numbers" data-line="51, 52, 53, 54, 55"><code class="language-bash">#!/bin/sh

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
exec xterm -geometry 80x66+0+0 -name login</code></pre>
<br/>
Notice lines 51 to 55, these are the only lines that you should edit! These lines indicate that twm, xclock and 3 xterm instances will be started (if installed obviously) once an Xorg session starts.
<br/>
<br/>
Since these are very outdated versions of what we intend to use, delete lines 51 to 55 and replace them with your favored session. In our case we love dwm and openbox delete lines 51 to 55 and add this for dwm:
<pre><code class="language-bash">exec dwm</code></pre>
<br/>
or this for openbox:
<pre><code class="language-bash">exec openbox-session</code></pre>
<br/>
Please be noted that the program(s) that you intend to start must be installed!
<hr/>
<h3 id="startx">4- startx</h3>
<br/>
Once you've done configuring xinit, you can now start your X session simply by running:
<pre><code class="language-bash">startx</code></pre>
<hr/>
<h3 id="Auto_startx_at_Login">(Optional) Auto startx at Login (BASH Users Only)</h3>
<br/>
If you're using BASH you can automate the process of startx after logging in by adding this line to your ~/.bash_profile (create this file if it doesn't exist):
<pre><code class="language-bash">if [ -z "$DISPLAY" ] && [ -n "$XDG_VTNR" ] && [ "$XDG_VTNR" -eq 1 ]; then
  exec startx
fi</code></pre>
