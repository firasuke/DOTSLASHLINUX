+++
title = "The Linux Kernel Configuration Guide Part 4"
slug = "the linux kernel configuration guide part 4"
nick = "kernel4"
date = "2017-08-27"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel4.png"
imgalt = "kernel4"
categories = [ "kernel" ]
+++
<h3>2- [&ast;] Enable loadable module support  ---></h3>
<h3>--- Enable loadable module support</h3>
```properties
Symbol:     CONFIG_MODULES

Help:       Kernel modules are small pieces of compiled code which can
            be inserted in the running kernel, rather than being
            permanently built into the kernel.  You use the "modprobe"
            tool to add (and sometimes remove) them.  If you say Y here,
            many parts of the kernel can be built as modules (by
            answering M instead of Y where indicated): this is most
            useful for infrequently used options which are not required
            for booting.  For more information, see the man pages for
            modprobe, lsmod, modinfo, insmod and rmmod.

            If you say Y here, you will need to run "make
            modules_install" to put the modules under /lib/modules/
            where modprobe can find them (you may need to be root to do
            this).

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/

            You can safely exclude this option if you're not on a optimus based laptop
            and have built all modules directly into your kernel.
```
<h3>[ ]   Forced module loading</h3>
```properties
Symbol:     CONFIG_MODULE_FORCE_LOAD

Help:       Allow loading of modules without version information (ie. modprobe
            --force).  Forced module loading sets the 'F' (forced) taint flag and
            is usually a really bad idea.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as forcing modules to load is dangerous
            and not recommended at all.
```
<h3>[&ast;]   Module unloading</h3>
```properties
Symbol:     CONFIG_MODULE_UNLOAD

Help:       Without this option you will not be able to unload any
            modules (note that some modules may not be unloadable
            anyway), which makes your kernel smaller, faster
            and simpler.  If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/

            You can safely exclude this option if you're not on a optimus based laptop
            and have built all modules directly into your kernel.
```
<h3>[ ]     Forced module unloading</h3>
```properties
Symbol:     CONFIG_MODULE_FORCE_UNLOAD

Help:       This option allows you to force a module to unload, even if the
            kernel believes it is unsafe: the kernel will remove the module
            without waiting for anyone to stop using it (using the -f option to
            rmmod).  This is mainly for kernel developers and desperate users.

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's even more dangerous than
            CONFIG_MODULE_FORCE_LOAD, and it's intended for developing purposes.
```
<h3>[ ]   Module versioning support</h3>
```properties
Symbol:     CONFIG_MODVERSIONS

Help:       Usually, you have to use modules compiled with your kernel.
            Saying Y here makes it sometimes possible to use modules
            compiled for different kernels, by adding enough information
            to the modules to (hopefully) spot any changes which would
            make them incompatible with the kernel you are running.  If
            unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's intended for testing
            and debugging purposes.
```
<h3>[ ]   Source checksum for all modules</h3>
```properties
Symbol:     CONFIG_MODULE_SRCVERSION_ALL

Help:       Modules which contain a MODULE_VERSION get an extra "srcversion"
            field inserted into their modinfo section, which contains a
            sum of the source files which made it.  This helps maintainers
            see exactly which source was used to build a module (since
            others sometimes change the module source without updating
            the version).  With this option, such a "srcversion" field
            will be created for all modules.  If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's intended for maintaining
            purposes.
```
<h3>[ ]   Module signature verification</h3>
```properties
Symbol:     CONFIG_MODULE_SIG

Help:       Check modules for valid signatures upon load: the signature
            is simply appended to the module. For more information see
            Documentation/module-signing.txt.

            Note that this option adds the OpenSSL development packages as a
            kernel build dependency so that the signing tool can use its crypto
            library.

            !!!WARNING!!!  If you enable this option, you MUST make sure that the
            module DOES NOT get stripped after being signed.  This includes the
            debuginfo strip done by some packagers (such as rpmbuild) and
            inclusion into an initramfs that wants the module size reduced.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's intended for maintaining
            purposes.
```
<h3>[ ]   Compress modules on installation</h3>
```properties
Symbol:     CONFIG_MODULES_COMPRESS

Help:       Compresses kernel modules when 'make modules_install' is run; gzip or
            xz depending on "Compression algorithm" below.

            module-init-tools MAY support gzip, and kmod MAY support gzip and xz.

            Out-of-tree kernel modules installed using Kbuild will also be
            compressed upon installation.

            Note: for modules inside an initrd or initramfs, it's more efficient
            to compress the whole initrd or initramfs instead.

            Note: This is fully compatible with signed modules.

            If in doubt, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as compressing your loadable
            kernel modules will slightly increase your boot time.

            Include this option only if you're space restricted.
```
<h3>[ ]   Trim unused exported kernel symbols</h3>
```properties
Symbol:     CONFIG_TRIM_UNUSED_KSYMS

Help:       The kernel and some modules make many symbols available for
            other modules to use via EXPORT_SYMBOL() and variants. Depending
            on the set of modules being selected in your kernel configuration,
            many of those exported symbols might never be used.

            This option allows for unused exported symbols to be dropped from
            the build. In turn, this provides the compiler more opportunities
            (especially when using LTO) for optimizing the code and reducing
            binary size.  This might have some security advantages as well.

            If unsure, or if you need to build out-of-tree modules, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as nvidia.ko kernel module requires
            these symbols in order to get a working bumblebee setup on an optimus
            based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
            
            It's not recommended that you include this option, but you can try
            and see if it works for you.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/09/14/linux%e5%86%85%e6%a0%b8%e9%85%8d%e7%bd%ae%e6%8c%87%e5%8d%97-enable-loadable-module-support/" target="_blank">click here</a>.
