#include<SoftwareSerial.h>
#define OP 4 //Output Pin going to relay

SoftwareSerial wifi(2,3);//Rx,Tx


String ssid="MyWifi";     //Wifi ID used to connect
String pass="password";   //Wifi Password

String data;
int number, state;


void setup() {
    pinMode(OP,OUTPUT);
    Serial.begin(9600);
    wifi.begin(9600);
    
    wificommand("AT+RST");
    wificommand("AT+CWMODE=1");
    wificommand("AT+CWJAP=\""+ssid+"\",\""+pass+"\"");
    
    while(wifi.find("OK")!=1)
    {//wait for connection
    }
    delay(1000);
    digitalWrite(OP,HIGH);  //by default relay module is high
    }


void loop() {
  
    wificommand("AT+CIPMUX=0");
    wificommand("AT+CIPSTART=\"TCP\",\"api.thinspeak.com\",80");
    data="GET/channels/1026895/fields/1.json?api_key=88AQ41S0LUBLIER8&results=1";
    number=data.length();
    wificommand("AT+CIPSEND="+String(num+4));
    wifi.find(">");
    wifi.println(data);
    String String1=wifi.readStringUntil('\n');
    state=int(String1.charAt(String1.length()-11))-48;  
    
    if(state==1)
    {
        digitalWrite(OP,LOW);               //condition for turning light ON
        Serial.println("LIGHT ON");
    }
    else if(state==0)
    {
        digitalWrite(OP,HIGH);              //condition for turning light OFF
        Serial.println("LIGHT OFF");
    }
}


void wificommand(String command)
{
     Serial.print("AT commant=>");
     Serial.println(command);
     wifi.println(command);
     delay(1000);
}
