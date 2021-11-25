Notes on first-time installation
================================

Checking branding
-----------------

The are two variants of "branding", in both cases the retail firmware images (modified or unmodified)  
will not work out of the box:  
- Provider branding (firmware_version != avm)  
- International version of the box (firmware_version == avm, retail flag not set).  

To safe yourself some trouble (and myself questions) i recommend buying a retail box. Otherwise, read ["Installation on branded/international Boxes"](#markdown-header-Installation-on-branded/international-Boxes) further below.

Checking BIOS version
---------------------

Before deciding/attempting how/whether to modify the box, check which BIOS version
you are running. To do so, restart the box and obtain extended support data
(erweiterete supportdaten) via http://192.168.178.1/support.lua.

It is generally a good idea to KEEP this file since it might become helpful
for recovering a bricked box!

Once the .txt file is downloaded look for the "BIOS" string and its date code:

For BIOS older CGM2.86C.627075.R.1910091149 10/09/2019 - Update via serial console
----------------------------------------------------------------------------------

This requires opening the box and connecting a UART adapter. Unless you break the
box by doing so, this method is relatively safe since it uses the standard AVM
update method.

Placement of console through-holes (FB6591):
~~~
  ┌──────────────────────────────────────────────────────────┐
  │                       Bottom                             │
  │                              ┌─────────┐                 │
  │                              │         │                 │
  │   ┌───────────────────────┐  │         └──────────┐      │
  │   │                       │  │      Metal shield  │      │
  │   │                       │  │                    │      │
  │   │  CPU/Heatsink         │  └────────────────────┘      │
  │   │                       │    oooo  <- Atom Console:    │
  │   │                       │             1.8V,Rx,Tx,GND   │
  │   │                       │                              │
  │   │                       │                              │
  │   └───────────────────────┘oooo   <- ARM console:        │
  │                                      GND,Tx,Rx,3.3V      │
  │Front                                                Rear │
  │ side                                                 side│
  │                                                          │
  │                 Top    Antennas                          │
  └──────────────────────────────────────────────────────────┘
~~~

The Atom console can be used for updating the box and for the EFI shell, it's operated at 1.8V level. 
In theory the ARM console can also be used (if you only have a 3.3V RS232 adapter), but there is no 
access to the EFI shell for recovery.

Connect a RS232 adapter to GND/Tx/Rx, configure terminal program to 115200/8/n/1.

To activate the UART pins:  
- Connect to the Eva ftp command shell
- Enter

      quote SETENV kernel_args mute=0
      quote REBOOT

This will presistently activate the UART. Depending on which console you have connected there 
should be some some output from the kernel. Press return at the end and you should have a shell
where you can execute the update (using burnuimg as described in README.md).

If you are connected to the ARM console and want to execute commands on the atom core, use rpc. For example:

rpc "sh -c ls"

Update via EVA (BIOS CGM2.86C.627075.R.1910091149 10/09/2019)
-------------------------------------------------------------

This is the more or less well known method via the EVA bootloader, using a ftp client
to push the four required eMMC partition contents.

There might be LATER BIOS VERSION .. i cant tell if/how it works there, so check twice
before proceeding!

Required is a ftp client which supports passive mode. I recommend using the native
Ubuntu/Debian ftp client (see troubleshooting section further below).
Alternatively you can use the [YourFritz/eva_tools](https://github.com/PeterPawn/YourFritz) PowerShell 
tools to query/change settings and push images to flash partitions.

All examples here use the default address 192.168.178.1.

To enter the EVA bootloader's FTP server:  
- Repower the box
- Wait ca 5 seconds
- Run the ftp client: ftp 192.168.178.1  
  user/password is adam2/adam2

The corresponding eva_tools command (re-power the box and run it):

      .\EVA-FTP-Client.ps1 -ScriptBlock { Login }

Steps:

1.  Generate the update image as described in README.md.  
    Once complete, there will be some image files in the subdirectory build/puma7/uimage:

        ffritz$ cd build/puma7/uimage/
        ffritz/build/puma7/uimage$ ls -l
        -r--r--r-- 1 felix osboxes  9437184 Apr 13 07:37 part_02_ATOM_KERNEL.bin
        -rw-r--r-- 1 felix osboxes 29569024 Apr 13 07:37 part_03_ATOM_ROOTFS.bin
        -r--r--r-- 1 felix osboxes  2335056 Apr 13 07:36 part_08_ARM_KERNEL.bin
        -rw-r--r-- 1 felix osboxes 17981440 Apr 13 07:37 part_09_ARM_ROOTFS.bin

    If you have an existing update image you want to install, you can extract these bin
    files from it using the uimg tool. For example:

        make -C tools/uimg-tool
        tar xf FRITZ.Box_6591_Cable-07.19-80492-Labor.image ./var/firmware-update.uimg
        tools/uimg-tool/uimg -u -n part ./var/firmware-update.uimg

2.  Connect to the ftp client and query the current active partition (unless you already know it):

        quote GETENV linux_fs_start

    This will provide the currently active partition set (0 or 1). We always
    want to write the one which is not active, and switch to it afterwards.

    If no value is provided assume partition number 0.

    **As the response to this command will most likely have confused your ftp client,
    re-power the box and re-enter the ftp server**.

    The corresponding eva_tools command:

        .\EVA-FTP-Client.ps1 -ScriptBlock { GetEnvironmentValue linux_fs_start }

3.  Configure ftp (binary/pasive)  

        bin
        quote MEDIA FLSH
        passive

    (Not required when using eva_tools)

4.  Write firmware images

    To write and switch to partition set I=0 (if linux_fs_start = 1):

        put part_03_ATOM_ROOTFS.bin mtd0
        put part_02_ATOM_KERNEL.bin mtd1
        put part_09_ARM_ROOTFS.bin mtd6
        put part_08_ARM_KERNEL.bin mtd7
        quote SETENV linux_fs_start 0

    To write and switch to partition set I=1 (if linux_fs_start = 0):

        put part_03_ATOM_ROOTFS.bin mtd;
        put part_02_ATOM_KERNEL.bin mtd<
        put part_09_ARM_ROOTFS.bin mtd=
        put part_08_ARM_KERNEL.bin mtd>
        quote SETENV linux_fs_start 1

    The corresponding eva_tools commands:

        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_03_ATOM_ROOTFS.bin mtd0 }
        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_02_ATOM_KERNEL.bin mtd1 }
        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_09_ARM_ROOTFS.bin mtd6 }
        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_08_ARM_KERNEL.bin mtd7 }
        .\EVA-FTP-Client.ps1 -ScriptBlock { SetEnvironmentValue linux_fs_start 0 }

      or

        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_03_ATOM_ROOTFS.bin 'mtd;' }
        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_02_ATOM_KERNEL.bin 'mtd<' }
        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_09_ARM_ROOTFS.bin 'mtd=' }
        .\EVA-FTP-Client.ps1 -ScriptBlock { UploadFlashFile .\part_08_ARM_KERNEL.bin 'mtd>' }
        .\EVA-FTP-Client.ps1 -ScriptBlock { SetEnvironmentValue linux_fs_start 1 }

5.  Reboot

        quote REBOOT

    or

        .\EVA-FTP-Client.ps1 -ScriptBlock { RebootTheDevice } 

The modified image should now start, and telnet/ssh login should be possible as described
in README.md. Subsequent updates can be done using the burnuimg tool.

If something went wrong, the box will either automatically switch back to the old boot bank,
or you need to change back linux_fs_start manually, or ....

The part_10_GWFS.bin file can not be written via the bootloader, but so far it was not required. 
To be on the safe side you might want to re-program everything using burnuimg.

Problems / Troubleshooting
--------------------------
- Under certain circumstances (i have not yet tried to figure out when/why exactly) the
  bootbank switch does not seem to work. It is generally also OK to write to the ACTIVE partition 
  and not change linux_fs_start.  

- A know issue with some ftp clients is that they sometimes seem to time out during flash 
  update (e.g. ncftp), especially when a partition is not empty.  
  I never had problems with the native Debian/Ubuntu ftp client or eva_tools.  

- Some ftp clients don't support the special characters in the partition name at all,
  some seem to require putting a backslash before them:

            put part_03_ATOM_ROOTFS.bin mtd\;
            put part_02_ATOM_KERNEL.bin mtd\<
            put part_09_ARM_ROOTFS.bin mtd\=
            put part_08_ARM_KERNEL.bin mtd\>

  I never had problems with the native Ubuntu/Debian ftp client or eva_tools.  

- The response to the getenv command confuses most ftp clients. Pressing return several times
  might reveal missing information, but don't assume that actions (setenv/put) will work or
  have an effect afterwards.  
  Close and re-start the ftp connection when in doubt.

- Also recommended is a switch between your PC and the box to avoid the link going down when
  the box restarts. And/or the IP address of your host on the box network (192.168.178)
  should be configured statically, at least for the time you work with the boot loader.

Installation on branded/international Boxes
===========================================
Information about this is stored in firmware variables "firmware_version" and "DMC". Those can be 
checked either by generating support data or reading them out on the Eva boot loader's command prompt 
("quote GETENV firmware_version").

~~~
firmware_version  DMC       Notes
----------------- ------------- ----------------------------------------------------------
avm               RTL=Y         Retail box, no further actions required.
                  (or nothing)  
avm               RTL=N,...     International version of box. Can be permanently changed
                                to RTL=Y.
something else    RTL=Y         Not seen in the wild.
something else    RTL=N,..      Provider box. Can not be changed permanently.
----------------- ------------- ----------------------------------------------------------
~~~

If anyone sold you an "original box" where firmware_version is not "avm" it's a fraud.

Temporarily modify firmware_version
-----------------------------------
To generate a firmware image which will boot on a branded box:

Copy the file user-oem.patch to the atom/arm directories and generate a modified update image:

    cp user-oem.patch puma7/atom/
    cp user-oem.patch puma7/arm/
    make

This image can be installed on a branded box, but several features might not work (DVB-C, SIP, ..?).
In any case, an automatic firmware update will not be offered .. which is good, as this would 
install an image that can't boot (as it obviously does not contain my patch).

For each new firmware version, you need to re-generate a patched image and install it manually.

You can try to activate missing features by doing the next step, but then 

! **don't ever install an update** offered by AVM via the GUI, and **never activate automatic update** !

To modify the "retail flag" (DMC)
---------------------------------
Connect with the eva ftp server of the boot loader (see "Update via EVA" step 2 above). Then execute

    quote SETENV DMC RTL=Y
    quote REBOOT

The original value of DMC sometimes contains a suffix after "RTL=N". I don't know what it's good for. 
You might want to retain it ("RTL=Y,suffix"), but i don't see a problem in just omitting it. In any 
case, you can change it back if there are issues.

Footnote
--------
As i'm being asked, changing firmware_version permanently is possible by editing the SPI flash
partitions (see below).
When you do this wrong, the only way to recover the box is to  
- have the flash partitions backed up _before_ you did this,  
- unsolder the flash,  
- re-program it with a flash programmer and  
- re-solder it.

Or, just buy a retail box (preferrably before you destroyed a provider box).


Getting Access to the EFI shell
===============================

This is only if you know what you can/want to do with it (and you have a serial
connector attached)...

If you have an old BIOS, enter "exit" immedeately after the "eva hack ready message" appears, 
followed by escape several times. 

On a new BIOS you need to reflash the ATOM_KERNEL partition after having modified the startup script:  

Steps:

1.  Unpack the boot image  

        make -C tools/uimg-tool/uimg
        tar xf FRITZ.Box_6591_Cable-07.19-80492-Labor.image ./var/firmware-update.uimg
        tools/uimg-tool/uimg -u -n part ./var/firmware-update.uimg

2.  Mount the boot partition  

        sudo su
        mkdir mnt
        mount -o loop part_02_ATOM_KERNEL.bin mnt

3.  Save/replace startup.nsh  

        cp mnt/EFI/BOOT/startup.nsh mnt/EFI/BOOT/startorg.nsh
        echo "mm 0xfed94810 0x00914b49 -w 4" > mnt/EFI/BOOT/startup.nsh
        echo "mm 0xfed94820 0x00914b49 -w 4" >> mnt/EFI/BOOT/startup.nsh
        umount mnt

    This change will enable the serial output, but not load/start the linux kernel 
    and drop to the EFI shell instead.  
    The backup of the original (startorg.nsh) can be used to boot FritzOS from the shell.

4.  Repack the image  

        tools/uimg-tool/uimg -p -n part out.img

5.  Program the image  
    You can either program the whole out.img from the shell, or only update 
    part_02_ATOM_KERNEL.bin via EVA/ftp as described above.

To program a firmware image from the EFI shell (recovery)
---------------------------------------------------------

1. Copy firmware-update.uimg to an USB stick and connect it to the box.
2. Power on an go to the EFI shell as described
3. The "map" command will list the default device mappings. The USB stick should appear like
   this:

      FS2: Alias(s):HD36c0b:;BLK22:
      PciRoot(0x0)/Pci(0x14,0x0)/USB(0x2,0x0)/HD(1,MBR,0x0047BD56,0x40,0x7807C0)

4. Load the image to memory (here FS2: is the USB stick as listed by map):

      load2mem -f FS2:\firmware-update.uimg

5. Note down the address
6. To write to the backup boot bank, switch to it first:

      aid toggle
      aid update

7. Now program the image (with the address from above):

      update -a A -s 0x513A010

9. Reboot on success ("Congrats! Looks like everything went as planned! Your flash has been updated! 
   Have a good day!"):

      reset

FB6591 eMMC partition information
=================================

P: Corresponds to /dev/mmcblk0pXX devices
I: Corresponds to linux_fs_start content

~~~
P  I Content           Type         Start End    Size   Start    End
                                   LBA   LBA    LBA    Offset   Offset     EVA mtd
-- - ---------------- ------------  ----- ------ ------ -------- --------- -------
1  0 SIGBLOCK0        raw          800   8FF    100    100000   11FE00
2  0 APP_CPU_KERNEL0  uefi/fat     1000  57FF   4800   200000   AFFE00     mtd1
3  0 APP_CPU_ROOTFS0  squashfs     5800  297FF  24000  B00000   52FFE00    mtd0
4  0 NP_CPU_KERNEL0   raw_bzImage  29800 2BFFF  2800   5300000  57FFE00    mtd7
5  0 NP_CPU_ROOTFS0   squashfs_be  2C000 357FF  9800   5800000  6AFFE00    mtd6
6  0 GW_FS0           tar          35800 497FF  14000  6B00000  92FFE00
7  1 SIGBLOCK1        raw          49800 498FF  100    9300000  931FE00
8  1 APP_CPU_KERNEL1  uefi/fat     4A000 4E7FF  4800   9400000  9CFFE00    mtd<
9  1 APP_CPU_ROOTFS1  squashfs     4E800 727FF  24000  9D00000  E4FFE00    mtd;
10 1 NP_CPU_KERNEL1   raw_bzImage  72800 74FFF  2800   E500000  E9FFE00    mtd>
11 1 NP_CPU_ROOTFS1   squashfs_be  75000 7E7FF  9800   EA00000  FCFFE00    mtd=
12 1 GW_FS1           tar          7E800 927FF  14000  FD00000  124FFE00
13   APP_CPU_NVRAM    ext4         92800 967FF  4000   12500000 12CFFE00
14   NP_CPU_NVRAM     ext4         96800 9A7FF  4000   12D00000 134FFE00
15   AVM_TFFS1        tffs         9A800 9E7FF  4000   13500000 13CFFE00
16   AVM_TFFS2        tffs         9E800 A27FF  4000   13D00000 144FFE00
17   AVM_UPD_TMP      ???          A2800 E27FF  40000  14500000 1C4FFE00
18   AVM_MEDIA        ext4         E2800 75FFDE 67D7DF 1C500000 EBFFBC00
~~~

(Yes, it's "mtd;" / "mtd<" / "mtd=" / "mtd>", not mtd11/12/13/14).

SPI Flash layout
================

Old BIOS:

~~~
device		offset		size		end		Name
--------------- --------------- --------------- --------------- ---------
mtdblock0	0x000000	0x001000	0x001000	Descriptor
mtdblock2	0x001000	0x0e0000	0x0e1000	ME   
mtdblock3	0x0e1000	0x043000	0x124000	PDR
mtdblock1	0x124000	0x0dc000	0x200000	BIOS
~~~

New BIOS:

~~~
device		offset		size		end		Name
--------------- --------------- --------------- ---------------	---------
mtdblock0	0x000000	0x001000	0x001000	Descriptor
mtdblock2	0x001000	0x0d8000	0x0d9000	ME   
mtdblock3	0x0d9000	0x04b000	0x124000	PDR
mtdblock1	0x124000	0x0dc000	0x200000	BIOS
~~~


