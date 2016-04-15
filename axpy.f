
      subroutine xsaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      real x(*),y(*),alpha
      
      ! Temporaries
      real y_t1(n), y_t2(n), yi_1, yi_2

      real xi,yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            
            yi_1 = xi * alpha + yi;
            yi_2 = xi * alpha + yi;
            y_t1(i) = yi_1;
            y_t2(i) = yi_2;
           
           ! yn = yn + yi;
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            
            yi_1 = xi * alpha + yi;
            yi_2 = xi * alpha + yi;
            y_t1(iy) = yi_1;
            y_t2(iy) = yi_2;
            
           ! yn = yn + yi;
            ix = ix + incx
            iy = iy + incy
         end do
      end if
!      if (abs(y(n + 1) + alpha*x(n + 1) - yn).ge.seps) then
!         print *, "Error occurs in saxpy"
!      end if
!     y(n + 1) = yn
      do i = 1,n
        if (abs(y_t1(i) - y_t2(i)).ge.seps) goto 100
      end do
      
      do i = 1,n
        y(i) = y_t1(i)
      end do
      
      return
      end
      
      
       subroutine xdaxpy(n,alpha,x,incx,y,incy)

      integer incx,incy,n
      double precision x(*),y(*),alpha
      
      ! Temporaries
      double precision y_t1(n), y_t2(n), yi_1, yi_2

      double precision xi,yn
      integer i,ix,iy

      intrinsic abs

      common seps,deps
100   yn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1 .and. incy.eq.1) then
         do i = 1,n
            xi = x(i)
            yi = y(i)
            
            yi_1 = xi * alpha + yi;
            yi_2 = xi * alpha + yi;
            y_t1(i) = yi_1;
            y_t2(i) = yi_2;
           
           ! yn = yn + yi;
         end do
      else
         ix = 1
         iy = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         if (incy.lt.0) iy = (-n+1)*incy + 1
         do i = 1,n
            xi = x(ix)
            yi = y(iy)
            
            yi_1 = xi * alpha + yi;
            yi_2 = xi * alpha + yi;
            y_t1(iy) = yi_1;
            y_t2(iy) = yi_2;
            
           ! yn = yn + yi;
            ix = ix + incx
            iy = iy + incy
         end do
      end if
!      if (abs(y(n + 1) + alpha*x(n + 1) - yn).ge.seps) then
!         print *, "Error occurs in saxpy"
!      end if
!     y(n + 1) = yn
      do i = 1,n
        if (abs(y_t1(i) - y_t2(i)).ge.deps) goto 100
      end do
      
      do i = 1,n
        y(i) = y_t1(i)
      end do
   
      return
      end
