# turboAVR
A cool utility that allows your AVR codes to be loaded quickly on Windows. Currently only supports the Il Matto board from the University of Southampton. 
More information about the Il Matto Board: https://www.ecs.soton.ac.uk/outreach/kits/micro-arcana-series 

To use, put it in the same folder as your project, and then use it by calling "turboAVR yourcode.c" on CMD. Currently doesn't support external libraries. 

# Mac Users

To use, you must first install avrdude

```brew install avrdude```

If you have driver issues, try running the following:

```brew install cmake pkg-config hidapi libftdi libusb libusb-compat libelf libserialport```
