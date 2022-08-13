/* SMS LOGGER */

/* LIBRARIES */
#include <Wire.h>
#include <SoftwareSerial.h>
#include <String.h>

/* LIBRARIES INITIALIZATIONS */
SoftwareSerial gprsSerial(7,8); // RX TX

// constants
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)

String number="";
String msg="";
String instr="";
int i=0,temp=0;
int rec_read=0;
int temp1=0;

void setup()
{

    gprsSerial.begin(9600); 
    Serial.begin(9600);

}


void loop()
{

    delay(1000);

    if(gprsSerial.available())
    {
        instr = gprsSerial.readString();

        if(instr.indexOf("\n+CMT: \"")>=0)
        {
            sms_flag=1;
        }

        if(sms_flag==1) // received sms
        {

            debugln(instr);
      
            from = instr.substring(10, 22);
            debugln(from);
            
            String sms = instr.substring(51);

            if (from.indexOf("MPESA"))
            {
                // LOG
                debug(F("from: MPESA"));
                debug(F("sms: "));
                debugln(sms);
            } else if (from.indexOf("TIGOPESA"))
            {
                // LOG
                debug(F("from: TIGOPESA"));
                debug(F("sms: "));
                debugln(sms);
            }
            else if (from.indexOf("AIRTELMONEY"))
            {
                // LOG
                debug(F("from: AIRTELMONEY"));
                debug(F("sms: "));
                debugln(sms);
            }

        }

    }

}
