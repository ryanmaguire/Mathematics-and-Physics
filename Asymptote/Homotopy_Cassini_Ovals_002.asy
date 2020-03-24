// The Cassini functions are defined in CassiniOval.asy.
import cassinioval;

// Boilerplate stuff.
import settings;
settings.render=4;
settings.outformat = "pdf";

// Size of the output.
size(300);

// Pens used for drawing lines and shading (Counter and Fill).
pen cpen = deepblue;
pen fpen = lightgreen+opacity(0.2)+evenodd;

// Distance between points.
real dist = 4;

// The first focii. The second focii is -A.
pair A = (dist/2, 0);

// The Cassini Oval structure is defined in CassiniOval.asy.
CassiniOval co, co2;

// Variable for indexing.
int i;

// The increment in oval parameter between successive Cassini ovals.
real steps = 0.5;

// Starting index, must be positive.
int start  = 1;

// Final index, determined by distance between focii and size of steps.
int finish = (int)(dist/steps);

// Draw the figure 8 Cassini oval.
co=CassiniOval(A, -A, dist);
draw(co.curve, cpen+2);

// Loop over successive ovals, shading in area around central figure 8.
for(i=start; i<finish; ++i){
    co  = CassiniOval(A, -A, dist+i*steps);
    co2 = CassiniOval(A, -A, dist-i*steps);

    // Create an array of paths and shade with the even-odd rule.
    path p1 = co.curve[0];
    path p2 = co2.curve[0];
    path p3 = co2.curve[1];
    path[] p = {p1, p2, p3};
    filldraw(p, fpen, cpen);
}