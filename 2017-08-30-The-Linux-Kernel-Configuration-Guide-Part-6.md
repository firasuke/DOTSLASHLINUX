+++
title = "The Linux Kernel Configuration Guide Part 6"
slug = "the linux kernel configuration guide part 6"
nick = "kernel6"
date = "2017-08-30"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel6.png"
imgalt = "kernel6"
+++
The choice of my options will be heavily affected by the cpu my laptop uses (an <a href="http://ark.intel.com/products/75117/Intel-Core-i7-4700MQ-Processor-6M-Cache-up-to-3_40-GHz" target="_blank">Intel Core i7 4700MQ</a>
<h3>Processor type and features  ---></h3>
<h3>[ ] DMA memory allocation support</h3>
```none
Symbol:     CONFIG_ZONE_DMA

Help:       DMA memory allocation support allows devices with less than 32-bit
            addressing to allocate within the first 16MB of address space.
            Disable if no such devices will be used.

            If unsure, say Y.

Type:       boolean

Choice:     excluded [ ]

Reason:     Recent systems (mainly post 2012) have almost no devices with less than
            32-bit addressing, so if you're on a modern system you can safely
            exclude this option like I did (late 2013 laptop).
```
<h3> </h3>
```none
```
