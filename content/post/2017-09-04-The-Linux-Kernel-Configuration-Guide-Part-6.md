+++
title = "The Linux Kernel Configuration Guide Part 6"
slug = "the linux kernel configuration guide part 6"
nick = "kernel6"
date = "2017-09-04"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel6.png"
imgalt = "kernel6"
categories = [ "kernel" ]
+++
The choice of my options will be heavily affected by the cpu my laptop uses (an <a href="http://ark.intel.com/products/75117/Intel-Core-i7-4700MQ-Processor-6M-Cache-up-to-3_40-GHz" target="_blank">Intel Core i7 4700MQ</a>
<h3>Processor type and features  ---></h3>
<h3>[&ast;] DMA memory allocation support</h3>
```none
Symbol:     CONFIG_ZONE_DMA

Help:       DMA memory allocation support allows devices with less than 32-bit
            addressing to allocate within the first 16MB of address space.
            Disable if no such devices will be used.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     Recent systems (mainly post 2012) have almost no devices with less than
            32-bit addressing; however, this option is required by x11-drivers/nvidia-drivers
            so I included it.
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
<h3>-&ast;- Intel SoC IOSF Sideband support for SoC platforms</h3>
```none
Symbol:     CONFIG_IOSF_MBI

Help:       This option enables sideband register access support for Intel SoC
            platforms. On these platforms the IOSF sideband is used in lieu of
            MSR's for some register accesses, mostly but not limited to thermal
            and power. Drivers may query the availability of this device to
            determine if they need the sideband in order to work on these
            platforms. The sideband is available on the following SoC products.
            This list is not meant to be exclusive.
             - BayTrail
             - Braswell
             - Quark

            You should say Y if you are running a kernel on one of these SoC's.

Type:       tristate

Choice:     built-in -*-

Reason:     This option was previously excluded in my configuration, however a 
            recent commit (thanks to grknight for providing the link)

              https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=264ec1a8221c60f9ccf13f58ac597da21235132d

            forcibly included it, due to I915 wake up related problems.

            You can safely exclude this option if you're not using an Intel SoC
            product.
```
<h3>[&ast;] Single-depth WCHAN output</h3>
```none
Symbol:     CONFIG_SCHED_OMIT_FRAME_POINTER

Help:       Calculate simpler /proc/<PID>/wchan values. If this option
            is disabled then wchan values will recurse back to the
            caller function. This provides more accurate wchan values,
            at the expense of slightly more scheduling overhead.

            If in doubt, say "Y".Calculate

Type:       boolean

Choice:     excluded [ ]

Reason:     Include this option to get simple wchan values as this will lower
            scheduling overhead.
```
<h3>[ ] Linux guest support  ----</h3>
```none
Symbol:     CONFIG_HYPERVISOR_GUEST

Help:       Say Y here to enable options for running Linux under various hyper-
            visors. This option enables basic hypervisor detection and platform
            setup.

            If you say N, all options in this submenu will be skipped and
            disabled, and Linux guest support won't be built in.

Type:       boolean

Choice:     excluded [ ]

Reason:     The kernel will be built for a host system.

            If you're building the kernel for a linux guest system then include
            this option.
```
<h3>Processor family (Core 2/newer Xeon)  ---></h3>
```none
Symbol:     CONFIG_MCORE2

Help:       Select this for Intel Core 2 and newer Core 2 Xeons (Xeon 51xx and
            53xx) CPUs. You can distinguish newer from older Xeons by the CPU
            family in /proc/cpuinfo. Newer ones have 6 and older ones 15
            (not a typo)                                            

Type:       boolean

Choice:     built-in [*]

Reason:     I included this option because the kernel is being built for a core i7 
            intel cpu system.

            If you wanted your kernel to work on all X86_64 systems then include
            CONFIG_GENERIC_CPU.
```
<h3>[&ast;] Supported processor vendors  ---></h3>
```none
Symbol:     CONFIG_PROCESSOR_SELECT

Help:       This lets you choose what x86 vendor support code your kernel
            will include.

Type:       boolean

Choice:     built-in [*]

Reason:     It's really important that you tell the kernel what type of cpu
            it's supposed to run on.

            In some cases, not doing that may result in an unbootable system.
```
<h3>Support Intel processors</h3>
```none
Symbol:     CONFIG_CPU_SUP_INTEL

Help:       This enables detection, tunings and quirks for Intel processors
            
            You need this enabled if you want your kernel to run on an
            Intel CPU. Disabling this option on other types of CPUs
            makes the kernel a tiny bit smaller. Disabling it on an Intel
            CPU might render the kernel unbootable.
            
            If unsure, say N.

Type:       boolean

Choice:     built-in [*]

Reason:     I included this option since I'm building the kernel for an intel cpu.
```
<h3>[ ] Enable DMI scanning</h3>
```none
Symbol:     CONFIG_DMI

Help:       Enabled scanning of DMI to identify machine quirks. Say Y
            here unless you have verified that your setup is not
            affected by entries in the DMI blacklist. Required by PNP
            BIOS code.

Type:       boolean

Choice:     excluded [ ]

Reason:     I read that this option is related to CONFIG_EMBEDDED and since
            kernel isn't being built for an embedded system I decided to 
            exclude this option.
```
<h3>[ ] IBM Calgary IOMMU support</h3>
```none
Symbol:     CONFIG_CALGARY_IOMMU

Help:       Support for hardware IOMMUs in IBM's xSeries x366 and x460
            systems. Needed to run systems with more than 3GB of memory
            properly with 32-bit PCI devices that do not support DAC
            (Double Address Cycle). Calgary also supports bus level
            isolation, where all DMAs pass through the IOMMU.  This
            prevents them from going anywhere except their intended
            destination. This catches hard-to-find kernel bugs and
            mis-behaving drivers and devices that do not use the DMA-API
            properly to set up their DMA buffers.  The IOMMU can be
            turned off at boot time with the iommu=off parameter.
            Normally the kernel will make the right choice by itself.
            If unsure, say Y.

Type:       boolean

Choice:     excluded [ ]

Reason:     The cpu I'm building the kernel for is an intel core i7 4700MQ
            which supports only VT-x and not VT-d (IOMMU), so I excluded
            every feature relating to IOMMU in that regard.
```
<h3>(8) Maximum number of CPUs</h3>
```none
Symbol:     CONFIG_NR_CPUS

Help:       This allows you to specify the maximum number of CPUs which this
            kernel will support.  If CPUMASK_OFFSTACK is enabled, the maximum
            supported value is 8192, otherwise the maximum value is 512.  The
            minimum value which makes sense is 2.

            This is purely to save memory - each supported CPU adds
            approximately eight kilobytes to the kernel image. 

Type:       integer

Choice:     (8) custom

Reason:     Set this value equal to the maximum number of cores (and multiply
            it by 2 if it supports hyperthreading).

            In my case 4*2=8 so yeah...
```
<h3>[&ast;] SMT (Hyperthreading) scheduler support</h3>
```none
Symbol:     CONFIG_SCHED_SMT

Help:       SMT scheduler support improves the CPU scheduler's decision making
            when dealing with Intel Pentium 4 chips with HyperThreading at a
            cost of slightly increased overhead in some places. If unsure say
            N here. 

Type:       boolean

Choice:     built-in [*]

Reason:     I included this option because my cpu supports hyperthreading.
```
<h3>[ ] Multi-core scheduler support</h3>
```none
Symbol:     CONFIG_SCHED_MC

Help:       Multi-core scheduler support improves the CPU scheduler's decision
            making when dealing with multi-core CPU chips at a cost of slightly
            increased overhead in some places. If unsure say N here.

Type:       boolean

Choice:     excluded [ ]

Reason:     It's recommended that you exclude this option if your cpu supports
            hyperthreading and include CONFIG_SCHED_SMT instead.

            Including this option alongside CONFIG_SCHED_SMT may result in a
            noticable reduce in performance.
```
<h3>Preemption Model (Preemptible Kernel (Low-Latency Desktop))  ---></h3>
```none
Symbol:     CONFIG_PREEMPT

Help:       This option reduces the latency of the kernel by making
            all kernel code (that is not executing in a critical section)
            preemptible.  This allows reaction to interactive events by
            permitting a low priority process to be preempted involuntarily
            even if it is in kernel mode executing a system call and would
            otherwise not be about to reach a natural preemption point.
            This allows applications to run more 'smoothly' even when the
            system is under load, at the cost of slightly lower throughput
            and a slight runtime overhead to kernel code.

            Select this if you are building a kernel for a desktop or
            embedded system with latency requirements in the milliseconds
            range.

Type:       boolean

Choice:     built-in [*]

Reason:     I included this option as I'm building a low latency system.

            If you wanted maximum performance (throughput) but minimum
            responsiveness then you should include CONFIG_PREEMPT_NONE.
```
<h3>[ ] Reroute for broken boot IRQs</h3>
```none
Symbol:     CONFIG_X86_REROUTE_FOR_BROKEN_BOOT_IRQS

Help:       This option enables a workaround that fixes a source of
            spurious interrupts. This is recommended when threaded
            interrupt handling is used on systems where the generation of
            superfluous "boot interrupts" cannot be disabled.

            Some chipsets generate a legacy INTx "boot IRQ" when the IRQ
            entry in the chipset's IO-APIC is masked (as, e.g. the RT
            kernel does during interrupt handling). On chipsets where this
            boot IRQ generation cannot be disabled, this workaround keeps
            the original IRQ line masked so that only the equivalent "boot
            IRQ" is delivered to the CPUs. The workaround also tells the
            kernel to set up the IRQ handler on the boot IRQ line. In this
            way only one interrupt is delivered to the kernel. Otherwise
            the spurious second interrupt may cause the kernel to bring
            down (vital) interrupt lines.

            Only affects "broken" chipsets. Interrupt sharing may be
            increased on these systems.This

Type:       boolean

Choice:     excluded [ ]

Reason:     Exclude this option only if it's not needed on your modern system.
            
            You should include this option if you're receiving:
                
                irq X: nobody cared (try booting with "irqpoll" option)
```
<h3>[&ast;] Machine Check / overheating reporting</h3>
```none
Symbol:     CONFIG_X86_MCE

Help:       Machine Check support allows the processor to notify the
            kernel if it detects a problem (e.g. overheating, data corruption).
            The action the kernel takes depends on the severity of the problem,
            ranging from warning messages to halting the machine.

Type:       boolean

Choice:     built-in [*]

Reason:     Including this option is a must as it reports overheating
            and other problems (mostly hardware issues) to the kernel.
```
<h3>[ ]   Support for deprecated /dev/mcelog character device</h3>
```none
Symbol:     CONFIG_X86_MCELOG_LEGACY

Help:       Enable support for /dev/mcelog which is needed by the old mcelog
            userspace logging daemon. Consider switching to the new generation
            rasdaemon solution.

Type:       boolean

Choice:     excluded [ ]

Reason:     I'm not using mcelog so I excluded this option.
```
<h3>[&ast;]   Intel MCE features</h3>
```none
Symbol:     CONFIG_X86_MCE_INTEL

Help:       Additional support for intel specific MCE features such as
            the thermal monitor.

Type:       boolean

Choice:     built-in [*]

Reason:     If you've included CONFIG_X86_MCE and have an intel cpu then
            you should include this option as well.
```
<h3>Performance monitoring  ---></h3>
<h3><&ast;> Intel uncore performance events</h3>
```none
Symbol:     CONFIG_PERF_EVENTS_INTEL_UNCORE

Help:       Include support for Intel uncore performance events. These are
            available on NehalemEX and more modern processors.

Type:       tristate

Choice:     built-in <*>

Reason:     It's a good idea to include performance and cpu power monitors like 
            (rapl, uncore and cstate) for your intel cpu.
```
<h3><&ast;> Intel rapl performance events</h3>
```none
Symbol:     CONFIG_PERF_EVENTS_INTEL_RAPL

Help:       Include support for Intel rapl performance events for power
            monitoring on modern processors.

Type:       tristate

Choice:     built-in <*>

Reason:     It's a good idea to include performance and cpu power monitors like 
            (rapl, uncore and cstate) for your intel cpu.
```
<h3><&ast;> Intel cstate performance events</h3>
```none
Symbol:     CONFIG_PERF_EVENTS_INTEL_CSTATE

Help:       Include support for Intel cstate performance events for power
            monitoring on modern processors.

Type:       tristate

Choice:     built-in <*>

Reason:     It's a good idea to include performance and cpu power monitors like 
            (rapl, uncore and cstate) for your intel cpu.
```
<h3>[ ] Enable vsyscall emulation</h3>
```none
Symbol:     CONFIG_X86_VSYSCALL_EMULATION

Help:       This enables emulation of the legacy vsyscall page.  Disabling
            it is roughly equivalent to booting with vsyscall=none, except
            that it will also disable the helpful warning if a program
            tries to use a vsyscall.  With this option set to N, offending
            programs will just segfault, citing addresses of the form
            0xffffffffff600?00.

            This option is required by many programs built before 2013, and
            care should be used even with newer programs if set to N.

            Disabling this option saves about 7K of kernel size and
            possibly 4K of additional runtime pagetable memory.

Type:       boolean

Choice:     excluded [ ]

Reason:     VSYSCALLS are now disabled on most recent linux distros mainly for
            security reasons (it's almost deprecated now). However, this may break
            some old applications that may rely on this syscall.

            If you happen to see attempted vsyscalls in dmesg, then include this
            vsyscall emulation option.
```
<h3>< > Dell i8k legacy laptop support</h3>
```none
Symbol:     CONFIG_I8K

Help:       This option enables legacy /proc/i8k userspace interface in hwmon
            dell-smm-hwmon driver. Character file /proc/i8k reports bios version,
            temperature and allows controlling fan speeds of Dell laptops via
            System Management Mode. For old Dell laptops (like Dell Inspiron 8000)
            it reports also power and hotkey status. For fan speed control is
            needed userspace package i8kutils.

            Say Y if you intend to run this kernel on old Dell laptops or want to
            use userspace package i8kutils.
            Say N otherwise. 

Type:       tristate

Choice:     excluded < >

Reason:     I excluded this option as I'm not building the kernel for an old Dell
            laptop.
```
<h3>[&ast;] CPU microcode loading support</h3>
Don't forget to check DOTSLASHLINUX's guide on building microcode updates directly into the linux kernel to eliminate the need of using a detached initrd (if space constrained on embedded perhaps):
<br/>
<br/>
<a href="https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-directly-into-the-linux-kernel" target="_blank">Building Intel CPU Microcode Updates Directly into the Linux Kernel</a>
```none
Symbol:     CONFIG_MICROCODE

Help:       If you say Y here, you will be able to update the microcode on
            Intel and AMD processors. The Intel support is for the IA32 family,
            e.g. Pentium Pro, Pentium II, Pentium III, Pentium 4, Xeon etc. The
            AMD support is for families 0x10 and later. You will obviously need
            the actual microcode binary data itself which is not shipped with
            the Linux kernel.

            The preferred method to load microcode from a detached initrd is described
            in Documentation/x86/early-microcode.txt. For that you need to enable
            CONFIG_BLK_DEV_INITRD in order for the loader to be able to scan the
            initrd for microcode blobs.

            In addition, you can build-in the microcode into the kernel. For that you
            need to enable FIRMWARE_IN_KERNEL and add the vendor-supplied microcode
            to the CONFIG_EXTRA_FIRMWARE config option.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you update the microcode on your respective
            cpu as many of these updates improve the security and the performance
            of your cpu.

            I also recommend that you build the microcode into the kernel to eliminate
            the need of using a detached initrd.
```
<h3>[&ast;]   Intel microcode loading support</h3>
```none
Symbol:     CONFIG_MICROCODE_INTEL

Help:       This options enables microcode patch loading support for Intel
            processors.

            For the current Intel microcode data package go to
            <https://downloadcenter.intel.com> and search for
            'Linux Processor Microcode Data File'.

Type:       boolean

Choice:     built [*]

Reason:     Include this option to allow microcode loading for intel cpus.
```
<h3>[ ]   AMD microcode loading support</h3>
```none
Symbol:     CONFIG_MICROCODE_AMD

Help:       If you select this option, microcode patch loading support for AMD
            processors will be enabled.

Type:       boolean

Choice:     excluded [ ]

Reason:     I excluded this option as I'm building the kernel for an intel cpu.
```
<h3><&ast;> /dev/cpu/*/msr - Model-specific register support</h3>
```none
Symbol:     CONFIG_X86_MSR

Help:       This device gives privileged processes access to the x86
            Model-Specific Registers (MSRs).  It is a character device with
            major 202 and minors 0 to 31 for /dev/cpu/0/msr to /dev/cpu/31/msr.
            MSR accesses are directed to a specific CPU on multi-processor
            systems.

Type:       tristate

Choice:     built-in <*>

Reason:     
```
<h3><&ast;> /dev/cpu/*/cpuid - CPU information support</h3>
```none
Symbol:     CONFIG_X86_CPUID

Help:       This device gives processes access to the x86 CPUID instruction to
            be executed on a specific processor.  It is a character device
            with major 203 and minors 0 to 31 for /dev/cpu/0/cpuid to
            /dev/cpu/31/cpuid.

Type:       tristate

Choice:     built-in <*>

Reason:     
```
<h3>[ ] Numa Memory Allocation and Scheduler Support</h3>
```none
Symbol:     CONFIG_NUMA

Help:       Enable NUMA (Non Uniform Memory Access) support.

            The kernel will try to allocate memory used by a CPU on the
            local memory controller of the CPU and add some more
            NUMA awareness to the kernel.

            For 64-bit this is recommended if the system is Intel Core i7
            (or later), AMD Opteron, or EM64T NUMA.

            For 32-bit this is only needed if you boot a 32-bit
            kernel on a 64-bit NUMA platform.

            Otherwise, you should say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     Systems with multiple physical processors (multiple sockets) will 
            benefit from NUMA.
            
            However, systems with a single physical cpu (even if it had multiple
            cores, since all the cores share the same memory bus) won't see any
            benefit at all from NUMA and in some cases it may cause more harm
            than good.

            Since most i7s are single cpus and cores share the same memory bus,
            (I'll only be getting a single node in numa) I decided to exclude
            this feature.
```
<h3>Memory model (Sparse Memory)  ---></h3>
<h3>(X) Sparse Memory</h3>
```none
Symbol:     CONFIG_SPARSEMEM_MANUAL

Help:       This will be the only option for some systems, including
            memory hotplug systems.  This is normal.

            For many other systems, this will be an alternative to
            "Discontiguous Memory".  This option provides some potential
            performance benefits, along with decreased code complexity,
            but it is newer, and more experimental.

            If unsure, choose "Discontiguous Memory" or "Flat Memory"
            over this option.

Type:       boolean

Choice:     built-in (X)

Reason:     This is the only option available on my system so I included it.

            If you had a 32-bit cpu then you should include Flat Memory instead.
```
<h3>[&ast;] Sparse Memory virtual memmap</h3>
```none
Symbol:     CONFIG_SPARSEMEM_VMEMMAP

Help:       SPARSEMEM_VMEMMAP uses a virtually mapped memmap to optimise
            pfn_to_page and page_to_pfn operations.  This is the most
            efficient option when sufficient kernel resources are available.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommendded that you include this option (if you've
            chosen CONFIG_SPARSEMEM_MANUAL) since it boosts performance.
```
<h3>[ ] Allow for memory hot-add</h3>
```none
Symbol:     CONFIG_MEMORY_HOTPLUG

Help:       There is no help available for this option.

Type:       boolean

Choice:     excluded [ ]

Reason:     This option allows you to hotplug memory mainly for your virtual
            guests without down time (which is really helpful if you're upgrading
            your host server).

            I excluded this option as I have no use for it on my system.
```
<h3>-&ast;- Allow for memory compaction</h3>
```none
Symbol:     CONFIG_COMPACTION

Help:       Compaction is the only memory management component to form
            high order (larger physically contiguous) memory blocks
            reliably. The page allocator relies on compaction heavily and
            the lack of the feature can lead to unexpected OOM killer
            invocations for high order memory requests. You shouldn't
            disable this option unless there really is a strong reason for
            it and then we would be really interested to hear about that at
            linux-mm@kvack.org.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included and I don't have a strong reason to disable it =D.
```
<h3>-&ast;-   Page migration</h3>
```none
Symbol:     CONFIG_MIGRATION

Help:       Allows the migration of the physical location of pages of processes
            while the virtual addresses are not changed. This is useful in
            two situations. The first is on NUMA systems to put pages nearer
            to the processors accessing. The second is when allocating huge
            pages as migration can relocate pages to satisfy a huge page
            allocation instead of reclaiming.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included by CONFIG_COMPACTION even though I've excluded both
            CONFIG_NUMA and huge pages.
```
<h3>[&ast;] Enable bounce buffers</h3>
```none
Symbol:     CONFIG_BOUNCE

Help:       Enable bounce buffers for devices that cannot access
            the full range of memory available to the CPU. Enabled
            by default when ZONE_DMA or HIGHMEM is selected, but you
            may say n to override this.

Type:       boolean

Choice:     built-in [*]

Reason:     I included this as I'm using the proprietary nvidia driver and it
            relies on CONFIG_ZONE_DMA which in turn relies on CONFIG_BOUNCE.

            (When the nvidia attempts a DMA on an unreachable address it creates
            bounce buffers, or so I understood.)
```
