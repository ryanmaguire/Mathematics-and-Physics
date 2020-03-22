import cassinioval;
import settings;
settings.outformat = "pdf";

size(300);

pen cpen = deepblue;
pen fpen = lightgreen+opacity(0.2);

pair A = (-2, 0);
pair B = (+2, 0);

CassiniOval co, co2;

int i;

co=CassiniOval(A, B, 4);
draw(co.curve, cpen);

for(i=5; i<8; ++i){
    co=CassiniOval(A, B, i);
    filldraw(co.curve, fpen, cpen);
}

co=CassiniOval(A, B, 3);
filldraw(co.curve, white, opacity(0.0));
filldraw(co.curve, fpen, cpen);

co2=CassiniOval(A, B, 2);
filldraw(co2.curve, white, cpen);
filldraw(co.curve, fpen, opacity(0.0));

co2=CassiniOval(A, B, 1);
filldraw(co2.curve, white, cpen);