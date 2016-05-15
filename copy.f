
      subroutine xscopy(n,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*)

      integer i,ix,iy

      intrinsic abs

      common seps,deps
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      return
      end


      subroutine xdcopy(n,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*)

      integer i,ix,iy

      intrinsic abs

      common seps,deps
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      return
      end



      subroutine xccopy(n,x,incx,y,incy)

      integer incx,incy,n
      complex x(*),y(*)

      integer i,ix,iy

      intrinsic abs

      common seps,deps
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      return
      end



      subroutine xzcopy(n,x,incx,y,incy)

      integer incx,incy,n
      complex*16 x(*),y(*)

      integer i,ix,iy

      intrinsic abs

      common seps,deps
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            y(i) = x(i)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            y(iy) = x(ix)
            ix = ix + incx
            iy = iy + incy
         end do
      end if

      return
      end
