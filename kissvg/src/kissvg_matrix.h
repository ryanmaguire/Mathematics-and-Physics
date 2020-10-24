
/*  Include guard for this file to prevent including this twice.              */
#ifndef _KISSVG_MATRIX_H_
#define _KISSVG_MATRIX_H_

#include <kissvg/src/kissvg_defs.h>
#include <kissvg/src/kissvg_vector.h>
#include <kissvg/src/kissvg_math.h>

/******************************************************************************
 ******************************************************************************
 *                                                                            *
 *                 Begin kissvg_TwoByTwoMatrix Functions                      *
 *                                                                            *
 ******************************************************************************
 ******************************************************************************/

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoByTwoMatrix_Component                                       *
 *  Purpose:                                                                  *
 *      Returns the (m,n) element of a 2x2 matrix.                            *
 *  Arguments:                                                                *
 *      kissvg_TwoByTwoMatrix A:                                              *
 *          A 2x2 matrix.                                                     *
 *      int m:                                                                *
 *          The first index of the element.                                   *
 *      int n:                                                                *
 *          The second index of the element.                                  *
 *  Outputs:                                                                  *
 *      double out:                                                           *
 *          The (m,n) component of the kissvg_TwoByTwoMatrix                  *
 *  Note:                                                                     *
 *      This is not a function, but rather a preprocessor macro.              *
 ******************************************************************************/
#define kissvg_TwoByTwoMatrix_Component(A, m, n) (A.dat[m][n])

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_New_TwoByTwoMatrix                                             *
 *  Purpose:                                                                  *
 *      Create a new kissvg_TwoByTwoMatrix from four doubles. This returns:   *
 *           -       -                                                        *
 *          |  a   b  |                                                       *
 *          |  c   d  |                                                       *
 *           -       -                                                        *
 *  Arguments:                                                                *
 *      double a:                                                             *
 *      double b:                                                             *
 *      double c:                                                             *
 *      double d:                                                             *
 *  Outputs:                                                                  *
 *      kissvg_TwoByTwoMatrix:                                                *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoByTwoMatrix
kissvg_New_TwoByTwoMatrix(double a, double b, double c, double d);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoVector_Matrix_Transform                                     *
 *  Purpose:                                                                  *
 *      Given a matrix A and a vector P, computes AP.                         *
 *  Arguments:                                                                *
 *      kissvg_TwoByTwoMatrix A:                                              *
 *          A 2x2 matrix.                                                     *
 *      kissvg_TwoVector P:                                                   *
 *          A two element vector.                                             *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector out:                                                 *
 *          The vector P transformed by A.                                    *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector
kissvg_TwoVector_Matrix_Transform(kissvg_TwoByTwoMatrix A, kissvg_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_Rotation_Matrix_2D                                             *
 *  Purpose:                                                                  *
 *      Returns the rotation matrix corresponding to the angle theta.         *
 *  Arguments:                                                                *
 *      double theta:                                                         *
 *          A real number, the angle to rotate by.                            *
 *  Outputs:                                                                  *
 *      kissvg_TwoByTwoMatrix R:                                              *
 *          The rotation matrix.                                              *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoByTwoMatrix kissvg_Rotation_Matrix_2D(double theta);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_TwoByTwo)Matrix)Scale                                          *
 *  Purpose:                                                                  *
 *      Returns the rotation matrix corresponding to the angle theta.         *
 *  Arguments:                                                                *
 *      double theta:                                                         *
 *          A real number, the angle to rotate by.                            *
 *  Outputs:                                                                  *
 *      kissvg_TwoByTwoMatrix R:                                              *
 *          The rotation matrix.                                              *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoByTwoMatrix
kissvg_TwoByTwoMatrix_Scale(double r, kissvg_TwoByTwoMatrix P);

extern double kissvg_TwoByTwoMatrix_Determinant(kissvg_TwoByTwoMatrix A);

extern kissvg_TwoByTwoMatrix
kissvg_Inverse_TwoByTwoMatrix(kissvg_TwoByTwoMatrix A);

#endif
