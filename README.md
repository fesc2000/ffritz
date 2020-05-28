Introduction 
============
This is a repository containing my modifications for FritzBox-6591 Cable.
It basically modifies the original AVM install image by adding an ssh
(dropbear) service to log in, and also provides an optional application
package adding further services (mainly for operating the box as audio/media
player).

This README covers the first topic. For information on the application
image see README-APP.md.

I take no responsibility for broken devices or other problems (e.g. with
your provider).  Use this at your own risk.
Also, what i DO NOT support is:

- Modifying other peoples property (do experiments with hardware you own)
- Commercial resellers of rebranded hardware

If you don't trust my binaries (you shouldn't), everything that is required to
rebuild them is provided (see below).

NOTE: This is the branch for FritzBox 6591. For 6490/6590 use the master
      branch of the repository (<https://bitbucket.org/fesc2000/ffritz/src/master/>).

Have Fun,
<f/e/s/c/2/0/0/0/@/g/m/a/i/l/./c/o/m>


Creating an install/update firmware image
=========================================

- Clone repository (6591 branch):

    `git clone --branch 6591 https://fesc2000@bitbucket.org/fesc2000/ffritz.git`

- Go to ffritz directory

- To change the default build settings (AVM image URL, etc) copy conf.mk.dfl to
  conf.mk and edit it.

- Run make

Note that this will use pre-built binaries checked into the git repository.
To rebuild these binaries:

	make rebuild

If you want to build an image based on a different original firmware, select
the URL definition in conf.mk (by commenting out the one you want).
Or place the image file to the packages/dl directory and set URL=filename

Gaining shell access/installing for the first time
--------------------------------------------------
There are two known ways on how to acheive this, depending on which version 
of the bootloader you are running. Details are described in README-6591.md.

But beware, each method has the potential risk of bricking your box!

Once telnet/ssh is running future updates no longer require this step.

Installing the image (with ssh/telnet/console access)
-----------------------------------------------------

- Copy the release tar image to the box, e.g. NAS (/var/media/ftp)
- If this is the very first installation you need to use the use a
  serial adapter to obtain shell access (as described in the forum link
  mentioned above). Otherwise just log in via ssh.
- Extract the image:

~~~
	cd /var/media/ftp; tar xf fb6591_7.13-24.tar
~~~

- Install the image:

~~~
	/sbin/burnuimg /var/media/ftp/var/firmware-update.uimg || echo FAILED
~~~

- After successful installation, execute the following command to switch
  the boot bank and reboot:

~~~
	/bin/aicmd pumaglued uimg switchandreboot
~~~

First use
---------

After first installation, ssh login needs to be set up:

- Log in to the box using console, or telnet and the web password within
  the first 10 minutes after startup.
- For password authentication, call "passwd" to change the root password
- For pubkey authentication, put your public key(s) to /.ssh/authorized_keys

Features
========

Persistent storage
------------------
Various data is stored persistently in the /nvram/ffnvram directory.
/nvram is a ext4 filesystem on the eMMC. The maximum size is 6MB, so
ffnvram is not supposed to contain much data (only configuration files).
By default this is

- the password database (/etc/shadow file)
- dropbear data (dropbear directory)
- the roots .ssh directory (root_ssh directory), which also contains a subfolder
  with the data for OpenVPN (root_ssh/openvpn).

The executable script /nvram/ffnvram/etc/rc.user, if it exists, is executed at
the end of system startup.

telnet
------
- A telnetd service is started at boot time and killed after 600 seconds.

dropber/ssh/scp
---------------
- The dropbear host key (/nvram/ffnvram/dropbear/dropbear_rsa_host_key) is always
  overwritten with the data derived from the web/SSL key of the box
  (/var/flash/websrv_ssl_key.pem).
- In order to use a different box key, create the file
  /nvram/ffnvram/dropbear/rsa_key_dontoverwrite and create a different rsa key
  using dropbearkey.

openssl
---------------------------
- /usr/bin/openssl is a wrapper to make sure openssl uses the correct libraries.

User defined startup script
---------------------------
The file /nvram/ffnvram/etc/init.d/rc.user can be used to add your own startup
commands.

Software Packages
=================

Application CPU (Atom)
----------------------
In addition to the core features it is possible to install an application image
to the Atom core. See README-APP.md for details.

ARM CPU
-------

By default no modifications are made to the root filesystem of the ARM CPU since
there is usually no point in running anything on it.

Defining the option FFRITZ_ARM_PACKAGE in conf.mk allows integrating an 
application package containing tools from a buildroot environment as it is
generated by the "make package-arm" build target.
The default configuration contains a few basic tools like dropbear, tcpdump,
curl, rsync, socat, gdb. This buildroot configuration for ARM can be modified
using the "make arm-brconfig" make target.

Note that unlike the atom application package (which can be re-installed at runtime)
the arm package is added statically into the firmware update image.

Notes
=====

Patches
-------
If you need/want to add your own patches for the Atom root filesystem, put them
to atom/user-*.patch.
To add/replace complete files/hierarchies in the filesystem, add them below
the atom/mod directory.

Likewise for ARM.

Toolchain
---------
Cross-compile toolchain for ARM and atom is buildroot-2019-05
It is installed in packages/x86/buildroot (just do a make there).

Build Host
----------

Tested: Debian 7, Debian 8, CentOS 7, Ubuntu 14.04, Ubuntu 16.04, Debian 9 (preferred)

Used disk space is ca. 10G.

Required (debian) packages are:
gcc g++ make bison libreadline-dev gawk libtool realpath pkg-config zlibc gnulib libcap-dev rsync busybox curl wget squashfs-tools flex python perl zip unzip tcl bzip2 locales git xsltproc libncurses-dev gettext sudo bc subversion fakeroot

Big endian squashfs tools
-------------------------

Binaries are provided in the "hosts" directory. If they dont work, try cloning
freetz and build them using "make squashfstools-be".

There is a make rule "squashfstools-be" that does this.

Required (debian) packages are:
apt-get install gawk libtool realpath pkg-config zlibc gnulib libcap-dev

You might have to remove "composite" and "sys/acl.h" from the
.build-prerequisites file

Credits
=======
Thanks to

- PeterPawn for his tools [https://github.com/PeterPawn], ideas and general contributions
- flole for helping with gaining shell access to 6591
- Themaister for libmaru [https://github.com/Themaister/libmaru]
- Bluekitchen for the user space bluetooth stack [https://github.com/bluekitchen]
- freetz project
- AVM, after all
