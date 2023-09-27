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
