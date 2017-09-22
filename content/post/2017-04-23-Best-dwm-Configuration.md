+++
title = "Best dwm Configuration"
slug = "best dwm configuration"
nick = "dwm"
date = "2017-04-23"
author = "Firas Khalil Khana"
imgsrc = "/img/dwm.png"
imgalt = "dwm"
+++
In this article I'll show you how to setup dwm and equip it with a nice basic configuration file.
<br/>
<hr/>
<h3>1- Installation</h3>
<br/>
Gentoo Linux:
```none
emerge --sync && emerge -av x11-wm/dwm
```
<br/>
Void Linux:
```none
xbps-install -Su && xbps-install -S dwm
```
<br/>
Arch Linux:
```none
pacman -Syu dwm
```
<hr/>
<h3>2- Accessing Configuration Files</h3>
<br/>
Since dwm's configuration file is written in C, chances are you're pretty much losing all customization options by downloading a binary based version of dwm. This is the case in Arch Linux and in Void Linux. To configure dwm, you need to compile it from source with the configuration you want. This is easily done in gentoo since you're pretty much building everything from source.
<br/>
<br/>
However, if you're using Arch Linux or Void Linux then you'll want to check <a href="https://wiki.archlinux.org/index.php/dwm#Configuration">Configuring dwm on Arch Linux</a>.The same applies to Void Linux, but you need to use xbps-src to install from source. Since no wiki article is written on dwm configuration on Void Linux at the moment, check this out <a href="https://wiki.voidlinux.eu/Xbps-src">Xbps-src Void Linux</a>. Don't worry I'll be waiting for you! Once you have access to the configuration file, you can tag along with us.
<br/>
<br/>
On gentoo, it's highly recommended to enable the <mark>savedconfig</mark> USE flag (After all who wouldn't want to save their configuration file once they're done lol). You can do that easily by:
```bash
echo "x11-wm/dwm savedconfig" >> /etc/portage/package.use
```
<br/>
Before accessing the configuration file, and in order to enable syntax highlighting for the C language in your favourite editor, you need to create a symlink using a header filename:
```bash
ln -s /etc/portage/savedconfig/x11-wm/dwm-6.1-r1 /etc/portage/savedconfig/x11-wm/dwm-6.1-r1.h
```
<br/>
Now, you can easily edit the configuration file (or the header file for syntax highlighting support) and start editing it with your favorite editor (for me that's vim and I respect your editor!):
```bash
vim /etc/portage/savedconfig/x11-wm/dwm-6.1-r1.h
```
<br/>
At the time of writing this article, dwm's version is 6.1-r1. Your version is probably the same, even if it's different just change the version number and you'll be good to go.
<br/>
<br/>
For those using nano as well, I recommend enabling syntax highlighting since it makes your life much easier, especially when editing text files in the terminal.
<hr/>
<h3>3- Configuration</h3>
<br/>
Once you've opened the configuration file, start editing it and tuning it to your liking. It's pretty straightforward as everything is explained. However, I'm here to provide you with a nice configuration file and save you some time. Here's my configuration file tuned to be used with gentoo:
```c,line-numbers
/* appearance */
static const char *fonts[] = {
	"xos4 Terminus:size=10"
};
static const char dmenufont[]       = "xos4 Terminus:size=10";
static const char normbordercolor[] = "#33393b";
static const char normbgcolor[]     = "#33393b";
static const char normfgcolor[]     = "#ffffff";
static const char selbordercolor[]  = "#54487a";
static const char selbgcolor[]      = "#54487a";
static const char selfgcolor[]      = "#ffffff";
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 0;       /* snap pixel, I've disabled pixel snapping by setting the value to 0, the default was 32 and it's only applicable in floating mode */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */

/* tagging */
/* I'm using a single tag as I don't require more. If you want more tags use this instead and as many tags as you want: */
/* static const char *tags[] = {"1", "2", "3", "4", "5"}; */
static const char *tags[] = {"DOTSLASHLINUX"};

/* rules */
static Rule rules[] = {
    /* class                instance        title       tags mask     isfloating */
    { "Gimp",                 NULL,       NULL,       NULL,            True },
};

/* layout(s) */
static const float mfact     = 0.70; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[T]",      tile },    /* first entry is default */
	{ "[F]",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle }
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
/* I'm using the dash shell here, if you're using any other shell just chande dash to sh */
/* #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } } */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/dash", "-c", cmd, NULL } }

/* commands */
/* I've made several commands for my different applications. You can create your own simply by
taking the command, splitting every word between whitespaces with quotation marks and terminating
the array with a NULL terminator (command eg. "wpa_supplicant -B -i wlp3s0 -c wpa.conf -D") */
/* static const char *commandname[] = {"wpa_supplicant", "-B", "-i", "wlp3s0", "-c", "wpa.conf", "-D", NULL} */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *termcmd[]  = { "urxvtc", NULL};
static const char *webcmd[]  = { "firefox", NULL};
static const char *filecmd[]  = { "pcmanfm", "/home/firas", NULL};
static const char *voldwcmd[]  = { "amixer", "-c", "PCH", "set", "Master", "1%-", NULL};
static const char *volupcmd[]  = { "amixer", "-c", "PCH", "set", "Master", "1%+", NULL};
static const char *volmcmd[]  = { "amixer", "-c", "PCH", "set", "Master", "toggle", NULL};
static const char *brtdwncmd[]  = { "xbacklight","-10", NULL};
static const char *brtupcmd[]  = { "xbacklight","+10", NULL};

/* shortcut keys */
static Key keys[] = {
	/* modifier                     key             function        argument */
	{ MODKEY,                       XK_d,           spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_x, 	        spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_w,           spawn,          {.v = webcmd } },
    { MODKEY,                       XK_e,	        spawn,          {.v = filecmd } },
    { 0,                            0x1008ff03,     spawn,          {.v = brtdwncmd } },
    { 0,                            0x1008ff02,     spawn,          {.v = brtupcmd } },
    { 0,                            0x1008ff11,	    spawn,          {.v = voldwcmd } },
    { 0,             	        	0x1008ff13,	   	spawn,          {.v = volupcmd } },
    { 0,                            0x1008ff12,	    spawn,          {.v = volmcmd } },
	{ MODKEY,                       XK_b,           togglebar,      {0} },
	{ MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,           incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_p,           incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Return,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,         view,           {0} },
	/* Since I use Shift+Alt to switch keyboard layouts I've changed ShiftMask to ControlMask */
	/* If you wanted to revert to the default configuration use this instead: */
	/* { MODKEY|ShiftMask,          XK_c,           killclient,     {0} }, */
	{ MODKEY,           			XK_c,           killclient,     {0} },
	{ MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,           setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,       setlayout,      {0} },
	{ MODKEY|ControlMask,           XK_space,       togglefloating, {0} },
	{ MODKEY,                       XK_0,           view,           {.ui = ~0 } },
	{ MODKEY|ControlMask,           XK_0,           tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,       focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period,      focusmon,       {.i = +1 } },
	{ MODKEY|ControlMask,           XK_comma,       tagmon,         {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period,      tagmon,         {.i = +1 } },
	/* Since I use Shift+Alt to switch keyboard layouts I've changed ShiftMask to ControlMask */
	/* If you wanted to revert to the default configuration use this instead: */
	/* { MODKEY|ShiftMask,          XK_q,           quit,           {0} } */
	{ MODKEY|ControlMask,           XK_q,           quit,           {0} }
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
```
<br/>
I've explained the basic stuff using comments in the configuration file for those who want further optimization. For those who love to copy-paste configuration files and use them directly, I've changed the main shortcuts for killing clients and quiting dwm since I use <mark>Shift+Alt</mark> for changing keyboard layouts. Here are the changes I made:
<br/>
<br/>
<mark>Shift+Alt+c</mark> to <mark>Alt+c</mark> to kill clients
<br/>
<mark>Shift+Alt+q</mark> to <mark>Ctrl+Alt+q</mark> to quit dwm
<br/>
<br/>
I've included these default shortcuts in the configuration file as well, just comment out my shortcuts and uncomment the defaults.
<br/>
<hr/>
<h3>4- Starting dwm</h3>
After we've done configuring dwm, it's time to fire it up. To start dwm, simply add the following to your .xinitrc:
```bash
exec dwm
```
<br/>
<hr/>
<h3>Conclusion</h3>
Hope you enjoyed this article and managed to get a successfuly working dwm tuned to your liking!
