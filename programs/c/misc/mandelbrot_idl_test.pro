function mandelbrot, xcenter, ycenter, radius, size, max_iter, xout, yout
   if (n_elements(size) eq 0) then size=100
   if (n_elements(max_iter) eq 0) then max_iter=255
   dx = double(radius)*2/size
   xstart = double(xcenter - radius)
   xstop = double(xcenter + radius)
   ystart = double(ycenter - radius)
   ystop = double(ycenter + radius)
   result = lonarr(size, size)
   xout = xstart + findgen(size)*dx
   yout = ystart + findgen(size)*dx
   s = call_external('mandelbrot.so', 'mandelbrot', $
                      long(size), $
                      long(size), $
                      double(xstart), $
                      double(ystart), $
                      double(dx), $
                      double(dx), $
                      long(max_iter), $
                      result)
   return, result
end
