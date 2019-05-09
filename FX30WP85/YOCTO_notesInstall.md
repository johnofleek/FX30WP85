# Building yocto image for FX30WP85


Try with 60Gb drive space
## -- might need this
```
sudo dpkg-reconfigure dash
```

## - install the toolchain
and  

Create a soft link from the versioned folder to /y17-ext (delete the existing soft link if needed)
```
$ cd /opt/swi
$ rm y-17-ext
$ sudo ln -s y17-ext-fx30 y17-ext
```

## -- extract the base system yocto 

Get then from source.sierrawireless.com
```
tar -xvf FX30_WP8548_full_R14.0.4.002.tar.gz
```
In the root of the above project

```
tar -xvf legato-16.10.1.m3.tar.bz2
```

## install  these puppies

makeinfo
gawk
chrpath
sdl-config


## edit this junk
Known Issues:
When building the Source code package, a build error occurs:
error “cat: modules/Columbia/apps/columbiaAtServiceComponent/columbiaAtService.c: No such file or directory”


To resolve this:
/home/john/FX30/workspace/meta-columbia-x/meta-columbia-x-app/recipes/legato-af

Edit the file            meta-columbia-x / meta-columbia-x-app/recipes/legato-af/legato-af_git.bbappend 

and remove the entire “do_compile_append” function.

>>>
except "do_compile_append” doesn't exist in the file but the following function does exist
```
do_compile_prepend() {
    COLUMBIA_FILE=modules/Columbia/apps/columbiaAtServiceComponent/columbiaAtService.c

    GEN_DATE=$(date -u)

    cat ${COLUMBIA_FILE} | sed "1 s/^.*$/char date[]=\"$GEN_DATE\";/" \
                           > ${COLUMBIA_FILE}_tmp
    mv ${COLUMBIA_FILE}_tmp ${COLUMBIA_FILE}

}
```


