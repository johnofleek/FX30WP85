# Had a problem with a WP77xx 1 click installer
The device had a broken image loaded but would go into boot mode    
In windows had a visible "DM" serial port  


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


## Workaround
1. Uncompress the 1 click .exe (with izarc)
1. Run up a windows power shell
1. Execute the installer with the new image
1.1 ./fdt2.exe WP77xx_Release9.1_PTCRB_GCF_SPK.spk


# Had a problem with EM7xxx 1 click installer
The device didn't go into boot mode when the installer was run

```
FDT version: 5.1.1509.0
Checking modem mode ...
Disabling selective suspend ...
Switching device to boot & hold mode ...

Firmware download failed.
Primary error code: 51 - Failed to switch device to BOOT&HOLD mode.
Secondary error code: 201 - Failed to switch device to QDL mode.
Device error code: 0x0 - Unknown device error code.
Total time elapsed: 1250 ms.
Press Enter to continue ...
```

## Workaround
Use AT command to manually force the module into boot mode
