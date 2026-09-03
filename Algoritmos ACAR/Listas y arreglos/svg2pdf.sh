#!/usr/bin/env bash
# ---------------------------------------------------------------------
#  Convierte los SVG de ./img a PDF, para la versión Beamer.
#
#  Solo hace falta si compila con \usarsvgfalse (la opción por omisión).
#  Si prefiere \usarsvgtrue, no ejecute esto: instale Inkscape y compile
#  con  pdflatex -shell-escape listas_numpy.tex
#
#  Uso:  ./svg2pdf.sh
#
#  Requiere uno de estos:  inkscape  |  rsvg-convert  |  cairosvg
#     Kubuntu:  sudo apt install inkscape
#           o:  sudo apt install librsvg2-bin
#           o:  pip install cairosvg
# ---------------------------------------------------------------------
set -e
cd "$(dirname "$0")"

if [ ! -d img ]; then
    echo "ERROR: no encuentro la carpeta ./img junto a este script."
    exit 1
fi

if   command -v inkscape     >/dev/null 2>&1; then HERRAMIENTA=inkscape
elif command -v rsvg-convert >/dev/null 2>&1; then HERRAMIENTA=rsvg
elif python3 -c "import cairosvg" >/dev/null 2>&1; then HERRAMIENTA=cairosvg
else
    echo "ERROR: no hay conversor disponible."
    echo "Instale uno:  sudo apt install inkscape"
    echo "          o:  sudo apt install librsvg2-bin"
    echo "          o:  pip install cairosvg"
    exit 1
fi

echo "Convirtiendo con: $HERRAMIENTA"

for f in img/*.svg; do
    salida="${f%.svg}.pdf"
    case "$HERRAMIENTA" in
        inkscape)
            # Inkscape 1.x
            inkscape "$f" --export-type=pdf --export-filename="$salida" >/dev/null 2>&1 \
              || inkscape "$f" --export-pdf="$salida" >/dev/null 2>&1   # Inkscape 0.92
            ;;
        rsvg)
            rsvg-convert -f pdf -o "$salida" "$f"
            ;;
        cairosvg)
            python3 -c "import cairosvg,sys; cairosvg.svg2pdf(url=sys.argv[1], write_to=sys.argv[2])" "$f" "$salida"
            ;;
    esac
    echo "  $f  ->  $salida"
done

echo
echo "Listo. Ahora:  pdflatex listas_numpy.tex   (dos veces)"
