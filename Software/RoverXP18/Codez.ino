
 void rover_XP18(){
 TEsqIzq= 1000; // Tiempo de esquiva Giro izquierdo
 TEsqDer= 1000; // Tiempo de esquiva Giro derecho
 DistDetect=7; //Distancia minima para esquivar
 ValMax1   = 170;  // 130; //Valor maximo motor izquierdo
 ValMax2   = 170;  //130; //Valor maximo motor derecho
 BackFwdIzq=1;
 BackFwdDer=1;
 ValM1   = 120;  //45; // Potencia Motor Izq
 ValM2   = 120;  //55; // Potencia Motor Der
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
 //BackFwdIzq=0;
 //BackFwdDer=0;
 ValM1   = 80; // Potencia Motor Izq
 ValM2   = 80; // Potencia Motor Der
 PWM1   = 11; // Pin Motor 1  (Der)    PWM1 = ValM1  , PoM1= HIGH => avanza
 PoM1 = 10;   // Pin Motor 1 (Der)  PWM1 = HIGH  , PoM1= ValM1 => retrocede
 PWM2   = 5; // Pin Motor 2  
 PoM2 = 3;   // Pin Motor 2  (Izq)
 BajoTrig = 6; // TRIG Ultrasonido bajo
 BajoEcho = 7;  // ECHO  ultrasonido bajo
    
  }  


void compass(){

/* Read each sensor axis data and output to the serial port */
EjeX = HMC5803L_Read(RegX);
EjeY = HMC5803L_Read(RegY);
//Serial.print(EjeX);
//Serial.print("   ");
//Serial.print(EjeY);
//Serial.print("   ");
//Serial.println(HMC5803L_Read(RegZ));
Dir="";
if ( (EjeX>=320) && (EjeY>=-220) && (EjeY<=-1)) { Dir="N";}
else if ((340>EjeX) && (EjeX>240) && (EjeY > 0) ) {Dir="NE";}
else if ((EjeX>100) && (EjeY > 20) ) {Dir="E";}
else if ((EjeX<110) && (EjeY > 20) ) {Dir="SE";}
else if ((EjeX<110) && (EjeY <0)&& (EjeY>=-220) ) {Dir="S";}
else if ((EjeX<110) && (EjeY <-200) ) {Dir="SO";}
else if ((340>EjeX) && (EjeX>240) && (EjeY<-136)) {Dir="NO";}
else if ((260>EjeX) && (EjeX>100) && (EjeY<-240)) {Dir="O";}

//else {Serial.println("Invalido");  }
//Serial.println(Dir);
//delay(100);

  }// compass
