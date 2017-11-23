+++
title = "The Linux Kernel Configuration Guide Part 14"
slug = "the linux kernel configuration guide part 14"
nick = "kernel14"
date = "2017-09-14"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel14.png"
imgalt = "kernel14"
categories = [ "kernel" ]
+++
<h3>Kernel hacking  ---></h3>
<h3>printk and dmesg options  ---></h3>
<h3>[&ast;] Show timing information on printks</h3>
```properties
Symbol:     CONFIG_PRINTK_TIME

Help:       Selecting this option causes time stamps of the printk()
            messages to be added to the output of the syslog() system
            call and at the console.

            The timestamp is always recorded internally, and exported
            to /dev/kmsg. This flag just specifies if the timestamp should
            be included, not that the timestamp is recorded.

            The behavior is also controlled by the kernel command line
            parameter printk.time=1. See Documentation/admin-guide/kernel-parameters.rst

Type:       boolean

Choice:     built-in [*]

Reason:     It's highly recommended that you include this option in your kernel
            as timestamps add another level of precision to your system logs.
```
<h3>(15) Default console loglevel (1-15)</h3>
```properties
Symbol:     CONFIG_CONSOLE_LOGLEVEL_DEFAULT

Help:       Default loglevel to determine what will be printed on the console.

            Setting a default here is equivalent to passing in loglevel=<x> in
            the kernel bootargs. loglevel=<x> continues to override whatever
            value is specified here as well.

            Note: This does not affect the log level of un-prefixed printk()
            usage in the kernel. That is controlled by the MESSAGE_LOGLEVEL_DEFAULT
            option.

Type:       integer

Choice:     (15) custom

Reason:     It's recommended that you set the value of this option to a value
            that ensures enough verbosity is being used.

            If you've already excluded a bunch of debugging options to minimize
            system overhead, then you'd likely want to set the value of this
            option and CONFIG_MESSAGE_LOGLEVEL_DEFAULT to a high enough value
            to get enough information.
```
<h3>(7) Default message log level (1-7)</h3>
```properties
Symbol:     CONFIG_MESSAGE_LOGLEVEL_DEFAULT

Help:       Default log level for printk statements with no specified priority.

            This was hard-coded to KERN_WARNING since at least 2.6.10 but folks
            that are auditing their logs closely may want to set it to a lower
            priority.

            Note: This does not affect what message level gets printed on the console
            by default. To change that, use loglevel=<x> in the kernel bootargs,
            or pick a different CONSOLE_LOGLEVEL_DEFAULT configuration value.

Type:       integer

Choice:     (7) custom

Reason:     It's recommended that you set the value of this option to a value
            that ensures enough verbosity is being used.

            If you've already excluded a bunch of debugging options to minimize
            system overhead, then you'd likely want to set the value of this
            option and CONFIG_CONSOLE_LOGLEVEL_DEFAULT to a high enough value
            to get enough information.
```
<h3>Compile-time checks and compiler options  ---></h3>
<h3>(0) Warn for stack frames larger than (needs gcc 4.4)</h3>
```properties
Symbol:     CONFIG_FRAME_WARN

Help:       Tell gcc to warn at build time for stack frames larger than this.
            Setting this too low will cause a lot of warnings.
            Setting it to 0 disables the warning.
            Requires gcc 4.4 

Type:       integer

Choice:     (0) custom

Reason:     If you can live with the warnings then don't disable this option.
```
<h3>-&ast;- Kernel debugging</h3>
```properties
Symbol:     CONFIG_DEBUG_KERNEL

Help:       Say Y here if you are developing drivers or trying to debug and
            identify kernel problems.

Type:       boolean

Choice:     built-in -*-

Reason:     Forcibly included by CONFIG_EXPERT.
```
<h3>(0) panic timeout</h3>
```properties
Symbol:     CONFIG_PANIC_TIMEOUT

Help:       Set the timeout value (in seconds) until a reboot occurs when the
            the kernel panics. If n = 0, then we wait forever. A timeout
            value n > 0 will wait n seconds before rebooting, while a timeout
            value n < 0 will reboot immediately.

Type:       integer

Choice:     (0) custom

Reason:     Setting the value of this option to (0) will give you all the time
            you want to carefully examine the cause of the kernel panic.
```
<h3>RCU Debugging  ---></h3>
<h3>(3) RCU CPU stall timeout in seconds</h3>
```properties
Symbol:     CONFIG_RCU_CPU_STALL_TIMEOUT

Help:       If a given RCU grace period extends more than the specified
            number of seconds, a CPU stall warning is printed.  If the
            RCU grace period persists, additional CPU stall warnings are
            printed at more widely spaced intervals.

Type:       integer

Choice:     (3) custom
```
<h3>    IO delay type (no port-IO delay)  ---></h3>
<h3>(X) no port-IO delay</h3>
```properties
Symbol:     CONFIG_IO_DELAY_NONE

Help:       No port-IO delay. Will break on old boxes that require port-IO
            delay for certain operations. Should work on most new machines.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            if you're on a modern system.
```
<h3>    Choose kernel unwinder (ORC unwinder)  ---></h3>
<h3>(X) ORC unwinder</h3>
```properties
Symbol:     CONFIG_ORC_UNWINDER

Help:       This option enables the ORC (Oops Rewind Capability) unwinder for
            unwinding kernel stack traces.  It uses a custom data format which is
            a simplified version of the DWARF Call Frame Information standard.
            
            This unwinder is more accurate across interrupt entry frames than the
            frame pointer unwinder.  It also enables a 5-10% performance
            improvement across the entire kernel compared to frame pointers.

            Enabling this option will increase the kernel's runtime memory usage
            by roughly 2-4MB, depending on your kernel config.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            as it provides better performance over other unwinders as it disables
            frame pointers.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/linux%E5%86%85%E6%A0%B8%E9%85%8D%E7%BD%AE%E6%8C%87%E5%8D%97-kernel-hackinglibrary-routines-the-end/" target="_blank">click here</a>.
