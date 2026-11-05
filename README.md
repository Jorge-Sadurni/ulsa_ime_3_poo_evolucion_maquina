# Práctica Unidad IV: La evolución de una máquina

Programación Orientada a Objetos · Ingeniería Mecatrónica · Tercer semestre

Llena cada espacio conforme avances en las fases de [PRACTICA.md](PRACTICA.md).

## Fase 1. Entender el problema

**1.1 El problema con mis propias palabras**

La planta de manufactura que se trabajo durante el segundo parcial tiene las maquinas torno, fresadora, pulidora, estación de inspección y banda transportadora que trabajan en conjunto en una linea de produccion. Cada maquina tiene un nombre, cuenta las piezas procesadas, el tiempo trabajado y sabe cuanto  tiempo dura un ciclo. Finalmente la planta ejecuta turnos y genera un reporte con las piezas, el tiempo y la capacidad por hora de cada máquina.

**1.2 Reglas que siempre deben cumplirse en una máquina** (escribe al menos tres)

1. Responsabilidad Unica
2. Proteccion de Datos Heredados 
3. Sobrescribir Metodos (virtual - override) / Polimorfismo

**1.3 ¿Quién más usa la clase `Maquina`? ¿Qué podría salir mal si otro equipo crea una máquina nueva sin conocer tus reglas?**

En caso de que otro equipo contribuya y desconozca de estas reglas puede ocurrir lo siguiente:
- Pérdida de encapsulamiento: Si los datos heredados no se protegen adecuadamente, cualquier programador podría modificarlos externamente de forma incorrecta, con el peligro de corromper el estado de la máquina y alterar los reportes de la planta.
- Ruptura del polimorfismo: Al no respetar el contrato de la clase base , se pierde la ventaja de tratar a todas las máquinas de forma genérica. El programa principal ya no podría interactuar con la máquina específica mediante polimorfismo.
- Ignorando el principio de responsabilidad unica, otros programadores podrian agregar responsabilidades extra a una maquina.

## Fase 2. Diseñar la solución

**2.1 Diagrama inicial (Etapa 0)**

![Diagrama inicial](diseno_inicial.png)

**2.2 Diagrama final (Etapa 9)**

![Diagrama final](diseno_solucion.png)

**2.3 ¿Qué cambió entre los dos diagramas?**

| Elemento | Etapa 0 | Etapa 9 | Etapa que lo cambió |
| --- | --- | --- | --- |
| Visibilidad de los atributos de `Maquina` | public | private | Etapa 1 |
| `procesar()` | Metodo concreto normal | Metodo virtual puro | Etapa 5 |
| `tiempoCicloSeg()` | No existia | Metodo virtual puro | Etapa 2 y 5 |
| Destructor de `Maquina` | Destructor estandar | Destructor virtual | Etapa 4  |
| ¿Se pueden crear objetos `Maquina`? | Si | No | Etapa 5  |
| Relación `ControlDeLinea` - `Maquina` | Composicion | Agregacion por punteros | Etapa 3  |
| Relación `Torno` - `Motor` | No existia  | Composicion | Etapa 4 |
| Relación `BandaTransportadora` - `Motor` | No existia | No tiene motor  | Diseño base |

## Fase 3. Implementar

**3.0 Etapa 0. Una máquina sin reglas**

a) ¿Qué imprime `ejecutarTurno()` para el torno y la fresadora? ¿Por qué no imprime "torneando" ni "fresando"?


Torno T-01: procesamiento generico
Fresadora F-01: procesamiento generico
Use code with caution.

No imprime los mensajes específicos porque en la clase base Maquina falta la palabra clave virtual en el método procesar(). Como la función ejecutarTurno recibe una Maquina& genérica, el compilador se confunde y decide ejecutar el código del padre (enlace estático), ignorando por completo que en realidad le pasaste un torno y una fresadora.


b) ¿Por qué el torno acumula 65 s y no 135 s?

El tiempo se calcula mal debido a que el programa suma dos cosas distintas en el main:
	1. La llamada directa: Suma 45 segundos porque se llama desde la variable torno directamente y ahí sí encuentra su código.
	2. El turno de 2 ciclos: Al entrar a ejecutarTurno, el compilador corre el código genérico de la clase padre en lugar del código del torno. Como cada ciclo genérico dura 10 segundos, solo se suman 20 segundos (\(10 \times 2\)).
Al final, el total se queda en (45 + 20 = 65) segundos, en lugar de los 135 segundos que deberían ser si los tres ciclos hubieran trabajado como un torno real.


**3.1 Etapa 1. Invariantes y constructores explicit**

a) ¿Qué regla de la sección 1.2 rompió `torno.piezasProcesadas = -5;`?

Rompio la regla de proteccion de datos, ninguna maquina puede procesar piezas negativas. Poniendo las variables en un espacio publico, en cualquier parte del programa se pueden modificar estos valores, destruyendo la logica y funcionalidad del reporte de la linea de produccion.

b) ¿De dónde salió la máquina "Fantasma"? ¿Qué hizo el compilador sin que se lo pidieras?

El compilador hizo una conversion  automatica, como la funcion de imprimirFicha pide una maquina y en el main se agrego un pedazo de string "Fantasma" (variable codigo), C++ utilizo el texto y lo convirtio gracias al constructor.

c) ¿Qué tuviste que cambiar en `Torno` y `Fresadora` y por qué?

Debido a los cambios hechos en maquina.h de poner los atributos en privado y la palabra explicit para evitar conversiones automaticas, las clases hijas (fresadora, torno) ya no pudieron modificar los valores directamente dentro de sus archivos. Por lo tanto, se crearon  funciones publicas y protegidas (agregarTiempo y registrarPieza) para controlar y validar la entrada de valores, ademas de que se agrego la palabra explicit para evitar conversiones.

**3.2 Etapa 2. Virtual y override**

a) La fresadora acumula 180 s, pero reporta 360 pzas/h. ¿Por qué un cálculo usó 60 s y el otro 10 s?

El programa uso el tiempo acumulado de 60 seg de procesar() porque si pudo enlazar directamente con el objeto derivado (fresadora). Por otro lado, en el caso de capacidadPorHora(), la cual vive dentro de maquina.h, no logra conectar con la clase hija y termina usando su valor por defecto debido a que no tiene la misma firma (override/virtual).

b) ¿Tu compilador mostró alguna advertencia antes de usar `override`? ¿Qué mensaje dio después de agregar `override`?

El compilador no mostro ningun error  y compilo, sin embargo como la firma de algunos metodos no coincidian, el programa penso que se trataba de un nuevo metodo y se estaba sobresrcibiendo, liberando una salida erronea. Despues, al agregar el override mostro la salida esperada.

**3.3 Etapa 3. La línea de producción**

a) ¿Por qué la línea procesó todo como "generico" si `procesar()` ya es virtual?

La linea proceso "generico" todo ya que se encontro con el object slicing, el controlDeLinea pasa por exclusivamente Maquinas y al querer pasar por la fresadora o torno, no las reconoce y tira todas las caracteristicas especiales de las clases hijas.

b) ¿Por qué el torno y la fresadora originales quedaron con 0 piezas?

Al igual que el punto 3.3, las clases derivadas originales se quedaron en 0 pzas, porque en vez de que la linea apuntara una de estas maquinas, el programa creaba una maquina generica y hacia el slicing.


c) La relación entre `ControlDeLinea` y `Maquina`, ¿es composición o agregación? ¿Por qué?

La relacion entre maquina y ControlDeLinea es agregacion ya que las maquinas pueden vivir sin la linea, si la linea deja de existir la fresadora o el torno siguen existiendo porque no mueren junto con la linea.

**3.4 Etapa 4. Destructores**

| Momento | Mensajes de destrucción que aparecieron |
| --- | --- |
| `delete temporal;` sin destructor virtual |  Destruyendo Torno
 Destruyendo Motor
Destruyendo Maquina |
| `delete temporal;` con destructor virtual | Destruyendo Torno
 Destruyendo Motor
Destruyendo Maquina |
| Al terminar `main` (torno y fresadora) | Destruyendo Maquina
Destruyendo Torno
 Destruyendo Motor
Destruyendo Maquina |

a) ¿Qué advertencia mostró el compilador? ¿Por qué decimos que ya te estaba avisando del problema?

src/main.cpp:21:5: warning: deleting object of polymorphic class type 'Maquina' which has non-virtual destructor might cause undefined behavior [-Wdelete-non-virtual-dtor] El compilador arroja este mensaje antes porque sabe que estas usando polimosfismo y al no tener el destructor virtual en maquina.h el compilador puede olvidar destruir las clases hijas y solo eliminar la maquina base. 

b) ¿Por qué el torno de `main` sí se destruyó completo aunque el destructor no fuera virtual? ¿A qué máquina corresponde el primer "Destruyendo Maquina" después de "Fin de main"?

En el main el torno si fue destruido ya que la maquina se creo localmente, por lo tanto sabia el tipo real y exacto. La primer maquina destruida corresponde a la ultima maquina declarada dentro del main de acuerdo a los conceptos LIFO (last in, first out).
**3.5 Etapa 5. La clase abstracta**

a) Copia los mensajes de error y explica con tus palabras qué dice cada uno.

src/main.cpp:10:14: error: cannot declare variable 'pulidora' to be of abstract type 'Pulidora'
   10 |     Pulidora pulidora("Pulidora P-01");
   Este error aparece debido a que hicimos la clase maquina.h abstracta y creamos metodos puros, creando una regla a las clases hijas a desarrollar y sobrescribir estos metodos, en este momento no se habia implementado el metodo de procesar en pulidora.

src/main.cpp:11:13: error: cannot declare variable 'generica' to be of abstract type 'Maquina'
   11 |     Maquina generica("Maquina sin tipo"); 
Este error surge porque en POO las clases abstractas no pueden instanciar directamente, estas plantillas definen el que va a hacer, mas no como lo hacen.
b) ¿Por qué es mejor este error de compilación que el comportamiento "generico" de antes?

Es mejor este error de compilacion ya que de avisa del error logico que tienes, en vez de que mienta el programa y emita una salida erronea. Ademas te detiene al ingresar maquinas fantasmas o si te falto desarrollar alguno de los metodos puros que establecio la maquina base, te lo dice.

**3.6 Etapa 6. El contrato que el compilador no ve**

a) ¿Qué partes del contrato violó `InspeccionVisual`?
Por parte de procesar y agregarTiempo, InspeccionVisual nunca llamo a que registaran la pieza y nunca agrego el tiempo trabajado, por lo que en el reporte de inspeccion se quedo en 0 pzas procesadas y 0 seg.

b) ¿Por qué el compilador no lo detectó?

El compilador no lo detecta porque solo revisa que las firmas y parametros sean correctos. No entiende la logica y la complejidad del contrato que se establecio de manera externa.

c) ¿Qué pasaría si el próximo equipo tampoco lee el comentario del contrato?

Ocurriria otra falla igual. Los contribuidores podrian ignorar o olvidar que hay una regla de por medio que toda maquina debe seguir, e introducirian su propia logica.

**3.7 Etapa 7. La base hace cumplir el contrato**

a) ¿Cómo puede una clase derivada sobrescribir un método que es privado en la base?

La etiqueta private bloque quien puede ver o llamar al metodo desde afuera, sin embargo no afecta al polimorfismo, al usar virtual la clase base puede usar una propia verion de las clases hijas.

b) ¿Qué ocurre ahora con una máquina cuyo tiempo de ciclo es 0? Compáralo con la Etapa 6.

En la etapa 6 el programa no decia nada y pasaba desapercibido valores invalidos (pzas negativas o infinitas). En la etapa 7 se agregaron validaciones y restricciones para que en el momento de que haya un valor invalido el try-catch lo puede reconocer.

c) ¿Por qué la línea ignoró el "atajo" del torno, pero la llamada directa no? ¿Cómo corregiste el diseño?

La linea maneja las maquinas a travez de la clase base, usando el metodo oficial, debido a esto los metodos sueltos que esten por fuera a una clase derivada no se ejecutan.

**3.8 Etapa 8. Herencia mal usada**

a) Da al menos dos razones por las que `BandaTransportadora : public Motor` es un error de diseño.

Para que exista esta relacion de herencia, la relacion tiene que ser "es un", en el caso de motor, la maquina no es un tipo de bandaTransportadora, por lo que ni comparten el comportamiento o trabajo. Ademas, con esta herencia los metodos heredados se convirtirian en inutiles ya que a ninguna de las dos maquinas tienen diferente funcionamiento.
b) La relación entre `BandaTransportadora` y `Motor`, ¿es composición o agregación? ¿Por qué?

La relacion dentre BandaTransportadora y Motor tiene que composicion ya que la banda tiene un motor, componente indispensable para la vida de la BandaTransportadora, si se destruye la maquina no sirve.

**3.9 Etapa 9. La librería y la prueba final**

a) Después de agregar la `Cortadora`, ¿qué archivos mostró `git status`? ¿Cuántos archivos de la librería tuviste que modificar?

C++ mostro unicamnete el main.cpp como modificado, junto con los dos archivos nuevos de Cortadora (untracked), mientras que los demas archivos permanecieron ocultos gracias al git.ignore. Ninguj archivo de la libreria tuvo que ser modificado, solo el main y cortadora sufrieron cambios.

b) ¿Qué pasó al escribir `-lplanta` antes de `src/main.cpp`? ¿Por qué?

El enlazador marcó errores de "referencia indefinida". Pasa porque el enlazador lee los argumentos de izquierda a derecha: si pones la librería antes, la revisa cuando el compilador todavía no pedía ninguna función, por lo que no enlaza nada. Al poner main.cpp primero, el programa avisa qué funciones necesita y luego la librería las encuentra y las resuelve.

**3.10 Bitácora de dudas**

| # | Etapa | Duda | Cómo la resolví | Fuente |
| --- | --- | --- | --- | --- |
| 1 | 2 | Virtual y Override | Use Virtual y Override para que las llamadas de metodos a las clases hijas funcionaran de manera correcta | Material de Clase. Unidad 4 |
| 2 | 4 | Destructores | Para que el destructor no solo destruyera la clase base use un destructor virtual para que se pudiera desplazar a las clases derivadas | Acertijos y Guias de la Practica asistida de Github |
| 3 | 5 | Clase Abstracta | Quite toda instancia que existia en la clase abstracta para que no romper los conceptos de polimorfismo | Material de Clase |

## Fase 4. Probar y mejorar

**4.1 Tabla de pruebas**

| # | Caso | Resultado esperado | Resultado obtenido | ¿Pasa? |
| --- | --- | --- | --- | --- |
| 1 | Máquina con nombre vacío | Excepción con mensaje claro | El nombre no puede estar vacio | Si |
| 2 | Reporte de una línea vacía | "La linea no tiene maquinas" |  La linea no tiene maquinas | Si |
| 3 | `agregar(nullptr)` | Devuelve `false` | Resultado OK: Se rechazo el nullptr correctamente (retorno false). | Si |
| 4 | Reporte antes de ejecutar el turno | 0 piezas, 0 s y capacidad calculada | 0 pzas, 0 s y capacidad calculada | Si |
| 5 | Turno de 0 ciclos | Nada cambia | Nada cambio | Si |
| 6 | Torno con 3 ciclos | 3 piezas, 135 s, 80 pzas/h | T-01 | piezas: 3 | tiempo: 135 s | capacidad: 80 pzas/h | Si |
| 7 | Máquina con `tiempoCicloSeg()` igual a 0 | Excepción con mensaje claro | Validacion de tiempos invalidos (0 o negativos):
Excepcion capturada correctamente: El tiempo de ciclo no puede ser menor o igual a 0 | Si |
| 8 | Máquina con `tiempoCicloSeg()` negativo | Excepción con mensaje claro | Validacion de tiempos invalidos (0 o negativos):
Excepcion capturada correctamente: El tiempo de ciclo no puede ser menor o igual a 0 | Si |
| 9 | La misma máquina agregada dos veces | No duplicar | Resultado OK: Se evito duplicar la misma maquina en la linea. | Si |

**4.2 Bitácora de mejoras**

| # | Falla o mejora detectada | Qué cambié | Por qué |
| --- | --- | --- | --- |
| 1 | La linea aceptaba maquinas duplicadas | Hice una restriccion en agregar(), que impide agregar maquinas duplicadas | En la vida real las maquinas tienen nombres y si agregan dos maquinas del mismo tipo, tienen que tener un identificador o simplemente no las aceptan. |
| 2 | Destructor de maquinas genereal | Puse el destrcutor vitrual en la maquina base | Para que en el momento de eliminar las clases hijas la el metodo si pueda eliminar el torno o fresadora. |

Retos opcionales que intenté: 0

## Fase 5. Publicar en GitHub

**5.1 Enlace a mi fork**

[[Inserta aquí el enlace a tu fork](https://github.com/Jorge-Sadurni/ulsa_ime_3_poo_evolucion_maquina/blob/main/README.md)]

## Cierre y reflexión

**6.1 Errores que ya no pueden ocurrir**

| Error | Etapa en que apareció | Restricción que lo impide ahora | ¿Quién lo detecta: el compilador o el programa? |
| --- | --- | --- | --- |
| Contadores con valores inválidos | 1 | dentro de agregarTiempo, std::invalid_argument | El programa |
| Máquina "fantasma" creada a escondidas | 1 | Explicit | El compilador |
| Método que no sobrescribe por un `const` | 2 | override | El compilador |
| Máquinas copiadas y "rebanadas" | 3 | Punteros | El compilador |
| Destrucción incompleta | 4 | Destructor virtual | El compilador |
| Máquina sin `procesar()` propio | 5 | Metodos vituales puros | El compilador |
| Tiempo de ciclo inválido | 6 | Contrato de tiempoCicloSeg() | El programa |
| Derivada que no registra sus piezas | 7 | logica y sistema | El programa |

**6.2 ¿Cuál de los errores fue el más peligroso: el de compilación, la advertencia o el que compilaba sin problemas? ¿Por qué?**

Yo creo que el que compilaba sin problema ya que si agregabas un valor invalido, un nombre vacio, un tiempo negativo o piezas procesadas negativas, la salida aunque visualmente no tiene errores, la logica de la planta nnunca iba a coincidir con el reporte.

**6.3 ¿Qué aprendiste en esta práctica?**

En esta practica aprendi sobre las clases abstractas de como definen un comportamiento, los contratos con virtual y override que obligan a las clases derivadas a desarrollar los metodos heredados de manera personalizada, como los destrcutores necesitan de un virtual para poder eliminar las clases hijas y no destruir solo las maquinas base, la importancia de punteros para desplazarse de maquina en maquina para no sufrir el slicing, el uso namespace  para evitar confusiones de maquinas, mantener una organizacion y tener la posibilidad de agregar maquinas en el futuro sin problema y finalmente de manera general el polimorfismo.

**6.4 ¿Qué cambiarías de tu proceso la próxima vez?**

Tener mas tiempo de preparacion para empezar el proyecto ya que hay 9 etapas, las cuales tienen varios puntos a realizar. Ser mas organizado en los archivos h y cpp para poder identificar donde estan mis metodos y desde el principio tener una idea de como seria el producto final.
