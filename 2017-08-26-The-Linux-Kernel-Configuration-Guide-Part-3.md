+++
title = "The Linux Kernel Configuration Guide Part 3"
slug = "the linux kernel configuration guide part 3"
nick = "kernel3"
date = "2017-08-26"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel3.png"
imgalt = "kernel3"
+++
Before starting with the <mark>General setup</mark> section, there's this important option just before it:
<h3>[*] 64-bit kernel</h3>
```none
Symbol:     CONFIG_64BIT

Help:       Say yes to build a 64-bit kernel - formerly known as x86_64
            Say no to build a 32-bit kernel - formerly known as i386

Type:       boolean

Choice:     built-in [*]
```
<hr/>
<h3>1- General setup</h3>
<h3>(ck-patchset Specific Option) [*] MuQSS cpu scheduler</h3>
```none
Symbol:     CONFIG_SCHED_MUQSS

Help:       The Multiple Queue Skiplist Scheduler for excellent interactivity and
            responsiveness on the desktop and highly scalable deterministic
            low latency on any hardware.
  
Type:       boolean

Choice:     built-in [*]

Reason:     Since I'm running Gentoo Linux and on an unstable branch ~amd64, I wanted
            to achieve as much responsiveness and reduce the latency in order to be able
            to use other applications when compiling (especially my seamonkey web browser).
```
<h3>() Cross-compiler tool prefix</h3>
```none
Symbol:     CONFIG_CROSS_COMPILE

Help:       Same as running 'make CROSS_COMPILE=prefix-' but stored for
            default make runs in this kernel build directory.  You don't
            need to set this unless you want the configured kernel build
            directory to select the cross-compiler automatically.

Type:       string

Choice:     excluded ()

Reason:     The kernel will be used directly on my laptop and won't be built for another
            machine.
```
<h3>(-DOTSLASHLINUX) Local version - append to kernel release</h3>
```none
Symbol:     CONFIG_LOCALVERSION

Help:       Append an extra string to the end of your kernel version.
            This will show up when you type uname, for example.
            The string you set here will be appended after the contents of
            any files with a filename matching localversion* in your
            object and source tree, in that order.  Your total string can
            be a maximum of 64 characters.

Type:       string

Choice:     -DOTSLASHLINUX

Reason:     In order not to lose track of the custom kernels I build, I like to append
            extra strings to the end of my kernel's version.
```
<h3></h3>
```none
```
