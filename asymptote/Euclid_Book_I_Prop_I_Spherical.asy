// Boilerplate stuff.
import settings;
import graph3;

if(!settings.multipleView)  settings.batchView=false;

settings.render=8;
settings.outformat="pdf";
settings.inlineimage=true;
settings.embed=true;
settings.toolbar=false;
viewportmargin=(2, 2);

currentprojection=perspective(camera = (100, 0, 50), up   = (0, 0, 1),
                              target = (0,  0,  0),  zoom = 0.85);

// Pen for drawing.
pen dpen = black+linewidth(1.0pt);
pen bpen = blue+linewidth(0.5pt);
pen rpen = red+linewidth(0.5pt);

// Size of the output figure.
size(128);

// Radius of the dot and pipes.
real dotR = 0.08;

triple A = (sqrt(0.5), -sqrt(0.5), 0);
triple B = (sqrt(0.5),  sqrt(0.5), 0);
triple C = (0, 0, 1);

triple great_circle(real t, triple P, triple Q){
    real u = cos(t);
    real v = sin(t);
    return scale(u, u, u)*P+scale(v, v, v)*Q;
}

triple c1(real t){return great_circle(t, A, B);}
triple c2(real t){return great_circle(t, B, C);}
triple c3(real t){return great_circle(t, C, A);}

radialshade(
    project(
        circle((0,0,0), 1, currentprojection.camera-currentprojection.target)
    ),
    rgb(0.8,0.8,0.8), project(O), 1.0,
    rgb(0.9,0.9,0.9), project(O), 0.2
);

guide3 q=graph(c2, pi/4, 2.2, 100, operator ..);
draw(project(q), bpen);
guide3 q=graph(c2, 5.3, 2pi, 100, operator ..);
draw(project(q), bpen);

guide3 q=graph(c3, pi/2, 2.4, 100, operator ..);
draw(project(q), rpen);
guide3 q=graph(c3, 5.6, 2pi, 100, operator ..);
draw(project(q), rpen);

guide3 q1=graph(c1, 0, pi/2, 100, operator ..);
guide3 q2=graph(c2, 0, pi/2, 100, operator ..);
guide3 q3=graph(c3, 0, pi/2, 100, operator ..);
guide3 g=q1--q2--q3--cycle;
filldraw(project(g), green);
dot(project(A));
dot(project(B));
dot(project(C));

label("$A$", project(A), NE);
label("$B$", project(B), NW);
label("$C$", project(C), S);
