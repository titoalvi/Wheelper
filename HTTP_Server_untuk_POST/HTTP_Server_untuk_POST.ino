//Tito Alvi N.
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

void konek(){

    // listen for incoming clients
    EthernetClient client = server.available();
    if (client) {
    Serial.println("Client Terhubung\n");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean currentLineIsGet = true; //tambahan
    int tCount = 0;
    char tBuf[64];
    char a,b;
    int r,t;
    char *pch;

    
    while (client.connected()) {
      while(client.available()) {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        //tambahan
        if(currentLineIsGet && tCount < 63)
        {
          tBuf[tCount] = c;
          tCount++;
          tBuf[tCount] = 0;          
        }

        
        if (c == '\n' && currentLineIsBlank) {
          //Data terkirim di sini
          int x=0, n=0;
          for(x=0;x<=60;x++){
          Serial.print(tBuf[n]);
          n++;}
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
          currentLineIsGet = false;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    Serial.println("Sambungan Terputus!");
  }
}

void setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac, ip, dns, gateway, subnet);
  server.begin();
  Serial.println("Setting HTTP Selesai :) \nLanjutkan Masbro!");
}

void loop()
{
  konek();

 }


