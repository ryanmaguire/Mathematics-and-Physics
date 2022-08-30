

import settings;
settings.outformat = "pdf";
size(256);

pair A[] = {(-0.5, 0.0), (0.5, 0.0), (0.5, -0.05), (-0.5, -0.05)};
pair B[] = {(-0.025, 0.0), (-0.025, 0.9), (0.025, 0.9), (0.025, 0.0)};
pair C[] = {(-0.5, 0.475), (0.5, 0.475), (0.5, 0.525), (-0.5, 0.525)};

pair D[] = {(0.65, 0.0), (1.65, 0.0), (1.65, -0.05), (0.65, -0.05)};
pair E[] = {(0.65, 0.85), (1.65, 0.85), (1.65, 0.8), (0.65, 0.8)};
pair F[] = {(0.775, 0.35), (0.825, 0.35), (0.825, 0.7), (0.775, 0.7)};
pair G[] = {(1.525, 0.35), (1.475, 0.35), (1.475, 0.7), (1.525, 0.7)};
pair H[] = {(0.775, 0.325), (1.525, 0.325), (1.525, 0.375), (0.775, 0.375)};
pair I[] = {(0.775, 0.725), (1.525, 0.725), (1.525, 0.675), (0.775, 0.675)};
pair J[] = {(0.95, 0.05), (1.0, 0.07), (0.92, 0.27), (0.87, 0.25)};
pair K[] = {(1.25, 0.0), (1.3, -0.02), (1.42, 0.28), (1.37, 0.3)};

filldraw(circle((1.0, 0.0), 2.0), white, white);
filldraw(A[0] -- A[1] -- A[2] -- A[3] -- cycle, black, black);
filldraw(B[0] -- B[1] -- B[2] -- B[3] -- cycle, black, black);
filldraw(C[0] -- C[1] -- C[2] -- C[3] -- cycle, black, black);

filldraw(D[0] -- D[1] -- D[2] -- D[3] -- cycle, black, black);
filldraw(E[0] -- E[1] -- E[2] -- E[3] -- cycle, black, black);
filldraw(F[0] -- F[1] -- F[2] -- F[3] -- cycle, black, black);
filldraw(G[0] -- G[1] -- G[2] -- G[3] -- cycle, black, black);
filldraw(H[0] -- H[1] -- H[2] -- H[3] -- cycle, black, black);
filldraw(I[0] -- I[1] -- I[2] -- I[3] -- cycle, black, black);
filldraw(J[0] -- J[1] -- J[2] -- J[3] -- cycle, black, black);
//filldraw(K[0] -- K[1] -- K[2] -- K[3] -- cycle, black, black);
