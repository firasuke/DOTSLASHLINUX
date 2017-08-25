+++
title = "The Linux Kernel Configuration Guide Part 2"
slug = "the linux kernel configuration guide part 2"
nick = "kernel2"
date = "2017-08-25"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel2.png"
imgalt = "kernel2"
+++
<h3>Prerequisites</h3>
It's preferrable if you were using a gnu/linux distro of any kind and have the ncurses library installed. I urge you to use one of the recommended distros and Gentoo is favored among others.
<br/>
<br/>
I highly recommend that you stick with the ncurses version <mark>make menuconfig</mark>, since it's much better than the regular <mark>make config</mark>, as you can save your progress, go back and forth with options, can be opened in any terminal emulator with a proper size (when ncurses in installed) as well as on ttys and that's extremely helpful when rescuing your system since you'll be looking at the same interface wherever you go and whatever you choose.
<hr/>
<h3>Basic Controls</h3>
The <mark>&uarr;</mark> and the <mark>&darr;</mark> arrows can be used to move between the configuration options shown.
<br/>
<br/>
The <mark>&rarr;</mark> and the <mark>&larr;</mark> along with the <mark>&#8633;</mark> (tab) button can be used to move between the options (Select, Exit, Help, Save and Load) in the horizontal menu below.
<br/>
<br/>
The <mark>/</mark> button can be used to search the available symbols. In order not to create a state of confusion, I'll be using the word symbol for the capitalized underscore-separated version of the name. For example:
```none
Symbol: CONFIG_MODULES
Name: Enable loadable modules support
```
The <mark>&#9166;</mark> (enter/return) button can be used to access the available nested child options for any single parent option.
<hr/>
<h3>(Gentoo Specific Options) 1- Gentoo Linux</h3>
The first section you'll see in the menu options when using Gentoo Linux, will be the Gentoo Linux section (that was predictable =D). Select that option and you'll see the following:
```none
[*] Gentoo Linux support
[*]   Linux dynamic and persistent device naming (userspace devfs) support
[*]   Select options required by Portage features
    Support for init systems, system and service managers  --->
```
Available options:
<h3>Gentoo Linux support</h3>
```none
Symbol:     CONFIG_GENTOO_LINUX

Help:       In order to boot Gentoo Linux a minimal set of config settings needs to
            be enabled in the kernel; to avoid the users from having to enable them 
            manually as part of a Gentoo Linux installation or a new clean config,
            we enable these config settings by default for convenience.

            See the settings that become available for more details and fine-tuning.

Type:       Boolean

Choice:     Enabled [*]
```
<h3>Linux dynamic and persistent device naming (userspace devfs) support</h3>
```none
Symbol:     CONFIG_GENTOO_LINUX_UDEV

Help:       In order to boot Gentoo Linux a minimal set of config settings needs to
            be enabled in the kernel; to avoid the users from having to enable them
            manually as part of a Gentoo Linux installation or a new clean config,
            we enable these config settings by default for convenience.
            
            Currently this only selects TMPFS, DEVTMPFS and their dependencies.
            TMPFS is enabled to maintain a tmpfs file system at /dev/shm, /run and
            /sys/fs/cgroup; DEVTMPFS to maintain a devtmpfs file system at /dev.

            Some of these are critical files that need to be available early in the
            boot process; if not available, it causes sysfs and udev to malfunction.

            To ensure Gentoo Linux boots, it is best to leave this setting enabled;
            if you run a custom setup, you could consider whether to disable this.

Type:       Boolean

Choice:     Enabled [*]
```
