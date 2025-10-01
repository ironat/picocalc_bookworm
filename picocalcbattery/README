A LXpanel plugin which displays hostname in Panel.
This is written for Raspbian but should work on any Linux using LXpanel.

To install plugin on the Raspberry Pi run either (32 bit)

	sudo cp hostname.so /usr/lib/arm-linux-gnueabihf/lxpanel/plugins/hostname.so

or (64 bit)

    sudo cp hostname64.so /usr/lib/aarch64-linux-gnu/lxpanel/plugins/hostname.so

Either restart or run `lxpanelctl restart` to make LXDE aware it is installed.

To compile from source

	sudo apt install lxpanel-dev
	gcc -Wall `pkg-config --cflags gtk+-2.0 lxpanel` -shared -fPIC hostname.c -o hostname.so `pkg-config --libs lxpanel`

For Raspberry Pi OS-Bullseye (with GTK3)
	gcc -Wall `pkg-config --cflags gtk+-3.0 lxpanel` -shared -fPIC hostname.c -o hostname.so `pkg-config --libs lxpanel`

The source and compiled versions `Raspberry Pi OS-Buster` (GTK2 or earlier) `Raspberry Pi OS-Bullseye` 32 or 64 bit can be downloaded [Hostname](http://binnie.id.au/Downloads/hostname.tgz)

`tar tzf hostname.tgz`	list
