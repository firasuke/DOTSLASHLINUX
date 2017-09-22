+++
title = "The Linux Kernel Configuration Guide Part 2"
slug = "the linux kernel configuration guide part 2"
nick = "kernel2"
date = "2017-08-25"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel2.png"
imgalt = "kernel2"
categories = [ "kernel" ]
+++
<h3>Prerequisites</h3>
It's preferrable if you were using a gnu/linux distro of any kind and have the ncurses library and make installed. I urge you to use one of the recommended distros and Gentoo is favored among others.
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
```properties
Symbol: CONFIG_MODULES
Name: Enable loadable modules support
```
The <mark>spacebar</mark> button can be used to include options in the kernel either as built-in [&ast;] or as modules [M] or exclude them [ ].
<br/>
<br/>
Similarly the <mark>y</mark> key can be used to include options [&ast;], and the <mark>n</mark> key can be used for excluding options [ ].
<br/>
<br/>
The <mark>&#9166;</mark> (enter/return) button can be used to access the available nested child options for any single parent option.
<br/>
<br/>
Some options may be included or excluded by other options. <mark>-&ast;-</mark> refers to these included options and you can't exclude them unless you exclude all the options that included it.
<hr/>
<h3>(Gentoo Specific Options) Gentoo Linux  ---></h3>
The first section you'll see in the menu options when using Gentoo Linux, will be the Gentoo Linux section (that was predictable =D). Select that option and you'll see the following:
```properties
[*] Gentoo Linux support
[*]   Linux dynamic and persistent device naming (userspace devfs) support
[ ]   Select options required by Portage features
    Support for init systems, system and service managers  --->
```
<h3>[&ast;] Gentoo Linux support</h3>
```properties
Symbol:     CONFIG_GENTOO_LINUX

Help:       In order to boot Gentoo Linux a minimal set of config settings needs to
            be enabled in the kernel; to avoid the users from having to enable them 
            manually as part of a Gentoo Linux installation or a new clean config,
            we enable these config settings by default for convenience.

            See the settings that become available for more details and fine-tuning.

Type:       boolean

Choice:     built-in [*]

Reason:     If you're on Gentoo Linux (or managed to get a copy of one of the sources
            available in the gentoo repos), then it's quite obvious that this option 
            should be built in.
```
<h3>[&ast;] Linux dynamic and persistent device naming (userspace devfs) support</h3>
```properties
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

Type:       boolean

Choice:     built-in [*]

Reason:     Include this option in for a bootable gentoo installation =D.
```
<h3>[ ] Select options required by Portage features</h3>
```properties
Symbol:     CONFIG_GENTOO_LINUX_PORTAGE

Help:       This enables options required by various Portage FEATURES.
            Currently this selects:

            CGROUPS     (required for FEATURES=cgroup)
            IPC_NS	(required for FEATURES=ipc-sandbox)
            NET_NS	(required for FEATURES=network-sandbox)
            SYSVIPC     (required by IPC_NS)

            It is highly recommended that you leave this enabled as these FEATURES
            are, or will soon be, enabled by default.

Type:       boolean

Choice:     excluded [ ]

Reason:     It's highly recommended that you build this set of options in your kernel.
            
            Users who want to exclude CONFIG_CGROUPS, may want to exclude this option
            and build CONFIG_NAMESPACES, CONFIG_IPC_NS, CONFIG_NET_NS and CONFIG_SYSVIPC
            into the kernel (which is what I did).
```
<h3>Support for init systems, system and service managers  ---></h3>
<h3>[&ast;] OpenRC, runit and other script based systems and managers</h3>
```properties
Symbol:     CONFIG_GENTOO_LINUX_INIT_SCRIPT

Help:       The init system is the first thing that loads after the kernel booted.
            
            These config settings allow you to select which init systems to support;
            instead of having to select all the individual settings all over the
            place, these settings allows you to select all the settings at once.
            
            This particular setting enables all the known requirements for OpenRC,
            runit and similar script based systems and managers.
            
            If you are unsure about this, it is best to leave this setting enabled.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using OpenRC or runit as your init system.

            You can safely exclude this option only if you're using systemd instead.
```
<h3>[ ] systemd</h3>
```properties
Symbol:     CONFIG_GENTOO_LINUX_INIT_SYSTEMD

Help:       The init system is the first thing that loads after the kernel booted.
            
            These config settings allow you to select which init systems to support;
            instead of having to select all the individual settings all over the
            place, these settings allows you to select all the settings at once.
            
            This particular setting enables all the known requirements for systemd;
            it also enables suggested optional settings, as the package suggests to.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're using OpenRC or runit as your
            init system.
            
            Include this option only if you're using systemd instead.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/08/27/linux%e5%86%85%e6%a0%b8%e9%85%8d%e7%bd%ae%e6%8c%87%e5%8d%97-gentoo-linux-support/" target="_blank">click here</a>.
