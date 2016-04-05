      subroutine drotmg(dd1,dd2,dx1,dy1,dparam)

      double precision dd1,dd2,dx1,dy1

      double precision dparam(5)

      double precision dflag,dh11,dh12,dh21,dh22,dp1,dp2,dq1,dq2,dtemp,
     $                 du,gam,gamsq,one,rgamsq,two,zero,dp1_2,dp2_2,
     $                 dq1_2,dq2_2,dh11_2,dh12_2,dh21_2,dh22_2,du_2,
     $                 dd1_2,dd2_2,dx1_2

      intrinsic dabs

      common seps,deps

      data zero,one,two/0.d0,1.d0,2.d0/
      data gam,gamsq,rgamsq/4096.d0,16777216.d0,5.9604645d-8/

      if (dd1.lt.zero) then
*        go zero-h-d-and-dx1..
         dflag = -one
         dh11 = zero
         dh12 = zero
         dh21 = zero
         dh22 = zero
*
         dd1 = zero
         dd2 = zero
         dx1 = zero
      else
*        case-dd1-nonnegative
10       dp2 = dd2*dy1
         dp2_2 = dd2*dy1
         if (dabs(dp2-dp2_2).gt.deps) then
            goto 10
         end if

         if (dp2.eq.zero) then
            dflag = -two
            dparam(1) = dflag
            return
         end if 
*        regular-case..
20       dp1 = dd1*dx1
         dq2 = dp2*dy1
         dq1 = dp1*dx1

         dp1_2 = dd1*dx1
         dq2_2 = dp2*dy1
         dq1_2 = dp1*dx1

         if (dabs(dp1-dp1_2).gt.deps) then
               goto 20
         end if
         if (dabs(dq1-dq1_2).gt.deps) then
               goto 20
         end if
         if (dabs(dq2-dq2_2).gt.deps) then
            goto 20
         end if

50       if (dabs(dq1).gt.dabs(dq2)) then
30          dh21 = -dy1/dx1
            dh12 = dp2/dp1
            du = one - dh12*dh21

            dh21_2 = -dy1/dx1
            dh12_2 = dp2/dp1
            du_2 = one - dh12_2*dh21_2

            if (dabs(du-du_2).gt.deps) then
               goto 30
            end if

           if (du.gt.zero) then
             dflag = zero

             dd1_2 = dd1/du
             dd2_2 = dd2/du
             dx1_2 = dx2*du

             dd1 = dd1/du
             dd2 = dd2/du
             dx1 = dx1*du
           end if
         else

            if (dq2.lt.zero) then
*              go zero-h-d-and-dx1..
               dflag = -one
               dh11 = zero
               dh12 = zero
               dh21 = zero
               dh22 = zero
*
               dd1 = zero
               dd2 = zero
               dx1 = zero
            else
40             dflag = one
               dh11 = dp1/dp2
               dh22 = dx1/dy1
               du = one + dh11*dh22

               dh11 = dp1/dp2
               dh22 = dx1/dy1
               du_2 = one + dh11_2*dh22_2

               if (dabs(du-du_2).gt.deps) then
                  goto 40
               end if

               dd1_2 = dd1/du
               dd2_2 = dd2/du
               dx1_2 = dy1*du

               dtemp = dd2/du
               dd2 = dd1/du
               dd1 = dtemp
               dx1 = dy1*du
            end if
         end if

         if (dabs(dd1-dd1_2).gt.deps) then
            goto 50
         end if
         if (dabs(dd2-dd2_2).gt.deps) then
            goto 50
         end if
         
60       dh11_2 = dh11
         dh12_2 = dh12
         dh21_2 = dh21
         dh22_2 = dh22         

*     procedure..scale-check
         if (dd1.ne.zero) then
            do while ((dd1.le.rgamsq) .or. (dd1.ge.gamsq))
               if (dflag.eq.zero) then
                  dh11 = one
                  dh22 = one
                  dh11_2 = one
                  dh22_2 = one
                  dflag = -one
               else
                  dh21 = -one
                  dh12 = one
                  dh21_2 = -one
                  dh12_2 = one
                  dflag = -one
               end if
               if (dd1.le.rgamsq) then
                  dd1 = dd1*gam**2
                  dx1 = dx1/gam
                  dh11 = dh11/gam
                  dh12 = dh12/gam

                  dd1_2 = dd1_2*gam**2
                  dx1_2 = dx1_2/gam
                  dh11_2 = dh11_2/gam
                  dh12_2 = dh12_2/gam
               else
                  dd1 = dd1/gam**2
                  dx1 = dx1*gam
                  dh11 = dh11*gam
                  dh12 = dh12*gam

                  dd1_2 = dd1/gam**2
                  dx1_2 = dx1_2*gam
                  dh11_2 = dh11_2*gam
                  dh12_2 = dh12_2*gam
               end if
            enddo
         end if

         if (dabs(dh11-dh11_2).gt.deps) then
            goto 60
         end if
         if (dabs(dh12-dh12_2).gt.deps) then
            goto 60
         end if
  
70       if (dd2.ne.zero) then
            do while ( (dabs(dd2).le.rgamsq) .or. (dabs(dd2).ge.gamsq) )
               if (dflag.eq.zero) then
                  dh11 = one
                  dh22 = one
                  dflag = -one
               else
                  dh21 = -one
                  dh12 = one
                  dflag = -one
               end if
               if (dabs(dd2).le.rgamsq) then
                  dd2 = dd2*gam**2
                  dh21 = dh21/gam
                  dh22 = dh22/gam

                  dd2_2 = dd2_2*gam**2
                  dh21_2 = dh21_2/gam
                  dh22_2 = dh22_2/gam
               else
                  dd2 = dd2/gam**2
                  dh21 = dh21*gam
                  dh22 = dh22*gam

                  dd2_2 = dd2_2/gam**2
                  dh21_2 = dh21_2*gam
                  dh22_2 = dh22_2*gam
               end if      
            end do
         end if

         if (dabs(dh21-dh21_2).gt.deps) then
            goto 70
         end if
         if (dabs(dh22-dh22_2).gt.deps) then
            goto 70
         end if
     
      end if

      if (dflag.lt.zero) then
         dparam(2) = dh11
         dparam(3) = dh21
         dparam(4) = dh12
         dparam(5) = dh22
      else if (dflag.eq.zero) then
         dparam(3) = dh21
         dparam(4) = dh12 
      else
         dparam(2) = dh11
         dparam(5) = dh22
      end if

      dparam(1) = dflag
      return
      end
      
     
     
     
