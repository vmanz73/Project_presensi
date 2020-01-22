/*
 * 
 * All the resources for this project: https://www.hackster.io/Aritro
 * Modified by Aritro Mukherjee
 * 
 * 
 */
 
#include <SPI.h>
#include <MFRC522.h>
 #include <Ethernet.h>
#define SS_PIN 9
#define RST_PIN 8
String id,idl,data;
byte mac[] = { 0x00, 0xAA, 0xBB, 0xCC, 0xDE, 0xA3 };// RESERVED MAC ADDRESS
IPAddress ip(192,168,100,10); 
IPAddress subnet(255, 255, 255, 0);
EthernetClient client;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
 
void setup() 
{
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("Approximate your card to the reader...");
  Serial.println();
  Ethernet.begin(mac,ip,subnet);
  Serial.println(Ethernet.localIP());
  


}
void loop() 
{
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  
  String content= "";
  byte letter;
  
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     //Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     //Serial.print(mfrc522.uid.uidByte[i], HEX);
     id = id + String(mfrc522.uid.uidByte[i], HEX);
     //content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     //content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  if (idl!=id){
    idl=id;
    Serial.print("UID tag :");
     for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     //id = id + String(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
 Serial.println();
 Serial.println(Ethernet.localIP());
  }
  id = "";
  
 
  
}
void database(String data){
  if (client.connect("192.168.100.1",80)) { // REPLACE WITH YOUR SERVER ADDRESS
    client.println("GET http://192.168.100.1/smart-class/mikro/up.php?"+data); 
    client.println("Host: 192.168.100.1"); // SERVER ADDRESS HERE TOO
    client.println("Content-Type: application/x-www-form-urlencoded"); 
    client.print("Content-Length: "); 
    client.println(data.length()); 
    client.println(); 
    client.print(data); 
    Serial.println (data);  
  }
  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  } 
} 
