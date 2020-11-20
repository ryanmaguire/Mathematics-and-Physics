#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kissvg/src/kissvg.h>
#include <cairo/src/cairo.h>
#include <cairo/src/cairo-pdf.h>

kissvg_Label2D *kissvg_CreateLabel2D(const char *label_content,
                                     kissvg_TwoVector anchor,
                                     kissvg_Canvas2D *canvas)
{

    kissvg_Label2D *label;
    long length;
    double margins[4];
    kissvg_TwoVector shift;

    if (label_content == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateLabel2D\n\n"
             "Input label_content is NULL. Aborting.\n\n");
        exit(0);
    }

    label = malloc(sizeof(*label));

    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateLabel2D\n\n"
             "Malloc failed for label and returned NULL. Aborting.\n\n");
        exit(0);
    }

    length = strlen(label_content) + 1;

    margins[0] = kissvg_DefaultLabelMargin;
    margins[1] = kissvg_DefaultLabelMargin;
    margins[2] = kissvg_DefaultLabelMargin;
    margins[3] = kissvg_DefaultLabelMargin;

    label->label_content = malloc(sizeof(*label->label_content) * length);

    if (label->label_content == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_CreateLabel2D\n\n"
            "Malloc failed for label_content and returned NULL. Aborting.\n\n"
        );
        exit(0);
    }

    strcpy(label->label_content, label_content);

    shift = kissvg_NewTwoVector(0.0, 0.0);

    kissvg_Label2DSetShift(label, shift);
    kissvg_Label2DSetAnchor(label, anchor);
    kissvg_Label2DSetMargins(label, margins);
    kissvg_Label2DSetFontSize(label, kissvg_DefaultLabelFontSize);
    kissvg_Label2DSetBaselineSkip(label, kissvg_DefaultLabelBaselineSkip);
    kissvg_SetCanvas(label, canvas);
    kissvg_SetLineColor(label, kissvg_Black);

    return label;
}

void kissvg_DestroyLabel2D(kissvg_Label2D *label)
{
    free(label->label_content);
    free(label);
    return;
}

void kissvg_ResetLabel2DContent(kissvg_Label2D *label,
                                const char *label_content)
{
    long length;
    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ResetLabel2DContent\n\n"
             "Input label is NULL. Aborting.\n\n");
        exit(0);
    }
    else if (label->label_content == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ResetLabel2DContent\n\n"
             "Input label_content is NULL. Use kissvg_CreateLabel2D to\n"
             "create a label before trying to reset the content.\n\n");
        exit(0);
    }

    if (label_content == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_ResetLabel2DContent\n\n"
             "Input label_content is NULL. Aborting.\n\n");
        exit(0);
    }

    length = strlen(label_content);
    free(label->label_content);

    label->label_content = malloc(sizeof(*label->label_content) * length);
    strcpy(label->label_content, label_content);
    return;
}

void kissvg_Label2DSetAnchor(kissvg_Label2D *label, kissvg_TwoVector anchor)
{
    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Label2DSetAnchor\n\n"
             "Input label is NULL. Aborting.\n\n");
        exit(0);
    }
    label->anchor = anchor;
    return;
}

void kissvg_Label2DSetShift(kissvg_Label2D *label, kissvg_TwoVector shift)
{
    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Label2DSetShift\n\n"
             "Input label is NULL. Aborting.\n\n");
        exit(0);
    }
    label->shift = shift;
    return;
}

void kissvg_Label2DSetMargins(kissvg_Label2D *label, double margins[4])
{
    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Label2DSetMargins\n\n"
             "Input label is NULL. Aborting.\n\n");
        exit(0);
    }
    label->margins[0] = margins[0];
    label->margins[1] = margins[1];
    label->margins[2] = margins[2];
    label->margins[3] = margins[3];
    return;
}

void kissvg_Label2DSetFontSize(kissvg_Label2D *label, int font_size)
{
    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Label2DSetFontSize\n\n"
             "Input label is NULL. Aborting.\n\n");
        exit(0);
    }
    label->font_size = font_size;
    return;
}

void kissvg_Label2DSetBaselineSkip(kissvg_Label2D *label, int baseline_skip)
{
    if (label == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Label2DSetBaselineSkip\n\n"
             "Input label is NULL. Aborting.\n\n");
        exit(0);
    }
    label->baseline_skip = baseline_skip;
    return;
}

void kissvg_DrawLabel2D(cairo_t *cr, kissvg_Label2D *label)
{
    cairo_surface_t *image;
    kissvg_TwoVector anchor, shift;
    double x_label, y_label;
    double *margins;
    int font_size, baseline_skip;
    char *label_content;
    FILE *file;

    margins = kissvg_Label2DMargins(label);
    font_size = kissvg_Label2DFontSize(label);
    baseline_skip = kissvg_Label2DBaselineSkip(label);
    anchor = kissvg_Label2DAnchor(label);
    shift = kissvg_Label2DShift(label);
    label_content = kissvg_Label2DContent(label);

    file = fopen("__temp_filename__Label2D.tex", "w");

    if (file == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_DrawLabel2D\n\n"
             "fopen failed to open file and returned NULL. Aborting.\n\n");
        exit(0);
    }

    fprintf(
        file,
        "\\documentclass[crop=true,margin={%fpt %fpt %fpt %fpt}]{standalone}\n"
        "\\fontsize{%d}{%d}\\selectfont\n"
        "\\begin{document}\n"
        "%s\n"
        "\\end{document}\n",
        margins[0], margins[1], margins[2], margins[3],
        font_size, baseline_skip, label_content
    );

    fclose(file);
    system("pdflatex __temp_filename__Label2D.tex");
    system("pdftocairo -singlefile __temp_filename__Label2D.pdf "
           "__temp_filename__Label2D -png -r 200");

    system("rm -f __temp_filename__Label2D.pdf");
    system("rm -f *.log *.aux *.tex");

    x_label = kissvg_TwoVectorXComponent(anchor);
    y_label = kissvg_TwoVectorYComponent(anchor);

    x_label += kissvg_TwoVectorXComponent(shift);
    y_label += kissvg_TwoVectorYComponent(shift);

    image = cairo_image_surface_create_from_png("__temp_filename__Label2D.png");
    cairo_set_source_surface (cr, image, 0*x_label, 0*y_label);
    cairo_paint (cr);
    cairo_surface_destroy(image);
    system("rm -f __temp_filename__Label2D.*");

    return;
}
