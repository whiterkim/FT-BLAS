      
      subroutine xsrotm(n,x,incx,y,incy,sparam)

      real sparam(5)
      integer incx,incy,n

      real x(*),y(*)

      real sflag, sh11, sh12, sh21, sh22, two, xi, yi, zero
      integer i,ix,iy, nsteps
      
      data zero, two/0.e0,2.e0/

      sflag = sparam(1)
      if (n.le.0 .or. (sflag+two.eq.zero)) return
      if (incx.eq.incy .and. incx.gt.0) then
         
         nsteps = n*incx
         if(sflag.lt.zero) then
            sh11 = sparam(2)
            sh12 = sparam(4)
            sh21 = sparam(3)
            sh22 = sparam(5)
            do i = 1,nsteps,incx
                xi = x(i)
                yi = y(i)
                x(i) = xi*sh11 + yi*sh12
                y(i) = xi*sh21 + yi*sh22
            end do
         else if (sflag.eq.zero) then 
            sh12 = sparam(4)
            sh21 = sparam(3)
            do i = 1,nsteps,incx
                xi = x(i)
                yi = y(i)
                x(i) = xi + yi*sh12
                y(i) = xi*sh21 + yi
            end do
         else
            sh11 = sparam(2)
            sh22 = sparam(5)
            do i = 1,nsteps,incx
                xi = x(i)
                yi = y(i)
                x(i) = xi*sh11 + yi
                y(i) = -xi + yi*sh22
            end do
         end if
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         
         if(sflag.lt.zero) then
            sh11 = sparam(2)
            sh12 = sparam(4)
            sh21 = sparam(3)
            sh22 = sparam(5)
            do i = 1,n
                xi = x(ix)
                yi = y(iy)
                x(ix) = xi*sh11 + yi*sh12
                y(iy) = xi*sh21 + yi*sh22
                ix = ix + incx
                iy = iy + incy
            end do
         else if (sflag.eq.zero) then 
            sh12 = sparam(4)
            sh21 = sparam(3)
            do i = 1,n
                xi = x(ix)
                yi = y(iy)
                x(ix) = xi + yi*sh12
                y(iy) = xi*sh21 + yi
                ix = ix + incx
                iy = iy + incy
            end do
         else
            sh11 = sparam(2)
            sh22 = sparam(5)
            do i = 1,n
                xi = x(ix)
                yi = y(iy)
                x(iy) = xi*sh11 + yi
                y(iy) = -xi + yi*sh22
                ix = ix + incx
                iy = iy + incy
            end do
         end if
      end if
      return
      end
         
         
               
      subroutine xdrotm(n,x,incx,y,incy,dparam)

      double precision dparam(5)
      integer incx,incy,n

      double precision x(*),y(*)

      double precision dflag, dh11, dh12, dh21, dh22, two, xi, yi, zero
      integer i,ix,iy, nsteps
      
      data zero, two/0.d0,2.d0/
      
      dflag = dparam(1)
      if (n.le.0 .or. (dflag+two.eq.zero)) return
      if (incx.eq.incy .and. incx.gt.0) then
         
         nsteps = n*incx
         if(dflag.lt.zero) then
            dh11 = dparam(2)
            dh12 = dparam(4)
            dh21 = dparam(3)
            dh22 = dparam(5)
            do i = 1,nsteps,incx
                xi = x(i)
                yi = y(i)
                x(i) = xi*dh11 + yi*dh12
                y(i) = xi*dh21 + yi*dh22
            end do
         else if (dflag.eq.zero) then 
            dh12 = dparam(4)
            dh21 = dparam(3)
            do i = 1,nsteps,incx
                xi = x(i)
                yi = y(i)
                x(i) = xi + yi*dh12
                y(i) = xi*dh21 + yi
            end do
         else
            dh11 = dparam(2)
            dh22 = dparam(5)
            do i = 1,nsteps,incx
                xi = x(i)
                yi = y(i)
                x(i) = xi*dh11 + yi
                y(i) = -xi + yi*dh22
            end do
         end if
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         
         if(dflag.lt.zero) then
            dh11 = dparam(2)
            dh12 = dparam(4)
            dh21 = dparam(3)
            dh22 = dparam(5)
            do i = 1,n
                xi = x(ix)
                yi = y(iy)
                x(ix) = xi*dh11 + yi*dh12
                y(iy) = xi*dh21 + yi*dh22
                ix = ix + incx
                iy = iy + incy
            end do
         else if (dflag.eq.zero) then 
            dh12 = dparam(4)
            dh21 = dparam(3)
            do i = 1,n
                xi = x(ix)
                yi = y(iy)
                x(ix) = xi + yi*dh12
                y(iy) = xi*dh21 + yi
                ix = ix + incx
                iy = iy + incy
            end do
         else
            dh11 = dparam(2)
            dh22 = dparam(5)
            do i = 1,n
                xi = x(ix)
                yi = y(iy)
                x(iy) = xi*dh11 + yi
                y(iy) = -xi + yi*dh22
                ix = ix + incx
                iy = iy + incy
            end do
         end if
      end if
      return 
      end
