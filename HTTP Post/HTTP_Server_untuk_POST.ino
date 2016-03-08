/*
A simple web server using an Arduino Wiznet Ethernet shield. 
For Arduino IDE V1.0 only. Previous IDE versions require mods to this code.

Original code created 18 Dec 2009
 by David A. Mellis
 modified 4 Sep 2010
 by Tom Igoe
 modified 18 Jan 2012
 by Tim Dicus 
*/

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x98, 0x4F, 0xEE, 0x00, 0x0A, 0xD7 };
IPAddress ip( 192,168,1,123 );
IPAddress gateway( 192,168,1,1 );
IPAddress subnet( 255,255,255,0 );
IPAddress dns( 192,168,1,1 );

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
  Serial.begin(9600);

  // set SPI SS pins on w5100 and SD
  pinMode(10,OUTPUT);
  digitalWrite(10,HIGH);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);

  // start the SD interface here if you want.
  // Add the SD.h library above
  // SD.begin(4);

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip, dns, gateway, subnet);
  // disable w5100 SPI so SD SPI can work with it
  digitalWrite(10,HIGH);
  delay(2000);
  server.begin();

  Serial.println("setup finished");
}

void loop()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("Client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      while(client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {

// Here is where the POST data is.  
          while(client.available())
          {
             Serial.write(client.read());
          }
          Serial.println(); //kasih jarak

          Serial.println("Sending response");
          // send a standard http response header
          client.println("HTTP/1.0 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          client.println("<HTML><BODY>TEST OK!</BODY></HTML>");
          client.stop();
        }
        else if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    Serial.println("Disconnected");
  }
}
