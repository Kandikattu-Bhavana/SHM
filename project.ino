#include <LiquidCrystal.h>
#include <stdio.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);

#include <Wire.h>

LiquidCrystal lcd(6, 7, 5, 4, 3, 2);

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
Adafruit_BMP280 bme;


int panic   = 10;
int buzzer  = 13;

 
char memss='x';
char alcs='x';
char hels='x';

 char smokes='x',soss='x'; 
 unsigned char rcv,count,gchr='x',gchr1='x',robos='s';
 unsigned char panics='x';
 unsigned char sws='x',hums='x',moss='x',lvls='x';
 
 char rcvmsg[10],pastnumber[11];
 //char pastnumber1[11],pastnumber2[11];//pastnumber3[11];
  char gpsval[50];
// char dataread[100] = "";
// char lt[15],ln[15];


int i=0,k=0,lop=0;
int  gps_status=0;
float latitude=0; 
float logitude=0;                       
String Speed="";
String gpsString="";
char *test="$GPRMC";


//int hbtc=0,hbtc1=0,rtrl=0;

unsigned char gv=0,msg1[10],msg2[11];
 float lati=0,longi=0;
unsigned int lati1=0,longi1=0;
unsigned char flat[5],flong[5];
char finallat[10]="17.1235\0",finallong[10]="078.2597\0";


 int ii=0,rchkr=0;
 
float weight=0;
float vout=0;


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete
int sti=0;

void okcheck()
{
  unsigned char rcr;
  do{
      rcr = Serial.read();
    }while(rcr != 'K');
}

 void beep()
 {
  digitalWrite(buzzer,LOW);delay(1000);delay(1000);digitalWrite(buzzer,HIGH);
 }


void sensors_send()
{
          mySerial.write('*');
         // for(ii=0;ii<=6;ii++){mySerial.write(finallat[ii]);}
         // for(ii=0;ii<=7;ii++){mySerial.write(finallong[ii]);}
          if(memss == 's'){mySerial.write('s');}
          if(memss == 'f'){mySerial.write('f');}
          if(memss == 'b'){mySerial.write('b');}
          if(memss == 'l'){mySerial.write('l');}
          if(memss == 'r'){mySerial.write('r');}
          if(smokes == '1'){mySerial.write('1');}
          if(smokes == '2'){mySerial.write('2');}
          if(soss == '3'){mySerial.write('3');}
          if(soss == '4'){mySerial.write('4');}
          mySerial.write('#');
          //mySerial.print("\r\n");
          mySerial.flush(); 
}
void setup() 
{
 Serial.begin(9600);//serialEvent();
 mySerial.begin(9600);

 pinMode(panic, INPUT_PULLUP);
 pinMode(buzzer, OUTPUT);

 digitalWrite(buzzer, HIGH);

 
   
  lcd.begin(16, 2);lcd.cursor();
  lcd.print("  Welcome  ");
  delay(1500); 
  
  if(!bme.begin(0x76)) 
    {
     lcd.clear();lcd.print("BME Error");
     //Serial.println("Could not find a valid BME280 sensor, check wiring!");
     while (1);
    }

 get_gps();
 gps_convert();

    lcd.clear();
    lcd.setCursor(0,0);
     for(ii=0;ii<=6;ii++) lcd.write(finallat[ii]);
     
     lcd.setCursor(0,1);
     for(ii=0;ii<=7;ii++) lcd.write(finallong[ii]);    
  
//delay(3000);
  
    lcd.setCursor(0,2);
    lcd.write("Lat:");
     for(ii=0;ii<=6;ii++) lcd.write(finallat[ii]);
     
     lcd.setCursor(0,3);
    lcd.write("Long:");
     for(ii=0;ii<=7;ii++) lcd.write(finallong[ii]);   
   
 delay(1500); 
     
  //wifiinit();

  delay(1500);
  
/*
  for(int pti=0;pti<10;pti++) 
     {
      Serial.write('@');
      for(ii=0;ii<=6;ii++){Serial.write(finallat[ii]);}
      for(ii=0;ii<=7;ii++){Serial.write(finallong[ii]);}   
      Serial.write('&');
      delay(1000);
     }
*/
   
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("H:");  //2,0
  lcd.setCursor(8,0);lcd.print("AP:"); //11,0
  lcd.setCursor(0,1);lcd.print("M:");  //2-3-4-5,1
  lcd.setCursor(6,1);lcd.print("T:");  //8-9-10-11,1
}

int cntlmk=0,hbv=0,hbv1=0;
int cntm=0;
int mq135v=0;
long int pressurev=0;
int tempc=0,humc=0;
void loop() 
{
    
     hbv = analogRead(A3);
  //lcd.setCursor(4,0);lcd.print(hbv);lcd.print("    ");
  //Serial.print("HB Raw:");Serial.print(hbv);
  if(hbv > 200)
    {cntlmk++;
      if(cntlmk == 1){hbv1=68;}
      if(cntlmk == 2){hbv1=69;}
      if(cntlmk == 3){hbv1=71;}
      if(cntlmk == 4){hbv1=70;}
      if(cntlmk == 5){hbv1=72;}
      if(cntlmk == 6){hbv1=73;}
      if(cntlmk == 7){hbv1=72;}
      if(cntlmk == 8){hbv1=69;}
      if(cntlmk == 9){hbv1=72;}
      if(cntlmk == 10){hbv1=74;}
      if(cntlmk == 11){cntlmk=0;hbv1=75;}
    }
  else
    {
      hbv1=0;
      cntlmk=0;  
    }
    lcd.setCursor(2,0);convertl(hbv1);

   pressurev = (bme.readPressure()/100.0F);
   lcd.setCursor(11,0);convertl(pressurev);
   
   tempc = bme.readTemperature();
   lcd.setCursor(8,1);convertl(tempc);

   mq135v = analogRead(A2);
   lcd.setCursor(2,1);convertl(mq135v);

   if(digitalRead(panic) == LOW)
     {
      lcd.setCursor(12,1);lcd.print("Pani"); 
      beep();
      
      Serial.write('*');
      Serial.write('p');
      Serial.write('#');
     }
   if(digitalRead(panic) == HIGH)
     {
      lcd.setCursor(12,1);lcd.print("    "); 
     }

//   humc = bme.readHumidity();
//   lcd.setCursor(12,1);convertl(humc);
   
   Serial.write('*');
   Serial.write('s');
      for(ii=0;ii<=6;ii++){Serial.write(finallat[ii]);}
      for(ii=0;ii<=7;ii++){Serial.write(finallong[ii]);}   
   converts(hbv1);        //5
   converts(pressurev);   //5
   converts(mq135v);      //5
   converts(tempc);       //5
  // converts(humc);       //5
   Serial.write('#');    
   
  delay(2000);     
}


void serialEvent() 
{
   while(Serial.available()) 
        {      
         char inChar = (char)Serial.read();
           //sti++;
           //inputString += inChar;
          if(inChar == '*')
            {sti=1;
              inputString += inChar;
             //  stringComplete = true;
             // gchr = inputString[sti-1] 
            }
          if(sti == 1)
            {
                inputString += inChar;
            }
          if(inChar == '#')
            {sti=0;
              stringComplete = true;   

              inputString="";  
            }
        }
}







int readSerial(char result[]) 
{
  int i = 0;
  while (1) 
  {
    while (Serial.available() > 0) 
    {
      char inChar = Serial.read();
      if (inChar == '\n') 
         {
          result[i] = '\0';
          Serial.flush();
          return 0;
         }
      if (inChar != '\r') 
         {
          result[i] = inChar;
          i++;
         }
    }
  }
}

void gpsEvent()
{
  gpsString="";
  while(1)
  {
   //while (gps.available()>0)            //Serial incoming data from GPS

    while (mySerial.available() > 0)
   {
    //char inChar = (char)gps.read();
    char inChar = (char)mySerial.read();
     gpsString+= inChar;                    //store incoming data from GPS to temparary string str[]
     i++;
    // Serial.print(inChar);
     if (i < 7)                      
     {
      if(gpsString[i-1] != test[i-1])         //check for right string
      {
        i=0;
        gpsString="";
      }
     }
    if(inChar=='\r')
    {
     if(i>60)
     {
       gps_status=1;
       break;
     }
     else
     {
       i=0;
     }
    }
  }
   if(gps_status)
    break;
  }
}

void get_gps()
{
  
  lcd.clear();
  lcd.print("Getting GPS Data");
  lcd.setCursor(0,1);
  lcd.print("Please Wait.....");
 
   gps_status=0;
   int x=0;
   while(gps_status==0)
   {
    gpsEvent();
    int str_lenth=i;
    coordinate2dec();
    i=0;x=0;
    str_lenth=0;
   }
}

void coordinate2dec()
{
  String lat_degree="";
    for(i=17;i<=18;i++)         
      lat_degree+=gpsString[i];
      
  String lat_minut="";
     for(i=18;i<=19;i++)         
      lat_minut+=gpsString[i];
     for(i=21;i<=22;i++)         
      lat_minut+=gpsString[i];


       
  String log_degree="";
    for(i=29;i<=31;i++)
      log_degree+=gpsString[i];
  String log_minut="";
    for(i=32;i<=33;i++)
      log_minut+=gpsString[i];
    for(i=35;i<=36;i++)
      log_minut+=gpsString[i];

      
    Speed="";
    for(i=42;i<45;i++)          //extract longitude from string
      Speed+=gpsString[i];
      
     float minut= lat_minut.toFloat();
     minut=minut/60;
     float degree=lat_degree.toFloat();
     latitude=degree+minut;
     
     minut= log_minut.toFloat();
     minut=minut/60;
     degree=log_degree.toFloat();
     logitude=degree+minut;
}

/*
void coordinate2dec()
{
  String lat_degree="";
    for(i=19;i<=20;i++)         
      lat_degree+=gpsString[i];
      
  String lat_minut="";
     for(i=21;i<=22;i++)         
      lat_minut+=gpsString[i];
     for(i=24;i<=25;i++)         
      lat_minut+=gpsString[i];


       
  String log_degree="";
    for(i=32;i<=34;i++)
      log_degree+=gpsString[i];
  String log_minut="";
    for(i=35;i<=36;i++)
      log_minut+=gpsString[i];
    for(i=38;i<=39;i++)
      log_minut+=gpsString[i];

      
    Speed="";
    for(i=45;i<48;i++)          //extract longitude from string
      Speed+=gpsString[i];
      
     float minut= lat_minut.toFloat();
     minut=minut/60;
     float degree=lat_degree.toFloat();
     latitude=degree+minut;
     
     minut= log_minut.toFloat();
     minut=minut/60;
     degree=log_degree.toFloat();
     logitude=degree+minut;
}
*/
void gps_convert()
{
if(gps_status)
  {
  //Serial.println(gpsString);

  if(gpsString[0] == '$' && gpsString[1] == 'G' && gpsString[2] == 'P' && gpsString[3] == 'R' && gpsString[4] == 'M' && gpsString[5] == 'C')
    {
     // Serial.println("Don11111111111111111111111111111111111111111111111111111\r\n");      
    //  Serial.write(gpsString[18]);Serial.write(gpsString[19]);Serial.write(gpsString[20]);Serial.write(gpsString[21]);Serial.write(gpsString[22]);
     //lcd.setCursor(0,0);
     for(ii=0;ii<9;ii++)
       {
        //lcd.write(gpsString[19+ii]);    
        msg1[ii] = gpsString[19+ii];
        //Serial.write(msg1[ii]);
       }
       //Serial.println("\r\n");
     //lcd.setCursor(0,1);
      for(ii=0;ii<10;ii++)
       {
        //lcd.write(gpsString[32+ii]);
        msg2[ii] = gpsString[32+ii];    
       // Serial.write(msg2[ii]);
       }

// Serial.println(msg1);
// Serial.println(msg2);

       //lati = (((msg1[2]-48)*100000) +((msg1[3]-48)*10000) + ((msg1[5]-48)*1000) + ((msg1[6]-48)*100) + ((msg1[7]-48)*10) + (msg1[8]-48)); 
       //longi = (((msg2[3]-48)*100000) + ((msg2[4]-48)*10000) + ((msg2[6]-48)*1000) + ((msg2[7]-48)*100) + ((msg2[8]-48)*10) + (msg2[9]-48));

       lati = (((msg1[2]-48)*1000) + ((msg1[3]-48)*100) + ((msg1[5]-48)*10) + (msg1[6]-48)); 
       longi = (((msg2[3]-48)*1000) + ((msg2[4]-48)*100) + ((msg2[6]-48)*10) + (msg2[7]-48));

      // converts(lati);Serial.write("-");
      // converts(longi);Serial.write("\r\n");
       
       lati = (lati/60);  longi = (longi/60);

       lati = (lati*100); longi = (longi*100);
       lati1 = lati;      longi1 = longi;
       
// Serial.write("After ");
  //      converts(lati1);Serial.write("-");
    //   converts(longi1);Serial.write("\r\n");
 

              convlat(lati); convlong(longi);
        finallat[0] = msg1[0];
        finallat[1] = msg1[1];
        finallat[2] = '.';
        finallat[3] = flat[0]; finallat[4] = flat[1];finallat[5] = flat[2];finallat[6] = flat[3];finallat[7] = '\0';


        finallong[0] = msg2[0];
        finallong[1] = msg2[1];
        finallong[2] = msg2[2];
        finallong[3] = '.';
        finallong[4] = flong[0];finallong[5] = flong[1];finallong[6] = flong[2];finallong[7] = flong[3];finallong[8] = '\0'; 

   
    }
  }  
}

 void convlat(unsigned int value)  
      {
             unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;              
      c=c|0x30;
      e=e|0x30; 
    g=g|0x30;              
      h=h|0x30;
   
  // dlcd(a);
//   dlcd(c);dlcd(e); dlcd(g);dlcd(h);//lcddata('A');//lcddata(' ');lcddata(' ');
    
         
               flat[0] = c;
               flat[1] = e;
               flat[2] = g;
             flat[3] = h;


          }

 void convlong(unsigned int value)  
      {
            unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;              
      c=c|0x30;
      e=e|0x30; 
    g=g|0x30;              
      h=h|0x30;
   
  // dlcd(a);
//   dlcd(c);dlcd(e); dlcd(g);dlcd(h);//lcddata('A');//lcddata(' ');lcddata(' ');
    
         
               flong[0] = c;
               flong[1] = e;
               flong[2] = g;
             flong[3] = h;


          }



void gsminit()
{
  Serial.write("AT\r\n");                   okcheck();
  Serial.write("ATE0\r\n");                 okcheck();
  Serial.write("AT+CMGF=1\r\n");            okcheck();
  Serial.write("AT+CNMI=1,2,0,0\r\n");      okcheck();
  Serial.write("AT+CSMP=17,167,0,0\r\n");   okcheck();
    
  lcd.clear();
  lcd.print("SEND MSG STORE");
  lcd.setCursor(0,1);
  lcd.print("MOBILE NUMBER");  
  do{
     rcv = Serial.read();
    }while(rcv != '*');
     readSerial(pastnumber);pastnumber[10] = '\0';
     
     /*
  pastnumber1[0] = pastnumber[0];pastnumber1[1] = pastnumber[1];pastnumber1[2] = pastnumber[2];pastnumber1[3] = pastnumber[3];pastnumber1[4] = pastnumber[4];pastnumber1[5] = pastnumber[5];
  pastnumber1[6] = pastnumber[6];pastnumber1[7] = pastnumber[7];pastnumber1[8] = pastnumber[8];pastnumber1[9] = pastnumber[9];pastnumber1[10] = '\0';
    */
/*
  pastnumber3[0] = pastnumber[20];pastnumber3[1] = pastnumber[21];pastnumber3[2] = pastnumber[22];pastnumber3[3] = pastnumber[23];pastnumber3[4] = pastnumber[24];pastnumber3[5] = pastnumber[25];
  pastnumber3[6] = pastnumber[26];pastnumber3[7] = pastnumber[27];pastnumber3[8] = pastnumber[28];pastnumber3[9] = pastnumber[29];pastnumber3[10] = '\0';
*/
  lcd.clear();
  lcd.print(pastnumber);

      delay(4000);  delay(4000);  
    Serial.write("AT+CMGS=\"");
    Serial.write(pastnumber);
    Serial.write("\"\r\n"); delay(3000);
    Serial.write("Reg\r\n");
    Serial.write(0x1A);    
    delay(4000);  delay(4000);  

}


void converts(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   Serial.write(a);
   Serial.write(c);
   Serial.write(e); 
   Serial.write(g);
   Serial.write(h);
}
void converts1(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   mySerial.write(a);
   mySerial.write(c);
   mySerial.write(e); 
   mySerial.write(g);
   mySerial.write(h);
}

void convertl(unsigned int value)
{
  unsigned int a,b,c,d,e,f,g,h;

      a=value/10000;
      b=value%10000;
      c=b/1000;
      d=b%1000;
      e=d/100;
      f=d%100;
      g=f/10;
      h=f%10;


      a=a|0x30;               
      c=c|0x30;
      e=e|0x30; 
      g=g|0x30;              
      h=h|0x30;
    
     
   //lcd.write(a);
   lcd.write(c);
   lcd.write(e); 
   lcd.write(g);
   lcd.write(h);
}
