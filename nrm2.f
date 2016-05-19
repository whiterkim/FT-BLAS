      ! function: snrm2
      ! S: Real version
      real function xsnrm2(n,x,incx)

      integer incx,n
      real x(*)

      real xi,a1,a2
      integer i,ix

      intrinsic abs,sqrt

      common seps,deps
100   a1 = 0.0e0
      a2 = 0.0e0
      xsnrm2 = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         do i = 1,n
            xi = x(i)
            a1 = a1 + xi*xi;
            a2 = a2 + xi*xi;
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)
            a1 = a1 + xi*xi;
            a2 = a2 + xi*xi;
            ix = ix + incx
         end do
      end if
      a1 = sqrt(a1)
      a2 = sqrt(a2)
      if (abs(a1 - a2).ge.seps) then
         goto 100
      end if
      xsnrm2 = a1
      return
      end

      ! function: dnrm2 
      ! D: Double precision version 
      double precision function xdnrm2(n,x,incx)
            
      integer incx,n
      double precision x(*)
      
      double precision one,zero
      parameter(one=1.0d+0,zero=0.0d+0)

      double precision scle,ssq1,ssq2,temp
      double precision xi,a1,a2
      integer i,ix      
      
      intrinsic abs,sqrt
            
      common seps,deps
110   a1 = 0.0d0
      a2 = 0.0d0
      xdrnm2 = 0.0d0
      if (n.lt.1 .or. incx.lt.1) then
         norm = zero
      else if (n.eq.1) then
         norm = abs(x(1))
      else
         scle = zero
         ssq1 = one
         ssq2 = one
         do ix = 1,1 + (n-1)*incx,incx
            if (x(ix).ne.zero) THEN
               temp = abs(x(ix))
               if (scle.lt.temp) then
                  ssq1 = one + ssq1* (scle/temp)**2
                  ssq2 = one + ssq2* (scle/temp)**2
                  scle = temp
               else
                  ssq1 = ssq1 + (temp/scle)**2
                  ssq2 = ssq2 + (temp/scle)**2
               end if
            end if
         end do
         a1 = scle*sqrt(ssq1)
         a2 = scle*sqrt(ssq2)
      end if
      
      ! Recalculate if not equal
      if (abs(a1 - a2).ge.deps) then
         goto 110
      end if

      xdnrm2 = a1
      return
      end            


      ! function: scnrm2
      ! SC: Single precision Complex to Real version
      real function xscnrm2(n,x,incx)

      integer incx,n
      complex*8 x(*)
      
      real one,zero
      parameter(one=1.0e+0,zero=0.0e+0)

      real scle,ssq1,ssq2,temp
      complex*8 xi
      real a1,a2
      integer i,ix      
      
      intrinsic abs,sqrt,aimag,REAL
            
      common seps,deps
120   a1 = zero
      a2 = zero
      xscnrm2 = zero

      if (n.lt.1 .or. incx.lt.1) then
         a1 = zero
         a2 = zero
         xscnrm2 = a1
         return
      else
         scle = 0.0e0+0
         ssq1 = one
         ssq2 = one
         do ix = 1,1 + (n-1)*incx,incx
            if (REAL(x(ix)).ne.zero) then
               temp = abs(REAL(x(ix)))
               if (scle.lt.temp) then
                  ssq1 = one + ssq1* (scle/temp)**2
                  ssq2 = one + ssq2* (scle/temp)**2
                  scle = temp
               else
                  ssq1 = ssq1 + (temp/scle)**2
                  ssq2 = ssq2 + (temp/scle)**2
               end if
            end if
            if (aimag(x(ix)).ne.zero) then
               temp = abs(aimag(x(ix)))
               if (scle.lt.temp) then
                  ssq1 = one + ssq1* (scle/temp)**2
                  ssq2 = one + ssq2* (scle/temp)**2
                  scle = temp
               else
                  ssq1 = ssq1 + (temp/scle)**2
                  ssq2 = ssq2 + (temp/scle)**2
               end if
            end if
         end do
         a1 = scle*sqrt(ssq1)
         a2 = scle*sqrt(ssq2)
      end if
      
      ! Recalculate if not equal
      if (abs(a1 - a2).ge.seps) then
         goto 120
      end if

      xscnrm2 = a1
      return
      end

      
      ! function: dznrm2
      ! DZ: Double precision Complex to Double version
      double precision function xdznrm2(n,x,incx)

      integer incx,n
      complex*16 x(*)
      
      double precision one,zero
      parameter(one=1.0d+0,zero=0.0d+0)

      double precision a1,a2,scle,ssq1,ssq2,temp
      integer ix      
      
      intrinsic abs,sqrt,dble,dimag
            
      common seps,deps
130   a1 = 0.0d0
      a2 = 0.0d0
      
      if (n.lt.1 .or. incx.lt.1) then
         a1 = zero
         a2 = zero
      else
         scle = zero
         ssq1 = one
         ssq2 = one
   
         do ix = 1,1 + (n-1)*incx,incx
            if (dble(x(ix)).ne.zero) then
               temp = abs(dble(x(ix)))
               if (scle.lt.temp) then
                  ssq1 = one + ssq1* (scle/temp)**2
                  ssq2 = one + ssq2* (scle/temp)**2
                  scle = temp
               else
                  ssq1 = ssq1 + (temp/scle)**2
                  ssq2 = ssq2 + (temp/scle)**2
               end if
            end if
            if (dimag(x(ix)).ne.zero) then
               temp = abs(dimag(x(ix)))
               if (scle.lt.temp) then
                  ssq1 = one + ssq1* (scle/temp)**2
                  ssq2 = one + ssq2* (scle/temp)**2
                  scle = temp
               else
                  ssq1 = ssq1 + (temp/scle)**2
                  ssq2 = ssq2 + (temp/scle)**2
               end if
            end if
         end do
         a1 = scle*sqrt(ssq1)
         a2 = scle*sqrt(ssq2)
      end if
      
      ! Recalculate if not equal
      if (abs(a1 - a2).ge.deps) then
         goto 130
      end if

      xdznrm2 = a1
      return
      end

