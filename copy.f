
      subroutine scopy(n,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*)

      real yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
            yn = yn + y(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            yn = yn + y(iy)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      if (abs(x(n + 1) - yn).ge.seps) then
         goto 100
      end if
      y(n + 1) = yn
      return
      end


      subroutine dcopy(n,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*)

      double precision yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
            yn = yn + y(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            yn = yn + y(iy)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      if (abs(x(n + 1) - yn).ge.deps) then
         goto 100
      end if
      y(n + 1) = yn
      return
      end



      subroutine ccopy(n,x,incx,y,incy)

      integer incx,incy,n
      complex x(*),y(*)

      complex yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
            yn = yn + y(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            yn = yn + y(iy)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      if (abs(x(n + 1) - yn).ge.seps) then
         goto 100
      end if
      y(n + 1) = yn
      return
      end
