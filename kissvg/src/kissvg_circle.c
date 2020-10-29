
#include <kissvg/src/kissvg_circle.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

kissvg_Circle *kissvg_Create_Circle(kissvg_TwoVector P, double r,
                                    kissvg_Palette *palette)
{
    kissvg_Circle *circle;

    circle = malloc(sizeof(*circle));

    if (circle == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CreateCircle\n\n"
             "Malloc failed to create circle and return NULL. Aborting.");
        exit(0);
    }

    circle->error_occured = kissvg_False;
    circle->is_line = kissvg_False;
    circle->error_message = NULL;
    circle->center = P;
    circle->radius = r;
    circle->palette = palette;
    return circle;
}

void kissvg_Circle_Set_Line(kissvg_Circle *circle, kissvg_TwoVector P,
                            kissvg_TwoVector V)
{
    if (circle == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_Reset_Circle\n\n"
            "Malloc failed to create circle and return NULL. Aborting."
        );
        exit(0);
    }

    circle->is_line = kissvg_True;
    circle->P = P;
    circle->V = V;
    return;
}


void kissvg_Circle_Set_Error_Message(kissvg_Circle *circle, char *mes)
{
    long mes_len;
    if (circle == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Circle_Set_Error_Message\n\n"
             "Input circle is NULL. Aborting.");
        exit(0);
    }

    if (mes == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_CircleSetErrorMessage\n\n"
             "Input error message is NULL. Aborting.");
        exit(0);
    }

    circle->error_occured = kissvg_True;

    mes_len = strlen(mes)+1;
    circle->error_message = malloc(sizeof(*circle->error_message)*mes_len);
    strcpy(circle->error_message, mes);
    return;
}

void kissvg_Reset_Circle(kissvg_Circle *circle, kissvg_TwoVector P, double r)
{
    if (circle == NULL)
    {
        puts(
            "Error Encountered: KissVG\n"
            "\tFunction: kissvg_Reset_Circle\n\n"
            "Malloc failed to create circle and return NULL. Aborting."
        );
        exit(0);
    }

    circle->center = P;
    circle->radius = r;
    circle->is_line = kissvg_False;
    circle->error_occured = kissvg_False;

    if (circle->error_message != NULL)
        free(circle->error_message);

    circle->error_message = NULL;

    return;
}

void kissvg_Destroy_Circle(kissvg_Circle **circle_pointer)
{
    char *err_mes;
    kissvg_Circle *circle;

    /*  Check that the input pointer was not NULL.                            */
    if (circle_pointer == NULL)
    {
        puts("Error Encountered: KissVG\n"
             "\tFunction: kissvg_Destroy_Circle\n\n"
             "Input circle_pointer is NULL. Aborting.");
        exit(0);
    }

    /*  Cast the circle_pointer to the circle variable.                       */
    circle = *circle_pointer;

    /*  If an error message was attached to the circle at any point, we need  *
     *  to free this as well to avoid memory leaks.                           */
    if (kissvg_Has_Error(circle))
    {
        err_mes = kissvg_Error_Message(circle);
        if (err_mes != NULL)
            free(err_mes);

        /*  Set the pointer to NULL once we're done with it.                  */
        err_mes = NULL;
    }

    /*  The only thing malloc'd by kissvg_Create_Circle is the circle itself  *
     *  so we only need to free this. If you already destroyed this, the      *
     *  circle variable is set to NULL after being free'd to prevent you from *
     *  free'ing it twice. However, it's best to just keep track of what      *
     *  you've created and destroyed.                                         */
    if (circle == NULL)
        puts("Warning: KissVG\n"
             "\tFunction: kissvg_Destroy_Circle\n\n"
             "You are calling kissvg_Destroy_Circle on a circle that is\n"
             "NULL. You likely already destroyed this circle. Returning.\n");

    /*  If it's not NULL, we should be able to safely free it.                */
    else
    {
        /*  Free the circle and set to NULL to prevent free'ing twice.        */
        free(circle);
        circle = NULL;
    }

    return;
}