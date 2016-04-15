
      subroutine xsswap(n,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*)

      real xn,yn, xi, yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   xn = 0.0e0
      yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            x(i) = yi
            y(i) = xi
            xn = xn + xi
            yn = yn + yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            x(ix) = yi
            y(iy) = xi
            xn = xn + xi
            yn = yn + yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if

!      if ((abs(x(n + 1) - xn).ge.seps)) then
!         print *, "Error occurs in sswap"
!      end if
!      if ((abs(y(n + 1) - yn).ge.seps)) then
!         print *, "Error occurs in sswap"
!    end if
!    x(n + 1) = yn
!    y(n + 1) = xn
      return
      end



      subroutine dswap(n,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*)

      double precision xn,yn, xi, yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   xn = 0.0d0
      yn = 0.0d0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            x(i) = yi
            y(i) = xi
            xn = xn + xi
            yn = yn + yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            x(ix) = yi
            y(iy) = xi
            xn = xn + xi
            yn = yn + yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if

!     if ((abs(x(n + 1) - xn).ge.deps)) then
!        print *, "Error occurs in dswap"
!     end if
!     if ((abs(y(n + 1) - yn).ge.deps)) then
!        print *, "Error occurs in dswap"
!     end if
!      x(n + 1) = yn
!      y(n + 1) = xn
      return
      end
