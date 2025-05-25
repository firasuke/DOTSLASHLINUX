+++
title = "The Linux Kernel Configuration Guide Part 17 - [∗] Virtualization  --->"
slug = "the linux kernel configuration guide part 17 virtualization"
nick = "kernel17"
date = "2017-09-17"
author = "Firas Khana"
imgsrc = "/img/kernel17.png"
imgalt = "kernel17"
categories = [ "kernel" ]
+++
As of kernel version <mark>4.14.10-r1</mark>, all virtualization-related options listed below were excluded from the kernel configuration file as they're mainly intended for QEMU. If you're running VirtualBox then you can safely exclude the options below.
<br/>
<br/>
Include the options below only if you're using QEMU.
<hr/>
<h3>[&lowast;] Virtualization  ---></h3>
```properties
Symbol:     CONFIG_VIRTUALIZATION

Help:       Say Y here to get to see options for using your Linux host to run other
            operating systems inside virtual machines (guests).
            This option alone does not add any kernel code.

            If you say N, all options in this submenu will be skipped and disabled.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you're planning to run guest vms on your host system.

            It's also recommended by the Gentoo wiki.
```
<h3><&lowast;>   Kernel-based Virtual Machine (KVM) support</h3>
```properties
Symbol:     CONFIG_KVM

Help:       Support hosting fully virtualized guest machines using hardware
            virtualization extensions.  You will need a fairly recent
            processor equipped with virtualization extensions. You will also
            need to select one or more of the processor modules below.

            This module provides access to the hardware capabilities through
            a character device node named /dev/kvm.

            To compile this as a module, choose M here: the module
            will be called kvm.

            If unsure, say N.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option as the KVM
            hypervisor enhances performance considerably in linux guests.
            
            It's also recommended by the Gentoo wiki.
```
<h3><&lowast;>     KVM for Intel processors support</h3>
```properties
Symbol:     CONFIG_KVM_INTEL

Help:       Provides support for KVM on Intel processors equipped with the VT
            extensions.

            To compile this as a module, choose M here: the module
            will be called kvm-intel.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option as the KVM
            hypervisor for Intel CPUs enhances performance considerably in
            linux guests.
            
            It's also recommended by the Gentoo wiki.
```
<h3><&lowast;>   Host kernel accelerator for virtio net</h3>
```properties
Symbol:     CONFIG_VHOST_NET

Help:       This kernel module can be loaded in host kernel to accelerate
            guest networking with virtio_net. Not to be confused with virtio_net
            module itself which needs to be loaded in guest kernel.

            To compile this driver as a module, choose M here: the module will
            be called vhost_net.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option as virtio
            net boosts network performance considerably in guest vms.
            
            It's also recommended by the Gentoo wiki.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX followers 杨鑫 (Yang Mame) from China, decided to follow up with the series and provide Chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in Chinese <a href="https://blog.yangmame.top/Linux内核配置指南-Kernel-hacking-Library-routines-The-End.html" target="_blank">click here</a>.
