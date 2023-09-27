# computacion-grafica-visualizacion
Este repositorio es un espacio dedicado a la recopilación y gestión de archivos y recursos relacionados con mi asignatura de Computación Gráfica y Visualización.

# Recomendaciones
Desde mi experiencia personal, he encontrado que llevar a cabo estas prácticas es considerablemente más efectivo en un entorno Linux. 
Aunque teóricamente es posible realizarlas en Windows mediante la instalación de Windows Subsystem for Linux (WSL), en mi caso, después de haber intentado esta configuración, me encontré con dificultades persistentes que afectaron mi capacidad de trabajo. 

En el contexto de la programación, el consejo ofrecido por el profesor fue optar por el uso de Visual Studio Code (VS Code), para instalarlo podemos ejecutar los siguientes comandos:
- `sudo apt update && sudo apt install software-properties-common apt-transport-https wget`
- `wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -`
- `sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"`
- `sudo apt install code`

# Instalación y configuración
Para las prácticas es preciso instalar las siguientes librerías:
- `freeglut3`
- `freeglut3-dev`

En algunas distribuciones antiguas es también necesario instalar:
- `libgl1-mesa-dev`

Para ellos en un entorno linux moderno será tan sencillo como ejecutar los comandos correspodientes al control de paquetes.

`apt install freeglut3 freeglut3-dev`

Opcionalmente, se recomienda el crear un archivo makefile que facilite la compilación de los ejemplos.El contenido podría ser similar al siguiente:
```
LIBS = -lGL -lGLU -lglut

ejemplo : ejemplo.c
	  gcc -o $@ $< $LIBS
```
En otro caso será necesario escribir la siguiente linea de cada vez que se necesite compilar:

`gcc ejemplo.c -o ejemplo  -lGL -lGLU -lglut`
