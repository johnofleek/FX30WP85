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
This relies on the Legato\bin existing

```
source ./bin/configlegatoenv
```


# Install the Legato cross build toolchain

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


## Build legato system
Download the Tarball and extract it to a directory on your local machine
```
$ mv ~/Downloads/legato-17.11.0.tar.bz2 legatoAF/
$ cd legatoAF/
$ tar -xvf legato-17.11.0.tar.bz2
```
The bit they forgot is that make is required to make the bin directory appear ***
tried 

```
make wp85
```
./bin appeared

then
```
make wp77xx
```

this worked   
then
```
source ./bin/configlegatoenv
```

Then
```
mksys -t wp77xx default.sdef
```
