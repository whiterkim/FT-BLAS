      
      subroutine xsrotm(n,x,incx,y,incy,sparam)

      real sparam(5)
      integer incx,incy,n

      real x(*),y(*)

      real sflag, sh11, sh12, sh21, sh22, two, xi, yi, zero
      real x1, x2, y1, y2
      integer i,ix,iy, nsteps
      
      data zero, two/0.e0,2.e0/
    
      common seps, deps

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
100            xi = x(i)
               yi = y(i)

               x1 = xi*sh11 + yi*sh12
               x2 = xi*sh11 + yi*sh12
               y1 = xi*sh21 + yi*sh22
               y2 = xi*sh21 + yi*sh22

               if(abs((x1 + y1) - (x2 + y2)).ge.seps) then
                  goto 100
               else
                  x(i) = x1
                  y(i) = y1
               end if 
            end do
         else if (sflag.eq.zero) then 
            sh12 = sparam(4)
            sh21 = sparam(3)
            do i = 1,nsteps,incx
200            xi = x(i)
               yi = y(i)

               x1 = xi + yi*sh12
               x2 = xi + yi*sh12
               y1 = xi*sh21 + yi
               y2 = xi*sh21 + yi

               if(abs((x1 + y1) - (x2 + y2)).ge.seps) then
                  goto 200
               else
                  x(i) = x1
                  y(i) = y1
               end if 
            end do
         else
            sh11 = sparam(2)
            sh22 = sparam(5)
            do i = 1,nsteps,incx
300            xi = x(i)
               yi = y(i)

               x1 = xi*sh11 + yi
               x2 = xi*sh11 + yi
               y1 = -xi + yi*sh22
               y2 = -xi + yi*sh22

               if(abs((x1 + y1) - (x2 + y2)).ge.seps) then
                  goto 300
               else
                  x(i) = x1
                  y(i) = y1
               end if 
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
400            xi = x(ix)
               yi = y(iy)

               x1 = xi*sh11 + yi*sh12
               x2 = xi*sh11 + yi*sh12
               y1 = xi*sh21 + yi*sh22
               y2 = xi*sh21 + yi*sh22

               if(abs(x1 - x2).ge.seps .or. abs(y1 - y2).ge.seps) then
                  goto 400
               else
                  x(ix) = x1
                  y(iy) = y1
               end if 

               ix = ix + incx
               iy = iy + incy
            end do
         else if (sflag.eq.zero) then 
            sh12 = sparam(4)
            sh21 = sparam(3)
            do i = 1,n
500            xi = x(ix)
               yi = y(iy)

               x1 = xi + yi*sh12
               x2 = xi + yi*sh12
               y1 = xi*sh21 + yi
               y2 = xi*sh21 + yi

               if(abs(x1 - x2).ge.seps .or. abs(y1 - y2).ge.seps) then
                  goto 500
               else
                  x(ix) = x1
                  y(iy) = y1
               end if 

               ix = ix + incx
               iy = iy + incy
            end do
         else
            sh11 = sparam(2)
            sh22 = sparam(5)
            do i = 1,n
600            xi = x(ix)
               yi = y(iy)

               x1 = xi*sh11 + yi
               x2 = xi*sh11 + yi
               y1 = -xi + yi*sh22
               y2 = -xi + yi*sh22

               if(abs(x1 - x2).ge.seps .or. abs(y1 - y2).ge.seps) then
                  goto 600
               else
                  x(ix) = x1
                  y(iy) = y1
               end if 

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
      double precision x1, x2, y1, y2
      integer i,ix,iy, nsteps
      
      data zero, two/0.d0,2.d0/
    
      common seps, deps

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
100            xi = x(i)
               yi = y(i)

               x1 = xi*dh11 + yi*dh12
               x2 = xi*dh11 + yi*dh12
               y1 = xi*dh21 + yi*dh22
               y2 = xi*dh21 + yi*dh22

               if(abs((x1 + y1) - (x2 + y2)).ge.deps) then
                  goto 100
               else
                  x(i) = x1
                  y(i) = y1
               end if 
            end do
         else if (dflag.eq.zero) then 
            dh12 = dparam(4)
            dh21 = dparam(3)
            do i = 1,nsteps,incx
200            xi = x(i)
               yi = y(i)

               x1 = xi + yi*dh12
               x2 = xi + yi*dh12
               y1 = xi*dh21 + yi
               y2 = xi*dh21 + yi

               if(abs((x1 + y1) - (x2 + y2)).ge.deps) then
                  goto 200
               else
                  x(i) = x1
                  y(i) = y1
               end if 
            end do
         else
            dh11 = dparam(2)
            dh22 = dparam(5)
            do i = 1,nsteps,incx
300            xi = x(i)
               yi = y(i)

               x1 = xi*dh11 + yi
               x2 = xi*dh11 + yi
               y1 = -xi + yi*dh22
               y2 = -xi + yi*dh22

               if(abs((x1 + y1) - (x2 + y2)).ge.deps) then
                  goto 300
               else
                  x(i) = x1
                  y(i) = y1
               end if 
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
400            xi = x(ix)
               yi = y(iy)

               x1 = xi*dh11 + yi*dh12
               x2 = xi*dh11 + yi*dh12
               y1 = xi*dh21 + yi*dh22
               y2 = xi*dh21 + yi*dh22

               if(abs(x1 - x2).ge.deps .or. abs(y1 - y2).ge.deps) then
                  goto 400
               else
                  x(ix) = x1
                  y(iy) = y1
               end if 

               ix = ix + incx
               iy = iy + incy
            end do
         else if (dflag.eq.zero) then 
            dh12 = dparam(4)
            dh21 = dparam(3)
            do i = 1,n
500            xi = x(ix)
               yi = y(iy)

               x1 = xi + yi*dh12
               x2 = xi + yi*dh12
               y1 = xi*dh21 + yi
               y2 = xi*dh21 + yi

               if(abs(x1 - x2).ge.deps .or. abs(y1 - y2).ge.deps) then
                  goto 500
               else
                  x(ix) = x1
                  y(iy) = y1
               end if 

               ix = ix + incx
               iy = iy + incy
            end do
         else
            dh11 = dparam(2)
            dh22 = dparam(5)
            do i = 1,n
600            xi = x(ix)
               yi = y(iy)

               x1 = xi*dh11 + yi
               x2 = xi*dh11 + yi
               y1 = -xi + yi*dh22
               y2 = -xi + yi*dh22

               if(abs(x1 - x2).ge.deps .or. abs(y1 - y2).ge.deps) then
                  goto 600
               else
                  x(ix) = x1
                  y(iy) = y1
               end if 

               ix = ix + incx
               iy = iy + incy
            end do
         end if
      end if
      return
      end
         
               
