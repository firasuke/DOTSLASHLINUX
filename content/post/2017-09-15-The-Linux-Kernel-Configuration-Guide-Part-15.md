+++
title = "The Linux Kernel Configuration Guide Part 15"
slug = "the linux kernel configuration guide part 15"
nick = "kernel15"
date = "2017-09-15"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel15.png"
imgalt = "kernel15"
categories = [ "kernel" ]
+++
While security is important, it isn't a high priority in this series (although we've gone through some options related to security).
<br/>
<br/>
You know what they say "There isn't a 100% secure system". You have to find the right balance between conveniency, usability and security otherwise you can easily render a system unusable if you beefed security up to an insane level.
<br/>
<br/>
I'd recommend (at least as a starting point) that you leave all options in this section excluded (or only include those required by other options).
<hr/>
<h3>Default security module (Unix Discretionary Access Controls)  ---></h3>
```properties
Help:       Select the security module that will be used by default if the
            kernel parameter security= is not specified.
```
<h3>(X) Unix Discretionary Access Controls</h3>
```properties
Symbol:     CONFIG_DEFAULT_SECURITY_DAC

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this option in your kernel
            (that is if it isn't already forcibly included as it's the only
            option available on many systems).
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX followers 杨鑫 (Yang Mame) from China, decided to follow up with the series and provide Chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in Chinese <a href="https://blog.yangmame.top/Linux内核配置指南-Kernel-hacking-Library-routines-The-End.html" target="_blank">click here</a>.
