      subroutine srotmg(d1,d2,a,b,sparam)

      real d1,d2,a,b

      real sparam(5)

      real gam,gamsq,one,rgamsq,sflag,sh11,sh12,sh21,sh22,sp1,sp2,sq1,
     $     sq2,stemp,su,two,zero
      real sp1_2,sp2_2,sq1_2,sq2_2,sh11_2,sh22_2,sh21_2,sh12_2,su_2,d1_2,
     $     d2_2,a_2

      intrinsic abs

      data zero,one,two/0.e0,1.e0,2.e0/
      data gam,gamsq,rgamsq/4096.e0,1.67772e7,5.96046e-8/

      if (d1.lt.zero) then
*        go zero-h-d-and-a..
         sflag = -one
         sh11 = zero
         sh12 = zero
         sh21 = zero
         sh22 = zero
*
         d1 = zero
         d2 = zero
         a = zero
      else
*        case-d1-nonnegative
10       sp2 = d2*b
         sp2_2 = d2*b
         if (sp2.ne.sp2_2) then
            goto 10
         end if
         if (sp2.eq.zero) then
            sflag = -two
            sparam(1) = sflag
            return
         end if 
*        regular-case..
20       sp1 = d1*a         
         sq2 = sp2*b
         sq1 = sp1*a
         sp1_2 = d1*a
         sq2_2 = sp2_2*b
         sq1_2 = sp1_2*a
         if ((sp1.ne.sp1_2).or.(sq1.ne.sq1_2).or.(sq2.ne.sq2_2)) then
            goto 20
         end if
*
50       if (abs(sq1).gt.abs(sq2)) then
30          sh21 = -b/a
            sh12 = sp2/sp1
            su = one - sh12*sh21

            sh21_2 = -b/a
            sh12_2 = sp2/sp1
            su_2 = one - sh12_2*sh21_2

           if (su.ne.su_2) then
              goto 30
           end if
           if (su.gt.zero) then
             sflag = zero

             d1_2 = d1/su
             d2_2 = d2/su
             a_2 = a*su

             d1 = d1/su
             d2 = d2/su
             a = a*su
           end if
         else

            if (sq2.lt.zero) then
*              go zero-h-d-and-a..
               sflag = -one
               sh11 = zero
               sh12 = zero
               sh21 = zero
               sh22 = zero
*
               d1 = zero
               d2 = zero
               a = zero
            else
40             sflag = one
               sh11 = sp1/sp2
               sh22 = a/b
               su = one + sh11*sh22

               sh11_2 = sp1/sp2
               sh22_2 = a/b
               su_2 = one + sh11_2*sh22_2

               if (su.ne.su_2) then
                  goto 40
               end if
               
               d1_2 = d2/su
               d2_2 = d1/su
               a_2 = b*su

               stemp = d2/su
               d2 = d1/su
               d1 = stemp
               a = b*su
            end if
         end if

         if ((d1.ne.d1_2).or.(d2.ne.d2_2)) then
            goto 50
         end if

60       sh11_2 = sh11
         sh12_2 = sh12
         sh21_2 = sh21
         sh22_2 = sh22
*     procesure..scale-check
         if (d1.ne.zero) then
            do while ((d1.le.rgamsq) .or. (d1.ge.gamsq))
               if (sflag.eq.zero) then
                  sh11 = one
                  sh22 = one
                  sh11_2 = one
                  sh22_2 = one
                  sflag = -one
               else
                  sh21 = -one
                  sh12 = one
                  sh21_2 = -one
                  sh12_2 = one
                  sflag = -one
               end if
               if (d1.le.rgamsq) then
                  d1 = d1*gam**2
                  a = a/gam
                  sh11 = sh11/gam
                  sh12 = sh12/gam

                  d1_2 = d1_2*gam**2
                  a_2 = a_2/gam
                  sh11_2 = sh11_2/gam
                  sh12_2 = sh12_2/gam
               else
                  d1 = d1/gam**2
                  a = a*gam
                  sh11 = sh11*gam
                  sh12 = sh12*gam

                  d1_2 = d1_2/gam**2
                  a_2 = a_2*gam
                  sh11_2 = sh11_2*gam
                  sh12_2 = sh12_2*gam
               end if
            enddo
         end if

         if ((sh11.ne.sh11_2).or.(sh12.ne.sh12_2)) then
            goto 60
         end if
  
70       if (d2.ne.zero) then
            do while ( (abs(d2).le.rgamsq) .or. (abs(d2).ge.gamsq) )
               if (sflag.eq.zero) then
                  sh11 = one
                  sh22 = one
                  sflag = -one
               else
                  sh21 = -one
                  sh12 = one
                  sflag = -one
               end if
               if (abs(d2).le.rgamsq) then
                  d2 = d2*gam**2
                  sh21 = sh21/gam
                  sh22 = sh22/gam

                  d2_2 = d2_2*gam**2
                  sh21_2 = sh21_2/gam
                  sh22_2 = sh22_2/gam
               else
                  d2 = d2/gam**2
                  sh21 = sh21*gam
                  sh22 = sh22*gam

                  d2_2 = d2_2/gam**2
                  sh21_2 = sh21_2*gam
                  sh22_2 = sh22_2*gam
               end if      
            end do
         end if

         if ((sh21.ne.sh21_2).or.(sh22.ne.sh22_2)) then
            goto 70
         end if
     
      end if

      if (sflag.lt.zero) then
         sparam(2) = sh11
         sparam(3) = sh21
         sparam(4) = sh12
         sparam(5) = sh22
      else if (sflag.eq.zero) then
         sparam(3) = sh21
         sparam(4) = sh12 
      else
         sparam(2) = sh11
         sparam(5) = sh22
      end if

      sparam(1) = sflag
      return
      end

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
      
     
     
     
