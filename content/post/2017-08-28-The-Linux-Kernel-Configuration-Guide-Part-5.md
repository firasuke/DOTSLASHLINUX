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

Reason:     This option is mandatory for using block devices. You won't be able
            to mount (or even use) your disks or any type of SCSI/USB storage and
            some filesystems will become unavailable as well.

            It's also required by CONFIG_GENTOO_LINUX, CONFIG_GENTOO_LINUX_UDEV
            and CONFIG_GENTOO_LINUX_INIT_SYSTEMD.

            You almost always have to include this option in your kernel unless
            you're building it for a custom embedded device.
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

Reason:     It's required by CONFIG_BLOCK, CONFIG_GENTOO_LINUX, 
            CONFIG_GENTOO_LINUX_UDEV and CONFIG_GENTOO_LINUX_INIT_SYSTEMD.

            Generally, you'd want to include this option if CONFIG_BLOCK is
            included as well.
```
<h3>[ ]   Block layer SG support v4 helper lib</h3>
```none
Symbol:     CONFIG_BLK_DEV_BSGLIB

Help:       Subsystems will normally enable this if needed. Users will not
            normally need to manually enable this.
            
            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     I excluded this option because I don't need it.
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

Reason:     I excluded this option as well because I don't need it.

            You can include this for better protected data and a more
            secure system.
```
<h3>[ ]   Zoned block device support</h3>
```none
Symbol:     CONFIG_BLK_DEV_ZONED

Help:       Block layer zoned block device support. This option enables
            support for ZAC/ZBC host-managed and host-aware zoned block devices.

            Say yes here if you have a ZAC or ZBC storage device.

Type:       boolean

Choice:     excluded [ ]

Reason:     I excluded this option as I don't have a ZAC or ZBC storage device.
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

Reason:     Again I've excluded this option as I'm not building the kernel for an
            embedded device.
```
<h3>[&ast;]   Enable support for block device writeback throttling</h3>
```none
Symbol:     CONFIG_BLK_WBT

Help:       Enabling this option enables the block layer to throttle buffered
            background writeback from the VM, making it more smooth and having
            less impact on foreground operations. The throttling is done
            dynamically on an algorithm loosely based on CoDel, factoring in
            the realtime performance of the disk.

Type:       boolean

Choice:     built-in [*]

Reason:     I can't stress enough how important this feature is. Ever noticed 
            your system suddenly lagged when doing extreme read/write operations
            (copying big files for example) and the mouse cursor started lagging,
            well include this option and CONFIG_BLK_WBT_SQ and CONFIG_BLK_WBT_MQ
            and hopefully your system won't lag when heavy I/O operations are
            running.
```
<h3>[&ast;]     Single queue writeback throttling</h3>
```none
Symbol:     CONFIG_BLK_WBT_SQ

Help:       Enable writeback throttling by default on legacy single queue devices

Type:       boolean

Choice:     built-in [*]

Reason:     I included this option because it's useful with CONFIG_BLK_WBT_MQ
            to prevent lagging when heavy I/O operations are running.
```
<h3>[&ast;]     Multiqueue writeback throttling (NEW)</h3>
```none
Symbol:     CONFIG_BLK_WBT_MQ

Help:       Enable writeback throttling by default on multiqueue devices.
            Multiqueue currently doesn't have support for IO scheduling,
            enabling this option is recommended.

Type:       boolean

Choice:     built-in [*]

Reason:     I included this option because it's useful with CONFIG_BLK_WBT_SQ
            to prevent lagging when heavy I/O operations are running.
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

Reason:     I excluded this option because it's a debugging option that I didn't
            need.
```
<h3>[ ]   Logic for interfacing with Opal enabled SEDs</h3>
```none
Symbol:     CONFIG_BLK_SED_OPAL

Help:       Builds Logic for interfacing with Opal enabled controllers.
            Enabling this option enables users to setup/unlock/lock
            Locking ranges for SED devices using the Opal protocol.

Type:       boolean

Choice:     excluded [ ]

Reason:     I excluded this option as my hard drive doesn't support Opal.
            
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

Reason:     Include this if you want to user mbr (msdos) or gpt partition
            or any other listed partition table.
```
<h3>[&ast;]   PC BIOS (MSDOS partition tables) support</h3>
```none
Symbol:     CONFIG_MSDOS_PARTITION

Help:       Say Y here.

Type:       boolean

Choice:     built-in [*]

Reason:     I excluded every other partition table except mbr(msdos).
            
            Since my laptop is from late 2013, my motherboard's has bios
            support and basic efi support. The efi is really buggy on my 
            laptop as it gives me a 5 sec "medium not found" until it boots
            normally.
```
<h3>IO Schedulers  ---></h3>
<h3>Default I/O scheduler (BFQ)  ---></h3>
```none
Help:       Select the I/O scheduler which will be used by default for all
            block devices.
```
<h3>(X) BFQ</h3>
```none
Symbol:     DEFAULT_BFQ

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in (X)

Reason:     If low latency and maximum responsiveness is what you want
            go for MuQSS/BFQ.

            If you want maximum throughput (performance) and you're on a 
            multicore (or maybe multicpu system) then CFS/CFQ is what you
            need.
```
<h3><*> BFQ I/O scheduler</h3>
```none
Symbol:     CONFIG_IOSCHED_BFQ

Help:       
            BFQ I/O scheduler for BLK-MQ. BFQ distributes the bandwidth of
            of the device among all processes according to their weights,
            regardless of the device parameters and with any workload. It
            also guarantees a low latency to interactive and soft
            real-time applications.  Details in
            Documentation/block/bfq-iosched.txt 

Type:       tristate

Choice:     built-in <*>

Reason:     Wow this is going to cause a lot of flame wars. CFQ is my all 
            time favorite I/O scheduler. It steadily holds its place amongst
            other I/O schedulers including the new kyber and mq-deadline
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
            to CFQ with 1000hz timer frequency and couldn't be any happier!

            But recently I switched again to MuQSS/BFQ with 100Hz timer frequency
            and things are going pretty well latency wise. I can browse the web
            with ease and do another tasks while waiting for my 9 job emerge to
            finish.
            
            For normal desktop/laptop users, CFQ is the best I/O scheduler and it
            shines alongside CFS on systems with more than 2 cores; therefore, include 
            CONFIG_IOSCHED_CFQ and exclude everything else.

            However, if you're on a system like gentoo and you do a lot of compiling
            then responsiveness is a must and BFQ works perfectly for that. So simply
            include CONFIG_IOSCHED_BFQ and exclude everything else.
```
