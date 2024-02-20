FUNCTION MANDELBROT, XCENTER, YCENTER, RADIUS, IMAGE_SIZE, MAX_ITER

   IF N_ELEMENTS(IMAGE_SIZE) EQ 0 THEN BEGIN
      IMAGE_SIZE = 100
   ENDIF

   IF N_ELEMENTS(MAX_ITER) EQ 0 THEN BEGIN
      MAX_ITER = 255
   ENDIF

   DX = RADIUS * 2.0 / IMAGE_SIZE
   XSTART = XCENTER - RADIUS
   YSTART = YCENTER - RADIUS

   RESULT = LONARR(IMAGE_SIZE, IMAGE_SIZE)

   s = CALL_EXTERNAL(   $
      './mandelbrot.so',  $
      'mandelbrot',     $
      LONG(IMAGE_SIZE), $
      LONG(IMAGE_SIZE), $
      DOUBLE(XSTART),   $
      DOUBLE(YSTART),   $
      DOUBLE(DX),       $
      DOUBLE(DX),       $
      LONG(MAX_ITER),   $
      RESULT            $
   )

   RETURN, RESULT
END
