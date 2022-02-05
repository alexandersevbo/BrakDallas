//Тестирование двух далласов одновременно при изменяющемся напряжении питания
//Питание на далласы идет через шим Т1- D6, Т2 - D5
//Данные с термодатчиков подключены Т1- D3, Т2 - D2
//Контроль питания датчиков, аналоговые входы Т1- A0, Т2 - A1
//



#include <DS18B20.h>

                                          // ------------------------Переменные и константы
DS18B20 ds1(5);                             // pin Т1 порт D5
DS18B20 ds2(6);                             // pin Т2 порт D6

#define LedBoard 13                         // pin Светодиод на плате
#define YLed_T1 2                           // pin Желт Т1
#define BLed_T1 4                           // pin Синий Т1
#define YLed_T2 8                           // pin Желт Т2
#define BLed_T2 7                           // pin Синий Т2

#define Pow_T1 3                            // pin Питание Т1 шим
#define Pow_T2 9                            // pin Питание Т2 шим

#define U_T1 0                              // pin Напряжение на Т1
#define U_T2 1                              // pin Напряжение на Т2

int Pow_T1_Vol = 255;                       // pin Переменная, кот хранит ШИМ для питания термодатчика Т1
int Pow_T2_Vol = 255;                       // pin Переменная, кот хранит ШИМ для питания термодатчика Т2

float volU_T1;
float volU_T2;
float VDD = 4.67;

float zamerT;
//float zamerT1;
//float zamerT2;



void setup() {                              // ------------------------Предварительные установки

  pinMode(LedBoard, OUTPUT);
  pinMode(YLed_T1, OUTPUT);
  pinMode(BLed_T1, OUTPUT);
  pinMode(YLed_T2, OUTPUT);
  pinMode(BLed_T2, OUTPUT);

  pinMode(Pow_T1, OUTPUT);
  pinMode(Pow_T2, OUTPUT);

  pinMode(U_T1, INPUT);
  pinMode(U_T2, INPUT);

digitalWrite(Pow_T1, HIGH);                   // включим питание термодатчику Т1
digitalWrite(Pow_T2, HIGH);                   // включим питание термодатчику Т2
  Serial.begin(9600);                           // start serial port
  delay(1000);                                  // при запуске видимо емкости не заряжены и напряжение низкое и термодатчики дают срыв
  Serial.println();                             // одна пустая строка организует начало вывода на экран монитора порта. Иначе первая строка сбивается
}


float tDatchika(byte nomerDatchika){          // ------------------------Функция замера температуры
  float z;
  switch (nomerDatchika) {
    case 1:
      z = -127;
      while (ds1.selectNext()) {
      z = ds1.getTempC();                        // запрос температуры Т1
    } 
      break;
    case 2:
      z = -127;
      while (ds2.selectNext()) {
      z = ds2.getTempC();                        // запрос температуры Т2
    } 
      break;
    default: 
      z = -127;
  }
  return z;
}

  


void loop() {                                  // ------------------------Основной цикл

  delay(1000);
  zamerT = tDatchika(1);
  if (zamerT == 0){
      Serial.println("нет датчика");
      digitalWrite(YLed_T1, HIGH); 
      digitalWrite(BLed_T1, HIGH);
  }
  else {
      Serial.println(zamerT);
      digitalWrite(YLed_T1, LOW); 
      digitalWrite(BLed_T1, LOW);      
  }
  



  
//    Serial.print("T1: ");
//    Serial.print(ds1.getTempC());           
//
//
//
// 
//
//  
//  Serial.print("\t");                         // печать табулятора
//  Serial.print("U(T1): ");
//  volU_T1 = (float) analogRead(U_T1)*VDD/1024.0;
//  Serial.print(volU_T1);             // замер напряжения питания Т1
//  Serial.print("\t");                         // печать табулятора
//
//  while (ds2.selectNext()) {
//    Serial.print("T2: ");
//    Serial.print(ds2.getTempC());           // запрос температуры Т2
//  }
//
//  Serial.print("\t");                     // печать табулятора
//  Serial.print("U(T2): ");
//  volU_T2 = (float) analogRead(U_T2)*VDD/1024.0;
//  Serial.print(volU_T2);             // замер напряжения питания Т2
//  
//  Serial.println(); // закончить строку
//
//  
////  if (Pow_T1_Vol > 0) Pow_T1_Vol-- ;
////  if (Pow_T2_Vol > 0) Pow_T2_Vol-- ;
//
//
//  Pow_T1_Vol = Pow_T1_Vol - 5 ;
//  if (Pow_T1_Vol < 0){
//    Pow_T1_Vol = 255;
//  }
//  analogWrite(Pow_T1, Pow_T1_Vol);
//  
//  Pow_T2_Vol = Pow_T2_Vol - 5 ;
//  if (Pow_T2_Vol < 0){
//    Pow_T2_Vol = 255;
//  }
//  analogWrite(Pow_T2, Pow_T2_Vol);
//  
//  digitalWrite(LedBoard, LOW);                   // ОТключим LedBoard
//  delay(1000);
//  digitalWrite(LedBoard, HIGH);                  // Включим LedBoard
}
