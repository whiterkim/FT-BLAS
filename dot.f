      ! function: sdot
      ! S: Real version
      real function xsdot(n,x,incx,y,incy)

      integer incx,incy,n,m,m1
      real x(*),y(*)

      real d1,d2,xi,yi
      integer i,ix,iy

      intrinsic abs,mod

      common seps,deps
100   d1 = 0.0e0
      d2 = 0.0e0
      xsdot = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
	 m = mod(n,5)
	 if (m.ne.0) then
	     do i = 1,m
		d1 = d1 + x(i)*y(i)
		d2 = d2 + x(i)*y(i)
	     end do
	     if (n.lt.5) then
		xsdot = d1                 
		return
	     end if
	 end if
	 m1 = m + 1
         do i = m1,n,5
	    d1 = d1 + x(i)*y(i) + x(i+1)*y(i+1) +
     $            x(i+2)*y(i+2) + x(i+3)*y(i+3) + x(i+4)*y(i+4)
	    d2 = d2 + x(i)*y(i) + x(i+1)*y(i+1) +
     $            x(i+2)*y(i+2) + x(i+3)*y(i+3) + x(i+4)*y(i+4)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            d1 = d1 + xi*yi
            d2 = d2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
110   if (abs(d1 - d2).ge.seps) then
         goto 100
      end if
      xsdot = d1
      return
      end


      ! function: ddot
      ! D: Double precison version
      double precision function xddot(n,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*)

      double precision d1,d2,xi,yi
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   d1 = 0.0d0
      d2 = 0.0d0
      xddot = 0.0d0
      if (n.le.0) return
       if (incx.eq.1 .and. incy.eq.1) then
	 m = mod(n,5)
	 if (m.ne.0) then
	     do i = 1,m
		d1 = d1 + x(i)*y(i)
		d2 = d2 + x(i)*y(i)
	     end do
	     if (n.lt.5) then
		xddot = d1                 
		return
	     end if
	 end if
	 m1 = m + 1
         do i = m1,n,5
	    d1 = d1 + x(i)*y(i) + x(i+1)*y(i+1) +
     $            x(i+2)*y(i+2) + x(i+3)*y(i+3) + x(i+4)*y(i+4)
	    d2 = d2 + x(i)*y(i) + x(i+1)*y(i+1) +
     $            x(i+2)*y(i+2) + x(i+3)*y(i+3) + x(i+4)*y(i+4)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            d1 = d1 + xi*yi
            d2 = d2 + xi*yi
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(d1 - d2).ge.deps) then
         goto 100
      end if
      xddot = d1
      return
      end


      ! function: dsdot
      ! DS: Real to Double precison version
      double precision function xdsdot(n,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*)

      double precision d1,d2,xi,yi
      integer i,ix,iy
 
      real x1,x2,x3,x4,x5
      real y1,y2,y3,y4,y5

      intrinsic abs,dble

      common seps,deps
100   d1 = 0.0d0
      d2 = 0.0d0
      xdsdot = 0.0d0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
	 m = mod(n,5)
	 if (m.ne.0) then
	     do i = 1,m
		d1 = d1 + x(i)*y(i)
		d2 = d2 + x(i)*y(i)
	     end do
	     if (n.lt.5) then
		xsdot = d1                 
		return
	     end if
	 end if
	 m1 = m + 1
         do i = m1,n,5
	    x1 = x(i)
	    x2 = x(i+1)
            x3 = x(i+2)
	    x4 = x(i+3)
	    x5 = x(i+4)
	    y1 = y(i)
	    y2 = y(i+1)
            y3 = y(i+2)
	    y4 = y(i+3)
	    y5 = y(i+4)
	    d1 = d1 + dble(x1)*dble(y1) + dble(x2)*dble(y2) +
     $      dble(x3)*dble(y3) + dble(x4)*dble(y4) + dble(x5)*dble(y5)
	    d2 = d2 + dble(x1)*dble(y1) + dble(x2)*dble(y2) +
     $      dble(x3)*dble(y3) + dble(x4)*dble(y4) + dble(x5)*dble(y5)
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            d1 = d1 + dble(xi)*dble(yi)
            d2 = d2 + dble(xi)*dble(yi)
            ix = ix + incx
            iy = iy + incy
         end do
      end if
      if (abs(d1 - d2).ge.deps) then
         goto 100
      end if
      xdsdot = d1
      return
      end
