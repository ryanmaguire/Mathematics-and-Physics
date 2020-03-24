arrowhead StealthHead(real dir=arrowdir, real barb=arrowbarb)
{
  arrowhead a;
  a.head=new path(path g, position position=EndPoint, pen p=currentpen,
                  real size=0, real angle=arrowangle)
    {
      if(size == 0) size=a.size(p);
      angle=min(angle*arrowhookfactor, 45);
      bool relative=position.relative;
      real position=position.position.x;
      if(relative) position=reltime(g, position);
      path r=subpath(g, position, 0);
      pair x=point(r, 0);
      real t=arctime(r, size);
      pair y=point(r,t);
      path base=arrowbase(r,y,t,size);
      path left=rotate(-angle,x)*r;
      path right=rotate(angle,x)*r;
      real[] T=arrowbasepoints(base,left,right,1);
      pair denom=point(right,T[1])-y;
      real factor=denom != 0 ? length((point(left,T[0])-y)/denom) : 1;
      path left=rotate(-angle*factor,x)*r;
      path right=rotate(angle*factor,x)*r;
      real[] T=arrowbasepoints(base,left,right,1);
      left=subpath(left,0,T[0]);
      right=subpath(right,T[1],0);
      pair pl0=point(left,0), pl1=relpoint(left,1);
      pair pr0=relpoint(right,0), pr1=relpoint(right,1);
      pair M=(pl1+pr0)/2;
      pair v=barb*unit(M-pl0);
      pl1=pl1+v; pr0=pr0+v;
      left=pl0{dir(-dir+degrees(M-pl0, false))}--pl1--M;
      right=M--pr0--pr1{dir(dir+degrees(pr1-M, false))};
      return left--right&cycle;
    };
  return a;
}
arrowhead StealthHead=StealthHead();

void stealth_arrow(picture pic=currentpicture, Label L="", path g,
                   align align=NoAlign, pen p=currentpen,
                   real mstart=0, real mend=0, real arsize=0)
{
    margin margins = TrueMargin(mstart, mend-arsize);
    draw(g, linewidth(0.1), margin=margins, Arrow(StealthHead, arsize));

    margin margins = TrueMargin(mstart, mend);
    draw(g, white+linewidth(0.1), margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void stealth_arrows(picture pic=currentpicture, Label L="", path g,
                   align align=NoAlign, pen p=currentpen,
                   real mstart=0, real mend=0, real arsize=0)
{
    margin margins = TrueMargin(mstart-arsize, mend-arsize);
    draw(g, linewidth(0.0), margin=margins, Arrows(StealthHead, arsize));

    margin margins = TrueMargin(mstart, mend);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void stealth_beginarrow(picture pic=currentpicture, Label L="", path g,
                        align align=NoAlign, pen p=currentpen,
                        real mstart=0, real mend=0, real arsize=0)
{
    margin margins = TrueMargin(mstart-arsize, mend-arsize);
    draw(g, linewidth(0.0), margin=margins, BeginArrow(StealthHead, arsize));

    margin margins = TrueMargin(mstart, mend);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}