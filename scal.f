
      subroutine sscal(n,alpha,x,incx)

      integer incx,n
      real x(*),alpha

      real xi,xn
      integer i,ix

      intrinsic abs

      common seps,deps
100   xn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         do i = 1,n
            xi = x(i)
            xi = xi * alpha;
            x(i) = xi;
            xn = xn + xi;
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            xi = xi * alpha;
            x(ix) = xi;
            xn = xn + xi;
            ix = ix + incx
         end do
      end if
      if (abs(x(n + 1)*alpha - xn).ge.seps) then
         print *, "Error occurs in sscal"
      end if
      x(n + 1) = xn
      return
      end

