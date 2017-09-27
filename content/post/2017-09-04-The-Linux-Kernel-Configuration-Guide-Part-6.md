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
```properties
Symbol:     CONFIG_ZONE_DMA

Help:       DMA memory allocation support allows devices with less than 32-bit
            addressing to allocate within the first 16MB of address space.
            Disable if no such devices will be used.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option as it's required by
            x11-drivers/nvidia-drivers in order to get a working bumblebee setup on
            an optimus based laptop.

            DOTSLASHLINUX has a guide on how to setup bumblebee on Gentoo Linux:

                https://www.dotslashlinux.com/2017/06/04/setting-up-bumblebee-on-gentoo-linux/

            You can safely exclude this option if you're not on a optimus based laptop.
```
<h3>[&ast;] Symmetric multi-processing support</h3>
```properties
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

Reason:     It's highly recommended that you include this option in your kernel as
            The Help that came with this option actually meant cores, so if you had
            for example a single cpu with 1 core and 2 threads you should enable this
            as 1*2 is 2 logical cores, otherwise only 1 core will be detected.
```
<h3>[ ] Enable MPS table</h3>
```properties
Symbol:     CONFIG_X86_MPPARSE

Help:       For old smp systems that do not have proper acpi support. Newer systems
            (esp with 64bit cpus) with acpi support, MADT and DSDT will override it

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're using a modern system.
```
<h3>[ ] Intel Resource Director Technology Allocation support</h3>
```properties
Symbol:     CONFIG_INTEL_RDT_A

Help:       Select to enable resource allocation which is a sub-feature of
            Intel Resource Director Technology(RDT). More information about
            RDT can be found in the Intel x86 Architecture Software
            Developer Manual.

            Say N if unsure.

Type:       boolean

Choice:     built-in [*]

Reason:     You can safely exclude this option due to the lack of information
            and a proper list of intel CPUs that support this new feature
            that intel released in late 2016.
```
<h3>[ ] Support for extended (non-PC) x86 platforms</h3>
```properties
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
```properties
Symbol:     CONFIG_X86_INTEL_LPSS

Help:       Select to build support for Intel Low Power Subsystem such as
            found on Intel Lynxpoint PCH. Selecting this option enables
            things like clock tree (common clock framework) and pincontrol
            which are needed by the LPSS peripheral drivers.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're using an Intel CPU
            that uses an older microarchitecture than Skylake (some users
            say that Haswell CPUs are also supported).
```
<h3>[ ] AMD ACPI2Platform devices support</h3>
```properties
Symbol:     CONFIG_X86_AMD_PLATFORM_DEVICE

Help:       Select to interpret AMD specific ACPI device to platform device
            such as I2C, UART, GPIO found on AMD Carrizo and later chipsets.
            I2C and UART depend on COMMON_CLK to set clock. GPIO driver is
            implemented under PINCTRL subsystem.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not using these AMD
            chipsets.
```
<h3>-&ast;- Intel SoC IOSF Sideband support for SoC platforms</h3>
```properties
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

Reason:     You can safely exclude this option if you're not using an Intel SoC
            product.
            
            However, in a recent commit:

              https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/commit/?id=264ec1a8221c60f9ccf13f58ac597da21235132d

            it was forcibly included it, due to I915 wake up related problems.
```
<h3>[&ast;] Single-depth WCHAN output</h3>
```properties
Symbol:     CONFIG_SCHED_OMIT_FRAME_POINTER

Help:       Calculate simpler /proc/<PID>/wchan values. If this option
            is disabled then wchan values will recurse back to the
            caller function. This provides more accurate wchan values,
            at the expense of slightly more scheduling overhead.

            If in doubt, say "Y".Calculate

Type:       boolean

Choice:     excluded [ ]

Reason:     It's highly recommended that you include this option in your kernel
            to get simple wchan values as this will lower scheduling overhead.
```
<h3>[ ] Linux guest support  ----</h3>
```properties
Symbol:     CONFIG_HYPERVISOR_GUEST

Help:       Say Y here to enable options for running Linux under various hyper-
            visors. This option enables basic hypervisor detection and platform
            setup.

            If you say N, all options in this submenu will be skipped and
            disabled, and Linux guest support won't be built in.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're planning to use your
            custom built kernel on a host system.
```
<h3>Processor family (Core 2/newer Xeon)  ---></h3>
```properties
Symbol:     CONFIG_MCORE2

Help:       Select this for Intel Core 2 and newer Core 2 Xeons (Xeon 51xx and
            53xx) CPUs. You can distinguish newer from older Xeons by the CPU
            family in /proc/cpuinfo. Newer ones have 6 and older ones 15
            (not a typo)                                            

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option if you're using
            an Intel CPU newer that Core 2 (for example, Core i3, Core i5, Core i7
            and all new Intel CPUs).
            
            If you wanted your kernel to work on all X86_64 systems then include
            CONFIG_GENERIC_CPU.
```
<h3>[&ast;] Supported processor vendors  ---></h3>
```properties
Symbol:     CONFIG_PROCESSOR_SELECT

Help:       This lets you choose what x86 vendor support code your kernel
            will include.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you tell the kernel what type of CPU
            your system is using.

            In some cases, not doing so may result in an unbootable system.
```
<h3>Support Intel processors</h3>
```properties
Symbol:     CONFIG_CPU_SUP_INTEL

Help:       This enables detection, tunings and quirks for Intel processors
            
            You need this enabled if you want your kernel to run on an
            Intel CPU. Disabling this option on other types of CPUs
            makes the kernel a tiny bit smaller. Disabling it on an Intel
            CPU might render the kernel unbootable.
            
            If unsure, say N.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you're using an Intel CPU.
```
<h3>[&ast;] Enable DMI scanning</h3>
```properties
Symbol:     CONFIG_DMI

Help:       Enabled scanning of DMI to identify machine quirks. Say Y
            here unless you have verified that your setup is not
            affected by entries in the DMI blacklist. Required by PNP
            BIOS code.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by newer versions of udev to detect many of your 
            system's components (especially input devices such as the Synaptics
            PS/2 and SMBus touchpad).

            Excluding this option may result in an undetectable touchpad.
```
<h3>[ ] IBM Calgary IOMMU support</h3>
```properties
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

Reason:     You can safely exclude this option if your CPU doesn't support IOMMU.
            
            This includes Intel CPUs that support VT-x only and not VT-d, and AMD
            CPUs that don't support AMD-V.
            
```
<h3>(8) Maximum number of CPUs</h3>
```properties
Symbol:     CONFIG_NR_CPUS

Help:       This allows you to specify the maximum number of CPUs which this
            kernel will support.  If CPUMASK_OFFSTACK is enabled, the maximum
            supported value is 8192, otherwise the maximum value is 512.  The
            minimum value which makes sense is 2.

            This is purely to save memory - each supported CPU adds
            approximately eight kilobytes to the kernel image. 

Type:       integer

Choice:     (8) custom

Reason:     It's highly recommended that you set the value of this option equal to
            the maximum number of cores (and multiply it by 2 if it supports Hyper-Threading).

            For example, an Intel 4700MQ CPU, has 4 physical cores and supports Hyper-Threading
            so 4 * 2 = 8 which is the value I went with for this option.
```
<h3>[&ast;] SMT (Hyperthreading) scheduler support</h3>
```properties
Symbol:     CONFIG_SCHED_SMT

Help:       SMT scheduler support improves the CPU scheduler's decision making
            when dealing with Intel Pentium 4 chips with HyperThreading at a
            cost of slightly increased overhead in some places. If unsure say
            N here. 

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports Hyper-Threading.
```
<h3>[ ] Multi-core scheduler support</h3>
```properties
Symbol:     CONFIG_SCHED_MC

Help:       Multi-core scheduler support improves the CPU scheduler's decision
            making when dealing with multi-core CPU chips at a cost of slightly
            increased overhead in some places. If unsure say N here.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as many users reported that it
            reduced performance by 3-10%.
```
<h3>Preemption Model (No Forced Preemption (Server))  ---></h3>
<h3>(X) No Forced Preemption (Server)</h3>
```properties
Symbol:     CONFIG_PREEMPT_NONE

Help:       This is the traditional Linux preemption model, geared towards
            throughput. It will still provide good latencies most of the
            time, but there are no guarantees and occasional longer delays
            are possible.

            Select this option if you are building a kernel for a server or
            scientific/computation system, or if you want to maximize the
            raw processing power of the kernel, irrespective of scheduling
            latencies.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            for maximum throughput and performance.

            If latency is what matters most to you, you can include CONFIG_PREEMPT
            instead.
```
<h3>[ ] Reroute for broken boot IRQs</h3>
```properties
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

Reason:     You can safely exclude this option if you're not receiving:
                
                irq X: nobody cared (try booting with "irqpoll" option)
```
<h3>[&ast;] Machine Check / overheating reporting</h3>
```properties
Symbol:     CONFIG_X86_MCE

Help:       Machine Check support allows the processor to notify the
            kernel if it detects a problem (e.g. overheating, data corruption).
            The action the kernel takes depends on the severity of the problem,
            ranging from warning messages to halting the machine.

Type:       boolean

Choice:     built-in [*]

Reason:     It's hihgly recommended that you include this option in your kernel
            as it reports overheating and other problems (mostly hardware issues)
            to the kernel.
```
<h3>[ ]   Support for deprecated /dev/mcelog character device</h3>
```properties
Symbol:     CONFIG_X86_MCELOG_LEGACY

Help:       Enable support for /dev/mcelog which is needed by the old mcelog
            userspace logging daemon. Consider switching to the new generation
            rasdaemon solution.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not using app-admin/mcelog.
```
<h3>[&ast;]   Intel MCE features</h3>
```properties
Symbol:     CONFIG_X86_MCE_INTEL

Help:       Additional support for intel specific MCE features such as
            the thermal monitor.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_X86_MCE and have an Intel CPU.
```
<h3>Performance monitoring  ---></h3>
<h3><&ast;> Intel uncore performance events</h3>
```properties
Symbol:     CONFIG_PERF_EVENTS_INTEL_UNCORE

Help:       Include support for Intel uncore performance events. These are
            available on NehalemEX and more modern processors.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using an Intel CPU as performance and CPU power monitors
            are mandatory.
```
<h3><&ast;> Intel rapl performance events</h3>
```properties
Symbol:     CONFIG_PERF_EVENTS_INTEL_RAPL

Help:       Include support for Intel rapl performance events for power
            monitoring on modern processors.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using an Intel CPU as performance and CPU power monitors
            are mandatory.
```
<h3><&ast;> Intel cstate performance events</h3>
```properties
Symbol:     CONFIG_PERF_EVENTS_INTEL_CSTATE

Help:       Include support for Intel cstate performance events for power
            monitoring on modern processors.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if you're using an Intel CPU as performance and CPU power monitors
            are mandatory.
```
<h3>[ ] Enable vsyscall emulation</h3>
```properties
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

Reason:     You can safely exclude this option as VSYSCALLS are now disabled on
            most GNU/Linux distros mainly for security reasons (it's almost deprecated
            now).
            
            However, this may break some old applications that may rely on this syscall.

            Include this option only if you happen to see attempted vsyscalls in dmesg.
```
<h3>< > Dell i8k legacy laptop support</h3>
```properties
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

Reason:     You can safely exclude this option if you're not using an old Dell laptop.
```
<h3>[&ast;] CPU microcode loading support</h3>
```properties
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

Reason:     It's highly recommended that you include this option in your kernel
            as updating the microcode on your respective CPU improves the performance
            (and in some cases the security) of your CPU.

            DOTSLASHLINUX has a guide on building microcode updates directly into the Linux
            kernel to eliminate the need of using a detached initrd:
                
                https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-updates-directly-into-the-linux-kernel/
```
<h3>[&ast;]   Intel microcode loading support</h3>
```properties
Symbol:     CONFIG_MICROCODE_INTEL

Help:       This options enables microcode patch loading support for Intel
            processors.

            For the current Intel microcode data package go to
            <https://downloadcenter.intel.com> and search for
            'Linux Processor Microcode Data File'.

Type:       boolean

Choice:     built [*]

Reason:     It's highly recommended that you include this option in your kernel
            as updating the microcode on your respective CPU improves the performance
            (and in some cases the security) of your CPU.

            DOTSLASHLINUX has a guide on building Intel CPU microcode updates directly into
            the Linux kernel to eliminate the need of using a detached initrd:
                
                https://www.dotslashlinux.com/2017/04/30/building-intel-cpu-microcode-updates-directly-into-the-linux-kernel/
```
<h3>[ ]   AMD microcode loading support</h3>
```properties
Symbol:     CONFIG_MICROCODE_AMD

Help:       If you select this option, microcode patch loading support for AMD
            processors will be enabled.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not using an AMD CPU.
```
<h3><&ast;> /dev/cpu/*/msr - Model-specific register support</h3>
```properties
Symbol:     CONFIG_X86_MSR

Help:       This device gives privileged processes access to the x86
            Model-Specific Registers (MSRs).  It is a character device with
            major 202 and minors 0 to 31 for /dev/cpu/0/msr to /dev/cpu/31/msr.
            MSR accesses are directed to a specific CPU on multi-processor
            systems.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports it.

            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.
            
            To see the flags that your CPU supports simply run:
                
                cat /proc/cpuinfo | grep flags

            And to see what these flags mean check this link:

                https://unix.stackexchange.com/questions/43539/what-do-the-flags-in-proc-cpuinfo-mean

            To check for MSR support, simply run:
                
                cat /proc/cpuinfo | grep msr
```
<h3><&ast;> /dev/cpu/*/cpuid - CPU information support</h3>
```properties
Symbol:     CONFIG_X86_CPUID

Help:       This device gives processes access to the x86 CPUID instruction to
            be executed on a specific processor.  It is a character device
            with major 203 and minors 0 to 31 for /dev/cpu/0/cpuid to
            /dev/cpu/31/cpuid.

Type:       tristate

Choice:     built-in <*>

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports it.

            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.
            
            To see the flags that your CPU supports simply run:
                
                cat /proc/cpuinfo | grep flags

            And to see what these flags mean check this link:

                https://unix.stackexchange.com/questions/43539/what-do-the-flags-in-proc-cpuinfo-mean

            To check for CPUID support, simply run:
                
                cat /proc/cpuinfo | grep cpuid
```
<h3>[ ] Numa Memory Allocation and Scheduler Support</h3>
```properties
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

Reason:     You can safely exclude this option as it's only useful for systems
            with multiple physical processors (multiple sockets).

            Systems with a single physical cpu (even if it had multiple
            cores, as all these cores share the same memory bus) won't see any
            benefit at all from NUMA and in some cases it may cause more harm
            than good.
```
<h3>Memory model (Sparse Memory)  ---></h3>
<h3>(X) Sparse Memory</h3>
```properties
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

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included as it's the only
            available option on many systems).
```
<h3>[&ast;] Sparse Memory virtual memmap</h3>
```properties
Symbol:     CONFIG_SPARSEMEM_VMEMMAP

Help:       SPARSEMEM_VMEMMAP uses a virtually mapped memmap to optimise
            pfn_to_page and page_to_pfn operations.  This is the most
            efficient option when sufficient kernel resources are available.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommendded that you include this option in your kernel
            if you've already included CONFIG_SPARSEMEM_MANUAL since it boosts performance.
```
<h3>[ ] Allow for memory hot-add</h3>
```properties
Symbol:     CONFIG_MEMORY_HOTPLUG

Help:       There is no help available for this option.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's only useful for some certain
            cloud hosting services, that want to perform live system upgrades without
            experiencing any down time.
```
<h3>-&ast;- Allow for memory compaction</h3>
```properties
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

Reason:     It's highly recommended that you include this option in your kernel
            as it speeds up your system at the cost of some latency.
```
<h3>-&ast;-   Page migration</h3>
```properties
Symbol:     CONFIG_MIGRATION

Help:       Allows the migration of the physical location of pages of processes
            while the virtual addresses are not changed. This is useful in
            two situations. The first is on NUMA systems to put pages nearer
            to the processors accessing. The second is when allocating huge
            pages as migration can relocate pages to satisfy a huge page
            allocation instead of reclaiming.

Type:       boolean

Choice:     built-in -*-

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included by CONFIG_COMPACTION).
```
<h3>[&ast;] Enable bounce buffers</h3>
```properties
Symbol:     CONFIG_BOUNCE

Help:       Enable bounce buffers for devices that cannot access
            the full range of memory available to the CPU. Enabled
            by default when ZONE_DMA or HIGHMEM is selected, but you
            may say n to override this.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_ZONE_DMA (if you have an NVIDIA GPU
            for example, as the nvidia module creates bounce buffers when attempting
            a DMA on an unreachable address.
```
<h3>[&ast;] Enable KSM for page merging</h3>
```properties
Symbol:     CONFIG_KSM

Help:       Enable Kernel Samepage Merging: KSM periodically scans those areas
            of an application's address space that an app has advised may be
            mergeable.  When it finds pages of identical content, it replaces
            the many instances by a single page with that content, so
            saving memory until one or another app needs to modify the content.
            Recommended for use with KVM, or with other duplicative applications.
            See Documentation/vm/ksm.txt for more information: KSM is inactive
            until a program has madvised that an area is MADV_MERGEABLE, and
            root has set /sys/kernel/mm/ksm/run to 1 (if CONFIG_SYSFS is set).

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as KSM helps save a lot of memory.

            You should also look into using UKSM which saves more memory than
            KSM, but isn't in mainline.
```
<h3>(0) Low address space to protect from user allocation</h3>
```properties
Symbol:     CONFIG_DEFAULT_MMAP_MIN_ADDR

Help:       This is the portion of low virtual memory which should be protected
            from userspace allocation.  Keeping a user from writing to low pages
            can help reduce the impact of kernel NULL pointer bugs.

            For most ia64, ppc64 and x86 users with lots of address space
            a value of 65536 is reasonable and should cause no problems.
            On arm and other archs it should not be higher than 32768.
            Programs which use vm86 functionality or have some need to map
            this low address space will need CAP_SYS_RAWIO or disable this
            protection by setting the value to 0.

            This value can be changed after boot using the
            /proc/sys/vm/mmap_min_addr tunable.

Type:       integer

Choice:     (0) custom

Reason:     You can safely set the value of this option to (0) to disable this
            protection feature and lower system overhead.

            The default value is (4096), which allows for some protection while allowing
            emulators and WINE to run. (Many users reported that setting this
            to 64k has caused problems for WINE and DOSemu.) 
```
<h3>[ ] Enable recovery from hardware memory errors</h3>
```properties
Symbol:     CONFIG_MEMORY_FAILURE

Help:       Enables code to recover from some memory failures on systems
            with MCA recovery. This allows a system to continue running
            even when some of its memory has uncorrected errors. This requires
            special hardware support and typically ECC memory.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you don't have ECC memory.
            
            You can check if you have ECC memory by running:
              
                dmidecode -t 17

            "Total Width:" should be 72 bits for ECC memory and 64 bits for non-ECC
            memory.
```
<h3>[ ] Transparent Hugepage Support</h3>
```properties
Symbol:     CONFIG_TRANSPARENT_HUGEPAGE

Help:       Transparent Hugepages allows the kernel to use huge pages and
            huge tlb transparently to the applications whenever possible.
            This feature can improve computing performance to certain
            applications by speeding up page faults during memory
            allocation, by reducing the number of tlb misses and by speeding
            up the pagetable walking.

            If memory constrained on embedded, you may want to say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's only useful for
            virtualization purposes with KVM.
```
<h3>[ ] Enable cleancache driver to cache clean pages if tmem is present</h3>
```properties
Symbol:     CONFIG_CLEANCACHE

Help:       Cleancache can be thought of as a page-granularity victim cache
            for clean pages that the kernel's pageframe replacement algorithm
            (PFRA) would like to keep around, but can't since there isn't enough
            memory.  So when the PFRA "evicts" a page, it first attempts to use
            cleancache code to put the data contained in that page into
            "transcendent memory", memory that is not directly accessible or
            addressable by the kernel and is of unknown and possibly
            time-varying size.  And when a cleancache-enabled
            filesystem wishes to access a page in a file on disk, it first
            checks cleancache to see if it already contains it; if it does,
            the page is copied into the kernel and a disk access is avoided.
            When a transcendent memory driver is available (such as zcache or
            Xen transcendent memory), a significant I/O reduction
            may be achieved.  When none is available, all cleancache calls
            are reduced to a single pointer-compare-against-NULL resulting
            in a negligible performance hit.

            If unsure, say Y to enable cleancache

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not running multiple
            VM guests that cache the same data (identical VM guests).
            
            Include this option only if you want multiple VM guests that cache
            the same data to do that using the same RAM. You'll also need to let
            the hypervisor manage the memory (ex. xen tmem).
```
<h3>[ ] Enable frontswap to cache swap pages if tmem is present</h3>
```properties
Symbol:     CONFIG_FRONTSWAP

Help:       Frontswap is so named because it can be thought of as the opposite
            of a "backing" store for a swap device.  The data is stored into
            "transcendent memory", memory that is not directly accessible or
            addressable by the kernel and is of unknown and possibly
            time-varying size.  When space in transcendent memory is available,
            a significant swap I/O reduction may be achieved.  When none is
            available, all frontswap calls are reduced to a single pointer-
            compare-against-NULL resulting in a negligible performance hit
            and swap data is stored as normal on the matching swap device.

            If unsure, say Y to enable frontswap.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as caching swap pages will increase
            your system's overhead.
```
<h3>[ ] Contiguous Memory Allocator</h3>
```properties
Symbol:     CONFIG_CMA

Help:       This enables the Contiguous Memory Allocator which allows other
            subsystems to allocate big physically-contiguous blocks of memory.
            CMA reserves a region of memory and allows only movable pages to
            be allocated from it. This way, the kernel can use the memory for
            pagecache and when a subsystem requests for contiguous area, the
            allocated pages are migrated away to serve the contiguous request.

            If unsure, say "n".

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option to lower system overhead.
```
<h3>< > Common API for compressed memory storage</h3>
```properties
Symbol:     CONFIG_ZPOOL

Help:       Compressed memory storage API.  This allows using either zbud or
            zsmalloc.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you're not using compressed
            memory.
```
<h3>< > Low (Up to 2x) density storage for compressed pages</h3>
```properties
Symbol:     CONFIG_ZBUD

Help:       A special purpose allocator for storing compressed pages.
            It is designed to store up to two compressed pages per physical
            page.  While this design limits storage density, it has simple and
            deterministic reclaim properties that make it preferable to a higher
            density approach when reclaim will be used.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you're not using compressed
            memory pages.
```
<h3>< > Memory allocator for compressed pages</h3>
```properties
Symbol:     CONFIG_ZSMALLOC

Help:       zsmalloc is a slab-based memory allocator designed to store
            compressed RAM pages.  zsmalloc uses virtual memory mapping
            in order to reduce fragmentation.  However, this results in a
            non-standard allocator interface where a handle, not a pointer, is
            returned by an alloc().  This handle must be mapped in order to
            access the allocated space.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you're not using compressed
            memory pages.
```
<h3>[ ] Enable idle page tracking</h3>
```properties
Symbol:     CONFIG_IDLE_PAGE_TRACKING

Help:       This feature allows to estimate the amount of user pages that have
            not been touched during a given period of time. This information can
            be useful to tune memory cgroup limits and/or for job placement
            within a compute cluster.

            See Documentation/vm/idle_page_tracking.txt for more details.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you've already excluded CONFIG_CGROUPS.
```
<h3>< > Support non-standard NVDIMMs and ADR protected memory</h3>
```properties
Symbol:     CONFIG_X86_PMEM_LEGACY

Help:       Treat memory marked using the non-standard e820 type of 12 as used
            by the Intel Sandy Bridge-EP reference BIOS as protected memory.
            The kernel will offer these regions to the 'pmem' driver so
            they can be used for persistent storage.

            Say Y if unsure.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option if you're not seeing errors when running:
                
                dmesg | grep e820
```
<h3>[ ] Check for low memory corruption</h3>
```properties
Symbol:     CONFIG_X86_CHECK_BIOS_CORRUPTION

Help:       Periodically check for memory corruption in low memory, which
            is suspected to be caused by BIOS.  Even when enabled in the
            configuration, it is disabled at runtime.  Enable it by
            setting "memory_corruption_check=1" on the kernel command
            line.  By default it scans the low 64k of memory every 60
            seconds; see the memory_corruption_check_size and
            memory_corruption_check_period parameters in
            Documentation/admin-guide/kernel-parameters.rst to adjust this.

            When enabled with the default parameters, this option has
            almost no overhead, as it reserves a relatively small amount
            of memory and scans it infrequently.  It both detects corruption
            and prevents it from affecting the running system.

            It is, however, intended as a diagnostic tool; if repeatable
            BIOS-originated corruption always affects the same memory,
            you can use memmap= to prevent the kernel from using that
            memory.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as BIOS corruptions are extremely
            rare even on buggy BIOSes like mine.            
```
<h3>(64) Amount of low memory, in kilobytes, to reserve for the BIOS</h3>
```properties
Symbol:     CONFIG_X86_RESERVE_LOW

Help:       Specify the amount of low memory to reserve for the BIOS.

            The first page contains BIOS data structures that the kernel
            must not use, so that page must always be reserved.

            By default we reserve the first 64K of physical RAM, as a
            number of BIOSes are known to corrupt that memory range
            during events such as suspend/resume or monitor cable
            insertion, so it must not be used by the kernel.

            You can set this to 4 if you are absolutely sure that you
            trust the BIOS to get all its memory reservations and usages
            right.  If you know your BIOS have problems beyond the
            default 64K area, you can set this to 640 to avoid using the
            entire low memory range.

            If you have doubts about the BIOS (e.g. suspend/resume does
            not work or there's kernel crashes after certain hardware
            hotplug events) then you might want to enable
            X86_CHECK_BIOS_CORRUPTION=y to allow the kernel to check
            typical corruption patterns.

            Leave this to the default value of 64 if you are unsure.

Type:       integer

Choice:     (64) default

Reason:     It's highly recommend that you set the value of this option to (64)
            which is the default value.

            You can run:

                lshw -short | grep BIOS

            and see what value is printed next to your BIOS.
```
<h3>[&ast;] MTRR (Memory Type Range Register) support</h3>
```properties
Symbol:     CONFIG_MTRR

Help:       On Intel P6 family processors (Pentium Pro, Pentium II and later)
            the Memory Type Range Registers (MTRRs) may be used to control
            processor access to memory ranges. This is most useful if you have
            a video (VGA) card on a PCI or AGP bus. Enabling write-combining
            allows bus write transfers to be combined into a larger transfer
            before bursting over the PCI/AGP bus. This can increase performance
            of image write operations 2.5 times or more. Saying Y here creates a
            /proc/mtrr file which may be used to manipulate your processor's
            MTRRs. Typically the X server should use this.

            This code has a reasonably generic interface so that similar
            control registers on other processors can be easily supported
            as well:

            The Cyrix 6x86, 6x86MX and M II processors have Address Range
            Registers (ARRs) which provide a similar functionality to MTRRs. For
            these, the ARRs are used to emulate the MTRRs.
            The AMD K6-2 (stepping 8 and above) and K6-3 processors have two
            MTRRs. The Centaur C6 (WinChip) has 8 MCRs, allowing
            write-combining. All of these processors are supported by this code
            and it makes sense to say Y here if you have one of them.

            Saying Y here also fixes a problem with buggy SMP BIOSes which only
            set the MTRRs for the boot CPU and not for the secondary CPUs. This
            can lead to all sorts of problems, so it's good to say Y here.

            You can safely say Y even if your machine doesn't have MTRRs, you'll
            just add about 9 KB to your kernel.

            See <file:Documentation/x86/mtrr.txt> for more information.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports it, as MTRR is really useful for applications such
            as the X server as it allows it to control how the CPU caches memory
            accesses resulting in a read/write boosts to certain memory ranges.

            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.
            
            To see the flags that your CPU supports simply run:
                
                cat /proc/cpuinfo | grep flags

            And to see what these flags mean check this link:

                https://unix.stackexchange.com/questions/43539/what-do-the-flags-in-proc-cpuinfo-mean

            To check for MTRR support, simply run:
                
                cat /proc/cpuinfo | grep mtrr
```
<h3>[&ast;]   MTRR cleanup support</h3>
```properties
Symbol:     CONFIG_MTRR_SANITIZER

Help:       Convert MTRR layout from continuous to discrete, so X drivers can
            add writeback entries.

            Can be disabled with disable_mtrr_cleanup on the kernel command line.
            The largest mtrr entry size for a continuous block can be set with
            mtrr_chunk_size.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as it fixes most MTRR programming issues in the kernel.
```
<h3>(1)     MTRR cleanup enable value (0-1)</h3>
```properties
Symbol:     CONFIG_MTRR_SANITIZER_ENABLE_DEFAULT

Help:       Enable mtrr cleanup default value

Type:       integer

Choice:     (1) custom

Reason:     It's highly recommended that you set the value of this option to (1)
            to enable mtrr cleanup.
```
<h3>(1)     MTRR cleanup spare reg num (0-7)</h3>
```properties
Symbol:     CONFIG_MTRR_SANITIZER_SPARE_REG_NR_DEFAULT

Help:       mtrr cleanup spare entries default, it can be changed via
            mtrr_spare_reg_nr=N on the kernel command line.

Type:       integer

Choice:     (1) default?

Reason:     It's highly recommended that you set the value of this option to (1).

            Some users reported that setting this and the value of
            CONFIG_MTRR_SANITIZER_ENABLE_DEFAULT to 1 helped them get rid of
            MTRR errors and type mismatch errors.
```
<h3>[&ast;]   x86 PAT support</h3>
```properties
Symbol:     CONFIG_X86_PAT

Help:       Use PAT attributes to setup page level cache control.

            PATs are the modern equivalents of MTRRs and are much more
            flexible than MTRRs.

            Say N here if you see bootup problems (boot crash, boot hang,
            spontaneous reboots) or a non-working video driver.

            If unsure, say Y.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports it.

            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.
            
            To see the flags that your CPU supports simply run:
                
                cat /proc/cpuinfo | grep flags

            And to see what these flags mean check this link:

                https://unix.stackexchange.com/questions/43539/what-do-the-flags-in-proc-cpuinfo-mean

            To check for PAT support, simply run:
                
                cat /proc/cpuinfo | grep pat
```
<h3>[&ast;] x86 architectural random number generator</h3>
```properties
Symbol:     CONFIG_ARCH_RANDOM

Help:       Enable the x86 architectural RDRAND instruction
            (Intel Bull Mountain technology) to generate random numbers.
            If supported, this is a high bandwidth, cryptographically
            secure hardware random number generator.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            if your CPU supports it.

            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.
            
            To see the flags that your CPU supports simply run:
                
                cat /proc/cpuinfo | grep flags

            And to see what these flags mean check this link:

                https://unix.stackexchange.com/questions/43539/what-do-the-flags-in-proc-cpuinfo-mean

            To check for RDRAND support, simply run:
                
                cat /proc/cpuinfo | grep rdrand
```
<h3>[ ] Supervisor Mode Access Prevention</h3>
```properties
Symbol:     CONFIG_X86_SMAP

Help:       Supervisor Mode Access Prevention (SMAP) is a security
            feature in newer Intel processors.  There is a small
            performance cost if this enabled and turned on; there is
            also a small increase in the kernel size if this is enabled.

            If unsure, say Y.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your CPU doesn't support SMAP,
            as it increases security at the cost of performance.
```
<h3>[ ] Intel MPX (Memory Protection Extensions)</h3>
```properties
Symbol:     CONFIG_X86_INTEL_MPX

Help:       MPX provides hardware features that can be used in
            conjunction with compiler-instrumented code to check
            memory references.  It is designed to detect buffer
            overflow or underflow bugs.

            This option enables running applications which are
            instrumented or otherwise use MPX.  It does not use MPX
            itself inside the kernel or to protect the kernel
            against bad memory references.

            Enabling this option will make the kernel larger:
            ~8k of kernel text and 36 bytes of data on a 64-bit
            defconfig.  It adds a long to the 'mm_struct' which
            will increase the kernel memory overhead of each
            process and adds some branches to paths used during
            exec() and munmap().

            For details, see Documentation/x86/intel_mpx.txt

            If unsure, say N.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your CPU doesn't support MPX,
            as it increases security at the cost of performance.
```
<h3>[ ] Intel Memory Protection Keys</h3>
```properties
Symbol:     CONFIG_X86_INTEL_MEMORY_PROTECTION_KEYS

Help:       Memory Protection Keys provides a mechanism for enforcing
            page-based protections, but without requiring modification of the
            page tables when an application changes protection domains.

            For details, see Documentation/x86/protection-keys.txt

            If unsure, say y.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if your CPU doesn't support Memory
            Protection Keys as it increases security at the cost of performance.
```
<h3>[ ] EFI runtime service support</h3>
```properties
Symbol:     CONFIG_EFI

Help:       This enables the kernel to use EFI runtime services that are
            available (such as the EFI variable services).

            This option is only useful on systems that have EFI firmware.
            In addition, you should use the latest ELILO loader available
            at <http://elilo.sourceforge.net> in order to take advantage
            of EFI runtime services. However, even with this option, the
            resultant kernel should continue to boot on existing non-EFI
            platforms.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're using MBR (MSDOS partition table)
            on your storage device.

            On some laptops (especially Toshiba laptops from late 2013), UEFI
            implementations are pretty buggy. These laptops usually come with both
            a BIOS and a UEFI implementation. Usually the BIOS is pretty buggy and the
            UEFI implementation rarely works (even if it did work, you may see
            error messages like unable to detect a bootable medium, or please insert
            a bootable medium, for like 5 seconds before the system starts booting
            normally).
```
<h3>[&ast;] Enable seccomp to safely compute untrusted bytecode</h3>
```properties
Symbol:     CONFIG_SECCOMP

Help:       This kernel feature is useful for number crunching applications
            that may need to compute untrusted bytecode during their
            execution. By using pipes or other transports made available to
            the process as file descriptors supporting the read/write
            syscalls, it's possible to isolate those applications in
            their own address space using seccomp. Once seccomp is
            enabled via prctl(PR_SET_SECCOMP), it cannot be disabled
            and the task is only allowed to execute a few safe syscalls
            defined by each seccomp mode.

            If unsure, say Y. Only embedded should say N here.

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as the security advantages it offers overweigh the near-minimum gains
            acheived by excluding it (no gains are gains with a damaged system).
```
<h3>Timer frequency (100 HZ)  ---></h3>
```properties
Help:       Allows the configuration of the timer frequency. It is customary
            to have the timer interrupt run at 1000 Hz but 100 Hz may be more
            beneficial for servers and NUMA systems that do not need to have
            a fast response for user interaction and that may experience bus
            contention and cacheline bounces as a result of timer interrupts.
            Note that the timer interrupt occurs on each processor in an SMP
            environment leading to NR_CPUS * HZ number of timer interrupts
            per second.
```
<h3>(X) 100 HZ</h3>
```properties
Symbol:     CONFIG_HZ_100_MUQSS

Help:       100 Hz is a suitable choice in combination with MuQSS which does
            not rely on ticks for rescheduling interrupts, and is not Hz limited
            for timeouts and sleeps from both the kernel and userspace.
            This allows us to benefit from the lower overhead and higher
            throughput of fewer timer ticks.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            if you've already included CONFIG_PREEMPT_NONE, as it boosts
            performance considerably at the cost of some latency.
```
<h3>[ ] kexec system call</h3>
```properties
Symbol:     CONFIG_KEXEC

Help:       kexec is a system call that implements the ability to shutdown your
            current kernel, and to start another kernel.  It is like a reboot
            but it is independent of the system firmware.   And like a reboot
            you can start any kernel with it, not just Linux.

            The name comes from the similarity to the exec system call.

            It is an ongoing process to be certain the hardware in a machine
            is properly shutdown, so do not be surprised if this code does not
            initially work for you.  As of this writing the exact hardware
            interface is strongly in flux, so no good recommendation can be
            made.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not planning on shutting
            down your current kernel to execute another kernel.
```
<h3>[ ] kexec file based system call</h3>
```properties
Symbol:     CONFIG_KEXEC_FILE

Help:       This is new version of kexec system call. This system call is
            file based and takes file descriptors as system call argument
            for kernel and initramfs as opposed to list of segments as
            accepted by previous system call.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not planning on shutting
            down your current kernel to execute another kernel.
```
<h3>[ ] kernel crash dumps</h3>
```properties
Symbol:     CONFIG_CRASH_DUMP

Help:       Generate crash dump after being started by kexec.
            This should be normally only set in special crash dump kernels
            which are loaded in the main kernel with kexec-tools into
            a specially reserved region and then later executed after
            a crash by kdump/kexec. The crash dump kernel must be compiled
            to a memory address not used by the main kernel or BIOS using
            PHYSICAL_START, or it must be built as a relocatable image
            (CONFIG_RELOCATABLE=y).
            For more details see Documentation/kdump/kdump.txt

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're not planning on shutting
            down your current kernel to execute another kernel.
```
<h3>(0x1000000) Physical address where the kernel is loaded</h3>
```properties
Symbol:     CONFIG_PHYSICAL_START

Help:       This gives the physical address where the kernel is loaded.

            If kernel is a not relocatable (CONFIG_RELOCATABLE=n) then
            bzImage will decompress itself to above physical address and
            run from there. Otherwise, bzImage will run from the address where
            it has been loaded by the boot loader and will ignore above physical
            address.

            In normal kdump cases one does not have to set/change this option
            as now bzImage can be compiled as a completely relocatable image
            (CONFIG_RELOCATABLE=y) and be used to load and run from a different
            address. This option is mainly useful for the folks who don't want
            to use a bzImage for capturing the crash dump and want to use a
            vmlinux instead. vmlinux is not relocatable hence a kernel needs
            to be specifically compiled to run from a specific memory area
            (normally a reserved region) and this option comes handy.

            So if you are using bzImage for capturing the crash dump,
            leave the value here unchanged to 0x1000000 and set
            CONFIG_RELOCATABLE=y.  Otherwise if you plan to use vmlinux
            for capturing the crash dump change this value to start of
            the reserved region.  In other words, it can be set based on
            the "X" value as specified in the "crashkernel=YM@XM"
            command line boot parameter passed to the panic-ed
            kernel. Please take a look at Documentation/kdump/kdump.txt
            for more details about crash dumps.

            Usage of bzImage for capturing the crash dump is recommended as
            one does not have to build two kernels. Same kernel can be used
            as production kernel and capture kernel. Above option should have
            gone away after relocatable bzImage support is introduced. But it
            is present because there are users out there who continue to use
            vmlinux for dump capture. This option should go away down the
            line.

            Don't change this unless you know what you are doing.

Type:       hex

Choice:     (0x1000000) default

Reason:     It's highly recommended that you leave the value of this option set
            to its default value of (0x1000000) unles you seriously know what you're
            doing.
```
<h3>[ ] Build a relocatable kernel</h3>
```properties
Symbol:     CONFIG_RELOCATABLE

Help:       This builds a kernel image that retains relocation information
            so it can be loaded someplace besides the default 1MB.
            The relocations tend to make the kernel binary about 10% larger,
            but are discarded at runtime.

            One use is for the kexec on panic case where the recovery kernel
            must live at a different physical address than the primary
            kernel.

            Note: If CONFIG_RELOCATABLE=y, then the kernel runs from the address
            it has been loaded at and the compile time physical address
            (CONFIG_PHYSICAL_START) is used as the minimum location.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you don't plan on using kexec to
            execute a recovery kernel.

            This is useful for users who may want to execute a rescue/recovery
            kernel since it's obvious that the new executed kernel should be
            placed (should live) in a differnt physical memory address than
            the primary kernel (the one with errors).
```
<h3>(0x200000) Alignment value to which kernel should be aligned</h3>
```properties
Symbol:     CONFIG_PHYSICAL_ALIGN

Help:       This value puts the alignment restrictions on physical address
            where kernel is loaded and run from. Kernel is compiled for an
            address which meets above alignment restriction.

            If bootloader loads the kernel at a non-aligned address and
            CONFIG_RELOCATABLE is set, kernel will move itself to nearest
            address aligned to above value and run from there.

            If bootloader loads the kernel at a non-aligned address and
            CONFIG_RELOCATABLE is not set, kernel will ignore the run time
            load address and decompress itself to the address it has been
            compiled for and run from there. The address for which kernel is
            compiled already meets above alignment restrictions. Hence the
            end result is that kernel runs from a physical address meeting
            above alignment restrictions.

            On 32-bit this value must be a multiple of 0x2000. On 64-bit
            this value must be a multiple of 0x200000.

            Don't change this unless you know what you are doing.

Type:       hex

Choice:     (0x200000) default

Reason:     It's highly recommended that you leave the value of this option set
            to its default value of (0x1000000) unles you seriously know what you're
            doing.
```
<h3>[ ] Support for hot-pluggable CPUs</h3>
```properties
Symbol:     CONFIG_HOTPLUG_CPU

Help:       Say Y here to allow turning CPUs off and on. CPUs can be
            controlled through /sys/devices/system/cpu.
            ( Note: power management support will enable this option
              automatically on SMP systems. )
            Say N if you want to disable CPU hotplug.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it'll be forcibly included
            by some power saving options.

            Include this option only if you want suspend/resume support.
```
<h3>[ ] Disable the 32-bit vDSO (needed for glibc 2.3.3)</h3>
```properties
Symbol:     CONFIG_COMPAT_VDSO

Help:       Certain buggy versions of glibc will crash if they are
            presented with a 32-bit vDSO that is not mapped at the address
            indicated in its segment table.

            The bug was introduced by f866314b89d56845f55e6f365e18b31ec978ec3a
            and fixed by 3b3ddb4f7db98ec9e912ccdf54d35df4aa30e04a and
            49ad572a70b8aeb91e57483a11dd1b77e31c4468.  Glibc 2.3.3 is
            the only released version with the bug, but OpenSUSE 9
            contains a buggy "glibc 2.3.2".

            The symptom of the bug is that everything crashes on startup, saying:
            dl_main: Assertion `(void *) ph->p_vaddr == _rtld_local._dl_sysinfo_dso' failed!

            Saying Y here changes the default value of the vdso32 boot
            option from 1 to 0, which turns off the 32-bit vDSO entirely.
            This works around the glibc bug but hurts performance.

            If unsure, say N: if you are compiling your own kernel, you
            are unlikely to be using a buggy version of glibc.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're using newer versions
            of glibc as it hurts performance.

            Include this option only if you're sure that your glibc version and
            settings require it (which is highly unlikely).
```
<h3>vsyscall table for legacy applications (None)  ---></h3>
```properties
Help:       Legacy user code that does not know how to find the vDSO expects
            to be able to issue three syscalls by calling fixed addresses in
            kernel space. Since this location is not randomized with ASLR,
            it can be used to assist security vulnerability exploitation.

            This setting can be changed at boot time via the kernel command
            line parameter vsyscall=[native|emulate|none].

            On a system with recent enough glibc (2.14 or newer) and no
            static binaries, you can say None without a performance penalty
            to improve security.

            If unsure, select "Emulate".
```
<h3>(X) None</h3>
```properties
Symbol:     CONFIG_LEGACY_VSYSCALL_NONE

Help:       There will be no vsyscall mapping at all. This will
            eliminate any risk of ASLR bypass due to the vsyscall
            fixed address mapping. Attempts to use the vsyscalls
            will be reported to dmesg, so that either old or
            malicious userspace programs can be identified.

Type:       boolean

Choice:     built-in (X)

Reason:     You can safely exclude this option if you're using a recent version
            of glibc.
```
<h3>[ ] Built-in kernel command line</h3>
```properties
Symbol:     CONFIG_CMDLINE_BOOL

Help:       Allow for specifying boot arguments to the kernel at
            build time.  On some systems (e.g. embedded ones), it is
            necessary or convenient to provide some or all of the
            kernel boot arguments with the kernel itself (that is,
            to not rely on the boot loader to provide them.)

            To compile command line arguments into the kernel,
            set this option to 'Y', then fill in the
            boot arguments in CONFIG_CMDLINE.

            Systems with fully functional boot loaders (i.e. non-embedded)
            should leave this option set to 'N'.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're using a fully functional
            boot loader (LILO, Syslinux, GRUB....etc) and the kernel isn't
            being built for an embedded system.
```
<h3>[ ] Enable the LDT (local descriptor table)</h3>
```properties
Symbol:     CONFIG_MODIFY_LDT_SYSCALL

Help:       Linux can allow user programs to install a per-process x86
            Local Descriptor Table (LDT) using the modify_ldt(2) system
            call.  This is required to run 16-bit or segmented code such as
            DOSEMU or some Wine programs.  It is also used by some very old
            threading libraries.

            Enabling this feature adds a small amount of overhead to
            context switches and increases the low-level kernel attack
            surface.  Disabling it removes the modify_ldt(2) system call.

            Saying 'N' here may make sense for embedded or server kernels.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option if you're a basic WINE user,
            and if most of your apps work without the need to modify anything
            kernel wise.

            Include this option only if you stumbled upon a WINE program that
            requires it.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/linux%E5%86%85%E6%A0%B8%E9%85%8D%E7%BD%AE%E6%8C%87%E5%8D%97-processor-type-and-features/" target="_blank">click here</a>.
