# Banco de preguntas abiertas · Parte II: Coordinación (caps. 6–13)

Vitillo, *Understanding Distributed Systems* · Sistemas Distribuidos · UIS

Cada pregunta incluye, en cursiva, los **elementos esperados** en una respuesta completa, como apoyo para la calificación. Las marcadas con **(C)** tocan contenidos de complemento presentados en clase que van más allá del texto del libro.

---

## A. Modelos de sistema (cap. 6)

1. ¿Qué es un modelo de sistema y por qué es necesario para razonar sobre algoritmos distribuidos?
   *Esperado: conjunto de supuestos sobre enlaces, procesos y tiempo; un algoritmo es correcto solo bajo sus supuestos; permite razonar y saber cuándo deja de valer.*

2. Compare los modelos de enlace con pérdida justa, confiable y confiable autenticado. ¿Cómo se construye uno confiable a partir de uno con pérdida justa?
   *Esperado: pérdida justa puede perder/duplicar pero algún reenvío llega; confiable entrega exactamente una vez; autenticado verifica emisor; retransmisiones + deduplicación (TCP), autenticación con TLS.*

3. Diferencie los modelos de proceso bizantino, de caída con recuperación y de caída con detención. Dé un ejemplo de sistema para el que sea apropiado el modelo bizantino.
   *Esperado: bizantino: desviación arbitraria/maliciosa; caída con recuperación: se reinicia conservando lo persistido; caída con detención: no vuelve; ejemplo: blockchain, aviónica.*

4. En el modelo de caída con recuperación, ¿qué implicación tiene para un proceso el responder a un cliente antes de persistir un cambio?
   *Esperado: si cae tras responder y antes de persistir, pierde el cambio que el cliente cree confirmado; persistir antes de responder.*

5. Explique los modelos de temporización síncrono, asíncrono y parcialmente síncrono, y justifique por qué el parcialmente síncrono describe mejor los sistemas reales.
   *Esperado: límites conocidos / sin límites / límites que se cumplen casi siempre; redes con congestión ocasional, pausas de GC, etc.*

6. ¿Qué modelo de sistema asume Vitillo por defecto en el resto del libro?
   *Esperado: enlaces con pérdida justa, procesos con caída y recuperación, sincronía parcial.*

## B. Detección de fallas (cap. 7)

7. ¿Por qué un cliente que no recibe respuesta no puede saber si el servidor cayó? Enumere los casos indistinguibles.
   *Esperado: petición perdida, servidor lento, servidor caído, respuesta perdida; todos se ven como ausencia de respuesta.*

8. Explique el compromiso al elegir el valor de un *timeout* para detectar fallas.
   *Esperado: corto: falsos positivos, reintentos innecesarios, sobrecarga; largo: detección lenta de caídas reales.*

9. Compare las técnicas de *ping* y *heartbeat*: quién inicia la comunicación y cómo se decide la sospecha.
   *Esperado: ping: el monitor pregunta y espera respuesta en un plazo; heartbeat: el vigilado envía "estoy vivo" periódicamente; sospecha si deja de llegar.*

10. ¿Por qué se dice que los detectores de fallas son imperfectos? ¿Qué consecuencia tiene para el diseño de algoritmos?
    *Esperado: solo sospechan; pueden equivocarse; los algoritmos deben ser seguros aunque la sospecha sea errónea (p. ej., dos líderes posibles → fichas de cercado).*

## C. Tiempo (cap. 8)

11. ¿Por qué no es buena idea usar el reloj de pared de cada máquina para ordenar eventos de un sistema distribuido?
    *Esperado: deriva de cuarzo, error de sincronización NTP, saltos hacia atrás/adelante; relojes de distintas máquinas no son comparables con precisión.*

12. ¿Qué es un reloj monótono, para qué sirve y para qué no sirve?
    *Esperado: nunca retrocede; medir intervalos en una máquina; no sirve para comparar eventos entre máquinas.*

13. Defina la relación *sucedió-antes* y explique qué significa que dos eventos sean concurrentes.
    *Esperado: mismo proceso en orden, envío→recepción, transitividad; concurrentes: ninguno sucedió antes del otro (sin relación causal).*

14. Enuncie las reglas de actualización de un reloj de Lamport.
    *Esperado: incrementar antes de cada evento; adjuntar al enviar; al recibir, max(local, recibido)+1.*

15. Tres procesos: P1 tiene eventos a (local) y b (envía m a P2); P2 tiene c (local) y d (recibe m). Calcule los relojes de Lamport de todos los eventos y diga si L(c) < L(b) implica c → b.
    *Esperado: a=1, b=2, c=1, d=max(1,2)+1=3; L(c)<L(b) pero c y b son concurrentes; no implica.*

16. ¿Cómo se obtiene un orden total a partir de los relojes de Lamport y para qué puede servir?
    *Esperado: desempatar por identificador de proceso; orden consistente con la causalidad usable para exclusión mutua, ordenar operaciones.*

17. Explique cómo funcionan los relojes vectoriales y cómo permiten detectar eventos concurrentes.
    *Esperado: contador por proceso; incrementar propio; al recibir máximo componente a componente e incrementar; V(a)<V(b) ⇔ a→b; si no comparables, concurrentes.*

18. Dados V(x) = [2, 1, 0] y V(y) = [1, 2, 0], ¿qué relación hay entre x e y? Justifique.
    *Esperado: ninguno es ≤ al otro componente a componente → concurrentes.*

19. Compare relojes de Lamport y vectoriales en costo y en capacidad de expresar la causalidad.
    *Esperado: Lamport un entero, no detecta concurrencia; vectorial crece con N, captura causalidad completa.*

## D. Elección de líder (cap. 9)

20. ¿Qué propiedades de seguridad y vivacidad debe cumplir un algoritmo de elección de líder?
    *Esperado: seguridad: a lo sumo un líder a la vez; vivacidad: eventualmente se elige un líder.*

21. Describa los tres estados de un proceso en Raft y las transiciones entre ellos.
    *Esperado: seguidor→candidato al vencer el timeout; candidato→líder con mayoría; candidato→seguidor si descubre líder o mandato mayor; candidato→candidato con votos divididos; líder→seguidor con mandato mayor.*

22. ¿Qué es un mandato (*term*) en Raft y qué papel cumple?
    *Esperado: número lógico creciente; a lo sumo un líder por mandato; permite detectar líderes obsoletos.*

23. ¿Por qué en Raft no pueden ganar dos candidatos en el mismo mandato?
    *Esperado: cada proceso vota una vez por mandato; ganar requiere mayoría; dos mayorías se solapan en al menos un proceso.*

24. ¿Para qué sirven los tiempos de elección aleatorios en Raft?
    *Esperado: evitar que varios seguidores se vuelvan candidatos a la vez y dividan los votos repetidamente; vivacidad.*

25. Explique cómo implementar elección de líder usando un almacén linealizable con arrendamientos.
    *Esperado: clave con TTL; adquirir con compare-and-swap si no existe; el líder renueva periódicamente; si cae, expira y otro la toma.*

26. Describa el problema que resuelven las fichas de cercado con un escenario concreto.
    *Esperado: líder con pausa de GC pierde el arrendamiento sin saberlo; otro adquiere; el viejo escribe; con fichas crecientes el recurso rechaza la ficha menor.*

27. ¿Por qué Vitillo recomienda minimizar el trabajo del líder o evitarlo cuando sea posible?
    *Esperado: punto único de falla (indisponibilidad durante elecciones) y cuello de botella de escalabilidad.*

## E. Replicación y consistencia (cap. 10)

28. Explique la idea de replicación de máquinas de estado y por qué se reduce al problema del consenso.
    *Esperado: mismo estado inicial + mismas operaciones deterministas en el mismo orden → mismo estado; acordar el orden del registro es consenso.*

29. Describa cómo Raft replica una operación desde que el líder la recibe hasta que se considera confirmada.
    *Esperado: agrega a su log; AppendEntries a seguidores; confirma cuando la mayoría la tiene; aplica y responde; seguidores aplican al saber el índice de confirmación.*

30. ¿Cuántas réplicas se necesitan para tolerar 2 fallas con Raft? ¿Por qué un número par de réplicas no aporta tolerancia adicional?
    *Esperado: 5 (2f+1); con 4 la mayoría es 3 y se tolera 1, igual que con 3.*

31. ¿Por qué Raft solo permite ser elegido líder a un candidato con un registro suficientemente actualizado?
    *Esperado: para no perder entradas confirmadas; la mayoría que vota contiene al menos un nodo con cada entrada confirmada.*

32. Defina linealizabilidad y explique qué debe hacer el líder de Raft para ofrecer lecturas linealizables.
    *Esperado: cada operación parece atómica en un instante entre invocación y respuesta; el líder debe confirmar que sigue siendo líder (contactando a la mayoría) o usar un arrendamiento.*

33. Compare consistencia fuerte, secuencial y eventual usando como ejemplo lecturas en un clúster Raft.
    *Esperado: fuerte: leer del líder confirmado; secuencial: leer de un seguidor (orden correcto, atrasado); eventual: leer de cualquier réplica sin garantía de orden, converge.*

34. Enuncie el teorema CAP e ilústrelo con un escenario de partición de red.
    *Esperado: ante partición, elegir consistencia (rechazar operaciones) o disponibilidad (responder con datos posiblemente viejos); escenario coherente.*

35. ¿Qué agrega PACELC a CAP y por qué es más relevante en el día a día?
    *Esperado: sin partición hay compromiso entre latencia y consistencia; las particiones son raras, la latencia es constante.*

36. Explique la replicación en cadena: dónde entran las escrituras, dónde se leen y quién gestiona la configuración.
    *Esperado: escrituras por la cabeza, se propagan hasta la cola que confirma; lecturas en la cola; plano de control con consenso gestiona la cadena.*

37. Compare replicación en cadena con Raft en latencia de escritura y sensibilidad a nodos lentos. ¿Qué mejora CRAQ?
    *Esperado: cadena recorre todos los nodos y un nodo lento la frena; Raft espera mayoría; CRAQ permite leer de cualquier nodo consultando a la cola si hay escrituras pendientes.*

## F. Evitar la coordinación (cap. 11)

38. Compare la difusión *best-effort*, confiable, por chismes y de orden total.
    *Esperado: best-effort sin garantía si el emisor cae; confiable: todos los correctos entregan; chismes: reenvío aleatorio, alta probabilidad, escalable; orden total: mismo orden, requiere consenso.*

39. ¿Qué propiedades debe cumplir la operación de fusión de un CRDT basado en estado y por qué cada una es necesaria?
    *Esperado: conmutativa (orden), asociativa (agrupamiento), idempotente (duplicados); permite converger con cualquier protocolo de difusión.*

40. Dos réplicas de un G-Counter tienen {A: 4, B: 1} y {A: 2, B: 3}. Calcule el resultado de la fusión y el valor del contador. ¿Por qué no se suman los vectores?
    *Esperado: {A: 4, B: 3} → 7; sumar no es idempotente: recibir dos veces el mismo estado contaría doble.*

41. Compare un registro "último escritor gana" con un registro multivalor ante escrituras concurrentes.
    *Esperado: LWW conserva la de mayor marca y descarta las demás (pérdida de datos); MV conserva todas y delega la resolución al cliente.*

42. En un almacén estilo Dynamo con N = 3, ¿qué combinaciones de W y R garantizan que una lectura se solape con la última escritura confirmada? ¿Qué se gana con W = 1?
    *Esperado: W + R > N (p. ej., W=2,R=2; W=3,R=1; W=1,R=3); W=1 da escrituras rápidas y disponibles a costa de lecturas más costosas.*

43. Explique la reparación en lectura y la antientropía. ¿Para qué se usan los árboles de Merkle?
    *Esperado: read repair actualiza réplicas atrasadas al detectarlas en una lectura; antientropía sincroniza en segundo plano; Merkle identifica rangos distintos sin transferir todo.*

44. Enuncie el teorema CALM y dé un ejemplo de problema monótono y uno no monótono.
    *Esperado: consistente sin coordinación ⇔ monótono; monótono: alcanzabilidad, acumular un conjunto; no monótono: "no existe camino", decisiones basadas en ausencia.*

45. ¿Qué garantiza la consistencia causal y por qué es relevante en relación con CAP?
    *Esperado: operaciones causalmente relacionadas se ven en el mismo orden; es el modelo más fuerte que mantiene disponibilidad ante particiones.*

## G. Transacciones (caps. 12–13)

46. Explique cada propiedad ACID y diferencie la "C" de ACID de la "C" de CAP.
    *Esperado: atomicidad, consistencia (invariantes de la aplicación), aislamiento, durabilidad; CAP: linealizabilidad entre réplicas.*

47. Describa las anomalías de lectura sucia, lectura no repetible y lectura fantasma, e indique el nivel de aislamiento mínimo que evita cada una.
    *Esperado: lectura sucia → lectura confirmada; no repetible → lectura repetible; fantasma → serializable.*

48. Compare el control de concurrencia pesimista (2PL), optimista (OCC) y multiversión (MVCC). ¿Cuándo conviene cada uno?
    *Esperado: 2PL bloquea, riesgo de interbloqueo, alta contención; OCC valida al final, pocos conflictos; MVCC instantáneas, lecturas no bloquean escrituras, cargas con muchas lecturas.*

49. Describa el protocolo de confirmación en dos fases y explique por qué es bloqueante. ¿Cómo mitiga Spanner este problema y qué papel cumple TrueTime?
    *Esperado: preparar/votar, confirmar/abortar; si el coordinador cae tras la preparación, participantes esperan con bloqueos; Spanner replica coordinador y participantes con Paxos; TrueTime da marcas de tiempo con incertidumbre acotada para serializabilidad estricta.*

50. Un servicio de reservas debe reservar vuelo, hotel y cobrar, cada uno en un servicio distinto. Diseñe la solución con una saga: pasos, compensaciones, uso del patrón *outbox*, requisitos de idempotencia y el problema de aislamiento.
    *Esperado: T1..T3 con C1, C2; orquestador con estado persistido; mensajes publicados vía outbox; consumidores y compensaciones idempotentes; estados intermedios visibles; bloqueos semánticos.*
