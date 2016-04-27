
      subroutine xsscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      real x(*),alpha

        ! Temporaries      
      real x_t(n), xi_1, xi_2

      real xn
      integer i,ix, mp1

      intrinsic abs

      common seps,deps
100   xi_1 = 0.0e0
      xi_2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         
        
        m = mod(n,5);
        if(m.NE.0) then
            do i = 1,m
                xi_1 = xi_1 +(x(i) * alpha)
                xi_2 = xi_2 + (x(i) * alpha)
                x_t(i) = x(i) * alpha
            end do

!           Recalculation
            if(abs(xi_1 - xi_2).ge.seps) then
                goto 100
            else
                do i = 1,m
                   x(i) = x_t(i);
                end do
            endif
            if (n.lt.5) return
        end if
        mp1 = m + 1
        xi_1 = 0.0e0
        xi_2 = 0.0e0
        do i = mp1, n, 5
            xi_1 = xi_1 + (x(i) * alpha) + (x(i+1) * alpha) + 
     $           (x(i+2) * alpha) + (x(i+3) * alpha) + (x(i+4) * alpha)
            xi_2 = xi_2 + (x(i) * alpha) + (x(i+1) * alpha) + 
     $           (x(i+2) * alpha) + (x(i+3) * alpha) + (x(i+4) * alpha)

!           Recalculation           
            if(abs(xi_1 - xi_2).ge.seps) then
                goto 100
            else
                x(i) = x(i) * alpha
                x(i+1) = x(i+1) * alpha
                x(i+2) = x(i+2) * alpha
                x(i+3) = x(i+3) * alpha
                x(i+4) = x(i+4) * alpha
            end if
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            
            ! Recalculation Check
            xi_1 = xi * alpha;
            xi_2 = xi * alpha;
            if(abs(xi_1 - xi_2).ge.seps) then
                goto 100
            else
                x(ix) = xi_1;
            endif
            ix = ix + incx
         end do
      end if
      
      return
      end




      subroutine xdscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      double precision x(*),alpha
      
       ! Temporaries
      double precision x_t(n), xi_1, xi_2
      
      double precision xi,xn
      integer i,ix

      intrinsic abs

      common seps,deps
200   xi_1 = 0.0e0
      xi_2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         
        
        m = mod(n,5);
        if(m.NE.0) then
            do i = 1,m
                xi_1 = xi_1 +(x(i) * alpha)
                xi_2 = xi_2 + (x(i) * alpha)
                x_t(i) = x(i) * alpha
            end do

!           Recalculation
            if(abs(xi_1 - xi_2).ge.seps) then
                goto 200
            else
                do i = 1,m
                   x(i) = x_t(i);
                end do
            endif
            if (n.lt.5) return
        end if
        mp1 = m + 1
        do i = mp1, n, 5
            xi_1 = xi_1 + (x(i) * alpha) + (x(i+1) * alpha) + 
     $           (x(i+2) * alpha) + (x(i+3) * alpha) + (x(i+4) * alpha)
            xi_2 = xi_2 + (x(i) * alpha) + (x(i+1) * alpha) + 
     $           (x(i+2) * alpha) + (x(i+3) * alpha) + (x(i+4) * alpha)

!           Recalculation           
            if(abs(xi_1 - xi_2).ge.deps) then
                goto 200
            else
                x(i) = x(i) * alpha
                x(i+1) = x(i+1) * alpha
                x(i+2) = x(i+2) * alpha
                x(i+3) = x(i+3) * alpha
                x(i+4) = x(i+4) * alpha
            end if
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            
            ! Recalculation Check
            xi_1 = xi * alpha;
            xi_2 = xi * alpha;
            if(abs(xi_1 - xi_2).ge.deps) then
                goto 200
            else
                x(i) = xi_1;
            endif
            ix = ix + incx
         end do
      end if
      
      return
      end
