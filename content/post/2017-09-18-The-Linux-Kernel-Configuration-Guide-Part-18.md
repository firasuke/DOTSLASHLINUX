+++
title = "The Linux Kernel Configuration Guide Part 18 - Library routines  --->"
slug = "the linux kernel configuration guide part 18 library routines"
nick = "kernel18"
date = "2017-09-18"
author = "Firas Khana"
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
<h3>-&lowast;- CRC-CCITT functions</h3>
```properties
Symbol:     CONFIG_CRC_CCITT

Help:       This option is provided for the case where no in-kernel-tree
            modules require CRC-CCITT functions, but a module built outside
            the kernel tree does. Such modules that use library CRC-CCITT
            functions require M here.

Type:       tristate

Choice:     built-in -∗-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_WLAN,
            CONFIG_USB and a lot of important options.
```
<h3>-&lowast;- CRC16 functions</h3>
```properties
Symbol:     CONFIG_CRC16

Help:       This option is provided for the case where no in-kernel-tree
            modules require CRC16 functions, but a module built outside
            the kernel tree does. Such modules that use library CRC16
            functions require M here.

Type:       tristate

Choice:     built-in -∗-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_BT,
            CONFIG_BLOCK, CONFIG_EXT4_FS, CONFIG_RFKILL and a lot of
            important options.
```
<h3><&lowast;> CRC calculation for the T10 Data Integrity Field</h3>
```properties
Symbol:     CONFIG_CRC_T10DIF

Help:       This option is only needed if a module that's not in the
            kernel tree needs to calculate CRC checks for use with the
            SCSI data integrity subsystem.

Type:       tristate

Choice:     built-in <∗>

Reason:     If you've followed the guide in part 11, then a simple:

                cat lsmod.txt | grep crct10dif

            should tell you whether you need this option or not.
```
<h3>-&lowast;- CRC ITU-T V.41 functions</h3>
```properties
Symbol:     CONFIG_CRC_ITU_T

Help:       This option is provided for the case where no in-kernel-tree
            modules require CRC ITU-T V.41 functions, but a module built outside
            the kernel tree does. Such modules that use library CRC ITU-T V.41
            functions require M here.

Type:       tristate

Choice:     built-in -∗-

Reason:     Forcibly included as it's required by CONFIG_PCI, CONFIG_NET,
            CONFIG_64BIT, CONFIG_BLOCK and a lot of important options.
```
<h3>-&lowast;- CRC32/CRC32c functions</h3>
```properties
Symbol:     CONFIG_CRC32

Help:       This option is provided for the case where no in-kernel-tree
            modules require CRC32/CRC32c functions, but a module built outside
            the kernel tree does. Such modules that use library CRC32/CRC32c
            functions require M here.

Type:       tristate

Choice:     built-in -∗-

Reason:     Forcibly included as it's required by a lot of important options.
```
<h3>CRC32 implementation (Slice by 8 bytes)  ---></h3>
```properties
Help:       This option allows a kernel builder to override the default choice
            of CRC32 algorithm.  Choose the default ("slice by 8") unless you
            know that you need one of the others.
```
<h3>(X) Slice by 8 bytes</h3>
```properties
Symbol:     CONFIG_CRC32_SLICEBY8

Help:       Calculate checksum 8 bytes at a time with a clever slicing algorithm.
            This is the fastest algorithm, but comes with a 8KiB lookup table.
            Most modern processors have enough cache to hold this table without
            thrashing the cache.

            This is the default implementation choice.  Choose this one unless
            you have a good reason not to.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this options as other options
            are intended for testing and debugging purposes.
```
<h3>-&lowast;- CRC32c (Castagnoli, et al) Cyclic Redundancy-Check</h3>
```properties
Symbol:     CONFIG_LIBCRC32C

Help:       This option is provided for the case where no in-kernel-tree
            modules require CRC32c functions, but a module built outside the
            kernel tree does. Such modules that use library CRC32c functions
            require M here.  See Castagnoli93.
            Module will be libcrc32c.

Type:       tristate

Choice:     built-in -∗-

Reason:     Forcibly included as it's required by CONFIG_PCI, CONFIG_NET and
            a lot of important options.
```
<h3><&lowast;> XZ decompression support</h3>
```properties
Symbol:     CONFIG_XZ_DEC

Help:       LZMA2 compression algorithm and BCJ filters are supported using
            the .xz file format as the container. For integrity checking,
            CRC32 is supported. See Documentation/xz.txt for more information.

Type:       tristate

Choice:     built-in <∗>
```
<h3>[&lowast;]   x86 BCJ filter decoder</h3>
```properties
Symbol:     CONFIG_XZ_DEC_X86

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [∗]
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX followers 杨鑫 (Yang Mame) from China, decided to follow up with the series and provide Chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in Chinese <a href="https://blog.yangmame.top/Linux内核配置指南-Kernel-hacking-Library-routines-The-End.html" target="_blank">click here</a>.
