
      subroutine saxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*),alpha

      real xi,yi,yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            yi = xi * alpha + yi;
            y(i) = yi;
            yn = yn + yi;
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            yi = xi * alpha + yi;
            y(iy) = yi;
            yn = yn + yi;
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(y(n + 1) + alpha*x(n + 1) - yn).ge.seps) then
         print *, "Error occurs in saxpy"
      end if
      y(n + 1) = yn
      return
      end

