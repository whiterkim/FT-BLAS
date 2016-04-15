      real function xsasum(n, x, incx)
      
      real x(*)
      integer i,nincx, m, mp1

      real sum1, sum2
      
      intrinsic abs

      common seps,deps
100   xsasum = 0.0
      sum1 = 0.0
      sum2 = 0.0
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
     $           abs(x(i+3)) + abs(x(i+4)) + abs(x(i+5))
          sum2 = sum2 + abs(x(i)) + abs(x(i+1)) + abs(x(i+2)) + 
     $           abs(x(i+3)) + abs(x(i+4)) + abs(x(i+5))
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
       
      double precision x(*) 
      integer i,nincx

      double precision sum1, sum2
      
      intrinsic abs
      
      common seps,deps
100   xdasum = 0.0
      sum1 = 0.0
      sum2 = 0.0
      if (n.le.0 .or. incx.le.0) return
      if (incx.eq.1) then
        do i = 1,n
          sum1 = sum1 + abs(x(i))
          sum2 = sum2 + abs(x(i))
        end do
      else
        nincx = n*incx
        do i = 1,nincx,incx
          sum1 = sum1 + abs(x(i))
          sum2 = sum2 + abs(x(i))
        end do
      end if
      if (abs(sum1 - sum2).ge.seps) goto 100

      xdasum = sum1
      return    
      end
