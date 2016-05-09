
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




      subroutine xcscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      complex x(*),alpha
      real r1, r2, i1, i2
      
      ! Temporaries      
      complex  x1, x2, x11, x12, x21, x22, x31, x32, x41, x42,
     $         x51, x52, xi
      integer i,ix

      intrinsic abs, real, aimag

      common seps,deps
100   x1 = 0.0
      x2 = 0.0
      r1 = 0.0
      r2 = 0.0
      i1 = 0.0
      i2 = 0.0
      if (n.le.0) return
      if (incx.eq.1) then
        m = mod(n,5)
        if(m.ne.0) then
            do i = 1,m
                xi = x(i)
                x1 = (x(i) * alpha)
                x2 = (x(i) * alpha)
                r1 = real(x1) + aimag(x1)
                r2 = real(x2) + aimag(x2)
!               Recalculation
                if(abs(r1 - r2).ge.seps) then
                    goto 100
                else
                    x(i) = x1
                endif
            end do
            if (n.lt.5) return
        end if
        mp1 = m + 1
        x11 = 0.0
        x21 = 0.0
        x31 = 0.0
        x41 = 0.0
        x51 = 0.0
        x12 = 0.0
        x22 = 0.0
        x32 = 0.0
        x42 = 0.0
        x52 = 0.0
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
            r1 = real(x11) + real(x21) + real(x31) + real(x41) +
     $           real(x51) + aimag(x11) + aimag(x21) + aimag(x31) + aimag(x41)
     $           + aimag(x51)
            r2 = real(x12) + real(x22) + real(x32) + real(x42) +
     $           real(x52) + aimag(x12) + aimag(x22) + aimag(x32) + aimag(x42) +
     $           + aimag(x52)
!            i1 = aimag(x11) + aimag(x21) + aimag(x31) + aimag(x41) +
! $           aimag(x51)
!           i2 = aimag(x12) + aimag(x22) + aimag(x32) + aimag(x42) +
! $           aimag(x52)
!            x1 = x11 + x21 + x31 + x41 + x51
!            x2 = x12 + x22 + x32 + x42 + x52
!           Recalculation           
            if(abs(r1 - r2).ge.seps) then
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
            x1 = (x(i) * alpha)
            x2 = (x(i) * alpha)
            r1 = real(x1) + aimag(x1)
            r2 = real(x2) + aimag(x2)

            if(abs(r1 - r2).ge.seps) then
                goto 100
            else
                x(ix) = x1
            endif
            ix = ix + incx
         end do
      end if
      
      
      return
      end




      subroutine xcsscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      complex x(*)
      real alpha, r1, r2, i1, i2
      
        ! Temporaries      
      complex  x1, x2, x11, x12, x21, x22, x31, x32, x41, x42,
     $         x51, x52, xi
      integer i,ix

      intrinsic abs, real, aimag, cmplx

      common seps,deps
100   x1 = 0.0
      x2 = 0.0
      r1 = 0.0
      r2 = 0.0
      i1 = 0.0
      i2 = 0.0
      if (n.le.0) return
      if (incx.eq.1) then
         
        
        m = mod(n,5)
        if(m.NE.0) then
            do i = 1,m
                xi = x(i)
                x1 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
                x2 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
                r1 = real(x1) + aimag(x1)
                r2 = real(x2) + aimag(x2)
!               Recalculation
                if(abs(r1 - r2).ge.seps) then
                    goto 100
                else
                    x(i) = x1
                endif
            end do
            if (n.lt.5) return
        end if
        mp1 = m + 1
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
            r1 = real(x11) + real(x21) + real(x31) + real(x41) +
     $           real(x51)
            r2 = real(x12) + real(x22) + real(x32) + real(x42) +
     $           real(x52)
            i1 = aimag(x11) + aimag(x21) + aimag(x31) + aimag(x41) +
     $           aimag(x51)
            i2 = aimag(x12) + aimag(x22) + aimag(x32) + aimag(x42) +
     $           aimag(x52)
!            x1 = x11 + x21 + x31 + x41 + x51
!            x2 = x12 + x22 + x32 + x42 + x52
!           Recalculation           
            if(abs(r1 - r2).ge.seps .or. abs(i1 - i2).ge.seps) then
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
            x1 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
            x2 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
            r1 = real(x1) + aimag(x1)
            r2 = real(x2) + aimag(x2)
           
!               Recalculation
            if(abs(r1 - r2).ge.seps) then
                goto 100
            else
                x(ix) = x1
            endif
            ix = ix + incx
         end do
      end if
      
      
      return
      end

