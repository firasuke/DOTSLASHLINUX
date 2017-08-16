+++
title = "Basic ALSA Configuration"
slug = "basic alsa configuration"
nick = "alsa"
date = "2017-03-30"
author = "Firas Khalil Khana"
imgsrc = "/img/alsa.png"
imgalt = "alsa"
+++
In this article I'll show you how to setup ALSA, with a working .asoundrc configuration file that supports multiple applications!
<br/>
<br/>
<hr/>
<h3 id="Installation">1- Installation</h3>
<br/>
Gentoo Linux:
```bash
emerge --ask --update --newuse media-sound/alsa-utils
```
<br/>
Void Linux:
```bash
xbps-install -S alsa-utils
```
<br/>
Arch Linux:
```bash
pacman -Syu alsa-utils
```
<br/>
<hr/>
<h3 id="Unmuting_Channels">2- Unmuting Channels</h3>
<br/>
Once ALSA is installed, we need to unmute the master channel for our sound card. We can do that using the ncurses interface of alsamixer (Use F6 to switch to your default soundcard):
```properties
┌────────────────────────────────────────────────────────────────────────── AlsaMixer v1.1.3 ───────────────────────────────────────────────────────────────────────────┐
│ Card: HDA Intel PCH                                                                                                                           F1:  Help               │
│ Chip: IDT 92HD99BXX                                                                                                                           F2:  System information │
│ View: F3:[Playback] F4: Capture  F5: All                                                                                                      F6:  Select sound card  │
│ Item: Master [dB gain: 0.00]                                                                                                                  Esc: Exit               │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│         ┌──┐            ┌──┐            ┌──┐            ┌──┐            ┌──┐            ┌──┐            ┌──┐                            ┌──┐                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │  │                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │  │                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         │▒▒│            │  │            │▒▒│            │▒▒│            │  │            │  │            │▒▒│                            │ ▒│                          │
│         ├──┤            ├──┤            ├──┤            └──┘            ├──┤            └──┘            ├──┤           Enabled          └──┘          Disabled        │
│         │OO│            │MM│            │OO│                            │MM│                            │MM│                                                          │
│         └──┘            └──┘            └──┘                            └──┘                            └──┘                                                          │
│         100             0<>0          100<>100        100<>100          0<>0            0<>0             33                             0<>53                         │
│   <    Master     >   Headphone        Speaker           PCM             Mic          Mic Boost         Beep       Auto-Mute Mode  Internal Mic Bo Loopback Mixing    │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
│                                                                                                                                                                       │
└───────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
```
<hr/>
<h3 id="ALSA_Services">3- ALSA Services</h3>
<br/>
These are (alsa-restore, alsa-state, alsasound... etc). In most distros, these services are automatically enabled, however just to be safe, let's see how we can enable and start them on:
<br/>
<br/>
Gentoo Linux (start and enable)
```bash
service alsasound start
rc-update add alsasound boot
```
<br/>
Void Linux (start and enable)
```bash
sv start alsa
ln -s /etc/sv/alsa /var/service/
```
<br/>
Arch Linux (start and enable)
```bash
systemctl start alsa-restore.service
systemctl start alsa-state.service
systemctl enable alsa-restore.service
systemctl enable alsa-state.service
```
<hr/>
<h3 id="Default_Sound_Card_and_Sound_from_Multiple_Applications">4- Default Sound Card & Sound from Multiple Applications</h3>
<br/>
After you've done all the previous steps, ALSA should be working perfectly. Sound from multiple applications which is supported by alsa's dmix plugin is enabled by default. However, on some setups (like mine), the default sound card may not be your main sound card (for example HDMI and Intel HD Audio PCH):
```bash
aplay -l
```
```bash
**** List of PLAYBACK Hardware Devices ****
card 0: HDMI [HDA Intel HDMI], device 3: HDMI 0 [HDMI 0]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 0: HDMI [HDA Intel HDMI], device 7: HDMI 1 [HDMI 1]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 0: HDMI [HDA Intel HDMI], device 8: HDMI 2 [HDMI 2]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 1: PCH [HDA Intel PCH], device 0: 92HD99BXX Analog [92HD99BXX Analog]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
```
<br/>
The HDMI soundcard is given an index of 0, and your main PCH soundcard is given an index of 1. Thus the default card chosen by ALSA is the HDMI card. Therefore, you'll hear nothing. To fix this, first we need to tell if the soundcard drivers and codecs are built into the kernel or left as modules.
<br/>
<br/>
In the latter, we can easily fix this problem by specifying our default sound card as a kernel parameter. Create a file in /etc/modprobe.d called alsa.conf or whatever_you_like.conf:
```bash
touch /etc/modprobe.d/alsa.conf
```
<br/>
And put the following in it:
```properties
options snd-hda-intel index=1,0
```
<br/>
This swaps the index numbers of both cards giving your main PCH sound card an index of 0, and your HDMI soundcard an index of 1.
<br/>
<br/>
However, if your soundcard drivers and codecs are built into the kernel. That previous line won't do a thing. You have to tell ALSA when you're starting an X session which card you want to use as your default soundcard. Therefore you need to create a file in your home directory called .asoundrc:
```bash
touch ~/.asoundrc
```
<br/>
Now here's a custom configuration that I use to swap both cards, and enable sound from multiple applications without sacrificing any sound quality whatsoever:
```properties,line-numbers
pcm.!default {
	type plug
	slave.pcm "dmixer"
}

pcm.dmixer  {
 	type dmix
 	ipc_key 1024
 	slave {
		pcm "hw:1,0"
		period_time 0
		period_size 1024
		buffer_size 4096
		rate 44100
	}
	bindings {
		0 0
		1 1
	}
}

ctl.dmixer {
	type hw
	card PCH
}
```
<hr/>
<h3 id="Controlling_Volume_using_shortcut_keys_on_dwm">(Optional) Controlling Volume using shortcut keys on dwm</h3>
Let's start by adding this to the commands section (Remeber we need to specify our default sound card in our previous case):
```bash,line-numbers
/* commands */
static const char *voldwcmd[]  = { "amixer", "-c", "PCH", "set", "Master", "1%-", NULL};
static const char *volupcmd[]  = { "amixer", "-c", "PCH", "set", "Master", "1%+", NULL};
static const char *volmcmd[]  = { "amixer", "-c", "PCH", "set", "Master", "toggle", NULL};
```
<br/>
This defines 3 character arrays that will hold our volume controlling commands respectively.
<br/>
<br/>
Now, let's map these commands to the hexadecimal code of your multimedia volume keys. To find out the hexadecimal code of your multimedia volume keys, fire up a terminal in a X session, focus on the shown window, press your shortcut keys and copy the codes. You should get something like this:
```bash
xev
```
```bash,line-numbers
KeyRelease event, serial 32, synthetic NO, window 0xe00001,
    root 0xd4, subw 0xe00002, time 4421968, (57,25), root:(1111,260),
    state 0x0, keycode 122 (keysym 0x1008ff11, XF86AudioLowerVolume), same_screen YES,
    XLookupString gives 0 bytes:
    XFilterEvent returns: False

KeyRelease event, serial 32, synthetic NO, window 0xe00001,
    root 0xd4, subw 0xe00002, time 4422488, (57,25), root:(1111,260),
    state 0x0, keycode 123 (keysym 0x1008ff13, XF86AudioRaiseVolume), same_screen YES,
    XLookupString gives 0 bytes:
    XFilterEvent returns: False

KeyPress event, serial 32, synthetic NO, window 0xe00001,
    root 0xd4, subw 0xe00002, time 4423054, (57,25), root:(1111,260),
    state 0x0, keycode 121 (keysym 0x1008ff12, XF86AudioMute), same_screen YES,
    XLookupString gives 0 bytes:
    XmbLookupString gives 0 bytes:
    XFilterEvent returns: False
```
<br/>
Then we'll add this entry to the modifiers section:
```c,line-numbers
/* modifier                     key        function        argument */
{ 0,                            0x1008ff11,	   spawn,          {.v = voldwcmd } },
{ 0,             	            0x1008ff13,	   spawn,          {.v = volupcmd } },
{ 0,                            0x1008ff12,	   spawn,          {.v = volmcmd } },
```
