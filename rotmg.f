      subroutine xsrotmg(d1,d2,a,b,sparam)

      real d1,d2,a,b

      real sparam(5)

      real gam,gamsq,one,rgamsq,sflag,sh11,sh12,sh21,sh22,sp1,sp2,sq1,
     $     sq2,stemp,su,two,zero
      real sp1_2,sp2_2,sq1_2,sq2_2,sh11_2,sh22_2,sh21_2,sh12_2,su_2,
     $     d1_2, d2_2,a_2

      intrinsic abs
      common seps,deps

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
         if (abs(sp2 - sp2_2).ge.seps) then
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
         if ((abs(sp1 - sp1_2).ge.seps).or.
     $       (abs(sq1 - sq1_2).ge.seps).or.
     $       (abs(sq2 - sq2_2).ge.seps)) then
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

           if (abs(su - su_2).ge.seps) then
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
               d1_2 = zero
               d2_2 = zero

               a = zero
               a_2 = zero
            else
40             sflag = one
               sh11 = sp1/sp2
               sh22 = a/b
               su = one + sh11*sh22

               sh11_2 = sp1/sp2
               sh22_2 = a/b
               su_2 = one + sh11_2*sh22_2

               if (abs(su - su_2).ge.seps) then
                  goto 40
               end if
               
               stemp = d2/su
               d2_2 = d1/su
               d1_2 = stemp 
               a_2 = b*su

               stemp = d2/su
               d2 = d1/su
               d1 = stemp
               a = b*su
            end if
         end if

         if ((abs(d1 - d1_2).ge.seps).or.(abs(d2 - d2_2).ge.seps)) then
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

         if ((abs(sh11 - sh11_2).ge.seps).or.
     $       (abs(sh12 - sh12_2).ge.seps)) then
            goto 60
         end if
  
70       if (d2.ne.zero) then
            do while ( (abs(d2).le.rgamsq) .or. (abs(d2).ge.gamsq) )
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

         if ((abs(sh21 - sh21_2).ge.seps).or.
     $       (abs(sh22 - sh22_2).ge.seps)) then
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

      subroutine xdrotmg(d1,d2,a,b,sparam)

      double precision d1,d2,a,b

      double precision sparam(5)

      double precision gam,gamsq,one,rgamsq,sflag,sh11,sh12,sh21,sh22,
     $                 sp1,sp2,sq1,sq2,stemp,su,two,zero
      double precision sp1_2,sp2_2,sq1_2,sq2_2,sh11_2,sh22_2,sh21_2,
     $                 sh12_2,su_2,d1_2, d2_2,a_2

      intrinsic abs
      common seps,deps

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
         if (abs(sp2 - sp2_2).ge.deps) then
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
         if ((abs(sp1 - sp1_2).ge.deps).or.
     $       (abs(sq1 - sq1_2).ge.deps).or.
     $       (abs(sq2 - sq2_2).ge.deps)) then
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

           if (abs(su - su_2).ge.deps) then
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
               d1_2 = zero
               d2_2 = zero

               a = zero
               a_2 = zero
            else
40             sflag = one
               sh11 = sp1/sp2
               sh22 = a/b
               su = one + sh11*sh22

               sh11_2 = sp1/sp2
               sh22_2 = a/b
               su_2 = one + sh11_2*sh22_2

               if (abs(su - su_2).ge.deps) then
                  goto 40
               end if
               
               stemp = d2/su
               d2_2 = d1/su
               d1_2 = stemp 
               a_2 = b*su

               stemp = d2/su
               d2 = d1/su
               d1 = stemp
               a = b*su
            end if
         end if

         if ((abs(d1 - d1_2).ge.deps).or.(abs(d2 - d2_2).ge.deps)) then
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

         if ((abs(sh11 - sh11_2).ge.deps).or.
     $       (abs(sh12 - sh12_2).ge.deps)) then
            goto 60
         end if
  
70       if (d2.ne.zero) then
            do while ( (abs(d2).le.rgamsq) .or. (abs(d2).ge.gamsq) )
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

         if ((abs(sh21 - sh21_2).ge.deps).or.
     $       (abs(sh22 - sh22_2).ge.deps)) then
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
