+++
title = "The Linux Kernel Configuration Guide Part 8"
slug = "the linux kernel configuration guide part 8"
nick = "kernel8"
date = "2017-09-07"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel8.png"
imgalt = "kernel8"
categories = [ "kernel" ]
+++
Wow we're at part 8 already. Time sure passes by quickly... I hope you're enjoying this series so far.
<br/>
<br/>
For those of you who want to know the options/features that their system supports, then unfortunately you'll have to wait until part 11 which will be about the Device Drivers section and how to find everything that your system supports.
<br/>
<br/>
Thanks for your time! Have fun configuring your kernel!
<hr/>
<h3>Bus options (PCI etc.)  ---></h3>
<h3>[&ast;] PCI support</h3>
```none
Symbol:     CONFIG_PCI

Help:       Find out whether you have a PCI motherboard. PCI is the name of a
            bus system, i.e. the way the CPU talks to the other stuff inside
            your box. Other bus systems are ISA, EISA, MicroChannel (MCA) or
            VESA. If you have PCI, say Y, otherwise N.

Type:       boolean

Choice:     built-in [*]

Reason:     Include this feature if your motherboard supports PCI. In most cases
            you'll have to include this option in your kernel (AFAIK almost all
            graphic cards use PCI or PCIe).
```
<h3>[&ast;]   Support mmconfig PCI config space access</h3>
```none
Symbol:     CONFIG_PCI_MMCONFIG

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [*]

Reason:     This is required to read extended information of PCI devices, as it
            grants access to drivers polling for extra information.
```
<h3>[ ]   Read CNB20LE Host Bridge Windows</h3>
```none
Symbol:     CONFIG_PCI_CNB20LE_QUIRK

Help:       Read the PCI windows out of the CNB20LE host bridge. This allows
            PCI hotplug to work on systems with the CNB20LE chipset which do
            not have ACPI.

            There's no public spec for this chipset, and this functionality
            is known to be incomplete.

            You should say N unless you know you need this.

Type:       boolean

Choice:     excluded [ ]

Reason:     A simple "lspci -k" will show you if you have a CNB20LE host bridge
            or not.

            In most cases you won't have this host bridge so you can safely
            exclude this option.
```
<h3>[&ast;]   PCI Express Port Bus support</h3>
```none
Symbol:     CONFIG_PCIEPORTBUS

Help:       This automatically enables PCI Express Port Bus support. Users can
            choose Native Hot-Plug support, Advanced Error Reporting support,
            Power Management Event support and Virtual Channel support to run
            on PCI Express Ports (Root or Switch).

Type:       boolean

Choice:     built-in [*]

Reason:     PCIe is an improved version of PCI designed to replace old buses. You
            
            Again with a simple "lspci -k" you can see if you have PCI Express Ports,
            which in most cases you'll have so include this option.
```
<h3>[ ]     PCI Express Hotplug driver</h3>
```none
Symbol:     CONFIG_HOTPLUG_PCI_PCIE

Help:       Say Y here if you have a motherboard that supports PCI Express Native
            Hotplug
            
            When in doubt, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     To see this option you need to include CONFIG_HOTPLUG_PCI.

            USB Type-C, Thunderbolt, ExpressCard, XQD card and M-PCIE (mobile) are an
            example of PCIe ports/cards that require PCI Express Native Hotplug so include 
            this option if you have such ports or cards on your motherboard.
```
<h3>[ ]     Root Port Advanced Error Reporting support</h3>
```none
Symbol:     CONFIG_PCIEAER

Help:       This enables PCI Express Root Port Advanced Error Reporting
            (AER) driver support. Error reporting messages sent to Root
            Port will be handled by PCI Express AER driver.

Type:       boolean

Choice:     excluded [ ]

Reason:     Exclude this option if you have no need for its error reporting
            feature.

            For example, if you're a developer working on a custom PCIe interface
            then the AER driver might fill your /var/log/messages with a ton of
            informative error messages that you may not need (or may already know).
            In this case you'll want to exclude this option.

            On the other hand, if you were experiencing fatal PCIe errors and your
            kernel was panicking or even crashing due to these errors, then you may 
            want to include this option in your kernel as it'll help you pinpoint the
            source of these errors.
```
<h3>[*]     PCI Express ASPM control</h3>
```none
Symbol:     CONFIG_PCIEASPM

Help:       This enables OS control over PCI Express ASPM (Active State
            Power Management) and Clock Power Management. ASPM supports
            state L0/L0s/L1.

            ASPM is initially set up by the firmware. With this option enabled,
            Linux can modify this state in order to disable ASPM on known-bad
            hardware or configurations and enable it when known-safe.

            ASPM can be disabled or enabled at runtime via
            /sys/module/pcie_aspm/parameters/policy

            When in doubt, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     PCIe ASPM is really an important feature that allows your PCIe devices
            to enter an idle state.

            It's highly recommended that you include this feature in your kernel,
            especially if you're on a laptop and want some power saving on your
            PCIe devices.
```
<h3>[ ]       Debug PCI Express ASPM (NEW)</h3>
```none
Symbol:     CONFIG_PCIEASPM_DEBUG

Help:       This enables PCI Express ASPM debug support. It will add per-device
            interface to control ASPM.

Type:       boolean

Choice:     excluded [ ]

Reason:     Exclude this option if you don't need it's debugging features like I
            did, for less system overhead.
```
<h3>Default ASPM policy (BIOS default)  ---></h3>
<h3>(X) BIOS default</h3>
```none
Symbol:     CONFIG_PCIEASPM_DEFAULT

Help:       Use the BIOS defaults for PCI Express ASPM.

Type:       boolean

Choice:     built-in (X)

Reason:     It's better to choose the BIOS defaults for ASPM.

            Remember do not use the "pcie_aspm=force" kernel parameter until
            you check that all your PCIe support ASPM, otherwise your system
            may stop responding.

            You can check for ASPM by simply running:
                
                lspci -vvv | grep ASPM

            or you can pipe it to less:

                lspci -vvv | less

            and see what parts support ASPM.
```
<h3>[ ]     PCIe Downstream Port Containment support</h3>
```none
Symbol:     CONFIG_PCIE_DPC

Help:       This enables PCI Express Downstream Port Containment (DPC)
            driver support.  DPC events from Root and Downstream ports
            will be handled by the DPC driver.  If your system doesn't
            have this capability or you do not want to use this feature,
            it is safe to answer N.

Type:       boolean

Choice:     exclude [ ]

Reason:     You can safely exclude this option if you don't have downstream
            ports that implement PCIe extended capability (like me) or if you 
            don't want to use this feature.

            On the other hand, if you had such ports and wanted to contain
            uncorrectable errors in hardware attached to a certain port
            you can include this feature.
```
<h3>[ ]     PCIe Precision Time Measurement support</h3>
```none
Symbol:     CONFIG_PCIE_PTM

Help:       This enables PCI Express Precision Time Measurement (PTM)
            support.

            This is only useful if you have devices that support PTM, but it
            is safe to enable even if you don't.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option.

            PTM is supported in intel's apollo lake platform which came out in
            late 2016. Some of these CPUs include Pentium J4205, Celeron J3355
            and Celeron J3455.
            
            To find out if your cpu supports it check this link:

                https://en.wikipedia.org/wiki/Goldmont
```
<h3>[&ast;]   Message Signaled Interrupts (MSI and MSI-X)</h3>
```none
Symbol:     CONFIG_PCI_MSI

Help:       This allows device drivers to enable MSI (Message Signaled
            Interrupts).  Message Signaled Interrupts enable a device to
            generate an interrupt using an inbound Memory Write on its
            PCI bus instead of asserting a device IRQ pin.

            Use of PCI MSI interrupts can be disabled at kernel boot time
            by using the 'pci=nomsi' option.  This disables MSI for the
            entire system.

            If you don't know what to do here, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this feature as it improves
            performance. Almost all motherboards support this feature and including
            it will make it available to wherever it's needed in the system.

            Excluding this option, will force the system to use older methods and may
            result in a performance hit.
```
<h3>[ ]   PCI Debugging</h3>
```none
Symbol:     CONFIG_PCI_DEBUG

Help:       Say Y here if you want the PCI core to produce a bunch of debug
            messages to the system log.  Select this if you are having a
            problem with PCI support and want to see more of what is going on.

            When in doubt, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     The general rule with all debugging options is to exclude them if
            everything is working as expected and include them to debug the
            source of the problem until everything works as expected then
            removing them.

            You can safely exclude this option if you have no need for it.
```
<h3>[ ]   Enable PCI resource re-allocation detection</h3>
```none
Symbol:     CONFIG_PCI_REALLOC_ENABLE_AUTO

Help:       Say Y here if you want the PCI core to detect if PCI resource
            re-allocation needs to be enabled. You can always use pci=realloc=on
            or pci=realloc=off to override it.  Note this feature is a no-op
            unless PCI_IOV support is also enabled; in that case it will
            automatically re-allocate PCI resources if SR-IOV BARs have not
            been allocated by the BIOS.

            When in doubt, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     Include this option only if you're unable to enable SR-IOV and you're
            receiving this error message "not enough MMIO resources for SR-IOV".

            You can safely exclude this option if you're not receiving that error.
```
<h3>< >   PCI Stub driver</h3>
```none
Symbol:     CONFIG_PCI_STUB

Help:       Say Y or M here if you want be able to reserve a PCI device
            when it is going to be assigned to a guest operating system.

            When in doubt, say N.

Type:       tristate

Choice:     excluded < >

Reason:     This option is only useful for those who want to do PCI passthrough
            (example VGA passthrough) along with CONFIG_IOMMU_SUPPORT (VT-d).

            You can safely exclude this option if your CPU doesn't support IOMMU
            (aka VT-d) or if you're not planning to do PCI passthrough.
```
<h3>[&ast;]   Interrupts on hypertransport devices</h3>
```none
Symbol:     CONFIG_HT_IRQ

Help:       This allows native hypertransport devices to use interrupts.

            If unsure say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     
```
<h3>[ ] PCI IOV support</h3>
```none
Symbol:     CONFIG_PCI_IOV

Help:       I/O Virtualization is a PCI feature supported by some devices
            which allows them to create virtual devices which share their
            physical resources.

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your CPU doesn't support IOMMU (VT-d)
            or if you're not planning to use it.
```
<h3>[ ] PCI PRI support</h3>
```none
Symbol:     CONFIG_PCI_PRI

Help:       PRI is the PCI Page Request Interface. It allows PCI devices that are
            behind an IOMMU to recover from page faults.

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your CPU doesn't support IOMMU (VT-d)
            or if you're not planning to use it.
```
<h3>[ ] PCI PASID support</h3>
```none
Symbol:     CONFIG_PCI_PASID

Help:       Process Address Space Identifiers (PASIDs) can be used by PCI devices
            to access more than one IO address space at the same time. To make
            use of this feature an IOMMU is required which also supports PASIDs.
            Select this option if you have such an IOMMU and want to compile the
            driver for it into your kernel.

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your CPU doesn't support IOMMU (VT-d)
            or if you're not planning to use it.
```
<h3>[*] Support for PCI Hotplug  ---></h3>
```none
Symbol:     CONFIG_HUTPLUG_PCI

Help:       Say Y here if you have a motherboard with a PCI Hotplug controller.
            This allows you to add and remove PCI cards while the machine is
            powered up and running.

            When in doubt, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     If you have USB Type-C, Thunderbolt, ExpressCard, XQD card or M-PCIE (mobile)
            then you should include this option along with CONFIG_HOTPLUG_PCI_PCIE to get
            them working.

            You should also include this option if you have a motherboard with a Hotplug
            controller (in my case I have a SHPC PCI Hotplug controller or shpchp).

            Otherwise, you can safely exclude this option.
```
<h3><&ast;>   SHPC PCI Hotplug driver</h3>
```none
Symbol:     CONFIG_HOTPLUG_PCI_SHPC

Help:       Say Y here if you have a motherboard with a SHPC PCI Hotplug
            controller.

            To compile this driver as a module, choose M here: the
            module will be called shpchp.

            When in doubt, say N.

Type:       tristate

Choice:     built-in <*>

Reason:     I included this option as it was supported on my motherboard.
            
            In fact, it was the only reason I included the whole PCI
            Hotplug option.
```
<h3>DesignWare PCI Core Support  ---></h3>
<h3>[ ] Platform bus based DesignWare PCIe Controller</h3>
```none
Symbol:     CONFIG_PCIE_DW_PLAT

Help:       This selects the DesignWare PCIe controller support. Select this if
            you have a PCIe controller on Platform bus.

            If you have a controller with this interface, say Y or M here.

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you don't have such controller.
```
<h3>PCI host controller drivers  ---></h3>
<h3>< > Intel Volume Management Device Driver</h3>
```none
Symbol:     CONFIG_VMD

Help:       Adds support for the Intel Volume Management Device (VMD). VMD is a
            secondary PCI host bridge that allows PCI Express root ports,
            and devices attached to them, to be removed from the default
            PCI domain and placed within the VMD domain. This provides
            more bus resources than are otherwise possible with a
            single domain. If you know your system provides one of these and
            has devices attached to it, say Y; if you are not sure, say N.

            To compile this driver as a module, choose M here: the
            module will be called vmd.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you don't have such device.
```
<h3>PCI Endpoint  ---></h3>
<h3>[&ast;] PCI Endpoint Support</h3>
```none
Symbol:     CONFIG_PCI_ENDPOINT

Help:       Enable this configuration option to support configurable PCI
            endpoint. This should be enabled if the platform has a PCI
            controller that can operate in endpoint mode.

            Enabling this option will build the endpoint library, which
            includes endpoint controller library and endpoint function
            library.

            If in doubt, say "N" to disable Endpoint support.

Type:       boolean

Choice:     built-in [*]

Reason:     You can check for PCI endpoint support by simply running:
                
                lspci -nnkvvv | grep Endpoint

            If no output is printed, you can safely exclude this option.
```
<h3>[ ]   PCI Endpoint Configfs Support</h3>
```none
Symbol:     CONFIG_PCI_ENDPOINT_CONFIGFS

Help:       This will enable the configfs entry that can be used to
            configure the endpoint function and used to bind the
            function with a endpoint controller.

Type:       boolean

Choice:     built-in [*]

Reason:     You can safely exclude this option as most of the times you
            won't need it.
```
<h3>< >   PCI Endpoint Test driver (NEW)</h3>
```none
Symbol:     CONFIG_PCI_EPF_TEST

Help:       Enable this configuration option to enable the test driver
            for PCI Endpoint.

            If in doubt, say "N" to disable Endpoint test driver.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's for testing purposes.
```
<h3>PCI switch controller drivers  ---></h3>
<h3>< > MicroSemi Switchtec PCIe Switch Management Driver</h3>
```none
Symbol:     CONFIG_PCI_SW_SWITCHTEC

Help:       Enables support for the management interface for the MicroSemi
            Switchtec series of PCIe switches. Supports userspace access
            to submit MRPC commands to the switch via /dev/switchtecX
            devices. See <file:Documentation/switchtec.txt> for more
            information.

Type:       tristate

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you don't have such PCIe switch.
```
<h3>[ ] ISA-style bus support on modern systems</h3>
```none
Symbol:     CONFIG_ISA_BUS

Help:       Enables ISA-style drivers on modern systems. This is necessary to
            support PC/104 devices on X86_64 platforms.

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as ISA buses were superseded by PCI 
            buses in 1993 so yeah they're that old!
```
<h3>[ ] ISA-style DMA support</h3>
```none
Symbol:     CONFIG_ISA_DMA_API

Help:       Enables ISA-style DMA support for devices requiring such controllers.
            If unsure, say Y.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's only required for floppy
            support and other outdated drivers.
```
<h3>< > PCCard (PCMCIA/CardBus) support  ----</h3>
```none
Symbol:     CONFIG_PCCARD

Help:       Say Y here if you want to attach PCMCIA- or PC-cards to your Linux
            computer.  These are credit-card size devices such as network cards,
            modems or hard drives often used with laptops computers.  There are
            actually two varieties of these cards: 16 bit PCMCIA and 32 bit
            CardBus cards.

            To compile this driver as modules, choose M here: the
            module will be called pcmcia_core.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you don't have such cards.
```
<h3>< > RapidIO support</h3>
```none
Symbol:     CONFIG_RAPIDIO

Help:       If enabled this option will include drivers and the core
            infrastructure code to support RapidIO interconnect devices.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you don't have such devices.
```
<h3>[ ] Mark VGA/VBE/EFI FB as generic system framebuffer</h3>
```none
Symbol:     CONFIG_X86_SYSFB

Help:       Firmwares often provide initial graphics framebuffers so the BIOS,
            bootloader or kernel can show basic video-output during boot for
            user-guidance and debugging. Historically, x86 used the VESA BIOS
            Extensions and EFI-framebuffers for this, which are mostly limited
            to x86.
            This option, if enabled, marks VGA/VBE/EFI framebuffers as generic
            framebuffers so the new generic system-framebuffer drivers can be
            used on x86. If the framebuffer is not compatible with the generic
            modes, it is adverticed as fallback platform framebuffer so legacy
            drivers like efifb, vesafb and uvesafb can pick it up.
            If this option is not selected, all system framebuffers are always
            marked as fallback platform framebuffers as usual.

            Note: Legacy fbdev drivers, including vesafb, efifb, uvesafb, will
            not be able to pick up generic system framebuffers if this option
            is selected. You are highly encouraged to enable simplefb as
            replacement if you select this option. simplefb can correctly deal
            with generic system framebuffers. But you should still keep vesafb
            and others enabled as fallback if a system framebuffer is
            incompatible with simplefb.

            If unsure, say Y.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you have an iGPU or a dGPU that's
            wired to your display and this is the case with most systems out there.
            
            For optimus laptops, the only framebuffer that should be included is 
            CONFIG_DRM_FBDEV_EMULATION.
```
