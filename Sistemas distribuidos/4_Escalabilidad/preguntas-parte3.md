# Banco de preguntas abiertas · Parte III: Escalabilidad (caps. 14–23)

Vitillo, *Understanding Distributed Systems* · Sistemas Distribuidos · UIS

Cada pregunta incluye, en cursiva, los **elementos esperados** en una respuesta completa, como apoyo para la calificación. Las marcadas con **(C)** tocan contenidos de complemento presentados en clase que van más allá del texto del libro.

---

## A. Patrones de escalabilidad

1. Defina escalabilidad y diferencie el escalado vertical del horizontal, con ventajas y limitaciones de cada uno.
   *Esperado: atender más carga agregando recursos; vertical: máquina más grande, simple, con techo y costo; horizontal: más máquinas, sin techo teórico, exige coordinación.*

2. Explique los tres patrones de escalabilidad que propone Vitillo y dé un ejemplo de cada uno.
   *Esperado: descomposición funcional (servicios), particionamiento (shards), replicación (réplicas, cachés, CDN).*

3. ¿Qué diferencia hay entre lo que escala la replicación y lo que escala el particionamiento?
   *Esperado: replicación escala lecturas y disponibilidad (mismos datos en varios nodos); particionamiento escala escrituras y volumen (cada nodo con una parte).*

## B. Caché HTTP y CDN (caps. 14–15)

4. ¿Qué indica el encabezado `Cache-Control: max-age=3600` y qué hace el cliente cuando vence ese plazo?
   *Esperado: la respuesta puede reutilizarse 3600 s sin consultar al servidor; luego queda obsoleta y se revalida.*

5. Describa el intercambio de revalidación con `ETag` e `If-None-Match`. ¿Qué se ahorra con un `304 Not Modified`?
   *Esperado: el cliente envía la ETag; si no cambió, 304 sin cuerpo; se ahorra transferir el contenido, no la ida y vuelta.*

6. ¿Por qué se usan URL versionadas (p. ej., `app.3f9a2c.js`) para recursos estáticos y qué permite hacer con `max-age`?
   *Esperado: cada versión es un recurso distinto; se puede usar caché muy larga/immutable sin impedir ver cambios.*

7. ¿Qué es un proxy inverso y qué funciones puede cumplir además de la caché?
   *Esperado: servidor frente a la aplicación que atiende a todos los clientes; terminación TLS, compresión, límite de tasa, balanceo.*

8. ¿Por qué se dice que la caché HTTP es eventualmente consistente?
   *Esperado: el cliente puede servir una copia vieja hasta que expire y se revalide; converge con el servidor.*

9. Explique qué es una CDN y cómo dirige a cada usuario hacia un servidor cercano.
   *Esperado: red superpuesta de servidores distribuidos que cachean contenido; balanceo global por DNS y/o anycast según ubicación, salud y carga.*

10. ¿Por qué una CDN puede reducir la latencia incluso para contenido que no se puede cachear?
    *Esperado: el cliente hace handshakes TCP/TLS con un PoP cercano (RTT bajo); el PoP usa conexiones persistentes y rutas optimizadas hacia el origen.*

11. ¿Para qué sirven las cachés intermedias de una CDN y por qué se particiona la caché dentro de un PoP?
    *Esperado: protegen al origen reduciendo fallos que llegan a él; particionar (hashing consistente) aprovecha la capacidad total sin duplicar.*

12. Relacione el funcionamiento de una CDN con los capítulos 2, 3 y 4 del libro.
    *Esperado: reduce RTT de TCP (cap. 2) y TLS (cap. 3); usa DNS para el enrutamiento global (cap. 4).*

## C. Particionamiento (cap. 16)

13. ¿Por qué se particiona una base de datos y qué componentes se necesitan para enrutar una petición a la partición correcta?
    *Esperado: datos o carga exceden un nodo; mapa partición→nodo en un servicio de coordinación; gateway o cliente que lo consulta.*

14. Compare el particionamiento por rango y por hash en cuanto a consultas por rango y distribución de la carga.
    *Esperado: rango: consultas por rango eficientes, riesgo de puntos calientes; hash: distribución uniforme, rangos dispersos.*

15. ¿Qué es un punto caliente? Dé un ejemplo con claves basadas en fechas y una forma de mitigarlo.
    *Esperado: partición con carga desproporcionada; todas las escrituras recientes caen en el último rango; prefijos aleatorios/compuestos, dividir particiones.*

16. Explique por qué asignar claves con `hash(k) mod N` es problemático al agregar un nodo. Ilustre con un ejemplo numérico.
    *Esperado: al cambiar N casi todas las claves cambian de nodo (solo ≈ 1/(N+1) se quedan); ejemplo con módulos correctos.*

17. Explique el hashing consistente y qué fracción de claves se mueve al agregar un nodo.
    *Esperado: nodos y claves en un anillo; clave al siguiente nodo en sentido horario; se mueve ≈ 1/N de las claves (solo las del arco del nuevo nodo).*

18. **(C)** ¿Qué problema resuelven los nodos virtuales en el hashing consistente?
    *Esperado: con pocos nodos los arcos son desiguales y la carga se desequilibra; varias posiciones por nodo físico reparten mejor.*

19. Compare el rebalanceo con particiones estáticas y con particiones dinámicas.
    *Esperado: estáticas: muchas más particiones que nodos, se mueven completas, número fijo; dinámicas: dividir/fusionar según tamaño o carga, se adaptan.*

20. ¿Qué dificultades introduce el particionamiento para consultas y transacciones que involucran varias particiones?
    *Esperado: hay que consultar varias particiones y combinar; transacciones requieren protocolos como 2PC; mayor latencia y complejidad.*

## D. Almacenamiento de archivos y de datos (caps. 17 y 19)

21. ¿Por qué no se recomienda guardar archivos grandes directamente en una base de datos y qué alternativa se usa?
    *Esperado: tamaño y costo, carga en la BD; almacén de objetos/blobs (S3, Azure Blob) con la referencia en la BD.*

22. Describa la arquitectura de Azure Storage: servicio de ubicación, sellos y las tres capas de un sello.
    *Esperado: ubicación asigna cuentas a sellos y actualiza DNS; front-end sin estado (autenticación, enrutamiento); particiones (abstracciones, rangos, administrador); streams (extensiones solo agregar, replicación en cadena).*

23. Identifique en Azure Storage al menos cuatro conceptos estudiados en las Partes I, II y III.
    *Esperado: DNS, replicación en cadena, plano de control con consenso, particionamiento por rango, servicio sin estado con balanceo, escalar agregando sellos.*

24. ¿Qué papel cumple la replicación en cadena en la capa de streams de Azure Storage y qué garantía de consistencia permite ofrecer?
    *Esperado: replica las extensiones de forma ordenada; consistencia fuerte.*

25. Explique la estrategia de réplicas de lectura. ¿Qué compromiso implica usar replicación asíncrona frente a síncrona?
    *Esperado: líder para escrituras, réplicas para lecturas; asíncrona: baja latencia pero lecturas atrasadas y posible pérdida si el líder cae; síncrona: durabilidad con más latencia.*

26. Un usuario actualiza su perfil y al recargar ve los datos anteriores. Explique la causa probable en una arquitectura con réplicas de lectura y proponga una solución.
    *Esperado: lectura desde réplica atrasada (consistencia eventual); leer las propias escrituras del líder, por un tiempo o según versión.*

27. Compare bases de datos relacionales y NoSQL en flexibilidad de consulta, transacciones y escalado.
    *Esperado: SQL: consultas flexibles, ACID general, escalado vertical + réplicas; NoSQL: consultas por patrones diseñados, transacciones limitadas, escalado horizontal nativo.*

28. En DynamoDB, ¿qué función cumplen la clave de partición y la clave de ordenamiento? Dé un ejemplo de consulta eficiente.
    *Esperado: partición por hash de la clave de partición; orden dentro de la partición por la de ordenamiento; p. ej., pedidos de un cliente entre dos fechas.*

29. ¿Qué significa diseñar un modelo NoSQL "a partir de los patrones de acceso" y por qué suele implicar desnormalización?
    *Esperado: primero se definen las consultas y luego claves e índices que las resuelven sin recorrer la tabla; duplicar datos donde se leen para evitar uniones.*

30. Diferencie un índice secundario local de uno global en DynamoDB.
    *Esperado: local: misma clave de partición, otra de ordenamiento; global: otra clave de partición, permite consultar por otros atributos a través de particiones.*

## E. Balanceo de carga (cap. 18)

31. ¿Por qué el balanceo de carga se aplica naturalmente a servicios sin estado? ¿Qué se hace con el estado?
    *Esperado: cualquier réplica puede atender cualquier petición; el estado se lleva a una BD o caché externa.*

32. Describa las tres funciones principales de un balanceador de carga según Vitillo.
    *Esperado: algoritmo de reparto, descubrimiento de servicios, verificación de salud.*

33. Explique la estrategia de la potencia de dos opciones aleatorias y por qué es preferible a enviar siempre al servidor menos cargado.
    *Esperado: elegir dos al azar y el menos cargado de ellos; la información de carga es desactualizada y todos enviarían al mismo "libre" (efecto rebaño).*

34. Compare la verificación de salud pasiva y la activa. ¿Qué riesgo tiene un endpoint de salud que comprueba todas las dependencias?
    *Esperado: pasiva observa errores del tráfico; activa consulta un endpoint; si una dependencia falla, todas las réplicas se marcan enfermas y se retiran a la vez.*

35. ¿Qué limitaciones tiene el balanceo de carga por DNS?
    *Esperado: no conoce la salud de los servidores; cachés con TTL retrasan los cambios; reparto desigual.*

36. Compare un balanceador de capa 4 y uno de capa 7: unidad de reparto, visibilidad del contenido, manejo de TLS y rendimiento.
    *Esperado: L4 reparte conexiones/flujos, no ve HTTP, TLS pasa cifrado, muy rápido; L7 reparte peticiones, ve rutas y encabezados, puede terminar TLS, más costoso.*

37. ¿Qué es el retorno directo del servidor (DSR) en un balanceador L4 y qué ventaja tiene?
    *Esperado: las respuestas van del servidor al cliente sin pasar por el balanceador; reduce su carga (las respuestas suelen ser mayores que las peticiones).*

38. **(C)** ¿Por qué un balanceador L4 reparte mal el tráfico de conexiones HTTP/2 o gRPC de larga duración?
    *Esperado: una sola conexión transporta muchas peticiones; el L4 asigna la conexión completa a una réplica, que recibe toda esa carga.*

39. ¿Qué es un *sidecar* y qué relación tiene con una malla de servicios?
    *Esperado: proxy L7 desplegado junto a cada instancia de servicio; el conjunto de sidecars gestionado centralmente forma la malla (balanceo, mTLS, reintentos).*

## F. Caché (cap. 20)

40. ¿Qué es la tasa de aciertos de una caché y de qué depende? ¿Cuándo una caché no ayuda?
    *Esperado: fracción de peticiones servidas desde caché; depende de la repetición de accesos; no ayuda si los datos cambian constantemente o se consultan una vez.*

41. Explique las políticas de expiración y de desalojo (por ejemplo, LRU).
    *Esperado: expiración (TTL) limita la antigüedad de los datos; desalojo decide qué quitar cuando se llena; LRU elimina el usado hace más tiempo.*

42. Compare una caché local en proceso con una caché externa compartida.
    *Esperado: local: mínima latencia, duplicada e inconsistente entre instancias, fría tras despliegues; externa: compartida, particionada y replicada, pero agrega latencia de red y una dependencia.*

43. ¿Qué es el efecto *thundering herd* en el contexto de las cachés y en qué situación ocurre?
    *Esperado: muchas peticiones van a la vez a la BD al vaciarse o expirar la caché (despliegue, reinicio, clave popular); puede saturarla.*

44. Compare los patrones *cache-aside* e *inline* (*read-through/write-through*).
    *Esperado: cache-aside: la aplicación consulta la caché y, si falla, la BD y llena la caché; inline: la aplicación solo habla con la caché, que gestiona la BD.*

45. Vitillo advierte que una caché no debe ser una "muleta". Explique el riesgo y proponga dos mitigaciones.
    *Esperado: si la BD solo aguanta con la caché, una caché vacía la tumba; dimensionar la BD, calentar gradualmente, descartar carga, limitar concurrencia por clave.*

## G. Microservicios, planos y mensajería (caps. 21–23)

46. Enumere beneficios e inconvenientes de los microservicios y explique por qué el libro recomienda empezar con un monolito.
    *Esperado: independencia de equipos, despliegue y escalado; costos: tecnologías, comunicación, acoplamiento, pruebas, operación, consistencia eventual; límites claros antes de dividir.*

47. Describa las funciones de un API *gateway* y dos riesgos de usarlo.
    *Esperado: enrutamiento, composición, traducción, funciones transversales (autenticación, límite de tasa, caché); riesgos: cuello de botella/punto único de falla, acoplamiento si acumula lógica.*

48. Diferencie plano de control y plano de datos, y explique qué es la estabilidad estática con un ejemplo.
    *Esperado: datos procesa cada petición en el camino crítico; control configura y gestiona; estabilidad estática: el plano de datos sigue con la última configuración si el control cae (p. ej., máquinas virtuales que siguen corriendo aunque no se puedan crear nuevas).*

49. ¿Qué es un lazo de control y cómo se aplica en un plano de control? Dé un ejemplo.
    *Esperado: monitorear estado actual, comparar con el deseado, actuar para corregir; Kubernetes (réplicas deseadas), autoescalado.*

50. Un servicio de pedidos publica eventos que consumen los servicios de correo e inventario. Explique qué tipo de canal usaría, por qué la entrega es "al menos una vez", cómo lograr el efecto "exactamente una vez", y qué hacer con un mensaje que siempre falla.
    *Esperado: publicación-suscripción; tras fallas o timeouts de visibilidad el mensaje se reentrega; consumidores idempotentes/deduplicación por id; tras N intentos, cola de mensajes muertos; monitorear acumulación.*
