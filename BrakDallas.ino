
//Питание на далласы идет через шим Т1- D3, Т2 - D9
//Данные с термодатчиков подключены Т1- D5, Т2 - D6
//Контроль питания датчиков, аналоговые входы Т1- A0, Т2 - A1

// версия 08 отличается переходом на внешний для процессора источник опорного напряжения.
// использую 3,3В от усб микросхемы как опорное, подав его на VREF вход.
// использовать переключение analogReference(EXTERNAL)



#include <DS18B20.h>

//-----------------------------------------Переменные и константы
DS18B20 ds1(5);                             // pin D5 Т1 порт 
DS18B20 ds2(6);                             // pin D6 Т2 порт 

#define LedBoard 13                         // pin D13 Светодиод на плате
#define YLed_T1 2                           // pin D2 Желт Т1
#define BLed_T1 4                           // pin D4 Синий Т1
#define YLed_T2 8                           // pin D8 Желт Т2
#define BLed_T2 7                           // pin D7 Синий Т2

#define Pow_T1 3                            // pin D3 Питание Т1 шим. 
#define Pow_T2 9                            // pin D9 Питание Т2 шим. 

#define U_T1 0                              // pin А0 Напряжение на Т1
#define U_T2 1                              // pin А1 Напряжение на Т2

//#define VDD 4.67                            // (В) опорное напряжение (питание процессора)
#define VREF  3.3                           // вольты. Опорное напряжение от USB моста

#define Pow_T_start 200                     // максимальное значение ШИМ. Выставляется в начале теста.  Соотв. 2.98В
#define Pow_T1_end 130                      // минимальное значение ШИМ. Конец теста.                   Соотв. 1.93В

#define volU_T_porog 2.30                   // (В) пороговое напряжение принятия решения о качестве датчика ! уточнить !!! очень низкое

int Pow_T1_Vol = 255;                       // Переменная, кот хранит ШИМ для питания термодатчика Т1
int Pow_T2_Vol = 255;                       // Переменная, кот хранит ШИМ для питания термодатчика Т2

float volU_T1;
float volU_T2;
float zamerT;
//-------------------------------------------

//------------------------------------------Предварительные установки
void setup() {

  /* переключение на внешний ИОН 3.3V от USB */
  analogReference(EXTERNAL);

  pinMode(LedBoard, OUTPUT);
  pinMode(YLed_T1, OUTPUT);
  pinMode(BLed_T1, OUTPUT);
  pinMode(YLed_T2, OUTPUT);
  pinMode(BLed_T2, OUTPUT);

  pinMode(Pow_T1, OUTPUT);
  pinMode(Pow_T2, OUTPUT);

  pinMode(U_T1, INPUT);
  pinMode(U_T2, INPUT);

  //digitalWrite(Pow_T1, HIGH);                   // включим питание термодатчику Т1
  //digitalWrite(Pow_T2, HIGH);                   // включим питание термодатчику Т2

  Pow_T1_Vol = Pow_T_start;
  Pow_T2_Vol = Pow_T_start;
  analogWrite(Pow_T1, Pow_T1_Vol);                // включим питание термодатчику Т1
  analogWrite(Pow_T2, Pow_T2_Vol);                // включим питание термодатчику Т2
    
  Serial.begin(9600);                           // start serial port
  delay(4000);                                  // при запуске видимо емкости не заряжены и напряжение низкое и термодатчики дают срыв
  Serial.println();                             // ? одна пустая строка организует начало вывода на экран монитора порта. Иначе первая строка сбивается ?
  Serial.print("Необходимо подключить внешний ИОН 3.3В");  
  Serial.println(); 
}
//-------------------------------------------

// ------------------------------------------Функция замера температуры
float tDatchika(byte nomerDatchika){          
  float z;
  switch (nomerDatchika) {
    case 1:
      z = -127;                                  // обозначим отсутствие ответа от датчика как -127С
      while (ds1.selectNext()) {
      z = ds1.getTempC();                        // запрос температуры Т1
    } 
      break;
    case 2:
      z = -127;                                  // обозначим отсутствие ответа от датчика как -127С
      while (ds2.selectNext()) {
      z = ds2.getTempC();                        // запрос температуры Т2
    } 
      break;
    default: 
      z = -127;
  }
  return z;
}
// ------------------------------------------

// ------------------------------------------Основной цикл
void loop() {
 


  zamerT = tDatchika(1);                                  //------------------------------ замер Т1  
  
  volU_T1 = ((float) analogRead(U_T1)*VREF)/1024.0;          // замер напряжения питания Т1  
  Serial.print("U(T1):");
  Serial.print(volU_T1);                                  // печать напряжения питания Т1
  
  if (zamerT < 10){                                       // плохой замер, в том числе отсутствие датчика
      Serial.print("\t");                                 // печать табулятора      
      Serial.print("нет Т1  ");
      digitalWrite(YLed_T1, HIGH); 
      digitalWrite(BLed_T1, HIGH);
  }
  else {                                                  // действительный замер
      Serial.print("\t");                                 // печать табулятора
      Serial.print("T1:");
      Serial.print(zamerT);
      digitalWrite(YLed_T1, LOW); 
      digitalWrite(BLed_T1, LOW);      
  }



  zamerT = tDatchika(2);                                  //------------------------------ замер Т2  
  
  volU_T2 = ((float) analogRead(U_T2)*VREF)/1024.0;          // замер напряжения питания Т2  
  Serial.print("\t");                                     // печать табулятора   
  Serial.print("U(T2):");
  Serial.print(volU_T2);                                  // печать напряжения питания Т2
  
  if (zamerT == -127){
      Serial.print("\t");                                 // печать табулятора      
      Serial.print("нет Т2  ");
      digitalWrite(YLed_T2, HIGH); 
      digitalWrite(BLed_T2, HIGH);
  }
  else {                                                  // действительный замер
      Serial.print("\t");                                 // печать табулятора
      Serial.print("T2:");
      Serial.print(zamerT);
      digitalWrite(YLed_T2, LOW); 
      digitalWrite(BLed_T2, LOW);      
  }




  Serial.print("\t");                                      // печать табулятора  
  Serial.print("Шим:");
  Serial.print(Pow_T2_Vol);                                // печать напряжения питания Т1



  Serial.println(); // закончить строку

  
//  if (Pow_T1_Vol > 0) Pow_T1_Vol-- ;
//  if (Pow_T2_Vol > 0) Pow_T2_Vol-- ;

  Pow_T1_Vol = Pow_T1_Vol - 5 ;
  if (Pow_T1_Vol < Pow_T1_end){
    Pow_T1_Vol = Pow_T_start;
  }
  analogWrite(Pow_T1, Pow_T1_Vol);
  //delay(1000);                                  // при резком увеличении напряжения емкость не успевает зарядиться
  
  Pow_T2_Vol = Pow_T2_Vol - 5 ;
  if (Pow_T2_Vol < Pow_T1_end){
    Pow_T2_Vol = Pow_T_start;
  }
  analogWrite(Pow_T2, Pow_T2_Vol);
  delay(1000);    // при резком увеличении напряжения емкость не успевает зарядиться  

  
  delay(100);
  
}
