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
1. Execute the installer (fdt2.exe) with the new image (WP77xx_Release9.1_PTCRB_GCF_SPK.spk)  

For example execute   in power shell
./fdt2.exe WP77xx_Release9.1_PTCRB_GCF_SPK.spk  

or

```
PS C:\Users\john\OneDrive\Documents\WP77xx\WP77xx_Release9.1_PTCRB_GCF_MOD> .\fdt2.exe yocto_wp77xx.4k.cwe
FDT version: 1.0.1806.0
Awaiting suitable port or adapter ...
Switching to boot & hold mode ...
Disabling selective suspend ...
Awaiting download port ...
Switching to streaming mode ...
Downloading images ...
Writing image -
Flashing image /
Awaiting adapter ...
Checking update status ...
Enabling selective suspend ...
Firmware image download succeeded.
Final Firmware update succeeded.

Preexisting images information:
        Current:
                Firmware:
                        ImageId: 001.028_001
                        BuildId: 02.16.06.00_GENERIC
                Configuration:
                        ImageId: 001.028_001
                        BuildId: 02.16.06.00_GENERIC
Final images information:
        Current:
                Firmware:
                        ImageId: 001.028_001
                        BuildId: 02.16.06.00_GENERIC
                Configuration:
                        ImageId: 001.028_001
                        BuildId: 02.16.06.00_GENERIC

OEM PRI: 9907365 001.004

IMEI: 352653090128562

Total time elapsed: 86157 ms.

Time to switch to boot mode: 20594 ms.

Images downloaded:
        Image ID:
        Build ID:
                write time: 14547 ms
                additional flash time: 5110 ms

Time to reset to application mode: 45438 ms.
```




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
