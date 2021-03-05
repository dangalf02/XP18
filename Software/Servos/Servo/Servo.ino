/*
 /*
  Sweep
Barrido de Servo
*/
#include <Servo.h>  // Libreria servo
int pos = 0;
Servo servo_9;  // Instancia Servo para attach en pin9
void setup()
{
  servo_9.attach(9);// Attach pin - Deberia usarse una variable
}
void loop()
{
  // sweepservo desde 0 a 180 grados en pasos
  // de 1 grado para que sea progresivo y dar tiempo al motor
  for (pos = 0; pos <= 180; pos += 10) {
    // A posicion variable 'pos'
    servo_9.write(pos);
    
    // espero 15 ms para que el servo lentamente llegue a la posicion
    delay(300); // 15 milliseconds
  }
  for (pos = 180; pos >= 0; pos -= 10) {
    // A posicion variable 'pos'
    servo_9.write(pos);
    // espero 15 ms
    delay(300); 
  }
}
