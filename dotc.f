      ! function: cdotc
      ! C: complex*8 precison version
      complex*8 function xcdotc(n,x,incx,y,incy)

      integer incx,incy,n
      complex*8 x(*),y(*)

      complex*8 c1,c2,xi,yi
      integer i,ix,iy

      intrinsic abs,conjg

      common seps,deps
100   c1 = (0.0,0.0)
      c2 = (0.0,0.0)
      xcdotc = (0.0,0.0)
   
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            c1 = c1 + conjg(xi)*yi
            c2 = c2 + conjg(xi)*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            c1 = c1 + conjg(xi)*yi
            c2 = c2 + conjg(xi)*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(c1 - c2).ge.seps) then
         goto 100
      end if
      xcdotc = c1
      return
      end


      ! function: zdotc
      ! Z: complex*16 precison version
      complex*16 function xzdotc(n,x,incx,y,incy)

      integer incx,incy,n
      complex*16 x(*),y(*)

      complex*16 c1,c2,xi,yi
      integer i,ix,iy

      intrinsic abs,dconjg

      common seps,deps
100   c1 = (0.0d0,0.0d0)
      c2 = (0.0d0,0.0d0)
      xzdotc = (0.0d0,0.0d0)
   
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            c1 = c1 + dconjg(xi)*yi
            c2 = c2 + dconjg(xi)*yi
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            c1 = c1 + dconjg(xi)*yi
            c2 = c2 + dconjg(xi)*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(c1 - c2).ge.deps) then
         goto 100
      end if
      xzdotc = c1
      return
      end
