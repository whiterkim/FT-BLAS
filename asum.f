      real function xsasum(n, x, incx)
      
      integer incx, n
      real x(*)

      integer i, nincx, m, mp1
      real sum1, sum2
      
      intrinsic abs

      common seps,deps
100   xsasum = 0.0e0
      sum1 = 0.0e0
      sum2 = 0.0e0
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        m = mod(n,6)
        if (m.NE.0) then
          do i = 1,m
            sum1 = sum1 + abs(x(i))
            sum2 = sum2 + abs(x(i))
          end do
          if (n.lt.6) then
            if (abs(sum1 - sum2).ge.seps) goto 100
            xsasum = sum1
            return
          end if
        end if
        mp1 = m + 1
        do i = mp1,n,6
          sum1 = sum1 + abs(x(i)) + abs(x(i+1)) + abs(x(i+2)) + 
     $                  abs(x(i+3)) + abs(x(i+4)) + abs(x(i+5))
          sum2 = sum2 + abs(x(i)) + abs(x(i+1)) + abs(x(i+2)) + 
     $                  abs(x(i+3)) + abs(x(i+4)) + abs(x(i+5))
        end do
      else
        nincx = n*incx
        do i = 1,nincx,incx
          sum1 = sum1 + abs(x(i))
          sum2 = sum2 + abs(x(i))
        end do
      end if
      if (abs(sum1 - sum2).ge.seps) goto 100

      xsasum = sum1 
      return
      end
      
      double precision function xdasum(n, x, incx)
      
      integer incx, n
      double precision x(*)

      integer i, nincx, m, mp1
      double precision sum1, sum2
      
      intrinsic abs

      common seps,deps
100   xdasum = 0.0d0
      sum1 = 0.0d0
      sum2 = 0.0d0
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        m = mod(n,6)
        if (m.NE.0) then
          do i = 1,m
            sum1 = sum1 + abs(x(i))
            sum2 = sum2 + abs(x(i))
          end do
          if (n.lt.6) then
            if (abs(sum1 - sum2).ge.seps) goto 100
            xdasum = sum1
            return
          end if
        end if
        mp1 = m + 1
        do i = mp1,n,6
          sum1 = sum1 + abs(x(i)) + abs(x(i+1)) + abs(x(i+2)) + 
     $                  abs(x(i+3)) + abs(x(i+4)) + abs(x(i+5))
          sum2 = sum2 + abs(x(i)) + abs(x(i+1)) + abs(x(i+2)) + 
     $                  abs(x(i+3)) + abs(x(i+4)) + abs(x(i+5))
        end do
      else
        nincx = n*incx
        do i = 1,nincx,incx
          sum1 = sum1 + abs(x(i))
          sum2 = sum2 + abs(x(i))
        end do
      end if
      if (abs(sum1 - sum2).ge.deps) goto 100

      xdasum = sum1 
      return
      end

      real function xscasum(n, x, incx)
      
      integer n, incx
      complex x(*)

      integer i, nincx
      real sum1, sum2
      
      intrinsic abs, real, aimag

      common seps,deps
100   xscasum = 0.0e0
      sum1 = 0.0e0
      sum2 = 0.0e0
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        do i = 1,n
          sum1 = sum1 + abs(real(x(i))) + abs(aimag(x(i)))
          sum2 = sum2 + abs(real(x(i))) + abs(aimag(x(i)))
        end do
      else
        nincx = n*incx
        do i = 1,nincx,incx
          sum1 = sum1 + abs(real(x(i))) + abs(aimag(x(i)))
          sum2 = sum2 + abs(real(x(i))) + abs(aimag(x(i)))
        end do
      end if
      if (abs(sum1 - sum2).ge.seps) goto 100

      xscasum = sum1 
      return
      end


      double precision function xdzasum(n, x, incx)
      
      integer n, incx
      complex*16 x(*)

      integer i, nincx
      double precision sum1, sum2
      
      intrinsic abs, dble, aimag

      common seps,deps

100   xdzasum = 0.0d0
      sum1 = 0.0d0
      sum2 = 0.0d0
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        do i = 1,n
          sum1 = sum1 + abs(dble(x(i))) + abs(aimag(x(i)))
          sum2 = sum2 + abs(dble(x(i))) + abs(aimag(x(i)))
        end do
      else
        nincx = n*incx
        do i = 1,nincx,incx
          sum1 = sum1 + abs(dble(x(i))) + abs(aimag(x(i)))
          sum2 = sum2 + abs(dble(x(i))) + abs(aimag(x(i)))
        end do
      end if
      if (abs(sum1 - sum2).ge.deps) goto 100

      xdzasum = sum1 
      return
      end
