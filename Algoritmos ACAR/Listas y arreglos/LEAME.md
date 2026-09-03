# Listas y arreglos en Python — dos versiones

Presentación sobre listas de Python y NumPy para el curso de programación
orientada a la computación científica. Las dos versiones tienen el mismo
contenido y comparten la carpeta `img/`.

```
listas_numpy.md      versión Marpit
listas_numpy.tex     versión Beamer
svg2pdf.sh           conversor de SVG a PDF (solo para la versión Beamer)
img/                 ocho diagramas en SVG, compartidos
```

## Marpit

```bash
marp listas_numpy.md --pdf --allow-local-files
marp listas_numpy.md            # HTML
marp -p listas_numpy.md         # vista previa con recarga
```

Las notas del presentador están en comentarios HTML y salen en el PDF con
`--pdf-notes`.

## Beamer

Beamer no incluye SVG directamente. Hay dos caminos.

**Camino A — convertir una vez a PDF (por omisión).**

```bash
./svg2pdf.sh                 # requiere inkscape, rsvg-convert o cairosvg
pdflatex listas_numpy.tex    # dos veces
```

**Camino B — usar los SVG en cada compilación.**

Cambie `\usarsvgfalse` por `\usarsvgtrue` en la cabecera del `.tex` y compile:

```bash
pdflatex -shell-escape listas_numpy.tex
```

Requiere Inkscape instalado. Es más lento, pero evita el paso de conversión.

**Dependencias LaTeX**: `beamer`, `listings`, `tcolorbox`, `tabularx`,
`booktabs`, `helvet` y `babel` en español. En Kubuntu:

```bash
sudo apt install texlive-latex-recommended texlive-latex-extra texlive-lang-spanish
```

Las notas del presentador están en `\note{}`. Para verlas, descomente la línea
`\setbeameroption{show notes on second screen=right}` o use `pdfpc`.

## Sobre los diagramas

`rendimiento.svg` muestra una medición hecha con Python 3 y NumPy 2.4 sobre
un millón de elementos: unos 38 ms para la comprensión de lista frente a
0,8 ms para `a * a`, y 32 MB frente a 8 MB de memoria. Los valores absolutos
dependen de la máquina; conviene repetir la medición en vivo con `%timeit`.
