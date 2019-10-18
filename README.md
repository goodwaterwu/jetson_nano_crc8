jetson_nano_crc8
C code for calculating CRC8 of Jetson Nano EEPROM

Installation:

$ make

$ make install

If you'd like to change default install path, please use

$ make install DESTDIR=<install_path>

If you'd like to do cross compiling, please export the toolchain path
to PATH, and set CROSS_COMPILE and ARCH.

<pre>Usage: crc8 [options]
	-f &lt;file>	file name
	-n &lt;size>	maximum size to be calculated
	-h		show this help</pre>
![result](https://github.com/goodwaterwu/jetson_nano_crc8/blob/master/readme.png)
