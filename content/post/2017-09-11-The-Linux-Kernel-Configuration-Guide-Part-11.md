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
lshw -short > /mnt/mountedblock/home/$USER/SystemRescueCd/lshwshort.txt
lshw > /mnt/mountedblock/home/$USER/SystemRescueCd/lshw.txt

lspci -kk > /mnt/mountedblock/home/$USER/SystemRescueCd/lspcikk.txt
lspci -nnkkvvv > /mnt/mountedblock/home/$USER/SystemRescueCd/lspcinnkkvvv.txt

lsusb > /mnt/mountedblock/home/$USER/SystemRescueCd/lsusb.txt
lsusb -v > /mnt/mountedblock/home/$USER/SystemRescueCd/lsusbv.txt

lsmod > /mnt/mountedblock/home/$USER/SystemRescueCd/lsmod.txt

dmesg > /mnt/mountedblock/home/$USER/SystemRescueCd/dmesg.txt

cat /proc/cpuinfo > /mnt/mountedblock/home/$USER/SystemRescueCd/cpuinfo.txt

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

            DOTSLASHLINUX has a detailed guide on how to build microcode updates
            directly into the linux kernel, kindly check the link below:

                https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-updates-directly-into-the-linux-kernel/
```
<h3>(intel-ucode/06-3c-03) External firmware blobs to build into the kernel binary</h3>
```none
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
```none
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
<h3>-&ast;- Plug and Play support  ---></h3>
```none
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

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already included by CONFIG_PCI, CONFIG_ACPI and
            CONFIG_X86).
```
<h3>[&ast;]   PNP debugging messages</h3>
```none
Symbol:     CONFIG_PNP_DEBUG_MESSAGES

Help:       Say Y here if you want the PNP layer to be able to produce debugging
            messages if needed.  The messages can be enabled at boot-time with
            the pnp.debug kernel parameter.

            This option allows you to save a bit of space if you do not want
            the messages to even be built into the kernel.

            If you have any doubts about this, say Y here.

Type:       boolean

Choice:     built-in [*]

Reason:     It's recommended that you include this option in your kernel as
            it provides really helpful information about PnP devices.
```
<h3>[&ast;] Block devices  ---></h3>
```none
Symbol:     CONFIG_BLK_DEV

Help:       Say Y here to get to see options for various different block device
            drivers. This option alone does not add any kernel code.

            If you say N, all options in this submenu will be skipped and disabled;
            only do this if you know what you are doing.

Type:       boolean

Choice:     built-in [*]

Reason:     It's recommended that you include this option in your kernel.
```
<h3><&ast;>   Loopback device support</h3>
```none
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

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as it allows you to mount images (files with .img, .iso ...etc extensions)
            as if they were devices.
```
<h3>(0)     Number of loop devices to pre-create at init time</h3>
```none
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
<h3>-&ast;- Intel Management Engine Interface</h3>
```none
Symbol:     CONFIG_INTEL_MEI

Help:       The Intel Management Engine (Intel ME) provides Manageability,
            Security and Media services for system containing Intel chipsets.
            if selected /dev/mei misc device will be created.

            For more information see
            <http://software.intel.com/en-us/manageability/>

Type:       tristate

Choice:     built-in -*-

Reason:     It's recommended that you include this option in your kernel if you're
            using a system with a modern intel chipset.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep mei -A2

            should tell you whether you need this option or not.
```
<h3><&ast;> ME Enabled Intel Chipsets</h3>
```none
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

Choice:     built-in <*>

Reason:     It's recommended that you include this option in your kernel if you're
            using a system with a modern intel chipset.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep mei -A2

            should tell you whether you need this option or not.
```
<h3>SCSI device support  ---></h3>
<h3>-&ast;- SCSI device support</h3>
```none
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

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel if
            you're using one of the SCSI devices mentioned above (mainly a SCSI
            hard drive and CD-ROM).
```
<h3>-&ast;- SCSI: use blk-mq I/O path by default</h3>
```none
Symbol:     CONFIG_SCSI_MQ_DEFAULT

Help:       This option enables the new blk-mq based I/O path for SCSI
            devices by default.  With the option the scsi_mod.use_blk_mq
            module/boot option defaults to Y, without it to N, but it can
            still be overridden either way.

            If unsure say N.

Type:       boolean

Choice:     built-in -*-

Reason:     If you've checked the list of priorities listed at the top of this
            page, you'll see "low-latency" listed as one of the top priorities.

            To achieve that, you can use ck-sources (MuQSS + BFQ), and 
            CONFIG_DEFAULT_BFQ requires this option to work.
```
<h3><&ast;> SCSI disk support</h3>
```none
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

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using a SCSI hard disk.

            When booting without an initrd:
                
                https://www.dotslashlinux.com/2017/04/29/booting-the-linux-kernel-without-an-initrd-initramfs/

            you shouldn't compile this option as a module as it may result in an
            unbootable system.
```
<h3><&ast;> SCSI CDROM support</h3>
```none
Symbol:     CONFIG_BLK_DEV_SR

Help:       If you want to use a CD or DVD drive attached to your computer
            by SCSI, FireWire, USB or ATAPI, say Y and read the SCSI-HOWTO
            and the CDROM-HOWTO at <http://www.tldp.org/docs.html#howto>.

            Make sure to say Y or M to "ISO 9660 CD-ROM file system support".

            To compile this driver as a module, choose M here and read
            <file:Documentation/scsi/scsi.txt>.
            The module will be called sr_mod.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using a SCSI CD/DVD drive.
```
<h3>[&ast;] Asynchronous SCSI scanning</h3>
```none
Symbol:     CONFIG_SCSI_SCAN_ASYNC

Help:       The SCSI subsystem can probe for devices while the rest of the
            system continues booting, and even probe devices on different
            busses in parallel, leading to a significant speed-up.

            You can override this choice by specifying "scsi_mod.scan=sync"
            or async on the kernel's command line.

            Note that this setting also affects whether resuming from
            system suspend will be performed asynchronously.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kerenl
            as it speeds up boot time.

            In extrememly rare cases, this option may cause an incorrect naming
            of your root device. Although unlikely, if that was your case then
            you can safely exclude this option (you might experience some
            increase in boot time though).
```
<h3><&ast;> Serial ATA and Parallel ATA drivers (libata)  ---></h3>
```none
Symbol:     CONFIG_ATA

Help:       If you want to use an ATA hard disk, ATA tape drive, ATA CD-ROM or
            any other ATA device under Linux, say Y and make sure that you know
            the name of your ATA host adapter (the card inside your computer
            that "speaks" the ATA protocol, also called ATA controller),
            because you will be asked for it.

            NOTE: ATA enables basic SCSI support; *however*,
            'SCSI disk support', 'SCSI tape support', or
            'SCSI CDROM support' may also be needed,
            depending on your hardware configuration.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a SCSI hard disk drive and a SCSI CD/DVD drive.
```
<h3>[&ast;]   ATA ACPI Support</h3>
```none
Symbol:     CONFIG_ATA_ACPI

Help:       This option adds support for ATA-related ACPI objects.
            These ACPI objects add the ability to retrieve taskfiles
            from the ACPI BIOS and write them to the disk controller.
            These objects may be related to performance, security,
            power management, or other areas.
            You can disable this at kernel boot time by using the
            option libata.noacpi=1

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_ATA as it may boost performance
            and power saving features of ATA devices.
```
<h3>[&ast;]     SATA Zero Power Optical Disc Drive (ZPODD) support</h3>
```none
Symbol:     CONFIG_SATA_ZPODD

Help:       This option adds support for SATA Zero Power Optical Disc
            Drive (ZPODD). It requires both the ODD and the platform
            support, and if enabled, will automatically power on/off the
            ODD when certain condition is satisfied. This does not impact
            end user's experience of the ODD, only power is saved when
            the ODD is not in use (i.e. no disc inside).

            If unsure, say N.

Type:       boolean

Choice:     built-in [*]

Reason:     It's recommended that you include this option in your kernel if you
            have a SCSI CD/DVD drive as it'll help save energy when the drive
            isn't in use.
```
<h3><&ast;>   AHCI SATA support</h3>
```none
Symbol:     CONFIG_SATA_AHCI

Help:       This option enables support for AHCI Serial ATA.
            If unsure, say N.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as it's basically the driver that'll be used for your SATA controller.

            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep ahci -B2

            should tell you whether you need this option or not.
```
<h3>[&ast;] Network device support  ---></h3>
```none
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

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            to access the network devices' drivers section.
```
<h3>[&ast;]   Ethernet driver support  ---></h3>
```none
Symbol:     CONFIG_ETHERNET

Help:       This section contains all the Ethernet device drivers.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel 
            if you wanted your ethernet adapter to work.
 
            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep Ethernet -A2

            should tell you whether you need this option or not.
```
<h3>[&ast;]   Atheros devices</h3>
```none
Symbol:     CONFIG_NET_VENDOR_ATHEROS

Help:       If you have a network (Ethernet) card belonging to this class, say Y.

            Note that the answer to this question doesn't directly affect the
            kernel: saying N will just cause the configurator to skip all
            the questions about Atheros devices. If you say Y, you will be asked
            for your specific card in the following questions.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using an atheros ethernet controller.
```
<h3><&ast;>     Qualcomm Atheros AR816x/AR817x support</h3>
```none
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

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros L1F ethernet adapter.
```
<h3>[&ast;]   Wireless LAN  ---></h3>
```none
Symbol:     CONFIG_WLAN

Help:       This section contains all the pre 802.11 and 802.11 wireless
            device drivers. For a complete list of drivers and documentation
            on them refer to the wireless wiki:

            http://wireless.kernel.org/en/users/Drivers 

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you wanted your wireless network adapter to work.
            
            If you've followed the guide above, then a simple:

                cat lspcikk.txt | grep Wireless -A2

            should tell you whether you need this option or not.
```
<h3>[&ast;]   Atheros/Qualcomm devices</h3>
```none
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

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros wireless network adapter.
```
<h3>[&ast;]     Atheros bluetooth coexistence support</h3>
```none
Symbol:     CONFIG_ATH9K_BTCOEX_SUPPORT

Help:       Say Y, if you want to use the ath9k/ath9k_htc radios together with
            Bluetooth modules in the same system.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using ath9k in order to get bluetooth working.
```
<h3><&ast;>     Atheros 802.11n wireless cards support</h3>
```none
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

Choice:     <*>

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros 802.11n wireless network adapter.
```
<h3>[&ast;]       Atheros ath9k PCI/PCIe bus support</h3>
```none
Symbol:     CONFIG_ATH9K_PCI

Help:       This option enables the PCI bus support in ath9k.

            Say Y, if you have a compatible PCI/PCIe wireless card.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using a Qualcomm Atheros PCI/PCIe compatible wireless network card.
```
<h3>[&ast;]       Atheros ath9k rfkill support</h3>
```none
Symbol:     CONFIG_ATH9K_RFKILL

Help:       Say Y to have ath9k poll the RF-Kill GPIO every couple of
            seconds. Turn off to save power, but enable it if you have
            a platform that can toggle the RF-Kill GPIO.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            your Qualcomm Atheros wireless network adapter has a RF-Kill switch, as
            it'll be necessary on some systems to get Wi-Fi working (since some
            wireless cards may be blocked by the RF-Kill switch and you may have to
            unblock them).
```
<h3>[&ast;]       Atheros ath9k support for PC OEM cards</h3>
```none
Symbol:     CONFIG_ATH9K_PCOEM

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel if
            you're using ath9k as it's required on some systems for the detection
            of the wireless network adapter.
```
<h3>Input device support  ---></h3>
<h3>-&ast;- Generic input layer (needed for keyboard, mouse, ...)</h3>
```none
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

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            if you want to use your mouse and keyboard.
```
<h3>-&ast;-   Sparse keymap support library</h3>
```none
Symbol:     CONFIG_INPUT_SPARSEKMAP

Help:       Say Y here if you are using a driver for an input
            device that uses sparse keymap. This option is only
            useful for out-of-tree drivers since in-tree drivers
            select it automatically.

            If unsure, say N.

            To compile this driver as a module, choose M here: the
            module will be called sparse-keymap.

Type:       tristate

Choice:     built-in -*-

Reason:     You can safely exclude this option unless it was forcibly included
            by other options related to out-of-tree drivers.
```
<h3><&ast;>   Mouse interface</h3>
```none
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

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel in
            order for your mouse to work.
```
<h3>(1024)  Horizontal screen resolution</h3>
```none
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
```none
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
<h3><&ast;>   Event interface</h3>
```none
Symbol:     CONFIG_INPUT_EVDEV

Help:       Say Y here if you want your input device events be accessible
            under char device 13:64+ - /dev/input/eventX in a generic way.

            To compile this driver as a module, choose M here: the
            module will be called evdev.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by Xorg input drivers (evdev, libinput ...etc).
```
<h3>[&ast;]   Keyboards  ---></h3>
```none
Symbol:     CONFIG_INPUT_KEYBOARD

Help:       Say Y here, and a list of supported keyboards will be displayed.
            This option doesn't affect the kernel.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your keyboard to work.
```
<h3><&ast;>   AT keyboard</h3>
```none
Symbol:     CONFIG_KEYBOARD_ATKBD

Help:       Say Y here if you want to use a standard AT or PS/2 keyboard. Usually
            you'll need this, unless you have a different type keyboard (USB, ADB
            or other). This also works for AT and PS/2 keyboards connected over a
            PS/2 to serial converter.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called atkbd.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel as
            in order for your AT or PS/2 keyboard to work.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep keyboard

            should tell you whether you need this option or not.
```
<h3>[&ast;]   Mice  ---></h3>
```none
Symbol:     CONFIG_INPUT_MOUSE

Help:       Say Y here, and a list of supported mice will be displayed.
            This option doesn't affect the kernel.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your mouse and touchpad to work.
```
<h3><&ast;>   PS/2 mouse</h3>
```none
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

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            in order for your PS/2 mouse and PS/2 touchpad to work.
            
            If you've followed the guide above, then a simple:

                cat dmesg.txt | grep psmouse

            should tell you whether you need this option or not.
```
<h3>[&ast;]     Synaptics PS/2 mouse protocol extension</h3>
```none
Symbol:     CONFIG_MOUSE_PS2_SYNAPTICS

Help:       Say Y here if you have a Synaptics PS/2 TouchPad connected to
            your system.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics Touchpad to be enumerated through
            PS/2.
```
<h3>[&ast;]     Synaptics PS/2 SMbus companion</h3>
```none
Symbol:     CONFIG_MOUSE_PS2_SYNAPTICS_SMBUS

Help:       Say Y here if you have a Synaptics RMI4 touchpad connected to
            to an SMBus, but enumerated through PS/2.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics RMI4 SMBus touchpad to work properly.

            Keep in mind that using this option alone without CONFIG_MOUSE_PS2_SYNPATICS
            will result in a terrible touchpad experience, therefore you have
            to include CONFIG_MOUSE_PS2_SYNAPTICS as well.

            This option is new, and it was included according to dmesg suggestion:
            
            "Your touchpad (PNP: TOS1150 TOS0310 PNP0f13) says it can support a different bus. If i2c-hid and hid-rmi are not used, you might want to try setting psmouse.synaptics_intertouch to 1 and report this to linux-input@vger.kernel.org"
```
<h3>-&ast;-   Synaptics RMI4 bus support</h3>
```none
Symbol:     CONFIG_RMI4_CORE

Help:       Say Y here if you want to support the Synaptics RMI4 bus.  This is
            required for all RMI4 device support.

            If unsure, say Y.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics RMI4 SMBus touchpad to work properly.
```
<h3><&ast;>     RMI4 SMB Support</h3>
```none
Symbol:     CONFIG_RMI4_SMB

Help:       Say Y here if you want to support RMI4 devices connected to an SMB
            bus.

            If unsure, say N.

            To compile this driver as a module, choose M here: the module will be
            called rmi_smbus.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            in order for your Synaptics RMI4 SMBus touchpad to work properly.
```
<h3>-&ast;-     RMI4 Function 03 (PS2 Guest)</h3>
```none
Symbol:     CONFIG_RMI4_F03

Help:       Say Y here if you want to add support for RMI4 function 03.

            Function 03 provides PS2 guest support for RMI4 devices. This
            includes support for TrackPoints on TouchPads.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>-&ast;-     RMI4 Function 11 (2D pointing)</h3>
```none
Symbol:     CONFIG_RMI4_F11

Help:       Say Y here if you want to add support for RMI4 function 11.

            Function 11 provides 2D multifinger pointing for touchscreens and
            touchpads. For sensors that support relative pointing, F11 also
            provides mouse input.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>-&ast;-     RMI4 Function 12 (2D pointing)</h3>
```none
Symbol:     CONFIG_RMI4_F12

Help:       Say Y here if you want to add support for RMI4 function 12.

            Function 12 provides 2D multifinger pointing for touchscreens and
            touchpads. For sensors that support relative pointing, F12 also
            provides mouse input.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>-&ast;-     RMI4 Function 30 (GPIO LED)</h3>
```none
Symbol:     CONFIG_RMI4_F30

Help:       Say Y here if you want to add support for RMI4 function 30.

            Function 30 provides GPIO and LED support for RMI4 devices. This
            includes support for buttons on TouchPads and ClickPads.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included by CONFIG_HID_RMI.
```
<h3>Hardware I/O ports  ---></h3>
<h3>-&ast;- Serial I/O support</h3>
```none
Symbol:     CONFIG_SERIO

Help:       Say Yes here if you have any input device that uses serial I/O to
            communicate with the system. This includes the
                          * standard AT keyboard and PS/2 mouse *
            as well as serial mice, Sun keyboards, some joysticks and 6dof
            devices and more.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called serio.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you included this option in your kernel
            (that is if it weren't already forcibly included by several important
            options).
```
<h3>-&ast;- i8042 PC Keyboard controller</h3>
```none
Symbol:     CONFIG_SERIO_I8042

Help:       i8042 is the chip over which the standard AT keyboard and PS/2
            mouse are connected to the computer. If you use these devices,
            you'll need to say Y here.

            If unsure, say Y.

            To compile this driver as a module, choose M here: the
            module will be called i8042.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you included this option in your kernel
            (that is if it weren't already forcibly included by several important
            options).
```
<h3>-&ast;- PS/2 driver library</h3>
```none
Symbol:     CONFIG_SERIO_LIBPS2

Help:       Say Y here if you are using a driver for device connected
            to a PS/2 port, such as PS/2 mouse or standard AT keyboard.

            To compile this driver as a module, choose M here: the
            module will be called libps2.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you included this option in your kernel
            (that is if it weren't already forcibly included by several important
            options).
```
<h3><&ast;> Raw access to serio ports</h3>
```none
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

Choice:     built-in <*>

Reason:     You can safely exclude this option if your Synaptics PS/2
            or RMI4 SMBus Touchpad is already working.

            In some cases including this option might fix an undetectable
            Synpatics touchpad.
```
