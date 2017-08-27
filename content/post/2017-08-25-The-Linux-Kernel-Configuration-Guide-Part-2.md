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
It's preferrable if you were using a gnu/linux distro of any kind and have the ncurses library and make installed. I urge you to use one of the recommended distros and Gentoo is favored among others.
<br/>
<br/>
I highly recommend that you stick with the ncurses version <mark>make menuconfig</mark>, since it's much better than the regular <mark>make config</mark>, as you can save your progress, go back and forth with options, can be opened in any terminal emulator with a proper size (when ncurses in installed) as well as on ttys and that's extremely helpful when rescuing your system since you'll be looking at the same interface wherever you go and whatever you choose.
<br/>
<br/>
I'll also be using the latest kernel version provided on the unstable branch on gentoo (gentoo-sources 4.12.9). You might have noticed that I switched from (ck-sources) because MuQSS was causing me a lot of boot time failures and many rcu stalls (basically a lot of headache) so I had to revert to CFS and CFQ.
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
```none
[*] Gentoo Linux support
[*]   Linux dynamic and persistent device naming (userspace devfs) support
[*]   Select options required by Portage features
    Support for init systems, system and service managers  --->
```
<h3>[*] Gentoo Linux support</h3>
```none
Symbol:     CONFIG_GENTOO_LINUX

Help:       In order to boot Gentoo Linux a minimal set of config settings needs to
            be enabled in the kernel; to avoid the users from having to enable them 
            manually as part of a Gentoo Linux installation or a new clean config,
            we enable these config settings by default for convenience.

            See the settings that become available for more details and fine-tuning.

Type:       boolean

Choice:     built-in [*]
```
<h3>[*] Linux dynamic and persistent device naming (userspace devfs) support</h3>
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

Type:       boolean

Choice:     built-in [*]
```
<h3>[*] Select options required by Portage features</h3>
```none
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

Choice:     built-in [*]
```
<h3>Support for init systems, system and service managers  ---></h3>
<h3>[*] OpenRC, runit and other script based systems and managers</h3>
```none
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
```
<h3>[ ] systemd</h3>
```none
Symbol:     CONFIG_GENTOO_LINUX_INIT_SYSTEMD

Help:       The init system is the first thing that loads after the kernel booted.
            
            These config settings allow you to select which init systems to support;
            instead of having to select all the individual settings all over the
            place, these settings allows you to select all the settings at once.
            
            This particular setting enables all the known requirements for systemd;
            it also enables suggested optional settings, as the package suggests to.

Type:       boolean

Choice:     excluded [ ]

Reason:     I'm currently using OpenRC to manage my boot scripts and as my service manager
            and have no need for systemd.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/08/27/%E7%BF%BB%E8%AF%91%EF%BC%9Alinux%E5%86%85%E6%A0%B8%E9%85%8D%E7%BD%AE%E6%8C%87%E5%8D%97%EF%BC%882%EF%BC%89/" target="_blank">click here</a>.
