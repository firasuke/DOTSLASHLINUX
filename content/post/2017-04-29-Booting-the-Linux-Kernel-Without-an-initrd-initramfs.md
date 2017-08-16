+++
title = "Booting the Linux Kernel Without an initrd/initramfs"
slug = "booting the linux kernel without an initrd initramfs"
nick = "noinitrd"
date = "2017-04-29"
author = "Firas Khalil Khana"
imgsrc = "/img/noinitrd.png"
imgalt = "noinitrd"
categories = [ "popular" ]
+++
No, this is not a myth... It's not a legend... It's the truth and it's doable!
<br/>
<br/>
As you probably guessed from the title, in this article we'll uncover the truth behind booting the linux kernel without using an initrd or an initramfs!
<br/>
<br/>
Before we even start, booting without an initrd/initramfs might speed up your boot time by 100ms to 500ms. However, on some setups it may slow down your boot time by 800ms to 1sec!
<br/>
<br/>
Prerequisites:
<br/>
You should compile your own kernel.
<br/>
You should compile your own kernel.
<br/>
You should compile your own kernel.
<br/>
You should compile your own kernel.
<br/>
<br/>
I know this may sound like a nightmare for some of you, but that's why DOTSLASHLINUX was created. Plus don't worry the kernel configuration series is coming really soon, so look up to it!
<br/>
<br/>
Here's what we're going to do:
<br/>
1- Remove initrd/initramfs support from the linux kernel.
<br/>
2- Remove UUIDs from kernel command line parameters and <mark>/etc/fstab</mark>.
<br/>
3- Build all modules into the linux kernel.
<br/>
4- Tell the bootloader where root is located and what filesystem it's using.
<br/>
5- Reboot and get that rescue cd/usb since no one makes it in his 1st attempt :)
<br/>
<br/>
It doesn't really matter what distro you use (that is if you know that your distro isn't going to break with the slightest change), but for those who want to tag along with me then I'll be using my all time favorite distro Gentoo Linux. The version of the kernel's source files that I'm using is 4.10.13.
<br/>
<hr/>
<h3>1- Removing initrd/initramfs Support from the Linux Kernel</h3>
<br/>
If you're using Gentoo Linux, simply navigate to:
```bash
cd /usr/src/linux
```
<br/>
Now make sure you have <mark>ncurses</mark> installed and run:
```bash
make menuconfig
```
<br>
Now go to <mark>General Setup</mark> then search for <mark>CONFIG_BLK_DEV_INITRD</mark> and disable it:
```properties
  RCU Subsystem  --->
  < > Kernel .config support
  (12) Kernel log buffer size (16 => 64KB, 17 => 128KB)
  (12) CPU kernel log buffer size contribution (13 => 8 KB, 17 => 128KB)
  (12) Temporary per-CPU NMI log buffer size (12 => 4KB, 13 => 8KB)
  [ ] Memory placement aware NUMA scheduler
  -*- Control Group support  --->
  [ ] Checkpoint/restore support
  -*- Namespaces support  --->
  [ ] Automatic process group scheduling
  [ ] Enable deprecated sysfs features to support old userspace tools
  -*- Kernel->user space relay support (formerly relayfs)
  [ ] Initial RAM filesystem and RAM disk (initramfs/initrd) support
  Compiler optimization level (Optimize for performance)  --->
  [*] Configure standard kernel features (expert users)  --->
  [*] Enable bpf() system call
  -*- Use full shmem filesystem
  [*] Enable AIO support
  [*] Enable madvise/fadvise syscalls
  [ ] Enable userfaultfd() system call
  [*] Enable PCI quirk workarounds
  [*] Enable membarrier() system call
  [ ] Embedded system
  Kernel Performance Events And Counters  --->
  [*] Enable VM event counters for /proc/vmstat
  [ ] Enable SLUB debugging support
  [*] Disable heap randomization
  Choose SLAB allocator (SLUB (Unqueued Allocator))  --->
  [ ] SLAB freelist randomization
  [ ] SLUB per cpu partial cache
  [ ] Profiling support
  [ ] Kprobes
  [*] Optimize very unlikely/likely branches
  [ ]   Static key selftest
  [ ] GCC plugins  ----
  Stack Protector buffer overflow detection (None)  --->
  (28) Number of bits to use for ASLR of mmap base address
  [*] Use a virtually-mapped stack
  GCOV-based kernel profiling  --->
```
  <br/>
  <hr/>
<h3>2- Remove these UUIDs!</h3>
<br/>
Udev won't start until root is mounted, so you can't use UUIDs before that happens. Therefore, remove your UUID entries from your kernel command line parameters and from your <mark>/etc/fstab</mark>. Some may argue that these are filesystem UUIDs and are unrelated to udev and that what I mentioned previously is called PARTUUID, I won't disagree as that is correct, but for the sake of simplicity just follow this tutorial.
<br/>
<br/>
For example, if your root was on <mark>/dev/sda1</mark> and you had:
<br/>
<br/>
<mark>root=UUID="be9683c1-e42c-4a2b-18ad-97cc96b13ada</mark>
<br/>
<br/>
as a kernel command line parameter or inside your <mark>/etc/fstab</mark>, then simply change it to:
<br/>
<br/>
<mark>root=/dev/sda1</mark>
<br/>
<br/>
For example, I'm using LILO as my bootloader and here's my <mark>/etc/lilo.conf</mark>:
```properties,line-numbers
lba32
boot=/dev/sda
default=gentoo

image=/boot/vmlinuz-4.10.13-gentoo-DOTSLASHLINUX
	label=gentoo
	read-only
	root=/dev/sda1
	append="rootfstype=ext4"
```
<br/>
And here's my <mark>/etc/fstab</mark>:
```properties
# (fs)			(mountpoint)	(type)		(opts)		(dump/pass)
/dev/sda1		/		         ext4		 noatime		0 1
```
<br/>
<hr/>
<h3>3- Build All Modules into the Linux Kernel</h3>
<br/>
Things may get a little controversial here. I generally recommend building all modules into the linux kernel and disable loadable modules support since my setup doesn't require many modules (I only have support for the basic stuff I use). You can do that by disabling <mark>CONFIG_MODULES</mark>:
<br/>
```properties
  Gentoo Linux  --->
  [*] 64-bit kernel
  General setup  --->
  [ ] Enable loadable module support  ----
  [*] Enable the block layer  --->
  Processor type and features  --->
  Power management and ACPI options  --->
  Bus options (PCI etc.)  --->
  Executable file formats / Emulations  --->
  [*] Networking support  --->
  Device Drivers  --->
  Firmware Drivers  --->
  File systems  --->
  Kernel hacking  --->
  Security options  --->
  -*- Cryptographic API  --->
  [ ] Virtualization  ----
  Library routines  --->
```
  <br/>
However, if you were one of those guys who use tons of devices then you may leave the extra devices as loadable modules.
<br/>
<br/>
There are still some necessary modules that need to be build into the linux kernel to be able to boot without an initrd/initramfs. These include modules for filesystems and modules for block devices.
<br/>
<br/>
If you're using ext4, navigate to <mark>Filesystems</mark> and make sure that <mark>CONFIG_EXT4_FS</mark> is built-in:
```properties
  [ ] Second extended fs support
  [ ] The Extended 3 (ext3) filesystem
  [*] The Extended 4 (ext4) filesystem
  [ ]   Use ext4 for ext2 file systems
  [ ]   Ext4 POSIX Access Control Lists
  [ ]   Ext4 Security Labels
  [ ]   Ext4 Encryption
  [ ]   EXT4 debugging support
  [ ] JBD2 (ext4) debugging support
  [ ] Reiserfs support
  [ ] JFS filesystem support
  [ ] XFS filesystem support
  [ ] GFS2 file system support
  [ ] OCFS2 file system support
  [ ] Btrfs filesystem support
  [ ] NILFS2 file system support
  [ ] F2FS filesystem support
  [ ] Direct Access (DAX) support
  [ ] Enable filesystem export operations for block IO
  [*] Enable POSIX file locking API
  [ ]   Enable Mandatory file locking
  [ ] FS Encryption (Per-file encryption)
  [ ] Dnotify support
  [*] Inotify support for userspace
  [*] Filesystem wide access notification
  [ ] Quota support
  [ ] Kernel automounter version 4 support (also supports v3)
  [*] FUSE (Filesystem in Userspace) support
  [ ]   Character device in Userspace support
  [ ] Overlay filesystem support
  Caches  --->
  CD-ROM/DVD Filesystems  --->
  DOS/FAT/NT Filesystems  --->
  Pseudo filesystems  --->
  [ ] Miscellaneous filesystems  ----
  [ ] Network File Systems  ----
  -*- Native language support  ---
  [ ] Distributed Lock Manager (DLM)  ----
```
  <br/>
  Now you need to check what block devices are you using (to be more precise, the block device where your root resides on), find out its kernel module and mark it as built-in. This is simple, fire up a terminal emulator and type:
  ```bash
  lspci -kk
  ```
  <br/>
  In my case I'm using a Toshiba MQ01ABD100 which is a SATA HDD that uses the <mark>ahci</mark> kernel module:
  ```properties
  00:1f.2 SATA controller: Intel Corporation 8 Series/C220 Series Chipset Family 6-port SATA Controller 1 [AHCI mode] (rev 04)
	    Subsystem: Toshiba America Info Systems 8 Series/C220 Series Chipset Family 6-port SATA Controller 1 [AHCI mode]
	    Kernel driver in use: ahci
  ```
<br/>
I navigate to <mark>Device Drivers</mark> then to <mark>Serial ATA and Parallel ATA drivers (libata)</mark> and mark <mark>CONFIG_SATA_AHCI</mark> as built-in:
```properties
  --- Serial ATA and Parallel ATA drivers (libata)
  [ ]   Verbose ATA error reporting
  [*]   ATA ACPI Support
  [*]     SATA Zero Power Optical Disc Drive (ZPODD) support
  [ ]   SATA Port Multiplier support
  *** Controllers with non-SFF native interface ***
  [*]   AHCI SATA support
  [ ]   Platform AHCI SATA support
  [ ]   Initio 162x SATA support (Very Experimental)
  [ ]   ACard AHCI variant (ATP 8620)
  [ ]   Silicon Image 3124/3132 SATA support
  [ ]   ATA SFF support (for legacy IDE and PATA)
```
<br/>
<hr/>
<h3>4- Notifying the Bootloader of the changes</h3>
Now we need to tell our bootloader the info that the initrd/initramfs would tell to the kernel. That is the location of root and the filesystem of root.
<br/>
<br/>
If you're using grub, fire up your favorite editor and edit <mark>/etc/default/grub</mark>:
```bash
nano /etc/default/grub
```
```properties,line-numbers
# Copyright 1999-2015 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
#
# To populate all changes in this file you need to regenerate your
# grub configuration file afterwards:
#     'grub2-mkconfig -o /boot/grub/grub.cfg'
#
# See the grub info page for documentation on possible variables and
# their associated values.

GRUB_DISTRIBUTOR="Gentoo"

# Default menu entry
GRUB_DEFAULT=0

# Boot the default entry this many seconds after the menu is displayed
GRUB_TIMEOUT=0
#GRUB_TIMEOUT_STYLE=menu

# Append parameters to the linux kernel command line
GRUB_CMDLINE_LINUX="root=/dev/sda1 rootfstype=ext4"
#
# Examples:
#
# Boot with network interface renaming disabled
# GRUB_CMDLINE_LINUX="net.ifnames=0"
#
# Boot with systemd instead of sysvinit (openrc)
# GRUB_CMDLINE_LINUX="init=/usr/lib/systemd/systemd"

# Append parameters to the linux kernel command line for non-recovery entries
#GRUB_CMDLINE_LINUX_DEFAULT=""

# Uncomment to disable graphical terminal (grub-pc only)
#GRUB_TERMINAL=console

# The resolution used on graphical terminal.
# Note that you can use only modes which your graphic card supports via VBE.
# You can see them in real GRUB with the command `vbeinfo'.
#GRUB_GFXMODE=640x480

# Set to 'text' to force the Linux kernel to boot in normal text
# mode, 'keep' to preserve the graphics mode set using
# 'GRUB_GFXMODE', 'WIDTHxHEIGHT'['xDEPTH'] to set a particular
# graphics mode, or a sequence of these separated by commas or
# semicolons to try several modes in sequence.
#GRUB_GFXPAYLOAD_LINUX=

# Path to theme spec txt file.
# The starfield is by default provided with use truetype.
# NOTE: when enabling custom theme, ensure you have required font/etc.
#GRUB_THEME="/boot/grub/themes/starfield/theme.txt"

# Background image used on graphical terminal.
# Can be in various bitmap formats.
#GRUB_BACKGROUND="/boot/grub/mybackground.png"

# Uncomment if you don't want GRUB to pass "root=UUID=xxx" parameter to kernel
#GRUB_DISABLE_LINUX_UUID=true

# Uncomment to disable generation of recovery mode menu entries
#GRUB_DISABLE_RECOVERY=true

# Uncomment to disable generation of the submenu and put all choices on
# the top-level menu.
# Besides the visual affect of no sub menu, this makes navigation of the
# menu easier for a user who can't see the screen.
#GRUB_DISABLE_SUBMENU=y

# Uncomment to play a tone when the main menu is displayed.
# This is useful, for example, to allow users who can't see the screen
# to know when they can make a choice on the menu.
#GRUB_INIT_TUNE="60 800 1"
```
<br/>
However, if you're lucky enough to use LILO (like me xD), then the following configuration file will do:
```properties,line-numbers
lba32
boot=/dev/sda
default=gentoo

image=/boot/vmlinuz-4.10.13-gentoo-DOTSLASHLINUX
	label=gentoo
	read-only
	root=/dev/sda1
	append="rootfstype=ext4"
```
<br/>
This'll also work as well:
```properties,line-numbers
lba32
boot=/dev/sda
default=gentoo

image=/boot/vmlinuz-4.10.13-gentoo-DOTSLASHLINUX
	label=gentoo
	read-only
	append="root=/dev/sda1 rootfstype=ext4"
```
<br/>
You may have to delete your initd/initramfs from your <mark>/boot</mark> and the initrd/initramfs entries in your bootloader's configuration files. Don't forget to recompile your kernel and to update your bootloader (if you're using GRUB2 or LILO) before rebooting.
<br/>
<hr/>
<h3>Conclusion</h3>
Booting without an initrd/initramfs is 100% doable so don't think it's impossible. You may fail on your 1st attempt but don't give up, just keep on trying different combinations every time you compile your kernel and you should be good to go.
<br/>
<br/>
I'm using Gentoo Linux and can confirm that you can achieve a bootable kernel without initrd/initramfs. If your kernel is panicking then debug the problem and keep trying until it works. If you have a question as well then lemme know in the comments section below.
<br/>
