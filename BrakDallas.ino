//Тестирование двух далласов одновременно при изменяющемся напряжении питания
//Питание на далласы идет через шим Т1- D6, Т2 - D5
//Данные с термодатчиков подключены Т1- D3, Т2 - D2
//Контроль питания датчиков, аналоговые входы Т1- A0, Т2 - A1
//Переставил порты, т.к. возможно для шима выбраны неудачные

//Работающая версия. Прогоняет два датчика синхронно по всему диапазону и выводит в порт



#include <DS18B20.h>

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

void setup() {

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
  delay(4000);                                  // при запуске видимо емкости не заряжены и напряжение низкое и термодатчики дают срыв
  Serial.println();                             // одна пустая строка организует начало вывода на экран монитора порта. Иначе первая строка сбивается


  
}

void loop() {
  //delay(100);
  //Порядок имеет значение
  //При замере температуры разряжается емкость, поэтому лучше измерять питание датчика ДО замера т-ры НАОБОРОТ!
  //

  

  
  while (ds1.selectNext()) {
    Serial.print("T1:");
    Serial.print(ds1.getTempC());           // запрос температуры Т1
  }
  volU_T1 = (float) analogRead(U_T1)*VDD/1024.0;// замер напряжения питания Т1  
  Serial.print("\t");                         // печать табулятора
  Serial.print("U(T1):");
  Serial.print(volU_T1);                      // печать напряжения питания Т1

  while (ds2.selectNext()) {
    Serial.print("\t");                     // печать табулятора
    Serial.print("T2:");
    Serial.print(ds2.getTempC());           // запрос температуры Т2
  }
  volU_T2 = (float) analogRead(U_T2)*VDD/1024.0;// замер напряжения питания Т2 
  Serial.print("\t");                         // печать табулятора  
  Serial.print("U(T2):");
  Serial.print(volU_T2);                      // печать напряжения питания Т2

  Serial.print("\t");                         // печать табулятора  
  Serial.print("Шим:");
  Serial.print(Pow_T2_Vol);                      // печать напряжения питания Т1



  Serial.println(); // закончить строку

  
//  if (Pow_T1_Vol > 0) Pow_T1_Vol-- ;
//  if (Pow_T2_Vol > 0) Pow_T2_Vol-- ;

  Pow_T1_Vol = Pow_T1_Vol - 5 ;
  if (Pow_T1_Vol < 0){
    Pow_T1_Vol = 255;
  }
  analogWrite(Pow_T1, Pow_T1_Vol);
  //delay(1000);                                  // при резком увеличении напряжения емкость не успевает зарядиться
  
  Pow_T2_Vol = Pow_T2_Vol - 5 ;
  if (Pow_T2_Vol < 0){
    Pow_T2_Vol = 255;
  delay(10000);
  }
  analogWrite(Pow_T2, Pow_T2_Vol);
  //delay(1000);    // при резком увеличении напряжения емкость не успевает зарядиться  

  
  delay(1000);
  
}
