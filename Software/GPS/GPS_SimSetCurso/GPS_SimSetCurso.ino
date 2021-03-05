void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Monitor working");

}

//Globals for return value from function  //NEED
float distanceTo, degrees;                //NEED
int closeTo = 0;                          //NEED

void loop() {
    int i;
  
    //Position and distance calculation unit test
    //To position
    float toLon = -58.595798;
    float toLat = -34.787206;

    //Test positions
    float testLon[10] = {20, -58.395798, 10, 10, 20, 30, 30, 30, 20, 22};
    float testLat[10] = {30, -34.587206, 20, 10, 10, 10, 20, 30, 30, 31};
    float answer[10] = {270.0, 225.0, 180.0, 135.0, 90.0, 45.0, 0.0, 315.0, 270.0, 280.304840};

    //loop through the test positions
    for(i=0; i<10; i++)
    {
        //function to call
        calculate(toLon, toLat, testLon[i], testLat[i]);  //NEED
        
        //if closeTo = 0 reduce speed else keep speed
        //setSpeed(closeTo)
        //if closeTo = 1
        //   reduce speed

        
        //SetDirection()  //based on angle from degrees
        //compassValue = 45
       //   calculate(-34.587206, -58.395798,-34.787206, -58.595798);
        //degrees = ouptut of calculate
        //setDirection(degrees)
        //energize motors until compassValue = degrees
        
        //RunForTime say 5sec
        //run for however long to run
        
        if(closeTo == 1){
            printf("slow down\n");
            Serial.print("slow down\n");
        }
        else
        {
            printf("normal speed\n");
            Serial.print("normal speed\n");
        }
        printf("distanceTo = %f, degrees = %f, answer = %f\n", distanceTo, degrees, answer[i]);
        if(degrees == answer[i])
            printf("test passed!!\n\n");
        else
            printf("******** TEST FAILED!! *******\n\n");
    }
  
    delay(5000);
    exit(0);
  
}



//calculates distance to position from current position
//calculates degrees to position from current position
//uses the following as global variables for output
//float distanceTo, degrees;
//toLon & toLat are the position to tow the bot to
//curLon & curLat are from the GPS receiver
void calculate(float toLon, float toLat, float curLon, float curLat)
{
    float x, y, angle;
    
    //calcualte distance
    x = -(curLon - toLon);
    y = curLat - toLat;
    distanceTo = sqrt((x*x) + (y*y));
    
    //calculate angle
    angle = atan(y/x);
   //Serial.println(angle);
    if(x > 0)
        degrees = (angle * 180)/3.14159265;
    else
        degrees = ((angle * 180)/3.14159265) + 180;
    degrees = degrees + 180;
    if(degrees >= 360)
        degrees = degrees - 360;
    
    //set clostTo flag (NEED TO UPDATE BASED ON GPS DISTANCE)
    if(distanceTo < 11)
        closeTo = 1;
    else
        closeTo = 0;
    
//    printf("x = %f, y = %f, distanceTo = %f, angle = %f\n", x, y, distanceTo, degrees);
    Serial.print("X: "); 
    Serial.print(x);
    Serial.print("   Y: "); 
    Serial.println(y);
    Serial.print("distanceTo: "); 
    Serial.print(distanceTo, 4);
    Serial.print("    degrees: "); 
    Serial.print(degrees, 4);
    Serial.println();
    //Serial.println("*********************");
    //Serial.println();
  
  
}