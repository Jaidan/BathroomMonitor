#include <Ethernet.h>
#include <SPI.h>

// the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xC8, 0x27 };  
//the IP address for the shield:
byte ip[] = { 192, 168, 1, 222 };    
EthernetServer server(80);
int inPin = 5;   // pushbutton connected to digital pin 7
//int outPin = 13;       // the number of the output pin
int buttonState;
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
  buttonState = analogRead(inPin);
  
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) 
  {
      boolean currentLineIsBlank = true;
      while (client.connected()) 
      {
          if (client.available()) 
          {
              char c = client.read();
              if (c == '\n' && currentLineIsBlank) 
              {
                  client.println("HTTP/1.1 200 OK");
                  client.println("Content-Type: text/html");
                  client.println();
                  client.print("<!doctype html>");
                  client.print("<html><head><title>CREO Bathroom Status</title>");
                  client.print("<script>setTimeout('refresh()', 30000);function refresh() { window.location.href = '/' }</script>");
                  client.print("</head><body>CREO Restroom Status<br>Bathroom:");
                  if (buttonState > 0)
                  {
                     client.print("Available");
                     //client.print(buttonState);
                  }
                  else
                  {
                     client.print("Occupied");
                     //client.print(buttonState );
                  }
                  client.println("</br></body></html>");
                  break;
           
              }
              if (c == '\n') 
              {
                  currentLineIsBlank = true;
              }
              else if (c != '\r') 
              {
                  currentLineIsBlank = false;
              }
          }
      }
//    digitalWrite(outPin, buttonState);
    // give the web browser time to receive the data
      delay(1);
    // close the connection:
      client.stop();
    }
}
