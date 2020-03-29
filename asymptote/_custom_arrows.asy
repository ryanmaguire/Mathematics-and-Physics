// This module contains functions for mimicing the tikz style of arrow heads.
// In particular, the sharpness of detail (arrows come to a point), and provides
// code for the stealth arrowhead which basic asymptote lacks.

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

private real position(position currentpos, real size, path g, bool center)
{
    // Set pos to the real value equivalent of position.
    real pos = currentpos.position.x;
    if(currentpos.relative) {
        pos *= arclength(g);
        if(center) pos += 0.5*size;
        pos=arctime(g, pos);
    }
    else if (center)
        pos=arctime(g, arclength(subpath(g, 0, pos))+0.5*size);
    return pos;
}

private void drawsharparrow(frame f, arrowhead arhead=DefaultHead,
                            path g, pen p=currentpen, real size=0,
                            real angle=arrowangle, filltype fill=null,
                            position currentpos=EndPoint, bool forwards=true,
                            margin the_margin=NoMargin, bool center=false)
{
    // Paths for a portion of the path g and the arrow head.
    path head, r;

    // Boolean used when drawing the path.
    bool endpoint;

    // Integer used for the length of the path.
    int L;

    // Used for the real value equivalent of the input currentpos.
    real pos;

    // If size was not set, return size of the current pen.
    if(size == 0) size = arhead.size(p);

    // If fill was not set, use the fill type of the current pen.
    if(fill == null) fill = arhead.defaultfilltype(p);

    // Make sure the size is a legal value.
    size = min(arrowsizelimit*arclength(g), size);

    // Convert the current position into a real number.
    pos = position(currentpos, size, g, center);

    // Adjust the path by the selected margin.
    g = the_margin(g, p).g;

    // Store the length of the new path as a variable.
    L = length(g);

    // If the path should be going backwards, adjust g and pos.
    if(!forwards) {
        g   = reverse(g);
        pos = L-pos;
    }

    // Get the subpath of g with respect to the position pos.
    r = subpath(g, pos, 0);

    // Again, make sure size is a legal value.
    size = min(arrowsizelimit*arclength(r), size);

    // Set information about the arrow head.
    head = arhead.head(g, pos, p, size, angle);

    endpoint = pos > L-sqrtEpsilon;
    if(cyclic(head) && (fill == NoFill || endpoint)) {
        if(pos > 0)   draw(f, subpath(r, arctime(r, size), length(r)), p);
        if(!endpoint) draw(f, subpath(g, pos, L), p);
    }
    else draw(f, g, p);

    // Fill the arrow head, setting line width to 0.0 to make it "sharp".
    fill.fill(f, head, p+linewidth(0.0)+solid);
}

private void drawsharparrow2(frame f, arrowhead arhead=DefaultHead, path g,
                             pen p=currentpen, real size=0,
                             real angle=arrowangle, filltype fill=null,
                             margin the_margin=NoMargin)
{
    // Paths for a portion of the path g, the arrow head, and arrow tail.
    path head, tail, r;

    // Integer used for the length of the path.
    int L;

    // If size was not set, return size of the current pen.
    if(size == 0) size = arhead.size(p);

    // If fill was not set, use the fill type of the current pen.
    if(fill == null) fill = arhead.defaultfilltype(p);

    // Make sure the size is a legal value.
    size = min(arrowsizelimit*arclength(g), size);

    // Adjust the path by the selected margin.
    g = the_margin(g, p).g;

    // Store the length of the new path as a variable.
    L = length(g);

    // Set r to the reverse path of g.
    r = reverse(g);

    // Set information about the arrow heads.
    head = arhead.head(g, L, p, size, angle);
    tail = arhead.head(r, L, p, size, angle);

    if(cyclic(head))
        draw(f, subpath(r, arctime(r, size), L-arctime(g, size)), p);
    else draw(f,g,p);

    // Fill in the head and tail ends of the path with arrows.
    fill.fill(f,head,p+linewidth(0.0)+solid);
    fill.fill(f,tail,p+linewidth(0.0)+solid);
}

private picture sharparrow(arrowhead arhead=DefaultHead,
                           path g, pen p=currentpen, real size=0,
                           real angle=arrowangle, filltype fill=null,
                           position currentpos=EndPoint, bool forwards=true,
                           margin the_margin=NoMargin, bool center=false)
{
    // Picture we're adding an arrow to.
    picture pic;

    // Real equivalent of currentpos.
    real pos;

    // Path used for reversing arrow if forwards=false is set.
    path G;

    // If size was not set, return size of the current pen.
    if(size == 0) size = arhead.size(p);

    // Add the arrow to pic.
    pic.add(
        new void(frame f, transform t) {
            drawsharparrow(f, arhead, t*g, p, size, angle, fill, currentpos,
                           forwards, the_margin, center);
        }
    );

    // Add the path to the picture with the selected pen.
    pic.addPath(g, p);

    // Get the real value equivalent of currentpos.
    pos = position(currentpos, size, g, center);

    // If the path should be backwards, reverse it.
    if(!forwards) {
        G   = reverse(g);
        pos = length(g)-pos;
    }
    else G = g;

    // Draw the arrow on the picture.
    addArrow(pic, arhead, G, p, size, angle, fill, pos);

    return pic;
}

picture sharparrow2(arrowhead arhead=DefaultHead, path g, pen p=currentpen,
                    real size=0, real angle=arrowangle, filltype fill=null,
                    margin the_margin=NoMargin)
{
    // Picture we're adding an arrow to.
    picture pic;

    // Integer representing the length of the path.
    int L;

    // If size was not set, return size of the current pen.
    if(size == 0) size = arhead.size(p);

    pic.add(
        new void(frame f, transform t) {
            drawsharparrow2(f, arhead, t*g, p, size, angle, fill, the_margin);
        }
    );

    // Add the path with the selected pen to the picture.
    pic.addPath(g, p);

    // Set L to the length of g.
    L = length(g);

    // Add an arrow to the head and tail of the path.
    addArrow(pic, arhead, g, p, size, angle, fill, L);
    addArrow(pic, arhead, reverse(g), p, size, angle, fill, L);

    return pic;
}

arrowbar BeginSharpArrow(arrowhead arhead=DefaultHead, real size=0,
                         real angle=arrowangle, filltype fill=null,
                         position currentpos=BeginPoint)
{
    return new bool(picture pic, path g, pen p, margin the_margin) {
        add(pic, sharparrow(arhead, g, p, size, angle, fill, currentpos,
                            forwards=false, the_margin));
        return false;
    };
}

arrowbar SharpArrow(arrowhead arhead=DefaultHead, real size=0,
                    real angle=arrowangle, filltype fill=null,
                    position currentpos=EndPoint)
{
    return new bool(picture pic, path g, pen p, margin the_margin) {
        add(pic, sharparrow(arhead, g, p, size, angle, fill,
                            currentpos, the_margin));
        return false;
    };
}

arrowbar EndSharpArrow(arrowhead arhead=DefaultHead, real size=0,
                       real angle=arrowangle, filltype fill=null,
                       position currentpos=EndPoint)=SharpArrow;

arrowbar MidSharpArrow(arrowhead arhead=DefaultHead, real size=0,
                       real angle=arrowangle, filltype fill=null)
{
    return new bool(picture pic, path g, pen p, margin the_margin) {
        add(pic, sharparrow(arhead, g, p, size, angle, fill, MidPoint,
                            the_margin, center=true));
        return false;
    };
}

arrowbar SharpArrows(arrowhead arhead=DefaultHead, real size=0,
                     real angle=arrowangle, filltype fill=null)
{
    return new bool(picture pic, path g, pen p, margin the_margin) {
        add(pic, sharparrow2(arhead, g, p, size, angle, fill, the_margin));
        return false;
    };
}