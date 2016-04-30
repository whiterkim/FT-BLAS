
      subroutine xsscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      real x(*),alpha

        ! Temporaries      
      real x1, x2, x11, x12, x21, x22, x31, x32, x41, x42, x51, x52
      real xi
      integer i,ix, mp1

      intrinsic abs

      common seps,deps
100   x1 = 0.0e0
      x2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         
        
        m = mod(n,5)
        if(m.NE.0) then
            do i = 1,m
                x1 = x1 +(x(i) * alpha)
                x2 = x2 + (x(i) * alpha)

!               Recalculation
                if(abs(x1 - x2).ge.seps) then
                    goto 100
                else
                    x(i) = x1
                endif
            end do
            if (n.lt.5) return
        end if
        mp1 = m + 1
        x1 = 0.0e0
        x2 = 0.0e0
        x11 = 0.0e0
        x21 = 0.0e0
        x31 = 0.0e0
        x41 = 0.0e0
        x51 = 0.0e0
        x12 = 0.0e0
        x22 = 0.0e0
        x32 = 0.0e0
        x42 = 0.0e0
        x52 = 0.0e0
        do i = mp1, n, 5
            x11 = x(i) * alpha
            x21 = x(i+1) * alpha
            x31 = x(i+2) * alpha
            x41 = x(i+3) * alpha
            x51 = x(i+4) * alpha
            x12 = x(i) * alpha
            x22 = x(i+1) * alpha
            x32 = x(i+2) * alpha
            x42 = x(i+3) * alpha
            x52 = x(i+4) * alpha
            x1 = x11 + x21 + x31 + x41 + x51
            x2 = x12 + x22 + x32 + x42 + x52
!           Recalculation          
            if(abs(x1 - x2).ge.seps) then
                goto 100
            else
                x(i) = x11
                x(i+1) = x21
                x(i+2) = x31
                x(i+3) = x41
                x(i+4) = x51
            end if
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            
            ! Recalculation Check
            x1 = xi * alpha
            x2 = xi * alpha
            if(abs(x1 - x2).ge.seps) then
                goto 100
            else
                x(ix) = x1
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
      double precision  x1, x2, x11, x12, x21, x22, x31, x32, x41, x42
      double precision  x51, x52
      integer i,ix

      intrinsic abs

      common seps,deps
100   x1 = 0.0e0
      x2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         
        
        m = mod(n,5)
        if(m.NE.0) then
            do i = 1,m
                x1 = x1 +(x(i) * alpha)
                x2 = x2 + (x(i) * alpha)

!               Recalculation
                if(abs(x1 - x2).ge.deps) then
                    goto 100
                else
                    x(i) = x1
                endif
            end do
            if (n.lt.5) return
        end if
        mp1 = m + 1
        x1 = 0.0e0
        x2 = 0.0e0
        x11 = 0.0e0
        x21 = 0.0e0
        x31 = 0.0e0
        x41 = 0.0e0
        x51 = 0.0e0
        x12 = 0.0e0
        x22 = 0.0e0
        x32 = 0.0e0
        x42 = 0.0e0
        x52 = 0.0e0
        do i = mp1, n, 5
            x11 = x(i) * alpha
            x21 = x(i+1) * alpha
            x31 = x(i+2) * alpha
            x41 = x(i+3) * alpha
            x51 = x(i+4) * alpha
            x12 = x(i) * alpha
            x22 = x(i+1) * alpha
            x32 = x(i+2) * alpha
            x42 = x(i+3) * alpha
            x52 = x(i+4) * alpha
            x1 = x11 + x21 + x31 + x41 + x51
            x2 = x12 + x22 + x32 + x42 + x52
!           Recalculation           
            if(abs(x1 - x2).ge.deps) then
                goto 100
            else
                x(i) = x11
                x(i+1) = x21
                x(i+2) = x31
                x(i+3) = x41
                x(i+4) = x51
            end if
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            
            ! Recalculation Check
            x1 = xi * alpha
            x2 = xi * alpha
            if(abs(x1 - x2).ge.deps) then
                goto 100
            else
                x(ix) = x1
            endif
            ix = ix + incx
         end do
      end if
      
      
      return
      end
