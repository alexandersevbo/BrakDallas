//Питание на далласы идет через шим Т1- D6, Т2 - D5
//Данные с термодатчиков подключены Т1- D3, Т2 - D2
//Контроль питания датчиков, аналоговые входы Т1- A0, Т2 - A1
//


#include <OneWire.h>                        // Подключаем библиотеку OneWire
#include <DallasTemperature.h>              // Подключаем библиотеку DallasTempature


// ---------Порты---

#define ONE_WIRE_BUS 5                      // Данные Т1 
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#define LedBoard 13                         // pin D13 Светодиод на плате
#define YLed_T1 2                           // pin D2 Желт Т1
#define BLed_T1 4                           // pin D4 Синий Т1
#define YLed_T2 8                           // pin D8 Желт Т2
#define BLed_T2 7                           // pin D7 Синий Т2

#define Pow_T1 3                            // pin D3 Питание Т1 шим. 
#define Pow_T2 9                            // pin D9 Питание Т2 шим. 

#define U_T1 0                              // pin А0 Напряжение на Т1
#define U_T2 1                              // pin А1 Напряжение на Т2

#define VDD 4.67                            // (В) опорное напряжение (питание процессора)

#define Pow_T_start 190                     // максимальное значение ШИМ. Выставляется в начале теста.  Соотв. 2.98В
#define Pow_T1_end 130                      // минимальное значение ШИМ. Конец теста.                   Соотв. 1.93В

#define volU_T_porog 2.30                   // (В) пороговое напряжение принятия решения о качестве датчика ! уточнить !!! очень низкое

int Pow_T1_Vol = 255;                       // Переменная, кот хранит ШИМ для питания термодатчика Т1
int Pow_T2_Vol = 255;                       // Переменная, кот хранит ШИМ для питания термодатчика Т2

float volU_T1;
float volU_T2;
float zamerT;
// ---------Порты---







void setup() {
  // настройка портов
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
  analogWrite(Pow_T1, Pow_T1_Vol);                // включим питание термодатчику Т1
  analogWrite(Pow_T2, Pow_T2_Vol);                // включим питание термодатчику Т2


  // start serial port
  Serial.begin(9600);
  Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();

  
}






// the loop function runs over and over again forever
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);  
  digitalWrite(YLed_T1, HIGH);
  digitalWrite(BLed_T1, HIGH);
  digitalWrite(YLed_T2, HIGH);
  digitalWrite(BLed_T2, HIGH);



  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  delay(1000);                       // wait for a second  
  
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  Serial.print("Temperature for the device 1 (index 0) is: ");
  Serial.println(sensors.getTempCByIndex(0));  

  
  delay(1000);                       // wait for a second

  
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(YLed_T1, LOW);
  digitalWrite(BLed_T1, LOW);
  digitalWrite(YLed_T2, LOW);
  digitalWrite(BLed_T2, LOW);
  
  delay(1000);                       // wait for a second





  
}
