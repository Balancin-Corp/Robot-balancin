
## Comandos de directorios

```Bash
cd directorio #Nos mueve en el directorio especificado

#Por ejemplo el siguiente comando me movería al escritorio:
cd C:/users/Francisco/desktop  #En Bash hay que usar /, ya que \ no se lee.
#Si apretamos el TAB mientras escribimos el directorio, nos autocompletará el texto o mostrará todas las coincidencias posibles
```
El . representa el directorio actual, .. el directorio anterior. Por ejemplo, si estamos dentro de una carpeta A en el escritorio, para moverse a escritorio se escribe ../.
Si tenemos una carpeta con espacios "Proyecto PP" por ejemplo, en el Bash se debe 
escribir así: Proyecto\ PP (No confundir con el /, que se usa para subcarpetas)

```Bash
ls directorio #Lista todos los archivos y carpetas en un determinado directorio.

ls -a #Muestra también los archivos ocultos
```

```Bash
pwd #indica el directorio actual
```

```Bash
mkdir NombreDelDirectorio #Crea una carpeta en el directorio  actual
```


## Comandos Git

```Bash
git init #Inicializa un repositorio en el directorio actual
```