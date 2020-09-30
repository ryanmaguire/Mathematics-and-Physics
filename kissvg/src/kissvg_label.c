#include <stdio.h>
#include <string.h>
#include <kissvg/include/kissvg.h>
#include <cairo.h>
#include <cairo-pdf.h>

void kissvg_DrawLabel2D(cairo_t *cr, kissvg_Label2D *label)
{
    cairo_surface_t *image;
    kissvg_Canvas2D *canvas;
    kissvg_TwoVector label_pos;
    double x_inches, y_inches;
    double x_label, y_label;
    double margins[4];
    int font_size, baseline_skip;
    char *filename;
    char *label_content;
    FILE *file;

    strcpy(filename, ".pdf");

    file = fopen(filename, "w");
    if (file == NULL)
    {
        fprintf(stderr, "Failed to open file %s for writing.\n", filename);
        return 1;
    }

    fprintf(
        file,
        "\\documentclass[crop=true,margin={%fpt %fpt %fpt %fpt}]{standalone}\n"
        "\fontsize{%d}{%d}\selectfont\n"
        "\begin{document}\n"
        "%s\n"
        "\end{document})\n",
        margins[0], margins[1], margins[2], margins[3],
        font_size, baseline_skip, label_content
    );

    fclose(file);

    canvas = kissvg_GetCanvas(label);

    x_inches = kissvg_Canvas2DXInches(canvas);
    y_inches = kissvg_Canvas2DYInches(canvas);

    x_label = kissvg_TwoVectorXComponent(label_pos);
    y_label = kissvg_TwoVectorYComponent(label_pos);

    image = cairo_image_surface_create(filename, x_inches, y_inches);
    cairo_set_source_surface (cr, image, 0, 0);
    cairo_paint (cr);
    cairo_surface_destroy(image);
    return;
}
