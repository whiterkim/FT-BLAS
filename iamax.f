      integer function xisamax(n, x, incx)
      
      integer incx, n      
      real x(*)
      
      real amax
      integer i, ix
      
      intrinsic abs
      
      xisamax = 0
      if (n.lt.1 .or. incx.le.0) return
      xisamax = 1
      if (n.eq.1) return
      
      if (incx.eq.1) then
        amax = abs(x(1))
        do i = 2,n
          if (abs(x(i)).gt.amax) then
            xisamax = i
            amax = abs(x(i))
          endif
        end do
      else
        ix = 1
        amax = abs(x(1))
        ix = ix + incx
        do i = 2,n
          if (abs(x(ix)).gt.amax) then
            xisamax = i
            amax = abs(x(ix))
          endif
          ix = ix + incx
        end do
      end if
      return
      end
      
      integer function xidamax(n, x, incx)
      
      integer incx, n      
      double precision x(*)
      
      double precision amax
      integer i, ix
      
      intrinsic abs
      
      xidamax = 0
      if (n.lt.1 .or. incx.le.0) return
      xidamax = 1
      if (n.eq.1) return
      
      if (incx.eq.1) then
        amax = abs(x(1))
        do i = 2,n
          if (abs(x(i)).gt.amax) then
            xidamax = i
            amax = abs(x(i))
          endif
        end do
      else
        ix = 1
        amax = abs(x(1))
        ix = ix + incx
        do i = 2,n
          if (abs(x(ix)).gt.amax) then
            xidamax = i
            amax = abs(x(i))
          endif
          ix = ix + incx
        end do
      end if
      return
      end
