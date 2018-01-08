+++
title = "The Linux Kernel Configuration Guide Part 10 - [∗] Networking support  --->"
slug = "the linux kernel configuration guide part 10 networking support"
nick = "kernel10"
date = "2017-09-09"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel10.png"
imgalt = "kernel10"
categories = [ "kernel" ]
+++
<h3>[&lowast;] Networking support  ---></h3>
```properties
Symbol:     CONFIG_NET

Help:       Unless you really know what you are doing, you should say Y here.
            The reason is that some programs need kernel networking support even
            when running on a stand-alone machine that isn't connected to any
            other computer.

            If you are upgrading from an older kernel, you
            should consider updating your networking tools too because changes
            in the kernel and the tools often go hand in hand. The tools are
            contained in the package net-tools, the location and version number
            of which are given in <file:Documentation/Changes>.

            For a general introduction to Linux networking, it is highly
            recommended to read the NET-HOWTO, available from
            <http://www.tldp.org/docs.html#howto>.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel as
            many programs rely on it (many of Xorg server features depend on it).It's
            also required by CONFIG_GENTOO_LINUX, CONFIG_GENTOO_LINUX_UDEV and 
            CONFIG_GENTOO_LINUX_INIT_SYSTEMD.

            You should only exclude this option if you're a developer or for
            testing purposes.
```
<h3>Networking options  ---></h3>
<h3><&lowast;> Packet socket</h3>
```properties
Symbol:     CONFIG_PACKET

Help:       The Packet protocol is used by applications which communicate
            directly with network devices without an intermediate network
            protocol implemented in the kernel, e.g. tcpdump.  If you want them
            to work, choose Y.

            To compile this driver as a module, choose M here: the module will
            be called af_packet.

            If unsure, say Y.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as it's required by net-wireless/wpa_supplicant.

            These include Wireshark, Metasploit, nmap, tcpdump ...etc. Some even say
            that this option may boost performance by allowing applications to directly
            communicate with network services.

            This option was used as a way to exploit the linux kernel (fixed on Mar. 29, 2017),
            kindly check this link:
                
                https://googleprojectzero.blogspot.com/2017/05/exploiting-linux-kernel-via-packet.html
```
<h3>-&lowast;- Unix domain sockets</h3>
```properties
Symbol:     CONFIG_UNIX

Help:       If you say Y here, you will include support for Unix domain sockets;
            sockets are the standard Unix mechanism for establishing and
            accessing network connections.  Many commonly used programs such as
            the X Window system and syslog use these sockets even if your
            machine is not connected to any network.  Unless you are working on
            an embedded system or something similar, you therefore definitely
            want to say Y here.

            To compile this driver as a module, choose M here: the module will be
            called unix.  Note that several important services won't work
            correctly if you say M here and then neglect to load the module.

            Say Y unless you know what you are doing.

Type:       tristate

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel as
            it's required by many programs such as the Xorg server which is used
            in almost all user systems (that is if this option wasn't already
            forcibly included by CONFIG_GENTOO_LINUX and CONFIG_GENTOO_LINUX_UDEV).
```
<h3>[&lowast;] TCP/IP networking</h3>
```properties
Symbol:     CONFIG_INET

Help:       These are the protocols used on the Internet and on most local
            Ethernets. It is highly recommended to say Y here (this will enlarge
            your kernel by about 400 KB), since some programs (e.g. the X window
            system) use TCP/IP even if your machine is not connected to any
            other computer. You will get the so-called loopback device which
            allows you to ping yourself (great fun, that!).

            For an excellent introduction to Linux networking, please read the
            Linux Networking HOWTO, available from
            <http://www.tldp.org/docs.html#howto>.

            If you say Y here and also to "/proc file system support" and
            "Sysctl support" below, you can change various aspects of the
            behavior of the TCP/IP code by writing to the (virtual) files in
            /proc/sys/net/ipv4/∗; the options are explained in the file
            <file:Documentation/networking/ip-sysctl.txt>.

            Short answer: say Y.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            as some say it's required by the Xorg server (although I doubt
            that).

            Exclude every other option listed beneath this option as you won't need
            them for basic networking (only include the ones required by some
            applications to work for example CONFIG_BRIDGE which is a nice feature to
            have in virtual machines).
```
<h3>[ ]   Amateur Radio support  ----</h3>
```properties
Symbol:     CONFIG_HAMRADIO

Help:       If you want to connect your Linux box to an amateur radio, answer Y
            here. You want to read <http://www.tapr.org/>
            and more specifically about AX.25 on Linux
            <http://www.linux-ax25.org/>.

            Note that the answer to this question won't directly affect the
            kernel: saying N will just cause the configurator to skip all
            the questions about amateur radio.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's unlikely that you'll connect
            your linux system to a ham radio.
```
<h3>< >   CAN bus subsystem support  ----</h3>
```properties
Symbol:     CONFIG_CAN

Help:       Controller Area Network (CAN) is a slow (up to 1Mbit/s) serial
            communications protocol which was developed by Bosch in
            1991, mainly for automotive, but now widely used in marine
            (NMEA2000), industrial, and medical applications.
            More information on the CAN network protocol family PF_CAN
            is contained in <Documentation/networking/can.txt>.

            If you want CAN support you should say Y here and also to the
            specific driver for your controller(s) below.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>< >   IrDA (infrared) subsystem support  ----</h3>
```properties
Symbol:     CONFIG_IRDA

Help:       Say Y here if you want to build support for the IrDA (TM) protocols.
            The Infrared Data Associations (tm) specifies standards for wireless
            infrared communication and is supported by most laptops and PDA's.

            To use Linux support for the IrDA (tm) protocols, you will also need
            some user-space utilities like irattach.  For more information, see
            the file <file:Documentation/networking/irda.txt>.  You also want to
            read the IR-HOWTO, available at
            <http://www.tldp.org/docs.html#howto>.

            If you want to exchange bits of data (vCal, vCard) with a PDA, you
            will need to install some OBEX application, such as OpenObex :
            <http://sourceforge.net/projects/openobex/>

            To compile this support as a module, choose M here: the module will
            be called irda.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that 
            your laptop (modern laptops) will use this protocol.
```
<h3><&lowast;>   Bluetooth subsystem support  ---></h3>
```properties
Symbol:     CONFIG_BT

Help:       Bluetooth is low-cost, low-power, short-range wireless technology.
            It was designed as a replacement for cables and other short-range
            technologies like IrDA.  Bluetooth operates in personal area range
            that typically extends up to 10 meters.  More information about
            Bluetooth can be found at <http://www.bluetooth.com/>.

            Linux Bluetooth subsystem consist of several layers:
               Bluetooth Core
                  HCI device and connection manager, scheduler
                  SCO audio links
                  L2CAP (Logical Link Control and Adaptation Protocol)
                  SMP (Security Manager Protocol) on LE (Low Energy) links
               HCI Device drivers (Interface to the hardware)
               RFCOMM Module (RFCOMM Protocol)
               BNEP Module (Bluetooth Network Encapsulation Protocol)
               CMTP Module (CAPI Message Transport Protocol)
               HIDP Module (Human Interface Device Protocol)

            Say Y here to compile Bluetooth support into the kernel or say M to
            compile it as module (bluetooth).

            To use Linux Bluetooth subsystem, you will need several user-space
            utilities like hciconfig and bluetoothd.  These utilities and updates
            to Bluetooth kernel modules are provided in the BlueZ packages.  For
            more information, see <http://www.bluez.org/>.

Type:       tristate

Choice:     built-in <∗>

Reason:     You can safely exclude this option if your device doesn't support 
            bluetooth or if you don't want bluetooth included at all.
```
<h3>[&lowast;]   Bluetooth Classic (BR/EDR) features</h3>
```properties
Symbol:     CONFIG_BT_BREDR

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if your device supports bluetooth.
```
<h3>< >     RFCOMM protocol support</h3>
```properties
Symbol:     CONFIG_BT_RFCOMM

Help:       RFCOMM provides connection oriented stream transport.  RFCOMM
            support is required for Dialup Networking, OBEX and other Bluetooth
            applications.

            Say Y here to compile RFCOMM support into the kernel or say M to
            compile it as module (rfcomm).

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely to be needed
            by users who want basic bluetooth support.
```
<h3>[ ]       RFCOMM TTY support</h3>
```properties
Symbol:     CONFIG_BT_RFCOMM_TTY

Help:       This option enables TTY emulation support for RFCOMM channels.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's highly unlikely to be needed
            by users who want basic bluetooth support.
```
<h3>< >     BNEP protocol support</h3>
```properties
Symbol:     CONFIG_BT_BNEP

Help:       BNEP (Bluetooth Network Encapsulation Protocol) is Ethernet
            emulation layer on top of Bluetooth.  BNEP is required for
            Bluetooth PAN (Personal Area Network).

            Say Y here to compile BNEP support into the kernel or say M to
            compile it as module (bnep).

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely to be needed
            by users who want basic bluetooth support.
```
<h3>< >     HIDP protocol support</h3>
```properties
Symbol:     CONFIG_BT_HDIP

Help:       HIDP (Human Interface Device Protocol) is a transport layer
            for HID reports.  HIDP is required for the Bluetooth Human
            Interface Device Profile.

            Say Y here to compile HIDP support into the kernel or say M to
            compile it as module (hidp).

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely to be needed
            by users who want basic bluetooth support.
```
<h3>[&lowast;]     Bluetooth High Speed (HS) features</h3>
```properties
Symbol:     CONFIG_BT_HS

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if your device supports bluetooth as recommended by the Gentoo wiki.
```
<h3>[&lowast;]   Bluetooth Low Energy (LE) features</h3>
```properties
Symbol:     CONFIG_BT_LE

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if your device supports bluetooth as recommended by the Gentoo wiki.
```
<h3>[ ]   Enable LED triggers</h3>
```properties
Symbol:     CONFIG_BT_LEDS

Help:       This option selects a few LED triggers for different
            Bluetooth events.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option.
```
<h3>[ ]   Bluetooth self testing support</h3>
```properties
Symbol:     CONFIG_BT_SELFTEST

Help:       Run self tests when initializing the Bluetooth subsystem.  This
            is a developer option and can cause significant delay when booting
            the system.

            When the Bluetooth subsystem is built as module, then the test
            cases are run first thing at module load time.  When the Bluetooth
            subsystem is compiled into the kernel image, then the test cases
            are run late in the initcall hierarchy.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's for intended for developing
            and testing purposes.
```
<h3>Bluetooth device drivers  ---></h3>
<h3><&lowast;> HCI USB driver</h3>
```properties
Symbol:     CONFIG_BT_HCIBTUSB

Help:       Bluetooth HCI USB driver.
            This driver is required if you want to use Bluetooth devices with
            USB interface.

            Say Y here to compile support for Bluetooth USB devices into the
            kernel or say M to compile it as module (btusb).

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a Bluetooth device with USB interface.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep btusb

            to see if your system has a Bluetooth device with USB interface or not.
```
<h3><&lowast;> HCI UART driver</h3>
```properties
Symbol:     CONFIG_BT_HCIUART

Help:       Bluetooth HCI UART driver.
            This driver is required if you want to use Bluetooth devices with
            serial port interface. You will also need this driver if you have
            UART based Bluetooth PCMCIA and CF devices like Xircom Credit Card
            adapter and BrainBoxes Bluetooth PC Card.

            Say Y here to compile support for Bluetooth UART devices into the
            kernel or say M to compile it as module (hci_uart).

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a UART based Bluetooth device.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep bt

            to see if your system has a UART based Bluetooth device or not.
```
<h3>-&lowast;-   UART (H4) protocol support</h3>
```properties
Symbol:     CONFIG_BT_HCIUART_H4

Help:       UART (H4) is serial protocol for communication between Bluetooth
            device and host. This protocol is required for most Bluetooth devices
            with UART interface, including PCMCIA and CF cards.

            Say Y here to compile support for HCI UART (H4) protocol.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            if you have a UART based Bluetooth device.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep bt

            to see if your system has a UART based Bluetooth device or not.
```
<h3>[&lowast;]   Atheros AR300x serial support</h3>
```properties
Symbol:     CONFIG_BT_HCIUART_ATH3K

Help:       HCIATH3K (HCI Atheros AR300x) is a serial protocol for
            communication between host and Atheros AR300x Bluetooth devices.
            This protocol enables AR300x chips to be enabled with
            power management support.
            Enable this if you have Atheros AR300x serial Bluetooth device.

            Say Y here to compile support for HCI UART ATH3K protocol.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if you have a AR300x Bluetooth device.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep ath3k

            to see if your system has a AR300x Bluetooth device or not.
```
<h3><&lowast;> Atheros firmware download driver</h3>
```properties
Symbol:     CONFIG_BT_ATH3K

Help:       Bluetooth firmware download driver.
            This driver loads the firmware into the Atheros Bluetooth
            chipset.

            Say Y here to compile support for "Atheros firmware download driver"
            into the kernel or say M to compile it as module (ath3k).

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a AR300x Bluetooth device.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep ath3k

            to see if your system has a AR300x Bluetooth device or not.
```
<h3>< >   RxRPC session sockets</h3>
```properties
Symbol:     CONFIG_AF_RXRPC

Help:       Say Y or M here to include support for RxRPC session sockets (just
            the transport part, not the presentation part: (un)marshalling is
            left to the application).

            These are used for AFS kernel filesystem and userspace utilities.

            This module at the moment only supports client operations and is
            currently incomplete.

            See Documentation/networking/rxrpc.txt.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>< >   KCM sockets</h3>
```properties
Symbol:     CONFIG_AF_KCM

Help:       KCM (Kernel Connection Multiplexor) sockets provide a method
            for multiplexing messages of a message based application
            protocol over kernel connectons (e.g. TCP connections).

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>-&lowast;-   Wireless  ---></h3>
```properties
Symbol:     CONFIG_WIRELESS

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            if you're using a laptop or any other system that has a wireless network device.
```
<h3><&lowast;>   cfg80211 - wireless configuration API</h3>
```properties
Symbol:     CONFIG_CFG80211

Help:       cfg80211 is the Linux wireless LAN (802.11) configuration API.
            Enable this if you have a wireless device.

            For more information refer to documentation on the wireless wiki:

            http://wireless.kernel.org/en/developers/Documentation/cfg80211

            When built as a module it will be called cfg80211.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a wireless device (recommended also by the Gentoo wiki).

            This option is aka WEXT, which is basically support for old
            "wireless-tools" and "iwconfig".
```
<h3>[&lowast;]     enable powersave by default</h3>
```properties
Symbol:     CONFIG_CFG80211_DEFAULT_PS

Help:       This option enables powersave mode by default.

            If this causes your applications to misbehave you should fix your
            applications instead -- they need to register their network
            latency requirement, see Documentation/power/pm_qos_interface.txt.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this option in your kernel
            if powersaving on wireless devices was a main concern to you as it'll
            reduce power consumption drastically on a laptop and other similar
            devices.

            The Gentoo wiki recommends that you include it, but on some buggy
            drivers this may cause some connection problems.
```
<h3><&lowast;>   Generic IEEE 802.11 Networking Stack (mac80211)</h3>
```properties
Symbol:     CONFIG_MAC80211

Help:       This option enables the hardware independent IEEE 802.11
            networking stack.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as mentioned in the Gentoo wiki.
```
<h3>[&lowast;]   Minstrel</h3>
```properties
Symbol:     CONFIG_MAC80211_RC_MINSTREL

Help:       This option enables the 'minstrel' TX rate control algorithm

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this rate control algorithm
            if you have a wireless network device as it's famous for its efficiency
            and precision (and it's recommended by the Gentoo wiki).
```
<h3>[&lowast;]     Minstrel 802.11n support</h3>
```properties
Symbol:     CONFIG_MAC80211_RC_MINSTREL_HT

Help:       This option enables the 'minstrel_ht' TX rate control algorithm

Type:       boolean

Choice:     built-in [∗]

Reason:     It's highly recommended that you include this rate control algorithm
            if you have a wireless network device as it's famous for its efficiency
            and precision (and it's recommended by the Gentoo wiki).
```
<h3>Default rate control algorithm (Minstrel)  ---></h3>
```properties
Help:       This option selects the default rate control algorithm
            mac80211 will use. Note that this default can still be
            overridden through the ieee80211_default_rc_algo module
            parameter if different algorithms are available. 
```
<h3>(X) Minstrel</h3>
```properties
Symbol:     CONFIG_MAC80211_RC_DEFAULT_MINSTREL

Help:       Select Minstrel as the default rate control algorithm.

Type:       boolean

Choice:     built-in (X)

Reason:     It's highly recommended that you include this rate control algorithm
            if you have a wireless network device as it's famous for its efficiency
            and precision (and it's recommended by the Gentoo wiki).
```
<h3>-&lowast;-   Enable LED triggers</h3>
```properties
Symbol:     CONFIG_MAC80211_LEDS

Help:       This option enables a few LED triggers for different
            packet receive/transmit events.

Type:       boolean

Choice:     built-in -∗-

Reason:     It's highly recommended that you include this option in your kernel
            to enable LED triggers when receiving/transmitting packets, that is
            if it isn't already forcibly included by CONFIG_WLAN, CONFIG_PCI,
            CONFIG_ATH9K and CONFIG_MAC80211).
```
<h3>< >   WiMAX Wireless Broadband support  ----</h3>
```properties
Symbol:     CONFIG_WIMAX

Help:       Select to configure support for devices that provide
            wireless broadband connectivity using the WiMAX protocol
            (IEEE 802.16).

            Please note that most of these devices require signing up
            for a service plan with a provider.

            The different WiMAX drivers can be enabled in the menu entry

            Device Drivers > Network device support > WiMAX Wireless
            Broadband devices

            If unsure, it is safe to select M (module).

Type:       tristate

Choice:     excluded < >

Reason:     It's highly recommended that you include this option in your kernel
            if you have a device that uses the WiMAX protocol.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lspcinnkkvvv.txt | grep WiMAX

            to see if your system has a device that uses the WiMAX protocol or not.
```
<h3><&lowast;>   RF switch subsystem support  ---></h3>
```properties
Symbol:     CONFIG_RFKILL

Help:       Say Y here if you want to have control over RF switches
            found on many WiFi and Bluetooth cards.

            To compile this driver as a module, choose M here: the
            module will be called rfkill.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            as RF switches are found in a lot of wireless network devices and
            bluetooth cards.

            Plus if you ever wonder why your wireless or bluetooth cards aren't
            working then you may need rfkill to unblock them in order to use them.
```
<h3>[&lowast;]   RF switch input support</h3>
```properties
Symbol:     CONFIG_RFKILL_INPUT

Help:       There is no help available for this option.

Type:       boolean

Choice:     built-in [∗]

Reason:     It's recommended that you include this option in your kernel
            along with CONFIG_RFKILL to ensure that "rfkill" works properly.
```
<h3>< >   Plan 9 Resource Sharing Support (9P2000)  ----</h3>
```properties
Symbol:     CONFIG_NET_9P

Help:       If you say Y here, you will get experimental support for
            Plan 9 resource sharing via the 9P2000 protocol.

            See <http://v9fs.sf.net> for more information.

            If unsure, say N.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>< >   CAIF support  ----</h3>
```properties
Symbol:     CONFIG_CAIF

Help:       The "Communication CPU to Application CPU Interface" (CAIF) is a packet
            based connection-oriented MUX protocol developed by ST-Ericsson for use
            with its modems. It is accessed from user space as sockets (PF_CAIF).

            Say Y (or M) here if you build for a phone product (e.g. Android or
            MeeGo ) that uses CAIF as transport, if unsure say N.

            If you select to build it as module then CAIF_NETDEV also needs to be
            built as modules. You will also need to say yes to any CAIF physical
            devices that your platform requires.

            See Documentation/networking/caif for a further explanation on how to
            use and configure CAIF.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            this option will be needed on a laptop or desktop.
```
<h3>< >   Ceph core library</h3>
```properties
Symbol:     CONFIG_CEPH_LIB

Help:       Choose Y or M here to include cephlib, which provides the
            common functionality to both the Ceph filesystem and
            to the rados block device (rbd).

            More information at http://ceph.newdream.net/.

            If unsure, say N.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3><&lowast;>   NFC subsystem support  ---></h3>
```properties
Symbol:     CONFIG_NFC

Help:       Say Y here if you want to build support for NFC (Near field
            communication) devices.

            To compile this support as a module, choose M here: the module will
            be called nfc.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a NFC device (the 'evil' Intel's Management Engine requires
            it).
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep mei

            to see if your system has a NFC device or not.
```
<h3><&lowast;>   NFC HCI implementation</h3>
```properties
Symbol:     CONFIG_NFC_HCI

Help:       Say Y here if you want to build support for a kernel NFC HCI
            implementation. This is mostly needed for devices that only process
            HCI frames, like for example the NXP pn544.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a NFC device (the 'evil' Intel's Management Engine requires
            it).
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep mei

            to see if your system has a NFC device or not.
```
<h3>Near Field Communication (NFC) devices  ---></h3>
<h3><&lowast;> MEI bus NFC device support</h3>
```properties
Symbol:     CONFIG_NFC_MEI_PHY

Help:       This adds support to use an mei bus nfc device. Select this if you
            will use an HCI NFC driver for an NFC chip connected behind an
            Intel's Management Engine chip.

            If unsure, say N.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a NFC chip connected behind an Intel's Management Engine
            chip.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep mei

            to see if your system has a NFC chip connected behind ann Intel's 
            Management Engine chip or not.
```
<h3><&lowast;> NXP PN544 device support (MEI)</h3>
```properties
Symbol:     CONFIG_NFC_PN544_MEI

Help:       This module adds support for the mei interface of adapters using
            NXP pn544 chipsets.  Select this if your pn544 chipset
            is handled by Intel's Management Engine Interface on your platform.

            If you choose to build a module, it'll be called pn544_mei.
            Say N if unsure.

Type:       tristate

Choice:     built-in <∗>

Reason:     It's highly recommended that you include this option in your kernel
            if you have a pn544 chipset handled by Intel's Management Engine
            Interface.
            
            Please refer to part 11:
            
                https://www.dotslashlinux.com/2017/09/11/the-linux-kernel-configuration-guide-part-11/

            and check the guide at the top to understand how to find what features
            your system supports and what options to include in your kernel.

            If you've followed the guide in part 11, you can simply run:
                
                cat lsmod.txt | grep pn544

            to see if your system has a pn544 chipset handled by Intel's Management
            Engine Interface or not.
```
<h3>< >   Packet-sampling netlink channel  ----</h3>
```properties
Symbol:     CONFIG_PSAMPLE

Help:       Say Y here to add support for packet-sampling netlink channel
            This netlink channel allows transferring packets alongside some
            metadata to userspace.

            To compile this support as a module, choose M here: the module will
            be called psample.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>< >   Inter-FE based on IETF ForCES InterFE LFB  ----</h3>
```properties
Symbol:     CONFIG_NET_IFE

Help:       Say Y here to add support of IFE encapsulation protocol
            For details refer to netdev01 paper:
            "Distributing Linux Traffic Control Classifier-Action Subsystem"
             Authors: Jamal Hadi Salim and Damascene M. Joachimpillai

            To compile this support as a module, choose M here: the module will
            be called ife.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>[ ]   Network light weight tunnels</h3>
```properties
Symbol:     CONFIG_LWTUNNEL

Help:       This feature provides an infrastructure to support light weight
            tunnels like mpls. There is no netdevice associated with a light
            weight tunnel endpoint. Tunnel encapsulation parameters are stored
            with light weight tunnel state associated with fib routes.

Type:       boolean

Choice:     excluded [ ]

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<h3>< >   Network physical/parent device Netlink interface</h3>
```properties
Symbol:     CONFIG_NET_DEVLINK

Help:       Network physical/parent device Netlink interface provides
            infrastructure to support access to physical chip-wide config and
            monitoring.

Type:       tristate

Choice:     excluded < >

Reason:     You can safely exclude this option as it's highly unlikely that
            a normal user will be using this option.
```
<hr/>
<h3>Chinese Translation</h3>
One of DOTSLASHLINUX followers 杨鑫 (Yang Mame) from China, decided to follow up with the series and provide Chinese translation of the kernel configuration guides on his blog.
<br/>
<br/>
To read this guide in Chinese <a href="https://blog.yangmame.top/Linux内核配置指南-Networking-support和Device-Drivers.html" target="_blank">click here</a>.
