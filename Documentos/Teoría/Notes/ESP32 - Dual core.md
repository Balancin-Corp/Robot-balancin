Created: 2023-09-08 10:18

Si corremos este programa en el ESP32, es posible ver que setup y loop corren en el núcleo 1.
```cpp
void setup() {
  Serial.begin(115200);
  Serial.print("setup() running on core ");
  Serial.println(xPortGetCoreID());
}

void loop() {
  Serial.print("loop() running on core ");
  Serial.println(xPortGetCoreID());
```
En general, el framework de Arduino hace que todas las tareas corran en el primer núcleo por defecto. Pero es posible correr varias tareas en paralelo independientemente. 
Para eso, primero hay que crear un TaskHandle:
```cpp
//Vamos a crear una tarea en el núcleo 0.
TaskHandle_t task1
TaskHandl_t task2

```
Luego, en setup escribimos:
```cpp
xTaskCreatePinnedToCore(
	Task1Code, // Función para implementar la tarea: El bloque de código que correrá la tarea.
	"Task1", //Nombre de la tarea
	10000, //Tamaño del stack en palabras (word: 16 bits.) (La memoria que se le asigna al bloque de función)
	NULL, //Parametro de entrada de la tarea
	0, //Prioridad de la tarea
	&Task1, //TaskHandle
	0 //Núcleo en el que correrá la tarea.
);

```
word: 16 bits. [Ver](https://www.arduino.cc/reference/en/language/variables/data-types/word/)

Luego, podemos definir la función de la tarea:
```cpp
void Task1code (void * pvParameters) {
	
}
```

Para eliminar la tarea escribimos:
```cpp
vTaskDelete(Task1)
```

Por ejemplo, el siguiente código crea dos tareas en núcleos distintos, una que parpadea un led cada 1000ms y otra que parpadea otro led cada 700ms.
```cpp
TaskHandle_t Task1;
TaskHandle_t Task2;

// LED pins
const int led1 = 2;
const int led2 = 4;

void setup() {
  Serial.begin(115200); 
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    Task1code,   /* Task function. */
                    "Task1",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task1,      /* Task handle to keep track of created task */
                    0);          /* pin task to core 0 */                  
  delay(500); 

  //create a task that will be executed in the Task2code() function, with priority 1 and executed on core 1
  xTaskCreatePinnedToCore(
                    Task2code,   /* Task function. */
                    "Task2",     /* name of task. */
                    10000,       /* Stack size of task */
                    NULL,        /* parameter of the task */
                    1,           /* priority of the task */
                    &Task2,      /* Task handle to keep track of created task */
                    1);          /* pin task to core 1 */
    delay(500); 
}

//Task1code: blinks an LED every 1000 ms
void Task1code( void * pvParameters ){
  Serial.print("Task1 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led1, HIGH);
    delay(1000);
    digitalWrite(led1, LOW);
    delay(1000);
  } 
}

//Task2code: blinks an LED every 700 ms
void Task2code( void * pvParameters ){
  Serial.print("Task2 running on core ");
  Serial.println(xPortGetCoreID());

  for(;;){
    digitalWrite(led2, HIGH);
    delay(700);
    digitalWrite(led2, LOW);
    delay(700);
  }
}

void loop() {
  
}
```

Arduino automáticamente hace que loop() se ejecute en el núcleo1, por lo que perfectamente se podría escribir Task2 en loop().

## References

1. [randomnerdtutorials](https://randomnerdtutorials.com/esp32-dual-core-arduino-ide/)

#note