/*
  Software serial multple serial test
 
 circuito:
 * RX digital pin 10 (conecta a TX del otro lado)
 * TX digital pin 11 (conecta a RX )

 */
#include <SoftwareSerial.h>
SoftwareSerial GPSSerial(2, 3); // RX, TX


String inputString = "";         // String para ir almacenando caracteres
String sCode= "GPRMC";
boolean stringComplete = false;  // Indica lectura completa de un string
float latgrados;
float latminutos;
float longgrados;
float longminutos;

int Led=13;
void setup() {
  Serial.begin(9600);
  Serial.println("Start");
  // data rate for the SoftwareSerial port
  GPSSerial.begin(9600);

  // reserva 200 bytes para inputString:
  inputString.reserve(200);
}

void loop() { // run over and over
  digitalWrite(13,LOW);
//  if (GPSSerial.available()) {  anulado porque el GPS manda data siempre
//    Serial.write(GPSSerial.read());}
  while (GPSSerial.available()) {
    // get the new byte:
    char inChar = (char)GPSSerial.read();
    // add it to the inputString:
    inputString += inChar;
    // Si el char recibido indica nueva linea, completo el string
    // detecto nueva linea porque el GPS envia "$" al comienzo

    if (inChar == '$') {
      //Serial.println(inputString);
      stringComplete = true;
      StringListo();
      } // $  Nuevo String
  }//while
  
}// Loop

void StringListo() {
   if(inputString.substring(0,5)==sCode){
          Serial.println(inputString);
         // Serial.println(inputString.substring(0,5));   
      //Serial.println(inputString.substring(16,17));
      if(inputString.substring(16,17)=="A"){
          digitalWrite(13,HIGH); delay(1000);
          
          Serial.println("OK1");
          latgrados=inputString.substring(18,20).toFloat();
          Serial.println(inputString.substring(18,20));
          latminutos=inputString.substring(20,28).toFloat();
        Serial.println(inputString.substring(20,28));  
        latminutos=latminutos/60;
          latgrados=-(latgrados+latminutos);
          Serial.println(latgrados,4);
        Serial.println(inputString.substring(32,34));
        Serial.println(inputString.substring(34,42));
          longgrados=inputString.substring(32,34).toFloat();
          longminutos=inputString.substring(34,42).toFloat();
          longminutos=longminutos/60;
          longgrados=-(longminutos+longgrados);
          Serial.println(longgrados,4);
        Serial.println(inputString.substring(41,42));
        
      }
    }
    inputString="";
    stringComplete=false;

} // StringListo
//  *******  EoF

