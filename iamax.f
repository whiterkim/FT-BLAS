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
            amax = abs(x(ix))
          endif
          ix = ix + incx
        end do
      end if
      return
      end

      integer function xicamax(n, x, incx)
      
      integer incx, n      
      complex x(*)
      
      real amax_1, amax_2, temp_1, temp_2
      integer i, ix
      
      intrinsic abs, aimag, real

      common seps,deps
      
      xicamax = 0
      if (n.lt.1 .or. incx.le.0) return
      xicamax = 1
      if (n.eq.1) return
      
      if (incx.eq.1) then
100     amax_1 = abs(real(x(1))) + abs(aimag(x(1)))
        amax_2 = abs(real(x(1))) + abs(aimag(x(1)))
        if (abs(amax_1 - amax_2) > seps) goto 100
        do i = 2,n
200       temp_1 = abs(real(x(i))) + abs(aimag(x(i)))
          temp_2 = abs(real(x(i))) + abs(aimag(x(i)))
          if (abs(temp_1 - temp_2) > seps) goto 200
          if (temp_1.gt.amax_1) then
            xicamax = i
            amax_1 = temp_1
          endif
        end do
      else
        ix = 1
300     amax_1 = abs(real(x(1))) + abs(aimag(x(1)))
        amax_2 = abs(real(x(1))) + abs(aimag(x(1)))
        if (abs(amax_1 - amax_2) > seps) goto 300
        ix = ix + incx
        do i = 2,n
400       temp_1 = abs(real(x(ix))) + abs(aimag(x(ix)))
          temp_2 = abs(real(x(ix))) + abs(aimag(x(ix)))
          if (abs(temp_1 - temp_2) > seps) goto 400
          if (temp_1.gt.amax_1) then
            xicamax = i
            amax_1 = temp_1
          endif
          ix = ix + incx
        end do
      end if
      return
      end

      integer function xizamax(n, x, incx)
      
      integer incx, n      
      complex*16 x(*)
      
      double precision amax_1, amax_2, temp_1, temp_2
      integer i, ix
      
      intrinsic dabs, aimag, dble

      common seps,deps
      
      xizamax = 0
      if (n.lt.1 .or. incx.le.0) return
      xizamax = 1
      if (n.eq.1) return
      
      if (incx.eq.1) then
100     amax_1 = abs(dble(x(1))) + abs(aimag(x(1)))
        amax_2 = abs(dble(x(1))) + abs(aimag(x(1)))
        if (abs(amax_1 - amax_2) > seps) goto 100
        do i = 2,n
200       temp_1 = abs(dble(x(i))) + abs(aimag(x(i)))
          temp_2 = abs(dble(x(i))) + abs(aimag(x(i)))
          if (dabs(temp_1 - temp_2) > seps) goto 200
          if (temp_1.gt.amax_1) then
            xizamax = i
            amax_1 = temp_1
          endif
        end do
      else
        ix = 1
300     amax_1 = abs(dble(x(1))) + abs(aimag(x(1)))
        amax_2 = abs(dble(x(1))) + abs(aimag(x(1)))
        if (abs(amax_1 - amax_2) > seps) goto 300
        ix = ix + incx
        do i = 2,n
400       temp_1 = abs(dble(x(ix))) + abs(aimag(x(ix)))
          temp_2 = abs(dble(x(ix))) + abs(aimag(x(ix)))
          if (abs(temp_1 - temp_2) > seps) goto 400
          if (temp_1.gt.amax_1) then
            xizamax = i
            amax_1 = temp_1
          endif
          ix = ix + incx
        end do
      end if
      return
      end
