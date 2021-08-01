import settings;
import three;
unitsize(1cm);

settings.outformat="pdf";
settings.render=0;
settings.prc=false;

currentprojection=perspective(
                  camera=(-10,0,5),
                  target=(48,2,-1),
                  angle=5,
                  autoadjust=false);

real height = 1;
real width = 0.5;
real depth = 0.08;
real separation = 0.5; //This is the interval from start to start.

surface domino = scale(depth, width, height) * shift(-1,-1/2,0) * unitcube;

triple labelposition = (-depth, 0, 0.7*height);

surface labelfor(string s) {
  static transform3 T = shift(labelposition)*rotate(90,Y)*rotate(90,Z)*scale3(0.016)*scale(-1,1,1);
  return T*surface(Label(s, p=fontsize(32)));
}


path receeding = scale(separation) * yscale(-1) * ( (0,-7) .. (7,0) .. (25,-6) .. (60,2) .. (95,-3) :: (140, -1) :: (200,0));


struct pointAndAngle {
  triple point;
  real angle;
}

pointAndAngle dominoPosition(int n) {
  pointAndAngle toreturn;
  real t = arctime(receeding, n*separation);
  toreturn.point = XYplane(point(receeding,t));
  pair tangent = dir(receeding, t);
  toreturn.angle = degrees(atan2(tangent.y, tangent.x));
  return toreturn;
}

transform3 dominoUpright(int n) {
  pointAndAngle info = dominoPosition(n);
  return shift(info.point) * rotate(info.angle, Z);
}

transform3 lyingDown(int n) {
  return dominoUpright(n) * rotate(90, Y);
}


int nDominoes = 200;

draw(dominoUpright(0) * domino, invisible);
draw(dominoUpright(nDominoes-1) * domino, invisible);
draw(lyingDown(nDominoes-1) * domino, invisible);

int nToppled = 8;

write("Computing image with " + (string)nToppled + " dominoes toppled.");

surface currentdomino;

for (int n = nDominoes-1; n >= 0; --n) {

  pointAndAngle position = dominoPosition(n);
  transform3 T = shift(position.point) * rotate(position.angle, Z);
  if (n <= nToppled-1) {
    if (currentdomino.s.length == 0) T = T * rotate(85,Y);
    else {
      path3 toisectleft = T * circle(c=(0, interp(-width/2, width/2, 1/3), 0),normal=Y,r=height);
      path3 toisectright = T* circle(c=(0, interp(-width/2, width/2, 2/3), 0),normal=Y,r=height);
      triple[] isectionpointsleft = intersectionpoints(toisectleft, currentdomino);
      triple[] isectionpointsright = intersectionpoints(toisectright, currentdomino);;
      real zleft=0, zright=0;
      for (triple pt : isectionpointsleft) {
    if (pt.z >= zleft) zleft = pt.z;
      }
      for (triple pt : isectionpointsright) {
    if (pt.z >= zright) zright = pt.z;
      }
      real angle1 = aSin(zleft / height);
      real angle2 = aSin(zright / height);
      if (angle1 > angle2) {
    real tmp = angle2;
    angle2 = angle1;
    angle1 = tmp;
      }
      real angle = interp(angle1, angle2, 2);
      T = T * rotate(90-angle, Y);
    }
  }
  currentdomino = T * domino;
  draw(currentdomino, gray(0.5));
  if (n < 80)
    draw( T*labelfor((string)(n+1)), emissive(white), meshpen=white );
}