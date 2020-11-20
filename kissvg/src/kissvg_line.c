

#include <stdlib.h>
#include <stdio.h>
#include <kissvg/src/kissvg_line.h>
#include <kissvg/src/kissvg_vector.h>

kissvg_Line2D *kissvg_Create_Line2D_From_Two_Points(kissvg_TwoVector P,
                                                    kissvg_TwoVector Q,
                                                    kissvg_Palette *palette)
{
    kissvg_Line2D *line;
    kissvg_TwoVector V;

    line = malloc(sizeof(*line));

    if (line == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateLineFromTwoPoints\n\n"
             "Malloc failed to create line and return NULL. Aborting.");
        exit(0);
    }

    V = kissvg_TwoVector_Subtract(Q, P);

    line->P = P;
    line->V = V;
    line->palette = palette;
    line->error_occured = kissvg_False;
    line->error_message = NULL;

    return line;
}

kissvg_Line2D *
kissvg_Create_Line2D_From_Point_And_Tangent(kissvg_TwoVector P,
                                            kissvg_TwoVector V,
                                            kissvg_Palette *palette)
{
    kissvg_Line2D *line;
    line = malloc(sizeof(*line));
    if (line == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateLineFromPointAndTangent\n\n"
             "Malloc failed to create line and return NULL. Aborting.");
        exit(0);
    }

    line->P = P;
    line->V = V;
    line->palette = palette;
    line->error_occured = kissvg_False;
    line->error_message = NULL;

    return line;
}

void kissvg_Destroy_Line2D(kissvg_Line2D **line_pointer)
{
    free(*line_pointer);
    *line_pointer = NULL;
    return;
}
