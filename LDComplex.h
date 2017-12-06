// @(#)root/mathcore:$Id$
// Author: Federico Carminati   22/04/2004

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

#ifndef ROOT_LDComplex
#define ROOT_LDComplex

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// LDComplex                                                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// --- modified by Ron Belmont to use long double instead of Double_t, 06 Dec 2017

#ifndef ROOT_TMath
#include "TMath.h"
#endif

#include "Rtypes.h"


class LDComplex {

protected:
   long double fRe;    // real part
   long double fIm;    // imaginary part

public:
   // ctors and dtors
   //LDComplex(): fRe(0), fIm(0) {}
   LDComplex() { fRe=0; fIm=0; }
   LDComplex(long double re) { LDComplex(re,0,false); }
   LDComplex(long double re, long double im) { LDComplex(re,im,false); }
   LDComplex(long double re, long double im, Bool_t polar);
   virtual ~LDComplex();

   // constants
   static LDComplex I() {return LDComplex(0,1);}
   static LDComplex One() {return LDComplex(1,0);}

   // getters and setters
   long double Re() const {return fRe;}
   long double Im() const {return fIm;}
   long double Rho() const {return sqrt(fRe*fRe+fIm*fIm);}
   long double Rho2() const {return fRe*fRe+fIm*fIm;}
   long double Theta() const {return (fIm||fRe)?atan2(fIm,fRe):0;}
   LDComplex operator()(long double x, long double y)
      { fRe = x; fIm = y; return *this; }
   LDComplex operator()(long double x, long double y, Bool_t polar)
      { if (polar) { fRe = x*cos(y); fIm = x*sin(y); }
        else { fRe = x; fIm = y; } return *this; }

   // Simple operators complex - complex
   LDComplex operator *(const LDComplex & c) const
      {return LDComplex(fRe*c.fRe-fIm*c.fIm,fRe*c.fIm+fIm*c.fRe);}
   LDComplex operator +(const LDComplex & c) const
      {return LDComplex(fRe+c.fRe, fIm+c.fIm);}
   LDComplex operator /(const LDComplex & c) const
      {return LDComplex(fRe*c.fRe+fIm*c.fIm,-fRe*c.fIm+fIm*c.fRe)/c.Rho2();}
   LDComplex operator -(const LDComplex & c) const
      {return LDComplex(fRe-c.fRe, fIm-c.fIm);}

   LDComplex operator *=(const LDComplex & c)
      {return ((*this) = (*this) * c);}
   LDComplex operator +=(const LDComplex & c)
      {return ((*this) = (*this) + c);}
   LDComplex operator /=(const LDComplex & c)
      {return ((*this) = (*this) / c);}
   LDComplex operator -=(const LDComplex & c)
      {return ((*this) = (*this) - c);}

   LDComplex operator -()
      {return LDComplex(-fRe,-fIm);}
   LDComplex operator +()
      {return *this;}

   // Simple operators complex - double
   LDComplex operator *(long double c) const
      {return LDComplex(fRe*c,fIm*c);}
   LDComplex operator +(long double c) const
      {return LDComplex(fRe+c, fIm);}
   LDComplex operator /(long double c) const
      {return LDComplex(fRe/c,fIm/c);}
   LDComplex operator -(long double c) const
      {return LDComplex(fRe-c, fIm);}

   // Simple operators double - complex
   friend LDComplex operator *(long double d, const LDComplex & c)
      {return LDComplex(d*c.fRe,d*c.fIm);}
   friend LDComplex operator +(long double d, const LDComplex & c)
      {return LDComplex(d+c.fRe, c.fIm);}
   friend LDComplex operator /(long double d, const LDComplex & c)
      {return LDComplex(d*c.fRe,-d*c.fIm)/c.Rho2();}
   friend LDComplex operator -(long double d, const LDComplex & c)
      {return LDComplex(d-c.fRe, -c.fIm);}

   // Convertors
   operator long double () const {return fRe;}
   operator float  () const {return static_cast<float>(fRe);}
   operator int    () const {return static_cast<int>(fRe);}

   //  extensions
   static LDComplex sqrt(const LDComplex &c)
      {return LDComplex(sqrt(c.Rho()),0.5*c.Theta(),kTRUE);}

   static LDComplex exp(const LDComplex &c)
      {return LDComplex(exp(c.fRe),c.fIm,kTRUE);}
   //static LDComplex log(const LDComplex &c)
   //   {return LDComplex(0.5*log(c.Rho2()),c.Theta());}
   //static LDComplex log2(const LDComplex &c)
   //   {return log(c)/log(2);}
   //static LDComplex log10(const LDComplex &c)
   //   {return log(c)/log(10);}

   //static LDComplex sin(const LDComplex &c)
   //   {return LDComplex(sin(c.fRe)*cosh(c.fIm),
   //                    cos(c.fRe)*sinh(c.fIm));}
   //static LDComplex cos(const LDComplex &c)
   //   {return LDComplex(cos(c.fRe)*cosh(c.fIm),
   //                    -sin(c.fRe)*sinh(c.fIm));}
   //static LDComplex tan(const LDComplex &c)
   //   {LDComplex cc=cos(c); return sin(c)*Conjugate(cc)/cc.Rho2();}

   //static LDComplex asin(const LDComplex &c)
   //   {return -I()*log(I()*c+TMath::Sign(1.,c.Im())*sqrt(1.-c*c));}
   //static LDComplex acos(const LDComplex &c)
   //   {return -I()*log(c+TMath::Sign(1.,c.Im())*sqrt(c*c-1.));}
   //static LDComplex atan(const LDComplex &c)
   //   {return -0.5*I()*log((1.+I()*c)/(1.-I()*c));}

   //static LDComplex sinh(const LDComplex &c)
   //   {return LDComplex(sinh(c.fRe)*cos(c.fIm),
   //                    cosh(c.fRe)*sin(c.fIm));}
   //static LDComplex cosh(const LDComplex &c)
   //   {return LDComplex(cosh(c.fRe)*cos(c.fIm),
   //                    sinh(c.fRe)*sin(c.fIm));}
   //static LDComplex tanh(const LDComplex &c)
   //   {LDComplex cc=cosh(c); return sinh(c)*Conjugate(cc)/cc.Rho2();}

   //static LDComplex asinh(const LDComplex &c)
   //   {return log(c+TMath::Sign(1.,c.Im())*sqrt(c*c+1.));}
   //static LDComplex acosh(const LDComplex &c)
   //   {return log(c+TMath::Sign(1.,c.Im())*sqrt(c*c-1.));}
   //static LDComplex atanh(const LDComplex &c)
   //   {return 0.5*log((1.+c)/(1.-c));}

   static long double fabs(const LDComplex &c)
      {return c.Rho();}

   //static LDComplex pow(const LDComplex& x, const LDComplex& y)
   //   {long double lrho=log(x.Rho());
   //    long double theta=x.Theta();
   //    return LDComplex(exp(lrho*y.Re()-theta*y.Im()),
   //                    lrho*y.Im()+theta*y.Re(),kTRUE);}
   //static LDComplex pow(const LDComplex& x, long double y)
   //   {return LDComplex(pow(x.Rho(),y),x.Theta()*y,kTRUE);}
   //static LDComplex pow(long double x, const LDComplex& y)
   //   {long double lrho=log(fabs(x));
   //    long double theta=(x>0)?0:Pi();
   //    return LDComplex(exp(lrho*y.Re()-theta*y.Im()),
   //                    lrho*y.Im()+theta*y.Re(),kTRUE);}
   //static LDComplex pow(const LDComplex& x, int y)
   //   {return LDComplex(pow(x.Rho(),y),x.Theta()*y,kTRUE);}

   //static int isfinite(const LDComplex& c)
   //   {return Min(isfinite(c.Re()),isfinite(c.Im()));}
   //static int isnan(const LDComplex& c)
   //   {return Max(isnan(c.Re()),isnan(c.Im()));}

   static LDComplex Min(const LDComplex &a, const LDComplex &b)
      {return a.Rho()<=b.Rho()?a:b;}
   static LDComplex Max(const LDComplex &a, const LDComplex &b)
      {return a.Rho()>=b.Rho()?a:b;}
   static LDComplex Normalize(const LDComplex &c)
      {return LDComplex(1.,c.Theta(),kTRUE);}
   static LDComplex Conjugate(const LDComplex &c)
      {return LDComplex(c.Re(),-c.Im());}
   static LDComplex Range(const LDComplex &lb, const LDComplex &ub, const LDComplex &c)
     {return Max(lb,Min(c,ub));}

   // I/O
   friend std::ostream& operator<<(std::ostream& out, const LDComplex& c);
   friend std::istream& operator>>(std::istream& in, LDComplex& c);

   //ClassDef(LDComplex,1)  //Complex Class
};

#endif
