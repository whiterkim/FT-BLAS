      ! function: sdsdot
      ! SDS: Real, using Double precision calculation, to Real version
      real function xsdsdot(n,sb,x,incx,y,incy)

      integer incx,incy,n
      real sb
      real x(*),y(*)

      double precision c1,c2,xi,yi
      integer i,ix,iy

      intrinsic abs,dble,REAL

      common seps,deps
      sdsdot = 0.0e0
100   c1 = sb
      c2 = sb
   
      if (n.le.0) then
         xsdsdot = c1;
         return
      end if
      if (incx.eq.incy .and. incx.gt.0) then
         ns = n*incx
         do i = 1,ns,incx
            xi = dble(x(i))
            yi = dble(y(i))
            c1 = c1 + xi*yi
            c2 = c2 + xi*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = dble(x(ix))
            yi = dble(y(iy))
            c1 = c1 + xi*yi
            c2 = c2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(c1 - c2).ge.seps) then
         goto 100
      end if
      xsdsdot = c1
      return
      end
