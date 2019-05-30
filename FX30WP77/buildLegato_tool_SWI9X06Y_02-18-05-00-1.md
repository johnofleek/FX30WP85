# This doc purpose
1. For command line cross building of Linux apps targeting WP77xx
1. For command line cross building of legato apps using the legato tools

# What you can do after the tool installs

## Environment setup for command line Linux build
So command line builds work such as $CC is set

```
$ . /opt/swi/SWI9X06Y_02.18.05.00/environment-setup-armv7a-neon-poky-linux-gnueabi
$ echo $CC
arm-poky-linux-gnueabi-gcc -march=armv7-a -mfpu=neon -mfloat-abi=softfp --sysroot=/opt/swi/SWI9X06Y_02.18.05.00/sysroots/armv7a-neon-poky-linux-gnueabi
```

## Environment setup for Legato build
This relies on the legato/bin folder existing - when you download the legato image it is in source form you have to build it and it relies on the cross build toolchain to build - if /bin is missing see below 

```
source ./bin/configlegatoenv
```

# Installing the stuff to build legato
1. install the cross build toolchain in /opt/swi
2. build the target legato system - this gives the legato specific build tools + the libs etc 

## STEP 1 - Install the Legato cross build toolchain

Download the toolchain from the source->  product -> Firmware page

Then follow the instructions in legato.io - roughly like this 
* make sure to carefully follow the instructions
* watch out it's likely that the toolchain you have is a different name to the legato.io documentation

```
. /opt/swi/SWI9X06Y_02.18.05.00/environment-setup-armv7a-neon-poky-linux-gnueabi

export PATH=/opt/SWI9X06Y_02.18.05.00/sysroots/x86_64-pokysdk-linux/usr/bin/arm-poky-linux-gnueabi:$PATH

cd /opt/swi/SWI9X06Y_02.18.05.00/sysroots/armv7a-neon-poky-linux-gnueabi/usr/src/kernel
```


```
$ sudo chown -R $USER .
$ ARCH=arm CROSS_COMPILE=arm-poky-linux-gnueabi- make scripts
$ sudo chown -R root .
```


## STEP2 - Build the legato system and image
Download the Tarball and extract it to a directory on your local machine
```
$ mv ~/Downloads/legato-17.11.0.tar.bz2 legatoAF/
$ cd legatoAF/
$ tar -xvf legato-17.11.0.tar.bz2
```
The bit the documentation forgets to mention is that 'make' is required to make the bin directory appear !!!  
tried 

**Build the tools**  
```
make wp85
```
./bin appeared

then
```
make wp77xx
```
this worked   !!!

**Set the environment to pick up the correct cross tools etc** 

then
```
source ./bin/configlegatoenv
```
**Cross build the legato image**  
   
Then
```
mksys -t wp77xx default.sdef
```

**Build output**
There are two core build outputs - .update files and .cwe files  
1. .update go into the overlay and can be rolled back etc
1. .cwe files replace the existing image and cannot be rolled back

The following appear following a successful mksys - in folder ./build/wp77xx  

*These files are loadable onto the target with*  

* From windows - fd2.exe or   
* Target command line - fwupdate or  
* Host command line - fwupdate  

*The .cwe files*  
```
legato.cwe
legato_rw.cwe
legato-squashfs.ubi.cwe
```

*These files are loadable onto the target with*  
* Target command line - update  
* Host command line - update  
  
*The .update files*  
```
system.wp77xx.update
```



