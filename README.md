<div align="center">

  <img src="assets/udc-logo.png" alt="Logo de la Universidad de A Coruña" width="400" height="auto" />
  <h1>Computación Gráfica y Visualización</h1>
  <p>Repositorio para centralizar apuntes, materiales, ejercicios y recursos relacionados con la materia.</p>
  
<p>
  <a href="https://github.com/Meleagrista/udc-computacion-graficae/graphs/contributors">
    <img src="https://img.shields.io/github/contributors/Meleagrista/udc-computacion-grafica" alt="Contribuidores"/>
  </a>
  <a href="">
    <img src="https://img.shields.io/github/last-commit/Meleagrista/udc-computacion-grafica" alt="Última actualización"/>
  </a>
  <a href="https://github.com/Meleagrista/udc-computacion-grafica/stargazers">
    <img src="https://img.shields.io/github/stars/Meleagrista/udc-computacion-grafica" alt="Favoritos"/>
  </a>
  <a href="https://github.com/Meleagrista/udc-computacion-grafica/watchers">
    <img src="https://img.shields.io/github/watchers/Meleagrista/udc-computacion-grafica" alt="Siguiendo"/>
  </a>
</p>

</div>
<br/>

<a id="top"></a>
<!-- <p align="right"><a href="#top">back to top</a></p> -->

# Table of Contents

## Descripción
La asignatura **Computación Gráfica y Visualización** es una materia optativa del cuarto curso del **Grado en Ingeniería Informática**, de la mención de **Computación**, impartida en el primer cuatrimestre y con una carga de **6 créditos**. 

> Su objetivo principal es presentar al alumnado los conceptos básicos de gráficos en computación, permitiendo adquirir la destreza necesaria para desarrollar aplicaciones informáticas que integren gráficos 3D en su interfaz o contenidos.

Más información en la **[guía docente oficial](https://guiadocente.udc.es/guia_docent/index.php?centre=614&ensenyament=614G01&assignatura=614G01066&idioma=cast&any_academic=2024_25)**.

## Evaluación
La evaluación de la asignatura se basa en **prácticas de laboratorio**, **trabajos tutelados** y una **prueba objetiva**. A continuación, se detallan los criterios y métodos utilizados para la calificación de los estudiantes.

> [!Warning]
> No se sabe con certeza que procentaje de la nota supen cada avctividad

### Criterios de evaluación y calificación
1. **Prácticas de laboratorio**: Durante las sesiones de prácticas, los alumnos deben completar ejercicios diarios guiados por un tutorial online, que son corregidos y puntuados en el momento por el profesor. Además, al finalizar cada bloque, se lleva a cabo una práctica final más compleja en la que deberán aplicar lo aprendido sin una guía detallada.

	Se dividen en dos bloques principales:
	- **Conceptos básicos**: Recorte, transformaciones y dibujo de formas básicas utilizando OpenGL.
	- **Conceptos avanzados**: Iluminación, extrusiones, materiales y modelado, utilizando un software de diseño y renderizado 3D.

2. **Trabajos tutelados**: Se realizan en grupos reducidos de tres a cuatro alumnos, quienes deben proponer un tema de actualidad relacionado con la asignatura. El trabajo se presenta a través de Teams en formato de diapositivas, permitiendo evaluar la capacidad de investigación y exposición de los alumnos.

3. **Prueba objetiva**: Consiste en un examen mixto que incluye preguntas tipo test y de respuesta corta.

### Calificaciones de las prácticas de laboratorio
Las siguientes tablas muestran las calificaciones obtenidas en las prácticas de laboratorio durante el curso, diferenciando entre **prácticas diarias** y **prácticas finales**.  

#### **Prácticas de laboratorio diarias**  
Estas prácticas consisten en ejercicios evaluados en cada sesión, donde los alumnos deben aplicar los conceptos trabajados en clase.  

| Identificador |  Alumno              |Descripción | Curso   | Calificación | Comentario |
|-------------- |--------------------- |------------|-------- |------------- |------------|
| p1		    | Martín do Río Rico   | -          | 2023/24 | 100.00%      | -          |
| p2            | Martín do Río Rico   | -          | 2023/24 |  97.50%      | _No se utilizan estructuras y/o vectores para almacenar las posiciones._ |
| p3            | Martín do Río Rico   | -          | 2023/24 |  90.00%      | _No se utilizan `Timers`._ |

#### **Prácticas de laboratorio finales**  
Estas prácticas requieren que los alumnos realicen un trabajo más complejo, aplicando lo aprendido a lo largo del curso sin una guía detallada.  

| Identificador | Alumno              | Descripción | Curso   | Calificación | Comentario  |
|-------------- |-------------------- |-------------|-------- |------------- |-------------|
| e1            | Martín do Río Rico  | -           | 2023/24 |  93.75%      | _Se registran las pulsaciones, pero algunas acciones que implican solo al teclado no funcionan. La tecla `s` se detiene en el sitio en el que está y la perspectiva no cambia._ |

## Introducción
Este proyecto consiste en la implementación de prácticas de gráficos en **OpenGL** utilizando la biblioteca **GLUT** en un entorno Linux. A continuación, se detallan los pasos para instalar las dependencias necesarias, configurar el entorno de desarrollo y compilar los ejemplos.  

### Requisitos Previos  
Para ejecutar las prácticas, es necesario instalar las siguientes bibliotecas en tu sistema:  
- `freeglut3`  
- `freeglut3-dev`  

En algunas distribuciones más antiguas, también puede ser necesario instalar:  
- `libgl1-mesa-dev`  

En un sistema **Linux**, puedes instalarlas con el siguiente comando:  

```bash
apt install freeglut3 freeglut3-dev
```

### Instalación
Se recomienda realizar estas prácticas en **Linux**, ya que proporciona un entorno más estable para trabajar con **OpenGL**.

Si bien es posible ejecutarlas en **Windows** utilizando **Windows Subsystem for Linux** (**WSL**), esta opción puede presentar problemas de compatibilidad con bibliotecas gráficas. Por experiencia personal, no recomiendo **WSL** para este proyecto debido a dificultades persistentes que pueden afectar la ejecución del código.

El profesor ha recomendado utilizar **Visual Studio Code** (**VS Code**) como editor de código. Para instalarlo en **Linux**, ejecuta los siguientes comandos:

```bash
sudo apt update && sudo apt install software-properties-common apt-transport-https wget
wget -q https://packages.microsoft.com/keys/microsoft.asc -O- | sudo apt-key add -
sudo add-apt-repository "deb [arch=amd64] https://packages.microsoft.com/repos/vscode stable main"
sudo apt install code
```

### Uso
Para compilar y ejecutar los ejemplos en C, puedes optar por dos métodos:

#### 1. Usando Makefile (Recomendado)  
Para facilitar la compilación, se recomienda crear un archivo `Makefile` con el siguiente contenido:

```make
LIBS = -lGL -lGLU -lglut  
ejemplo: ejemplo.c  
	gcc -o $@ $< $(LIBS)
```  
Luego, solo necesitas ejecutar el comando:  

```sh
make ejemplo
```  

#### 2. Compilación Manual  
Si prefieres compilar manualmente, puedes usar el siguiente comando cada vez que lo necesites: 

```sh
gcc ejemplo.c -o ejemplo -lGL -lGLU -lglut
```

## Contribuir al Proyecto
Si tienes una sugerencia para mejorar este proyecto, puedes hacer un **fork** del repositorio y crear un **pull request**, o simplemente abrir un **issue** para discutirlo.  

Todas las contribuciones son **enormemente apreciadas**. ¡Gracias por tu apoyo!  

### ¿Cómo contribuir?  

1. Realiza un **fork** del proyecto.  
2. Crea una nueva rama para tu mejora.  

```bash
git checkout -b feature/<nueva caracteristica>
```
3. Realiza los cambios y haz un **commit**.  

```bash
git commit -m 'Añadir <nueva característica>'
```
4. Sube los cambios a tu rama.
```bash
git push origin feature/<nueva caracteristica>
```
5. Abre un **pull request** para revisión.  

### Contribuyentes Destacados  

<a href="https://github.com/Meleagrista/udc-computacion-grafica/graphs/contributors">
  <img src="https://contrib.rocks/image?repo=Meleagrista/udc-computacion-grafica" />
</a>

## Contactos
Para cualquier consulta o sugerencia, puedes ponerte en contacto con:  

📧 **Martín do Río Rico** – [mdoriorico@gmail.com](mailto:mdoriorico@gmail.com) 