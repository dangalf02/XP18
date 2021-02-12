// Initialize
String vers = "RoverXP18 v0.1 2021Feb10; // 
int TipoRover=1;// 1-XP18   2-Negro
// Constantes segun cada robot 
int TEsqIzq = 0; // Tiempo de esquiva Giro izquierdo
int TEsqDer = 0; // Tiempo de esquiva Giro derecho
int DistDetect = 0; //Distancia minima //para esquivar lo cambie estaba en 15
int ValMax1 = 0; //Valor maximo motor izquierdo
int ValMax2 = 0; //Valor maximo motor derecho
int ValM1 = 0; // Potencia Motor Izq
int ValM2 = 0; // Potencia Motor Der // cambie la potencia,estaba en 175
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
 
void setup()
{
 
  pinMode(PWM1, OUTPUT); 
  pinMode(PoM1, OUTPUT); 
  pinMode(PWM2, OUTPUT);   
  pinMode(PoM2, OUTPUT);   
  pinMode(BajoTrig,OUTPUT);
  pinMode(BajoEcho,INPUT);
  pinMode(PinBotonA,INPUT);
  
  Serial.begin(9600);         // Inicializo canal de comunicaciones
  Serial.println("Start");
  Serial.print("Version: "); Serial.println(vers);
  Serial.print("Rover: "); Serial.println(TipoRover);
 
 if(TipoRover==1){
    rover_XP18();  
    }
 if(TipoRover==2){
    rover_negro();  
    }
delay(2000);//Para dar tiempo luego de programarlo /conectar bateria
    }//setup

 
// Main program
void loop()
{
Serial.println("Loop");
delay(2000);  // para dar tiempo a posicionar al Rover

//  aca se podria encender un led indicando modo seteo de Pasos

Serial.println("Empieza proceso..");

while (1){ //Instrucciones
  Esquivar();
  Avanza();
}  // while
Para();      

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
  analogWrite(PoM1, HIGH) ;   
  analogWrite(PWM1, ValMax1);
  delay(50);
  analogWrite(PoM1, HIGH) ;   
  analogWrite(PWM1, ValM1) ;
  analogWrite(PoM2, HIGH) ;   
  analogWrite(PWM2, ValMax2);
  
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



// End.
