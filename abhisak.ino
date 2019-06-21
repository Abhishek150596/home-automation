#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>   
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>


//Web/Server address to read/write from 
//website domain name or IP address of server
const char *host = "14it016.tk";   

ESP8266WiFiMulti WiFiMulti;
WiFiServer server(80);
WiFiClient client;

int relay1 = 5;
int relay2 = 4;
int relay3 = 0;
int relay4 = 2;



void setup() {
  // put your setup code here, to run once:
 Serial.begin(115200);
 
 pinMode(relay1, OUTPUT);
 pinMode(relay2, OUTPUT);
 pinMode(relay3, OUTPUT);
 pinMode(relay4, OUTPUT);

 WiFiManager wifiManager;
 wifiManager.resetSettings();
     
wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  
    wifiManager.autoConnect("GUJ INFOTECH");
  
    
    //if you get here you have connected to the WiFi
    Serial.println("You are connected connected___:)");




      if(WiFiMulti.run() == WL_CONNECTED) {
      Serial.println("");
      Serial.print("WiFi connected. ");
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());
      }


      digitalWrite(relay1, HIGH);
      digitalWrite(relay2, HIGH);
      digitalWrite(relay3, HIGH);
      digitalWrite(relay4, HIGH);
      delay(1000);
      digitalWrite(relay1, LOW);
      digitalWrite(relay2, LOW);
      digitalWrite(relay3, LOW);
      digitalWrite(relay4, LOW);
      delay(1000);      
}

void loop() {
  // put your main code here, to run repeatedly:

  String line;
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 
      HTTPClient http;  //Declare an object of class HTTPClient
 
      http.begin("http://14it016.tk/home_auto/getalldevices.php");                  //Specify request destination
      int httpCode = http.GET();                                                                  //Send the request
 
      if (httpCode > 0){                                       //Check the returning code      
 
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload)  ;   //Print the response payload

const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(5) + 70;
DynamicJsonBuffer jsonBuffer(capacity);

//const char* json = "{\"response\":\"Success\",\"data\":[{\"id\":\"1\",\"relay1\":\"0\",\"relay2\":\"1\",\"relay3\":\"0\",\"relay4\":\"1\"}]}";

JsonObject& root = jsonBuffer.parseObject(payload);

const char* response = root["response"]; // "Success"

JsonObject& data_0 = root["data"][0];
String data_0_id = data_0["id"]; 

String data_0_relay1 = data_0["relay1"];
int valve1 = data_0_relay1.toInt();
Serial.print("Relay1 is = ");
Serial.println(valve1);
if (valve1 == 1)
{
  digitalWrite(relay1, HIGH);
  Serial.print("realay 1 is high");
}
else
{
  digitalWrite(relay1,LOW);
}


String data_0_relay2 = data_0["relay2"];  
int valve2 = data_0_relay2.toInt();
Serial.print("Relay2 is = ");
Serial.println(valve2);
if (valve2 == 1)
{
  digitalWrite(relay2, HIGH);
  Serial.print("realay 2 is high");
}
else
{
  digitalWrite(relay2,LOW);
}

String data_0_relay3 = data_0["relay3"];  
int valve3 = data_0_relay3.toInt();
Serial.print("Relay3 is = ");
Serial.println(valve3);
if (valve3 == 1)
{
  digitalWrite(relay3, HIGH);
  Serial.print("realay 3 is high");
}
else
{
  digitalWrite(relay3,LOW);
}


String data_0_relay4 = data_0["relay4"]; 
int valve4 = data_0_relay4.toInt();
Serial.print("Relay4 is = ");
Serial.println(valve4);
if (valve4 == 1)
{
  digitalWrite(relay4, HIGH);
  Serial.print("realay 4 is high");
}
else
{
  digitalWrite(relay4,LOW);
}


      http.end();   //Close connection
          }
      }
}
