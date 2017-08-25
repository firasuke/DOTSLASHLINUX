+++
title = "The Linux Kernel Configuration Guide Part 3"
slug = "the linux kernel configuration guide part 3"
nick = "kernel3"
date = "2017-08-26"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel3.png"
imgalt = "kernel3"
+++
Before starting with the <mark>General setup</mark> section, there's this important option before it:
<h3>[*] 64-bit kernel</h3>
```none
Symbol:     CONFIG_64BIT

Help:       Say yes to build a 64-bit kernel - formerly known as x86_64
            Say no to build a 32-bit kernel - formerly known as i386

Type:       boolean

Choice:     built-in [*]
```
<hr/>
