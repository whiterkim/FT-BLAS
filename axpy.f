
      subroutine xsaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*),alpha
      
      ! Temporaries
      real y_t(n), yi_1, yi_2

      real xi,yn
      integer i,ix,iy, m, mp1

      intrinsic abs, mod

      common seps,deps
100   yi_1 = 0.0e0
      yi_2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         
        m = mod(n,4)
        if (m.ne.0) then
            do i = 1,m
                yi_1 = (y(i) + x(i) * alpha) 
                yi_2 = (y(i) + x(i) * alpha) 
                
!           Recalculation
                if(abs(yi_1 - yi_2).ge.seps) then
                    goto 100
                else
                    y(i) = yi_1
                endif
            end do 
            if(n.lt.4) return
        end if
        mp1 = m + 1
        do i = mp1, n, 4
            yi_1 = 0.0e0
            yi_2 = 0.0e0
            yi_1 = yi_1 + (y(i) + x(i) * alpha) + 
     $           (y(i+1) + x(i+1) * alpha) + (y(i+2) + x(i+2) * alpha) +
     $           (y(i+3) + x(i+3) * alpha)
            yi_2 = yi_2 + (y(i) + x(i) * alpha) + 
     $           (y(i+1) + x(i+1) * alpha) + (y(i+2) + x(i+2) * alpha) +
     $            (y(i+3) + x(i+3) * alpha)

!           Recalculation           
            if(abs(yi_1 - yi_2).ge.seps) then
                goto 100
            else
                y(i) = y(i) * alpha
                y(i+1) = y(i+1) * alpha
                y(i+2) = y(i+2) * alpha
                y(i+3) = y(i+3) * alpha
            end if
        end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            yi_1 = y(iy) + x(ix) * alpha;
            yi_2 = y(iy) + x(ix) * alpha;
            if(abs(yi_1 - yi_2).ge.seps) then
                goto 100
            else
                y(iy) = yi_1
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
      double precision y_t1(n), y_t2(n), yi_1, yi_2

      double precision xi,yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
200   yi_1 = 0.0e0
      yi_2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         
        m = mod(n,4)
        if (m.ne.0) then
            do i = 1,m
                yi_1 = (y(i) + x(i) * alpha) 
                yi_2 = (y(i) + x(i) * alpha) 
                
!           Recalculation
                if(abs(yi_1 - yi_2).ge.deps) then
                    goto 200
                else
                    y(i) = yi_1
                endif
            end do 
            if(n.lt.4) return
        end if
        mp1 = m + 1
        do i = mp1, n, 4
            yi_1 = 0.0e0
            yi_2 = 0.0e0
            yi_1 = yi_1 + (y(i) + x(i) * alpha) + 
     $           (y(i+1) + x(i+1) * alpha) + (y(i+2) + x(i+2) * alpha) +
     $           (y(i+3) + x(i+3) * alpha)
            yi_2 = yi_2 + (y(i) + x(i) * alpha) + 
     $           (y(i+1) + x(i+1) * alpha) + (y(i+2) + x(i+2) * alpha) +
     $            (y(i+3) + x(i+3) * alpha)

!           Recalculation           
            if(abs(yi_1 - yi_2).ge.seps) then
                goto 200
            else
                y(i) = y(i) * alpha
                y(i+1) = y(i+1) * alpha
                y(i+2) = y(i+2) * alpha
                y(i+3) = y(i+3) * alpha
            end if
        end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            yi_1 = y(iy) + x(ix) * alpha;
            yi_2 = y(iy) + x(ix) * alpha;
            if(abs(yi_1 - yi_2).ge.deps) then
                goto 200
            else
                y(iy) = yi_1
            end if
            ix = ix + incx
            iy = iy + incy              
         end do
      end if
      
      return
      end
