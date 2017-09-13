+++
title = "The Linux Kernel Configuration Guide Part 18"
slug = "the linux kernel configuration guide part 18"
nick = "kernel18"
date = "2017-09-18"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel18.png"
imgalt = "kernel18"
categories = [ "kernel" ]
+++
Similarly to part 16, it's highly recommended that you leave this section alone. All needed options in this section will be forcibly included by other options in other sections so you don't have to worry about this section much.
<br/>
<br/>
One thing you could do is after you've included all the required options for your system, you can enter this section and exclude options that weren't forcibly included by other options (as in most cases they will not be used).
<br/>
<br/>
Again, the options I'll be listing here will be the ones that got forcibly included on my system, in addition to some other options that I found useful (with the help of SystemRescueCd of course) as you may find it useful.
<hr/>
<h3>Library routines  ---></h3>
<h3>-&ast;- CRC-CCITT functions</h3>
```none
Symbol:     CONFIG_CRC_CCITT

Help:       This option is provided for the case where no in-kernel-tree
            modules require CRC-CCITT functions, but a module built outside
            the kernel tree does. Such modules that use library CRC-CCITT
            functions require M here.

Type:       tristate

Choice:     built-in -*-

Reason:
```
