
      subroutine xsswap(n,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*)

      real temp
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   xn = 0.0e0
      yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            temp = x(i)
            x(i) = y(i)
            y(i) = temp 
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            temp = x(ix)
            x(ix) = y(iy)
            y(iy) = temp 
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end



      subroutine xdswap(n,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*)

      double precision temp
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   xn = 0.0d0
      yn = 0.0d0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            temp = x(i)
            x(i) = y(i)
            y(i) = temp 
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            temp = x(ix)
            x(ix) = y(iy)
            y(iy) = temp 
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end



      subroutine xcswap(n,x,incx,y,incy)

      integer incx,incy,n
      complex x(*),y(*)

      complex temp
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   xn = 0.0e0
      yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            temp = x(i)
            x(i) = y(i)
            y(i) = temp 
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            temp = x(ix)
            x(ix) = y(iy)
            y(iy) = temp 
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end



      subroutine xzswap(n,x,incx,y,incy)

      integer incx,incy,n
      complex*16 x(*),y(*)

      complex*16 temp
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   xn = 0.0e0
      yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            temp = x(i)
            x(i) = y(i)
            y(i) = temp 
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            temp = x(ix)
            x(ix) = y(iy)
            y(iy) = temp 
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end
