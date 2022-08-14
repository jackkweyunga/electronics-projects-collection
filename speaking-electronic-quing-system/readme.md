# SPEAKING ELECTRONICS QUEUING SYSTEM.

Speaking electronic queuing system speaks the number in the queue, it can be used to control the queue in hospitals, restaurants and other places calling people in the queue.

<p align="center"><img src="./speaking -electronic-quing-system\images\project image.png" alt="Project image"/></p>

## Credits

All credits goes to [Uteh Str](https://youtu.be/656rrJu7ezs)

## What you will need.

| NAME                                         | QTY |
| -------------------------------------------- | --- |
| Arduino UNO board.                           | 1   |
| Serial MP3 Player Module                     | 1   |
| Micro SD Card                                | 1   |
| P10 LED Panel                                | 1   |
| LED 16 x 2                                   | 1   |
| Breadboard                                   | 1   |
| Male to Male and Make to Female jumper wires | 30  |
| Trimpot / variable resistor (100K)           | 1   |
| Headphone / Speaker                          | 1   |

## Schematics

<p align="center"><img src="./speaking -electronic-quing-system\images\project-schematics.png" alt="project schematics"/></p>

## Programming Arduino for speaking electronic queuing system

> <p>The program will require the installation of the required libraries (link at the end of the readMe), then configuration of the P10 module, LCD 16x2 configuration, seral MP3 player module configuration and DMD configuration</p>

### A brief description of the playback code for the mp3 file

> <p>This is the command to play  mp3 files with specific files and folders</p>
> <table border="1" cellspacing="1" cellpadding="0"><tr><td>7E FF 06 0F 00 01 01 EF</td><td>Play the song with the directory /01/001xxx.mp3</td></tr><tr><td>7E FF 06 0F 00 01 02 EF</td><td>Play the song with the directory /01/002xxx.mp3</td></tr></table>
> <p>This project will use two folders inside the micro SD card 01 (intros) and 02 (numbers), the folders should be named 01 and 02 not with the given names in this repository, they are just for understanding!</p>
> <p>In folder 01 there are two files '001 Bell' sound and '002 Number', so to play mp3 files in "01" folder with the name "01 Bell sound" the code is like this:</p>

```
    sendCOMMAND(CMD_PLAY_FOLDER_FILE, 1, 1);
```

### Button description
1. Forward button
><p>short press to display the next queue number. Long press to display the next queue number, the queue number will continue forward until the button is released</p>
<p align="center"><img src="./speaking -electronic-quing-system\images\button forward.png" alt="button forward"/></p>

2. Replay button
><p>short press to repeat calling the queue number. Long press to return the queue number to 0</p>
<p align="center"><img src="./speaking -electronic-quing-system\images\button replay.png" alt="button replay"/></p>

3. Previous button
><p>short press to display the previous queue number. Long press to display the previous queue number, the queue number will continue backward until the button is released</p>
<p align="center"><img src="./speaking -electronic-quing-system\images\button previous.png" alt="button replay"/></p>

### The EEPROM
><p>Until this point, the queue number will return to "00" if there is loss of power, unstable power and so on.</p>
><p>To overcome that, the queue number data will be stored in the EEPROM. But for implementation, its not recommended using internal arduino EEPROM, use external EEPROM or Data Logger.</p>
><p>The demonstration video of both the code with EEPROM and without EEPROM will be shown below.</p>

## Video
[![Watch the video for queuing system here!](./speaking%20-electronic-quing-system/images/project%20image.png)](https://youtu.be/656rrJu7ezs)

## Libraries

 1. Freetronics dot matrix display library 
 [https://github.com/freetronics/DMD](https://github.com/freetronics/DMD)

 2. TimerOne Library: Use with Freetronics dot matrix display library to configure 16bits hardware timer
 [http://code.google.com/p/arduino-timerone/downloads/list](http://code.google.com/p/arduino-timerone/downloads/list)

 3. LCD Monitor Library: Arduino LiquidCrystal driver based on the Hitachi HD44780
 [https://github.com/adafruit/LiquidCrystal](https://github.com/adafruit/LiquidCrystal)