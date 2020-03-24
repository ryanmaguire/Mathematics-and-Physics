import cassinioval;
import settings;
settings.outformat = "pdf";

size(300);

pen cpen = deepblue;
pen fpen = lightgreen+opacity(0.2)+evenodd;

real dist = 4;
pair A = (-dist/2, 0);
pair B = (+dist/2, 0);

CassiniOval co, co2;

int i;
real steps = 0.5;
int start  = 1;
int finish = (int)(dist/steps);

co=CassiniOval(A, B, dist);
draw(co.curve, cpen);

for(i=start; i<finish; ++i){
    co  = CassiniOval(A, B, dist+i*steps);
    co2 = CassiniOval(A, B, dist-i*steps);

    path p1 = co.curve[0];
    path p2 = co2.curve[0];
    path p3 = co2.curve[1];
    path[] p = {p1, p2, p3};
    filldraw(p, fpen, cpen);
}