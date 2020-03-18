import settings;
settings.render = 4;

outformat="pdf";

size(600);

path p;
real xshift = 2.0;
real yshift = 0.0;
position pos1 = 0.50;
position pos2 = 0.55;
margin TorusMargin;

draw((0,  0.5) -- (1.0,  0.5), Arrow(10bp, pos1));
draw((1, -0.5) -- (0.0, -0.5), BeginArrow(10bp, pos1));

pos1 = 0.45;
draw((1,  0.5) -- (1.0, -0.5), BeginArrow(10bp, pos1), BeginArrow(10bp, pos2));
draw((0, -0.5) -- (0.0,  0.5), Arrow(10bp, pos1), Arrow(10bp, pos2));

pos1 = 0.50;
p = (0, 0.15) -- (1, 0.15);
draw(shift(xshift,  0.0)*p, Arrow(10bp, pos1));
draw(shift(xshift, -0.3)*p, Arrow(10bp, pos1));

p = ( 0.00, -0.15){SW}..(-0.15, -0.40){W}..
    (-0.40,  0.0){N}..  (-0.15,  0.40){E}..( 0.00,  0.15){SE};

pos1 = 2.20;
pos2 = 2.00;

draw(shift(xshift, yshift)*p, Arrow(10bp, pos1), Arrow(10bp, pos2));

p = (-0.15, 0.40)--(0.85, 0.40){E}..(1.0, 0.15){SE};
draw(shift(xshift, yshift)*p);

p = (-0.15, -0.40)--(0.85, -0.40){E}..(1.0, -0.15){NE};
draw(shift(xshift, yshift)*p);

pos1 = 0.4;
pos2 = 0.8;

p = (0.75, 0.15){dir(-105)}..(0.75, -0.15){dir(-75)};
draw(shift(xshift, 0)*p, Arrow(10bp, pos1), Arrow(8bp, pos2));

xshift = 3.65;
pos1 = 1.8;
pos2 = 2.0;

p = ellipse(0.0, 0.15, 0.4);
draw(shift(xshift, 0)*p, BeginArrow(10bp, pos1), BeginArrow(10bp, pos2));

p = (0.0, 0.4)--(1.0, 0.4)
    --scale(0.375, 1)*arc((2.667, 0.0), 0.4, 90, -90)--(0.0, -0.4);

draw(shift(xshift, 0)*p);

p = (0.15, 0)--(1.15, 0.0);
draw(shift(xshift, 0)*p, Arrow(10bp, pos1));

xshift = -0.1;
yshift = -1.5;

pos1 = 1.85;
pos2 = 2.15;

p = scale(1.0, 2.0)*arc((1.0, 0), 0.1, 0, 360);
draw(shift(xshift, yshift)*p, BeginArrow(10bp, pos1), BeginArrow(10bp, pos2));

p = scale(1.0, 2.0)*arc((1.4, 0), 0.1, -180, 180);
draw(shift(xshift, yshift)*p, EndArrow(10bp, pos1), Arrow(10bp, pos2));

p = (1.0, -0.2) {dir(170)}..(0.2, 0.1){NW}..
    (1.2,  0.8) {dir(0)}..  (2.2, 0.1){SW}..(1.4, -0.2){dir(190)};
draw(shift(xshift, yshift)*p);

p = (1.0, 0.2) {dir(170)}..(0.5, 0.4){NW};
draw(shift(xshift, yshift)*p);

p = (1.4, 0.2) {dir(10)}..(1.9, 0.4){NE};
draw(shift(xshift, yshift)*p);

TorusMargin = TrueMargin(0.02cm, 0.0cm);
p = (0.635, 0.3){NE}..(1.2, 0.5)..(1.755, 0.3){SE};
draw(shift(xshift, yshift)*p, margin=TorusMargin);

TorusMargin = TrueMargin(0.005cm, 0.0cm);
p = (0.56, 0.35){NE}..(1.2, 0.6)..(1.84, 0.35){SE};
draw(shift(xshift, yshift)*p, margin=TorusMargin, MidArrow(10bp));

xshift =  2.5;
yshift = -1.5;
pos1 = 0.9;
pos2 = 1.2;

p = scale(1.2, 2.0)*arc((1.0, 0), 0.1, -90, 90);
draw(shift(xshift, yshift)*p, Arrow(10bp, pos1), Arrow(10bp, pos2));

p = (0.5, 0.4){SE}..(1.2, 0.2){E}..(1.9, 0.4){NE};
draw(shift(xshift, yshift)*p);

p = (1.2, -0.2) {W}..(0.2, 0.1){NW}..
    (1.2,  0.8) {dir(0)}..  (2.2, 0.1){SW}..cycle;
draw(shift(xshift, yshift)*p);

p = (0.64, 0.3){NE}..(1.2, 0.5)..(1.76, 0.3){SE};
draw(shift(xshift, yshift)*p);

TorusMargin = TrueMargin(0.005cm, 0.0cm);
p = (0.56, 0.35){NE}..(1.2, 0.6)..(1.84, 0.35){SE};
draw(shift(xshift, yshift)*p, margin=TorusMargin, MidArrow(10bp));