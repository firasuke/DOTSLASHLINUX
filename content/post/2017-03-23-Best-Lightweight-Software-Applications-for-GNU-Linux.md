+++
title = "Best Lightweight Software/Applications for GNU/Linux!"
slug = "best lightweight software applications for gnu linux"
nick = "lapps"
date = "2017-03-23"
author = "Firas Khalil Khana"
imgsrc = "/img/lightweight.png"
imgalt = "lightweight"
categories = [ "popular" ]
+++
In this article I'll be listing some of the lightest applications the GNU/Linux world has to offer, some of which you may know and some not. These applications will not only be lightweight but will not sacrifice that much convenience for the performance and low memory footprint they offer.
<br/>
<br/>

I'll start from ground up, and by that I mean from the bootloader to userspace.
<br/>
<hr/>
<h3>1- Bootloader: <a href="https://lilo.alioth.debian.org/" target="_blank">LILO</a> vs <a href="http://www.syslinux.org/wiki/index.php?title=EXTLINUX" target="_blank">EXTLINUX</a></h3>
LILO is the lightest bootloader currently available. It's development was discontinued in Dec. 2015 , but it still works perfectly fine with ext4 filesystems. The configuration file is very straightforward and it requires updating so don't you forget to update LILO once you're done editing its configuration file.
<br/>
<br/>
It also has another limitation, that is you can't use more than one initrd. So if you had your microcode updates in an initrd, they won't work with LILO, but don't worry DOTSLASHLINUX has guides on booting without an initrd and building microcode updates directly into the kernel.
<br/>
<br/>
On the other hand, EXTLINUX is another flavor of Syslinux the lightweight bootloader. It has a simple configuration, supports <mark>ext2, ext3, ext4, BTRFS, NTFS, FAT12, FAT16, FAT32, XFS, UFS and FFS</mark> and it doesn't require updating once you're done with editing its configuration file, which is impressive once you start to count the number of times you forgot to update your GRUB or LILO config.
<br/>
<hr/>
<h3>2- Kernel: Custom Kernel</h3>
Hopefully, a whole series on how to configure your kernel is coming, so please look up to it!
<br/>
<hr/>
<h3>3- initrd/initramfs : None</h3>
Yes, you can boot without an initrd/initramfs. Kindly check our article <a href="https://www.dotslashlinux.com/2017/04/29/Booting-the-Linux-Kernel-Without-an-initrd-initramfs.html" target="_blank">Booting the Linux Kernel Without an initrd/initramfs</a>.
<br/>
<br/>
"Hold your horses... What about the intel/amd microcode updates that boost my processor's performance?" Well, I never said that you needed an initrd to use them. You can easily build them directly into the linux kernel. How you ask? Kindly follow our guide on <a href="https://www.dotslashlinux.com/2017/04/30/Building-Intel-CPU-Microcode-Updates-Directly-into-the-Linux-Kernel.html" target="_blank">Building Intel CPU Microcode Updates Directly into the Linux Kernel</a>.
<br/>
<hr/>
<h3>4- Shell: <a href="https://en.wikipedia.org/wiki/Almquist_shell" target="_blank">DASH</a> VS <a href="https://www.gnu.org/software/bash/" target="_blank">GNU BASH</a></h3>
After the boot process finished, it's time to choose a shell and here's where it gets tough. You see DASH or (Debian Almquist shell) is a modern POSIX implementation of sh and is 4x times faster then BASH. It also uses very minimal resources and has an overall low memory footprint. Since it's a POSIX compliant shell built for efficiency, you'll find the arrow keys not working and instead spitting out
<mark>^[[A ^[[B ^[[C ^[[D ^[[7~ ^[[8~</mark>
and you won't have a history file of your previous shell commands.
<br/>
<br/>
So if you're that type of person that loves minimalism and speed and can type long shell commands repeatedly without errors then go with DASH.On the other hand, if you prefer having a life... I mean a history of your commands, tab prediction at the price of some overhead then choose BASH.
<br/>
<hr/>
<h3>5- Display Servers: <a href="https://www.x.org/wiki/" target="_blank">Xorg</a> VS <a href="https://wayland.freedesktop.org/" target="_blank">Wayland</a></h3>
We have a tie here why? Well I'd pick a tie over flame wars any day! "Xorg is outdated, bloated with old unnecessary code..." we get that and we all hope that wayland will replace it one day. If wayland is working for you then stick with it, otherwise (and for the sake of this article) go for xorg.
<br/>
<hr/>
<h3>6- Starting X Server: <a href="https://en.wikipedia.org/wiki/Xinit" target="_blank">xinit</a></h3>
Yes, you do not need a display/login manager to start your Xorg server. You can easily use xinit and its frontend startx instead. You can even automate startx to start once you've logged in.
<br/>
<br/>
Here's DOTSLASHLINUX's guide to do that <a href="https://www.dotslashlinux.com/2017/03/29/Starting-Xorg-Server-Using-xinit.html" target="_blank">Starting Xorg Server Using xinit</a>.
<br/>
<hr/>
<h3>7- Sound System: <a href="https://en.wikipedia.org/wiki/Advanced_Linux_Sound_Architecture" target="_blank">ALSA</a> VS <a href="https://en.wikipedia.org/wiki/PulseAudio" target="_blank">PulseAudio</a></h3>
There isn't much comparison here as ALSA is a device driver, an interface between sound hardware and the kernel. Using ALSA alone is lighter than pulseaudio. Late versions of alsa support sound from multiple applications using the plugin dmix which is enabled by default. PulseAudio is a sound server built on top of alsa and can control sound coming from multiple applications unlike alsa which doesn't have this functionality.
<br/>
<br/>
If you wanted a basic configuration file to use on laptops with PCH/HDMI sound cards, kindly check DOTSLASHLINUX's custom ALSA configuration <a href="https://www.dotslashlinux.com/2017/03/30/Basic-ALSA-Configuration.html" target="_blank">Basic ALSA Configuration</a>.
<br/>
<hr/>
<h3>8- Window Manager: <a href="http://dwm.suckless.org/" target="_blank">dwm</a> VS <a href="http://openbox.org/wiki/Main_Page" target="_blank">Openbox</a></h3>
DWM isn't only a tiled window manager for X, it's a dynamic one as well but the reason why I chose dwm is that it's highly configurable, does what it needs to do perfectly well and super fast! Can't it get any better!
<br/>
<br/>
Here's DOTSLASHLINUX's custom dwm configuration <a href="https://www.dotslashlinux.com/2017/04/23/Best-dwm-Configuration.html" target="_blank">Best dwm Configuration</a>.
<br/>
<br/>
On the other hand, openbox is the de facto stacked window manager for lightweight GNU/Linux distros. It's heavier than dwm, but it's for those who absolutely can't use or hate tiled window managers.
<br/>
<hr/>
<h3>9- Status Bar vs Panel: <a href="https://github.com/drkhsh/slstatus/" target="_blank">slstatus</a> vs <a href="https://wiki.lxde.org/en/LXPanel" target="_blank">LXPanel</a></h3>
slstatus is the lightest status bar, it was made and should be used with dwm. Here's DOTSLASHLINUX's custom slstatus configuration <a href="https://www.dotslashlinux.com/2017/04/24/Best-slstatus-Configuration.html" target="_blank">Best slstatus Configuration</a>.
<br/>
<br/>
If you're into openbox then LXPanel is your friend. Yes, LXPanel is lighter than fbpanel, pypanel, tint2... you name it! How come? Out of the box it has a workspace switcher, minimize-all-windows button, volume plugin, battery plugin, networking plugin, cpu/ram usage plugin, temperature plugin, date/time plugin...etc.
<br/>
<br/>
Overall it has a significantly lower memory footprint than other panels using the same plugins.
<br/>
<hr/>
<h3>10- File Manager: <a href="https://blog.lxde.org/category/pcmanfm/" target="_blank">PCManFM</a></h3>
There really isn't much competition here. PCManFM dominates the lightweight category of file managers with a GUI.
<br/>
<hr/>
<h3>11- Desktop Manager: None VS <a href="https://blog.lxde.org/category/pcmanfm/" target="_blank">PCManFM</a></h3>
PCManFM can be used to manage the desktop. You can easily organize your icons on your desktop in a neat grid provided by PCManFM. You can also operate on your desktop as you would normally do inside a folder in a file manager.
<br/>
<hr/>
<h3>12- Application Launcher: <a href="http://tools.suckless.org/dmenu/" target="_blank">dmenu</a></h3>
Lightest application launcher available. It was originally developed to be used with dwm, but it can be used with any window manager. You can map it to a keyboard shortcut.
<br/>
<hr/>
<h3>13- Terminal Emulator: <a href="https://en.wikipedia.org/wiki/Rxvt-unicode" target="_blank">rxvt-unicode</a> (urxvtd & urxvtc)</h3>
Some may argue and say that st is lighter or that lxterminal is better, but if you're only going to run a single instance of a terminal emulator without needing the support for scrolling back up then go with st... Otherwise, you can heavily benefit from urxvt. Once you get the daemon (urxvtd) running, you can open for example 100 clients (urxvtc) and the memory footprint would roughly stay the same. Try opening 100 tabs in lxterminal or opening 100 instances of st and measure its memory usage and see for yourself...
<br/>
<br/>
Here's DOTSLASHLINUX's custom urxvt configuration for least memory footprint <a href="https://www.dotslashlinux.com/2017/03/30/Configuring-rxvt-unicode-urxvt.html" target="_blank">Configuring rxvt-unicode (urxvt)</a>.
<br/>
<hr/>
<h3>14- Network Manager: <a href="https://01.org/connman" target="_blank">ConnMan</a></h3>
Connman is lighter than both NetworkManager and WICD. It supports wifi connection via wpa_supplicant, bluetooth via bluez, automatically manages wired connections and supports the usage of proxies and VPNs. The only drawback to it is that there's no official applet for it and the currently available applets are either old, slow or lacking some features.
<br/>
<hr/>
<h3>15- Image Viewer: <a href="https://spiegl.de/qiv/" target="_blank">QIV</a> VS <a href="http://lxde.sourceforge.net/gpicview/" target="_blank">GPicView</a></h3>
It's a matter of preference and easiness of use as both are lightweight image viewers, but qiv is lighter and loads images faster. However, qiv's controls may be hard to learn for some users. On the other hand, gpicview has a simple gtk gui that many users will prefer.
<br/>
<hr/>
<h3>16- Web Browser: <a href="https://www.qupzilla.com/" target="_blank">Qupzilla</a> VS <a href="https://otter-browser.org/" target="_blank">Otter</a></h3>
These two are the lightest "usable" web browsers with a GUI available on GNU/Linux. You may be wondering that " If they were so lightweight then why is my package manager pulling lots of dependencies? ". True they have some dependencies related to qt5 and qtwebkit, but once they're installed, they're much lighter than your mainstream browsers. They're even lighter than midori which is considered a lightweight gtk web browser. Otter is lighter than qupzilla but it's still under heavy development.
<br/>
<hr/>
<h3>17- PDF Reader: <a href="https://github.com/jristz/epdfview" target="_blank">ePDFView</a> VS <a href="https://mupdf.com/" target="_blank">MuPDF</a></h3>
ePDFView is convenient lightweight pdf reader for GNU/Linux. It's so small it weighs less than 200 kilobytes. However, it's not the fastest. That title goes to MuPDF which is not so light (package is around ~20 megabytes) but is the fastest pdf reader available for GNU/Linux. MuPDF controls may be annoying to some users as well.
<br/>
<hr/>
<h3>18- Audio Player: <a href="https://github.com/Alexey-Yakovenko/deadbeef" target="_blank">DeaDBeef</a> VS <a href="http://audacious-media-player.org/" target="_blank">Audacious</a></h3>
DeaDBeef is the lighter one (but not by much). However, I've encountered several problems while trying deadbeef. Audio files that had.m4a or.aac extension were unplayable and crashed the player. On the other hand, my experience with audacious was super smooth and it played whatever I through at it as long as it had audio.
<br/>
<hr/>
<h3>17- Video Player: <a href="https://mpv.io/" target="blank">mpv</a></h3>
Some may argue that mplayer is lighter, that is true but only slightly. Mpv plays all video formats known to man-kind and it uses less cpu resources than both mplayer and vlc. It also supports VAAPI (Video Acceleration API) and VDPAU (Video Decode and Presentation API) which can significantly reduce its cpu usage (VAAPI) and its gpu usage (VDPAU) making it the fastest, most powerful and least resource hungry video player on GNU/Linux.
<br/>
<br/>
Here's DOTSLASHLINUX's custom mpv configuration for maximum performance and maximum powersaving <a href="https://www.dotslashlinux.com/2017/03/31/Optimal-mpv-Configuration.html" target="_blank">Optimal mpv Configuration</a>.
<hr/>
<h3>18- Text Editor: <a href="https://sites.google.com/site/e3editor/" target="_blank">e3</a> VS <a href="https://en.wikipedia.org/wiki/GNU_nano" target="_blank">GNU nano</a> VS <a href="http://tarot.freeshell.org/leafpad/" target="_blank">Leafpad</a></h3>
e3 is the lightest and is written in assembly. Nano and e3 are for when you're inside a terminal or in a tty, and leafpad's when you're not. However, I'd pick e3/nano over leafpad any day any time.
<br/>
<hr/>
<h3>19- Screen Capture Tool: <a href="https://github.com/naelstrof/maim" target="_blank">maim</a></h3>
MAIM or (MAke IMage) is a lightweight screen capture tool that utilizes imlib2 to take screenshots. Just fire up a terminal and type:
<pre><code class="language-bash">maim imagename.format</code></pre>
<br/>
and a screenshot of your desktop with the name and format that you specified will be saved in the current directory that you're in. It has some nice options and can be mapped to a given keyboard shortcut.
<br/>
<hr/>
<h3>20- Screen Recording Tool: <a href="http://recordmydesktop.sourceforge.net/" target="_blank">recordMyDesktop</a> VS <a href="http://www.maartenbaert.be/simplescreenrecorder/" target="_blank">SimpleScreenRecorder</a> VS <a href="https://github.com/green-project/green-recorder" target="_blank">Green Recorder</a></h3>
Recordmydesktop is slightly lighter than simplescreenrecorder but doesn't have as many options as it does. Unless you have a good reason not to choose simplescreenrecorder, go with recordmydesktop. Green recorder is a new screen recorder claiming to be simple and functional, it's also the first screen recorder to support Wayland display server on GNOME session.
<br/>
<hr/>
<h3>21- BitTorrent Client: <a href ="https://transmissionbt.com/" target="_blank">Transmission</a></h3>
Available for CLI usage and has two GUI flavors (GTK & QT), transmission is a lightweight bittorrent client available for GNU/Linux.
<br/>
<hr/>
<h3>22- Archive Manager: <a href="xarchiver.sourceforge.net/" target="_blank">xarchiver</a></h3>
Xarchiver supports <mark>7-zip, arj, bzip2, gzip, rar, lha, lzma, lzop, deb, rpm, tar and zip</mark>.
<br/>
<hr/>
<h3>23- Process Viewer: <a href="https://hisham.hm/htop/" target="_blank">htop</a></h3>
Htop is an interactive process viewer for GNU/Linux. It supports mouse usage in terminal or tty through GPM (General Purpose Mouse or Console Mouse Support). It also monitors your cpu usage, memory usage, battery...etc.
<br/>
<hr/>
<h3>24- IRC Client: <a href="https://irssi.org/" target="_blank">irssi</a> VS <a href="http://xchat.org/" target="_blank">XChat</a></h3>
If you're in a terminal emulator or in a tty use irssi, otherwise use xchat. The only downside to irssi is that it's limited by the terminal emulator it was launched in and since many terminals don't support right to left languages (and if they did the text doesn't appear properly), you may want to choose xchat to talk in languages other than English.
<br/>
<hr/>
<h3>25- HTTP Server: <a href="https://www.lighttpd.net/" target="_blank">Lighttpd</a> or <a href="https://www.nginx.com/" target="_blank">NGINX</a></h3>
True lighttpd is the lightest available http server out there for GNU/Linux, but nginx outperforms it under heavy load.
<br/>
<hr/>
<h3>26- FTP Server: <a href="vsftpd.beasts.org/" target="_blank">vsftpd</a></h3>
Very Secure FTP Daemon (or vsftpd for short) is a tiny, stable and secure FTP daemon for GNU/Linux. It has a simple configuration file and is super fast.
<br/>
<hr/>
<h3>27- Voice Chat Server & Client: <a href="https://www.mumble.com/" target="_blank">Murmur</a> & <a href="https://www.mumble.com/" target="_blank">Mumble</a></h3>
I was really shocked by the high quality of murmur (server) and mumble (client). I definitely recommend it for gamers, work offices, local use...etc
<br/>
<hr/>
<h3>28- C/C++ IDE: <a href="https://www.geany.org/" target="_blank">Geany</a> VS <a href="https://www.qt.io/ide/" target="_blank">QtCreator</a></h3>
Geany is for GTK users and has poor autocompletion support (it can be extended using ctags but it's still not enough). On the other hand, qt creator albeit being used to create Qt applications, it can be used as a C/C++ IDE and it's a fast one indeed. It has an awesome autocompletion. To me it's a revamped code::blocks with a better GUI.
<br/>
<hr/>
<h3>29- Download Manager: <a href="https://www.gnu.org/software/wget/" target="_blank">GNU Wget</a> or <a href="http://ugetdm.com/" target="_blank">uGet</a></h3>
Wget something when you're in a terminal or a tty, uGet it when not.
<br/>
<hr/>
<h3>CONCLUSION</h3>
I hope you've enjoyed this article. This list of applications will be constantly updated and new entries will be added (that is if I found another lightweight yet convenient application for GNU/Linux). If you think I missed an application that you think is lightweight, then please let us know in the comments section below.
