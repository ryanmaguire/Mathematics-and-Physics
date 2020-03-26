// This little module contains functions for mimicing the tikz style of arrow
// heads. In particular, the sharpness of detail (arrows come to a point), and
// provides code for the stealth arrowhead which basic asymptote lacks. This
// code is very rough but gets the job done.

/***************************Defined Functions**********************************
 *  stealth_arrow, stealth_arrows, stealth_beginarrow:                        *
 *      Tikz styled steath arrow. stealth_arrows places arrows at the start   *
 *      and end of the path, stealth_beginarrow places on at the start.       *
 *  sharp_arrow, sharp_arrows, sharp_beginarrow:                              *
 *      The same of Arrows() in default asymptote be with a sharper arrowhead.*
 *      Thus it mimics the standard tikz arrow head. Particularly appealing   *
 *      for commutative diagrams and axes.                                    *
 *  inputs:                                                                   *
 *      picture pic=currentpicture                                            *
 *          Picture, if any, applied to the path.                             *
 *      Label L=""                                                            *
 *          Label used for the path.                                          *
 *      path g                                                                *
 *          The path the arrows are to be applied to.                         *
 *      align align=NoAlign                                                   *
 *          Orientation information for picture / label.                      *
 *      pen p=currentpen                                                      *
 *          The pen used to draw the path.                                    *
 *      real mstart=0                                                         *
 *          Margin applied to the start of the path (the amount trimmed off). *
 *      real mend=0                                                           *
 *          Margin applied to the end of the path.                            *
 *      real arsize=0                                                         *
 *          The size of the arrow head.                                       *
 ******************************************************************************/
import graph3;

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

arrowhead3 StealthHead3(real dir=arrowdir, real barb=arrowbarb)
{
  arrowhead3 a;
  a.head=new surface(path3 g, position position=EndPoint,
                     pen p=currentpen, real size=0, real angle=arrowangle,
                     filltype filltype=null, bool forwards=true,
                     projection P=currentprojection) {
    if(size == 0) size=a.size(p);
    
    bool relative=position.relative;
    real position=position.position.x;
    if(relative) position=reltime(g,position);

    path3 r=subpath(g,position,0);
    path3 s=subpath(r,arctime(r,size),0);
    bool straight1=length(s) == 1 && straight(g,0);
    path3 H=path3(StealthHead(dir,barb).head((0,0)--(0,size),p,size,angle),
                  YZplane);
    surface head=surface(O,reverse(approach(subpath(H,1,0),7,1.5))&
                         approach(subpath(H,1,2),4,2),Z);
  
    if(straight1) {
      triple v=point(s,0);
      triple u=point(s,1)-v;
      return shift(v)*align(unit(u))*head;
    } else {
      bend(head,s,size);
      return head;
    }
  };
  a.arrowhead2=StealthHead;
  a.gap=0.7;
  return a;
}
arrowhead3 StealthHead3=StealthHead3();

void stealth_arrow(picture pic=currentpicture, Label L="", path g,
                   align align=NoAlign, pen p=currentpen,
                   real mstart=0, real mend=0, real arsize=5bp)
{
    margin margins = TrueMargin(mstart, mend);
    draw(g, linewidth(0.0), margin=margins, Arrow(StealthHead, arsize));

    margin margins = TrueMargin(mstart, mend+arsize);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void stealth_arrows(picture pic=currentpicture, Label L="", path g,
                   align align=NoAlign, pen p=currentpen,
                   real mstart=0, real mend=0, real arsize=5bp)
{
    margin margins = TrueMargin(mstart, mend);
    draw(g, linewidth(0.0), margin=margins, Arrows(StealthHead, arsize));

    margin margins = TrueMargin(mstart+arsize, mend+arsize);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void stealth_beginarrow(picture pic=currentpicture, Label L="", path g,
                        align align=NoAlign, pen p=currentpen,
                        real mstart=0, real mend=0, real arsize=5bp)
{
    margin margins = TrueMargin(mstart, mend);
    draw(g, linewidth(0.0), margin=margins, BeginArrow(StealthHead, arsize));

    margin margins = TrueMargin(mstart+arsize, mend);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void sharp_arrow(picture pic=currentpicture, Label L="", path g,
                 align align=NoAlign, pen p=currentpen,
                 real mstart=0, real mend=0, real arsize=5bp)
{
    margin margins = TrueMargin(mstart, mend);
    draw(g, linewidth(0.1), margin=margins, Arrow(arsize));

    margin margins = TrueMargin(mstart, mend+arsize);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void sharp_arrows(picture pic=currentpicture, Label L="", path g,
                  align align=NoAlign, pen p=currentpen,
                  real mstart=0, real mend=0, real arsize=5bp)
{
    margin margins = TrueMargin(mstart, mend);
    draw(g, linewidth(0.0), margin=margins, Arrows(arsize));

    margin margins = TrueMargin(mstart+arsize, mend+arsize);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}

void sharp_beginarrow(picture pic=currentpicture, Label L="", path g,
                      align align=NoAlign, pen p=currentpen,
                      real mstart=0, real mend=0, real arsize=5bp)
{
    margin margins = TrueMargin(mstart, mend);
    draw(g, linewidth(0.0), margin=margins, BeginArrow(arsize));

    margin margins = TrueMargin(mstart+arsize, mend+arsize);
    draw(g, white, margin=margins);
    draw(pic, L, g, align, p, margin=margins);
}