
https://forum.legato.io/t/python-receipts-in-legato/2356 suggests adding IMAGE_INSTALL statements to mdm9x15-image.inc  

In the FX30 yocto image I found this:  

/home/john/FX30/workspace/meta-swi/meta-swi-mdm9x15/recipes-core/images/mdm9x15-image.inc

The odd thing is that python us already installed on the target - where did it come from?


# Current changes

```
# Add WiFi TI drivers, tools, and scripts
# JT
# IMAGE_INSTALL += "ti-compat-wireless"
# IMAGE_INSTALL += "sierra-init-tiwifi"

# JT
IMAGE_INSTALL += "python-pickle"

```

After this I tried a lot more - adding them all gives

```
 size of the image file "/home/john/FX30/workspace/build_bin/tmp/deploy/images/swi-mdm9x15/mdm9x15-image-minimal-swi-mdm9x15-20190416140704.rootfs.squashfs" is 55590912, 

which is larger than volume size 33554432
```

So after this I cut it down to
```
# JT
#IMAGE_INSTALL += "python-ptest"
IMAGE_INSTALL += "libpython2"
#IMAGE_INSTALL += "python-dbg"
IMAGE_INSTALL += "python-2to3"
#IMAGE_INSTALL += "python-audio"
#IMAGE_INSTALL += "python-bsddb"
IMAGE_INSTALL += "python-codecs"
IMAGE_INSTALL += "python-compile"
IMAGE_INSTALL += "python-compiler"
IMAGE_INSTALL += "python-compression"
IMAGE_INSTALL += "python-core"
IMAGE_INSTALL += "python-crypt"
IMAGE_INSTALL += "python-ctypes"
IMAGE_INSTALL += "python-curses"
IMAGE_INSTALL += "python-datetime"
IMAGE_INSTALL += "python-db"
#IMAGE_INSTALL += "python-debugger"
#IMAGE_INSTALL += "python-dev"
#IMAGE_INSTALL += "python-difflib"
#IMAGE_INSTALL += "python-distutils-staticdev"
#IMAGE_INSTALL += "python-distutils"
#IMAGE_INSTALL += "python-doctest"
#IMAGE_INSTALL += "python-elementtree"
IMAGE_INSTALL += "python-email"
IMAGE_INSTALL += "python-fcntl"
#IMAGE_INSTALL += "python-gdbm"
#IMAGE_INSTALL += "python-hotshot"
#IMAGE_INSTALL += "python-html"
IMAGE_INSTALL += "python-idle"
#IMAGE_INSTALL += "python-image"
IMAGE_INSTALL += "python-importlib"
IMAGE_INSTALL += "python-io"
IMAGE_INSTALL += "python-json"
#IMAGE_INSTALL += "python-lang"
IMAGE_INSTALL += "python-logging"
#IMAGE_INSTALL += "python-mailbox"
IMAGE_INSTALL += "python-math"
IMAGE_INSTALL += "python-mime"
#IMAGE_INSTALL += "python-mmap"
IMAGE_INSTALL += "python-multiprocessing"
#IMAGE_INSTALL += "python-netclient"
#IMAGE_INSTALL += "python-netserver"
IMAGE_INSTALL += "python-numbers"
IMAGE_INSTALL += "python-pickle"
#IMAGE_INSTALL += "python-pkgutil"
#IMAGE_INSTALL += "python-pprint"
#IMAGE_INSTALL += "python-profile"
#IMAGE_INSTALL += "python-pydoc"
IMAGE_INSTALL += "python-re"
IMAGE_INSTALL += "python-readline"
IMAGE_INSTALL += "python-resource"
#IMAGE_INSTALL += "python-robotparser"
#IMAGE_INSTALL += "python-shell"
IMAGE_INSTALL += "python-smtpd"
IMAGE_INSTALL += "python-sqlite3"
#IMAGE_INSTALL += "python-sqlite3-tests"
#IMAGE_INSTALL += "python-stringold"
IMAGE_INSTALL += "python-subprocess"
IMAGE_INSTALL += "python-syslog"
#IMAGE_INSTALL += "python-terminal"
#IMAGE_INSTALL += "python-tests"
#IMAGE_INSTALL += "python-textutils"
IMAGE_INSTALL += "python-threading"
#IMAGE_INSTALL += "python-tkinter"
#IMAGE_INSTALL += "python-unittest"
#IMAGE_INSTALL += "python-unixadmin"
#IMAGE_INSTALL += "python-xml"
#IMAGE_INSTALL += "python-xmlrpc"
#IMAGE_INSTALL += "python-zlib"
IMAGE_INSTALL += "python-modules"
IMAGE_INSTALL += "python-misc"
#IMAGE_INSTALL += "python-man"
``` 


Yocto - from "workspace"
```
make 
```


Try a 

```
cd /home/john/FX30/workspace/legato/
source ./bin/configlegatoenv

instlegato wp85 192.168.2.2
````

Which works - but only changes the legato part not the OS etc and I suspect just overwrites the overlay


From
https://docs.legato.io/16_10/yoctoLegatoOverview.html files are here

```
/home/john/FX30/workspace/build_bin/tmp/deploy/images/swi-mdm9x15
```

 but then the question is which built file contains the targets filesystem image with the above mentioned "pickle" code?

I think in this case we need - a 28Mb file
```
yocto-legato_wp85.cwe		package with yocto (= kernel + rootfs) + legato

```

And now I need a way to flash it onto the FX30

Thanks to David

The difference between fwupdate and swiflash is:  
*fwupdate* (host script) works over an SSH connection, to provision the file and call the fwupdate (embedded tool) to apply the update from the Linux land.  

*swiflash* works at a lower level, requiring a physical USB connection to the device, and is able to perform download even if linux or legato is not running correctly on the device
(designed for recovery use cases)  

Like this
https://docs.legato.io/18_02/toolsHost_fwupdate.html

```
-- doesn't have -fwupdate downloadOnly yocto-legato_wp85.cwe 192.168.2.2

-- doesn't have -fwupdate install 192.168.2.2

-- doesn't have -fwupdate markGood 192.168.2.2


fwupdate download yocto-legato_wp85.cwe 192.168.2.2

fwupdate query 192.168.2.2

```


## have a go at using bitbake to find what is available

. ./poky/oe-init-build-env
```
bitbake -e python | grep ^PACKAGES=
PACKAGES="python-ptest libpython2 python-dbg python-2to3 python-audio python-bsddb python-codecs python-compile python-compiler python-compression python-core python-crypt python-ctypes python-curses python-datetime python-db python-debugger python-dev python-difflib python-distutils-staticdev python-distutils python-doctest python-elementtree python-email python-fcntl python-gdbm python-hotshot python-html python-idle python-image python-importlib python-io python-json python-lang python-logging python-mailbox python-math python-mime python-mmap python-multiprocessing python-netclient python-netserver python-numbers python-pickle python-pkgutil python-pprint python-profile python-pydoc python-re python-readline python-resource python-robotparser python-shell python-smtpd python-sqlite3 python-sqlite3-tests python-stringold python-subprocess python-syslog python-terminal python-tests python-textutils python-threading python-tkinter python-unittest python-unixadmin python-xml python-xmlrpc python-zlib python-modules python-misc python-man"
```












