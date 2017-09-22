+++
title = "The Linux Kernel Configuration Guide Part 9"
slug = "the linux kernel configuration guide part 9"
nick = "kernel9"
date = "2017-09-08"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel9.png"
imgalt = "kernel9"
categories = [ "kernel" ]
+++
<h3>Executable file formats / Emulations  ---></h3>
<h3>-&ast;- Kernel support for ELF binaries</h3>
```properties
Symbol:     CONFIG_BINFMT_ELF

Help:       ELF (Executable and Linkable Format) is a format for libraries and
            executables used across different architectures and operating
            systems. Saying Y here will enable your kernel to run ELF binaries
            and enlarge it by about 13 KB. ELF support under Linux has now all
            but replaced the traditional Linux a.out formats (QMAGIC and ZMAGIC)
            because it is portable (this does *not* mean that you will be able
            to run executables from different architectures or operating systems
            however) and makes building run-time libraries very easy. Many new
            executables are distributed solely in ELF format. You definitely
            want to say Y here.

            Information about ELF is contained in the ELF HOWTO available from
            <http://www.tldp.org/docs.html#howto>.

            If you find that after upgrading from Linux kernel 1.2 and saying Y
            here, you still can't run any ELF binaries (they just crash), then
            you'll have to install the newest ELF runtime libraries, including
            ld.so (check the file <file:Documentation/Changes> for location and
            latest version).

Type:       boolean

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            as ELF is the binary format used on linux systems (that is if it isn't
            already forcibly included by CONFIG_X86_64 and CONFIG_IA32_EMULATION.
```
<h3>-&ast;- Kernel support for scripts starting with #!</h3>
```properties
Symbol:     CONFIG_BINFMT_SCRIPT

Help:       Say Y here if you want to execute interpreted scripts starting with
            #! followed by the path to an interpreter.

            You can build this support as a module; however, until that module
            gets loaded, you cannot run scripts.  Thus, if you want to load this
            module from an initramfs, the portion of the initramfs before loading
            this module must consist of compiled binaries only.

            Most systems will not boot if you say M or N here.  If unsure, say Y.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            as it's required to execute scripts and binaries that need an interpreter
            (and these include Java, Python2, Python3, .NET, DOS executables ...etc).

            This is also required by many init scripts as well and is used on countless
            distributions (CONFIG_GENTOO_LINUX and CONFIG_GENTOO_LINUX_INIT_SCRIPT).
```
<h3><&ast;> Kernel support for MISC binaries</h3>
```properties
Symbol:     CONFIG_BINFMT_MISC

Help:       If you say Y here, it will be possible to plug wrapper-driven binary
            formats into the kernel. You will like this especially when you use
            programs that need an interpreter to run like Java, Python, .NET or
            Emacs-Lisp. It's also useful if you often run DOS executables under
            the Linux DOS emulator DOSEMU (read the DOSEMU-HOWTO, available from
            <http://www.tldp.org/docs.html#howto>). Once you have
            registered such a binary class with the kernel, you can start one of
            those programs simply by typing in its name at a shell prompt; Linux
            will automatically feed it to the correct interpreter.

            You can do other nice things, too. Read the file
            <file:Documentation/binfmt_misc.txt> to learn how to use this
            feature, <file:Documentation/admin-guide/java.rst> for information about how
            to include Java support. and <file:Documentation/admin-guide/mono.rst> for
            information about how to include Mono-based .NET support.

            To use binfmt_misc, you will need to mount it:
                  mount binfmt_misc -t binfmt_misc /proc/sys/fs/binfmt_misc

            You may say M here for module support and later load the module when
            you have use for it; the module is called binfmt_misc. If you
            don't know what to answer at this point, say Y.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel as
            it's extremely useful when running emulators and virtual machines.
```
<h3>[ ] Enable core dump support</h3>
```properties
Symbol:     CONFIG_COREDUMP

Help:       This option enables support for performing core dumps. You almost
            certainly want to say Y here. Not necessary on systems that never
            need debugging or only ever run flawless code.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's intended for debugging
            purposes.
```
<h3>[&ast;] IA32 Emulation</h3>
```properties
Symbol:     CONFIG_IA32_EMULATION

Help:       Include code to run legacy 32-bit programs under a
            64-bit kernel. You should likely turn this on, unless you're
            100% sure that you don't have any 32-bit programs left.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you want to run 32-bit programs as you never know when you'll need
            support for 32-bit programs. The price of not doing so on Gentoo Linux
            and running a pure 64-bit system is costly as you'll have to rebuild 
            the whole system to get 32-bit support working.
```
<h3>< >   IA32 a.out support</h3>
```properties
Symbol:     CONFIG_IA32_AOUT

Help:       Support old a.out binaries in the 32bit emulation.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's not necessary to include
            support for such binaries anymore.

            Extremely old BSD and Linux systems may use a.out binaries that have
            shared libraries that rely on this format.
```
<h3>[&ast;] x32 ABI for 64-bit mode</h3>
```properties
Symbol:     CONFIG_X86_X32

Help:       Include code to run binaries for the x32 native 32-bit ABI
            for 64-bit processors.  An x32 process gets access to the
            full 64-bit register file and wide data path while leaving
            pointers at 32 bits for smaller memory footprint.

            You will need a recent binutils (2.22 or later) with
            elf32_x86_64 support enabled to compile a kernel with this
            option set.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you're planning on running 32-bit programs.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/09/21/linux%e5%86%85%e6%a0%b8%e9%85%8d%e7%bd%ae%e6%8c%87%e5%8d%97-executable-file-formats-emulations/" target="_blank">click here</a>.
