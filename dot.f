
      real function sdot(n,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*)

      real d1,d2,xi,yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   d1 = 0.0e0
      d2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            d1 = d1 + xi*yi
            d2 = d2 + xi*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            d1 = d1 + xi*yi
            d2 = d2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(d1 - d2).ge.seps) then
         goto 100
      end if
      sdot = d1
      return
      end



      double precision function ddot(n,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*)

      double precision d1,d2,xi,yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   d1 = 0.0e0
      d2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            d1 = d1 + xi*yi
            d2 = d2 + xi*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            d1 = d1 + xi*yi
            d2 = d2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(d1 - d2).ge.deps) then
         goto 100
      end if
      ddot = d1
      return
      end
