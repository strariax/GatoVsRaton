# 😾 Juego del Gato y el Ratón 🐭

En este respositorio encontrarás el código desarrollado para implementar un juego del gato vs el ratón, en el que el objetivo consiste en que el gato atrape al ratón, y que este último sobreviva sin ser atrapado durante un número establecido de jugadas.

Para que ambos jugadores (gato y ratón) realicen las mejores jugadas posibles, se implementó el algoritmo minimax, que busca, dependiendo del turno, maximizar o minimizar la distancia entre los jugadores.

## Algoritmo Minimax:

El algoritmo Minimax es una estrategia de decisión utilizada en juegos de dos jugadores con información perfecta, como en el juego de Gato y Ratón. En este contexto, el algoritmo se utiliza para determinar el mejor movimiento posible para cada jugador en cada turno, maximizando las posibilidades de ganar del ratón mientras minimiza las del gato y viceversa. Funciona explorando recursivamente los posibles movimientos en el juego (como movimientos hacia arriba, abajo, izquierda y derecha en el tablero) y evaluando el estado resultante del tablero. Para cada movimiento, se calcula una puntuación basada en una función de evaluación, en este caso, la distancia Manhattan.

El algoritmo opera bajo el principio de que ambos jugadores, el ratón y el gato, jugarán de manera óptima. En cada turno del ratón, el algoritmo busca el movimiento que maximice su puntuación, mientras que en cada turno del gato, busca minimizar la puntuación del ratón (acercándose a él). Esto se realiza explorando todas las posibles secuencias de movimientos futuros hasta una cierta profundidad y seleccionando el movimiento que lleva al mejor resultado posible desde la perspectiva del jugador actual. A través de esta simulación de posibles movimientos y contramovimientos, Minimax ayuda a tomar decisiones estratégicas en el juego, equilibrando entre movimientos seguros y arriesgados para maximizar las posibilidades de alcanzar el objetivo del juego.

## Distancia Manhattan

En el juego de Gato y Ratón, la distancia Manhattan se refiere a la forma de medir la distancia entre dos puntos (en este caso, el gato y el ratón) en una cuadrícula, basada en un camino que sólo se desplaza horizontal y verticalmente, como las calles de una ciudad. La distancia Manhattan se calcula sumando la diferencia absoluta en las coordenadas horizontales (columnas) y verticales (filas) de los dos puntos. Por ejemplo, si el ratón está en la posición (3,2) y el gato en (1,5), la distancia Manhattan es |3-1| + |2-5| = 2 + 3 = 5. 

En el contexto del juego, esta medida es útil para evaluar qué tan cerca están el gato y el ratón uno del otro. Al minimizar esta distancia, el gato intenta acercarse al ratón, mientras que el ratón busca maximizarla para alejarse del gato.

## Recursividad

La recursividad en este contexto, especialmente en la implementación del algoritmo Minimax, se refiere al proceso por el cual la función se llama a sí misma con diferentes parámetros para explorar las posibles secuencias de movimientos en el juego. En cada llamada recursiva, el estado del juego (representado por el tablero) se modifica según un posible movimiento del Gato o del Ratón, y luego la función se llama a sí misma para considerar la respuesta del otro jugador a ese movimiento.

Por ejemplo, en la función `minimax`, cuando es el turno del Ratón, la función explora todos los posibles movimientos que el Ratón podría hacer (moverse hacia arriba, abajo, izquierda o derecha). Para cada movimiento, la función se llama a sí misma (`minimax`), esta vez considerando que es el turno del Gato. En este nuevo nivel de la llamada recursiva, se evalúan los movimientos del Gato en respuesta al movimiento del Ratón. Este proceso continúa alternando entre los turnos del Ratón y del Gato, profundizando en el árbol de juego hasta que se alcanza una condición de parada, como un límite en la profundidad de búsqueda o una situación en la que el juego termina (por ejemplo, el Gato atrapa al Ratón o se agotan los movimientos).

## Bibliotecas utilizadas

1. **`<iostream>`**: Se utiliza para imprimir el tablero y mostrar mensajes al usuario, como indicaciones de los movimientos o el resultado del juego.

2. **`<vector>`**: Proporciona una forma eficiente y flexible de trabajar con arrays dinámicos. Se utiliza para representar el tablero de juego, lo que permite almacenar y manipular el estado del juego (la posición del Gato, del Ratón, los obstáculos, etc.).

3. **`<stdlib.h>`**: Se utiliza para generar números aleatorios (para el momento de colocar obstáculos).

## Proceso

1. Declaración de variables

2. Creación e inicialización del tablero:

    - Para la ubicación de los obstáculos: Utilicé la función `srand` para "sembrar" el generador de números aleatorios con un punto de partida (en este caso 42), asegurando que la secuencia de números aleatorios generados por rand() sea la misma cada vez que se ejecuta el programa.

    - Para la ubicación del Gato y el Ratón: Utilicé variables por si en algún momento las posiciones quiseran ser modificadas.

3. Imprimir tablero: Esta función es para la parte visual, tratando de simular un tablero real.

4. Funciones de movimiento:

    En las primeras etapas del desarrollo, implementé funciones separadas para cada movimiento posible: `moverArriba`, `moverDerecha`, `moverIzquierda` y `moverAbajo`. Mi enfoque inicial para cada una de estas funciones incluía buscar la posición actual del jugador (gato o ratón) dentro del tablero en cada llamada a la función. 

    Durante el proceso de implementación y pruebas, me encontré con un desafío significativo: en algunas profundidades de la ejecución del algoritmo Minimax, la búsqueda del jugador fallaba. Esto era particularmente problemático con el gato, ya que parecía "desaparecer" del tablero, un comportamiento inesperado que se manifestaba cuando el ratón "comía" al gato en el juego simulado.

    Realicé los siguientes ajustes en mi diseño:

    - Desarrollé la función, `encontrarJugador`, que se convirtió en un componente central para determinar la ubicación actual del gato y del ratón antes de realizar cualquier movimiento.

    - Implementé la función `comprobarMovimiento`, se encarga de verificar las siguientes condiciones: que el movimiento no resulte en salirse del tablero, que la celda destino no esté bloqueada por un obstáculo, y que el Ratón no pueda comer al gato.

    - Creé la función `mover` que, además de sustituir a las primeras funciones (moverArriba, moverDerecha, moverIzquierda, moverAbajo), utiliza `encontrarJugador` y `comprobarMovimiento`. Esto no solo resolvió el problema de la "desaparición" del gato sino que también hizo que el código fuera más modular, limpio y fácil de mantener.

5. Funcionalidad y Relación de las Funciones Clave:

    Utilicé tres funciones clave que trabajan en conjunto para simular la inteligencia artificial y determinar el estado del juego.

    #### Función `distanciaManhattan`

    - Localiza al gato y al ratón en el tablero usando la función `encontrarJugador`.

    - Si ambos, el gato y el ratón, se encuentran en el tablero, calcula la suma del valor absoluto de las diferencias en sus coordenadas de fila y columna.

    - Esta distancia se utiliza como la función de evaluación en el algoritmo Minimax, representando el objetivo del gato, de atrapar al ratón y del ratón, de evadir al gato.

    #### Función `juegoTerminado`

    El juego puede terminar en dos situaciones:

    - Cuando la distancia Manhattan entre el gato y el ratón es cero, lo que significa que el gato ha atrapado al ratón.

    - Cuando se han agotado los turnos restantes del juego.

    #### Función `minimax`

    Utiliza un enfoque recursivo para simular y evaluar todas las posibles secuencias de movimientos del gato y del ratón, alternando entre maximizar la distancia (para el ratón) y minimizarla (para el gato). La implementación se basa en:

    - Verificar si el juego ha terminado o se ha alcanzado la profundidad máxima del algoritmo.

    - Para el ratón (cuando `esTurnoRaton` es `true`), la función busca maximizar la distancia Manhattan, indicando su intento de evadir al gato.

    - Para el gato, la función intenta minimizar esta distancia, lo que refleja su objetivo de atrapar al ratón.

    - La función considera todos los movimientos válidos en cada turno y elige el que mejore la posición del jugador actual (gato o ratón) según su objetivo.

6. JugarGato y JugarRaton:

    Ambas funciones, `jugarGato` y `jugarRaton`, trabajan estrechamente con la función `minimax` para determinar el mejor movimiento para el gato y el ratón, respectivamente, en cada turno.

    #### Función `jugarGato`

    - Inicialmente, establece la evaluación mínima a un valor alto (`FILAS + COLUMNAS`).

    - Examina cada posible dirección de movimiento (Arriba, Derecha, Abajo, Izquierda).

    - Para cada dirección válida (verificada por `comprobarMovimiento`), calcula el valor Minimax del movimiento resultante.

    - Si el valor Minimax de un movimiento es menor o igual que la evaluación actual más baja (`menorEval`), actualiza `mejorMovimiento` con ese movimiento y `menorEval` con su valor Minimax.

    - Retorna el `mejorMovimiento`, que representa el movimiento óptimo para el gato bajo las reglas del algoritmo Minimax.

    #### Función `jugarRaton`

    - Se inicia con una evaluación máxima muy baja (`-1`).

    - Al igual que `jugarGato`, examina todas las direcciones posibles.

    - Utiliza `comprobarMovimiento` para asegurarse de que cada movimiento sea válido.

    - Calcula el valor Minimax para cada movimiento válido. Si este valor es mayor o igual que la evaluación máxima actual (`mayorEval`), actualiza `mejorMovimiento` con este movimiento y `mayorEval` con su valor Minimax.

    - Al final, retorna `mejorMovimiento`, que es el mejor movimiento para el ratón según Minimax.

    Estas funciones permiten simular un juego inteligente y estratégico entre los dos jugadores.



    

