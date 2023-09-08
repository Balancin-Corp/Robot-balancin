ver este [video](https://youtu.be/VdGzPZ31ts8?si=axucHtKxb9IE-KD0&t=1459)


```Bash
git status #Nos muestra el estado actual de nuestro repositorio
```

```Bash
git add <file> #git por defecto no sigue los archivos que coloquemos dentro del proyecto, por lo que tenemos que seleccionarlos. Este comando añade el cambio hecho sobre un archivo a Stage.

#Ejemplos
git add . #Añade todos los archivos de la carpeta. Es una mala práctica.
git add ./<subcarpeta> #Añade todos los archivosen una subcarpeta.
git add *.txt* #Añade todos los archivos txt
#etc..

```
## Commit
```Bash
git commit -m "Comentario"
o
git commit #En este caso se abre un archivo de texto en el editor, donde nos dejar+a escribir el comentario.
```

## Como eliminar un archivo

Si tenemos un archivo en un branch y queremos eliminarlo, primero debemos borrarlo de la carpeta:
```Bash
rm <archivo>
```
Y luego poner:
```Bash
git add <archivo>
```

Esto lo que va a hacer es guardar el cambio hecho sobre ese archivo (En este caso, borrarlo), y cuando hagamos el commit se borrará exitosamente.
Otra forma es usando el siguiente comando:
```Bash
git rm <archivo>
```

## Como revertir un cambio en la etapa de Stage

[video]()
Si queremos revertir un cambio hecho en Stage, podemos escribir:
```Bash
git restore --staged <archivo>
```
Esto elimina el cambio en stage, pero no nos restaura los cambios. Para restaurarlo escribimos:
```Bash
git restore <archivo>
```
Si no usamos el restore, el archivo nos quedaría borrado en la carpeta, pero al actualizar el branch 

## Como cambiar el nombre de un archivo

[video](https://youtu.be/VdGzPZ31ts8?si=ggjobz74vyICryKb&t=2465)
Supongamos que queremos cambiar archivo1.txt a archivo.txt. Entonces podriamos escribir

```Bash
mv archivo1.txt archivo.txt
```
Y para añadir el cambio a stage, 
```bash
git add archivo1.txt archivo.txt
```
Esto guardaría dos cambios: que se borró archivo1.txt y que se creó archivo.txt. Pero hay una instrucción de git que hace lo mismo:
```Bash
git mv archivo1
```

## Como ignorar archivos en el commit

[video](https://youtu.be/VdGzPZ31ts8?si=mRFjWsaVM48h7pHL&t=2603)

## Un mejor git status
[video](https://youtu.be/VdGzPZ31ts8?si=I0Nw6JrxmpiKbXVH&t=2799)
git status nos da mucha información, como posibles comandos sugerencias, en qué branch estamos. El comando
```Bash
git status -s
```
Únicamente nos da los cambios en stage e indica si están trackeados o no y de qué tipo son (modificados, creados, renombrados, etc...).

## Visualizando los cambios
[video](https://youtu.be/VdGzPZ31ts8?si=5mbds9xLS1i5SWl4&t=2977)
Para ver los cambios realizados, podemos usar el comando
```Bash
git diff
```
Nos muestra todos los cambios no añadidos a stage en cada archivo.
```Bash
git diff --staged #Nos muestra todos los cambios en staged
```

## Viendo el historial

[video](https://youtu.be/VdGzPZ31ts8?si=9MtH8t-yYHwCEpSh&t=3161)

```Bash
git log #Nos muestra quienes realizaron cada commit
```

```Bash
git log --online # Nos muestra el historial con un pequeño hash, el cual sirve como identificador de ese commit. Un número único con el cual se va identificar ese commit dentro de nusetro registro en git.
```

## Ramas en git o branches

```Bash
git branch #Nos dice en qué rama nos encontramos
```
```Bash
git checkout -b "BranchName" #Crea una rama con el nombre especificado y nos lleva a ella.
git checkout "BranchName" #Nos mueve a la rama especificada

git brach -d <BranchName> "Borra la branch del repositorio"

```
Para añadir los cambios de una rama B a una rama A, debemos, dentro de la rama A, escribir
```Bash
git merge "ramaB"
```

## Conectando con Github

[Video](https://youtu.be/VdGzPZ31ts8?si=XUAsZxxxjLtsyRRb&t=3639)

Para trabajar desde un repositorio de Github, primero se debe crear un repositorio git:
```Bash
#Seleccionar la carpeta donde guardarlo
git init
git remote add origin https://github.com/Balancin-corp/Robot-balancin.git
git pull origin master # Carga la rama principal en tu copia local
git pull origin <rama1> # Carga la rama1 en tu copia local

git push origin <rama1> #Carga la rama1 de tu copia local a github.


# Con los siguientes comandos se puede añadir o actualizar una rama en 
```