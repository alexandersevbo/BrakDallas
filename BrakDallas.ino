//Тестирование двух далласов одновременно при изменяющемся напряжении питания
//Питание на далласы идет через шим Т1- D6, Т2 - D5
//Данные с термодатчиков подключены Т1- D3, Т2 - D2
//Контроль питания датчиков, аналоговые входы Т1- A0, Т2 - A1
//



#include <DS18B20.h>

DS18B20 ds1(3);                             // pin Т1 порт D3
DS18B20 ds2(2);                             // pin Т2 порт D2

#define LedBoard 13                         // pin Светодиод на плате
#define YLed_T1 9                           // pin Желт Т1
#define BLed_T1 4                           // pin Синий Т1
#define YLed_T2 8                           // pin Желт Т2
#define BLed_T2 7                           // pin Синий Т2

#define Pow_T1 6                            // pin Питание Т1
#define Pow_T2 5                            // pin Питание Т2

#define U_T1 0                              // pin Напряжение на Т1
#define U_T2 1                              // pin Напряжение на Т2

int Pow_T1_Vol = 255;                       // pin Переменная, кот хранит ШИМ для питания термодатчика Т1
int Pow_T2_Vol = 255;                       // pin Переменная, кот хранит ШИМ для питания термодатчика Т2

float volU_T1;
float volU_T2;
float VDD = 4.7;

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
  delay(1000);                                  // при запуске видимо емкости не заряжены и напряжение низкое и термодатчики дают срыв
  Serial.println();                             // одна пустая строка организует начало вывода на экран монитора порта. Иначе первая строка сбивается


  
}

void loop() {
  //delay(100);
  //Порядок имеет значение
  //При замере температуры разряжается емкость, поэтому лучше измерять питание датчика ДО замера т-ры
  //
  Serial.print("U(T1):");
  volU_T1 = (float) analogRead(U_T1)*VDD/1024.0;
  Serial.print(volU_T1);             // замер напряжения питания Т1
  Serial.print("\t");                         // печать табулятора
  while (ds1.selectNext()) {
    Serial.print("T1:");
    Serial.print(ds1.getTempC());           // запрос температуры Т1
  }
  Serial.print("\t");                         // печать табулятора
  Serial.print("U(T2):");
  volU_T2 = (float) analogRead(U_T2)*VDD/1024.0;
  Serial.print(volU_T2);             // замер напряжения питания Т2
  while (ds2.selectNext()) {
    Serial.print("\t");                     // печать табулятора
    Serial.print("T2:");
    Serial.print(ds2.getTempC());           // запрос температуры Т2
  }


  Serial.println(); // закончить строку

  
//  if (Pow_T1_Vol > 0) Pow_T1_Vol-- ;
//  if (Pow_T2_Vol > 0) Pow_T2_Vol-- ;

  Pow_T1_Vol = Pow_T1_Vol - 5 ;
  if (Pow_T1_Vol < 0){
    Pow_T1_Vol = 255;
    //delay(500);                                  // при запуске видимо емкости не заряжены и напряжение низкое и термодатчики дают срыв
  }
  analogWrite(Pow_T1, Pow_T1_Vol);

  
  Pow_T2_Vol = Pow_T2_Vol - 5 ;
  if (Pow_T2_Vol < 0){
    Pow_T2_Vol = 255;
    //delay(500);                                  // при запуске видимо емкости не заряжены и напряжение низкое и термодатчики дают срыв
  }
  analogWrite(Pow_T2, Pow_T2_Vol);
  //delay(10000);
}
