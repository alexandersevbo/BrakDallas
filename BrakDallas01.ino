//Тестирование двух далласов одновременно при изменяющемся напряжении питания
//Питание на далласы идет через шим Т1- D6, Т2 - D5
//Данные с термодатчиков подключены Т1- D3, Т2 - D2
//Контроль питания датчиков, аналоговые входы Т1- A0, Т2 - A1
//


#include <OneWire.h>                        // Подключаем библиотеку OneWire
#include <DallasTemperature.h>              // Подключаем библиотеку DallasTempature


// ---------Порты---

#define ONE_WIRE_BUS 3                      // Данные Т2 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define LedBoard 13                         // Светодиод на плате
#define YLed_T1 9                           // Желт Т1
#define BLed_T1 4                           // Синий Т1
#define YLed_T2 8                           // Желт Т2
#define BLed_T2 7                           // Синий Т2

#define Pow_T1 6                            // Питание Т1
#define Pow_T2 5                            // Питание Т2

#define U_T1 0                              // Напряжение на Т1
#define U_T2 1                              // Напряжение на Т2
// ---------Порты---




// ---------Переменные---
int count1 = 300;

float temp = 0;

// ---------Переменные---


void setup() {
  // настройка портов
  pinMode(LedBoard, OUTPUT);
  pinMode(YLed_T1, OUTPUT);
  pinMode(BLed_T1, OUTPUT);
  pinMode(YLed_T2, OUTPUT);
  pinMode(BLed_T2, OUTPUT);

  pinMode(Pow_T1, OUTPUT);
  pinMode(Pow_T2, OUTPUT);

 // pinMode(U_T1, INPUT);
 // pinMode(U_T2, INPUT);  

  digitalWrite(Pow_T1, HIGH);                   // включим питание термодатчику Т1
  digitalWrite(Pow_T2, HIGH);                   // включим питание термодатчику Т2


  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();


}






// the loop function runs over and over again forever
void loop() {

  
  delay(100);                       // wait for a second


      TempSend();


  
}

// Функция отправки показаний с термодатчика
void TempSend(){
  if (count1==0)
  {
  sensors.requestTemperatures();   // от датчика получаем значение температуры
  float temp = sensors.getTempCByIndex(0);
  //client.publish("sevbodacha/ds18b20",String(temp)); // отправляем в топик для термодатчика значение температуры
  Serial.println(temp);
  count1 = 300;  // пауза меду отправками значений температуры  коло 3 секунд
  }
  count1--; 
  delay(10);  
}
