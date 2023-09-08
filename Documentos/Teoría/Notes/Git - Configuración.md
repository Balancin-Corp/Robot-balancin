Esto es sacado de este [video](https://youtu.be/VdGzPZ31ts8?si=H7cgsEcMisoGnKM1&t=535)
Para comenzar, primero hay que escribir "git --version" en el bash de Git:

```Bash
git --version
```
![[Pasted image 20230907172349.png]]
Esto nos permite saber si el programa se instaló correctamente. Luego hay que poner los siguientes dos comandos:

```Bash
git config --global user.name "Tu nombre"
git config --global user.email tuEmail
```
(El mail va sin "")
Por ejemplo, 
```Bash
git config --global user.name "Iglesias Francisco"
git config --global user.email franviglesias@gmail.com
```
Para añadir a VSCode como el editor por defecto, ponemos el siguiente comando:
```Bash
git config --global core.editor "code --wait"

El --wait es para que el Bash se quede esperando hasta que cerremos el archivo abierto.
```
Para ver nuestro archivo de configuración global, escribimos
```Bash
git config --global -e
```
Y se abrirá dentro de VSCode.

## core.autocrlf

En Windows cada vez que añadamos un salto de línea, se añaden dos caracteres especiales CR (carriage Return) y LF (line feed). En Linux o en Mac, el caracter especial que se agrega es solamente LF.
Por lo tanto, si queremos pasar un texto de Windows a Linux, debemos borrar el caracter CR, y de Linux a Windows, debemos agregarlo. **Por lo tanto, la propiedad core.autocrlf debe tener el valor True en Windows y Input en Linux/Mac.**:
```Bash
En Windows:
git config --global core.autocrlf true

En Linux/Mac
git config --global core.autocrlf input
```

Y con esto se termina la configuración básica.
Para ver todas las configuraciones posibles, se puede poner el comando
```Bash
git config -h

Nos entrega un listado de todas las configuraciones
```