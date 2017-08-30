+++
title = "The Linux Kernel Configuration Guide Part 6"
slug = "the linux kernel configuration guide part 6"
nick = "kernel6"
date = "2017-08-30"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel6.png"
imgalt = "kernel6"
categories = [ "kernel" ]
+++
The choice of my options will be heavily affected by the cpu my laptop uses (an <a href="http://ark.intel.com/products/75117/Intel-Core-i7-4700MQ-Processor-6M-Cache-up-to-3_40-GHz" target="_blank">Intel Core i7 4700MQ</a>
<h3>Processor type and features  ---></h3>
<h3>[ ] DMA memory allocation support</h3>
```none
Symbol:     CONFIG_ZONE_DMA

Help:       DMA memory allocation support allows devices with less than 32-bit
            addressing to allocate within the first 16MB of address space.
            Disable if no such devices will be used.

            If unsure, say Y.

Type:       boolean

Choice:     excluded [ ]

Reason:     Recent systems (mainly post 2012) have almost no devices with less than
            32-bit addressing, so if you're on a modern system you can safely
            exclude this option like I did (late 2013 laptop).
```
<h3>[&ast;] Symmetric multi-processing support</h3>
```none
Symbol:     CONFIG_SMP

Help:       This enables support for systems with more than one CPU. If you have
            a system with only one CPU, say N. If you have a system with more
            than one CPU, say Y.

            If you say N here, the kernel will run on uni- and multiprocessor
            machines, but will use only one CPU of a multiprocessor machine. If
            you say Y here, the kernel will run on many, but not all,
            uniprocessor machines. On a uniprocessor machine, the kernel
            will run faster if you say N here.

            Note that if you say Y here and choose architecture "586" or
            "Pentium" under "Processor family", the kernel will not work on 486
            architectures. Similarly, multiprocessor kernels for the "PPro"
            architecture may not work on all Pentium based boards.
            
            People using multiprocessor machines who say Y here should also say
            Y to "Enhanced Real Time Clock Support", below. The "Advanced Power
            Management" code will be disabled if you say Y here.

            See also <file:Documentation/x86/i386/IO-APIC.txt>,
            <file:Documentation/lockup-watchdogs.txt> and the SMP-HOWTO available at
            <http://www.tldp.org/docs.html#howto>.

            If you don't know what to do here, say N.

Type:       boolean

Choice:     built-in [*]

Reason:     My cpu has 4 cores and 8 threads, but it's basically a single cpu so
            I should exclude this option right? WRONG... The documentation actually 
            meant cores,so if you had for example a single cpu with 1 core and 2 
            threads you should enable this as 1*2 is 2 logical cores, otherwise
            only 1 core will be detected.
```
<h3>[&ast;] Support x2apic</h3>
```none
Symbol:     CONFIG_X86_X2APIC

Help:       This enables x2apic support on CPUs that have this feature.
            This allows 32-bit apic IDs (so it can support very large systems),
            and accesses the local apic via MSRs not via mmio.

            If you don't know what to do here, say N.

Type:       boolean

Choice:     built-in [*]

Reason:     My cpu supports x2apic, so I included this feature.
```
<h3>[ ] Enable MPS table</h3>
```none
Symbol:     CONFIG_X86_MPPARSE

Help:       For old smp systems that do not have proper acpi support. Newer systems
            (esp with 64bit cpus) with acpi support, MADT and DSDT will override it

Type:       boolean

Choice:     excluded [ ]

Reason:     My system isn't that old (late 2013) so I safely excluded this option.
```
<h3>[ ] Intel Resource Director Technology Allocation support</h3>
```none
Symbol:     CONFIG_INTEL_RDT_A

Help:       Select to enable resource allocation which is a sub-feature of
            Intel Resource Director Technology(RDT). More information about
            RDT can be found in the Intel x86 Architecture Software
            Developer Manual.

            Say N if unsure.

Type:       boolean

Choice:     built-in [*]

Reason:     A new feature provided by intel in late 2016, due to the lack of
            information and a proper list of supported cpus, and since my cpu
            probably won't be on that list I decided to exclude it.
```
<h3>[ ] Support for extended (non-PC) x86 platforms</h3>
```none
Symbol:     CONFIG_X86_EXTENDED_PLATFORM

Help:       If you disable this option then the kernel will only support
            standard PC platforms. (which covers the vast majority of
            systems out there.)

            If you enable this option then you'll be able to select support
            for the following (non-PC) 64 bit x86 platforms:
                  Numascale NumaChip
                  ScaleMP vSMP
                  SGI Ultraviolet

            If you have one of these systems, or if you want to build a
            generic distribution kernel, say Y here - otherwise say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you have a standard pc
            platform.
```
<h3>[ ] Intel Low Power Subsystem Support</h3>
```none
Symbol:     CONFIG_X86_INTEL_LPSS

Help:       Select to build support for Intel Low Power Subsystem such as
            found on Intel Lynxpoint PCH. Selecting this option enables
            things like clock tree (common clock framework) and pincontrol
            which are needed by the LPSS peripheral drivers.

Type:       boolean

Choice:     excluded [ ]

Reason:     Some say this feature is for intel chipsets starting from haswell
            others say starting from skylake.

            Due to confusion I decided to exclude this option for now until
            I 
```
<h3>[ ] AMD ACPI2Platform devices support</h3>
```none
Symbol:     CONFIG_X86_AMD_PLATFORM_DEVICE

Help:       Select to interpret AMD specific ACPI device to platform device
            such as I2C, UART, GPIO found on AMD Carrizo and later chipsets.
            I2C and UART depend on COMMON_CLK to set clock. GPIO driver is
            implemented under PINCTRL subsystem.

Type:       boolean

Choice:     excluded [ ]

Reason:     I don't have such chipsets; therefore, I excluded this option.
```
<h3>-*- Intel SoC IOSF Sideband support for SoC platforms</h3>
```none
Symbol:     
```
