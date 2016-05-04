      
      subroutine xsrot(n,x,incx,y,incy,c,s)

      real c,s
      integer incx,incy,n

      real x(*),y(*)

      real xi,yi,t11,t12,t21,t22
      integer i,ix,iy

      intrinsic abs,sign,sqrt

      common seps,deps
100   xi = 0.0e0
      yi = 0.0e0
      t11 = 0.0e0
      t12 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            t11 = c*xi + s*yi
            t12 = c*xi + s*yi
            t21 = c*yi - s*xi
            t22 = c*yi - s*xi
                
!           Recalculation
            if(abs(t11 - t12).ge.seps .or. abs(t21-t22).ge.seps) then
                goto 100
            else
                x(i) = t11
            endif
                y(i) = t21
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            t11 = c*xi + s*yi
            t12 = c*xi + s*yi
            t21 = c*yi - s*xi
            t22 = c*yi - s*xi

!           Recalculation
            if(abs(t11 - t12).ge.seps .or. abs(t21-t22).ge.seps) then
                goto 100
            else
                x(ix) = t11
                y(iy) = t21
            endif
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

      double precision xi,yi,t11, t12, t21, t22
      integer i,ix,iy

      intrinsic abs,sign,sqrt

      common seps,deps
100   xi = 0.0e0
      yi = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            t11 = c*xi + s*yi
            t12 = c*xi + s*yi
            t21 = c*yi - s*xi
            t22 = c*yi - s*xi

!           Recalculation
            if(abs(t11 - t12).ge.seps .or. abs(t21-t22).ge.seps) then
                goto 100
            else
                x(i) = t11
                y(i) = t21
            endif
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            t11 = c*xi + s*yi
            t12 = c*xi + s*yi
            t21 = c*yi - s*xi
            t22 = c*yi - s*xi

!           Recalculation
            if(abs(t11 - t12).ge.seps .or. abs(t21-t22).ge.seps) then
                goto 100
            else
                x(ix) = t11
                y(iy) = t21
            endif
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      
      return
      end
