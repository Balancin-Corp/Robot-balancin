Para usar el Serialplot es importante saber ciertas cosas 

*No podrás usarlo conjunto al Serial Monitor ya que solo uno de los dos puede tener permiso de lectura

*Obligatoriamente tienes que usar Serial.PrintLn() ya que este modifica los datos a ASCII al puerto serial, además resaltar que si intentas imprimir un entero el grafico no tendrá ningún sentido.

How to install:  https://hackaday.io/project/5334-serialplot-realtime-plotting-software


Configuración de SerialPlot


Para configurar:

![[SerialPlot.png]]
Primero abre el programa.

Después asegurarte que salga el ESP32 con el COM correspondiente. Además los Baudeos del plotter tiene que coincidir con el *Serial..Begin();* para probar el plotter usamos 9600 baudeos y el código mas abajo. 
![[IMPORTANTE ascii.png]]
*IMPORTANTE* Seleccionar en esta sección ASCII de otra manera no funcionara de manera correcta.

![[SerialPlot Graph.png]]
Este fue el resultado al usar el código mostrado abajo, usando un for para que constantemente nos de datos y el SerialPlot pueda graficarlos. Como se puede observar también se puede modificar el ancho, el mínimo y em máximo.   

```cpp
#include <Arduino.h>


int myFunction(int, int);

  

void setup() {

Serial.begin(9600);

}

  

void loop() {

for (int i = 0; i < 500 ; i++)

{

  Serial.println(i);

  delayMicroseconds(100);

}

for (int i = 500; i > 0 ; i--)

{

  Serial.println(i);

  delayMicroseconds(100);

}

}
```