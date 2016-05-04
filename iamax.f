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

      integer function xicamax(n, x, incx)
      
      integer incx, n      
      complex x(*)
      
      real amax, temp
      integer i, ix
      
      intrinsic abs, aimag, real
      
      xicamax = 0
      if (n.lt.1 .or. incx.le.0) return
      xicamax = 1
      if (n.eq.1) return
      
      if (incx.eq.1) then
        amax = abs(real(x(1))) + abs(aimag(x(1)))
        do i = 2,n
          temp = abs(real(x(i))) + abs(aimag(x(i)))
          if (temp.gt.amax) then
            xicamax = i
            amax = temp
          endif
        end do
      else
        ix = 1
        amax = abs(real(x(1))) + abs(aimag(x(1)))
        ix = ix + incx
        do i = 2,n
          temp = abs(real(x(i))) + abs(aimag(x(i)))
          if (temp.gt.amax) then
            xicamax = i
            amax = temp
          endif
          ix = ix + incx
        end do
      end if
      return
      end

      integer function xizamax(n, x, incx)
      
      integer incx, n      
      complex*16 x(*)
      
      double precision amax, temp
      integer i, ix
      
      intrinsic abs, dimag, dble
      
      xizamax = 0
      if (n.lt.1 .or. incx.le.0) return
      xizamax = 1
      if (n.eq.1) return
      
      if (incx.eq.1) then
        amax = abs(dble(x(1))) + abs(dimag(x(1)))
        do i = 2,n
          temp = abs(dble(x(i))) + abs(dimag(x(i)))
          if (temp.gt.amax) then
            xizamax = i
            amax = temp
          endif
        end do
      else
        ix = 1
        amax = abs(dble(x(1))) + abs(dimag(x(1)))
        ix = ix + incx
        do i = 2,n
          temp = abs(dble(x(i))) + abs(dimag(x(i)))
          if (temp.gt.amax) then
            xizamax = i
            amax = temp
          endif
          ix = ix + incx
        end do
      end if
      return
      end
