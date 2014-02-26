#include <Ethernet.h>
#include <SPI.h>
#include <WString.h>
#include "Stack.h"

// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 
  0x90, 0xA2, 0xDA, 0x00, 0xC8, 0x27 };  
//the IP address for the shield:
byte ip[] = { 
  192, 168, 1, 222 };    
EthernetServer server(80);
int inPin = 5;   // pushbutton connected to digital pin 7
//int outPin = 13;       // the number of the output pin
int buttonState;
typedef Stack<int,25> IntStack;
static IntStack myStack;
String requestString = String(100);
int format = 1; // 1 = HTML, 2 = JSON

void setup()
{
  Ethernet.begin(mac, ip);
  Serial.begin(9600);
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  pinMode(inPin, INPUT);      // sets the digital pin 7 as input
  //  pinMode(outPin, OUTPUT);
}




void loop()
{
  myStack.push(analogRead(inPin));

  if (myStack.full()) {
    int total = 0;
    while (!myStack.empty()) {
      total = total+myStack.pop();
    }
    if (total > 0) {
      buttonState = 1;
    }
    else {
      buttonState = 0;
    }
  }
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (requestString.length() < 100) {
          requestString.append(c);
          }
          if (c == '\n') {
            if (requestString.contains("?")) {
              int lastIndex = 0;
              int currentIndex = 0;
              char valueIndex = 0;
              char var[25] = "";
              char value[25] = "";
              String param = String(25);
              while true {
                currentIndex = requestString.indexOf('&', lastIndex);
                if (currentIndex != -1) {
                  param = requestString.substring(lastIndex + 1, currentIndex);
                  valueIndex = param.indexOf('=');
                  requestString.substring(0, valueIndex).toCharArray(var, 25);
                  requestString.substring(valueIndex + 1).toCharArray(value, 25);
                  if (var == "format") {
                    switch (value) {
                    case "json":
                      format = 2;
                      break;
                    case "html":
                      format = 1;
                      break;
                    }
                  }
                }
              }
            }
            if (format == 1) {
              client.println(F("HTTP/1.1 200 OK"));
              client.println(F("Content-Type: text/html"));
              client.println();
              client.print(F("<!doctype html>"));
              client.print(F("<html><head>")); 
              client.print(F("<meta http-equiv=\"refresh\" content=\"10\">"));
              client.print(F("</head><body>CREO Restroom Status</br>Bathroom:"));
              if (buttonState > 0) {
                client.print(F("Available"));
              } 
              else {
                client.print(F("Occupied"));
              }
              client.println(F("</br></body></html>"));
              break;
            } 
            else if (format == 2) {
              client.println(F("HTTP/1.1 200 OK"));
              client.println(F("Content-Type: application/json"));
              client.println();
              if (buttonState > 0) {
                client.print(F("{available: 1}"));
              } 
              else {
                client.print(F("{available: 0}"));
              }
              break;
            }
          }
        if (c == '\n') {
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

