+++
title = "The Linux Kernel Configuration Guide Part 11 - Device Drivers  --->"
slug = "the linux kernel configuration guide part 11 device drivers"
nick = "kernel11"
date = "2017-09-11"
author = "Firas Khana"
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
Now you may have noticed that some of the options I included may not necessarly be required on your end. Worry not, as it's probably something driver specific . Though to be clear, we didn't go through a lot of driver options (maybe a little in the <mark>[&lowast;] Networking support  ---></mark> section).
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
<h3><u>SystemRescueCd</u></h3>
So basically you create a temporary directory, and mount the bootable ISO with the options <mark>-o loop,exec</mark>, then you plug in the USB stick you intend to boot from, and memorize its path. Then simply change your directory to where you mounted the ISO and run <mark>usb_inst.sh</mark>. When it's done, you <mark>cd</mark> your way out and unmount the ISO.
```bash
mkdir -p /tmp/cdrom
mount -o loop,exec systemrescuecd-x86-5.1.0.iso /tmp/cdrom
cd /tmp/cdrom
bash ./usb_inst.sh
cd ~
umount /tmp/cdrom
```
<h3><u>Arch Linux</u></h3>
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
lshw -short > /mnt/mountedblock/home/$USER/SystemRescueCd/lshwshort.txt
lshw > /mnt/mountedblock/home/$USER/SystemRescueCd/lshw.txt

lspci -kk > /mnt/mountedblock/home/$USER/SystemRescueCd/lspcikk.txt
lspci -nnkkvvv > /mnt/mountedblock/home/$USER/SystemRescueCd/lspcinnkkvvv.txt

lsusb > /mnt/mountedblock/home/$USER/SystemRescueCd/lsusb.txt
lsusb -v > /mnt/mountedblock/home/$USER/SystemRescueCd/lsusbv.txt

lsmod > /mnt/mountedblock/home/$USER/SystemRescueCd/lsmod.txt

dmesg > /mnt/mountedblock/home/$USER/SystemRescueCd/dmesg.txt

lscpu > /mnt/mountedblock/home/$USER/SystemRescueCd/lscpu.txt
cat /proc/cpuinfo > /mnt/mountedblock/home/$USER/SystemRescueCd/cpuinfo.txt

cpuinfo2cpuflags-x86 > /mnt/mountedblock/home/$USER/SystemRescueCd/cpuinfo2cpuflags.txt
cpuid2cpuflags > /mnt/mountedblock/home/$USER/SystemRescueCd/cpuid2cpuflags.txt

zcat /proc/config.gz > /mnt/mountedblock/home/$USER/SystemRescueCd/SysRescueCdKernel.config

dmidecode > /mnt/mountedblock/home/$USER/SystemRescueCd/dmidecode.txt

sensors > /mnt/mountedblock/home/$USER/SystemRescueCd/sensors.txt

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
I recommend that you start by reading <mark>lspcikk.txt</mark> and including the drivers your system supports. Once you're done you can start with <mark>lsusb.txt</mark>. Moving on with <mark>lshwshort.txt</mark>
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
You should have a solid base to stand on right now. You can continue fine-tuning your kernel by reading <mark>lspcinnkkvvv.txt</mark>, <mark>lsusbv.txt</mark> and <mark>lshw.txt</mark> and see if there are any extra features your hardware supports that you didn't include yet (ASPM being an example, you can do a simple <mark>cat lspcinnkkvvv.txt | grep ASPM</mark> and find out whether ASPM is supported or not. You can keep doing this over and over with every other option out there).
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
<h3>-&lowast;- Maintain a devtmpfs filesystem to mount at /dev</h3>
```properties
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

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it wasn't already forcibly included by CONFIG_GENTOO_LINUX
            and CONFIG_GENTOO_LINUX_UDEV).
```
<h3>[&lowast;]   Automount devtmpfs at /dev, after the kernel mounted the rootfs</h3>
```properties
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

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel as it's
            useful when attempting a system rescue.
```
<h3>[&lowast;] Select only drivers that don't need compile-time external firmware</h3>
```properties
Symbol:     CONFIG_STANDALONE

Help:       Select this option if you don't have magic firmware for drivers that
            need it.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            as it's extremely unlikely that you'll have such 'magic' firmware.
```
<h3>[&lowast;] Prevent firmware from being built</h3>
```properties
Symbol:     CONFIG_PREVENT_FIRMWARE_BUILD

Help:       Say yes to avoid building firmware. Firmware is usually shipped
            with the driver and only when updating the firmware should a
            rebuild be made.
            If unsure, say Y here.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            and rebuilding the firmware should only be considered when updating
            it.
```
<h3>-&lowast;- Userspace firmware loading support</h3>
```properties
Symbol:     CONFIG_FW_LOADER

Help:       This option is provided for the case where none of the in-tree modules
            require userspace firmware loading support, but a module built
            out-of-tree does.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option as well if you want
            to load modules (the list of options and drivers that require this option
            is endless so it's a good idea to include it).
```
<h3>[&lowast;]   Include in-kernel firmware blobs in kernel binary</h3>
```properties
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

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel as it's
            required for building microcode updates directly into the linux kernel.

            DOTSLASHLINUX has a detailed guide on how to build microcode updates
            directly into the linux kernel, kindly check the link below:

                https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-updates-directly-into-the-linux-kernel/
```
<h3>(intel-ucode/06-3c-03) External firmware blobs to build into the kernel binary</h3>
```properties
Symbol:     CONFIG_EXTRA_FIRMWARE

Help:       This option allows firmware to be built into the kernel for the case
            where the user either cannot or doesn't want to provide it from
            userspace at runtime (for example, when the firmware in question is
            required for accessing the boot device, and the user doesn't want to
            use an initrd).

            This option is a string and takes the (space-separated) names of the
            firmware files -- the same names that appear in MODULE_FIRMWARE()
            and request_firmware() in the source. These files should exist under
            the directory specified by the EXTRA_FIRMWARE_DIR option, which is
            by default the firmware subdirectory of the kernel source tree.

            For example, you might set CONFIG_EXTRA_FIRMWARE="usb8388.bin", copy
            the usb8388.bin file into the firmware directory, and build the kernel.
            Then any request_firmware("usb8388.bin") will be satisfied internally
            without needing to call out to userspace.

            WARNING: If you include additional firmware files into your binary
            kernel image that are not available under the terms of the GPL,
            then it may be a violation of the GPL to distribute the resulting
            image since it combines both GPL and non-GPL work. You should
            consult a lawyer of your own before distributing such an image.

Type:       string

Choice:     (intel-ucode/06-3c-03) custom

Reason:     You may need to change this value if you're using a different processor.
            Check the link below for more information.
            
            It's recommended that you include this option in your kernel as it's
            required for building microcode updates directly into the linux kernel.

            DOTSLASHLINUX has a detailed guide on how to build microcode updates
            directly into the linux kernel, kindly check the link below:

                https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-updates-directly-into-the-linux-kernel/
```
<h3>(/lib/firmware) Firmware blobs root directory</h3>
```properties
Symbol:     CONFIG_EXTRA_FIRMWARE_DIR

Help:       This option controls the directory in which the kernel build system
            looks for the firmware files listed in the EXTRA_FIRMWARE option.
            The default is firmware/ in the kernel source tree, but by changing
            this option you can point it elsewhere, such as /lib/firmware/ or
            some other directory containing the firmware files.

Type:       string

Choice:     (/lib/firmware) custom

Reason:     It's recommended that you include this option in your kernel as it's
            required for building microcode updates directly into the linux kernel.

            DOTSLASHLINUX has a detailed guide on how to build microcode updates
            directly into the linux kernel, kindly check the link below:

                https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-updates-directly-into-the-linux-kernel/
```
<h3>-&lowast;- Plug and Play support  ---></h3>
```properties
Symbol:     CONFIG_PNP

Help:       Plug and Play (PnP) is a standard for peripherals which allows those
            peripherals to be configured by software, e.g. assign IRQ's or other
            parameters. No jumpers on the cards are needed, instead the values
            are provided to the cards from the BIOS, from the operating system,
            or using a user-space utility.

            Say Y here if you would like Linux to configure your Plug and Play
            devices. You should then also say Y to all of the protocols below.
            Alternatively, you can say N here and configure your PnP devices
            using user space utilities such as the isapnptools package.

            If unsure, say Y.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already included by CONFIG_PCI, CONFIG_ACPI and
            CONFIG_X86).
```
<h3>[&lowast;]   PNP debugging messages</h3>
```properties
Symbol:     CONFIG_PNP_DEBUG_MESSAGES

Help:       Say Y here if you want the PNP layer to be able to produce debugging
            messages if needed.  The messages can be enabled at boot-time with
            the pnp.debug kernel parameter.

            This option allows you to save a bit of space if you do not want
            the messages to even be built into the kernel.

            If you have any doubts about this, say Y here.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel as
            it provides really helpful information about PnP devices.
```
<h3>[&lowast;] Block devices  ---></h3>
```properties
Symbol:     CONFIG_BLK_DEV

Help:       Say Y here to get to see options for various different block device
            drivers. This option alone does not add any kernel code.

            If you say N, all options in this submenu will be skipped and disabled;
            only do this if you know what you are doing.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel.
```
<h3><&lowast;>   Loopback device support</h3>
```properties
Symbol:     CONFIG_BLK_DEV_LOOP

Help:       Saying Y here will allow you to use a regular file as a block
            device; you can then create a file system on that block device and
            mount it just as you would mount other block devices such as hard
            drive partitions, CD-ROM drives or floppy drives. The loop devices
            are block special device files with major number 7 and typically
            called /dev/loop0, /dev/loop1 etc.

            This is useful if you want to check an ISO 9660 file system before
            burning the CD, or if you want to use floppy images without first
            writing them to floppy. Furthermore, some Linux distributions avoid
            the need for a dedicated Linux partition by keeping their complete
            root file system inside a DOS FAT file using this loop device
            driver.

            To use the loop device, you need the losetup utility, found in the
            util-linux package, see
            <https://www.kernel.org/pub/linux/utils/util-linux/>.

            The loop device driver can also be used to "hide" a file system in
            a disk partition, floppy, or regular file, either using encryption
            (scrambling the data) or steganography (hiding the data in the low
            bits of, say, a sound file). This is also safe if the file resides
            on a remote file server.

            There are several ways of encrypting disks. Some of these require
            kernel patches. The vanilla kernel offers the cryptoloop option
            and a Device Mapper target (which is superior, as it supports all
            file systems). If you want to use the cryptoloop, say Y to both
            LOOP and CRYPTOLOOP, and make sure you have a recent (version 2.12
            or later) version of util-linux. Additionally, be aware that
            the cryptoloop is not safe for storing journaled filesystems.

            Note that this loop device has nothing to do with the loopback
            device used for network connections from the machine to itself.

            To compile this driver as a module, choose M here: the
            module will be called loop.

            Most users will answer N here.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it allows you to mount images (files with .img, .iso ...etc extensions)
            as if they were devices.
```
<h3>(0)     Number of loop devices to pre-create at init time</h3>
```properties
Symbol:     CONFIG_BLK_DEV_LOOP_MIN_COUNT

Help:       Static number of loop devices to be unconditionally pre-created
            at init time.

            This default value can be overwritten on the kernel command
            line or with module-parameter loop.max_loop.

            The historic default is 8. If a late 2011 version of losetup(8)
            is used, it can be set to 0, since needed loop devices can be
            dynamically allocated with the /dev/loop-control interface.

Type:       integer

Choice:     (0) custom

Reason:     It's highly recommended that you set the value of this option to 0
            as loop devices should be created on-demand and not precreated (unless
            neccessary).
```
<h3>Misc devices  ---></h3>
<h3>-&lowast;- Intel Management Engine Interface</h3>
```properties
Symbol:     CONFIG_INTEL_MEI

Help:       The Intel Management Engine (Intel ME) provides Manageability,
            Security and Media services for system containing Intel chipsets.
            if selected /dev/mei misc device will be created.

            For more information see
            <http://software.intel.com/en-us/manageability/>

Type:       tristate

Choice:     built-in -∗-

Reason:     It's recommended that you include this option in your kernel if you're
            using a system with a modern intel chipset.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep mei -A2

            should tell you whether you need this option or not.
```
<h3><&lowast;> ME Enabled Intel Chipsets</h3>
```properties
Symbol:     CONFIG_INTEL_MEI_ME

Help:       MEI support for ME Enabled Intel chipsets.

            Supported Chipsets are:
            7 Series Chipset Family
            6 Series Chipset Family
            5 Series Chipset Family
            4 Series Chipset Family
            Mobile 4 Series Chipset Family
            ICH9
            82946GZ/GL
            82G35 Express
            82Q963/Q965
            82P965/G965
            Mobile PM965/GM965
            Mobile GME965/GLE960
            82Q35 Express
            82G33/G31/P35/P31 Express
            82Q33 Express
            82X38/X48 Express

Type:       tristate

Choice:     built-in <∗>

Reason:     It's recommended that you include this option in your kernel if you're
            using a system with a modern intel chipset.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep mei -A2

            should tell you whether you need this option or not.
```
<h3>SCSI device support  ---></h3>
<h3>-&lowast;- SCSI device support</h3>
```properties
Symbol:     CONFIG_SCSI

Help:       If you want to use a SCSI hard disk, SCSI tape drive, SCSI CD-ROM or
            any other SCSI device under Linux, say Y and make sure that you know
            the name of your SCSI host adapter (the card inside your computer
            that "speaks" the SCSI protocol, also called SCSI controller),
            because you will be asked for it.

            You also need to say Y here if you have a device which speaks
            the SCSI protocol.  Examples of this include the parallel port
            version of the IOMEGA ZIP drive, USB storage devices, Fibre
            Channel, and FireWire storage.

            To compile this driver as a module, choose M here and read
            <file:Documentation/scsi/scsi.txt>.
            The module will be called scsi_mod.

            However, do not compile this as a module if your root file system
            (the one containing the directory /) is located on a SCSI device.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel if
            you're using one of the SCSI devices mentioned above (mainly a SCSI
            hard drive and CD-ROM).
```
<h3><&lowast;> SCSI disk support</h3>
```properties
Symbol:     CONFIG_BLK_DEV_SD

Help:       If you want to use SCSI hard disks, Fibre Channel disks,
            Serial ATA (SATA) or Parallel ATA (PATA) hard disks,
            USB storage or the SCSI or parallel port version of
            the IOMEGA ZIP drive, say Y and read the SCSI-HOWTO,
            the Disk-HOWTO and the Multi-Disk-HOWTO, available from
            <http://www.tldp.org/docs.html#howto>. This is NOT for SCSI
            CD-ROMs.

            To compile this driver as a module, choose M here and read
            <file:Documentation/scsi/scsi.txt>.
            The module will be called sd_mod.

            Do not compile this driver as a module if your root file system
            (the one containing the directory /) is located on a SCSI disk.
            In this case, do not compile the driver for your SCSI host adapter
            (below) as a module either.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using a SCSI hard disk.

            When booting without an initrd:
                
                https://www.dotslashlinux.com/2017/04/29/booting-the-linux-kernel-without-an-initrd-initramfs/

            you shouldn't compile this option as a module as it may result in an
            unbootable system.
```
<h3><&lowast;> SCSI CDROM support</h3>
```properties
Symbol:     CONFIG_BLK_DEV_SR

Help:       If you want to use a CD or DVD drive attached to your computer
            by SCSI, FireWire, USB or ATAPI, say Y and read the SCSI-HOWTO
            and the CDROM-HOWTO at <http://www.tldp.org/docs.html#howto>.

            Make sure to say Y or M to "ISO 9660 CD-ROM file system support".

            To compile this driver as a module, choose M here and read
            <file:Documentation/scsi/scsi.txt>.
            The module will be called sr_mod.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using a SCSI CD/DVD drive.
```
<h3>[&lowast;] Asynchronous SCSI scanning</h3>
```properties
Symbol:     CONFIG_SCSI_SCAN_ASYNC

Help:       The SCSI subsystem can probe for devices while the rest of the
            system continues booting, and even probe devices on different
            busses in parallel, leading to a significant speed-up.

            You can override this choice by specifying "scsi_mod.scan=sync"
            or async on the kernel's command line.

            Note that this setting also affects whether resuming from
            system suspend will be performed asynchronously.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kerenl
            as it speeds up boot time.

            In extrememly rare cases, this option may cause an incorrect naming
            of your root device. Although unlikely, if that was your case then
            you can safely exclude this option (you might experience some
            increase in boot time though).
```
<h3><&lowast;> Serial ATA and Parallel ATA drivers (libata)  ---></h3>
```properties
Symbol:     CONFIG_ATA

Help:       If you want to use an ATA hard disk, ATA tape drive, ATA CD-ROM or
            any other ATA device under Linux, say Y and make sure that you know
            the name of your ATA host adapter (the card inside your computer
            that "speaks" the ATA protocol, also called ATA controller),
            because you will be asked for it.

            NOTE: ATA enables basic SCSI support; ∗however∗,
            'SCSI disk support', 'SCSI tape support', or
            'SCSI CDROM support' may also be needed,
            depending on your hardware configuration.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a SCSI hard disk drive and a SCSI CD/DVD drive.
```
<h3>[&lowast;]   ATA ACPI Support</h3>
```properties
Symbol:     CONFIG_ATA_ACPI

Help:       This option adds support for ATA-related ACPI objects.
            These ACPI objects add the ability to retrieve taskfiles
            from the ACPI BIOS and write them to the disk controller.
            These objects may be related to performance, security,
            power management, or other areas.
            You can disable this at kernel boot time by using the
            option libata.noacpi=1

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_ATA as it may boost performance
            and power saving features of ATA devices.
```
<h3>[&lowast;]     SATA Zero Power Optical Disc Drive (ZPODD) support</h3>
```properties
Symbol:     CONFIG_SATA_ZPODD

Help:       This option adds support for SATA Zero Power Optical Disc
            Drive (ZPODD). It requires both the ODD and the platform
            support, and if enabled, will automatically power on/off the
            ODD when certain condition is satisfied. This does not impact
            end user's experience of the ODD, only power is saved when
            the ODD is not in use (i.e. no disc inside).

            If unsure, say N.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel if you
            have a SCSI CD/DVD drive as it'll help save energy when the drive
            isn't in use.
```
<h3><&lowast;>   AHCI SATA support</h3>
```properties
Symbol:     CONFIG_SATA_AHCI

Help:       This option enables support for AHCI Serial ATA.
            If unsure, say N.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it's basically the driver that'll be used for your SATA controller.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep ahci -B2

            should tell you whether you need this option or not.
```
<h3>[&lowast;] Network device support  ---></h3>
```properties
Symbol:     CONFIG_NETDEVICES

Help:       You can say N here if you don't intend to connect your Linux box to
            any other computer at all.

            You'll have to say Y if your computer contains a network card that
            you want to use under Linux. If you are going to run SLIP or PPP over
            telephone line or null modem cable you need say Y here. Connecting
            two machines with parallel ports using PLIP needs this, as well as
            AX.25/KISS for sending Internet traffic over amateur radio links.

            See also "The Linux Network Administrator's Guide" by Olaf Kirch and
            Terry Dawson. Available at <http://www.tldp.org/guides.html>.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            to access the network devices' drivers section.
```
<h3>[&lowast;]   Ethernet driver support  ---></h3>
```properties
Symbol:     CONFIG_ETHERNET

Help:       This section contains all the Ethernet device drivers.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel 
            if you wanted your ethernet adapter to work.
 
            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep Ethernet -A2

            should tell you whether you need this option or not.
```
<h3>[&lowast;]   Atheros devices</h3>
```properties
Symbol:     CONFIG_NET_VENDOR_ATHEROS

Help:       If you have a network (Ethernet) card belonging to this class, say Y.

            Note that the answer to this question doesn't directly affect the
            kernel: saying N will just cause the configurator to skip all
            the questions about Atheros devices. If you say Y, you will be asked
            for your specific card in the following questions.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using an atheros ethernet controller.
```
<h3><&lowast;>     Qualcomm Atheros AR816x/AR817x support</h3>
```properties
Symbol:     CONFIG_ALX

Help:       This driver supports the Qualcomm Atheros L1F ethernet adapter,
            i.e. the following chipsets:

            1969:1091 - AR8161 Gigabit Ethernet
            1969:1090 - AR8162 Fast Ethernet
            1969:10A1 - AR8171 Gigabit Ethernet
            1969:10A0 - AR8172 Fast Ethernet

            To compile this driver as a module, choose M here.  The module
            will be called alx.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros L1F ethernet adapter.
```
<h3>[&lowast;]   Wireless LAN  ---></h3>
```properties
Symbol:     CONFIG_WLAN

Help:       This section contains all the pre 802.11 and 802.11 wireless
            device drivers. For a complete list of drivers and documentation
            on them refer to the wireless wiki:

            http://wireless.kernel.org/en/users/Drivers 

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            you wanted your wireless network adapter to work.
            
            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep Wireless -A2

            should tell you whether you need this option or not.
```
<h3>[&lowast;]   Atheros/Qualcomm devices</h3>
```properties
Symbol:     CONFIG_WLAN_VENDOR_ATH

Help:       If you have a wireless card belonging to this class, say Y.

            Note that the answer to this question doesn't directly affect the
            kernel: saying N will just cause the configurator to skip all
            the questions about  cards. If you say Y, you will be asked for
            your specific card in the following questions.

            For more information and documentation on this module you can visit:

            http://wireless.kernel.org/en/users/Drivers/ath

            For information on all Atheros wireless drivers visit:

            http://wireless.kernel.org/en/users/Drivers/Atheros 

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros wireless network adapter.
```
<h3>[&lowast;]     Atheros bluetooth coexistence support</h3>
```properties
Symbol:     CONFIG_ATH9K_BTCOEX_SUPPORT

Help:       Say Y, if you want to use the ath9k/ath9k_htc radios together with
            Bluetooth modules in the same system.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using ath9k in order to get bluetooth working.
```
<h3><&lowast;>     Atheros 802.11n wireless cards support</h3>
```properties
Symbol:     CONFIG_ATH9K

Help:       This module adds support for wireless adapters based on
            Atheros IEEE 802.11n AR5008, AR9001 and AR9002 family
            of chipsets. For a specific list of supported external
            cards, laptops that already ship with these cards and
            APs that come with these cards refer to ath9k wiki
            products page:

            http://wireless.kernel.org/en/users/Drivers/ath9k/products

            If you choose to build a module, it'll be called ath9k.

Type:       tristate

Choice:     <∗>

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros 802.11n wireless network adapter.
```
<h3>[&lowast;]       Atheros ath9k PCI/PCIe bus support</h3>
```properties
Symbol:     CONFIG_ATH9K_PCI

Help:       This option enables the PCI bus support in ath9k.

            Say Y, if you have a compatible PCI/PCIe wireless card.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros PCI/PCIe compatible wireless network card.
```
<h3>[&lowast;]       Atheros ath9k rfkill support</h3>
```properties
Symbol:     CONFIG_ATH9K_RFKILL

Help:       Say Y to have ath9k poll the RF-Kill GPIO every couple of
            seconds. Turn off to save power, but enable it if you have
            a platform that can toggle the RF-Kill GPIO.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            your Qualcomm Atheros wireless network adapter has a RF-Kill switch, as
            it'll be necessary on some systems to get Wi-Fi working (since some
            wireless cards may be blocked by the RF-Kill switch and you may have to
            unblock them).
```
<h3>[&lowast;]       Atheros ath9k support for PC OEM cards</h3>
```properties
Symbol:     CONFIG_ATH9K_PCOEM

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using ath9k as it's required on some systems for the detection
            of the wireless network adapter.
```
<h3>Input device support  ---></h3>
<h3>-&lowast;- Generic input layer (needed for keyboard, mouse, ...)</h3>
```properties
Symbol:     CONFIG_INPUT

Help:       Say Y here if you have any input device (mouse, keyboard, tablet,
            joystick, steering wheel ...) connected to your system and want
            it to be available to applications. This includes standard PS/2
            keyboard and mouse.

            Say N here if you have a headless (no monitor, no keyboard) system.

            More information is available: <file:Documentation/input/input.txt>

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called input.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            if you want to use your mouse and keyboard.
```
<h3>-&lowast;-   Sparse keymap support library</h3>
```properties
Symbol:     CONFIG_INPUT_SPARSEKMAP

Help:       Say Y here if you are using a driver for an input
            device that uses sparse keymap. This option is only
            useful for out-of-tree drivers since in-tree drivers
            select it automatically.

            If unsure, say N.

            To compile this driver as a module, choose M here: the
            module will be called sparse-keymap.

Type:       tristate

Choice:     built-in -∗-

Reason:     You can safely exclude this option unless it was forcibly included
            by other options related to out-of-tree drivers.
```
<h3><&lowast;>   Mouse interface</h3>
```properties
Symbol:     CONFIG_INPUT_MOUSEDEV

Help:       Say Y here if you want your mouse to be accessible as char devices
            13:32+ - /dev/input/mouseX and 13:63 - /dev/input/mice as an
            emulated IntelliMouse Explorer PS/2 mouse. That way, all user space
            programs (including SVGAlib, GPM and X) will be able to use your
            mouse.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called mousedev.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel in
            order for your mouse to work.
```
<h3>(1024)  Horizontal screen resolution</h3>
```properties
Symbol:     CONFIG_INPUT_MOUSEDEV_SCREEN_X

Help:       If you're using a digitizer, or a graphic tablet, and want to use
            it as a mouse then the mousedev driver needs to know the X window
            screen resolution you are using to correctly scale the data. If
            you're not using a digitizer, this value is ignored.

Type:       integer

Choice:     (1024) default

Reason:     You can safely leave the value of this option to its default value
            of (1024) if you're not using a digitizer or tablet pointing devices.
```
<h3>(768)   Vertical screen resolution</h3>
```properties
Symbol:     CONFIG_INPUT_MOUSEDEV_SCREEN_Y

Help:       If you're using a digitizer, or a graphic tablet, and want to use
            it as a mouse then the mousedev driver needs to know the X window
            screen resolution you are using to correctly scale the data. If
            you're not using a digitizer, this value is ignored.

Type:       integer

Choice:     (768) default

Reason:     You can safely leave the value of this option to its default value
            of (768) if you're not using a digitizer or tablet pointing devices.
```
<h3><&lowast;>   Event interface</h3>
```properties
Symbol:     CONFIG_INPUT_EVDEV

Help:       Say Y here if you want your input device events be accessible
            under char device 13:64+ - /dev/input/eventX in a generic way.

            To compile this driver as a module, choose M here: the
            module will be called evdev.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by Xorg input drivers (evdev, libinput ...etc).
```
<h3>[&lowast;]   Keyboards  ---></h3>
```properties
Symbol:     CONFIG_INPUT_KEYBOARD

Help:       Say Y here, and a list of supported keyboards will be displayed.
            This option doesn't affect the kernel.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your keyboard to work.
```
<h3><&lowast;>   AT keyboard</h3>
```properties
Symbol:     CONFIG_KEYBOARD_ATKBD

Help:       Say Y here if you want to use a standard AT or PS/2 keyboard. Usually
            you'll need this, unless you have a different type keyboard (USB, ADB
            or other). This also works for AT and PS/2 keyboards connected over a
            PS/2 to serial converter.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called atkbd.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel as
            in order for your AT or PS/2 keyboard to work.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep keyboard

            should tell you whether you need this option or not.
```
<h3>[&lowast;]   Mice  ---></h3>
```properties
Symbol:     CONFIG_INPUT_MOUSE

Help:       Say Y here, and a list of supported mice will be displayed.
            This option doesn't affect the kernel.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your mouse and touchpad to work.
```
<h3><&lowast;>   PS/2 mouse</h3>
```properties
Symbol:     CONFIG_MOUSE_PS2

Help:       Say Y here if you have a PS/2 mouse connected to your system. This
            includes the standard 2 or 3-button PS/2 mouse, as well as PS/2
            mice with wheels and extra buttons, Microsoft, Logitech or Genius
            compatible.

            Synaptics, ALPS or Elantech TouchPad users might be interested
            in a specialized Xorg/XFree86 driver at:
                  <http://w1.894.telia.com/~u89404340/touchpad/index.html>
            and a new version of GPM at:
                  <http://www.geocities.com/dt_or/gpm/gpm.html>
                  <http://xorg.freedesktop.org/archive/individual/driver/>
            to take advantage of the advanced features of the touchpad.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called psmouse.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for your PS/2 mouse and PS/2 touchpad to work.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep psmouse

            should tell you whether you need this option or not.
```
<h3>[&lowast;]     Synaptics PS/2 mouse protocol extension</h3>
```properties
Symbol:     CONFIG_MOUSE_PS2_SYNAPTICS

Help:       Say Y here if you have a Synaptics PS/2 TouchPad connected to
            your system.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics Touchpad to be enumerated through
            PS/2.
```
<h3>[&lowast;]     Synaptics PS/2 SMbus companion</h3>
```properties
Symbol:     CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS

Help:       Say Y here if you have a Synaptics RMI4 touchpad connected to
            to an SMBus, but enumerated through PS/2.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics RMI4 SMBus touchpad to work properly.

            Keep in mind that using this option alone without CONFIG_MOUSE_PS2_SYNPATICS
            will result in a terrible touchpad experience, therefore you have
            to include CONFIG_MOUSE_PS2_SYNAPTICS as well.

            This option is new, and it was included according to dmesg suggestion:
            
            "Your touchpad (PNP: TOS1150 TOS0310 PNP0f13) says it can support a different bus. If i2c-hid and hid-rmi are not used, you might want to try setting psmouse.synaptics_intertouch to 1 and report this to linux-input@vger.kernel.org"
```
<h3>-&lowast;-   Synaptics RMI4 bus support</h3>
```properties
Symbol:     CONFIG_RMI4_CORE

Help:       Say Y here if you want to support the Synaptics RMI4 bus.  This is
            required for all RMI4 device support.

            If unsure, say Y.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics RMI4 SMBus touchpad to work properly.
```
<h3><&lowast;>     RMI4 SMB Support</h3>
```properties
Symbol:     CONFIG_RMI4_SMB

Help:       Say Y here if you want to support RMI4 devices connected to an SMB
            bus.

            If unsure, say N.

            To compile this driver as a module, choose M here: the module will be
            called rmi_smbus.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics RMI4 SMBus touchpad to work properly.
```
<h3>-&lowast;-     RMI4 Function 03 (PS2 Guest)</h3>
```properties
Symbol:     CONFIG_RMI4_F03

Help:       Say Y here if you want to add support for RMI4 function 03.

            Function 03 provides PS2 guest support for RMI4 devices. This
            includes support for TrackPoints on TouchPads.

Type:       boolean

Choice:     built-in -∗-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>-&lowast;-     RMI4 Function 11 (2D pointing)</h3>
```properties
Symbol:     CONFIG_RMI4_F11

Help:       Say Y here if you want to add support for RMI4 function 11.

            Function 11 provides 2D multifinger pointing for touchscreens and
            touchpads. For sensors that support relative pointing, F11 also
            provides mouse input.

Type:       boolean

Choice:     built-in -∗-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>-&lowast;-     RMI4 Function 12 (2D pointing)</h3>
```properties
Symbol:     CONFIG_RMI4_F12

Help:       Say Y here if you want to add support for RMI4 function 12.

            Function 12 provides 2D multifinger pointing for touchscreens and
            touchpads. For sensors that support relative pointing, F12 also
            provides mouse input.

Type:       boolean

Choice:     built-in -∗-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>-&lowast;-     RMI4 Function 30 (GPIO LED)</h3>
```properties
Symbol:     CONFIG_RMI4_F30

Help:       Say Y here if you want to add support for RMI4 function 30.

            Function 30 provides GPIO and LED support for RMI4 devices. This
            includes support for buttons on TouchPads and ClickPads.

Type:       boolean

Choice:     built-in -∗-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>Hardware I/O ports  ---></h3>
<h3>-&lowast;- Serial I/O support</h3>
```properties
Symbol:     CONFIG_SERIO

Help:       Say Yes here if you have any input device that uses serial I/O to
            communicate with the system. This includes the
                          ∗ standard AT keyboard and PS/2 mouse ∗
            as well as serial mice, Sun keyboards, some joysticks and 6dof
            devices and more.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called serio.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you included this option in your kernel
            (that is if it weren't already forcibly included by several important
            options).
```
<h3>-&lowast;- i8042 PC Keyboard controller</h3>
```properties
Symbol:     CONFIG_SERIO_I8042

Help:       i8042 is the chip over which the standard AT keyboard and PS/2
            mouse are connected to the computer. If you use these devices,
            you'll need to say Y here.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called i8042.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you included this option in your kernel
            (that is if it weren't already forcibly included by several important
            options).
```
<h3>-&lowast;- PS/2 driver library</h3>
```properties
Symbol:     CONFIG_SERIO_LIBPS2

Help:       Say Y here if you are using a driver for device connected
            to a PS/2 port, such as PS/2 mouse or standard AT keyboard.

            To compile this driver as a module, choose M here: the
            module will be called libps2.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you included this option in your kernel
            (that is if it weren't already forcibly included by several important
            options).
```
<h3>< > Raw access to serio ports</h3>
```properties
Symbol:     CONFIG_SERIO_RAW

Help:       Say Y here if you want to have raw access to serio ports, such as
            AUX ports on i8042 keyboard controller. Each serio port that is
            bound to this driver will be accessible via a char device with
            major 10 and dynamically allocated minor. The driver will try
            allocating minor 1 (that historically corresponds to /dev/psaux)
            first. To bind this driver to a serio port use sysfs interface:

                echo -n "serio_raw" > /sys/bus/serio/devices/serioX/drvctl

            To compile this driver as a module, choose M here: the
            module will be called serio_raw.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if your Synaptics PS/2
            or RMI4 SMBus Touchpad is already working.

            In some cases including this option might fix an undetectable
            Synpatics touchpad.
```
<h3>Character devices  ---></h3>
<h3>[&lowast;] Enable TTY</h3>
```properties
Symbol:     CONFIG_TTY

Help:       Allows you to remove TTY support which can save space, and
            blocks features that require TTY from inclusion in the kernel.
            TTY is required for any text terminals or serial port
            communication. Most users should leave this enabled.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for text terminals to work.
```
<h3>[&lowast;]   Virtual terminal</h3>
```properties
Symbol:     CONFIG_VT

Help:       If you say Y here, you will get support for terminal devices with
            display and keyboard devices. These are called "virtual" because you
            can run several virtual terminals (also called virtual consoles) on
            one physical terminal. This is rather useful, for example one
            virtual terminal can collect system messages and warnings, another
            one can be used for a text-mode user session, and a third could run
            an X session, all in parallel. Switching between virtual terminals
            is done with certain key combinations, usually Alt-<function key>.

            The setterm command ("man setterm") can be used to change the
            properties (such as colors or beeping) of a virtual terminal. The
            man page console_codes(4) ("man console_codes") contains the special
            character sequences that can be used to change those properties
            directly. The fonts used on virtual terminals can be changed with
            the setfont ("man setfont") command and the key bindings are defined
            with the loadkeys ("man loadkeys") command.

            You need at least one virtual terminal device in order to make use
            of your keyboard and monitor. Therefore, only people configuring an
            embedded system would want to say N here in order to save some
            memory; the only way to log into such a system is then via a serial
            or network connection.

            If unsure, say Y, or else you won't be able to do much with your new
            shiny Linux system :-)

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for virtual terminals to work.
```
<h3>[&lowast;]     Support for console on virtual terminal</h3>
```properties
Symbol:     CONFIG_VT_CONSOLE

Help:       The system console is the device which receives all kernel messages
            and warnings and which allows logins in single user mode. If you
            answer Y here, a virtual terminal (the device used to interact with
            a physical terminal) can be used as system console. This is the most
            common mode of operations, so you should say Y here unless you want
            the kernel messages be output only to a serial port (in which case
            you should say Y to "Console on serial port", below).

            If you do say Y here, by default the currently visible virtual
            terminal (/dev/tty0) will be used as system console. You can change
            that with a kernel command line option such as "console=tty3" which
            would use the third virtual terminal as system console. (Try "man
            bootparam" or see the documentation of your boot loader (lilo or
            loadlin) about how to pass options to the kernel at boot time.)

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for virtual terminals to work as system consoles as well.
```
<h3>-&lowast;-     Support for binding and unbinding console drivers</h3>
```properties
Symbol:     CONFIG_VT_HW_CONSOLE_BINDING

Help:       The virtual terminal is the device that interacts with the physical
            terminal through console drivers. On these systems, at least one
            console driver is loaded. In other configurations, additional console
            drivers may be enabled, such as the framebuffer console. If more than
            1 console driver is enabled, setting this to 'y' will allow you to
            select the console driver that will serve as the backend for the
            virtual terminals.

            See <file:Documentation/console/console.txt> for more
            information. For framebuffer console users, please refer to
            <file:Documentation/fb/fbcon.txt>.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_VT (that is if it isn't already 
            forcibly included by CONFIG_VT, CONFIG_FB and CONFIG_HAS_IOMEM).
```
<h3>[&lowast;]   Unix98 PTY support</h3>
```properties
Symbol:     CONFIG_UNIX98_PTYS

Help:       A pseudo terminal (PTY) is a software device consisting of two
            halves: a master and a slave. The slave device behaves identical to
            a physical terminal; the master device is used by a process to
            read data from and write data to the slave, thereby emulating a
            terminal. Typical programs for the master side are telnet servers
            and xterms.

            Linux has traditionally used the BSD-like names /dev/ptyxx for
            masters and /dev/ttyxx for slaves of pseudo terminals. This scheme
            has a number of problems. The GNU C library glibc 2.1 and later,
            however, supports the Unix98 naming standard: in order to acquire a
            pseudo terminal, a process opens /dev/ptmx; the number of the pseudo
            terminal is then made available to the process and the pseudo
            terminal slave can be accessed as /dev/pts/<number>. What was
            traditionally /dev/ttyp2 will then be /dev/pts/2, for example.

            All modern Linux systems use the Unix98 ptys.  Say Y unless
            you're on an embedded system and want to conserve memory.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by telnet servers, xterms and SSH.
```
<h3><&lowast;> Hardware Random Number Generator Core support  ---></h3>
```properties
Symbol:     CONFIG_HW_RANDOM

Help:       Hardware Random Number Generator Core infrastructure.

            To compile this driver as a module, choose M here: the
            module will be called rng-core.  This provides a device
            that's usually called /dev/hwrng, and which exposes one
            of possibly several hardware random number generators.

            These hardware random number generators do not feed directly
            into the kernel's random number generator.  That is usually
            handled by the "rngd" daemon.  Documentation/hw_random.txt
            has more information.

            If unsure, say Y.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports the RDRAND instruction.
            
            If you've followed the guide above, then a simple:

                cat cpuinfo.txt | grep rdrand

            should tell you whether you need this option or not.
```
<h3><&lowast;>   Intel HW Random Number Generator support (NEW)</h3>
```properties
Symbol:     CONFIG_HW_RANDOM_INTEL

Help:       This driver provides kernel-side support for the Random Number
            Generator hardware found on Intel i8xx-based motherboards.

            To compile this driver as a module, choose M here: the
            module will be called intel-rng.

            If unsure, say Y.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports the RDRAND instruction.
            
            If you've followed the guide above, then a simple:

                cat cpuinfo.txt | grep rdrand

            should tell you whether you need this option or not.
```
<h3>I2C support  ---></h3>
<h3>-&lowast;- I2C support</h3>
```properties
Symbol:     CONFIG_I2C

Help:       I2C (pronounce: I-squared-C) is a slow serial bus protocol used in
            many micro controller applications and developed by Philips.  SMBus,
            or System Management Bus is a subset of the I2C protocol.  More
            information is contained in the directory <file:Documentation/i2c/>,
            especially in the file called "summary" there.

            Both I2C and SMBus are supported here. You will need this for
            hardware sensors support, and also for Video For Linux support.

            If you want I2C support, you should say Y here and also to the
            specific driver for your bus adapter(s) below.

            This I2C support can also be built as a module.  If so, the module
            will be called i2c-core.

Type:       tristate

Choice:     built-in -∗-

Reason:     If you've followed the guide above, then a simple:

                cat lsmod.txt | grep i2c

            and:

                cat lspcikk.txt | grep i2c -B3

            should tell you whether you need this option or not.
```
<h3><&lowast;>   I2C device interface</h3>
```properties
Symbol:     CONFIG_I2C_CHARDEV

Help:       Say Y here to use i2c-∗ device files, usually found in the /dev
            directory on your system.  They make it possible to have user-space
            programs use the I2C bus.  Information on how to do this is
            contained in the file <file:Documentation/i2c/dev-interface>.

            This support is also available as a module.  If so, the module
            will be called i2c-dev.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_I2C (it's also recommended by the
            Gentoo Wiki).
```
<h3>-&lowast;-   I2C bus multiplexing support</h3>
```properties
Symbol:     CONFIG_I2C_MUX

Help:       Say Y here if you want the I2C core to support the ability to
            handle multiplexed I2C bus topologies, by presenting each
            multiplexed segment as a I2C adapter.

            This support is also available as a module.  If so, the module
            will be called i2c-mux.

Type:       tristate

Choice:     built-in -∗-

Reason:     You can safely exclude this option unless it was forcibly included
            by some other important options.
```
<h3>[&lowast;]   Autoselect pertinent helper modules</h3>
```properties
Symbol:     CONFIG_I2C_HELPER_AUTO

Help:       Some I2C bus drivers require so-called "I2C algorithm" modules
            to work. These are basically software-only abstractions of generic
            I2C interfaces. This option will autoselect them so that you don't
            have to care.

            Unselect this only if you need to enable additional helper
            modules, for example for use with external I2C bus drivers.

            In doubt, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_I2C (it's also recommended by the
            Gentoo Wiki).
```
<h3>I2C Hardware Bus support  ---></h3>
<h3><&lowast;> Intel 82801 (ICH/PCH)</h3>
```properties
Symbol:     CONFIG_I2C_I801

Help:       If you say yes to this option, support will be included for the Intel
            801 family of mainboard I2C interfaces.  Specifically, the following
            versions of the chipset are supported:
              82801AA
              82801AB
              82801BA
              82801CA/CAM
              82801DB
              82801EB/ER (ICH5/ICH5R)
              6300ESB
              ICH6
              ICH7
              ESB2
              ICH8
              ICH9
              EP80579 (Tolapai)
              ICH10
              5/3400 Series (PCH)
              6 Series (PCH)
              Patsburg (PCH)
              DH89xxCC (PCH)
              Panther Point (PCH)
              Lynx Point (PCH)
              Lynx Point-LP (PCH)
              Avoton (SOC)
              Wellsburg (PCH)
              Coleto Creek (PCH)
              Wildcat Point (PCH)
              Wildcat Point-LP (PCH)
              BayTrail (SOC)
              Sunrise Point-H (PCH)
              Sunrise Point-LP (PCH)
              DNV (SOC)
              Broxton (SOC)
              Lewisburg (PCH)
              Gemini Lake (SOC)

            This driver can also be built as a module.  If so, the module
            will be called i2c-i801.

Type:       tristate

Choice:     built-in <∗>

Reason:     If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep i2c_i801 -B3

            should tell you whether you need this option or not.
```
<h3>-&lowast;- Power supply class support  ---></h3>
```properties
Symbol:     CONFIG_POWER_SUPPLY

Help:       Say Y here to enable power supply class support. This allows
            power supply (batteries, AC, USB) monitoring by userspace
            via sysfs and uevent (if available) and/or APM kernel interface
            (if selected below).

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_ACPI,
            CONFIG_ACPI_AC, CONFIG_X86, CONFIG_INPUT, CONFIG_RFKILL and a lot
            of important options).
```
<h3><&lowast;> Hardware Monitoring support  ---></h3>
```properties
Symbol:     CONFIG_HWMON

Help:       Hardware monitoring devices let you monitor the hardware health
            of a system. Most modern motherboards include such a device. It
            can include temperature sensors, voltage sensors, fan speed
            sensors and various additional features such as the ability to
            control the speed of the fans.  If you want this support you
            should say Y here and also to the specific driver(s) for your
            sensors chip(s) below.

            To find out which specific driver(s) you need, use the
            sensors-detect script from the lm_sensors package.  Read
            <file:Documentation/hwmon/userspace-tools> for details.

            This support can also be built as a module.  If so, the module
            will be called hwmon.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by sensors found on almost all modern motherboards.
```
<h3><&lowast;>   Intel Core/Core2/Atom temperature sensor</h3>
```properties
Symbol:     CONFIG_SENSORS_CORETEMP

Help:       If you say yes here you get support for the temperature
            sensor inside your CPU. Most of the family 6 CPUs
            are supported. Check Documentation/hwmon/coretemp for details.

Type:       tristate

Choice:     built-in <∗>

Reason:     If you've followed the guide above, then a simple:

                cat lsmod.txt | grep coretemp

            and:

                cat sensors.txt | grep coretemp

            should tell you whether you need this option or not.

            It's also recommended by the Gentoo Wiki.
```
<h3>-&lowast;- Generic Thermal sysfs driver  ---></h3>
```properties
Symbol:     CONFIG_THERMAL

Help:       Generic Thermal Sysfs driver offers a generic mechanism for
            thermal management. Usually it's made up of one or more thermal
            zone and cooling device.
            Each thermal zone contains its own temperature, trip points,
            cooling devices.
            All platforms with ACPI thermal support can use this driver.
            If you want this support, you should say Y or M here.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_X86, CONFIG_ACPI,
            CONFIG_ACPI_VIDEO, CONFIG_INPUT, CONFIG_PCI, CONFIG_DRM and a lot of 
            important options).
```
<h3>(0)   Emergency poweroff delay in milli-seconds</h3>
```properties
Symbol:     CONFIG_THERMAL_EMERGENCY_POWEROFF_DELAY_MS

Help:       Thermal subsystem will issue a graceful shutdown when
            critical temperatures are reached using orderly_poweroff(). In
            case of failure of an orderly_poweroff(), the thermal emergency
            poweroff kicks in after a delay has elapsed and shuts down the system.
            This config is number of milliseconds to delay before emergency
            poweroff kicks in. Similarly to the critical trip point,
            the delay should be carefully profiled so as to give adequate
            time for orderly_poweroff() to finish on regular execution.
            If set to 0 emergency poweroff will not be supported.

            In doubt, leave as 0.

Type:       integer

Choice:     (0) default

Reason:     It's highly recommended that you leave the value of this option set to
            the default value of (0).
```
<h3>Default Thermal governor (step_wise)  ---></h3>
```properties
Help:       This option sets which thermal governor shall be loaded at
            startup. If in doubt, select 'step_wise'.
```
<h3>(X) step_wise</h3>
```properties
Symbol:     CONFIG_THERMAL_DEFAULT_GOV_STEP_WISE

Help:       Use the step_wise governor as default. This throttles the
            devices one step at a time.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            as step_wise is the best thermal governor.
```
<h3>-&lowast;-   Step_wise thermal governor</h3>
```properties
Symbol:     CONFIG_THERMAL_GOV_STEP_WISE

Help:       Enable this to manage platform thermals using a simple linear
            governor.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            as step_wise is the best thermal governor.
```
<h3><&lowast;> Multimedia support  ---></h3>
```none
Symbol:     CONFIG_MEDIA_SUPPORT

Help:       If you want to use Webcams, Video grabber devices and/or TV devices
            enable this option and other options below.
            Additional info and docs are available on the web at
            <https://linuxtv.org>

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for your webcam device to work.

            It's also recommended by the Gentoo wiki.
```
<h3>[&lowast;]   Cameras/video grabbers support</h3>
```none
Symbol:     CONFIG_MEDIA_CAMERA_SUPPORT

Help:       Enable support for webcams and video grabbers.

            Say Y when you have a webcam or a video capture grabber board.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your webcam device to work.

            It's also recommended by the Gentoo wiki.
```
<h3>[&lowast;]   Media USB Adapters  ---></h3>
```none
Symbol:     CONFIG_MEDIA_USB_SUPPORT

Help:       Enable media drivers for USB bus.
            If you have such devices, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your USB-bus webcam device to work.

            If you've followed the guide above, then a simple:

                cat lsusbv.txt | grep Camera

            should tell you whether you need this option or not.
```
<h3><&lowast;>   USB Video Class (UVC)</h3>
```none
Symbol:     CONFIG_USB_VIDEO_CLASS

Help:       Support for the USB Video Class (UVC).  Currently only video
            input devices, such as webcams, are supported.

            For more information see: <http://linux-uvc.berlios.de/>

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for your webcam device to work.

            If you've followed the guide above, then a simple:

                cat lsusbv.txt | grep UVC

            should tell you whether you need this option or not.
```
<h3>[&lowast;]     UVC input events device support (NEW)</h3>
```none
Symbol:     CONFIG_USB_VIDEO_CLASS_INPUT_EVDEV

Help:       This option makes USB Video Class devices register an input device
            to report button events.

            If you are in doubt, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your webcam device to work.

            If you've followed the guide above, then a simple:

                cat lsusbv.txt | grep UVC

            should tell you whether you need this option or not.
            
            It's also recommended by the Gentoo wiki.
```
<h3>[&lowast;]   Autoselect ancillary drivers (tuners, sensors, i2c, spi, frontends) (NEW)</h3>
```none
Symbol:     CONFIG_MEDIA_SUBDRV_AUTOSELECT

Help:       By default, a media driver auto-selects all possible ancillary
            devices such as tuners, sensors, video encoders/decoders and
            frontends, that are used by any of the supported devices.

            This is generally the right thing to do, except when there
            are strict constraints with regards to the kernel size,
            like on embedded systems.

            Use this option with care, as deselecting ancillary drivers which
            are, in fact, necessary will result in the lack of the needed
            functionality for your device (it may not tune or may not have
            the needed demodulators).

            If unsure say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_MEDIA_SUPPORT.

            It's also recommended by the Gentoo wiki.
```
<h3>Graphics support  ---></h3>
You may want to check <a href="https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/" target="_blank">Setting up Bumblebee on Gentoo Linux | DOTSLASHLINUX</a>.
<h3><&lowast;> /dev/agpgart (AGP Support)  ---></h3>
```properties
Symbol:     CONFIG_AGP

Help:       AGP (Accelerated Graphics Port) is a bus system mainly used to
            connect graphics cards to the rest of the system.

            If you have an AGP system and you say Y here, it will be possible to
            use the AGP features of your 3D rendering video card. This code acts
            as a sort of "AGP driver" for the motherboard's chipset.

            If you need more texture memory than you can get with the AGP GART
            (theoretically up to 256 MB, but in practice usually 64 or 128 MB
            due to kernel allocation issues), you could use PCI accesses
            and have up to a couple gigs of texture space.

            Note that this is the only means to have X/GLX use
            write-combining with MTRR support on the AGP bus. Without it, OpenGL
            direct rendering will be a lot slower but still faster than PIO.

            To compile this driver as a module, choose M here: the
            module will be called agpgart.

            You should say Y here if you want to use GLX or DRI.

            If unsure, say N.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3><&lowast;>   Intel 440LX/BX/GX, I8xx and E7x05 chipset support</h3>
```properties
Symbol:     CONFIG_AGP_INTEL

Help:       This option gives you AGP support for the GLX component of X
            on Intel 440LX/BX/GX, 815, 820, 830, 840, 845, 850, 860, 875,
            E7205 and E7505 chipsets and full support for the 810, 815, 830M,
            845G, 852GM, 855GM, 865G and I915 integrated graphics chipsets.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>[&lowast;] VGA Arbitration</h3>
```properties
Symbol:     CONFIG_VGA_ARB

Help:       Some "legacy" VGA devices implemented on PCI typically have the same
            hard-decoded addresses as they did on ISA. When multiple PCI devices
            are accessed at same time they need some kind of coordination. Please
            see Documentation/vgaarbiter.txt for more details. Select this to
            enable VGA arbiter.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>(2)   Maximum number of GPUs</h3>
```properties
Symbol:     CONFIG_VGA_ARB_MAX_GPUS

Help:       Reserves space in the kernel to maintain resource locking for
            multiple GPUS.  The overhead for each GPU is very small.

Type:       integer

Choice:     (2) custom

Reason:     It's highly recommended that you set the value of this option to (2)
            as the default value of (16) is an overkill for a system with 2 GPUs
            (an iGPU and a dGPU) which is the case on almost all optimus based
            laptops.

            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3><&lowast;> Direct Rendering Manager (XFree86 4.1.0 and higher DRI support)  ---></h3>
```properties
Symbol:     CONFIG_DRM

Help:       Kernel-level support for the Direct Rendering Infrastructure (DRI)
            introduced in XFree86 4.0. If you say Y here, you need to select
            the module that's right for your graphics card from the list below.
            These modules provide support for synchronization, security, and
            DMA transfers. Please see <http://dri.sourceforge.net/> for more
            details.  You should also select and configure AGP
            (/dev/agpgart) support if it is available for your platform.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>[&lowast;]   Enable legacy fbdev support for your modesetting driver</h3>
```properties
Symbol:     CONFIG_DRM_FBDEV_EMULATION

Help:       Choose this option if you have a need for the legacy fbdev
            support. Note that this support also provides the linux console
            support on top of your modesetting driver.

            If in doubt, say "Y".

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>(300)   Overallocation of the fbdev buffer</h3>
```properties
Symbol:     CONFIG_DRM_FBDEV_OVERALLOC

Help:       Defines the fbdev buffer overallocation in percent. Default
            is 100. Typical values for double buffering will be 200,
            triple buffering 300.

Type:       integer

Choice:     (300) custom

Reason:     It's highly recommended that you set the value of this option to (300)
            to enable triple buffering.

            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3><&lowast;> Intel 8xx/9xx/G3x/G4x/HD Graphics</h3>
```properties
Symbol:     CONFIG_DRM_I915

Help:       Choose this option if you have a system that has "Intel Graphics
            Media Accelerator" or "HD Graphics" integrated graphics,
            including 830M, 845G, 852GM, 855GM, 865G, 915G, 945G, 965G,
            G35, G41, G43, G45 chipsets and Celeron, Pentium, Core i3,
            Core i5, Core i7 as well as Atom CPUs with integrated graphics.

            This driver is used by the Intel driver in X.org 6.8 and
            XFree86 4.4 and above. It replaces the older i830 module that
            supported a subset of the hardware in older X.org releases.

            Note that the older i810/i815 chipsets require the use of the
            i810 driver instead, and the Atom z5xx series has an entirely
            different implementation.

            If "M" is selected, the module will be called i915.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>[&lowast;]   Always enable userptr support</h3>
```properties
Symbol:     CONFIG_DRM_I915_USERPTR

Help:       This option selects CONFIG_MMU_NOTIFIER if it isn't already
            selected to enabled full userptr support.

            If in doubt, say "Y".

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>Frame buffer Devices  ---></h3>
<h3>-&lowast;- Support for frame buffer devices  ---></h3>
```properties
Symbol:     CONFIG_FB

Help:       The frame buffer device provides an abstraction for the graphics
            hardware. It represents the frame buffer of some video hardware and
            allows application software to access the graphics hardware through
            a well-defined interface, so the software doesn't need to know
            anything about the low-level (hardware register) stuff.

            Frame buffer devices work identically across the different
            architectures supported by Linux and make the implementation of
            application programs easier and more portable; at this point, an X
            server exists which uses the frame buffer device exclusively.
            On several non-X86 architectures, the frame buffer device is the
            only way to use the graphics hardware.

            The device is accessed through special device nodes, usually located
            in the /dev directory, i.e. /dev/fb∗.

            You need an utility program called fbset to make full use of frame
            buffer devices. Please read <file:Documentation/fb/framebuffer.txt>
            and the Framebuffer-HOWTO at
            <http://www.munted.org.uk/programming/Framebuffer-HOWTO-1.3.html> for more
            information.

            Say Y here and to the driver for your graphics board below if you
            are compiling a kernel for a non-x86 architecture.

            If you are compiling for the x86 architecture, you can say Y if you
            want to play with it, but it is not essential. Please note that
            running graphical applications that directly touch the hardware
            (e.g. an accelerated X server) and that are not frame buffer
            device-aware may cause unexpected results. If unsure, say N.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_X86, CONFIG_PCI,
            CONFIG_DRM, CONFIG_MMU and CONFIG_HAS_IOMEM).
```
<h3>-&lowast;- Backlight & LCD device support  ---></h3>
```properties
Symbol:     CONFIG_BACKLIGH_LCD_SUPPORT

Help:       Enable this to be able to choose the drivers for controlling the
            backlight and the LCD panel on some platforms, for example on PDAs.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_X86, CONFIG_PCI,
            CONFIG_ACPI, CONFIG_DRM, CONFIG_MMU and CONFIG_HAS_IOMEM).
```
<h3>-&lowast;-   Lowlevel Backlight controls</h3>
```properties
Symbol:     CONFIG_BACKLIGHT_CLASS_DEVICE

Help:       This framework adds support for low-level control of the LCD
            backlight. This includes support for brightness and power.

            To have support for your specific LCD panel you will have to
            select the proper drivers which depend on this option.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_X86, CONFIG_PCI,
            CONFIG_ACPI, CONFIG_DRM, CONFIG_MMU and CONFIG_HAS_IOMEM).
```
<h3>Console display driver support  ---></h3>
<h3>[&lowast;] VGA text console</h3>
```properties
Symbol:     CONFIG_VGA_CONSOLE

Help:       Saying Y here will allow you to use Linux in text mode through a
            display that complies with the generic VGA standard. Virtually
            everyone wants that.

            The program SVGATextMode can be used to utilize SVGA video cards to
            their full potential in text mode. Download it from
            <ftp://ibiblio.org/pub/Linux/utils/console/>.

            Say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>(80) Initial number of console screen columns</h3>
```properties
Symbol:     CONFIG_DUMMY_CONSOLE_COLUMNS

Help:       On PA-RISC, the default value is 160, which should fit a 1280x1024
            monitor.
            Select 80 if you use a 640x480 resolution by default.

Type:       integer

Choice:     (80) default

Reason:     You can safely leave the value of this option set to its default value
            of (80) as it's for dummy consoles.
```
<h3>(25) Initial number of console screen rows</h3>
```properties
Symbol:     CONFIG_DUMMY_CONSOLE_ROWS

Help:       On PA-RISC, the default value is 64, which should fit a 1280x1024
            monitor.
            Select 25 if you use a 640x480 resolution by default.

Type:       integer

Choice:     (25) default

Reason:     You can safely leave the value of this option set to its default value
            of (25) as it's for dummy consoles.
```
<h3><&lowast;> Framebuffer Console support</h3>
```properties
Symbol:     CONFIG_FRAMEBUFFER_CONSOLE

Help:       Low-level framebuffer-based console driver.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3>-&lowast;-   Map the console to the primary display device</h3>
```properties
Symbol:     CONFIG_FRAMEBUFFER_CONSOLE_DETECT_PRIMARY

Help:       If this option is selected, the framebuffer console will
            automatically select the primary display device (if the architecture
            supports this feature).  Otherwise, the framebuffer console will
            always select the first framebuffer driver that is loaded. The latter
            is the default behavior.

            You can always override the automatic selection of the primary device
            by using the fbcon=map: boot option.

            If unsure, select n.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_HAS_IOMEM
            and CONFIG_FRAMEBUFFER_CONSOLE).
```
<h3><&lowast;> Sound card support  ---></h3>
```properties
Symbol:     CONFIG_SOUND

Help:       If you have a sound card in your computer, i.e. if it can say more
            than an occasional beep, say Y.  Be sure to have all the information
            about your sound card and its configuration down (I/O port,
            interrupt and DMA channel), because you will be asked for it.

            You want to read the Sound-HOWTO, available from
            <http://www.tldp.org/docs.html#howto>. General information about
            the modular sound system is contained in the files
            <file:Documentation/sound/oss/Introduction>.  The file
            <file:Documentation/sound/oss/README.OSS> contains some slightly
            outdated but still useful information as well.  Newer sound
            driver documentation is found in <file:Documentation/sound/alsa/∗>.

            If you have a PnP sound card and you want to configure it at boot
            time using the ISA PnP tools (read
            <http://www.roestock.demon.co.uk/isapnptools/>), then you need to
            compile the sound card support as a module and load that module
            after the PnP configuration is finished.  To do this, choose M here
            and read <file:Documentation/sound/oss/README.modules>; the module
            will be called soundcore.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for sound to work.
```
<h3>[&lowast;]   Preclaim OSS device numbers</h3>
```properties
Symbol:     CONFIG_SOUND_OSS_CORE_PRECLAIM

Help:       With this option enabled, the kernel will claim all OSS device
            numbers if any OSS support (native or emulation) is enabled
            whether the respective module is loaded or not and try to load the
            appropriate module using sound-slot/service-∗ and char-major-∗
            module aliases when one of the device numbers is opened.  With
            this option disabled, kernel will only claim actually in-use
            device numbers and opening a missing device will generate only the
            standard char-major-∗ aliases.

            The only visible difference is use of additional module aliases
            and whether OSS sound devices appear multiple times in
            /proc/devices.  sound-slot/service-∗ module aliases are scheduled
            to be removed (ie. PRECLAIM won't be available) and this option is
            to make the transition easier.  This option can be overridden
            during boot using the kernel parameter soundcore.preclaim_oss.

            Disabling this allows alternative OSS implementations.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            as many applications (especially lightweight status bars such as slstatus
            rely on the existence of /dev/mixer).
            
            DOTSLASHLINUX has a guide on how to configure the lightest status bar
            ever slstatus, kindly check:
            
                https://www.dotslashlinux.com/2017/04/24/best-slstatus-configuration/
```
<h3><&lowast;>   Advanced Linux Sound Architecture  ---></h3>
```properties
Symbol:     CONFIG_SND

Help:       Say 'Y' or 'M' to enable ALSA (Advanced Linux Sound Architecture),
            the new base sound system.

            For more information, see <http://www.alsa-project.org/>

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for sound to work.
```
<h3><&lowast;>   OSS Mixer API</h3>
```properties
Symbol:     CONFIG_SND_MIXER_OSS

Help:       To enable OSS mixer API emulation (/dev/mixer∗), say Y here
            and read <file:Documentation/sound/alsa/OSS-Emulation.txt>.

            Many programs still use the OSS API, so say Y.

            To compile this driver as a module, choose M here: the module
            will be called snd-mixer-oss.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as many applications (especially lightweight status bars such as slstatus
            rely on the existence of /dev/mixer).
            
            DOTSLASHLINUX has a guide on how to configure the lightest status bar
            ever slstatus, kindly check:
            
                https://www.dotslashlinux.com/2017/04/24/best-slstatus-configuration/
```
<h3><&lowast;>   OSS PCM (digital audio) API</h3>
```properties
Symbol:     CONFIG_SND_PCM_OSS

Help:       To enable OSS digital audio (PCM) emulation (/dev/dsp∗), say Y
            here and read <file:Documentation/sound/alsa/OSS-Emulation.txt>.

            Many programs still use the OSS API, so say Y.

            To compile this driver as a module, choose M here: the module
            will be called snd-pcm-oss.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as many applications (especially lightweight status bars such as slstatus
            rely on the existence of /dev/mixer).
            
            DOTSLASHLINUX has a guide on how to configure the lightest status bar
            ever slstatus, kindly check:
            
                https://www.dotslashlinux.com/2017/04/24/best-slstatus-configuration/
```
<h3>[&lowast;]   PCM timer interface</h3>
```properties
Symbol:     CONFIG_SND_PCM_TIMER

Help:       If you disable this option, pcm timer will be unavailable, so
            those stubs that use pcm timer (e.g. dmix, dsnoop & co) may work
            incorrectlly.

            For some embedded devices, we may disable it to reduce memory
            footprint, about 20KB on x86_64 platform.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for dmix which is required for allowing sound output from
            multiple applications at the same time on systems that don't use
            PulseAudio to work properly.

            DOTSLASHLINUX has a guide on how to setup a basic ALSA configuration
            with dmix to allow sound from multiple applications without using
            PulseAudio, kindly check:

                https://www.dotslashlinux.com/2017/03/30/basic-alsa-configuration/
```
<h3>[&lowast;]   Dynamic device file minor numbers</h3>
```properties
Symbol:     CONFIG_SND_DYNAMIC_MINORS

Help:       If you say Y here, the minor numbers of ALSA device files in
            /dev/snd/ are allocated dynamically.  This allows you to have
            more than 8 sound cards, but requires a dynamic device file
            system like udev.

            If you are unsure about this, say N here.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you're receving dmesg errors indicating that you should include
            this option.
```
<h3>(4)     Max number of sound cards</h3>
```properties
Symbol:     CONFIG_SND_MAX_CARDS

Help:       Specify the max number of sound cards that can be assigned
            on a single machine.

Type:       integer

Choice:     (4) custom

Reason:     You can safely set the value of this option equal to (4)
            as on most systems you won't be using more than 1 or 2
            sound cards.
```
<h3>[&lowast;]   PCI sound devices  ---></h3>
```properties
Symbol:     CONFIG_SND_PCI

Help:       Support for sound devices connected via the PCI bus.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            in order for Intel High Definition Audio to work properly.
```
<h3>HD-Audio  ---></h3>
<h3><&lowast;> HD Audio PCI</h3>
```properties
Symbol:     CONFIG_SND_HDA_INTEL

Help:       Say Y here to include support for Intel "High Definition
            Audio" (Azalia) and its compatible devices.

            This option enables the HD-audio controller.  Don't forget
            to choose the appropriate codec options below.

            To compile this driver as a module, choose M here: the module
            will be called snd-hda-intel.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for Intel High Definition Audio to work properly.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep snd_hda_intel

            should tell you whether you need this option or not.
```
<h3><&lowast;> Build IDT/Sigmatel HD-audio codec support</h3>
```properties
Symbol:     CONFIG_SND_HDA_CODEC_SIGMATEL

Help:       Say Y or M here to include IDT (Sigmatel) HD-audio codec support in
            snd-hda-intel driver, such as STAC9200.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for IDT codecs to work properly in Intel High Definition Audio driver.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep snd_hda_codec_idt

            should tell you whether you need this option or not.
```
<h3><&lowast;> Build HDMI/DisplayPort HD-audio codec support</h3>
```properties
Symbol:     CONFIG_SND_HDA_CODEC_HDMI

Help:       Say Y or M here to include HDMI and DisplayPort HD-audio codec
            support in snd-hda-intel driver.  This includes all AMD/ATI,
            Intel and Nvidia HDMI/DisplayPort codecs.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order for HDMI codecs to work properly in Intel High Definition Audio driver.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep snd_hda_codec

            should tell you whether you need this option or not.
```
<h3>-&lowast;- Enable generic HD-audio codec parser</h3>
```properties
Symbol:     CONFIG_SND_HDA_GENERIC

Help:       Say Y or M here to enable the generic HD-audio codec parser
            in snd-hda-intel driver.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included a CODEC option above (that is if it isn't
            already forcibly included by CONFIG_SND_HDA_CODEC_SIGMATEL and 
            CONFIG_SND_HDA_CODEC_HDMI).
```
<h3>(1) Default time-out for HD-audio power-save mode</h3>
```properties
Symbol:     CONFIG_SND_HDA_POWER_SAVE_DEFAULT

Help:       The default time-out value in seconds for HD-audio automatic
            power-save mode.  0 means to disable the power-save mode.

Type:       integer

Choice:     (1) custom

Reason:     You can safely set the value of this option to (1) to boost power
            saving on the sound card when not in use.
```
<h3>(64)  Pre-allocated buffer size for HD-audio driver</h3>
```properties
Symbol:     CONFIG_SND_HDA_PREALLOC_SIZE

Help:       Specifies the default pre-allocated buffer-size in kB for the
            HD-audio driver.  A larger buffer (e.g. 2048) is preferred
            for systems using PulseAudio.  The default 64 is chosen just
            for compatibility reasons.

            Note that the pre-allocation size can be changed dynamically
            via a proc file (/proc/asound/card∗/pcm∗/sub∗/prealloc), too.

Type:       integer

Choice:     (64) default

Reason:     You can safely leave the value of this option set to the default
            value of (64) as it's enough for systems using ALSA only without
            PulseAudio.

            DOTSLASHLINUX has a guide on how to setup a basic ALSA configuration
            with dmix to allow sound from multiple applications without using
            PulseAudio, kindly check:

                https://www.dotslashlinux.com/2017/03/30/basic-alsa-configuration/
            
            Change the value of this option to (2048) if you plan on using
            PulseAudio.
```
<h3>HID support  ---></h3>
<h3>-&lowast;- HID bus support</h3>
```properties
Symbol:     CONFIG_HID

Help:       A human interface device (HID) is a type of computer device that
            interacts directly with and takes input from humans. The term "HID"
            most commonly used to refer to the USB-HID specification, but other
            devices (such as, but not strictly limited to, Bluetooth) are
            designed using HID specification (this involves certain keyboards,
            mice, tablets, etc). This option adds the HID bus to the kernel,
            together with generic HID layer code. The HID devices are added and
            removed from the HID bus by the transport-layer drivers, such as
            usbhid (USB_HID) and hidp (BT_HIDP).

            For docs and specs, see http://www.usb.org/developers/hidpage/

            If unsure, say Y.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_X86_64, CONFIG_NET,
            CONFIG_INPUT, CONFIG_USB, CONFIG_USB_HID, CONFIG_I2C and CONFIG_PCI).

            It's also recommended by the Gentoo Wiki.
```
<h3><&lowast;>   Generic HID driver</h3>
```properties
Symbol:     CONFIG_HID_GENERIC

Help:       Support for generic devices on the HID bus. This includes most
            keyboards and mice, joysticks, tablets and digitizers.

            To compile this driver as a module, choose M here: the module
            will be called hid-generic.

            If unsure, say Y.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required for USB keyboards and mice to work properly.
            
            It's also recommended by the Gentoo Wiki.
```
<h3>USB HID support  ---></h3>
<h3><&lowast;> USB HID transport layer</h3>
```properties
Symbol:     CONFIG_USB_HID

Help:       Say Y here if you want to connect USB keyboards,
            mice, joysticks, graphic tablets, or any other HID based devices
            to your computer via USB, as well as Uninterruptible Power Supply
            (UPS) and monitor control devices.

            You can't use this driver and the HIDBP (Boot Protocol) keyboard
            and mouse drivers at the same time. More information is available:
            <file:Documentation/input/input.txt>.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called usbhid.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required for USB keyboards and mice to work properly.
            
            It's also recommended by the Gentoo Wiki.
```
<h3>[&lowast;] USB support  ---></h3>
```properties
Symbol:     CONFIG_USB_SUPPORT

Help:       This option adds core support for Universal Serial Bus (USB).
            You will also need drivers from the following menu to make use of it.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted USB support to work.

            It's also recommended by the Gentoo Wiki.
```
<h3><&lowast;>   Support for Host-side USB</h3>
```properties
Symbol:     CONFIG_USB

Help:       Universal Serial Bus (USB) is a specification for a serial bus
            subsystem which offers higher speeds and more features than the
            traditional PC serial port.  The bus supplies power to peripherals
            and allows for hot swapping.  Up to 127 USB peripherals can be
            connected to a single USB host in a tree structure.

            The USB host is the root of the tree, the peripherals are the
            leaves and the inner nodes are special USB devices called hubs.
            Most PCs now have USB host ports, used to connect peripherals
            such as scanners, keyboards, mice, modems, cameras, disks,
            flash memory, network links, and printers to the PC.

            Say Y here if your computer has a host-side USB port and you want
            to use USB devices.  You then need to say Y to at least one of the
            Host Controller Driver (HCD) options below.  Choose a USB 1.1
            controller, such as "UHCI HCD support" or "OHCI HCD support",
            and "EHCI HCD (USB 2.0) support" except for older systems that
            do not have USB 2.0 support.  It doesn't normally hurt to select
            them all if you are not certain.

            If your system has a device-side USB port, used in the peripheral
            side of the USB protocol, see the "USB Gadget" framework instead.

            After choosing your HCD, then select drivers for the USB peripherals
            you'll be using.  You may want to check out the information provided
            in <file:Documentation/usb/> and especially the links given in
            <file:Documentation/usb/usb-help.txt>.

            To compile this driver as a module, choose M here: the
            module will be called usbcore.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted USB support to work.

            It's also recommended by the Gentoo Wiki.
```
<h3>[&lowast;]   PCI based USB host interface</h3>
```properties
Symbol:     CONFIG_USB_PCI

Help:       A lot of embeded system SOC (e.g. freescale T2080) have both
            PCI and USB modules. But USB module is controlled by registers
            directly, it have no relationship with PCI module.

            When say N here it will not build PCI related code in USB driver.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            as it solves the problem of undetectable mice and keyboards as reported
            by many users.
```
<h3>[&lowast;]   Enable USB persist by default</h3>
```properties
Symbol:     CONFIG_USB_DEFAULT_PERSIST

Help:       Say N here if you don't want USB power session persistence
            enabled by default.  If you say N it will make suspended USB
            devices that lose power get reenumerated as if they had been
            unplugged, causing any mounted filesystems to be lost.  The
            persist feature can still be enabled for individual devices
            through the power/persist sysfs node. See
            Documentation/driver-api/usb/persist.rst for more info.

            If you have any questions about this, say Y here, only say N
            if you know exactly what you are doing.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted USB support to work.

            It's also recommended by the Gentoo Wiki.
```
<h3><&lowast;>   xHCI HCD (USB 3.0) support</h3>
```properties
Symbol:     CONFIG_USB_XHCI_HCD

Help:       The eXtensible Host Controller Interface (xHCI) is standard for USB 3.0
            "SuperSpeed" host controller hardware.

            To compile this driver as a module, choose M here: the
            module will be called xhci-hcd.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted USB 3.0 support to work.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep xhci
            
            and:

                cat dmesg.txt | grep xhci

            and:

                cat lsusb.txt | grep 3.0

            should tell you whether you need this option or not.
            
            It's also recommended by the Gentoo Wiki.
```
<h3><&lowast;>   EHCI HCD (USB 2.0) support</h3>
```properties
Symbol:     CONFIG_USB_EHCI_HCD

Help:       The Enhanced Host Controller Interface (EHCI) is standard for USB 2.0
            "high speed" (480 Mbit/sec, 60 Mbyte/sec) host controller hardware.
            If your USB host controller supports USB 2.0, you will likely want to
            configure this Host Controller Driver.

            EHCI controllers are packaged with "companion" host controllers (OHCI
            or UHCI) to handle USB 1.1 devices connected to root hub ports.  Ports
            will connect to EHCI if the device is high speed, otherwise they
            connect to a companion controller.  If you configure EHCI, you should
            probably configure the OHCI (for NEC and some other vendors) USB Host
            Controller Driver or UHCI (for Via motherboards) Host Controller
            Driver too.

            You may want to read <file:Documentation/usb/ehci.txt>.

            To compile this driver as a module, choose M here: the
            module will be called ehci-hcd.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted USB 2.0 support to work.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep ehci
            
            and:
                
                cat dmesg.txt | grep ehci

            and:

                cat lsusb.txt | grep 2.0

            should tell you whether you need this option or not.
            
            It's also recommended by the Gentoo Wiki.
```
<h3>[&lowast;]     Improved Transaction Translator scheduling</h3>
```properties
Symbol:     CONFIG_USB_EHCI_IT_NEWSCHED

Help:       This changes the periodic scheduling code to fill more of the low
            and full speed bandwidth available from the Transaction Translator
            (TT) in USB 2.0 hubs.  Without this, only one transfer will be
            issued in each microframe, significantly reducing the number of
            periodic low/fullspeed transfers possible.

            If you have multiple periodic low/fullspeed devices connected to a
            highspeed USB hub which is connected to a highspeed USB Host
            Controller, and some of those devices will not work correctly
            (possibly due to "ENOSPC" or "-28" errors), say Y.  Conversely, if
            you have only one such device and it doesn't work, you could try
            saying N.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_USB_EHCI_HCD as it speeds up USB
            transfers.
            
            It's also recommended by the Gentoo Wiki.
```
<h3><&lowast;>   USB Mass Storage support</h3>
```properties
Symbol:     CONFIG_USB_STORAGE

Help:       Say Y here if you want to connect USB mass storage devices to your
            computer's USB port. This is the driver you need for USB
            floppy drives, USB hard disks, USB tape drives, USB CD-ROMs,
            USB flash devices, and memory sticks, along with
            similar devices. This driver may also be used for some cameras
            and card readers.

            This option depends on 'SCSI' support being enabled, but you
            probably also need 'SCSI device support: SCSI disk support'
            (BLK_DEV_SD) for most USB storage devices.

            To compile this driver as a module, choose M here: the
            module will be called usb-storage.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_USB_SUPPORT.
            
```
<h3>-&lowast;- LED Support  ---></h3>
```properties
Symbol:     CONFIG_NEW_LEDS

Help:       Say Y to enable Linux LED support.  This allows control of supported
            LEDs from both userspace and optionally, by kernel events (triggers).

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_PCI, CONFIG_I2C,
            CONFIG_X86, CONFIG_ACPI, CONFIG_ACPI_VIDEO, CONFIG_RFKILL, CONFIG_INPUT
            and a lot of important options).
```
<h3>-&lowast;-   LED Class Support</h3>
```properties
Symbol:     CONFIG_LEDS_CLASS

Help:       This option enables the led sysfs class in /sys/class/leds.  You'll
            need this to do anything useful with LEDs.  If unsure, say N.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_PCI, CONFIG_I2C,
            CONFIG_X86, CONFIG_ACPI, CONFIG_ACPI_VIDEO, CONFIG_RFKILL, CONFIG_INPUT
            and a lot of important options).
```
<h3>-&lowast;-   LED Trigger support  ---></h3>
```properties
Symbol:     CONFIG_LEDS_TRIGGERS

Help:       This option enables trigger support for the leds class.
            These triggers allow kernel events to drive the LEDs and can
            be configured via sysfs. If unsure, say Y.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_NET, CONFIG_WLAN,
            CONFIG_HID and CONFIG_INPUT).
```
<h3>[&lowast;] Real Time Clock  ---></h3>
```properties
Symbol:     CONFIG_RTC_CLASS

Help:       Generic RTC class support. If you say yes here, you will
            be allowed to plug one or more RTCs to your system. You will
            probably want to enable one or more of the interfaces below.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            to have a working hardware clock.

            It's also recommended by the Gentoo Wiki.
```
<h3>[&lowast;]   Set system time from RTC on startup and resume</h3>
```properties
Symbol:     CONFIG_RTC_HCTOSYS

Help:       If you say yes here, the system time (wall clock) will be set using
            the value read from a specified RTC device. This is useful to avoid
            unnecessary fsck runs at boot time, and to network better.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            as it speeds up boot time.

            It's also recommended by the Gentoo Wiki.
```
<h3>(rtc0)  RTC used to set the system time</h3>
```properties
Symbol:     CONFIG_RTC_HCTOSYS_DEVICE

Help:       The RTC device that will be used to (re)initialize the system
            clock, usually rtc0. Initialization is done when the system
            starts up, and when it resumes from a low power state. This
            device should record time in UTC, since the kernel won't do
            timezone correction.

            The driver for this RTC device must be loaded before late_initcall
            functions run, so it must usually be statically linked.

            This clock should be battery-backed, so that it reads the correct
            time when the system boots from a power-off state. Otherwise, your
            system will need an external clock source (like an NTP server).

            If the clock you specify here is not battery backed, it may still
            be useful to reinitialize system time when resuming from system
            sleep states. Do not specify an RTC here unless it stays powered
            during all this system's supported sleep states.

Type:       string

Choice:     (rtc0) default

Reason:     You can safely leave the value of this option to the default value
            of (rtc0) as recommended by the Gentoo Wiki.
```
<h3>[&lowast;]   /sys/class/rtc/rtcN (sysfs)</h3>
```properties
Symbol:     CONFIG_RTC_INTF_SYSFS

Help:       Say yes here if you want to use your RTCs using sysfs interfaces,
            /sys/class/rtc/rtc0 through /sys/.../rtcN.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            to have a working hardware clock.

            It's also recommended by the Gentoo Wiki.
```
<h3>[&lowast;]   /proc/driver/rtc (procfs for rtcN)</h3>
```properties
Symbol:     CONFIG_RTC_INTF_PROC

Help:       Say yes here if you want to use your system clock RTC through
            the proc interface, /proc/driver/rtc.
            Other RTCs will not be available through that API.
            If there is no RTC for the system clock, then the first RTC(rtc0)
            is used by default.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            to have a working hardware clock.

            It's also recommended by the Gentoo Wiki.
```
<h3>[&lowast;]   /dev/rtcN (character devices)</h3>
```properties
Symbol:     CONFIG_RTC_INTF_DEV

Help:       Say yes here if you want to use your RTCs using the /dev
            interfaces, which "udev" sets up as /dev/rtc0 through
            /dev/rtcN.

            You may want to set up a symbolic link so one of these
            can be accessed as /dev/rtc, which is a name
            expected by "hwclock" and some other programs. Recent
            versions of "udev" are known to set up the symlink for you.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            to have a working hardware clock.

            It's also recommended by the Gentoo Wiki.
```
<h3><&lowast;>   PC-style 'CMOS'</h3>
```properties
Symbol:     CONFIG_RTC_DRV_CMOS

Help:       Say "yes" here to get direct support for the real time clock
            found in every PC or ACPI-based system, and some other boards.
            Specifically the original MC146818, compatibles like those in
            PC south bridges, the DS12887 or M48T86, some multifunction
            or LPC bus chips, and so on.

            Your system will need to define the platform device used by
            this driver, otherwise it won't be accessible. This means
            you can safely enable this driver if you don't know whether
            or not your board has this kind of hardware.

            This driver can also be built as a module. If so, the module
            will be called rtc-cmos.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            to have a working hardware clock.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep rtc

            should tell you whether you need this option or not.

            It's also recommended by the Gentoo Wiki.
```
<h3>DMABUF options  ---></h3>
<h3>-&lowast;- Explicit Synchronization Framework</h3>
```properties
Symbol:     CONFIG_SYNC_FILE

Help:       The Sync File Framework adds explicit syncronization via
            userspace. It enables send/receive 'struct dma_fence' objects to/from
            userspace via Sync File fds for synchronization between drivers via
            userspace components. It has been ported from Android.

            The first and main user for this is graphics in which a fence is
            associated with a buffer. When a job is submitted to the GPU a fence
            is attached to the buffer and is transferred via userspace, using Sync
            Files fds, to the DRM driver for example. More details at
            Documentation/sync_file.txt.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_X86, CONFIG_PCI,
            CONFIG_AGP, CONFIG_DRM, CONFIG_DRM_I915 and CONFIG_MMU).
```
<h3>[&lowast;] X86 Platform Specific Device Drivers  ---></h3>
```properties
Symbol:     CONFIG_X86_PLATFORM_DEVICES

Help:       Say Y here to get to see options for device drivers for various
            x86 platforms, including vendor-specific laptop extension drivers.
            This option alone does not add any kernel code.

            If you say N, all options in this submenu will be skipped and disabled.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted to include some vendor specific extension drivers.
```
<h3><&lowast;>   WMI</h3>
```properties
Symbol:     CONFIG_ACPI_WMI

Help:       This driver adds support for the ACPI-WMI (Windows Management
            Instrumentation) mapper device (PNP0C14) found on some systems.

            ACPI-WMI is a proprietary extension to ACPI to expose parts of the
            ACPI firmware to userspace - this is done through various vendor
            defined methods and data blocks in a PNP0C14 device, which are then
            made available for userspace to call.

            The implementation of this in Linux currently only exposes this to
            other kernel space drivers.

            This driver is a required dependency to build the firmware specific
            drivers needed on many machines, including Acer and HP laptops.

            It is safe to enable this driver even if your DSDT doesn't define
            any ACPI-WMI devices.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if your system supports ACPI-WMI.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep WMI

            should tell you whether you need this option or not.
```
<h3><&lowast;>   Toshiba Bluetooth RFKill switch support</h3>
```properties
Symbol:     CONFIG_TOSHIBA_BT_RFKILL

Help:       This driver adds support for Bluetooth events for the RFKill
            switch on modern Toshiba laptops with full ACPI support and
            an RFKill switch.

            This driver handles RFKill events for the TOS6205 Bluetooth,
            and re-enables it when the switch is set back to the 'on'
            position.

            If you have a modern Toshiba laptop with a Bluetooth and an
            RFKill switch (such as the Portege R500), say Y.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you wanted to include some vendor specific extension drivers.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep toshiba_bluetooth

            should tell you whether you need this option or not.
```
<h3><&lowast;>   Toshiba HDD Active Protection Sensor</h3>
```properties
Symbol:     CONFIG_TOSHIBA_HAPS

Help:       This driver adds support for the built-in accelerometer
            found on recent Toshiba laptops equipped with HID TOS620A
            device.

            This driver receives ACPI notify events 0x80 when the sensor
            detects a sudden move or a harsh vibration, as well as an
            ACPI notify event 0x81 whenever the movement or vibration has
            been stabilized.

            Also provides sysfs entries to get/set the desired protection
            level and resetting the HDD protection interface.

            If you have a recent Toshiba laptop with a built-in accelerometer
            device, say Y.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if your Toshiba laptop is equiped with a HID TOS620A device.
            
            If you've followed the guide above, then a simple:

                cat lsmod.txt | grep toshiba_haps

            should tell you whether you need this option or not.
```
<h3><&lowast;>   Toshiba WMI Hotkeys Driver (EXPERIMENTAL)</h3>
```properties
Symbol:     CONFIG_TOSHIBA_WMI

Help:       This driver adds hotkey monitoring support to some Toshiba models
            that manage the hotkeys via WMI events.

            WARNING: This driver is incomplete as it lacks a proper keymap and the
            ∗notify function only prints the ACPI event type value. Be warned that
            you will need to provide some information if you have a Toshiba model
            with WMI event hotkeys and want to help with the develpment of this
            driver.

            If you have a WMI-based hotkeys Toshiba laptop, say Y or M here.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if your Toshiba laptop supports WMI.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep WMI

            should tell you whether you need this option or not.
```
<h3><&lowast;>   WMI support for MXM Laptop Graphics</h3>
```properties
Symbol:     CONFIG_MXM_WMI

Help:       MXM is a standard for laptop graphics cards, the WMI interface
            is required for switchable nvidia graphics machines

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            in order to get a working bumblebee setup on an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/
```
<h3><&lowast;>   Intel Rapid Start Technology Driver</h3>
```properties
Symbol:     CONFIG_INTEL_RST

Help:       This driver provides support for modifying paramaters on systems
            equipped with Intel's Rapid Start Technology. When put in an ACPI
            sleep state, these devices will wake after either a configured
            timeout or when the system battery reaches a critical state,
            automatically copying memory contents to disk. On resume, the
            firmware will copy the memory contents back to RAM and resume the OS
            as usual.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if your laptop supports Intel RST and you want to improve suspend
            to disk and resume support.
```
<h3>[&lowast;] Generic powercap sysfs driver  ---></h3>
```properties
Symbol:     CONFIG_POWERCAP

Help:       The power capping sysfs interface allows kernel subsystems to expose power
            capping settings to user space in a consistent way.  Usually, it consists
            of multiple control types that determine which settings may be exposed and
            power zones representing parts of the system that can be subject to power
            capping.

            If you want this code to be compiled in, say Y here.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you're using an Intel CPU to enable RAPL support.
```
<h3><&lowast;>   Intel RAPL Support</h3>
```properties
Symbol:     CONFIG_INTEL_RAPL

Help:       This enables support for the Intel Running Average Power Limit (RAPL)
            technology which allows power limits to be enforced and monitored on
            modern Intel processors (Sandy Bridge and later).

            In RAPL, the platform level settings are divided into domains for
            fine grained control. These domains include processor package, DRAM
            controller, CPU core (Power Plance 0), graphics uncore (Power Plane
            1), etc.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using an Intel CPU to enable RAPL support.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep RAPL

            and:

                cat lsmod.txt | grep rapl

            should tell you whether you need this option or not.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX followers 杨鑫 (Yang Mame) from China, decided to follow up with the series and provide Chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in Chinese <a href="https://blog.yangmame.top/Linux内核配置指南-Networking-support和Device-Drivers.html" target="_blank">click here</a>.
