
      subroutine xsaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*),alpha
      
      ! Temporaries
      real y1,y2,y11,y12,y21,y22,y31,y32,y41,y42
      real xi,yi
      integer i,ix,iy,m,mp1

      intrinsic abs, mod

      common seps,deps

      if (n.le.0) return
      if (alpha.eq.0.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         m = mod(n,4)
         if (m.ne.0) then
            do i = 1,m
100            y1 = y(i) + x(i) * alpha
               y2 = y(i) + x(i) * alpha 
!              Recalculation
               if(abs(y1 - y2).ge.seps) goto 100
               y(i) = y1
            end do 
         end if
         if(n.lt.4) return
         mp1 = m + 1
         do i = mp1,n,4
200         y11 = y(i) + x(i) * alpha
            y21 = y(i+1) + x(i+1) * alpha
            y31 = y(i+2) + x(i+2) * alpha
            y41 = y(i+3) + x(i+3) * alpha

            y12 = y(i) + x(i) * alpha 
            y22 = y(i+1) + x(i+1) * alpha
            y32 = y(i+2) + x(i+2) * alpha
            y42 = y(i+3) + x(i+3) * alpha

            y1 = y11 + y21 + y31 + y41
            y2 = y12 + y22 + y32 + y42
!           Recalculation           
            if(abs(y1 - y2).ge.seps) goto 200
            y(i) = y11
            y(i+1) = y21
            y(i+2) = y31
            y(i+3) = y41
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
300         y1 = y(iy) + x(ix) * alpha;
            y2 = y(iy) + x(ix) * alpha;
            if(abs(y1 - y2).ge.seps) goto 300
            y(iy) = y1
            ix = ix + incx
            iy = iy + incy              
         end do
      end if
      
      return
      end
      
      

      subroutine xdaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*),alpha
      
      ! Temporaries
      real y1,y2,y11,y12,y21,y22,y31,y32,y41,y42
      real xi,yi
      integer i,ix,iy,m,mp1

      intrinsic abs, mod

      common seps,deps

      if (n.le.0) return
      if (alpha.eq.0.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         m = mod(n,4)
         if (m.ne.0) then
            do i = 1,m
400            y1 = y(i) + x(i) * alpha
               y2 = y(i) + x(i) * alpha 
!              Recalculation
               if(abs(y1 - y2).ge.deps) goto 400
               y(i) = y1
            end do 
         end if
         if(n.lt.4) return
         mp1 = m + 1
         do i = mp1,n,4
500         y11 = y(i) + x(i) * alpha
            y21 = y(i+1) + x(i+1) * alpha
            y31 = y(i+2) + x(i+2) * alpha
            y41 = y(i+3) + x(i+3) * alpha

            y12 = y(i) + x(i) * alpha 
            y22 = y(i+1) + x(i+1) * alpha
            y32 = y(i+2) + x(i+2) * alpha
            y42 = y(i+3) + x(i+3) * alpha

            y1 = y11 + y21 + y31 + y41
            y2 = y12 + y22 + y32 + y42
!           Recalculation           
            if(abs(y1 - y2).ge.deps) goto 500
            y(i) = y11
            y(i+1) = y21
            y(i+2) = y31
            y(i+3) = y41
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
600         y1 = y(iy) + x(ix) * alpha;
            y2 = y(iy) + x(ix) * alpha;
            if(abs(y1 - y2).ge.deps) goto 600
            y(iy) = y1
            ix = ix + incx
            iy = iy + incy              
         end do
      end if
      
      return
      end
