+++
title = "Best slstatus Configuration"
slug = "best slstatus configuration"
nick = "slstatus"
date = "2017-04-24"
author = "Firas Khalil Khana"
imgsrc = "/img/slstatus.png"
imgalt = "slstatus"
+++
In this article I'll show you how to setup and configure slstatus the lightest status bar to use with dwm.
<br/>
<hr/>
<h3 id="Installation">1- Installation</h3>
<br/>
I highly recommend installing the source files for slstatus from github and compiling it from source. The official repos for Gentoo Linux and Arch Linux don't have slstatus (as far as I know); however, Void Linux seems to have it, but I don't recommend installing from the repos since it'll only worsen matters when trying to configure it. If you still want to download it from Void Linux's repos and managed to get to the configuration file, then execute the following:
<br/>
<br/>
Void Linux:
```bash
xbps-install -S slstatus
```
<br/>
What I recommend is doing this instead. Navigate to your home directory (any directory is fine but keep track of the directory you're using), and clone slstatus's github repo:
```bash
cd ~
git clone https://github.com/drkhsh/slstatus
```
<hr/>
<h3 id="Configuration">2- Configuration</h3>
<br/>
Navigate to your freshly cloned directory:
```bash
cd ~/slstatus
```
<br/>
Now edit the file config.h with your beloved editor:
```bash
nano ~/slstatus/config.h
```
<br/>
Due to lack of documentation available, you may find it hard to get everything working the way you like it, but I've been lucky enough to get mine working after the 20th try or so (not kidding :P). Here's my configuration file:
```c,line-numbers
/* See LICENSE file for copyright and license details. */

/* how often to update the statusbar (min value == 1) */
#define UPDATE_INTERVAL 1

/* text to show if no value can be retrieved */
#define UNKNOWN_STR     "n/a"

/* statusbar
- battery_perc (battery percentage) [argument: battery name]
- battery_state (battery charging state) [argument: battery name]
- cpu_perc (cpu usage in percent) [argument: NULL]
- datetime (date and time) [argument: format]
- disk_free (free disk space in GB) [argument: mountpoint]
- disk_perc (disk usage in percent) [argument: mountpoint]
- disk_total (total disk space in GB) [argument: mountpoint]
- disk_used (used disk space in GB) [argument: mountpoint]
- entropy (available entropy) [argument: NULL]
- gid (gid of current user) [argument: NULL]
- hostname [argument: NULL]
- ip (ip address) [argument: interface]
- kernel_release (uname -r) [argument: NULL]
- keyboard_indicators (caps/num lock indicators) [agrument: NULL]
- load_avg (load average) [argument: NULL]
- ram_free (free ram in GB) [argument: NULL]
- ram_perc (ram usage in percent) [argument: NULL]
- ram_total (total ram in GB) [argument: NULL]
- ram_used (used ram in GB) [argument: NULL]
- run_command (run custom shell command) [argument: command]
- swap_free (free swap in GB) [argument: NULL]
- swap_perc (swap usage in percent) [argument: NULL]
- swap_total (total swap in GB) [argument: NULL]
- swap_used (used swap in GB) [argument: NULL]
- temp (temperature in celsius) [argument: temperature file]
- uid (uid of current user) [argument: NULL]
- uptime (uptime) [argument: NULL]
- username (username of current user) [argument: NULL]
- vol_perc (oss/alsa volume status (see README)) [argument: /dev/mixer]
- wifi_perc (wifi signal in percent) [argument: wifi card interface name]
- wifi_essid (wifi essid) [argument: wifi card interface name] */
static const struct arg args[] = {
	/* function	format        argument */
        /* Displays the temperature read from the file /sys/class/thermal/thermal_zone0/temp , you can change that file
        to any other file that displays the temperature of certain components, you can even list multiple
        temperatures by duplicating it */
        { temp,         "[TEMP %s] ",     "/sys/class/thermal/thermal_zone0/temp"},
        { cpu_perc,     "[CPU %s] ",      NULL },
        { ram_perc,     "[RAM %s] ",      NULL },
        /* If you have two sound cards (like me PCH/HDMI) then you may need to use /dev/mixer1 instead of /dev/mixer to get vol_perc working*/
        { vol_perc,     "[VOL %s] ",      "/dev/mixer1"},
        /* Displays battery's capacity, you need to specify the battery folder's name listed in /sys/class/power_supply,
        for me it's BAT0 and it'll automatically read the capacity file */
        { battery_perc, "[BAT %s] ",      "BAT0"},
        /* Displays IPv4 address for the given network interface (which in my case is wlp3s0) in your local network */
        { ip,           "[IP %s] ",       "wlp3s0"},
        { datetime,     "[%s]",           "%F %r" }
};
```
<br/>
If you were facing problems getting <mark>vol_perc</mark> working, then you may be specifying the wrong mixer as an argument. You see on laptops or any other 
setup that uses 2 sound cards (PCH,HDMI), you'll get 2 mixers in <mark>/dev</mark> the first being <mark>mixer</mark> and the second being <mark>mixer1</mark>.
<br/>
If so, simply use this instead:
```c
{ vol_perc, "[VOL %s] ", "/dev/mixer1"},
```
<hr/>
<br/>
<h3 id="Starting_slstatus">3- Starting slstatus</h3>
After configuring slstatus, we now have to start it. To do that add the following to your .xinitrc:
```bash
slstatus -d
```
