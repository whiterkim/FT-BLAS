
      subroutine xsaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*),alpha
      
      ! Temporaries
      real y1, y2, y11, y12, y21, y22, y31, y32, y41, y42
      real xi, yi
      integer i,ix,iy, m, mp1

      intrinsic abs, mod

      common seps,deps
100   y1 = 0.0e0
      y2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         
        m = mod(n,4)
        if (m.ne.0) then
            do i = 1,m
                y1 = y(i) + x(i) * alpha
                y2 = y(i) + x(i) * alpha 
                
!           Recalculation
                if(abs(y1 - y2).ge.seps) then
                    goto 100
                else
                    y(i) = y1
                endif
            end do 
            if(n.lt.4) return
        end if
        mp1 = m + 1
        y1 = 0.0e0
        y2 = 0.0e0
        y11 = 0.0e0
        y21 = 0.0e0
        y31 = 0.0e0
        y41 = 0.0e0
        y12 = 0.0e0
        y22 = 0.0e0
        y32 = 0.0e0
        y42 = 0.0e0
        do i = mp1, n, 4
           y11 = y(i) + x(i) * alpha
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
            if(abs(y1 - y2).ge.seps) then
                goto 100
            else
                y(i) = y11
                y(i+1) = y21
                y(i+2) = y31
                y(i+3) = y41
            end if
        end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy) 

            y1 = yi + xi * alpha;
            y2 = yi + xi * alpha;
            if(abs(y1 - y2).ge.seps) then
                goto 100
            else
                y(iy) = y1
            end if
            ix = ix + incx
            iy = iy + incy              
         end do
      end if
      
      return
      end
      
      
       subroutine xdaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*),alpha
      
     ! Temporaries
      double precision y1, y2, y11, y12, y21, y22, y31, y32, y41, y42
      double precision xi, yi
      integer i,ix,iy, m, mp1

      intrinsic abs, mod

      common seps,deps
100   y1 = 0.0e0
      y2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         
        m = mod(n,4)
        if (m.ne.0) then
            do i = 1,m
                y1 = (y(i) + x(i) * alpha) 
                y2 = (y(i) + x(i) * alpha) 
                
!           Recalculation
                if(abs(y1 - y2).ge.seps) then
                    goto 100
                else
                    y(i) = y1
                endif
            end do 
            if(n.lt.4) return
        end if
        mp1 = m + 1
        y1 = 0.0e0
        y2 = 0.0e0
        y11 = 0.0e0
        y21 = 0.0e0
        y31 = 0.0e0
        y41 = 0.0e0
        y12 = 0.0e0
        y22 = 0.0e0
        y32 = 0.0e0
        y42 = 0.0e0
        do i = mp1, n, 4
           y11 = y(i) + x(i) * alpha
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
            if(abs(y1 - y2).ge.deps) then
                goto 100
            else
                y(i) = y11
                y(i+1) = y21
                y(i+2) = y31
                y(i+3) = y41
            end if
        end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy) 

            y1 = yi + xi * alpha;
            y2 = yi + xi * alpha;
            if(abs(y1 - y2).ge.deps) then
                goto 100
            else
                y(iy) = y1
            end if
            ix = ix + incx
            iy = iy + incy              
         end do
      end if
      
      
      return
      end
