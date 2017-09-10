+++
title = "The Linux Kernel Configuration Guide Part 11"
slug = "the linux kernel configuration guide part 11"
nick = "kernel11"
date = "2017-09-11"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel11.png"
imgalt = "kernel11"
categories = [ "kernel" ]
+++
Wow you've made it this far! Good job!
<br/>
<br/>
The reason you're here is either because you've been reading the articles steadily and you've reached part 11 or you skipped your way to part 11 in order to find out the required information needed to configure your kernel and know what options to include/exclude.
<br/>
<br/>
I don't blame you, but for sanity's sake I had to put this in the <mark>Device Drivers  ---></mark> section as it's heavily related.
<br/>
<br/>
Now you may have noticed that some of the options I included may not necessarly be required on your end. Worry not, as it's probably something driver specific . Though to be clear, we didn't go through a lot of driver options (maybe a little in the <mark>[&ast;] Networking support  ---></mark> section).
<br/>
<br/>
Okay enough talking, let's get this thing started!
<hr/>
<h3>How do I know what options I need to include in my kernel configuration?</h3>
The question that tired a lot of people especially kernel newbies. The ugly truth is that you're not going to find what your system supports if you're going to boot a kernel that you've made (unless you've enabled everything which is really a tedious and error prone process).
<br/>
<br/>
So the best solution is to grab a bootable ISO from a distribution well-known for its compatibility and performance. Luckily, we have two options to choose from.
<br/>
<br/>
The first being <a href="https://www.system-rescue-cd.org/Download/" target="_blank">SystemRescueCd</a> which is my obvious choice for two simple reasons. It's based on Gentoo Linux which is a pro if you're going to configure the kernel for a Gentoo Linux installation. And the second being it's support for various platforms.
<br/>
<br/>
The second being <a href="https://www.archlinux.org/download/" target="_blank">Arch Linux</a> which I don't recommend but can be useful in some cases.
<br/>
<br/>
So grab a bootable ISO from the underlined links above and I highly recommend that you download <a href="https://www.system-rescue-cd.org/Download/" target="_blank">SystemRescueCd</a>.
<hr>
<h3>How to create a live bootable USB from the ISO I just downloaded?</h3>
The process is pretty much straight forward (and off-topic but meh...), the only reason I've included this section is because the bootable ISO for SystemRescueCd is for Cds (now who didn't see that coming =D), so it won't work with the good ol' <mark>dd if=PathToISO.iso of=/dev/sdX status=progress</mark> and that might be a reason for newbies leaving it and picking the Arch Linux ISO instead (which I don't recommend).
<br/>
<br/>
<h3>SystemRescueCd</h3>
So basically you create a temporary directory, and mount the bootable ISO with the options <mark>-o loop,exec</mark>, then you plug in the USB stick you intend to boot from, and memorize its path. Then simply change your directory to where you mounted the ISO and run <mark>usb_inst.sh</mark>. When it's done, you <mark>cd</mark> your way out and unmount the ISO.
```bash
mkdir -p /tmp/cdrom
mount -o loop,exec systemrescuecd-x86-5.1.0.iso /tmp/cdrom
cd /tmp/cdrom
bash ./usb_inst.sh
cd ~
umount /tmp/cdrom
```
<h3>Arch Linux</h3>
Remember to change <mark>/dev/sdX</mark> to the real path of your USB stick.
```bash
dd if=PathToISO.iso of=/dev/sdX status=progress
```
<hr/>
<h3>Grab everything you can and leave... literally...</h3>
If everything is working as expected you should be live booting the ISO now on your USB. In case you went with SystemRescueCd, you can run <mark>startx</mark> to get a GUI if that makes you more comfortable. The guys who went with Arch Linux ISO won't have this luxury =D (not that it matters anyways).
<br/>
<br/>
Ok now mount your HDD or SDD partition on where you have Gentoo or your linux distribution installed (SystemRescueCd already has a <mark>/mnt/gentoo</mark> directory which is suitable in this case). Now it's preferrable that you create a directory in your <mark>/home/$USER</mark> and output everything into it.
```bash
mkdir /mnt/mountedblock
mount /dev/sdXY /mnt/mountedblock
mkdir /mnt/mountedblock/home/$USER/SystemRescueCd
cd /mnt/mountedblock/home/$USER/SystemRescueCd
```
Now we're going to grab the output of several useful tools and we'll be using those files later on the pick the right options for our kernel:
```bash
lspci -kk > /mnt/mountedblock/home/$USER/SystemRescueCd/lspcikk.txt
lspci -nnkvv > /mnt/mountedblock/home/$USER/SystemRescueCd/lspcinnkvv.txt
lsusb > /mnt/mountedblock/home/$USER/SystemRescueCd/lsusb.txt
lsusb -v > /mnt/mountedblock/home/$USER/SystemRescueCd/lsusbv.txt
lsmod > /mnt/mountedblock/home/$USER/SystemRescueCd/lsmod.txt

dmesg > /mnt/mountedblock/home/$USER/SystemRescueCd/dmesg.txt

cat /proc/cpuinfo > /mnt/mountedblock/home/$USER/SystemRescueCd/cpuinfo.txt
zcat /proc/config.gz > /mnt/mountedblock/home/$USER/SystemRescueCd/SysRescueCdKernel.config

tree /proc > /mnt/mountedblock/home/$USER/SystemRescueCd/treeproc.txt
tree /sys > /mnt/mountedblock/home/$USER/SystemRescueCd/treesys.txt
tree /dev > /mnt/mountedblock/home/$USER/SystemRescueCd/treedev.txt
```
<hr/>
<h3>Still Confused?</h3>
Congratulations, you've just grabbed a ton of information about your system. Now you need get ready to read through most of this info in order to understand your system better.
<br/>
<br/>
In most cases you'll be grepping certain keywords from these files. These keywords will be related to a kernel option one way or another.
<br/>
<br/>
I recommend that you start by reading <mark>lspcikk.txt</mark> and including the drivers your system supports. Once you're done you can start with <mark>lsusb.txt</mark>.
<br/>
<br/>
That should be enough to get your system booting (assuming you've included support for your partition table, filesystem and block device).
<br/>
<br/>
Now you can continue with <mark>cpuinfo.txt</mark> and see what flags and instructions your CPU supports, like <mark>msr</mark>, <mark>cpuid</mark>, <mark>mtrr</mark> ...etc. You can easily understand what these flags mean by visiting this link <a href="https://unix.stackexchange.com/questions/43539/what-do-the-flags-in-proc-cpuinfo-mean" target="_blank">What do the flags in /proc/cpuinfo mean?</a>
<br/>
<br/>
Now you can read <mark>dmesg.txt</mark> and understand what is being loaded and what's not, check if there are any ACPI warnings, conflicts or errors. In some cases it might even tell you if one of your drivers is old and there's a newer and in most cases better versions of it available (for example, synaptics PS/2 and RMI4/SMBUS).
<br/>
<br/>
You should have a solid base to stand on right now. You can continue fine-tuning your kernel by reading <mark>lspcinnkvvv.txt</mark> and <mark>lsusbv.txt</mark> and see if there are any extra features your hardware supports that you didn't include yet (ASPM being an example, you can do a simple <mark>cat lspcinnkvvv.txt | grep ASPM</mark> and find out whether ASPM is supported or not. You can keep doing this over and over with every other option out there).
<br/>
<br/>
Now you should be probably finished. Whenever, you feel stuck or extremely confused by an option, you can check this guide for further information or politely ask in IRC channels. You can also check <mark>SysRescueCdKernel.config</mark> and see whether they included this option or not (beware you shouldn't be copy pasting everything you see included in <mark>SysRescueCdKernel.config</mark> as you'll be back to square one with a bloated kernel that's suited for a couple of million systems and not fine-tuned to run on your system).
<br/>
<br/>
You can also use <mark>treeproc.txt</mark>, <mark>treesys.txt</mark> and <mark>treedev.txt</mark> as reference to get further information of your system.
<br/>
<br/>
Hope this small sub-guide helped you out! Now back to the main guide!
<br/>
<br/>
One last thing, starting from this part, I'll only be listing the options that are required for my drivers to work. Not much explanation is needed as the reason for excluding other options would simply be because I don't have such parts in my system.
<hr/>
<h3>Device Drivers  ---></h3>
<h3>Generic Driver Options  ---></h3>
<h3>-&ast;- Maintain a devtmpfs filesystem to mount at /dev</h3>
```none
Symbol:     CONFIG_DEVTMPFS

Help:       This creates a tmpfs/ramfs filesystem instance early at bootup.
            In this filesystem, the kernel driver core maintains device
            nodes with their default names and permissions for all
            registered devices with an assigned major/minor number.
            Userspace can modify the filesystem content as needed, add
            symlinks, and apply needed permissions.
            It provides a fully functional /dev directory, where usually
            udev runs on top, managing permissions and adding meaningful
            symlinks.
            In very limited environments, it may provide a sufficient
            functional /dev without any further help. It also allows simple
            rescue systems, and reliably handles dynamic major/minor numbers.

            Notice: if CONFIG_TMPFS isn't enabled, the simpler ramfs
            file system will be used instead.

Type:       boolean

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it wasn't already forcibly included by CONFIG_GENTOO_LINUX
            and CONFIG_GENTOO_LINUX_UDEV).
```
<h3>[&ast;]   Automount devtmpfs at /dev, after the kernel mounted the rootfs</h3>
```none
Symbol:     CONFIG_DEVTMPFS_MOUNT

Help:       This will instruct the kernel to automatically mount the
            devtmpfs filesystem at /dev, directly after the kernel has
            mounted the root filesystem. The behavior can be overridden
            with the commandline parameter: devtmpfs.mount=0|1.
            This option does not affect initramfs based booting, here
            the devtmpfs filesystem always needs to be mounted manually
            after the rootfs is mounted.
            With this option enabled, it allows to bring up a system in
            rescue mode with init=/bin/sh, even when the /dev directory
            on the rootfs is completely empty.

Type:       boolean

Choice:     built-in [*]

Reason:     It's recommended that you include this option in your kernel as it's
            useful when attempting a system rescue.
```
<h3>-&ast;- Userspace firmware loading support</h3>
```none
Symbol:     CONFIG_FW_LOADER

Help:       This option is provided for the case where none of the in-tree modules
            require userspace firmware loading support, but a module built
            out-of-tree does.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option as well if you want
            to load modules (the list of options and drivers that require this option
            is endless so it's a good idea to include it).
```
<h3>[&ast;]   Include in-kernel firmware blobs in kernel binary</h3>
```none
Symbol:     CONFIG_FIRMARE_IN_KERNEL

Help:       The kernel source tree includes a number of firmware 'blobs'
            that are used by various drivers. The recommended way to
            use these is to run "make firmware_install", which, after
            converting ihex files to binary, copies all of the needed
            binary files in firmware/ to /lib/firmware/ on your system so
            that they can be loaded by userspace helpers on request.

            Enabling this option will build each required firmware blob
            into the kernel directly, where request_firmware() will find
            them without having to call out to userspace. This may be
            useful if your root file system requires a device that uses
            such firmware and do not wish to use an initrd.

            This single option controls the inclusion of firmware for
            every driver that uses request_firmware() and ships its
            firmware in the kernel source tree, which avoids a
            proliferation of 'Include firmware for xxx device' options.

            Say 'N' and let firmware be loaded from userspace.

Type:       boolean

Choice:     built-in [*]

Reason:     It's recommended that you include this option in your kernel as it's
            required for building microcode updates directly into the linux kernel.
```
