/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
#include <Servo.h> 
#include <SoftwareSerial.h>

const char* ssid = "ERROR 0xc00000e9";
const char* password = "kamidisinianak-anaktekkom";
SoftwareSerial seri2 (12, 13); // RX, TX

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(80);

Servo myservo;
int motorpin1 = 3;
int motorpin2 = 4; 
int satu = 1;
int nol = 2;
long cm = 0;


void setup() {
  //
  Serial.begin(115200);
  seri2.begin(115200);

  // prepare GPIO2
  pinMode(2, OUTPUT);
  pinMode(motorpin1,OUTPUT);  
  pinMode(motorpin2,OUTPUT);
  digitalWrite(2, 0);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
 
}

void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int val;
  if (req.indexOf("/belok/kanan") != -1)
    kanan();
  else if (req.indexOf("/belok/kiri") != -1)
    kiri();
  else if (req.indexOf("/maju/depan") != -1)
    maju();
  else if (req.indexOf("/maju/belakang") != -1)
    mundur();
  else if (req.indexOf("/berhenti/0") != -1)
    berhenti();
   else if (req.indexOf("/majumundur/cantik") != -1)
    cantik();
  else {
    client.stop();
    return;
  }
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed
}

void maju(){
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,HIGH);
}

void mundur(){
  digitalWrite(motorpin1,HIGH);
  digitalWrite(motorpin2,LOW);
}

void berhenti(){
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,LOW);
}

void kanan(){
  int ulang;
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,HIGH);
  seri2.write(satu);
}

void kiri(){
  int ulang;
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,HIGH);
  seri2.write(nol);
}

void cantik(){
  int ulang;
  digitalWrite(motorpin1,LOW);
  digitalWrite(motorpin2,HIGH);
  delay(3000);
  digitalWrite(motorpin1,HIGH);
  digitalWrite(motorpin2,LOW);
  delay(3000);
}

