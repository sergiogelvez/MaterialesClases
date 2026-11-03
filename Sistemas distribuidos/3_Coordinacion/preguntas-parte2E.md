# Banco de preguntas abiertas · Parte II: Coordinación (caps. 6–13)

Vitillo, *Understanding Distributed Systems* · Sistemas Distribuidos · UIS

---

## A. Modelos de sistema (cap. 6)

1. ¿Qué es un modelo de sistema y por qué es necesario para razonar sobre algoritmos distribuidos?

2. Compare los modelos de enlace con pérdida justa, confiable y confiable autenticado. ¿Cómo se construye uno confiable a partir de uno con pérdida justa?

3. Diferencie los modelos de proceso bizantino, de caída con recuperación y de caída con detención. Dé un ejemplo de sistema para el que sea apropiado el modelo bizantino.

4. En el modelo de caída con recuperación, ¿qué implicación tiene para un proceso el responder a un cliente antes de persistir un cambio?

5. Explique los modelos de temporización síncrono, asíncrono y parcialmente síncrono, y justifique por qué el parcialmente síncrono describe mejor los sistemas reales.

6. ¿Qué modelo de sistema asume Vitillo por defecto en el resto del libro?

## B. Detección de fallas (cap. 7)

7. ¿Por qué un cliente que no recibe respuesta no puede saber si el servidor cayó? Enumere los casos indistinguibles.

8. Explique el compromiso al elegir el valor de un *timeout* para detectar fallas.

9. Compare las técnicas de *ping* y *heartbeat*: quién inicia la comunicación y cómo se decide la sospecha.

10. ¿Por qué se dice que los detectores de fallas son imperfectos? ¿Qué consecuencia tiene para el diseño de algoritmos?

## C. Tiempo (cap. 8)

11. ¿Por qué no es buena idea usar el reloj de pared de cada máquina para ordenar eventos de un sistema distribuido?

12. ¿Qué es un reloj monótono, para qué sirve y para qué no sirve?

13. Defina la relación *sucedió-antes* y explique qué significa que dos eventos sean concurrentes.

14. Enuncie las reglas de actualización de un reloj de Lamport.

15. Tres procesos: P1 tiene eventos a (local) y b (envía m a P2); P2 tiene c (local) y d (recibe m). Calcule los relojes de Lamport de todos los eventos y diga si L(c) < L(b) implica c → b.

16. ¿Cómo se obtiene un orden total a partir de los relojes de Lamport y para qué puede servir?

17. Explique cómo funcionan los relojes vectoriales y cómo permiten detectar eventos concurrentes.

18. Dados V(x) = [2, 1, 0] y V(y) = [1, 2, 0], ¿qué relación hay entre x e y? Justifique.

19. Compare relojes de Lamport y vectoriales en costo y en capacidad de expresar la causalidad.

## D. Elección de líder (cap. 9)

20. ¿Qué propiedades de seguridad y vivacidad debe cumplir un algoritmo de elección de líder?

21. Describa los tres estados de un proceso en Raft y las transiciones entre ellos.

22. ¿Qué es un mandato (*term*) en Raft y qué papel cumple?

23. ¿Por qué en Raft no pueden ganar dos candidatos en el mismo mandato?

24. ¿Para qué sirven los tiempos de elección aleatorios en Raft?

25. Explique cómo implementar elección de líder usando un almacén linealizable con arrendamientos.

26. Describa el problema que resuelven las fichas de cercado con un escenario concreto.

27. ¿Por qué Vitillo recomienda minimizar el trabajo del líder o evitarlo cuando sea posible?

## E. Replicación y consistencia (cap. 10)

28. Explique la idea de replicación de máquinas de estado y por qué se reduce al problema del consenso.

29. Describa cómo Raft replica una operación desde que el líder la recibe hasta que se considera confirmada.

30. ¿Cuántas réplicas se necesitan para tolerar 2 fallas con Raft? ¿Por qué un número par de réplicas no aporta tolerancia adicional?

31. ¿Por qué Raft solo permite ser elegido líder a un candidato con un registro suficientemente actualizado?

32. Defina linealizabilidad y explique qué debe hacer el líder de Raft para ofrecer lecturas linealizables.

33. Compare consistencia fuerte, secuencial y eventual usando como ejemplo lecturas en un clúster Raft.

34. Enuncie el teorema CAP e ilústrelo con un escenario de partición de red.

35. ¿Qué agrega PACELC a CAP y por qué es más relevante en el día a día?

36. Explique la replicación en cadena: dónde entran las escrituras, dónde se leen y quién gestiona la configuración.

37. Compare replicación en cadena con Raft en latencia de escritura y sensibilidad a nodos lentos. ¿Qué mejora CRAQ?

## F. Evitar la coordinación (cap. 11)

38. Compare la difusión *best-effort*, confiable, por chismes y de orden total.

39. ¿Qué propiedades debe cumplir la operación de fusión de un CRDT basado en estado y por qué cada una es necesaria?

40. Dos réplicas de un G-Counter tienen {A: 4, B: 1} y {A: 2, B: 3}. Calcule el resultado de la fusión y el valor del contador. ¿Por qué no se suman los vectores?

41. Compare un registro "último escritor gana" con un registro multivalor ante escrituras concurrentes.

42. En un almacén estilo Dynamo con N = 3, ¿qué combinaciones de W y R garantizan que una lectura se solape con la última escritura confirmada? ¿Qué se gana con W = 1?

43. Explique la reparación en lectura y la antientropía. ¿Para qué se usan los árboles de Merkle?

44. Enuncie el teorema CALM y dé un ejemplo de problema monótono y uno no monótono.

45. ¿Qué garantiza la consistencia causal y por qué es relevante en relación con CAP?

## G. Transacciones (caps. 12–13)

46. Explique cada propiedad ACID y diferencie la "C" de ACID de la "C" de CAP.

47. Describa las anomalías de lectura sucia, lectura no repetible y lectura fantasma, e indique el nivel de aislamiento mínimo que evita cada una.

48. Compare el control de concurrencia pesimista (2PL), optimista (OCC) y multiversión (MVCC). ¿Cuándo conviene cada uno?

49. Describa el protocolo de confirmación en dos fases y explique por qué es bloqueante. ¿Cómo mitiga Spanner este problema y qué papel cumple TrueTime?

50. Un servicio de reservas debe reservar vuelo, hotel y cobrar, cada uno en un servicio distinto. Diseñe la solución con una saga: pasos, compensaciones, uso del patrón *outbox*, requisitos de idempotencia y el problema de aislamiento.
