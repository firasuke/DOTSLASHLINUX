+++
title = "The Linux Kernel Configuration Guide Part 13"
slug = "the linux kernel configuration guide part 13"
nick = "kernel13"
date = "2017-09-13"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel13.png"
imgalt = "kernel13"
categories = [ "kernel" ]
+++
<h3>File systems  ---></h3>
<h3><&ast;> XFS filesystem support</h3>
```properties
Symbol:     CONFIG_XFS_FS

Help:       XFS is a high performance journaling filesystem which originated
            on the SGI IRIX platform.  It is completely multi-threaded, can
            support large files and large filesystems, extended attributes,
            variable block sizes, is extent based, and makes extensive use of
            Btrees (directories, extents, free space) to aid both performance
            and scalability.

            Refer to the documentation at <http://oss.sgi.com/projects/xfs/>
            for complete details.  This implementation is on-disk compatible
            with the IRIX version of XFS.

            To compile this file system support as a module, choose M here: the
            module will be called xfs.  Be aware, however, that if the file
            system of your root partition is compiled as a module, you'll need
            to use an initial ramdisk (initrd) to boot.

Type:       tristate

Choice:     built-in <*>

Reason:     For a basic system using CONFIG_EXT4_FS is advised; however, if you
            wanted a change of pace you can try CONFIG_XFS_FS instead.

            Do not build this option as a module [M] as it'll result in an unbootable
            system if you're not using an initrd.
```
<h3>[&ast;] Enable POSIX file locking API</h3>
```properties
Symbol:     CONFIG_FILE_LOCKING

Help:       This option enables standard file locking support, required
            for filesystems like NFS and for the flock() system
            call. Disabling this option saves about 11k.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as excluding it may result in a read-only root partition.
```
<h3>[&ast;] Inotify support for userspace</h3>
```properties
Symbol:     CONFIG_INOTIFY_USER

Help:       Say Y here to enable inotify support for userspace, including the
            associated system calls.  Inotify allows monitoring of both files and
            directories via a single open fd.  Events are read from the file
            descriptor, which is also select()- and poll()-able.
            Inotify fixes numerous shortcomings in dnotify and introduces several
            new features including multiple file events, one-shot support, and
            unmount notification.

            For more information, see <file:Documentation/filesystems/inotify.txt>

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by several important options including CONFIG_GENTOO_LINUX,
            CONFIG_GENTOO_LINUX_UDEV and CONFIG_GENTOO_LINUX_INIT_SYSTEMD.

            It's also required by several applications.
```
<h3><&ast;> FUSE (Filesystem in Userspace) support</h3>
```properties
Symbol:     CONFIG_FUSE_FS

Help:       With FUSE it is possible to implement a fully functional filesystem
            in a userspace program.

            There's also a companion library: libfuse2.  This library is available
            from the FUSE homepage:
            <http://fuse.sourceforge.net/>
            although chances are your distribution already has that library
            installed if you've installed the "fuse" package itself.

            See <file:Documentation/filesystems/fuse.txt> for more information.
            See <file:Documentation/Changes> for needed library/utility version.

            If you want to develop a userspace FS, or if you want to use
            a filesystem based on FUSE, answer Y or M.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you want to use MTP to mount the storage of your portable devices
            (mobile phones, cameras ...etc) in order to share files.

            It's also recommended by the Gentoo wiki in order to enable full
            read and write capabilities for NTFS in Linux.
```
<h3>CD-ROM/DVD Filesystems  ---></h3>
<h3><&ast;> ISO 9660 CDROM file system support</h3>
```properties
Symbol:     CONFIG_ISO9960_FS

Help:       This is the standard file system used on CD-ROMs.  It was previously
            known as "High Sierra File System" and is called "hsfs" on other
            Unix systems.  The so-called Rock-Ridge extensions which allow for
            long Unix filenames and symbolic links are also supported by this
            driver.  If you have a CD-ROM drive and want to do more with it than
            just listen to audio CDs and watch its LEDs, say Y (and read
            <file:Documentation/filesystems/isofs.txt> and the CD-ROM-HOWTO,
            available from <http://www.tldp.org/docs.html#howto>), thereby
            enlarging your kernel by about 27 KB; otherwise say N.

            To compile this file system support as a module, choose M here: the
            module will be called isofs.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel as it's
            required to read and write on the majority of optical discs and it's 
            recommended as well by the Gentoo Wiki.
```
<h3>[&ast;]   Microsoft Joliet CDROM extensions</h3>
```properties
Symbol:     CONFIG_JOLIET

Help:       Joliet is a Microsoft extension for the ISO 9660 CD-ROM file system
            which allows for long filenames in unicode format (unicode is the
            new 16 bit character code, successor to ASCII, which encodes the
            characters of almost all languages of the world; see
            <http://www.unicode.org/> for more information).  Say Y here if you
            want to be able to read Joliet CD-ROMs under Linux.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel as it's
            required to read and write on optical discs with long filenames and it's 
            recommended as well by the Gentoo Wiki.
```
<h3>[&ast;]   Transparent decompression extension</h3>
```properties
Symbol:     CONFIG_ZISOFS

Help:       This is a Linux-specific extension to RockRidge which lets you store
            data in compressed form on a CD-ROM and have it transparently
            decompressed when the CD-ROM is accessed.  See
            <http://www.kernel.org/pub/linux/utils/fs/zisofs/> for the tools
            necessary to create such a filesystem.  Say Y here if you want to be
            able to read such compressed CD-ROMs.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel as it's
            wanted to store more data on your discs via compression and it's 
            recommended as well by the Gentoo Wiki.
```
<h3><&ast;> UDF file system support</h3>
```properties
Symbol:     CONFIG_UDF_FS

Help:       This is a file system used on some CD-ROMs and DVDs. Since the
            file system is supported by multiple operating systems and is more
            compatible with standard unix file systems, it is also suitable for
            removable USB disks. Say Y if you intend to mount DVD discs or CDRW's
            written in packet mode, or if you want to use UDF for removable USB
            disks. Please read <file:Documentation/filesystems/udf.txt>.

            To compile this file system support as a module, choose M here: the
            module will be called udf.

            If unsure, say N.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel as it's
            required to read and write on rewritable optical discs and it's 
            recommended as well by the Gentoo Wiki.

            It allows rewritable discs to behave more like removable USB disks.
```
<h3>DOS/FAT/NT Filesystems  ---></h3>
<h3><&ast;> VFAT (Windows-95) fs support </h3>
```properties
Symbol:     CONFIG_VFAT_FS

Help:       This option provides support for normal Windows file systems with
            long filenames.  That includes non-compressed FAT-based file systems
            used by Windows 95, Windows 98, Windows NT 4.0, and the Unix
            programs from the mtools package.

            The VFAT support enlarges your kernel by about 10 KB and it only
            works if you said Y to the "DOS FAT fs support" above.  Please read
            the file <file:Documentation/filesystems/vfat.txt> for details.  If
            unsure, say Y.

            To compile this as a module, choose M here: the module will be called
            vfat.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're ever going to work with a FAT filesystem (common examples
            include attaching your Windows friend's FAT formatted USB on your Linux
            box).

            It's also recommended by the Gentoo wiki.
```
<h3>(437) Default codepage for FAT</h3>
```properties
Symbol:     CONFIG_FAT_DEFAULT_CODEPAGE

Help:       This option should be set to the codepage of your FAT filesystems.
            It can be overridden with the "codepage" mount option.
            See <file:Documentation/filesystems/vfat.txt> for more information.

Type:       integer

Choice:     (437) default

Reason:     You can safely leave the value of this option set to the default value
            of (437) as recommended by the Gentoo wiki.
```
<h3>(iso8859-1) Default iocharset for FAT</h3>
```properties
Symbol:     CONFIG_FAT_DEFAULT_IOCHARSET

Help:       Set this to the default input/output character set you'd
            like FAT to use. It should probably match the character set
            that most of your FAT filesystems use, and can be overridden
            with the "iocharset" mount option for FAT filesystems.
            Note that "utf8" is not recommended for FAT filesystems.
            If unsure, you shouldn't set "utf8" here - select the next option
            instead if you would like to use UTF-8 encoded file names by default.
            See <file:Documentation/filesystems/vfat.txt> for more information.

            Enable any character sets you need in File Systems/Native Language
            Support.

Type:       string

Choice:     (iso8859-1) default

Reason:     You can safely leave the value of this option set to the default value
            of (iso8859-1) as recommended by the Gentoo wiki.
```
<h3>[&ast;]   Enable FAT UTF-8 option by default</h3>
```properties
Symbol:     CONFIG_FAT_DEFAULT_UTF8

Help:       Set this if you would like to have "utf8" mount option set
            by default when mounting FAT filesystems.

            Even if you say Y here can always disable UTF-8 for
            particular mount by adding "utf8=0" to mount options.

            Say Y if you use UTF-8 encoding for file names, N otherwise.

            See <file:Documentation/filesystems/vfat.txt> for more information.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel as
            it'll save you the hassle of specifying "utf8" as a mount option everytime
            you mount a FAT filesystem.
```
<h3><&ast;> NTFS file system support</h3>
```properties
Symbol:     CONFIG_NTFS_FS

Help:       NTFS is the file system of Microsoft Windows NT, 2000, XP and 2003.

            Saying Y or M here enables read support.  There is partial, but
            safe, write support available.  For write support you must also
            say Y to "NTFS write support" below.

            There are also a number of user-space tools available, called
            ntfsprogs.  These include ntfsundelete and ntfsresize, that work
            without NTFS support enabled in the kernel.

            This is a rewrite from scratch of Linux NTFS support and replaced
            the old NTFS code starting with Linux 2.5.11.  A backport to
            the Linux 2.4 kernel series is separately available as a patch
            from the project web site.

            For more information see <file:Documentation/filesystems/ntfs.txt>
            and <http://www.linux-ntfs.org/>.

            To compile this file system support as a module, choose M here: the
            module will be called ntfs.

            If you are not using Windows NT, 2000, XP or 2003 in addition to
            Linux on your computer it is safe to say N.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're ever going to work with a NTFS filesystem (common examples
            include attaching your Windows friend's NTFS formatted USB or external
            hard drive on your Linux box).

            It's also recommended by the Gentoo wiki.
```
<h3>[&ast;]   NTFS write support</h3>
```properties
Symbol:     CONFIG_NTFS_RW

Help:       This enables the partial, but safe, write support in the NTFS driver.

            The only supported operation is overwriting existing files, without
            changing the file length.  No file or directory creation, deletion or
            renaming is possible.  Note only non-resident files can be written to
            so you may find that some very small files (<500 bytes or so) cannot
            be written to.

            While we cannot guarantee that it will not damage any data, we have
            so far not received a single report where the driver would have
            damaged someones data so we assume it is perfectly safe to use.

            Note:  While write support is safe in this version (a rewrite from
            scratch of the NTFS support), it should be noted that the old NTFS
            write support, included in Linux 2.5.10 and before (since 1997),
            is not safe.

            This is currently useful with TopologiLinux.  TopologiLinux is run
            on top of any DOS/Microsoft Windows system without partitioning your
            hard disk.  Unlike other Linux distributions TopologiLinux does not
            need its own partition.  For more information see
            <http://topologi-linux.sourceforge.net/>

            It is perfectly safe to say N here.

Type:       boolean

Choice:     built-in [*]

Reason:     You can safely exclude this option as you probably won't need it,
            and the current support it provides is far from perfect.

            Hopefully, when microsoft releases the internals of NTFS (which is
            unlikely), including this option should help you install Linux
            on your NTFS hard drive.

            The Gentoo wiki recommends that you include this option though
            alongside CONFIG_NTFS_FS.
```
<h3>Pseudo filesystems  ---></h3>
<h3>[&ast;] /proc file system support</h3>
```properties
Symbol:     CONFIG_PROC_FS

Help:       This is a virtual file system providing information about the status
            of the system. "Virtual" means that it doesn't take up any space on
            your hard disk: the files are created on the fly by the kernel when
            you try to access them. Also, you cannot read the files with older
            version of the program less: you need to use more or cat.

            It's totally cool; for example, "cat /proc/interrupts" gives
            information about what the different IRQs are used for at the moment
            (there is a small number of Interrupt ReQuest lines in your computer
            that are used by the attached devices to gain the CPU's attention --
            often a source of trouble if two devices are mistakenly configured
            to use the same IRQ). The program procinfo to display some
            information about your system gathered from the /proc file system.

            Before you can use the /proc file system, it has to be mounted,
            meaning it has to be given a location in the directory hierarchy.
            That location should be /proc. A command such as "mount -t proc proc
            /proc" or the equivalent line in /etc/fstab does the job.

            The /proc file system is explained in the file
            <file:Documentation/filesystems/proc.txt> and on the proc(5) manpage
            ("man 5 proc").

            This option will enlarge your kernel by about 67 KB. Several
            programs depend on this, so everyone should say Y here.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel as
            it's required by several important options including CONFIG_GENTOO_LINUX,
            CONFIG_GENTOO_LINUX_UDEV and CONFIG_GENTOO_LINUX_INIT_SYSTEMD and by
            several drivers as well.
```
<h3>[&ast;]   Sysctl support (/proc/sys)</h3>
```properties
Symbol:     CONFIG_PROC_SYSCTL

Help:       The sysctl interface provides a means of dynamically changing
            certain kernel parameters and variables on the fly without requiring
            a recompile of the kernel or reboot of the system.  The primary
            interface is through /proc/sys.  If you say Y here a tree of
            modifiable sysctl entries will be generated beneath the
            /proc/sys directory. They are explained in the files
            in <file:Documentation/sysctl/>.  Note that enabling this
            option will enlarge the kernel by at least 8 KB.

            As it is generally a good thing, you should say Y here unless
            building a kernel for install/rescue disks or your system is very
            limited in memory.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel as
            it may be used by some other options like I915 and SCSI.
```
<h3>[&ast;] sysfs file system support</h3>
```properties
Symbol:     CONFIG_SYSFS

Help:       The sysfs filesystem is a virtual filesystem that the kernel uses to
            export internal kernel objects, their attributes, and their
            relationships to one another.

            Users can use sysfs to ascertain useful information about the running
            kernel, such as the devices the kernel has discovered on each bus and
            which driver each is bound to. sysfs can also be used to tune devices
            and other kernel subsystems.

            Some system agents rely on the information in sysfs to operate.
            /sbin/hotplug uses device and object attributes in sysfs to assist in
            delegating policy decisions, like persistently naming devices.

            sysfs is currently used by the block subsystem to mount the root
            partition.  If sysfs is disabled you must specify the boot device on
            the kernel boot command line via its major and minor numbers.  For
            example, "root=03:01" for /dev/hda1.

            Designers of embedded systems may wish to say N here to conserve space.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as it provides an interface to kernel objects. It's also required by 
            several important options including CONFIG_GENTOO_LINUX,
            CONFIG_GENTOO_LINUX_UDEV and CONFIG_GENTOO_LINUX_INIT_SYSTEMD.

            CONFIG_KSM may rely on this option as well.
```
<h3>-&ast;- Tmpfs virtual memory file system support (former shm fs)</h3>
```properties
Symbol:     CONFIG_TMPFS

Help:       Tmpfs is a file system which keeps all files in virtual memory.

            Everything in tmpfs is temporary in the sense that no files will be
            created on your hard drive. The files live in memory and swap
            space. If you unmount a tmpfs instance, everything stored therein is
            lost.

            See <file:Documentation/filesystems/tmpfs.txt> for details.

Type:       boolean

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            as it provides an interface to kernel objects (that is if it isn't
            already forcibly included by many important options including CONFIG_GENTOO_LINUX,
            CONFIG_GENTOO_LINUX_UDEV, CONFIG_GENTOO_LINUX_INIT_SYSTEMD, CONFIG_DRM_I915,
            CONFIG_X86, CONFIG_PCI ...etc

            It's also recommended by the Gentoo wiki.
```
<h3>-&ast;- Native language support  ---></h3>
```properties
Symbol:     CONFIG_NLS

Help:       The base Native Language Support. A number of filesystems
            depend on it (e.g. FAT, JOLIET, NT, BEOS filesystems), as well
            as the ability of some filesystems to use native languages
            (NCP, SMB).

            If unsure, say Y.

            To compile this code as a module, choose M here: the module
            will be called nls_base.

Type:       tristate

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            as it's required for several filesystems (mainly FAT) to work properly.
```
<h3>(utf8) Default NLS Option</h3>
```properties
Symbol:     CONFIG_NLS_DEFAULT

Help:       The default NLS used when mounting file system. Note, that this is
            the NLS used by your console, not the NLS used by a specific file
            system (if different) to store data (filenames) on a disk.
            Currently, the valid values are:
            big5, cp437, cp737, cp775, cp850, cp852, cp855, cp857, cp860, cp861,
            cp862, cp863, cp864, cp865, cp866, cp869, cp874, cp932, cp936,
            cp949, cp950, cp1251, cp1255, euc-jp, euc-kr, gb2312, iso8859-1,
            iso8859-2, iso8859-3, iso8859-4, iso8859-5, iso8859-6, iso8859-7,
            iso8859-8, iso8859-9, iso8859-13, iso8859-14, iso8859-15,
            koi8-r, koi8-ru, koi8-u, sjis, tis-620, macroman, utf8.
            If you specify a wrong value, it will use the built-in NLS;
            compatible with iso8859-1.

            If unsure, specify it as "iso8859-1".

Type:       string

Choice:     (utf8) custom

Reason:     It's highly recommended that you set the value of this option to
            (utf8) as it's more suited for multilanguage environments.

            It's also recommended by the Gentoo wiki.
```
<h3><&ast;>   Codepage 437 (United States, Canada)</h3>
```properties
Symbol:     CONFIG_NLS_CODEPAGE_437

Help:       The Microsoft FAT file system family can deal with filenames in
            native language character sets. These character sets are stored
            in so-called DOS codepages. You need to include the appropriate
            codepage if you want to be able to read/write these filenames on
            DOS/Windows partitions correctly. This does apply to the filenames
            only, not to the file contents. You can include several codepages;
            say Y here if you want to include the DOS codepage that is used in
            the United States and parts of Canada. This is recommended.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required to read and write filenames using native language
            character sets on DOS/Windows partitions.
            
            It's also recommended by the Gentoo wiki.
```
<h3><&ast;>   NLS ISO 8859-1  (Latin 1; Western European Languages)</h3>
```properties
Symbol:     CONFIG_NLS_ISO8859_1

Help:       If you want to display filenames with native language characters
            from the Microsoft FAT file system family or from JOLIET CD-ROMs
            correctly on the screen, you need to include the appropriate
            input/output character sets. Say Y here for the Latin 1 character
            set, which covers most West European languages such as Albanian,
            Catalan, Danish, Dutch, English, Faeroese, Finnish, French, German,
            Galician, Irish, Icelandic, Italian, Norwegian, Portuguese, Spanish,
            and Swedish. It is also the default for the US. If unsure, say Y.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required to read and write filenames with native language
            characters on FAT and JOLIET filesystems.
            
            It's also recommended by the Gentoo wiki.
```
<h3><&ast;>   NLS UTF-8</h3>
```properties
Symbol:     CONFIG_NLS_UTF8

Help:       If you want to display filenames with native language characters
            from the Microsoft FAT file system family or from JOLIET CD-ROMs
            correctly on the screen, you need to include the appropriate
            input/output character sets. Say Y here for the UTF-8 encoding of
            the Unicode/ISO9646 universal character set.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required to read and write filenames with native language
            characters on FAT and JOLIET filesystems.
            
            It's also recommended by the Gentoo wiki.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/2017/09/21/linux%e5%86%85%e6%a0%b8%e9%85%8d%e7%bd%ae%e6%8c%87%e5%8d%97-firmware-drivers%e5%92%8cfile-systems/" target="_blank">click here</a>.
