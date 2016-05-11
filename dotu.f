      ! function: cdotu
      ! C: Complex*8 version
      complex*8 function xcdotu(n,x,incx,y,incy)

      integer incx,incy,n
      complex*8 x(*),y(*)

      complex*8 c1,c2,xi,yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   c1 = (0.0,0.0)
      c2 = (0.0,0.0)      
      xcdotu = (0.0,0.0)

      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            c1 = c1 + xi*yi
            c2 = c2 + xi*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            c1 = c1 + xi*yi
            c2 = c2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(c1 - c2).ge.seps) then
         goto 100
      end if
      xcdotu = c1
      return
      end

      ! function: zdotu
      ! Z: Complex*16 version
      complex*16 function xzdotu(n,x,incx,y,incy)

      integer incx,incy,n
      complex*16 x(*),y(*)

      complex*16 c1,c2,xi,yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   c1 = (0.0d0,0.0d0)
      c2 = (0.0d0,0.0d0)
      xzdotu = (0.0d0,0.0d0)
  
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            c1 = c1 + xi*yi
            c2 = c2 + xi*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            c1 = c1 + xi*yi
            c2 = c2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(c1 - c2).ge.deps) then
         goto 100
      end if
      xzdotu = c1
      return
      end
