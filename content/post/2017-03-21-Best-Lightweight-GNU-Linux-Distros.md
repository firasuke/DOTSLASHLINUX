+++
title = "Best Lightweight GNU/Linux Distros!"
slug = "best lightweight gnu linux distros"
nick = "ldistros"
date = "2017-03-21"
author = "Firas Khalil Khana"
imgsrc = "/img/lightweight.png"
imgalt = "lightweight"
+++
In this article I'll be talking about some lightweight GNU/Linux distro that don't sacrifice conveniency for being lightweight. (Yes I'm looking at you TinyCoreLinux)...
<br/>
<br/>

Let's define some rough outlines before venturing any further. The distros that I'll be mentioning won't be those super tiny ones that can be run on a toaster. They will be distros that can be run mainly on a x64/x32 machine and possibly on ARM hardware.
<br/>
<br/>


<h3><a href="https://gentoo.org/" target="_blank">Gentoo Linux</a></h3>
Who didn't see this coming... The truth is that gentoo is an awesome independent source-based rolling-release GNU/Linux Distro. What that means is that you download the source code of the packages you want and build them. The devs were kind enough to provide a precompiled version of the basic files used for the installation of gentoo known as stages.
<br/>
<br/>

<strong>"But wait aren't source files bigger than their compiled relatives?"</strong>, bigger yes as they take more space, but once you've compiled the package the result is almost always smaller (even if by 1%) that it's original relative. Not only that but you can choose what you want from a certain package and disable what you don't want (this feature is known as USE flags).
<br/>
<br/>

Why on earth would you want to download all the locales available in the world for every single package when you only speak one maybe two or three languages? Why would you need xorg server support and sound support when you're building a headless server (without a GUI)? Why would you need networking support in a package that you know most certainly isn't going to use it anyways? The list goes on and on...
<br/>
<br/>

The same thing that goes for the packages can be applied to the kernel as they highly recommend that you build your own kernel. For example, I was able to idle at 37mb RAM usage on a headless 64bit machine, and at 49mb RAM usage using DWM (a super lightweight dynamic wm that does its thing perfectly) and I had everything working from sound to microcode updates to compositing to everything just name it... (Don't you worry I'll be posting my results and my builds and what I did to achieve them later on).
The number of packages it provides by default is also quite notable. It can be extended further more using overlays (some are official and some are not).
<br/>
<br/>


<strong>"Alright I'll go download that gentoo and install it on my Pi!!"</strong>... woah woah woah hold on there... True gentoo has lots of pros, but let's look at the cons as well. First of all compiling everything from source is a time consuming, heat producing and age reducing process.. (your age as well as the hardware's age). I was running gentoo on my toshiba laptop and compiling everything meant that I had to leave the machine running at 80 to 90 degrees celsius and at 90-99% CPU usage for times variying from 1 minute to sometimes hours.
<br/>
<br/>

My laptop had a quad core intel cpu, now imagine doing that on a pi... I wonder if it's ever going to finish compiling... But you can as always cross-compile by forcing your stronger higher end hardware to build the packages with a configuration suitable for that pi or any other lower end hardware. <strong>"Ok I have a high-end PC should I download gentoo now?"</strong>... The truth is gentoo requires a lot and a lot of knowledge to work with it. But if you're interested I'll be more than pleased to help you on that (lemme know in the comments below).
<br/>
<br/>
<br/>

<h3><a href="https://www.voidlinux.eu/" target="_blank">Void Linux</a></h3>
<strong>"Wait what? I've never heard of this distro before? How did it make it here?"</strong>.. Simply said it EARNED it. Sorry for being too loud but that's the truth. Void Linux is an independent rolling-release GNU/Linux distro, developed entirely by volunteers and they nailed every aspect in it. Everything in it is lightweight and does what it needs to do perfectly. Their package manager xbps is awesome. Their service manager runit kicks systemd's and openrc's ass. It boots under 10 seconds on an old HDD and between 2-4 seconds on an SSD.
<br/>
<br/>

They even provide two flavors of void. The glibc based void with glibc packages and the musl based void with musl based packages. The different between the two is that musl is lighter and somewhat faster but has very little packages as many software in the GNU/Linux won't compile using musl. But if you're lucky and all the software you use is available in the musl repositories then go for the musl version.
<br/>
<br/>

That's not it they even provide a source based version of void using xbps-src, which I think is good for those who want to tinker with their packages. But seriously if you want to use a source based distro just choose gentoo...
<br/>
<br/>

I can't think of any cons for void as I didn't use it for a long period of time (it took me alot to configure bumblebee for my optimus laptop which I didn't like other than that it was great).
<br/>
<br/>
<br/>

<h3><a href="https://www.archlinux.org/" target="_blank">Arch Linux</a></h3>
Oh boy... You saw this coming from a mile didn't you... It's our all time star Arch Linux! The distro with the worst community ever. The distro where I tried to report several bugs in the irc and got roasted as either they were upstream or that I'm a retard for using the features that bugs made unavailable... Anyways...
<br/>
<br/>

Archlinux, is an independent rolling-release binary based GNU/Linux distro. And no it's not hard to install unlike gentoo... In fact the whole installation process can be automated using scripts so you don't have to manually reinstall it (if you ever needed to). In fact that's what some distros are doing. They're automating the installation process of archlinux and leave you with a basic archlinux install.
<br/>
<br/>

Archlinux uses systemd by default which will hopefully be a distro of itself if they keep doing what they're doing now. Thus it offers you a fast boot time (faster than OpenRC in gentoo and slightly slower than runit on void), and higher memory footprint for its journald service. The wiki is astonishing. It has everything you need to know to make arch whatever you want. But that doesn't mean that their community should badmouth everyone who asks for help. In fact the installation of archlinux is the easier among the distros mentioned on this list, so they get no right to brag...
<br/>
<br/>

The official repositories offer a fair amount of packages (more than voidlinux and less than gentoo). This can also be extended using the aur which is completely unofficial. Everything seems super smooth with arch as pacman does most of the work for you. Optimus laptops won't have any hard time using arch. In fact arch is the only distro that makes the <strong>"But I have 2 graphics card an iGPU and dGPU..."</strong> a problem of the past. The devs did a lot of configuration for the packages so you don't have to bother about missing libs or having to relink libs or stuff like that.
<br/>
<br/>

You don't need to know that much in GNU/Linux to install arch. The amount of knowledge needed to install arch is like a mere 5% to 20% (at max) compared to gentoo.
<br/>
<br/>

<h3><span class="line-center">Honorable Mentions</span></h3>
There are a couple of distros that would've made the list if they weren't too old or only available for a certain platform or had very little packages to work with or had so many problems and a small number of devs. These include:
<ol>
<li><a href="http://www.porteus.org/" target="_blank">Porteus Linux</a></li>
<li><a href="https://alpinelinux.org/" target="_blank">Alpine Linux</a></li>
<li><a href="http://puppylinux.org/main/Overview%20and%20Getting%20Started.htm" target="_blank">Puppy Linux</a></li>
<li><a href="http://www.slitaz.org/en/" target="_blank">SliTaz Linux</a></li>
<li><a href="http://tinycorelinux.net/" target="_blank">TinyCore Linux</a></li>
<li><a href="http://www.absolutelinux.org/" target="_blank">Absolute Linux</a></li>
<li><a href="https://www.bunsenlabs.org/" target="_blank">BunsenLabs Linux</a></li>
</ol>
<br/>

<h3><span class="line-center">TL;DR</span></h3>

<table style="width:100%">
  <tr>
    <th>Distro</th>
    <th>Package Manager</th>
    <th>Available Packages</th>
    <th>Service Manager</th>
    <th>Wiki</th>
    <th>Community</th>
    <th>Knowledge</th>
  </tr>
  <tr>
    <td>Gentoo Linux</td>
    <td>portage</td>
    <td>~20,000</td>
    <td>OpenRC/systemd</td>
    <td>great</td>
    <td>great</td>
    <td>a lot</td>
  </tr>
  <tr>
  <td>Void Linux</td>
  <td>xbps</td>
  <td>~7,000</td>
  <td>runit</td>
  <td>mediocre</td>
  <td>great</td>
  <td>medium</td>
  </tr>
  <tr>
  <td>Arch Linux</td>
  <td>pacman</td>
  <td>~15,000</td>
  <td>systemd</td>
  <td>great</td>
  <td>not so great</td>
  <td>medium</td>
  </tr>
</table>
<br/>

If you had time and wish to learn GNU/Linux go with gentoo. Otherwise go with archlinux or voidlinux. Remember never make an OS your end goal unless you're willing to become a sysadmin.
<br/>
<br/>

<h3><span class="line-center">Conclusion</span></h3>
In the end, every distro can be lightweight if it offered the means for users to customize it to their likings without breaking on every stupid thing. This is just the start, after you've installed a base system using one of these distros, be sure to follow other guides on our site to choose your set of lightweight apps suitable for your work.
<br/>
<br/>
