      
      subroutine xsrot(n,x,incx,y,incy,c,s)

      real c,s
      integer incx,incy,n

      real x(*),y(*)

      real xi,yi,x1,x2,y1 y2
      integer i,ix,iy

      intrinsic abs

      common seps,deps
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
100         xi = x(i)
            yi = y(i)

            x1 = c*xi + s*yi
            x2 = c*xi + s*yi

            y1 = c*yi - s*xi
            y2 = c*yi - s*xi
            
            if(abs(x1 - x2).ge.seps .or. abs(y1 - y2).ge.seps) goto 100
            x(i) = x1
            y(i) = y1
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
200         xi = x(ix)
            yi = y(iy)

            x1 = c*xi + s*yi
            x2 = c*xi + s*yi

            y1 = c*yi - s*xi
            y2 = c*yi - s*xi

            if(abs(x1 - x2).ge.seps .or. abs(y1 - y2).ge.seps) goto 200
            x(ix) = x1
            y(iy) = y1

            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end

      
      
      subroutine xdrot(n,x,incx,y,incy,c,s)

      double precision c,s
      integer incx,incy,n

      double precision x(*),y(*)

      double precision xi,yi,x1,x2,y1, y2
      integer i,ix,iy

      intrinsic abs

      common seps,deps

      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
100         xi = x(i)
            yi = y(i)

            x1 = c*xi + s*yi
            x2 = c*xi + s*yi

            y1 = c*yi - s*xi
            y2 = c*yi - s*xi
            
            if(abs(x1 - x2).ge.deps .or. abs(y1 - y2).ge.deps) goto 100
            x(i) = x1
            y(i) = y1
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
200         xi = x(ix)
            yi = y(iy)

            x1 = c*xi + s*yi
            x2 = c*xi + s*yi

            y1 = c*yi - s*xi
            y2 = c*yi - s*xi

            if(abs(x1 - x2).ge.deps .or. abs(y1 - y2).ge.deps) goto 200
            x(ix) = x1
            y(iy) = y1

            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end
