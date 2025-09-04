This poject allows to install bookworm and use it on the Picocalc with the Zero Mod.

This project uses partly the https://github.com/wasdwasd0105/picocalc-pi-zero-2 project.

Follow his keyboard setup and audio setup but not the display part!

Remember you must but the dtoverlay for the keyboard in the /boot/firmware/config.txt. The script put it into the /boot/config.txt
```
dtparam=i2c_arm=on
dtoverlay=picocalc_kbd
```


Do compile the overlay for the display

```
git clone https://github.com/ironat/picocalc_bookworm
cd picocalc_bookworm
dtc -I dts -O dtb -o picodisplay.dtbo picodisplay.dts
sudo cp picodisplay.dtbo /boot/overlays/.
```
Update /boot/firmware/config.txt

```
# For more options and information see
# http://rptl.io/configtxt
# Some settings may impact device functionality. See link above for details

# Uncomment some or all of these to enable the optional hardware interfaces
#FOR KEYBOARD
dtparam=i2c_arm=on
dtoverlay=picocalc_kbd

#dtparam=i2s=on

# FOR DISPLAY
dtparam=spi=on

# Enable audio (loads snd_bcm2835)
# FOR AUDIO
dtparam=audio=on
dtoverlay=audremap,pins_12_13

# Additional overlays and parameters are documented
# /boot/firmware/overlays/README

# Automatically load overlays for detected cameras
camera_auto_detect=1

# Automatically load overlays for detected DSI displays
display_auto_detect=1

#FOR DISPLAY
#Display
dtoverlay=spi0-1cs
dtoverlay=picodisplay

# Automatically load initramfs files, if found
auto_initramfs=1

# Enable DRM VC4 V3D driver
dtoverlay=vc4-kms-v3d
max_framebuffers=2

# Don't have the firmware create an initial video= setting in cmdline.txt.
# Use the kernel's default instead.
disable_fw_kms_setup=1

# Disable compensation for displays with overscan
disable_overscan=1

# Run as fast as firmware / board allows
arm_boost=1

[cm4]
# Enable host mode on the 2711 built-in XHCI USB controller.
# This line should be removed if the legacy DWC2 controller is required
# (e.g. for USB device mode) or if USB support is not required.
otg_mode=1

[cm5]
dtoverlay=dwc2,dr_mode=host

[all]
```





