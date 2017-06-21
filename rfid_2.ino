#include <SPI.h>
#include <MFRC522.h>
#include <Keyboard.h>
 
#define RST_PIN    9
#define SS_PIN    10
 
const String VALID_UID = "27ef8c65";
const String MY_PASSWORD = "1702";
const String VALID1_UID = "f5331253";
int lo = 1;
int co = 0;
int ull = 3;
 
String readUID;
 
MFRC522 mfrc522(SS_PIN, RST_PIN);
 
void readByteToString(byte *buffer, byte bufferSize){
  readUID = "";
  for(byte i=0;i<bufferSize;i++){
    readUID = readUID + String(buffer[i], HEX);
  }
}
 
void keyboardLogin(String password){
  int sizePasswordString = password.length()+1;
  char charBuf[sizePasswordString];
  password.toCharArray(charBuf,sizePasswordString);
  for (int i = 0; i < sizePasswordString-1; i++) {
    Keyboard.print(charBuf[i]);
  }
  Keyboard.write(KEY_RETURN);
  lo = 1;
}
void lockpc(){
  delay(500);
  Keyboard.write(KEY_LEFT_GUI);
  delay(100);
  Keyboard.write(KEY_LEFT_ARROW);
  delay(100);
  Keyboard.write(KEY_DOWN_ARROW);
  delay(100);
  Keyboard.write(KEY_RETURN);
  delay(500);
  lo = 0;
  ull = 3;
}

void setup() {
  Keyboard.begin();
  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);
// Initialize serial communications with the PC

}
 
void loop() {
  if (lo == 0){
    //Keyboard.println(lo);
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }
   
    readByteToString(mfrc522.uid.uidByte, mfrc522.uid.size);
    //Serial.println(readUID);
    if(readUID==VALID_UID){
      keyboardLogin(MY_PASSWORD);
      delay(1000);
      lo = 1;
    }
    else if(readUID==VALID1_UID){
      keyboardLogin(MY_PASSWORD);
      delay(1000);
      lo = 1; 
    }else{
      delay(1000);
    } 
  }else if (lo == 1) {
    Serial.println(ull);
    //Keyboard.println("   ");
    if (ull == (3+3)){
      lockpc();   
    } else {
      
    }

    readUID = "";
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      delay(200);
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      co++;
      if (co == 2){
        return;
      } else {
        ull ++;
        co = 0;
        return;
      }
    }


    readByteToString(mfrc522.uid.uidByte, mfrc522.uid.size);
    if(readUID==VALID_UID){
      delay(200);
      ull = 3;
    }
    else if(readUID==VALID1_UID){
      delay(200);
      ull = 3;
    }

    
  }

}

