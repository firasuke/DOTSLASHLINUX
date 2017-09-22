+++
title = "Best Vim Configuration and Plug-ins for Web Development"
slug = "best vim configuration and plugins for web development"
nick = "vim"
date = "2017-09-23"
author = "Firas Khalil Khana"
imgsrc = "/img/vim.png"
imgalt = "vim"
+++
I've been constantly switching between text editors. At first I started using nano for terminal/tty purposes and Leafpad for a GUI editor. They were pretty neat for quick basic editing (especially nano), but they were never suitable for programming and writing articles.
<br/>
<br/>
I then moved to Geany, which was wonderful. It had everything I needed, a nice color scheme (monokai from geany-themes on github), and was super fast, but it was only suitable for C/C++ programming and it wasn't meant to be used for web development.
<br/>
<br/>
Throughout the way I've gave Vim like 50 chances to prove it was worth it, but it failed me every time. I then found out about Bluefish Editor, and I hated it the moment I started using it. It was fast, and had a lot of features, but its editor lacked a lot of stuff I thought were important, plus using it just felt weird (with all do respect to all Bluefish developers, you're doing a great job, it's just that it wasn't suited for a user like me).
<br/>
<br/>
A couple of months passed, and I was switching constantly between Geany, nano and Leafpad until I found out about Atom from Github and boy it was awesome! Fired up that terminal emulator and a whopping 600mb package was waiting to be built from source, now isn't that fantastic... Atom needed electron, the base Javascript framework that it was build on, and compiling a package this big from source isn't something easy (all the Gentoo boys and girls who tried to emerge chromium will be nodding their heads in approval... yes I can feel you...) as you never know if it'll work as expected or not, or if you've missed a feature or not but I did it, and couldn't be any happier.
<br/>
<br/>
I then wrote the first version of this website in Atom, things were really easy. Instant preview in an integrated web browser, auto completion, amazing color scheme, snippets for everything and a ton of features. But then as I added more and more plug-ins Atom was growing into a bloated mess of Javascript code that I couldn't withstand. I mean every time I started it, it took at least 10 seconds to get fully working and I hated that. It also (although rarely) crashed on me in several occasions which made me finally make the decision of switching to Vim.
<br/>
<br/>
I emerged Vim, and at first it was the worst thing I've tried on GNU/Linux so far... I said to myself "I wonder if I'm mistaken, I mean look at all those power Vim users out there and how quickly they finish tasks that take at least a couple of minutes on other editors in a second or two". I acknowledged that the problem was with me and not with Vim. And I forced myself into learning Vim and I'm glad I did that.
<br/>
<br/>
I coded the website from scratch this time using Vim. Day after day, I was getting better and faster. I stopped using nano and Leafpad. The Vim editor, that I thought was the worst thing to ever exist on a GNU/Linux operating system, was slowly turning into the best thing that I've ever used. It can be launched in any terminal emulator/tty. It starts in a mere second or two with all plug-ins fully loaded. It has a ton of plug-ins to choose from and a strong community behind it.
<br/>
<br/>
It took me 3 months to get used to Vim and its key bindings, and I now highly recommend it to anyone who wants a light productive text editor.
<br/>
<br/>
So yes the website you're viewing right now was proudly coded using Vim, and all of my articles were rewritten using Vim. It was until recently that a couple of DOTSLASHLINUX followers requested that I post a guide on how to configure Vim, and what plug-ins I use alongside it since they thought that the pictures that showcased Vim the most were the coolest ones, and here I'm writing an article for DOTSLASHLINUX's loyal viewers.
<br/>
<br/>
Enough talking, let's get this thing started!
<hr/>
<h3>1- Installation</h3>
<br/>
Gentoo Linux:
```none
emerge --sync && emerge -av app-editors/vim
```
<br/>
Void Linux:
```none
xbps-install -Su && xbps-install -S vim
```
<br/>
Arch Linux:
```none
pacman -Syu vim
```
