---
marp: true
theme: default
paginate: true
header: "Sistemas Distribuidos — Cap. 4: Descubrimiento"
footer: "Basado en *Understanding Distributed Systems* de Roberto Vitillo"
style: |
  section {
    font-family: 'Segoe UI', 'Helvetica Neue', Arial, sans-serif;
    background-color: #fdfdfd;
    color: #1a1a2e;
  }
  section.title {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    text-align: center;
    background: linear-gradient(135deg, #2B060E, #590D22, #3D0814);
    color: #ffe0e8;
  }
  section.title h1 {
    font-size: 2.4em;
    color: #fff;
    border-bottom: 3px solid #A4133C;
    padding-bottom: 10px;
  }
  section.title h2 {
    font-size: 1.2em;
    color: #d4a0ab;
    font-weight: 300;
  }
  section.section-divider {
    display: flex;
    flex-direction: column;
    justify-content: center;
    align-items: center;
    text-align: center;
    background: linear-gradient(135deg, #3D0814, #590D22);
    color: #ffe0e8;
  }
  section.section-divider h1 {
    font-size: 2.2em;
    color: #A4133C;
  }
  section.section-divider p {
    font-size: 1.1em;
    color: #d4a0ab;
  }
  h1 { color: #590D22; font-size: 1.6em; }
  h2 { color: #A4133C; font-size: 1.3em; }
  strong { color: #A4133C; }
  code { background: #f5e6ea; padding: 2px 6px; border-radius: 3px; font-size: 0.9em; }
  blockquote {
    border-left: 4px solid #A4133C;
    background: #FFF0F3;
    padding: 12px 16px;
    margin: 10px 0;
    font-style: italic;
    color: #333;
  }
  table { font-size: 0.85em; }
  th { background: #590D22; color: white; padding: 8px 12px; }
  td { border: 1px solid #ccc; padding: 6px 10px; }
  img[alt~="center"] {
    display: block;
    margin: 0 auto;
  }
  ul { font-size: 0.95em; }
  li { margin-bottom: 4px; }
  pre { background: #f8f0f2; border: 1px solid #e0c0c8; border-radius: 6px; font-size: 0.85em; }
---

<!-- _class: title -->
<!-- _paginate: false -->
<!-- _header: "" -->
<!-- _footer: "" -->

# Capítulo 4: Descubrimiento
## *Discovery*

Understanding Distributed Systems — Roberto Vitillo

<!--
Bienvenidos al capítulo 4. En los capítulos anteriores aprendimos a crear canales de comunicación confiables (TCP) y seguros (TLS). Pero para conectarnos con otro proceso, primero necesitamos saber dónde está — es decir, su dirección IP. Hoy vamos a ver cómo se resuelve ese problema en Internet a través del DNS.
-->

---

# Contexto: ¿dónde estamos?

En los capítulos anteriores usted aprendió a:

- **Cap. 2 — Reliable Links**: crear un canal confiable con TCP
- **Cap. 3 — Secure Links**: proteger el canal con TLS

Pero hay un problema previo que no hemos resuelto:

> Para abrir una conexión TCP con un servidor, usted necesita conocer su **dirección IP**. ¿Cómo la obtiene?

La respuesta es el **DNS** (Domain Name System) — el sistema de descubrimiento de Internet.

<!--
Hacer la conexión con los capítulos anteriores. Enfatizar que hasta ahora hemos asumido que conocíamos la IP del otro extremo. En la práctica, los humanos usamos nombres como "google.com" y algo tiene que traducir esos nombres a IPs.
-->

---

# DNS: la guía telefónica de Internet

![center](img/01-dns-phonebook.svg)

<!--
El DNS es como la guía telefónica, pero de Internet. Usted le da un nombre legible como www.example.com y el DNS le devuelve una dirección IP numérica. Es un almacén clave-valor distribuido, jerárquico y eventualmente consistente. Estos tres adjetivos son importantes y los vamos a descomponer uno a uno.
-->

---

# ¿Por qué no usar simplemente direcciones IP?

Las direcciones IP son difíciles de memorizar para los humanos, pero hay razones más importantes:

- **Las IPs cambian**: un servidor puede moverse de máquina, de proveedor de hosting, o de región geográfica. El nombre de dominio permanece igual.
- **Balanceo de carga**: un mismo nombre puede resolver a **múltiples IPs** diferentes, distribuyendo el tráfico.
- **Redundancia**: si un servidor falla, se actualiza el registro DNS para apuntar a otro.
- **Abstracción**: desacopla la identidad del servicio (nombre) de su ubicación (IP).

> DNS es un nivel de **indirección** fundamental en la arquitectura de Internet.

<!--
Este es un buen momento para preguntar a los estudiantes: ¿qué pasaría si todos los sitios web fueran accedidos solo por IP? Cada vez que un servicio cambiara de servidor, todos los clientes quedarían desconectados. DNS resuelve este acoplamiento.
-->

---

<!-- _class: section-divider -->

# La resolución DNS

¿Qué pasa cuando usted escribe una URL en el navegador?

<!--
Vamos a entrar en detalle en el proceso de resolución DNS, paso a paso.
-->

---

# Paso 1: la caché del navegador

Cuando usted escribe `www.example.com` en su navegador:

1. **El navegador revisa su caché local** — si ya resolvió este nombre recientemente, tiene la IP guardada y la reutiliza.

2. Si no la tiene, consulta la **caché del sistema operativo** (que puede tener un archivo `hosts` local con entradas estáticas).

3. Si tampoco, envía la consulta a un **resolver DNS** — típicamente un servidor DNS de su proveedor de Internet (ISP) o un resolver público como `8.8.8.8` (Google) o `1.1.1.1` (Cloudflare).

> La mayoría de las consultas DNS se resuelven desde alguna caché sin llegar a los servidores autoritativos.

<!--
Preguntar a los estudiantes si saben dónde está el archivo hosts en su sistema. En Windows está en C:\Windows\System32\drivers\etc\hosts. En Linux/Mac en /etc/hosts. Esto puede ser útil en desarrollo local para simular dominios.
-->

---

# Paso 2: resolución iterativa

Si el resolver no tiene la respuesta en su caché, inicia una **resolución iterativa**:

![center](img/02-dns-resolution.svg)

<!--
Recorrer el diagrama paso a paso. Enfatizar que se llama "iterativa" porque el resolver hace el trabajo: pregunta primero al root, luego al TLD, luego al autoritativo. El navegador hace una sola consulta y espera la respuesta final. 

Preguntar: ¿por qué el resolver no hace una sola consulta? Porque ningún servidor conoce todas las IPs. Cada nivel de la jerarquía conoce solo el siguiente.
-->

---

# La jerarquía DNS

DNS está organizado como un **árbol invertido**:

![center](img/03-dns-hierarchy.svg)

Cada nivel del árbol es gestionado por servidores diferentes, lo que permite **delegar la responsabilidad** y **escalar** a miles de millones de nombres.

<!--
Los root servers son solo 13 clusters (etiquetados de A a M), pero cada uno tiene réplicas anycast distribuidas por todo el mundo — en total hay más de 1500 instancias. Los TLD son gestionados por registros como Verisign (.com), PIR (.org), etc. Cada organización gestiona sus propios servidores autoritativos para sus dominios.
-->

---

# Los 13 servidores raíz

Los **root name servers** son el punto de entrada cuando el resolver no tiene información cacheada:

| Letra | Operador | Instancias globales |
|-------|----------|-------------------|
| A | Verisign | 10+ |
| B | USC-ISI | 1 |
| F | ISC | 200+ |
| J | Verisign | 200+ |
| K | RIPE NCC | 70+ |
| L | ICANN | 170+ |
| M | WIDE Project | 10+ |

---

En total hay **más de 1,500 instancias** distribuidas por todo el mundo usando **anycast**: la misma IP enruta al servidor más cercano geográficamente.

<!--
Anycast es un concepto clave aquí: múltiples servidores comparten la misma dirección IP, y el enrutamiento de la red se encarga de dirigir las consultas al más cercano. Esto da resiliencia y baja latencia. Si un servidor raíz falla, los demás siguen respondiendo transparentemente.
-->

---

# Tipos de registros DNS

No solo se resuelven nombres a IPs. DNS almacena varios tipos de registros:

![center](img/05-dns-records.svg)

<!--
Los más comunes son A y AAAA para resolución de nombres a IPs. CNAME es para alias — por ejemplo, si su blog está alojado en un CDN, blog.example.com puede ser un CNAME que apunta al CDN. MX es esencial para el correo electrónico. SRV permite descubrimiento de servicios con puerto específico.

Mencionar que también existe el registro TXT usado para verificación de dominios y SPF/DKIM en correo electrónico.
-->

---

<!-- _class: section-divider -->

# Caché y consistencia eventual

El rol del TTL y sus implicaciones

<!--
Ahora vamos a ver uno de los aspectos más importantes de DNS desde la perspectiva de sistemas distribuidos: el caching y la consistencia eventual.
-->

---

# Las capas de caché DNS

![center](img/04-dns-caching.svg)

Cada respuesta DNS incluye un **TTL** (Time to Live) que indica cuánto tiempo puede ser cacheada.

<!--
El caching es lo que hace que DNS sea rápido y escalable. Sin caché, cada consulta requeriría recorrer toda la jerarquía, generando una carga inmensa en los servidores raíz. Pero el caching tiene un costo: consistencia eventual.
-->

---

# Consistencia eventual en DNS

El DNS es **eventualmente consistente**: si usted cambia la IP asociada a un nombre de dominio, el cambio **no se refleja inmediatamente** en todos los clientes.

**¿Por qué?**
- Cada caché retiene la respuesta anterior hasta que expire su TTL.
- Un TTL de 1 hora significa que pueden pasar hasta 60 minutos antes de que todos los clientes vean el nuevo valor.
- Algunos resolvers ignoran el TTL y cachean por más tiempo.

**Implicaciones prácticas:**
- Al migrar un servicio, **reduzca el TTL antes** de la migración (e.g., bájelo a 60 segundos días antes).
- Después de la migración, espere al menos un ciclo de TTL antes de apagar el servidor viejo.
- Nunca asuma que un cambio DNS es "instantáneo".

<!--
Este es un excelente ejemplo de consistencia eventual en la vida real. Preguntar a los estudiantes: si usted está migrando un servicio de un servidor a otro, ¿qué pasaría si cambia la IP en DNS y apaga el servidor viejo inmediatamente? Respuesta: muchos clientes seguirían intentando conectarse a la IP vieja durante un tiempo igual al TTL.
-->

---

# TTL: el compromiso rendimiento vs. frescura

| TTL corto (60s) | TTL largo (1h+) |
|---|---|
| Los cambios se propagan rápido | Los cambios tardan en propagarse |
| Mayor carga en servidores DNS | Menor carga en servidores DNS |
| Mayor latencia percibida (más consultas) | Mejor rendimiento (más cache hits) |
| Ideal para migración o failover | Ideal para servicios estables |

> El TTL es un ejemplo clásico del compromiso entre **frescura de datos** y **rendimiento**.

<!--
Relacionar con el concepto general de caching en sistemas distribuidos: siempre hay un trade-off entre cuán actualizado está el dato y cuánto cuesta obtenerlo. DNS no es diferente.
-->

---

# DNS como sistema distribuido

DNS es uno de los sistemas distribuidos **más exitosos** de la historia. Veamos sus propiedades:

| Propiedad | Cómo la implementa DNS |
|---|---|
| **Distribuido** | Miles de servidores en todo el mundo |
| **Jerárquico** | Root → TLD → Autoritative → Subdominio |
| **Escalable** | Cada nivel delega al siguiente; anycast |
| **Eventualmente consistente** | Caché con TTL en cada nivel |
| **Tolerante a fallos** | Múltiples servidores por nivel; anycast |
| **Descentralizado** | Cada organización administra su zona |

---

> DNS es un caso de estudio perfecto de los principios de diseño de sistemas distribuidos que veremos a lo largo del curso.

<!--
DNS encarna casi todos los conceptos que veremos en el resto del libro: distribución, replicación, consistencia eventual, tolerancia a fallos, particionamiento (por zonas), caching. Es por eso que Vitillo lo incluye temprano en el libro — es un ejemplo concreto y familiar de todos estos conceptos abstractos.
-->

---

<!-- _class: section-divider -->

# Más allá de la resolución básica

Aspectos avanzados del descubrimiento de servicios

<!--
Vamos a complementar el contenido del capítulo con algunos temas adicionales que son relevantes en la práctica.
-->

---

# DNS y la seguridad

DNS fue diseñado en los años 80 sin consideraciones de seguridad. Esto ha generado problemas:

- **DNS Spoofing / Cache Poisoning**: un atacante inyecta registros falsos en la caché de un resolver, redirigiendo tráfico a un servidor malicioso.
- **DNS Hijacking**: un atacante modifica los registros DNS directamente en el proveedor.
- **DNS Amplification DDoS**: se usa DNS como amplificador de tráfico en ataques de denegación de servicio.

---

**Soluciones:**
- **DNSSEC** (DNS Security Extensions): firma criptográficamente los registros DNS para verificar su autenticidad.
- **DoH** (DNS over HTTPS) / **DoT** (DNS over TLS): cifra las consultas DNS para prevenir espionaje y manipulación.

<!--
Relacionar con el capítulo 3: al igual que HTTP sin TLS es inseguro, las consultas DNS normales viajan en texto plano por UDP. Cualquiera en la red puede ver qué dominios está consultando usted, e incluso modificar las respuestas. DoH y DoT resuelven eso cifrando las consultas.
-->

---

# Descubrimiento de servicios en la práctica

En sistemas distribuidos modernos (microservicios, cloud), el descubrimiento de servicios va **más allá de DNS**:

| Mecanismo | Ejemplo | Uso típico |
|---|---|---|
| **DNS clásico** | Registros A/CNAME | Servicios públicos (web) |
| **DNS interno** | CoreDNS, Route53 | Servicios dentro de un cluster |
| **Service Registry** | Consul, Eureka, etcd | Microservicios dinámicos |
| **Service Mesh** | Istio, Linkerd | Descubrimiento + balanceo + seguridad |

> En entornos cloud, los servidores se crean y destruyen constantemente. El descubrimiento de servicios debe ser **dinámico y automático**.

<!--
Este tema se expandirá en capítulos posteriores del libro (especialmente en particionamiento y balanceo de carga). Por ahora, lo importante es entender que DNS es la base, pero los sistemas modernos necesitan mecanismos más sofisticados que reaccionen más rápido a cambios.
-->

---

# Ejemplo práctico: `nslookup` y `dig`

Usted puede explorar DNS desde la terminal:

```bash
# Consulta básica
nslookup www.google.com

# Consulta detallada con dig (Linux/Mac)
dig www.google.com

# Ver registros MX (correo)
dig example.com MX

# Ver toda la cadena de resolución
dig +trace www.example.com
```

**Ejercicio sugerido:** use `dig +trace www.example.com` y observe cómo la consulta viaja desde el root NS hasta el servidor autoritativo, nivel por nivel.

<!--
Si hay tiempo en clase, hacer una demostración en vivo con dig +trace. Esto hace tangible todo el proceso de resolución iterativa que vimos en la teoría. nslookup funciona en Windows sin instalar nada adicional. dig requiere instalar bind-utils en Linux o usar WSL en Windows.
-->

---

# Puntos clave del capítulo

1. **DNS** es un almacén clave-valor distribuido, jerárquico y eventualmente consistente que traduce nombres de dominio a direcciones IP.

2. La **resolución iterativa** recorre la jerarquía: Root → TLD → Autoritativo, con caching en cada nivel.

3. El **TTL** controla cuánto tiempo se cachea una respuesta, estableciendo un compromiso entre rendimiento y frescura.

4. DNS es **eventualmente consistente**: los cambios no son instantáneos. Esto tiene implicaciones importantes para migraciones y failover.

---

5. DNS fue diseñado sin seguridad; **DNSSEC**, **DoH** y **DoT** abordan estas limitaciones.

6. En sistemas distribuidos modernos, el descubrimiento de servicios extiende DNS con registros dinámicos, health checks y service meshes.

<!--
Resumir los puntos clave y preguntar si hay dudas antes de cerrar.
-->

---

# Para profundizar

- **RFC 1034 / 1035** — Especificación original de DNS
- **RFC 4033-4035** — DNSSEC
- Herramienta: `dig +trace` para ver la resolución completa
- Herramienta: `nslookup` disponible en todos los sistemas operativos
- Cloudflare Learning Center: https://www.cloudflare.com/learning/dns/

> **Ejercicio sugerido:** investigue qué registros DNS tiene el dominio de su universidad. Use `dig` o `nslookup` para encontrar registros A, MX, TXT y NS. ¿Cuántos servidores de correo tiene?

<!--
El ejercicio con el dominio de la universidad hace que el tema sea personal y relevante. Los estudiantes pueden descubrir cosas interesantes sobre la infraestructura de su propia institución.
-->

---

<!-- _class: title -->

# ¿Preguntas?

## Capítulo 4: Descubrimiento — *Discovery*

<!--
Cerrar el capítulo y dar paso a preguntas. Recordar a los estudiantes que DNS aparecerá de nuevo en capítulos posteriores cuando hablemos de balanceo de carga y particionamiento.
-->
