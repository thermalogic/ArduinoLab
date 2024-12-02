# Arduino under Ubuntu 

**Arduino IDE 1.8.9**

* Linux https://www.arduino.cc/en/Guide/Linux

```bash
sudo apt install arduino
```

**Arduino IDE 2**

* https://docs.arduino.cc/software/ide-v2/tutorials/getting-started/ide-v2-downloading-and-installing/

1. Download Arduino IDE2 AppImage and make it executable

   * https://www.arduino.cc/en/software

```bash
chmod a+x arduino-ide_2.3.3_Linux_64bit.AppImage
```

2.  Create a directory with the same name as the AppImage plus the ".config" extension
  in the same directory as the AppImage
```bash
mkdir arduino-ide_2.3.3_Linux_64bit.AppImage.config
```
3. Run Arduino IDE2

```bash
./arduino-ide_2.3.3_Linux_64bit.AppImage --no-sandbox
```

必须加：--no-sandbox，不然，会运行错误

Arduino IDE 2目前是AppImageKit打包的可运行文件，可用性较差

* **AppImageKit** https://github.com/AppImage/AppImageKit

##  使用serial port 

To enable the Arduino IDE to access the serial port and upload code to your board, the following rule can be added to

```bash
sudo nano /etc/udev/rules.d/99-arduino.rules
```

```bash
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", GROUP="plugdev", MODE="0666"
```




