# OBO - Open BASIC Operator 

Boceto de lenguaje de programación para el curso de Lenguajes de programación de la universidad EAFIT (Semestre 2019-2)

## Para empezar

El código de C++ funciona como un compilador del lenguaje, leyendo archivos .obo y ejecutándolos.

### Prerequisitos

Compilador de C++ (GNU).
IDE para ejecutar el código desde ahí.

### Instalación

Descarga todo el proyecto en una sola carpeta y ábrelo en Visual Studio Code. Si vas a ejecutar
tu propio código de OBO, debes ponerlo en esta carpeta.

### Instrucciones de uso

Desde la terminal ingresa los siguientes comandos para compilar y ejecutar:

```
> g++ -o main.exe Source.cpp

> ./main.exe
```

Te pedirá un nombre de archivo:
```
Type filename that you want to read (.obo only):
```
Deberás escribir la ruta donde está el archivo (si es que está en una carpeta) o directamente su nombre.
Mira el ejemplo por defecto del proyecto:
```
> BNF and examples/example.obo
```

### Codificar en OBO

Por el momento, este lenguaje solo admite la lectura de documentos y no tiene ejecución intecractiva como
Haskell a través de GHCi. Mira el [Backus-Naur Form](https://github.com/juansedo/Open-BASIC-Operator/blob/master/BNF%20and%20examples/bnf_document) del programa, compara con el archivo de ejemplo y aprende a 
programar en OBO.

## Fuentes

* [BNF_Grammar](https://rosettacode.org/wiki/BNF_Grammar) - Documentación en la que nos basamos
* [PurpleBooth's template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2) - Formato para README.md

## Autores

* **Juan Sebastián Díaz Osorio** - [juansedo](https://github.com/juansedo)
* **David Calle González** - [dcalleg707](https://github.com/dcalleg707)

Mira la lista completa de [contribuyentes](https://github.com/your/project/contributors) que participaron en el proyecto.

## Reconocimientos

* Edwin Andrey Duque Loaiza (Profesor de lenguajes de programación)
