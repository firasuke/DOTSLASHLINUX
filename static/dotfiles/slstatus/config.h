/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
static const int interval = 100;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
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
  /* function format          argument */
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
};
