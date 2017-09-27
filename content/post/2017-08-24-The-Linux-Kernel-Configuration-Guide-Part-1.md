+++
title = "The Linux Kernel Configuration Guide Part 1"
slug = "the linux kernel configuration guide part 1"
nick = "kernel1"
date = "2017-08-24"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel1.png"
imgalt = "kernel1"
categories = [ "kernel" ]
+++
<h3>Intro</h3>
Finally, it's here... The series you've all been waiting for. I want to apologize for making you wait a lot before starting this series. The truth is that I've redesigned the website from scratch which took some time. It's much lighter now and fully supports SSL (https and it works well in a terminal web browser! I've also added an <a href="/index.xml" target="_blank">RSS</a> feed so don't forgot to subscribe.
<br/>
<br/>
I've also updated several articles, and have migrated to the unstable branch of Gentoo (aka ~arch) based on the request of several DOTSLASHLINUX followers, and hopefully will update all sections where configuring something using the unstable branch is a tiny bit different than in the stable one. And after the release of 4.12, and the introduction of several new schedulers and the turbo boost 3.0 feature, and having moved to 4.12.8 using ck patchset, I knew I had to do a lot of testing before starting this series.
<br/>
<br/>
Enough talking, let's begin with the real thing. Configuring the linux kernel is regarded as one of the most tedious tasks a gnu/linux enthusiast might ever do. It's not that hard but it sure is time consuming. The amount of options that's available is nerve-racking. For enthusiasts who like to customize everything in their distro, it's like going to the heaven of customization.
<br/>
<br/>
But hang on, that wasn't the tough part. You have to compile your kernel after the slightest change... And if by any chance you forgot to tell your bootloader about your new kernel (appended a string to your kernel perhaps), or forgot to include your filesystem/block device support in your kernel, then you're pretty much going to get grey hair sooner than ever.
<br/>
<br/>
<em>"Were the new options that I've changed related to this kernel panic? Ok let me remove them. Recompile... Not Working... Dang I forgot to include support for my xfs filesystem. Reimplement changes. Recompile... Ok now working."</em>
<br/>
<br/>
This is a simple example of what you might face when configuring your kernel. I once had to recompile my whole gentoo system, because I thought that the kernel can't boot without an initrd on a xfs filesystem until I remembered that I'd forgotten to include support for xfs in my kernel (that caused this article to get delayed for 3 days so yeah... a real life example of what you might experience).
<hr/>
<h3>Expectations</h3>
I'm no expert and I don't claim to be one. I'm a mere enthusiast that happens to have a proper time schedule and thus more time for testing and experimenting with what I love.
<br/>
<br/>
I've spent around 2 months experimenting with my kernel configuration, until I got mine fully working the way I wanted it to. Therefore all the results and speculations that I have come to know may differ or not even be applicable on your end.
<br/>
<br/>
I'm not responsible for you breaking your system or losing important data because I've already experienced a lot (one of my suicidal builds was a ext4 with no journal -aka ext2 by some fellow gnu/linux users- and when using MuQSS from the ck-patchset along with BFQ I/O scheduler and setting my timer frequency to 1000hz, my laptop froze when emerging chromium -it was 80% done though- and boom my filesystem got corrupted and I had to reinstall gentoo).
<br/>
<br/>
But don't worry, looking back at my previous articles I've noticed that a lot of you found them helpful, so I have high hopes for this series.
<hr/>
<h3>Target Audience</h3>
Every single son of a tux out there who's interested in messing with the internals of his/her system. Anyone who wants to customize their kernel for maximum throughput, performance, (minimum)latency, gaming, streaming, music production, video editing, embedded systems etc...
<br/>
<br/>
Basically, we'll keep it as minimal and as simple as possible, choosing options that provide the highest performance possible alongside a proper latency level that won't lag your system when emerging or compiling or whatever task that makes use of cpu resources.
<br/>
<br/>
Some of you may wonder, how on earth will I be able to provide proper configuration to all those audiences. Well I won't... I'll be posting results achieved on my end (my <a href="/about/" target="_blank">Toshiba L50-A664</a>) and I have a ton, and if any of you wanted to contribute or improve on something I said or even correct a misconception I had regarding anything then feel free to drop a comment below or email me with what you have in mind.
<br/>
<br/>
With my findings and your help, let's try to make this series a well established starting point (or even a reference) for all those who want to configure their kernels.
<hr/>
<h3>Description</h3>
I'll go through every kernel configuration option out there, and include the help summary provided with it, its type and the choice I went with and the reason why (unless it was obvious).
<br/>
<br/>
For those who want my kernel .config (and I don't recommend that since I extremely configured it to work on my end and it probably will result in several kernel panics before you get your kernel booting on your end) you can download it from <a href="/dotfiles/" target="_blank">DOTSLASHLINUX DOTFILES</a> (The file is named DOTSLASHLINUX.config, just be sure to change it to .config and run these commands beforehand:
```bash
make oldconfig && make prepare
```
<br/>
As for those who're willing to go through this with me, to make things less confusing, I'll be using a template like this:
```properties
Symbol:

Help: 

Type:

Choice:

Reason:
```
In order not to create a state of confusion, I'll be using the word symbol for the capitalized underscore-separated version of the name. For example:
```properties
Symbol: CONFIG_MODULES
Name: Enable loadable modules support
```
Not only that will make it easier for you(and me as well), it'll make it much easier for those who want to contribute to this series as well. Say you have an option from a different patchset and wanted to include it in the series, just send me the option using the template above, and the name of the patchset if any and I'll attribute everyone who contributes and list their names/blogs upon request.
<hr/>
<h3>Time</h3>
This series will be as long as it needs to be, and that actually depends on how many configuration options there are.
<hr/>
<h3>Conclusion</h3>
This article is only an intro to the series. And no that doesn't mean that you have to wait a couple of months before reading part 2. You can trust me on this as I'm determined to finish this series as fast and as precise as a human being possibly could, so stay tuned (for those who want to support me kindly click here <a href="https://www.paypal.me/DOTSLASHLINUX/5" target="_blank">Support DOTSLASHLINUX on PayPal</a>.
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX's followers from china 杨鑫 (Yang Mame), decided to follow up with the series and provide chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in chinese <a href="https://blog.yangmame.top/linux%E5%86%85%E6%A0%B8%E9%85%8D%E7%BD%AE%E6%8C%87%E5%8D%97-%E8%AF%B4%E6%98%8E/" target="_blank">click here</a>.
