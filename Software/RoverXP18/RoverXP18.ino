#include <Wire.h>
// Initialize
String vers = "RoverXP18 v0.2 2021Feb24"; // 
int TipoRover=1;// 1-XP18   2-Negro

// Constantes segun cada robot 
int TEsqIzq = 0; // Tiempo de esquiva Giro izquierdo
int TEsqDer = 0; // Tiempo de esquiva Giro derecho
int DistDetect = 0; //Distancia minima //para esquivar lo cambie estaba en 15
int ValMax1 = 0; //Valor maximo motor izquierdo
int ValMax2 = 0; //Valor maximo motor derecho
int ValM1 = 0; // Potencia Motor Izq
int ValM2 = 0; // Potencia Motor Der 
int BackFwdDer,BackFwdIzq;
//******************************************

int PWM1 = 6;   // Pin Motor 1  Izq)  PWM1 = ValM1  , PoM1= HIGH => avanza
int PoM1 = 11;  // Pin Motor 1 (Izq)  PWM1 = HIGH  , PoM1= ValM1 => retrocede
int PWM2 = 5;   // Pin Motor 2  
int PoM2 = 3;   // Pin Motor 2  (Der)
int BajoTrig ; // TRIG Ultrasonido bajo
int BajoEcho ;  // ECHO  ultrasonido bajo
int PinServoDist=9;   // Servo que mueve al ultrasonico
int PinServoPanel=10; // Servo del panel solar
int x,y;
int i = 1;     // increment 
int Obs = 0; 
// --------  compass
String Dir;
//#include <Wire.h> // I2C address of the module 
#define HMC5803L_Address 0x1E
// I2C   A4:Data   A5: Clk

/* Register address for the X Y and Z data */
#define RegX 3
#define RegY 7
#define RegZ 5
int EjeX; int EjeY; int EjeZ;
//---- compass
 
void setup()
{
  pinMode(PWM1, OUTPUT); 
  pinMode(PoM1, OUTPUT); 
  pinMode(PWM2, OUTPUT);   
  pinMode(PoM2, OUTPUT);   
  pinMode(BajoTrig,OUTPUT);
  pinMode(BajoEcho,INPUT);

  
  Serial.begin(9600);         // Inicializo canal de comunicaciones
  Serial.println("Start");
  Serial.print("Version: "); Serial.println(vers);
  Serial.print("Rover: "); Serial.println(TipoRover);
 
 if(TipoRover==1){
    rover_XP18();  
    }
 if(TipoRover==2){
   // rover_negro();  
    }


  Wire.begin();
  //Inicializo Magnetometro
  Init_HMC5803L(); 


delay(2000);//Para dar tiempo luego de programarlo /conectar bateria
 
Giro(1000);
Para();delay(300);
Giro(-1000);
Para();delay(300);    

    
Serial.println("Loop");
delay(2000);  // para dar tiempo a posicionar al Rover
Serial.println("Empieza proceso..");
    
    }//setup

 
// Main program
void loop()
{
//************* Instrucciones *************************
  //Esquivar();
compass();
if (Dir =="NO"){Serial.println("GIRO DER"); Giro(20);} 
if (Dir =="NE"){Giro(-20);} 
if (Dir =="E") {Giro(-20);}
if (Dir =="SE"){Giro(-20);} 
if (Dir =="S") {Giro(20);} 
if (Dir =="O") {Giro(20);} 
if (Dir =="SO"){Giro(20);} 
else {Avanza(); delay(200); }
      
}//endloop

//*****************************  Funciones ******************************

void Esquivar(){
   if ( ( distancia(BajoTrig,BajoEcho)<DistDetect))  {
      //Para(); 
      Retrocede();delay(600);// estaba en 300
      GiroDer();delay(TEsqDer);Serial.println("Dentro de If <10..");
      Para(); 
      Avanza();delay(500);
      Para();
      GiroIzq();delay(TEsqIzq);
      Para();
     }//Endif
  }//Esquivar

 
void Avanza() {
//  analogWrite(PoM1, HIGH) ;   
//  analogWrite(PWM1, ValMax1);
//  analogWrite(PoM2, HIGH) ;   
//  analogWrite(PWM2, ValMax2);
//  delay(80);
  analogWrite(PoM1, HIGH) ;   
  analogWrite(PWM1, ValM1) ;
  analogWrite(PoM2, HIGH) ;   
  analogWrite(PWM2, ValM2);
  
}

void Retrocede() {
  analogWrite(PoM1, ValM1) ;   
  analogWrite(PWM1, HIGH) ;
  analogWrite(PoM2, ValM2) ;  
  analogWrite(PWM2, HIGH) ;  
}

void Para(){
    digitalWrite(PoM1, LOW) ;   // Both motor with same polarity
    digitalWrite(PoM2, LOW) ;  
    digitalWrite(PWM1, LOW) ;   // Both motor with same polarity
    digitalWrite(PWM2, LOW) ;   
    delay(10);
}
void GiroDer() {
  analogWrite(PoM1, HIGH) ;   //izq avanza
  analogWrite(PWM1, ValM1) ;
  analogWrite(PoM2, ValM2) ;  
  analogWrite(PWM2, HIGH) ;
}
void GiroIzq() {
  analogWrite(PoM1, ValM1) ;   //Motor izq retrocede
  analogWrite(PWM1, HIGH) ;
  analogWrite(PoM2, HIGH) ; 
  analogWrite(PWM2, ValM2);  
}
void Giro(int Dly) {
  
 if (Dly <0) { //Giro a Izq
  Dly = Dly * -1;
  analogWrite(PoM1, ValMax1) ;   //izq retrocede
  analogWrite(PWM1, BackFwdIzq) ;
  analogWrite(PoM2, BackFwdDer) ;
  analogWrite(PWM2,ValMax2 ) ;
  delay(80);
 
  analogWrite(PoM1, ValM1+30) ;   //Motor izq retrocede
  analogWrite(PWM1, BackFwdIzq) ;
  analogWrite(PoM2, BackFwdDer) ;
  analogWrite(PWM2, ValM2+30);
  delay(Dly);
}
 else { // Gira a Derecha
  analogWrite(PoM1, BackFwdIzq) ;   //izq avanza
  analogWrite(PWM1, ValMax1) ;
  analogWrite(PoM2, ValMax2) ;
  analogWrite(PWM2,BackFwdDer ) ;
  delay(80);
  
  analogWrite(PoM1, BackFwdIzq) ;   //izq avanza
  analogWrite(PWM1, ValM1+30) ;
  analogWrite(PoM2, ValM2+30) ;
  analogWrite(PWM2,BackFwdDer );
  delay(Dly);
 }
 //Para();
  
} // Giro

void ArcoDer() {
  analogWrite(PoM1, HIGH) ;   //Motor izq retrocede
  analogWrite(PWM1, ValM1) ;
  analogWrite(PoM2, LOW) ; 
  analogWrite(PWM2, LOW) ; 
}

void ArcoIzq() {
    analogWrite(PoM1, 0) ;   //Motor izq 
    analogWrite(PWM1, 0) ;
    analogWrite(PoM2, 255) ; 
    analogWrite(PWM2, ValM2) ;
}


long distancia(int Trig, int Echo){//Mide la distancia y la guarda en "cm"
 long resultado; long Tiempo_us;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  Tiempo_us = pulseIn(Echo, HIGH,4060); 
    resultado = Tiempo_us/58;                        
  delay(100); // Verificar
  if (Tiempo_us == 0){resultado =70;}
  return resultado;
} // distancia

void Init_HMC5803L(void){
/* Set the module to 8x averaging and 15Hz measurement rate */
Wire.beginTransmission(HMC5803L_Address);
Wire.write(0x00);
Wire.write(0x70);

/* Set a gain of 5 */
Wire.write(0x01);
Wire.write(0xA0);
Wire.endTransmission();
}

/* This function will read once from one of the 3 axis data registers
and return the 16 bit signed result. */
int HMC5803L_Read(byte Axis){
int Result;

/* Initiate a single measurement */
Wire.beginTransmission(HMC5803L_Address);
Wire.write(0x02);
Wire.write(0x01);
Wire.endTransmission();
delay(6);

/* Move modules the resiger pointer to one of the axis data registers */
Wire.beginTransmission(HMC5803L_Address);
Wire.write(Axis);
Wire.endTransmission();

/* Read the data from registers (there are two 8 bit registers for each axis) */ 
Wire.requestFrom(HMC5803L_Address, 2);
Result = Wire.read() << 8;
Result |= Wire.read();

return Result;
}

// End.
