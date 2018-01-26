//ERFINDER CODE
#include <SoftwareSerial.h>

SoftwareSerial mySerial(9, 10);
#define CH3 7

void setup()
{
 
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  pinMode(CH3, OUTPUT);
  digitalWrite(CH3,HIGH);
}


void loop()
{


// starts the voltage reader

  int sensorValue = analogRead(A0);
  float voltage = sensorValue *(5.0 / 1023.0);
  //

  // ends the voltage reader

  if (voltage >= 4){   
    
    
    SendMessage(); 
   // Serial.println(voltage);
    delay(5000);  
    digitalWrite(CH3, LOW); 
      
/* if (mySerial.available()>0){
   Serial.write(mySerial.read());  
    SendMessage();
    }
    */
  }
    else{
      digitalWrite(CH3, HIGH);
     // Serial.println("No");
      //RecieveMessage();
      }
  }


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+251915766334\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Hi Munib, the Power was Turned off from EEPCO and it came again So I turned it on! Thank You");// The SMS text you want to send
  delay(100);
  mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}



void SendTrueMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+251915766334\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println("Hi Munib, The Transformer is On and Seems Everything Okay");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}

void RecieveMessage()
{
  
  if (mySerial.available()>0)
   Serial.write(mySerial.read());
   if (mySerial.read()==1){
    SendTrueMessage();
    
    }
    mySerial.println("AT+CNMI=2,2,0,0,0");
   // AT Command to recieve a live SMS
  delay(1000);
}

 
 
