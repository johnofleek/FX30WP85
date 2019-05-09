# Had a problem with a WP77xx 1 click installer
The device had a broken image loaded but would go into boot mode and in windows had a visible "DM" serial port  


The installer failed like this
```
Device error code: 0x0 - Unknown device error code.

Preexisting images information:
        Current:
                Firmware:
                        ImageId:
                        BuildId:
                Configuration:
                        ImageId:
                        BuildId:
Final images information:
        Current:
                Firmware:
                        ImageId:
                        BuildId:
                Configuration:
                        ImageId:
                        BuildId:
```


# Workaround
1. Uncompress the 1 click .exe (with izarc)
1. Run up a windows power shell
1. Execute the installer with the new image
1.1 ./fdt2.exe WP77xx_Release9.1_PTCRB_GCF_SPK.spk


