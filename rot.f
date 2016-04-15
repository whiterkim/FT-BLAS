      
      subroutine xsrot(n,x,incx,y,incy,c,s)

      real c,s
      integer incx,incy,n

      real x(*),y(*)

      real xi,yi,xn,yn,t1,t2
      integer i,ix,iy

      intrinsic abs,sign,sqrt

      common seps,deps
      xn = 0.0e0
      yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            t1 = c*xi + s*yi
            t2 = c*yi - s*xi
            xn = xn + t1
            yn = yn + t2
            x(i) = t1
            y(i) = t2
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            t1 = c*xi + s*yi
            t2 = c*yi - s*xi
            xn = xn + t1
            yn = yn + t2
            x(ix) = t1
            y(iy) = t2
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      t1 = c*x(n + 1) + s*y(n + 1)
      t2 = c*y(n + 1) - s*x(n + 1)
*      if (abs(t1 - xn).ge.seps) then
*         print *, "Error occurs in srot"
*      end if
*      if (abs(t2 - yn).ge.seps) then
*         print *, "Error occurs in srot"
*      end if
      x(n + 1) = t1
      y(n + 1) = t2
      return
      end

      
      subroutine xdrot(n,x,incx,y,incy,c,s)

      double precision c,s
      integer incx,incy,n

      double precision x(*),y(*)

      double precision xi,yi,xn,yn,t1,t2
      integer i,ix,iy

      intrinsic abs,sign,sqrt

      common seps,deps
      xn = 0.0e0
      yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            t1 = c*xi + s*yi
            t2 = c*yi - s*xi
            xn = xn + t1
            yn = yn + t2
            x(i) = t1
            y(i) = t2
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            t1 = c*xi + s*yi
            t2 = c*yi - s*xi
            xn = xn + t1
            yn = yn + t2
            x(ix) = t1
            y(iy) = t2
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      t1 = c*x(n + 1) + s*y(n + 1)
      t2 = c*y(n + 1) - s*x(n + 1)
*      if (abs(t1 - xn).ge.deps) then
*         print *, "Error occurs in drot"
*      end if
*      if (abs(t2 - yn).ge.deps) then
*         print *, "Error occurs in drot"
*      end if
      x(n + 1) = t1
      y(n + 1) = t2
      return
      end
