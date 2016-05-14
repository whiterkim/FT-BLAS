
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
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        m = mod(n,5)
        if(m.NE.0) then
            do i = 1,m
100             x1 = x1 +(x(i) * alpha)
                x2 = x2 + (x(i) * alpha)

                if(abs(x1 - x2).ge.seps) goto 100
                 x(i) = x1
            end do
        end if
        if (n.lt.5) return
        mp1 = m + 1
        do i = mp1, n, 5
200         x11 = x(i) * alpha
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
            
            if(abs(x1 - x2).ge.seps) goto 200
            x(i) = x11
            x(i+1) = x21
            x(i+2) = x31
            x(i+3) = x41
            x(i+4) = x51
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
300         x1 = x(ix) * alpha
            x2 = x(ix) * alpha
           
            if(abs(x1 - x2).ge.seps) goto 300
            x(ix) = x1
            
            ix = ix + incx
         end do
      end if
      
      return
      end




      subroutine xdscal(n,alpha,x,incx)

      integer incx,n
      double precision x(*),alpha
      
      double precision  x1, x2, x11, x12, x21, x22, x31, x32, x41, x42
      double precision  x51, x52
      integer i,ix

      intrinsic abs

      common seps,deps
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        m = mod(n,5)
        if(m.NE.0) then
            do i = 1,m
100             x1 = x1 +(x(i) * alpha)
                x2 = x2 + (x(i) * alpha)

                if(abs(x1 - x2).ge.deps) goto 100
                 x(i) = x1
            end do
        end if
        if (n.lt.5) return
        mp1 = m + 1
        do i = mp1, n, 5
200         x11 = x(i) * alpha
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
            
            if(abs(x1 - x2).ge.deps) goto 200
            x(i) = x11
            x(i+1) = x21
            x(i+2) = x31
            x(i+3) = x41
            x(i+4) = x51
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
300         x1 = x(ix) * alpha
            x2 = x(ix) * alpha
           
            if(abs(x1 - x2).ge.deps) goto 300
            x(ix) = x1
            
            ix = ix + incx
         end do
      end if
      
      return
      end

      subroutine xcscal(n,alpha,x,incx)

      integer incx,n
      complex x(*),alpha
      complex x11, x12, x21, x22, x31, x32, x41, x42, x51, x52
      complex xi, x1, x2
      integer i,ix, m, mp1

      intrinsic abs, mod

      common seps,deps
      
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        m = mod(n,5)
        if(m.ne.0) then
            do i = 1,m
100             x1 = (x(i) * alpha)
                x2 = (x(i) * alpha)
   
                if((abs(real(x1) - real(x2)).ge. seps).or.
     $             (abs(aimag(x1) - aimag(x2)).ge. seps)) goto 100
                x(i) = x1
            end do
        end if
        if (n.lt.5) return
        mp1 = m + 1
        do i = mp1, n, 5
200         x11 = x(i) * alpha
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

            if((abs(real(x1) - real(x2)).ge. seps).or.
     $         (abs(aimag(x1) - aimag(x2)).ge. seps)) goto 200
            x(i) = x11
            x(i+1) = x21
            x(i+2) = x31
            x(i+3) = x41
            x(i+4) = x51
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
300         x1 = x(ix) * alpha
            x2 = x(ix) * alpha

            if((abs(real(x1) - real(x2)).ge. seps).or.
     $         (abs(aimag(x1) - aimag(x2)).ge. seps)) goto 300
            x(ix) = x1

            ix = ix + incx
         end do
      end if
      
      return
      end




      subroutine xcsscal(n,alpha,x,incx)

      integer incx,n
      complex x(*)
      real alpha
      
      complex  x1, x2, x11, x12, x21, x22, x31, x32, x41, x42,
     $         x51, x52, xi
      integer i,ix

      intrinsic abs, mod

      common seps,deps
      
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        m = mod(n,5)
        if(m.NE.0) then
            do i = 1,m
100             xi = x(i)
                x1 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
                x2 = cmplx(real(xi) * alpha, aimag(xi) * alpha)

                if((abs(real(x1) - real(x2)).ge. seps).or.
     $             (abs(aimag(x1) - aimag(x2)).ge. seps)) goto 100
                x(i) = x1
            end do
        end if
        if (n.lt.5) return
        mp1 = m + 1
        do i = mp1, n, 5
200         x11 = cmplx(real(x(i)) * alpha, aimag(x(i)) * alpha)
            x21 = cmplx(real(x(i+1)) * alpha, aimag(x(i+1)) * alpha)
            x31 = cmplx(real(x(i+2)) * alpha, aimag(x(i+2)) * alpha)
            x41 = cmplx(real(x(i+3)) * alpha, aimag(x(i+3)) * alpha)
            x51 = cmplx(real(x(i+4)) * alpha, aimag(x(i+4)) * alpha)

            x12 = cmplx(real(x(i)) * alpha, aimag(x(i)) * alpha)
            x22 = cmplx(real(x(i+1)) * alpha, aimag(x(i+1)) * alpha)
            x32 = cmplx(real(x(i+2)) * alpha, aimag(x(i+2)) * alpha)
            x42 = cmplx(real(x(i+3)) * alpha, aimag(x(i+3)) * alpha)
            x52 = cmplx(real(x(i+4)) * alpha, aimag(x(i+4)) * alpha)
            
            x1 = x11 + x21 + x31 + x41 + x51
            x2 = x12 + x22 + x32 + x42 + x52

            if((abs(real(x1) - real(x2)).ge. seps).or.
     $         (abs(aimag(x1) - aimag(x2)).ge. seps)) goto 200
            x(i) = x11
            x(i+1) = x21
            x(i+2) = x31
            x(i+3) = x41
            x(i+4) = x51
        end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
300         xi = x(ix)
            x1 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
            x2 = cmplx(real(xi) * alpha, aimag(xi) * alpha)
           
            if((abs(real(x1) - real(x2)).ge. seps).or.
     $         (abs(aimag(x1) - aimag(x2)).ge. seps)) goto 300
            x(ix) = x1

            ix = ix + incx
         end do
      end if
      
      
      return
      end

