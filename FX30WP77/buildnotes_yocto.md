
# seems useful

https://forum.sierrawireless.com/t/wp7702-and-yocto/14612/4  

in particular this file link   

meta-swi-extras/meta-swi-mdm9x28/recipes/images/mdm9x28-sierra-image.inc

# Fix not enough space to add full python libs via yocto

## Plan A - rootfs size Pt1 - failed

**It turns out that it is not possible to change the size of the roots**
Ran into this issue when adding a lot of python modules - this worked with the WP85 image

ubinize: error!: error in section "sysfs_volume": size of the image file 
"/home/john/FX30/workspace/build_bin/tmp/deploy/images/swi-mdm9x28-wp/mdm9x28-image-minimal-swi-mdm9x28-wp-20190507083900.rootfs.2k.ubifs"
is 50790400, which is larger than volume size 39845888

**Got this from SW**  

https://forum.sierrawireless.com/t/wp76xx-yocto-increase-filesystem-size/16318  

essentially  

```
./meta-swi/meta-swi-mdm9x28/conf/machine/swi-mdm9x28.conf	
change UBI_ROOTFS_SIZE ?= “48MiB”
```

Which did build ok  
But failed to flash on the device as the WP77 rootfs is fixed size - according to deadpoolcode  


## Plan B - rootfs - delete perl - failed perl is essential part of Debian
Plan B is to reduce the space usage by removing parts of the system
*First attempt remove perl*
 
Try something like in  
/home/john/FX30/workspace/meta-swi/common/classes/swi-image-initramfs.bbclass  
has  
PACKAGE_EXCLUDE += "busybox-syslog busybox-udhcpc"  

Maybe  

PACKAGE_EXCLUDE += "perl"  

## this is a useful doc
README.build.wp76.md
and this
https://www.yoctoproject.org/docs/2.7/overview-manual/overview-manual.html  

1. Files that have the .bb suffix are "recipes" files
1. Class files (.bbclass) contain information that is useful to share between recipes files
1. The configuration files (.conf) define various configuration variables that govern the OpenEmbedded build process

## final steps
4.3.5.5. Image Generation¶  

do_generate_cwe  

# Plan C - modify image build .inc to make everything fit 

This file seems to be current one to edit
```
/home/john/FX30/workspace/meta-swi/meta-swi-mdm9x28/recipes-core/images/mdm9x28-image.inc
```

Removed the wifi and other stuff - I guess we need i2cgpioctl though
```
# Add WiFi tools and scripts
# JT - remove wifi
# IMAGE_INSTALL_append = " wpa-supplicant"
# IMAGE_INSTALL_append = " hostapd"
# IMAGE_INSTALL_append = " iw"
# IMAGE_INSTALL_append = " ti-wifi-utils-wl18xx"
# IMAGE_INSTALL_append = " crda"
# IMAGE_INSTALL_append = " i2cgpioctl"
# IMAGE_INSTALL_append = " sierra-init-tiwifi"
# end JT
```

See local .inc file for finished working 

```
/home/john/FX30/workspace/meta-swi/meta-swi-mdm9x28/recipes-core/images/mdm9x28-image.inc
```







