#(after following instructions below)

## Environment setup 
So command line builds work such as $CC is set

```
$ . /opt/swi/SWI9X06Y_02.18.05.00/environment-setup-armv7a-neon-poky-linux-gnueabi
$ echo $CC
arm-poky-linux-gnueabi-gcc -march=armv7-a -mfpu=neon -mfloat-abi=softfp --sysroot=/opt/swi/SWI9X06Y_02.18.05.00/sysroots/armv7a-neon-poky-linux-gnueabi

```

# Install the toolchain

Download the toolchain from the source->  product -> Firmware page

Then follow the instructions in legato.io - roughly like this

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


## legato
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
