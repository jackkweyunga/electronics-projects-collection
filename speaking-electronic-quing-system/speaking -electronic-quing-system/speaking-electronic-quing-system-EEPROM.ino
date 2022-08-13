// The SPI, DMD, TimerOne, Font and EEPROM libraries are used.
#include <SPI.h>       
#include <DMD.h>    
#include <TimerOne.h>  
#include "SystemFont5x7.h"
#include <LiquidCrystal.h>
#include <EEPROM.h>

// P10 Configuration
#define DISPLAYS_ACROSS 1 //-> Number of P10 panels used, side to side.
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN); 


// LCD 16X2 Configuration
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //-> LiquidCrystal lcd(RS, E, D4, D5, D6, D7);


// The byte commands are based on the table contained in the MP3 Player Module Document.
#define CMD_SEL_DEV           0X09    //-> Select device.
#define DEV_TF                0X02    //-> 02 for TF card.
// Select device : 7E FF 06 09 00 00 02 EF -> Select storage device to TF card.

#define CMD_PLAY_FOLDER_FILE  0X0F    //-> Play with folder and file name.
// Play with folder and file name : 7E FF 06 0F 00 01 01 EF -> Play the song with the directory: /01/001xxx.mp3
// Play with folder and file name : 7E FF 06 0F 00 01 02 EF -> Play the song with the directory: /01/002xxx.mp3

#define CMD_SET_VOLUME        0X06    //-> Set volume.
// Set volume : 7E FF 06 06 00 00 1E EF -> Set the volume to 30 (0x1E is 30) (Set volume is 06).


static int8_t Send_buf[8] = {0}; //-> Buffer to send commands. 

int Queue_number=0; //-> Queue Number Variable

int btn_Repeat, btn_Prev, btn_Next; //-> Variable for buttons control 
int count_btn_Prev=0; //-> Indicator variable for short press or long press on the btn_Prev.
int count_btn_Next=0; //-> Indicator variables for short press or long press on the btn_Next.
int count_btn_Repeat=0; //-> Indicator variables for short press or long press on the btn_Repeat.

char Qn [3]; //-> Variable to display the queue number
String str_Qn; //-> Variable to hold the queue number data


// ScanDMD()
void ScanDMD() { 
  dmd.scanDisplayBySPI();
}


// setup()
void setup() {
  
  
  // Configure pin 5,4 and 3 as input and enable the internal pull-up resistor.
  pinMode(5, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  Serial.begin(9600);
  delay(100);

  Timer1.initialize(5000);          
  Timer1.attachInterrupt(ScanDMD);   
  dmd.clearScreen(true);  
  dmd.selectFont(SystemFont5x7);
  delay(100);

  sendCommand(CMD_SEL_DEV, 0, DEV_TF);
  delay(500);
  sendCommand(CMD_SET_VOLUME, 0, 30);
  delay(500);

  // Syntax : EEPROM.write(address, value) 
  EEPROM.write(0, Queue_number); //-> Activate this code for the first time, then deactivate it.
  // Syntax : EEPROM.read(address) 
  Queue_number = EEPROM.read(0);
  delay(100);
  
  lcd.begin(16, 2);
  display_QN();
}

// loop()
void loop() {

  read_button();

  //  Conditions for Repeat.
  if (btn_Repeat==LOW) {
    delay(500);
    count_btn_Repeat++;
  }

  if (count_btn_Repeat==1 && btn_Repeat==HIGH) { //-> Short press to repeat calling the queue number.
    if (Queue_number!=0) {
      Bell_sound();
    }

    count_btn_Repeat=0;
  }

  if (count_btn_Repeat>1 && btn_Repeat==LOW) { //-> Long press to return queue number to 0.
    while(1) {
      read_button();
      if (btn_Repeat==LOW) {
        Queue_number=0;

        display_QN();
      }
      else {
        write_EEPROM();
        count_btn_Repeat=0;
        return;   
      }
      delay(500);
    }
  }

  // Conditions for Previous queue number.
  if (btn_Prev==LOW) {
    delay(500);
    count_btn_Prev++;
  }

  if (count_btn_Prev==1 && btn_Prev==HIGH) { //-> Short press to display the previous queue number.
    Queue_number--;

    if (Queue_number<0) {
      Queue_number=60;
    }

    write_EEPROM();
    count_btn_Prev=0;
    Bell_sound();
  }
  if (count_btn_Prev>1 && btn_Prev==LOW) { //-> Long press to display the previous queue number, the queue number will continue backward until the button is released.
    while(1) {
      read_button();
      if (btn_Prev==LOW) {
        Queue_number--;

        if (Queue_number<0) {
          Queue_number=60;
        }

        display_QN();
      }
      else {
        write_EEPROM();
        count_btn_Prev=0;
        Bell_sound();
        return;   
      }
      delay(500);
    }
  }
  
  // Conditions for Next queue number.
  if (btn_Next==LOW) {
    delay(500);
    count_btn_Next++;
  }

  if (count_btn_Next==1 && btn_Next==HIGH) { //-> Short press to display the next queue number.
    Queue_number++;

    if (Queue_number>60) {
      Queue_number=0;
    }

    write_EEPROM();
    count_btn_Next=0;
    Bell_sound();
  }
  if (count_btn_Next>1 && btn_Next==LOW) { //-> Long press to display the next queue number, the queue number will continue forward until the button is released.
    while(1) {
      read_button();
      if (btn_Next==LOW) {
        Queue_number++;

        if (Queue_number>60) {
          Queue_number=0;
        }

        display_QN();
      }
      else {
        write_EEPROM();
        count_btn_Next=0;
        Bell_sound();
        return;   
      }
      delay(500);
    }
  }

  delay(100);
}

// read_button()
void read_button() {
  btn_Next = digitalRead(5);
  btn_Repeat = digitalRead(4);
  btn_Prev = digitalRead(3);
}

// write_EEPROM()
// Write queue number into EEPROM.
void write_EEPROM() {
  EEPROM.write(0, Queue_number);
}

// display_QN()
// Subroutine to display queue numbers on panel P10 and LCD 16x2.
void display_QN() {  
  dmd.drawString(1, 0, "QUEUE", 5, GRAPHICS_NORMAL);
  dmd.drawString(1, 9, "NO", 2, GRAPHICS_NORMAL);
  dmd.drawString(13, 9, ":", 1, GRAPHICS_NORMAL);

  str_Qn = String(Queue_number);
  str_Qn.toCharArray(Qn,3);

  lcd.setCursor(0,0);             
  lcd.print("  QUEUE NUMBER  ");
  
  if (Queue_number<10) {
    dmd.drawString(19, 9, "0", 1, GRAPHICS_NORMAL);
    dmd.drawString(25, 9, Qn, 1, GRAPHICS_NORMAL);

    lcd.setCursor(7, 1);
    lcd.print("0");
    lcd.print(Queue_number);
  }
  else {
    dmd.drawString(19, 9, Qn, 2, GRAPHICS_NORMAL);

    lcd.setCursor(7, 1);
    lcd.print(Queue_number);
  }
}

// Bell_sound()
// Subroutine to play bell sound and enter the next subroutine.
void Bell_sound() {  
  if (Queue_number!=0) {
    display_QN();
    sendCommand(CMD_PLAY_FOLDER_FILE, 1, 1);
    delay(4000);
    Queue_number_process();
  }
  else {
    display_QN(); 
  }
}

// Queue_number_process()
// Subroutines to play "number" sound and "queue number" sound based on predetermined conditions.
void Queue_number_process() {  
  // Conditions for queue numbers from 0 to 20.
  if (Queue_number>0 && Queue_number<=20) {
    sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
    delay(1000);
    sendCommand(CMD_PLAY_FOLDER_FILE, 2, Queue_number);
    delay(1000);
  }
  
  // Conditions for queue numbers from 21 to 29.
  if (Queue_number>20 && Queue_number<30) {
    int suffix_20 = Queue_number - 20;

    sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
    delay(1000);
    sendCommand(CMD_PLAY_FOLDER_FILE, 2, 20);
    delay(1000);
    sendCommand(CMD_PLAY_FOLDER_FILE, 2, suffix_20);
    delay(500);
  }

  // Conditions for queue numbers from 30 to 39.
  if (Queue_number>=30 && Queue_number<40) {
    int suffix_30 = Queue_number - 30;

    if (Queue_number==30) {
      sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, 30);
      delay(1000);
    }
    else {
      sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, 30);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, suffix_30);
      delay(500);
    }
  }

  // Conditions for queue numbers from 40 to 49.
  if (Queue_number>=40 && Queue_number<50) {
    int suffix_40 = Queue_number - 40;

    if (Queue_number==40) {
      sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, 40);
      delay(1000);
    }
    else {
      sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, 40);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, suffix_40);
      delay(500);
    }
  }

  // Conditions for queue numbers from 50 to 59.
  if (Queue_number>=50 && Queue_number<60) {
    int suffix_50 = Queue_number - 50;

    if (Queue_number==50) {
      sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, 50);
      delay(1000);
    }
    else {
      sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, 50);
      delay(1000);
      sendCommand(CMD_PLAY_FOLDER_FILE, 2, suffix_50);
      delay(500);
    }
  }

  // Conditions for queue number 60.
  if (Queue_number==60) {
    sendCommand(CMD_PLAY_FOLDER_FILE, 1, 2);
    delay(1000);
    sendCommand(CMD_PLAY_FOLDER_FILE, 2, 60);
    delay(1000);
  }
}

// sendCommand
// Function for sending commands.
void sendCommand(byte command){
  sendCommand(command, 0, 0);
}

void sendCommand(byte command, byte dat1, byte dat2){
  delay(20);
  Send_buf[0] = 0x7E;    //-> Every command should start with $(0x7E)
  Send_buf[1] = 0xFF;    //-> Version information
  Send_buf[2] = 0x06;    //-> The number of bytes of the command without starting byte and ending byte
  Send_buf[3] = command; //-> Such as PLAY and PAUSE and so on
  Send_buf[4] = 0x00;    //-> 0x00 = not feedback, 0x01 = feedback
  Send_buf[5] = dat1;    //-> data1
  Send_buf[6] = dat2;    //-> data2
  Send_buf[7] = 0xEF;    //-> Ending byte of the command
  
  for (uint8_t i = 0; i < 8; i++){
    Serial.write(Send_buf[i]);
  }
}