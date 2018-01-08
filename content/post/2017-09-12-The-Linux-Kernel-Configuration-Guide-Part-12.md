+++
title = "The Linux Kernel Configuration Guide Part 12 - Firmware Drivers  --->"
slug = "the linux kernel configuration guide part 12 firmware drivers"
nick = "kernel12"
date = "2017-09-12"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel12.png"
imgalt = "kernel12"
categories = [ "kernel" ]
+++
<h3>Firmware Drivers  ---></h3>
<h3>< > BIOS Enhanced Disk Drive calls determine boot disk</h3>
```properties
Symbol:     CONFIG_EDD

Help:       Say Y or M here if you want to enable BIOS Enhanced Disk Drive
            Services real mode BIOS calls to determine which disk
            BIOS tries boot from.  This information is then exported via sysfs.

            This option is experimental and is known to fail to boot on some
            obscure configurations. Most disk controller BIOS vendors do
            not yet implement this feature.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's experimental and may result
            in an unbootable system.
```
<h3>[ ] Add firmware-provided memory map to sysfs</h3>
```properties
Symbol:     CONFIG_FIRMWARE_MEMMAP

Help:       Add the firmware-provided (unmodified) memory map to /sys/firmware/memmap.
            That memory map is used for example by kexec to set up parameter area
            for the next kernel, but can also be used for debugging purposes.

            See also Documentation/ABI/testing/sysfs-firmware-memmap.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you've already excluded CONFIG_KEXEC
            and have no need for its debugging features.
```
<h3>< > BIOS update support for DELL systems via sysfs</h3>
```properties
Symbol:     CONFIG_DELL_RBU

Help:       Say m if you want to have the option of updating the BIOS for your
            DELL system. Note you need a Dell OpenManage or Dell Update package (DUP)
            supporting application to communicate with the BIOS regarding the new
            image for the image update to take effect.
            See <file:Documentation/dell_rbu.txt> for more details on the driver.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you're not using a DELL system.
```
<h3>< > Dell Systems Management Base Driver</h3>
```properties
Symbol:     CONFIG_DCDBAS

Help:       The Dell Systems Management Base Driver provides a sysfs interface
            for systems management software to perform System Management
            Interrupts (SMIs) and Host Control Actions (system power cycle or
            power off after OS shutdown) on certain Dell systems.

            See <file:Documentation/dcdbas.txt> for more details on the driver
            and the Dell systems on which Dell systems management software makes
            use of this driver.

            Say Y or M here to enable the driver for use by Dell systems
            management software such as Dell OpenManage.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you're not using a DELL system.
```
<h3>[&lowast;] Export DMI identification via sysfs to userspace</h3>
```properties
Symbol:     CONFIG_DMIID

Help:       Say Y here if you want to query SMBIOS/DMI system identification
            information from userspace through /sys/class/dmi/id/ or if you want
            DMI-based module auto-loading.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel as it
            provides important information about your hardware. This option is
            also necessary if you want to use dmidecode.
```
<h3>< > DMI table support in sysfs</h3>
```properties
Symbol:     CONFIG_DMI_SYSFS

Help:       Say Y or M here to enable the exporting of the raw DMI table
            data via sysfs.  This is useful for consuming the data without
            requiring any access to /dev/mem at all.  Tables are found
            under /sys/firmware/dmi when this option is enabled and
            loaded.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as some may say it's dangerous.
            
            Include this option only when needed.
```
<h3>[ ] iSCSI Boot Firmware Table Attributes</h3>
```properties
Symbol:     CONFIG_ISCSI_IBFT_FIND

Help:       This option enables the kernel to find the region of memory
            in which the ISCSI Boot Firmware Table (iBFT) resides. This
            is necessary for iSCSI Boot Firmware Table Attributes module to work
            properly.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you've already excluded
            CONFIG_ISCSI_BOOT_SYSFS.
```
<h3>< > QEMU fw_cfg device support in sysfs</h3>
```properties
Symbol:     CONFIG_FW_CFG_SYSFS

Help:       Say Y or M here to enable the exporting of the QEMU firmware
            configuration (fw_cfg) file entries via sysfs. Entries are
            found under /sys/firmware/fw_cfg when this option is enabled
            and loaded.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option.

            Include this option only if it's required by some QEMU setups.
```
<h3>[ ] Google Firmware Drivers  ----</h3>
```properties
Symbol:     CONFIG_GOOGLE_FIRMWARE

Help:       These firmware drivers are used by Google's servers.  They are
            only useful if you are working directly on one of their
            proprietary servers.  If in doubt, say "N".

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's highly unlikely for
            any user to use this option unless he's/she's a developer working for
            Google on one of their proprietary servers.
```
<h3>Tegra firmware driver  ----</h3>
```properties
Choice:     excluded ----
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX followers 杨鑫 (Yang Mame) from China, decided to follow up with the series and provide Chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in Chinese <a href="https://blog.yangmame.top/Linux内核配置指南-Firmware-Drivers和File-systems.html" target="_blank">click here</a>.
