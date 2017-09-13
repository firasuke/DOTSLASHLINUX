+++
title = "The Linux Kernel Configuration Guide Part 16"
slug = "the linux kernel configuration guide part 16"
nick = "kernel16"
date = "2017-09-16"
author = "Firas Khalil Khana"
imgsrc = "/img/kernel16.png"
imgalt = "kernel16"
categories = [ "kernel" ]
+++
It's highly recommended that you leave this section alone. All needed options in this section will be forcibly included by other options in other sections so you don't have to worry about this section much.
<br/>
<br/>
One thing you could do is after you've included all the required options for your system, you can enter this section and exclude options that weren't forcibly included by other options (as in most cases they will not be used).
<br/>
<br/>
Again, the options I'll be listing here will be the ones that got forcibly included on my system, in addition to some other options that I found useful (with the help of SystemRescueCd of course) as you may find it useful.
<hr/>
<h3>-&ast;- Cryptographic API  ---></h3>
```none
Symbol:     CONFIG_CRYPTO

Help:       This option provides the core Cryptographic API.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by a lot of important options.
```
<h3>-&ast;-   ECDH algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_ECDH

Help:       Generic implementation of the ECDH algorithm

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_BT and
            CONFIG_RFKILL.
```
<h3>-&ast;-   Cryptographic algorithm manager</h3>
```none
Symbol:     CONFIG_CRYPTO_MANAGER

Help:       Create default cryptographic template instantiations such as
            cbc(aes).

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by a lot of important options.
```
<h3>-&ast;-   GF(2^128) multiplication functions</h3>
```none
Symbol:     CONFIG_CRYPTO_GF128MUL

Help:       Efficient table driven implementation of multiplications in the
            field GF(2^128).  This is needed by some cypher modes. This
            option will be selected automatically if you select such a
            cipher mode.  Only select this option by hand if you expect to load
            an external module that requires these functions.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_CRYPTO_GHASH.
```
<h3>-&ast;-   Null algorithms</h3>
```none
Symbol:     CONFIG_CRYPTO_NULL

Help:       These are 'Null' algorithms, used by IPsec, which do nothing.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by a lot of important options.
```
<h3>-&ast;-   CCM support</h3>
```none
Symbol:     CONFIG_CRYPTO_CCM

Help:       Support for Counter with CBC MAC. Required for IPsec.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_WIRELESS,
            CONFIG_CFG80211 and CONFIG_MAC80211.
```
<h3>-&ast;-   GCM/GMAC support</h3>
```none
Symbol:     CONFIG_CRYPTO_GCM

Help:       Support for Galois/Counter Mode (GCM) and Galois Message
            Authentication Code (GMAC). Required for IPSec.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_WIRELESS,
            CONFIG_CFG80211 and CONFIG_MAC80211.
```
<h3>-&ast;-   Sequence Number IV Generator</h3>
```none
Symbol:     CONFIG_CRYPTO_SEQIV

Help:       This IV generator generates an IV based on a sequence number by
            xoring it with a salt.  This algorithm is mainly useful for CTR

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by some important options.
```
<h3>-&ast;-   CTR support</h3>
```none
Symbol:     CONFIG_CRYPTO_CTR

Help:       CTR: Counter mode
            This block cipher algorithm is required for IPSec.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_NET and a lot of 
            important options.
```
<h3>-&ast;-   ECB support</h3>
```none
Symbol:     CONFIG_CRYPTO_ECB

Help:       ECB: Electronic CodeBook mode
            This is the simplest block cipher algorithm.  It simply encrypts
            the input block by block.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_PCI, CONFIG_NET,
            CONFIG_WLAN and a lot of important options.
```
<h3>-&ast;-   CMAC support</h3>
```none
Symbol:     CONFIG_CRYPTO_CMAC

Help:       Cipher-based Message Authentication Code (CMAC) specified by
            The National Institute of Standards and Technology (NIST).

            https://tools.ietf.org/html/rfc4493
            http://csrc.nist.gov/publications/nistpubs/800-38B/SP_800-38B.pdf

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_BT,
            CONFIG_MAC80211, CONFIG_RFKILL and other important options.
```
<h3>-&ast;-   HMAC support</h3>
```none
Symbol:     CONFIG_CRYPTO_HMAC

Help:       HMAC: Keyed-Hashing for Message Authentication (RFC2104).
            This is required for IPSec.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_GENTOO_LINUX,
            CONFIG_GENTOO_LINUX_INIT_SYSTEMD, CONFIG_NET and a lot of important
            options.
```
<h3>-&ast;-   CRC32c CRC algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_CRC32C

Help:       Castagnoli, et al Cyclic Redundancy-Check Algorithm.  Used
            by iSCSI for header and data digests and by others.
            See Castagnoli93.  Module will be crc32c.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_SCSI, CONFIG_NET,
            CONFIG_BLOCK, CONFIG_EXT4_FS and some other important options.
```
<h3><&ast;>   CRC32c INTEL hardware acceleration</h3>
```none
Symbol:     CONFIG_CRYPTO_CRC32C_INTEL

Help:       In Intel processor with SSE4.2 supported, the processor will
            support CRC32C implementation using hardware accelerated CRC32
            instruction. This option will create 'crc32c-intel' module,
            which will enable any routine to use the CRC32 instruction to
            gain performance compared with software implementation.
            Module will be crc32c-intel.

Type:       tristate

Choice:     built-in <*>

Reason:     If you've followed the guide in part 11, then a simple:

                cat lsmod.txt | grep crc32c_intel

            should tell you whether you need this option or not.
```
<h3><&ast;>   CRC32 PCLMULQDQ hardware acceleration</h3>
```none
Symbol:     CONFIG_CRYPTO_CRC32_PCLMUL

Help:       From Intel Westmere and AMD Bulldozer processor with SSE4.2
            and PCLMULQDQ supported, the processor will support
            CRC32 PCLMULQDQ implementation using hardware accelerated PCLMULQDQ
            instruction. This option will create 'crc32-plcmul' module,
            which will enable any routine to use the CRC-32-IEEE 802.3 checksum
            and gain better performance as compared with the table implementation.

Type:       tristate

Choice:     built-in <*>

Reason:     If you've followed the guide in part 11, then a simple:

                cat lsmod.txt | grep crc32_pclmul

            should tell you whether you need this option or not.
```
<h3>-&ast;-   CRCT10DIF algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_CRCT10DIF

Help:       CRC T10 Data Integrity Field computation is being cast as
            a crypto transform.  This allows for faster crc t10 diff
            transforms to be used if they are available.

Type:       tristate

Choice:     built-in -*-

Reason:     If you've followed the guide in part 11, then a simple:

                cat lsmod.txt | grep crct10dif

            should tell you whether you need this option or not.
```
<h3><&ast;>   CRCT10DIF PCLMULQDQ hardware acceleration</h3>
```none
Symbol:     CONFIG_CRYPTO_CRCT10DIF_PCLMUL

Help:       For x86_64 processors with SSE4.2 and PCLMULQDQ supported,
            CRC T10 DIF PCLMULQDQ computation can be hardware
            accelerated PCLMULQDQ instruction. This option will create
            'crct10dif-plcmul' module, which is faster when computing the
            crct10dif checksum as compared with the generic table implementation.

Type:       tristate

Choice:     built-in <*>

Reason:     If you've followed the guide in part 11, then a simple:

                cat lsmod.txt | grep crct10dif

            should tell you whether you need this option or not.
```
<h3>-&ast;-   GHASH digest algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_GHASH

Help:       GHASH is message digest algorithm for GCM (Galois/Counter Mode).

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by some important options.
```
<h3><&ast;>   MD5 digest algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_MD5

Help:       MD5 message digest algorithm (RFC1321).

Type:       tristate

Choice:     built-in <*>
```
<h3>-&ast;-   SHA224 and SHA256 digest algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_SHA256

Help:       SHA256 secure hash standard (DFIPS 180-2).

            This version of SHA implements a 256 bit hash with 128 bits of
            security against collision attacks.

            This code also includes SHA-224, a 224 bit hash with 112 bits
            of security against collision attacks.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_GENTOO_LINUX,
            CONFIG_GENTOO_LINUX_UDEV, CONFIG_GENTOO_LINUX_INIT_SYSTEMD,
            CONFIG_NET and a lot of important options.
```
<h3><&ast;>   SHA384 and SHA512 digest algorithms</h3>
```none
Symbol:     CONFIG_CRYPTO_SHA512

Help:       SHA512 secure hash standard (DFIPS 180-2).

            This version of SHA implements a 512 bit hash with 256 bits of
            security against collision attacks.

            This code also includes SHA-384, a 384 bit hash with 192 bits
            of security against collision attacks.

Type:       tristate

Choice:     built-in <*>
```
<h3>-&ast;-   AES cipher algorithms</h3>
```none
Symbol:     CONFIG_CRYPTO_AES

Help:       AES cipher algorithms (FIPS-197). AES uses the Rijndael
            algorithm.

            Rijndael appears to be consistently a very good performer in
            both hardware and software across a wide range of computing
            environments regardless of its use in feedback or non-feedback
            modes. Its key setup time is excellent, and its key agility is
            good. Rijndael's very low memory requirements make it very well
            suited for restricted-space environments, in which it also
            demonstrates excellent performance. Rijndael's operations are
            among the easiest to defend against power and timing attacks.

            The AES specifies three key sizes: 128, 192 and 256 bits

            See <http://csrc.nist.gov/CryptoToolkit/aes/> for more information.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_NET, CONFIG_BT,
            CONFIG_MAC80211, CONFIG_CFG80211, CONFIG_WIRELESS, CONFIG_RFKILL
            and a lot of important options.
```
<h3>-&ast;-   ARC4 cipher algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_ARC4

Help:       ARC4 cipher algorithm.

            ARC4 is a stream cipher using keys ranging from 8 bits to 2048
            bits in length.  This algorithm is required for driver-based
            WEP, but it should not be for other purposes because of the
            weakness of the algorithm.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by CONFIG_PCI, CONFIG_NET,
            CONFIG_MAC80211, CONFIG_CFG80211, CONFIG_WIRELESS, CONFIG_RFKILL
            and some other important options.
```
<h3><&ast;>   LZ4 compression algorithm</h3>
```none
Symbol:     CONFIG_CRYPTO_LZ4

Help:       This is the LZ4 algorithm.

Type:       tristate

Choice:     built-in <*>
```
<h3>-&ast;-   NIST SP800-90A DRBG  ---></h3>
```none
Symbol:     CONFIG_CRYPTO_DRBG_MENU

Help:       NIST SP800-90A compliant DRBG. In the following submenu, one or
            more of the DRBG types must be selected.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by some important options.
```
<h3>-&ast;-   Jitterentropy Non-Deterministic Random Number Generator</h3>
```none
Symbol:     CONFIG_CRYPTO_JITTERENTROPY

Help:       The Jitterentropy RNG is a noise that is intended
            to provide seed to another RNG. The RNG does not
            perform any cryptographic whitening of the generated
            random numbers. This Jitterentropy RNG registers with
            the kernel crypto API and can be used by any caller.

Type:       tristate

Choice:     built-in -*-

Reason:     Forcibly included as it's required by some important options.
```
