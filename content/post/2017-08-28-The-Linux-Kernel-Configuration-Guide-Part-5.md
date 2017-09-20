+++
title = "The Linux Kernel Configuration Guide Part 5"
slug = "the linux kernel configuration guide part 5"
nick = "kernel5"
date = "2017-08-28"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel5.png"
imgalt = "kernel5"
categories = [ "kernel" ]
+++
<h3>[&ast;] Enable the block layer  ---></h3>
<h3>--- Enable the block layer</h3>
```none
Symbol:     CONFIG_BLOCK

Help:       Provide block layer support for the kernel.

            Disable this option to remove the block layer support from the
            kernel. This may be useful for embedded devices.

            If this option is disabled:
              - block device files will become unusable
              - some filesystems (such as ext3) will become unavailable.

            Also, SCSI character devices and USB storage will be disabled since
            they make use of various block layer definitions and facilities.

            Say Y here unless you know you really don't want to mount disks and
            suchlike.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            since it's mandatory for using block devices as you won't be able
            to mount (or even use) your disks or any type of SCSI/USB storage and
            some filesystems will become unavailable as well.

            It's also required by CONFIG_GENTOO_LINUX, CONFIG_GENTOO_LINUX_UDEV
            and CONFIG_GENTOO_LINUX_INIT_SYSTEMD.
```
<h3>[&ast;]   Block layer SG support v4</h3>
```none
Symbol:     CONFIG_BLK_DEV_BSG

Help:       Saying Y here will enable generic SG (SCSI generic) v4 support
            for any block device.

            Unlike SG v3 (aka block/scsi_ioctl.c drivers/scsi/sg.c), SG v4
            can handle complicated SCSI commands: tagged variable length cdbs
            with bidirectional data transfers and generic request/response
            protocols (e.g. Task Management Functions and SMP in Serial
            Attached SCSI).

            This option is required by recent UDEV versions to properly
            access device serial numbers, etc.
            
            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by CONFIG_BLOCK, CONFIG_GENTOO_LINUX, 
            CONFIG_GENTOO_LINUX_UDEV and CONFIG_GENTOO_LINUX_INIT_SYSTEMD.
```
<h3>[ ]   Block layer SG support v4 helper lib</h3>
```none
Symbol:     CONFIG_BLK_DEV_BSGLIB

Help:       Subsystems will normally enable this if needed. Users will not
            normally need to manually enable this.
            
            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option to lower system overhead.
```
<h3>[ ]   Block layer data integrity support</h3>
```none
Symbol:     CONFIG_BLK_DEV_INTEGRITY

Help:       Some storage devices allow extra information to be
            stored/retrieved to help protect the data.  The block layer
            data integrity option provides hooks which can be used by
            filesystems to ensure better data integrity.

            Say yes here if you have a storage device that provides the
            T10/SCSI Data Integrity Field or the T13/ATA External Path
            Protection.  If in doubt, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option to lower system overhead.

            Include only if you have such storage devices for security
            purposes.
```
<h3>[ ]   Zoned block device support</h3>
```none
Symbol:     CONFIG_BLK_DEV_ZONED

Help:       Block layer zoned block device support. This option enables
            support for ZAC/ZBC host-managed and host-aware zoned block devices.

            Say yes here if you have a ZAC or ZBC storage device.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you don't have a ZAC or
            ZBC storage device.
```
<h3>[ ]   Block device command line partition parser</h3>
```none
Symbol:     CONFIG_BLK_CMDLINE_PARSER

Help:       Enabling this option allows you to specify the partition layout from
            the kernel boot args.  This is typically of use for embedded devices
            which don't otherwise have any standardized method for listing the
            partitions on a block device.

            See Documentation/block/cmdline-partition.txt for more information.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option to lower system overhead as it's
            intended for embedded devices.
```
<h3>[ ]   Enable support for block device writeback throttling</h3>
```none
Symbol:     CONFIG_BLK_WBT

Help:       Enabling this option enables the block layer to throttle buffered
            background writeback from the VM, making it more smooth and having
            less impact on foreground operations. The throttling is done
            dynamically on an algorithm loosely based on CoDel, factoring in
            the realtime performance of the disk.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it can impact the performance
            of your storage disks.

            Include this option along with CONFIG_BLK_WBT_SQ and CONFIG_BLK_WBT_MQ
            if you want to lower your system's latency and prevent lags when heavy
            IO operations are being performed.
```
<h3>[ ]   Block layer debugging information in debugfs</h3>
```none
Symbol:     CONFIG_BLK_DEBUG_FS

Help:       Include block layer debugging information in debugfs. This information
            is mostly useful for kernel developers, but it doesn't incur any cost
            at runtime.

            Unless you are building a kernel for a tiny system, you should
            say Y here.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's intended for debugging
            purposes.
```
<h3>[ ]   Logic for interfacing with Opal enabled SEDs</h3>
```none
Symbol:     CONFIG_BLK_SED_OPAL

Help:       Builds Logic for interfacing with Opal enabled controllers.
            Enabling this option enables users to setup/unlock/lock
            Locking ranges for SED devices using the Opal protocol.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your hard drive doesn't support Opal.
            
            You can check for opal support using sys-block/sedutil.
```
<h3>Partition Types  ---></h3>
<h3>[&ast;] Advanced partition selection</h3>
```none
Symbol:     CONFIG_PARTITION_ADVANCED

Help:       Say Y here if you would like to use hard disks under Linux which
            were partitioned under an operating system running on a different
            architecture than your Linux system.

            Note that the answer to this question won't directly affect the
            kernel: saying N will just cause the configurator to skip all
            the questions about foreign partitioning schemes.

            If unsure, say N.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this if you want to use mbr (msdos)
            or gpt partition or any other listed partition table.
```
<h3>[&ast;]   PC BIOS (MSDOS partition tables) support</h3>
```none
Symbol:     CONFIG_MSDOS_PARTITION

Help:       Say Y here.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option if your system has
            a BIOS and UEFI, and your UEFI implementation was buggy (especially on
            laptops from late 2013).

            You can safely exclude this option and include CONFIG_EFI_PARTITION instead
            if your system's UEFI implementation was working properly.
```
<h3>IO Schedulers  ---></h3>
<h3>Default I/O scheduler (CFQ)  ---></h3>
```none
Help:       Select the I/O scheduler which will be used by default for all
            block devices.
```
<h3><&ast;> CFQ I/O scheduler</h3>
```none
Symbol:     CONFIG_IOSCHED_CFQ

Help:       The CFQ I/O scheduler tries to distribute bandwidth equally
            among all processes in the system. It should provide a fair
            and low latency working environment, suitable for both desktop
            and server systems.

            This is the default I/O scheduler.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as CFQ is the best I/O scheduler for throughput and performance
            (especially on HDDs and alongside CFS on systems with a CPU that has
            more than 2 cores).
            
            This sure is going to cause a lot of flame wars. CFQ is my all 
            time favorite I/O scheduler. It steadily holds its place amongst
            other I/O schedulers including the newly added BFQ, kyber and mq-deadline
            schedulers.

            When I started with gentoo, my goal was primarly throughput,
            and boy using CFQ with a 100hz timer frequency boosted my 
            system's performance by 5-7% easily. Although I lagged like
            hell whenever I ran something intensive and the system was
            barely responsive (pasting something in vim when compiling
            was scary xD 1 line per 1 second), but it boosted my performance
            nicely.

            I started worrying about latency later on and decided to make the
            switch to the ck patchset. Used MuQSS instead of CFS and BFQ instead
            of CFQ and used 1000hz (then changed to 100hz since MuQSS changed to
            emulated tickless and frequency didn't matter much) and I lost
            my performance gain. I even lost 1-3% performance compared to
            normal use, which got me mad but meh I was happy with the latency.
            Started emerging chromium and my system froze unexpectedly at around
            60%. I was thinking that was because I had my other web browser open
            while emerging, so I tried emerging chromium again and went afk so
            only the emerge job was running. And it froze at 80%. So I returned
            to CFQ with 100hz timer frequency and couldn't be any happier!
            
            For normal desktop/laptop users, CFQ is the best I/O scheduler and it
            shines alongside CFS on systems with more than 2 cores; therefore, include 
            CONFIG_IOSCHED_CFQ and exclude everything else.
```
<h3>(X) CFQ</h3>
```none
Symbol:     CONFIG_DEFAULT_CFQ

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            as CFQ is the best I/O scheduler for throughput and performance
            (especially on HDDs and alongside CFS on systems with a CPU that has
            more than 2 cores).
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/09/14/linux%e5%86%85%e6%a0%b8%e9%85%8d%e7%bd%ae%e6%8c%87%e5%8d%97-enable-the-block-layer/" target="_blank">click here</a>.
