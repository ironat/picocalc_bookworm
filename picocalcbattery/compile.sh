
#!/bin/bash
gcc -Wall $(pkg-config --cflags gtk+-2.0 lxpanel) -shared -fPIC picocalcbattery.c -o picocalcbattery.so $(pkg-config --libs --cflags lxpanel)
