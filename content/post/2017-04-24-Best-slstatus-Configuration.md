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
```none
xbps-install -Su && xbps-install -S slstatus
```
<br/>
What I recommend is doing this instead. Navigate to your home directory (any directory is fine but keep track of the directory you're using), and clone slstatus's github repo:
```bash
cd ~ && git clone https://github.com/drkhsh/slstatus
```
<hr/>
<h3 id="Configuration">2- Configuration</h3>
<br/>
Navigate to your freshly cloned directory:
```bash
cd ~/slstatus
```
<br/>
Now we'll create a symlink just like we did with the dwm configuration file:
```bash
ln -s ~/slstatus/config.def.h ~/slstatus/config.h
```
<br/>
Now edit the file config.h with your beloved editor:
```none
vim ~/slstatus/config.h
```
<br/>
Due to lack of documentation available, you may find it hard to get everything working the way you like it, but I've been lucky enough to get mine working after the 20th try or so (not kidding :P). Here's my configuration file:
```c,line-numbers
/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
/* default is 1000 */
static const int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
/* default is 2048 */
#define MAXLEN 256

/*
 * function             description                     argument
 *
 * battery_perc         battery percentage              battery name
 * battery_power        battery power usage             battery name
 * battery_state        battery charging state          battery name
 * cpu_perc             cpu usage in percent            NULL
 * cpu_freq             cpu frequency in MHz            NULL
 * datetime             date and time                   format string
 * disk_free            free disk space in GB           mountpoint path
 * disk_perc            disk usage in percent           mountpoint path
 * disk_total           total disk space in GB          mountpoint path
 * disk_used            used disk space in GB           mountpoint path
 * entropy              available entropy               NULL
 * gid                  GID of current user             NULL
 * hostname             hostname                        NULL
 * ipv4                 IPv4 address                    interface name
 * ipv6                 IPv6 address                    interface name
 * kernel_release       `uname -r`                      NULL
 * keyboard_indicators  caps/num lock indicators        NULL
 * load_avg             load average                    NULL
 * num_files            number of files in a directory  path
 * ram_free             free memory in GB               NULL
 * ram_perc             memory usage in percent         NULL
 * ram_total            total memory size in GB         NULL
 * ram_used             used memory in GB               NULL
 * run_command          custom shell command            command
 * swap_free            free swap in GB                 NULL
 * swap_perc            swap usage in percent           NULL
 * swap_total           total swap size in GB           NULL
 * swap_used            used swap in GB                 NULL
 * temp                 temperature in degree celsius   sensor file
 * uid                  UID of current user             NULL
 * uptime               system uptime                   NULL
 * username             username of current user        NULL
 * vol_perc             OSS/ALSA volume in percent      "/dev/mixer"
 * wifi_perc            WiFi signal in percent          interface name
 * wifi_essid           WiFi ESSID                      interface name
 */
static const struct arg args[] = {
  /* Displays the temperature read from the file /sys/class/thermal/thermal_zone0/temp , you can change that file
     to any other file that displays the temperature of certain components, you can even list multiple
     temperatures by duplicating it */ 
    { temp, "[TEMP %sC] ", "/sys/class/thermal/thermal_zone0/temp" },
	{ cpu_perc, "[CPU %s%] ", NULL },
	{ ram_perc, "[RAM %s%] ", NULL },
  /* If you have two sound cards (like me PCH/HDMI) then you may need to use /dev/mixer1 instead of /dev/mixer to get vol_perc working*/
	{ vol_perc, "[VOL %s%] ", "/dev/mixer1" },
  /* Displays battery's capacity, you need to specify the battery folder's name listed in /sys/class/power_supply,
     for me it's BAT0 and it'll automatically read the capacity file */
	{ battery_perc, "[BAT %s%] ", "BAT0" },
  /* Displays IPv4 address for the given network interface (which in my case is wlp3s0) in your local network */
	{ ipv4, "[IP %s] ", "wlp3s0" },
	{ datetime, "[%s]", "%F %r" },
}
```
<br/>
If you were facing problems getting <mark>vol_perc</mark> working, then you may be specifying the wrong mixer as an argument. You see on laptops or any other setup that uses 2 sound cards (PCH,HDMI), you'll get 2 mixers in <mark>/dev</mark> the first being <mark>mixer</mark> and the second being <mark>mixer1</mark>.
<br/>
If so, simply use this instead:
```c
{ vol_perc, "[VOL %s] ", "/dev/mixer1"},
```
<hr/>
<h3 id="Starting_slstatus">3- Starting slstatus</h3>
After configuring slstatus, we now have to start it. To do that add the following to your .xinitrc:
```none
slstatus &
```
