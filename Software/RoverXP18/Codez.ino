
 void rover_XP18(){
 TEsqIzq= 1000; // Tiempo de esquiva Giro izquierdo
 TEsqDer= 1000; // Tiempo de esquiva Giro derecho
 DistDetect=7; //Distancia minima para esquivar
 ValMax1   = 150;  // 130; //Valor maximo motor izquierdo
 ValMax2   = 180;  //130; //Valor maximo motor derecho
 BackFwdIzq=1;
 BackFwdDer=1;
 ValM1   = 70;  //45; // Potencia Motor Izq
 ValM2   = 105;  //55; // Potencia Motor Der
 PWM1   = 11; // Pin Motor 1  (Der)    PWM1 = ValM1  , PoM1= HIGH => avanza
 PoM1 = 6;   // Pin Motor 1 (Der)  PWM1 = HIGH  , PoM1= ValM1 => retrocede
 PWM2   = 5; // Pin Motor 2  
 PoM2 = 3;   // Pin Motor 2  (Izq)
 BajoTrig = 13; // TRIG Ultrasonido bajo
 BajoEcho = 12;  // ECHO  ultrasonido bajo
  }   
  
  
 void rover_Sab(){
 ValMax1   = 255; //Valor maximo motor izquierdo
 ValMax2   = 255; //Valor maximo motor derecho
 BackFwdIzq=0;
 BackFwdDer=0;
 ValM1   = 80; // Potencia Motor Izq
 ValM2   = 80; // Potencia Motor Der
 PWM1   = 11; // Pin Motor 1  (Der)    PWM1 = ValM1  , PoM1= HIGH => avanza
 PoM1 = 10;   // Pin Motor 1 (Der)  PWM1 = HIGH  , PoM1= ValM1 => retrocede
 PWM2   = 5; // Pin Motor 2  
 PoM2 = 3;   // Pin Motor 2  (Izq)
 BajoTrig = 6; // TRIG Ultrasonido bajo
 BajoEcho = 7;  // ECHO  ultrasonido bajo
    
  }  

