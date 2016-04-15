
      subroutine xsscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      real x(*),alpha

        ! Temporaries      
      real x_t1(n), x_t2(n), xi_1, xi_2

      real xn
      integer i,ix

      intrinsic abs

      common seps,deps
100   xn = 0.0e0
      if (n.le.0) return
      if (incx.eq.1) then
         do i = 1,n
            xi = x(i)
            
!            x(i) = xi * alpha;
            xi_1 = xi * alpha;
            xi_2 = xi * alpha;
            x_t1(i) = xi_1;
            x_t2(i) = xi_2;
           ! xn = xn + xi;
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(i)
            
!            x(i) = xi * alpha;
            xi_1 = xi * alpha;
            xi_2 = xi * alpha;
            x_t1(i) = xi_1;
            x_t2(i) = xi_2;
           ! xn = xn + xi;
            ix = ix + incx
         end do
      end if
*     if (abs(x(n + 1)*alpha - xn).ge.seps) then
*       print *, "Error occurs in sscal"
*     end if
*     x(n + 1) = xn


        ! Recalculation check
      do i = 1,n
       if (abs(x_t1(i) - x_t2(i)).ge.seps) goto 100
      end do
      
      do i = 1,n
       x(i) = x_t1(i)
      end do
      
      return
      end




      subroutine xdscal(n,alpha,x,incx)
      ! n: Specifes the number of elements in vector x
      ! a: Specifies the scalar a.
      ! x: Array
      ! incx: specifies the increment for he elements of x

      integer incx,n
      double precision x(*),alpha
      
       ! Temporaries
      double precision x_t1(n), x_t2(n), xi_1, xi_2
      
      double precision xi,xn
      integer i,ix

      intrinsic abs

      common seps,deps
200   xn = 0.0d0
      if (n.le.0) return
      if (incx.eq.1) then
         do i = 1,n
            xi = x(i)

!            x(i) = xi * alpha;
            xi_1 = xi * alpha;
            xi_2 = xi * alpha;
            x_t1(i) = xi_1;
            x_t2(i) = xi_2;
           ! xn = xn + xi;
         end do
      else
         ix = 1
         if (incx.lt.0) ix = (-n+1)*incx + 1
         do i = 1,n
            xi = x(ix)

!            x(i) = xi * alpha;
            xi_1 = xi * alpha;
            xi_2 = xi * alpha;
            x_t1(i) = xi_1;
            x_t2(i) = xi_2;
           ! xn = xn + xi;
            ix = ix + incx
         end do
      end if
*      if (abs(x(n + 1)*alpha - xn).ge.deps) then
*        print *, "Error occurs in dscal"
*      end if
*      x(n + 1) = xn
  
        ! Recalculation check
      do i = 1,n
        if (dabs(x_t1(i) - x_t2(i)).ge.deps) goto 200
      end do
      
      do i = 1,n
        x(i) = x_t1(i)
      end do
      
      return
      end
