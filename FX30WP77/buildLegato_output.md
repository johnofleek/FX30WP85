## Legato mksys build output files 

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
