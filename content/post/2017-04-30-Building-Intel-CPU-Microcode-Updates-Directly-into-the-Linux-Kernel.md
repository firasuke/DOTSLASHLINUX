+++
title = "Building Intel CPU Microcode Updates Directly into the Linux Kernel"
slug = "building intel cpu microcode updates directly into the linux kernel"
nick = "microcode"
date = "2017-04-30"
author = "Firas Khalil Khana"
imgsrc = "/img/microcode.png"
imgalt = "microcode"
categories = [ "popular" ]
+++
<mark>DOTSLASHLINUX is proud to say that part of this article was added to the <a href="https://wiki.gentoo.org/wiki/Intel_microcode#Kernel_3" target="_blank">Gentoo Wiki</a></mark>
<br/>
<br/>
To achieve our dream of booting the kernel without an initrd/initramfs we have to build our CPU's microcode updates directly into the linux kernel (removing any need for an initrd/initramfs). This is doable, but due to lack of documentation on the process, one may find this thing hard to do. Yes, I know, that's why DOTSLASHLINUX was created xD.
<br/>
<br/>
For those who'd like to know, I'm using Gentoo Linux. Any distro will be fine though, as long as you can access your kernel's source files. The version of the kernel's source files that I'm using is 4.10.13.
<hr/>

<h3>1. Getting Ready</h3>
<br/>
Fire up your favorite terminal emulator, navigate to your kernel's source folder:
```bash
cd /usr/src/linux
```
<br/>
Now make sure you have <mark>ncurses</mark> installed and type in:
```bash
make menuconfig
```
<br/>
If you don't have ncurses installed you can use:
<br/>
<ul>
<li><mark>make gconfig</mark> if you had <mark>GTK</mark> installed</li>
<li><mark>make xconfig</mark> if you had <mark>Qt</mark> installed</li>
</ul>
<br/>
I personally prefer <mark>make menuconfig</mark> as it's better maintained and can be accessed from your terminal emulator or from a TTY. But as long as you can store your changes whenever you want, and go back and forth with the configuration menus then you're good to go.
<br/>
<hr/>
<h3>2. Enable CPU Microcode Loading Support</h3>
<br/>
Navigate to <mark>Processor type and features</mark> and mark <mark>CONFIG_MICROCODE</mark> as built-in. You'll receive two options now "Blue vs Red" microcode loading support or should I say <mark>CONFIG_MICROCODE_INTEL</mark> vs <mark>CONFIG_MICROCODE_AMD</mark>.
```none
  [*] DMA memory allocation support
  [*] Symmetric multi-processing support
  [ ] Enable MPS table
  [ ] Intel Resource Director Technology Allocation support
  [ ] Support for extended (non-PC) x86 platforms
  [ ] Intel Low Power Subsystem Support
  [ ] AMD ACPI2Platform devices support
  < > Intel SoC IOSF Sideband support for SoC platforms
  [ ] Single-depth WCHAN output
  [ ] Linux guest support  ----
  Processor family (Core 2/newer Xeon)  --->
  [*] Supported processor vendors  --->
  [*] Enable DMI scanning
  [ ] IBM Calgary IOMMU support
  [ ] Enable Maximum number of SMP Processors and NUMA Nodes
  (8) Maximum number of CPUs
  [*] SMT (Hyperthreading) scheduler support
  [*] Multi-core scheduler support
  [*]   CPU core priorities scheduler support
  Preemption Model (No Forced Preemption (Server))  --->
  [ ] Reroute for broken boot IRQs
  [*] Machine Check / overheating reporting
  [*]   Intel MCE features
  < > Machine check injector support
  Performance monitoring  --->
  [ ] Enable support for 16-bit segments
  [*] Enable vsyscall emulation
  < > Dell i8k legacy laptop support
  [*] CPU microcode loading support
  [*]   Intel microcode loading support
  [ ]   AMD microcode loading support
  <*> /dev/cpu/*/msr - Model-specific register support
  <*> /dev/cpu/*/cpuid - CPU information support
  [*] Numa Memory Allocation and Scheduler Support
  [ ]   Old style AMD Opteron NUMA detection
  [*]   ACPI NUMA detection
  [ ]   NUMA emulation
  (2) Maximum NUMA Nodes (as a power of 2)
  Memory model (Sparse Memory)  --->
```
<br/>
<hr/>
<h3>3- Installing Intel CPU Microcode Updates</h3>
<br/>
Gentoo Linux:
```none
emerge --sync && emerge -av sys-firmware/intel-microcode
```
<br/>
Void Linux:
```none
xbps-install -Su && xbps-install -S intel-ucode
```
<br/>
Arch Linux:
```none
pacman -Syu intel-ucode
```
<br/>
Now hold on, don't follow your wiki's guide on how to build microcode updates with an initrd/initramfs, remember we're not using an initrd/initramfs here.
<br/>
<br/>
Instead, we're going to check to see if <mark>/lib/firmware</mark> was populated with intel's CPUs microcode update files:
```bash
ls -l /lib/firmware
```
```bash
drwxr-xr-x 2 root root 4096 Apr 13 21:47 intel-ucode
```
<br/>
Alright, looks like a new folder <mark>intel-ucode</mark> was created. Let's see if it had the microcode update files:
```bash
ls -l /lib/firmware/intel-ucode
```
```none
06-03-02  06-06-05  06-08-01  06-0a-01	06-0f-02  06-16-01  06-1c-02  06-26-01	06-3c-03  06-3f-04  06-56-02  0f-01-02	0f-03-02  0f-04-07  0f-06-05
06-05-00  06-06-0a  06-08-03  06-0b-01	06-0f-06  06-17-06  06-1c-0a  06-2a-07	06-3d-04  06-45-01  06-56-03  0f-02-04	0f-03-03  0f-04-08  0f-06-08
06-05-01  06-06-0d  06-08-06  06-0b-04	06-0f-07  06-17-07  06-1d-01  06-2d-06	06-3e-04  06-46-01  06-56-04  0f-02-05	0f-03-04  0f-04-09
06-05-02  06-07-01  06-08-0a  06-0d-06	06-0f-0a  06-17-0a  06-1e-05  06-2d-07	06-3e-06  06-47-01  06-5e-03  0f-02-06	0f-04-01  0f-04-0a
06-05-03  06-07-02  06-09-05  06-0e-08	06-0f-0b  06-1a-04  06-25-02  06-2f-02	06-3e-07  06-4e-03  0f-00-07  0f-02-07	0f-04-03  0f-06-02
06-06-00  06-07-03  06-0a-00  06-0e-0c	06-0f-0d  06-1a-05  06-25-05  06-3a-09	06-3f-02  06-4f-01  0f-00-0a  0f-02-09	0f-04-04  0f-06-04
```
<br/>
Awesome, here are <strong>all</strong> of intel's CPUs microcode update files! Now, we have to do some research to figure out which file is the one to use for our cpu :D
<br/>
<hr/>
<h3>4- Choosing the Correct Microcode Update File</h3>
<br/>
The file names here are somewhat related to the CPUID signature. The default way to get your CPUID signature (as suggested by the <a href="https://wiki.gentoo.org/wiki/Intel_microcode#Software_3" target="_blank">Gentoo Wiki</a>) is to install a tool called <mark>iucode_tool</mark>:
```none
emerge --sync && emerge -av sys-apps/iucode_tool
```
<br/>
<mark>iucode_tool</mark> is also available in Arch's AUR. (This package isn't available on Void Linux by the time this article was written).
<br/>
<br/>
Now run this:
```none
iucode_tool -S
```
```none
iucode_tool: system has processor(s) with signature 0x000306c3
```
<br/>
As you can see my CPUID signature is <mark>0x000306c3</mark>. If that didn't work for you then don't worry we have other ways as well to get your CPUID signature.
<br/>
<br/>
 You can do your research and find your CPUID signature. For example, my CPU is a <em>4th Gen. Intel Core i7 4700MQ</em>, a little googling and I found this on cpu-world.com :
<div class="frame"><img src="/img/cpuid.png" alt="cpuid"></div>
<br/>
Another way to do this is to install <mark>cpuid</mark>:
```none
emerge --sync && emerge -av sys-apps/cpuid
```
<br/>
<mark>cpuid</mark> is also available in Arch's AUR. (This package isn't available on Void Linux by the time this article was written).
<br/>
<br/>
Now run:
```bash
cpuid | grep "processor serial number"
```
```none
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
      processor serial number                = false
   processor serial number: 0003-06C3-0000-0000-0000-0000
```
<br/>
Notice how it says processor serial number: <mark>0003-06C3</mark>-0000-0000-0000-0000. I've highlighted this part <mark>0003-06C3</mark>.
<br/>
<br/>
Another way to do it, is to install <mark>dmidecode</mark>:
<br/>
<br/>
Gentoo Linux:
```none
emerge --sync && emerge -av sys-apps/dmidecode
```
<br/>
Void Linux:
```none
xbps-install -Su && xbps-install -S dmidecode
```
<br/>
Arch Linux:
```none
pacman -Syu dmidecode
```
<br/>
Now run:
```bash
dmidecode | grep -w ID
```
```none
  ID: 0
	ID: 1
	ID: 2
	ID: 3
	ID: 4
	ID: C3 06 03 00 FF FB EB BF
```
<br/>
As you can see, (C, 3, 6, 0) are popping wherever I looked. You may simply choose to stop here if the signature was pretty obvious to you and you could easily identify the correct microcode update file to use (in my case I can easily tell that it's <mark>06-3c-03</mark>).
<br/>
<br/>
Now we can use <mark>iucode_tool</mark> to identify the correct microcode update file (and with the magic of grep):
```bash
iucode_tool -L /lib/firmware/intel-ucode | grep 0x000306c3 -B 1
```
```bash
microcode bundle 26: /lib/firmware/intel-ucode/06-3c-03
  026/001: sig 0x000306c3, pf_mask 0x32, 2017-01-27, rev 0x0022, size 22528
  026/002: sig 0x000306c3, pf_mask 0x32, 2017-01-27, rev 0x0022, size 22528
```
<br/>
 As you can clearly see my microcode update file in <mark>/lib/firmware/intel-ucode</mark> is <mark>06-3c-03</mark>.
<br/>
<hr/>
<h3>5- Configuring the Linux Kernel to Build with the Correct Microcode Update File</h3>
<br/>
Woot.. The hard part is done, all we have to do right now is to tell the linux kernel the location of our microcode update file so that it'll be included in the kernel's build process.
<br/>
<br/>
Fire up your favorite terminal, and run:
```bash
cd /usr/src/linux
```
```bash
make menuconfig
```
<br/>
Navigate to <mark>Device Drivers</mark> then to <mark>Generic Driver Options</mark>.
<br/>
<br/>
Now include <mark>CONFIG_FIRMWARE_IN_KERNEL</mark>,<mark>CONFIG_EXTRA_FIRMWARE</mark> and <mark>CONFIG_EXTRA_FIRMWARE_DIR</mark> as shown below:
```none
  [ ] Support for uevent helper
  -*- Maintain a devtmpfs filesystem to mount at /dev
  [*]   Automount devtmpfs at /dev, after the kernel mounted the rootfs
  [ ] Select only drivers that don't need compile-time external firmware
  [ ] Prevent firmware from being built
  -*- Userspace firmware loading support
  [*]   Include in-kernel firmware blobs in kernel binary
  (intel-ucode/06-3c-03) External firmware blobs to build into the kernel binary
  (/lib/firmware) Firmware blobs root directory
  [ ] Fallback user-helper invocation for firmware loading
  [ ] Allow device coredump
  [ ] Driver Core verbose debug messages
  [ ] Managed device resources verbose debug messages
  [ ] Test driver remove calls during probe (UNSTABLE)
  < > Build kernel module to test asynchronous driver probing
  [ ] Enable verbose DMA_FENCE_TRACE messages
```
<br/>
Change:
<br/>
<br/>
<mark>CONFIG_EXTRA_FIRMWARE</mark> to <mark>intel-ucode/YOUR_MICROCODE_UPDATE_FILE_NAME</mark>
<br/>
<br/>
<mark>CONFIG_EXTRA_FIRMWARE_DIR</mark> to <mark>/lib/firmware</mark>
<br/>
<br/>
Save your configuration file, compile your kernel and reboot. Microcode updates should be working now without using an initrd.
<br/>
<hr/>
<h3>6- Verify that Microcode Updates are Working</h3>
This is quite simple, just run:
```bash
dmesg | grep microcode
```
```none
[    0.000000] microcode: microcode updated early to revision 0x22, date = 2017-01-27
[    0.795219] microcode: sig=0x306c3, pf=0x10, revision=0x22
[    0.795433] microcode: Microcode Update Driver: v2.01 <tigran@aivazian.fsnet.co.uk>, Peter Oruba
```
<br/>
As you can see, microcode updates are 100% working, final revision <mark>0x22</mark> is being used.
<br/>
<hr/>
<h3>Conclusion</h3>
If you followed our previous article <a href="https://www.dotslashlinux.com/2017/04/29/Booting-the-Linux-Kernel-Without-an-initrd-initramfs.html" target="_blank">Booting the Linux Kernel Without an initrd/initramfs</a>, your boot folder now should only have the kernel inside it, as it contains everything from your modules to your microcode updates!
<br/>
