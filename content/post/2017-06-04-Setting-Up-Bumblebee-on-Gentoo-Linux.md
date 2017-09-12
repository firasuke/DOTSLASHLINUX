+++
title = "Setting Up Bumblebee on Gentoo Linux"
slug = "setting up bumblebee on gentoo linux"
nick = "bumblebee"
date = "2017-06-04"
author = "Firas Khalil Khana"
imgsrc = "/img/bumblebee.png"
imgalt = "bumblebee"
categories = [ "popular" ]
+++
Optimus support on a GNU/Linux distro has always been a hassle thanks to NVIDIA... Therefore projects were created to compensate for this powersaving feature. Enter bumblebee a project aimed to replicate NVIDIA's optimus function on GNU/Linux!.
<br/>
<br/>
In this article I'll be talking about setting up a working bumblebee setup on Gentoo Linux. Worry not because setting up bumblebee on Arch Linux/Void Linux is easy. Not that it's hard on Gentoo, but several steps are required to get a fully working bumblebee setup.

When we talk bumblebee, several things should come to one's mind:
<ol>
<li>A laptop with 2 GPUs an iGPU (integrated intel gpu) and a dGPU (discrete NVIDIA gpu).</li>
<li>A kernel that supports loading and unloading modules.</li>
<li>A proper <mark>/etc/portage/make.conf</mark> that works with this setup.</li>
<li>The packages bumblebee, primus and bbswitch must be installed.</li>
<li>Your user must be added to the following groups <mark>video</mark> and <mark>bumblebee</mark>.</li>
<li>You should enable the service <mark>bumblebee</mark>.</li>
</ol>
On Gentoo, extra steps are required to get bumblebee working, but guess what, you won't be going back to Arch Linux ever again because bumblebee on Gentoo is hard to setup.
<br/>
<br/>
Before we get started, I want to point out that bumblebee is a fairly old project (last release was on 26 April 2013), but it still works perfectly. Until NVIDIA decides to make optimus working properly on GNU/Linux, you should be using bumblebee.
<hr/>
<h3>1- Checking if Your Laptop Uses NVIDIA Optimus</h3>
<br/>
This is pretty much straightforward. If you have an intel processor (2nd Gen +) and a NVIDIA gpu, then you probably have optimus on your laptop. For those who want to check fire up your favorite terminal and run:

```none
lspci -k
```
```none
...
00:02.0 VGA compatible controller: Intel Corporation 4th Gen Core Processor Integrated Graphics Controller (rev 06)
	Subsystem: Toshiba America Info Systems 4th Gen Core Processor Integrated Graphics Controller
	Kernel driver in use: i915
01:00.0 3D controller: NVIDIA Corporation GK208M [GeForce GT 740M] (rev ff)
...
```
<br/>
In my case I'm using an <mark>Intel HD4600</mark> (cpu is 4th Gen Core i7 4700MQ) as my iGPU and my dGPU is a <mark>NVIDIA GT740M</mark>.
<br/>
Don't worry if your drivers in use (for now) are different, in my case I have built-in modules and my NVIDIA card is OFF (NVIDIA driver isn't loaded at boot which means bumblebee is working perfectly).
<br/>
<br/>
As you can see, optimus laptops have VGA compatible controller which is the integrated intel card that manages the display and uses the i915 kernel driver, and a 3D controller which is the stronger NVIDIA card which is going to be used when needed via bumblebee.
<br/>
<br/>
If your GNU/Linux experience was awful so far because your laptop was on fire 24/7, then you probably have an optimus laptop that needs correct configuration.
<hr/>
<h3>2- Checking if Your Kernel Supports Loading/Unloading Modules</h3>
<br/>
In order for bumblebee to work, then <mark>bbswitch</mark> must be loaded at boot time and <mark>nvidia</mark> mustn't.
<br/>
<br/>
Make sure that <mark>CONFIG_MODULES=y</mark> and <mark>CONFIG_MODULE_UNLOAD=y</mark> are enabled.
	<br/>
<hr/>
<h3>3- Optimizing your '/etc/portage/make.conf'</h3>
<br/>
Now make sure that you have the following in your <mark>/etc/portage/make.conf</mark>:
<br/>
```none
vim /etc/portage/make.conf
```
```none
...
VIDEO_CARDS="intel i965 nvidia"
...
```
<br/>
In most cases using <mark>i965</mark> should be fine, however if you were using an older card then please check the following <a href="https://wiki.gentoo.org/wiki/Intel#Feature_support" target="_blank">Intel Feature Support on Gentoo Linux</a>.
<br/>
<br/>
Now sync and update your system:
```none
emerge --sync && emerge -avuDN @world
```
<br/>
Now simply reboot your system, and continue this article.
```bash
shutdown -r now
```
<hr/>
<h3>4- Installation</h3>
<br/>
For the installation part, we need 3 packages, <mark>bumblebee</mark>,<mark>primus</mark> and <mark>bbswitch</mark>. It's recommended to download the live (git or -9999) versions of the previous packages to ensure that they work well with recent kernel and nvidia-drivers versions.
<br/>
<br/>
Fire up your favorite text editor, and make sure your <mark>/etc/portage/package.accept_keywords</mark> -(which in my case is a single file and not a directory)- contains the following:
```none,line-numbers
=sys-power/bbswitch-9999 **
=x11-misc/bumblebee-9999 **
=x11-misc/primus-0.2 ~amd64
```
<br/>
Now simply run:
```none
emerge -av bbswitch primus bumblebee
```
<hr/>
<h3>5- Adding Your User to the Groups video and bumblebee</h3>
<br/>
After installing the previous packages, add your <mark>USER</mark> to the groups <mark>video</mark> and <mark>bumblebee</mark>:
```none
gpasswd -a USER video && gpasswd -a USER bumblebee
```
<br/>
Don't forget to replace <mark>USER</mark> with your real username.
<br/>
<br/>
Now logout and relogin and your user should be in these groups.
<hr/>
<h3>6- Modifying /etc/init.d/bumblebee</h3>
<br/>
Here's where it gets tricky, this file is the one responsible for the hassle. Notice at the beginning of the file it depends on <mark>xdm</mark> and <mark>vgl</mark> and we don't need both of them for our setup to work.
<br/>
<br/>
You see it depends on xdm to make sure that bumblebee isn't started if there's no Xorg server installed. As for vgl, then we're using primus which is much better performance wise.
<br/>
<br/>
Open a terminal emulator and edit <mark>/etc/init.d/bumblebee</mark> with your favorite editor (vim is my favorite editor now), and delete the first 5 lines (or their equivalent; the depend() part) as shown below:
<br/>
```none
vim /etc/init.d/bumblebee
```
```none,line-numbers
depend() {
    need xdm
    need vgl
	after sshd
}

PIDFILE="${PIDFILE:-/var/run/bumblebee.pid}"

start() {
	ebegin "Starting BumbleBee Daemon"
		start-stop-daemon -S -p "${PIDFILE}" -x /usr/sbin/bumblebeed -- -D ${BUMBLEBEE_EXTRA_OPTS} --pidfile "${PIDFILE}"
	eend $?
}

stop() {
	ebegin "Stopping BumbleBee Daemon"
		start-stop-daemon -K -p "${PIDFILE}" -R SIGTERM/10
	eend $?
}
```
<br/>
So your file should look like this:
```none,line-numbers
PIDFILE="${PIDFILE:-/var/run/bumblebee.pid}"

start() {
	ebegin "Starting BumbleBee Daemon"
		start-stop-daemon -S -p "${PIDFILE}" -x /usr/sbin/bumblebeed -- -D ${BUMBLEBEE_EXTRA_OPTS} --pidfile "${PIDFILE}"
	eend $?
}

stop() {
	ebegin "Stopping BumbleBee Daemon"
		start-stop-daemon -K -p "${PIDFILE}" -R SIGTERM/10
	eend $?
}
```
<hr/>
<h3>7- Modifying /etc/bumblebee/bumblebee.conf</h3>
<br/>
We need to change some of the default settings that bumblebee uses, start that terminal emulator and with your favorite editor (vim), edit the file <mark>/etc/bumblebee/bumblebee.conf</mark>:
```none,line-numbers
# Configuration file for Bumblebee. Values should **not** be put between quotes

## Server options. Any change made in this section will need a server restart
# to take effect.
[bumblebeed]
# The secondary Xorg server DISPLAY number
VirtualDisplay=:8
# Should the unused Xorg server be kept running? Set this to true if waiting
# for X to be ready is too long and don't need power management at all.
KeepUnusedXServer=false
# The name of the Bumbleblee server group name (GID name)
ServerGroup=bumblebee
# Card power state at exit. Set to false if the card shoud be ON when Bumblebee
# server exits.
TurnCardOffAtExit=false
# The default behavior of '-f' option on optirun. If set to "true", '-f' will
# be ignored.
NoEcoModeOverride=false
# The Driver used by Bumblebee server. If this value is not set (or empty),
# auto-detection is performed. The available drivers are nvidia and nouveau
# (See also the driver-specific sections below)
Driver=nvidia
# Directory with a dummy config file to pass as a -configdir to secondary X
XorgConfDir=/etc/bumblebee/xorg.conf.d

## Client options. Will take effect on the next optirun executed.
[optirun]
# Acceleration/ rendering bridge, possible values are auto, virtualgl and
# primus.
Bridge=primus
# The method used for VirtualGL to transport frames between X servers.
# Possible values are proxy, jpeg, rgb, xv and yuv.
VGLTransport=rgb
# List of paths which are searched for the primus libGL.so.1 when using
# the primus bridge
PrimusLibraryPath=/usr/lib/primus:/usr/lib32/primus
# Should the program run under optirun even if Bumblebee server or nvidia card
# is not available?
AllowFallbackToIGC=false


# Driver-specific settings are grouped under [driver-NAME]. The sections are
# parsed if the Driver setting in [bumblebeed] is set to NAME (or if auto-
# detection resolves to NAME).
# PMMethod: method to use for saving power by disabling the nvidia card, valid
# values are: auto - automatically detect which PM method to use
#         bbswitch - new in BB 3, recommended if available
#       switcheroo - vga_switcheroo method, use at your own risk
#             none - disable PM completely
# https://github.com/Bumblebee-Project/Bumblebee/wiki/Comparison-of-PM-methods

## Section with nvidia driver specific options, only parsed if Driver=nvidia
[driver-nvidia]
# Module name to load, defaults to Driver if empty or unset
KernelDriver=nvidia
PMMethod=bbswitch
# colon-separated path to the nvidia libraries
LibraryPath=/usr/lib64/opengl/nvidia/lib:/usr/lib/opengl/nvidia/lib
# comma-separated path of the directory containing nvidia_drv.so and the
# default Xorg modules path
XorgModulePath=/usr/lib64/opengl/nvidia/lib,/usr/lib64/opengl/nvidia/extensions,/usr/lib64/xorg/modules/drivers,/usr/lib64/xorg/modules
XorgConfFile=/etc/bumblebee/xorg.conf.nvidia
```
<br/>
I've highlighted the lines that you should check, just make sure that:
	<br/>
	<br/>
	KeepUnusedXServer=false
	<br/>
	Driver=nvidia
	<br/>
	Bridge=primus
	<br/>
	VGLTransport=rgb (for vgl users)
	<br/>
	KernelDriver=nvidia
	<br/>
	PMMethod=bbswitch
	<br/>
<hr/>
<h3>8- Enabling and Starting bumblebee Service</h3>
<br/>
Simply add the service <mark>bumblebee</mark> to the runlevel <mark>default</mark>:
```none
rc-update add bumblebee default
```
<br/>
Now simply reboot and you should be good to go!
```bash
shutdown -r now
```
<hr/>
<h3>(Optional) Checking if bumblebee is Working</h3>
<br/>
If you've followed along with this article then your bumblebee setup should be working 100%. I recommend using <mark>primusrun</mark> instead of <mark>optirun</mark> since optirun tends to spit out more errors than primusrun (but after our configuration they should both be using the primus bridge and provide similar performance.
<br/>
<br/>
To test our bumblebee configuration, install the package <mark>mesa-progs</mark>:
```none
emerge -av mesa-progs
```
<br/>
Now before testing anything the NVIDIA card should be OFF, and the nvidia module shouldn't be loaded, instead the module bbswitch should be loaded. To double check fire up that terminal emulator and run:
```bash
lsmod
```
```bash
Module                  Size  Used by
bbswitch                5461  0
```
<br/>
then run:
```bash
cat /proc/acpi/bbswitch
```
```none
0000:01:00.0 OFF
```
<br/>
As you can see:
<br/>
1- bbswitch is loaded
<br/>
2- nvidia isn't loaded
<br/>
3- card is OFF as reported by bbswitch
<br/>
<br/>
Now let's check if the NVIDIA card will be switched ON and the nvidia module will be loaded once optirun/primusrun are executed, and if it'll switch OFF and the nvidia module will be unloaded once optirun/primusrun finish executing.
<br/>
<br/>
Inside your terminal emulator (and while you're running in a Xorg session... obviously...) run:
```none
optirun glxgears
```
<br/>
or (but not both):
```none
primusrun glxgears
```
<br/>
A window showing glxgears should open. While it's running check the following:
```none
lsmod
```
```none
Module                  Size  Used by
nvidia              10652360  51
bbswitch                5461  0
```
<br/>
and:
```bash
cat /proc/acpi/bbswitch
```
```none
0000:01:00.0 ON
```
<br/>
Notice how the nvidia module got loaded and the card switched on. Now end the running glxgears and do a simple check, the card should be OFF and the nvidia module should be unloaded and bbswitch will stay loaded.
<br/>
<br/>
Some of you may say that using vgl gets me more fps when running glxgears or any benchmark application. That is simply not the case as vgl doesn't adjust itself to the screen's refresh rate like primus does. Try running the following and see how primus crushes vgl:
```none
vblank_mode=0 primusrun glxgears
```
<br/>
If your card was refusing to turn OFF and the nvidia module is still loaded upon finishing the execution, then run the following:
```bash
rmmod nvidia && echo "OFF" >> /proc/acpi/bbswitch
```
<hr/>
<h3>(Optional) USE Flags</h3>
<br/>
For those of you that are wondering what USE flags I'm using for my packages:
<br/>
<br/>
For <mark>nvidia-drivers</mark>(notice how I disabled <mark>uvm</mark> and <mark>kms</mark> USE flags, as they can lead to errors when unloading the nvidia module unless you're using a patched version of bumblebee):
```none
equery u nvidia-drivers
```
```none
* Found these USE flags for x11-drivers/nvidia-drivers-381.22:
 U I
 + + X           : Install the X.org driver, OpenGL libraries, XvMC libraries, and VDPAU libraries
 + + acpi        : Add support for Advanced Configuration and Power Interface
 + + compat      : Install non-GLVND libGL for backwards compatibility
 + + driver      : Install the kernel driver module
 + + gtk3        : Install nvidia-settings with support for GTK+ 3
 - - kms         : Enable support for kernel mode setting (KMS)
 - - pax_kernel  : PaX patches from the PaX project
 - - static-libs : Build static versions of dynamic libraries as well
 + + tools       : Install additional tools such as nvidia-settings
 - - uvm         : Install the Unified Memory kernel module (nvidia-uvm) for sharing memory between CPU and GPU in CUDA programs
 - - wayland     : Enable dev-libs/wayland backend
```
<br/>
For <mark>xf86-video-intel</mark>:
```none
equery u xf86-video-intel
```
```none
* Found these USE flags for x11-drivers/xf86-video-intel-2.99.917_p20170313:
 U I
 - - debug : Enable extra debug codepaths, like asserts and extra output. If you want to get meaningful backtraces see
             https://wiki.gentoo.org/wiki/Project:Quality_Assurance/Backtraces
 + + dri   : Enable direct rendering: used for accelerated 3D and some 2D, like DMA
 + + dri3  : (Restricted to <=x11-drivers/xf86-video-intel-2.99.917_p20160621)
             Enable DRI3 support
 + + sna   : Enable SandyBridge's New Acceleration (useful on all chipsets, not just SandyBridge)
 - - tools : Build the intel-virtual-output tool
 + + udev  : Enable virtual/udev integration (device discovery, power and storage device support, etc)
 - - uxa   : Enable UMA Acceleration Architecture
 + + xvmc  : Enables X-Video Motion Compensation support
```
<br/>
For <mark>bumblebee</mark>:
```none
equery u bumblebee
```
```none
* Found these USE flags for x11-misc/bumblebee-3.2.1:
 U I
 + + bbswitch            : Add dependency on sys-power/bbswitch for PM feature
 - - video_cards_nouveau : VIDEO_CARDS setting to build reverse-engineered driver for nvidia cards
 + + video_cards_nvidia  : VIDEO_CARDS setting to build driver for nvidia video cards
```
<hr/>
<h3>Workarounds</h3>
If bbswitch was unable to switch the ACPI state of the dGPU then you might want to double check your <mark>nvidia-drivers</mark> USE flags and make sure that only <mark>nvidia</mark> is being loaded and both <mark>uvm</mark> and <mark>kms</mark> are disabled. Make sure that no other power management services are running (as they may interfere with bbswitch and prevent it from turning the card off). These include <mark>tlp</mark>, <mark>powertop</mark> and <mark>laptop-mode-tools</mark> (either disable these services or uninstall them completely).
<br/>
<br/>
If bbswitch is still refusing to turn off the card (which is unlikely if you followed what I mentioned earlier) try adding
```none
"acpi_osi=!Windows\x202013" acpi_osi=Linux nogpumanager i915.enable_hd_vgaarb=1 enable_hd_vgaarb=1
```
<br/>
to your kernel command-line (this has worked for a couple of users, especially those with Thinkpads and Lenovo laptops).
<br/>
<br/>
Some users were receiving vgaarb errors (in dmesg):
```none
vgaarb: this pci device is not a vga device
vgaarb: this pci device is not a vga device
```
<br/>
Make sure that <mark>CONFIG_VGA_ARB=y</mark> and <mark>CONFIG_VGA_ARB_MAX_GPUS=2</mark>. If you're still seeing this error (even though it was fixed in 3.10 according to this <a href="https://bugzilla.kernel.org/show_bug.cgi?id=63641" target="_blank">Bugzilla Kernel 63641</a> and <a href="https://github.com/Bumblebee-Project/Bumblebee/issues/159" target="_blank">Bumblebee Github Issue #159</a>), you can try to patch your kernel with this <a href="https://pastebin.com/wpmFi38k" target="_blank">vgaarb patch</a> by running this (after downloading the patch file of course):
```none
patch -Np1 -i patch_file.patch
```
<hr/>
<h3>Conclusion</h3>
<br/>
Congratulations! No need to go back to Arch Linux now! You have a working bumblebee configuration on Gentoo Linux. One important thing to note though is that you may get some errors regarding the secondary gpu not starting or some segfaults, simply wait a few seconds and rerun what you're executing and it'll run.
<br/>
<br/>
Just keep in mind that since the card is being turned ON and OFF, you may want to wait a few seconds before and after the execution of any code using bumblebee to prevent errors from popping up.
<br/>
<br/>
Another important thing to keep note of is that whenever you do a major change in your kernel configuration remember to recompile the nvidia-drivers (and the kernel OFC :P), otherwise expect a ton of errors.
<br/>
<br/>
Thanks for reading the article! Have a great day!
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), provided chinese translation of this guide on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/08/23/gentoo%E5%8F%8C%E6%98%BE%E5%8D%A1%E5%AE%89%E8%A3%85%E9%85%8D%E7%BD%AE/" target="_blank">click here</a>.
