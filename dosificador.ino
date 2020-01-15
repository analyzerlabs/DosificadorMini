#include <Wire.h>
#include "RTClib.h"
int dia,mes,anio,hora,minuto,segundo; 
int hora_aux,minuto_aux,segundo_aux,segundo_led;
RTC_DS1307 rtc;
int state=0;
char daysOfTheWeek[7][12] = {"Domingo","Lunes", "Martes", "Miercoles", 
                              "Jueves","Viernes", "Sabado"};
int LedVerde = 15,LedAzul = 2,LedVerde2=5;
int LedRojo = 18,LedAzul2 = 4,LedVerde3=19;
void setup () {
  pinMode(LedVerde,OUTPUT);
  pinMode(LedVerde2,OUTPUT);
  pinMode(LedVerde3,OUTPUT);
  pinMode(LedRojo,OUTPUT);
  pinMode(LedAzul,OUTPUT);
  pinMode(27,OUTPUT);
  digitalWrite(LedAzul,LOW);
  digitalWrite(LedRojo,LOW);
  digitalWrite(27,HIGH);
  Serial.begin(115200);
  if (! rtc.begin()) {
      Serial.println("Couldn't find RTC");
      while (1);
  }
  getTimeDs1307();
  hora_aux = hora;
  minuto_aux = minuto;
  segundo_aux = segundo;
  segundo_led = segundo;
  digitalWrite(LedRojo,HIGH);
  while(true){  
  digitalWrite(27,LOW);
  getTimeDs1307();
  if(minuto - minuto_aux == 2 && segundo_aux == segundo){
          digitalWrite(27,HIGH);
          break;
      }
  }
  digitalWrite(LedVerde,HIGH);
  digitalWrite(LedVerde2,HIGH);
  digitalWrite(LedVerde3,HIGH);
  digitalWrite(LedRojo,LOW);
}

void loop () {
    printDs1307Time();
    getTimeDs1307();
    if(hora%24 == 0 && minuto == 45){
        dosificar(4000);
    }
}
int desvanecer=0;
int j =1;

void dosificar(int volumen){
    digitalWrite(LedAzul,HIGH);  
    digitalWrite(LedVerde3,HIGH);  
    int t = 8*volumen/100;
    hora_aux = hora;
    minuto_aux = minuto;
    segundo_aux = segundo;
    segundo_led = segundo;
    while(true){
        if(segundo - segundo_led == 1 || segundo - segundo_led == 59){
            segundo_led = segundo;
            state = 1 - state;
            digitalWrite(LedVerde , state);
            digitalWrite(LedVerde2, state);         
        }
        digitalWrite(27,LOW);
        getTimeDs1307();
        DateTime now = rtc.now();
        if(minuto - minuto_aux == t && segundo_aux == segundo){
            digitalWrite(27,HIGH);
            break;
        }
    }
    digitalWrite(LedAzul,LOW);  
    digitalWrite(LedVerde3,LOW);  
}

void getTimeDs1307(){
    DateTime now = rtc.now();
    dia= now.day();
    mes= now.month();
    anio = now.year();
    hora = now.hour();
    minuto = now.minute();  
    segundo = now.second();
}

void printDs1307Time(){
    delay(3000);
    DateTime now = rtc.now();
    Serial.print(now.day(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.year(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}