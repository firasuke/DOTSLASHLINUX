+++
title = "The Linux Kernel Configuration Guide Part 17"
slug = "the linux kernel configuration guide part 17"
nick = "kernel17"
date = "2017-09-17"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel17.png"
imgalt = "kernel17"
categories = [ "kernel" ]
+++
<h3>[&ast;] Virtualization  ---></h3>
```none
Symbol:     CONFIG_VIRTUALIZATION

Help:       Say Y here to get to see options for using your Linux host to run other
            operating systems inside virtual machines (guests).
            This option alone does not add any kernel code.

            If you say N, all options in this submenu will be skipped and disabled.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you're planning to run guest vms on your host system.

            It's also recommended by the Gentoo wiki.
```
<h3><&ast;>   Kernel-based Virtual Machine (KVM) support</h3>
```none
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

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option as the KVM
            hypervisor enhances performance considerably in linux guests.
            
            It's also recommended by the Gentoo wiki.
```
<h3><&ast;>     KVM for Intel processors support</h3>
```none
Symbol:     CONFIG_KVM_INTEL

Help:       Provides support for KVM on Intel processors equipped with the VT
            extensions.

            To compile this as a module, choose M here: the module
            will be called kvm-intel.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option as the KVM
            hypervisor for Intel CPUs enhances performance considerably in
            linux guests.
            
            It's also recommended by the Gentoo wiki.
```
<h3><&ast;>   Host kernel accelerator for virtio net</h3>
```none
Symbol:     CONFIG_VHOST_NET

Help:       This kernel module can be loaded in host kernel to accelerate
            guest networking with virtio_net. Not to be confused with virtio_net
            module itself which needs to be loaded in guest kernel.

            To compile this driver as a module, choose M here: the module will
            be called vhost_net.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option as virtio
            net boosts network performance considerably in guest vms.
            
            It's also recommended by the Gentoo wiki.
```
