      
      subroutine srotg(sa,sb,c,s)

      real c,s,sa,sb

      real r1,r2,c1,c2,s1,s2,z1,z2,roe,scale

      intrinsic abs,sign,sqrt

      common seps,deps
100   roe = sb
      if (abs(sa).gt.abs(sb)) roe = sa
      scale = abs(sa) + abs(sb)
      if (scale.eq.0.0) then
         c = 1.0
         s = 0.0
         sa = 0.0
         sb = 0.0
         return
      else
         r1 = scale*sqrt((sa/scale)**2+ (sb/scale)**2)
         r2 = scale*sqrt((sa/scale)**2+ (sb/scale)**2)
         r1 = sign(1.0,roe)*r1
         r2 = sign(1.0,roe)*r2
         c1 = sa/r1
         c2 = sa/r2
         s1 = sb/r1
         s2 = sb/r2
         z1 = 1.0
         z2 = 1.0
         if (abs(sa).gt.abs(sb)) then 
            z1 = s1
            z2 = s2
         end if
         if (abs(sb).ge.abs(sa) .and. c.ne.0.0) then
            z1 = 1.0/c1
            z2 = 1.0/c2
         end if
      end if
      if (abs(r1 - r2).ge.seps) goto 100
      if (abs(c1 - c2).ge.seps) goto 100
      if (abs(s1 - s2).ge.seps) goto 100
      if (abs(z1 - z2).ge.seps) goto 100
      
      sa = r1
      sb = z1
      c = c1
      s = s1
      return
      end

      subroutine drotg(sa,sb,c,s)

      double precision c,s,sa,sb

      double precision r1,r2,c1,c2,s1,s2,z1,z2,roe,scale

      intrinsic dabs,dsign,dsqrt

      common seps,deps
200   roe = sb
      if (dabs(sa).gt.dabs(sb)) roe = sa
      scale = dabs(sa) + dabs(sb)
      if (scale.eq.0.0d0) then
         c = 1.0d0
         s = 0.0d0
         sa = 0.0d0
         sb = 0.0d0
         return
      else
         r1 = scale*dsqrt((sa/scale)**2+ (sb/scale)**2)
         r2 = scale*dsqrt((sa/scale)**2+ (sb/scale)**2)
         r1 = dsign(1.0d0,roe)*r1
         r2 = dsign(1.0d0,roe)*r2
         c1 = sa/r1
         c2 = sa/r2
         s1 = sb/r1
         s2 = sb/r2
         z1 = 1.0d0
         z2 = 1.0d0
         if (dabs(sa).gt.dabs(sb)) then 
            z1 = s1
            z2 = s2
         end if
         if (dabs(sb).ge.dabs(sa) .and. c.ne.0.0) then
            z1 = 1.0d0/c1
            z2 = 1.0d0/c2
         end if
      end if
      if (dabs(r1 - r2).ge.seps) goto 200
      if (dabs(c1 - c2).ge.seps) goto 200
      if (dabs(s1 - s2).ge.seps) goto 200
      if (dabs(z1 - z2).ge.seps) goto 200
      
      sa = r1
      sb = z1
      c = c1
      s = s1
      return
      end