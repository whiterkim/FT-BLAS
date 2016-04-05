
      real function snrm2(n,x,incx)

      integer incx,n
      real x(*)

      real xi,a1,a2
      integer i,ix

      intrinsic abs,sqrt

      common seps,deps
100   a1 = 0.0e0
      a2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         do i = 1,n
            xi = x(i)
            a1 = a1 + xi*xi;
            a2 = a2 + xi*xi;
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            a1 = a1 + xi*xi;
            a2 = a2 + xi*xi;
            ix = ix + incx
         end do
      end if
      a1 = sqrt(a1)
      a2 = sqrt(a2)
      if (abs(a1 - a2).ge.seps) then
         goto 100
      end if
      snrm2 = a1
      return
      end

