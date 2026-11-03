# Banco de preguntas abiertas · Parte III: Escalabilidad (caps. 14–23)

Vitillo, *Understanding Distributed Systems* · Sistemas Distribuidos · UIS

Las marcadas con **(C)** tocan contenidos de complemento presentados en clase que van más allá del texto del libro.

---

## A. Patrones de escalabilidad

1. Defina escalabilidad y diferencie el escalado vertical del horizontal, con ventajas y limitaciones de cada uno.

2. Explique los tres patrones de escalabilidad que propone Vitillo y dé un ejemplo de cada uno.

3. ¿Qué diferencia hay entre lo que escala la replicación y lo que escala el particionamiento?

## B. Caché HTTP y CDN (caps. 14–15)

4. ¿Qué indica el encabezado `Cache-Control: max-age=3600` y qué hace el cliente cuando vence ese plazo?

5. Describa el intercambio de revalidación con `ETag` e `If-None-Match`. ¿Qué se ahorra con un `304 Not Modified`?

6. ¿Por qué se usan URL versionadas (p. ej., `app.3f9a2c.js`) para recursos estáticos y qué permite hacer con `max-age`?

7. ¿Qué es un proxy inverso y qué funciones puede cumplir además de la caché?

8. ¿Por qué se dice que la caché HTTP es eventualmente consistente?

9. Explique qué es una CDN y cómo dirige a cada usuario hacia un servidor cercano.

10. ¿Por qué una CDN puede reducir la latencia incluso para contenido que no se puede cachear?

11. ¿Para qué sirven las cachés intermedias de una CDN y por qué se particiona la caché dentro de un PoP?

12. Relacione el funcionamiento de una CDN con los capítulos 2, 3 y 4 del libro.

## C. Particionamiento (cap. 16)

13. ¿Por qué se particiona una base de datos y qué componentes se necesitan para enrutar una petición a la partición correcta?

14. Compare el particionamiento por rango y por hash en cuanto a consultas por rango y distribución de la carga.

15. ¿Qué es un punto caliente? Dé un ejemplo con claves basadas en fechas y una forma de mitigarlo.

16. Explique por qué asignar claves con `hash(k) mod N` es problemático al agregar un nodo. Ilustre con un ejemplo numérico.

17. Explique el hashing consistente y qué fracción de claves se mueve al agregar un nodo.

18. **(C)** ¿Qué problema resuelven los nodos virtuales en el hashing consistente?

19. Compare el rebalanceo con particiones estáticas y con particiones dinámicas.

20. ¿Qué dificultades introduce el particionamiento para consultas y transacciones que involucran varias particiones?

## D. Almacenamiento de archivos y de datos (caps. 17 y 19)

21. ¿Por qué no se recomienda guardar archivos grandes directamente en una base de datos y qué alternativa se usa?

22. Describa la arquitectura de Azure Storage: servicio de ubicación, sellos y las tres capas de un sello.

23. Identifique en Azure Storage al menos cuatro conceptos estudiados en las Partes I, II y III.

24. ¿Qué papel cumple la replicación en cadena en la capa de streams de Azure Storage y qué garantía de consistencia permite ofrecer?

25. Explique la estrategia de réplicas de lectura. ¿Qué compromiso implica usar replicación asíncrona frente a síncrona?

26. Un usuario actualiza su perfil y al recargar ve los datos anteriores. Explique la causa probable en una arquitectura con réplicas de lectura y proponga una solución.

27. Compare bases de datos relacionales y NoSQL en flexibilidad de consulta, transacciones y escalado.

28. En DynamoDB, ¿qué función cumplen la clave de partición y la clave de ordenamiento? Dé un ejemplo de consulta eficiente.

29. ¿Qué significa diseñar un modelo NoSQL "a partir de los patrones de acceso" y por qué suele implicar desnormalización?

30. Diferencie un índice secundario local de uno global en DynamoDB.

## E. Balanceo de carga (cap. 18)

31. ¿Por qué el balanceo de carga se aplica naturalmente a servicios sin estado? ¿Qué se hace con el estado?

32. Describa las tres funciones principales de un balanceador de carga según Vitillo.

33. Explique la estrategia de la potencia de dos opciones aleatorias y por qué es preferible a enviar siempre al servidor menos cargado.

34. Compare la verificación de salud pasiva y la activa. ¿Qué riesgo tiene un endpoint de salud que comprueba todas las dependencias?

35. ¿Qué limitaciones tiene el balanceo de carga por DNS?

36. Compare un balanceador de capa 4 y uno de capa 7: unidad de reparto, visibilidad del contenido, manejo de TLS y rendimiento.

37. ¿Qué es el retorno directo del servidor (DSR) en un balanceador L4 y qué ventaja tiene?

38. **(C)** ¿Por qué un balanceador L4 reparte mal el tráfico de conexiones HTTP/2 o gRPC de larga duración?

39. ¿Qué es un *sidecar* y qué relación tiene con una malla de servicios?

## F. Caché (cap. 20)

40. ¿Qué es la tasa de aciertos de una caché y de qué depende? ¿Cuándo una caché no ayuda?

41. Explique las políticas de expiración y de desalojo (por ejemplo, LRU).

42. Compare una caché local en proceso con una caché externa compartida.

43. ¿Qué es el efecto *thundering herd* en el contexto de las cachés y en qué situación ocurre?

44. Compare los patrones *cache-aside* e *inline* (*read-through/write-through*).

45. Vitillo advierte que una caché no debe ser una "muleta". Explique el riesgo y proponga dos mitigaciones.

## G. Microservicios, planos y mensajería (caps. 21–23)

46. Enumere beneficios e inconvenientes de los microservicios y explique por qué el libro recomienda empezar con un monolito.

47. Describa las funciones de un API *gateway* y dos riesgos de usarlo.

48. Diferencie plano de control y plano de datos, y explique qué es la estabilidad estática con un ejemplo.

49. ¿Qué es un lazo de control y cómo se aplica en un plano de control? Dé un ejemplo.

50. Un servicio de pedidos publica eventos que consumen los servicios de correo e inventario. Explique qué tipo de canal usaría, por qué la entrega es "al menos una vez", cómo lograr el efecto "exactamente una vez", y qué hacer con un mensaje que siempre falla.
