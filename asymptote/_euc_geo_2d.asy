// Find midpoint given two points in the plane.
pair MidPointTwo(pair A, pair B){return scale(0.5)*(A+B);}

// Returns the Euclidean norm of a 2-dimensional point.
real EucNormTwo(pair A){return sqrt(A.x^2+A.y^2);}

// Given three non-colinear points in the plane, returns center of their circle.
pair FindCenterTwo(pair A, pair B, pair C){
    pair U = MidPointTwo(A, B);
    pair V = MidPointTwo(B, C);

    real a =  (B.y-A.y)/(B.y-A.y+B.x-A.x);
    real b = -(B.x-A.x)/(B.y-A.y+B.x-A.x);
    real c =  (C.y-B.y)/(C.y-B.y+C.x-B.x);
    real d = -(C.x-B.x)/(C.y-B.y+C.x-B.x);
    real t0 = (c*(V.y-U.y)-d*(V.x-U.x))/(b*c-a*d);
    real t1 = (a*(V.y-U.y)-b*(V.x-U.x))/(b*c-a*d);
    return (U.x+t0*a, U.y+t0*b);
}

// Given an array of pairs, draw a smooth curve through the point.
path PathFromPoints(pair[] Pts, int ArSize, bool closed){
    assert(ArSize>1);
    path g;
    int i;
    g = Pts[0]..Pts[1];

    // Loop through the array and construct the path.
    for (i=2; i<ArSize; ++i) g = g..Pts[i];

    // If the closed Boolean is true, close the path into a cycle.
    if (closed) g = g..cycle;
    return g;
}

// Given an array of pairs, draw a polygonal curve through the point.
path PolyFromPoints(pair[] Pts, int ArSize, bool closed){
    assert(ArSize>1);
    path g;
    int i;
    g = Pts[0]--Pts[1];

    // Loop through the array and construct the path.
    for (i=2; i<ArSize; ++i) g = g--Pts[i];

    // If the closed Boolean is true, close the path into a cycle.
    if (closed) g = g--cycle;
    return g;
}

// Given an array of pairs and an array of reals, draw a path between the pairs
// with angle specified by the array of reals.
path PathFromPointsAndAngles(pair[] Pts, real[] Dirs, int ArSize, bool closed){
    assert(ArSize>1);
    path g;
    int i;
    g = Pts[0]{dir(Dirs[0])}..Pts[1]{dir(Dirs[1])};

    // Loop through the arrays and construct the path.
    for (i=2; i<ArSize; ++i) g = g..Pts[i]{dir(Dirs[i])};

    // If the closed Boolean is true, close the path into a cycle.
    if (closed) g = g..cycle;
    return g;
}