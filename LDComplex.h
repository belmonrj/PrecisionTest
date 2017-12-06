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

#ifndef ROOT_TMath
#include "TMath.h"
#endif

#include "Rtypes.h"


class LDComplex {

protected:
   Double_t fRe;    // real part
   Double_t fIm;    // imaginary part

public:
   // ctors and dtors
   LDComplex(): fRe(0), fIm(0) {}
   LDComplex(Double_t re, Double_t im=0, Bool_t polar=kFALSE);
   virtual ~LDComplex() {}

   // constants
   static LDComplex I() {return LDComplex(0,1);}
   static LDComplex One() {return LDComplex(1,0);}

   // getters and setters
   Double_t Re() const {return fRe;}
   Double_t Im() const {return fIm;}
   Double_t Rho() const {return TMath::Sqrt(fRe*fRe+fIm*fIm);}
   Double_t Rho2() const {return fRe*fRe+fIm*fIm;}
   Double_t Theta() const {return (fIm||fRe)?TMath::ATan2(fIm,fRe):0;}
   LDComplex operator()(Double_t x, Double_t y, Bool_t polar=kFALSE)
      { if (polar) { fRe = x*TMath::Cos(y); fIm = x*TMath::Sin(y); }
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
   LDComplex operator *(Double_t c) const
      {return LDComplex(fRe*c,fIm*c);}
   LDComplex operator +(Double_t c) const
      {return LDComplex(fRe+c, fIm);}
   LDComplex operator /(Double_t c) const
      {return LDComplex(fRe/c,fIm/c);}
   LDComplex operator -(Double_t c) const
      {return LDComplex(fRe-c, fIm);}

   // Simple operators double - complex
   friend LDComplex operator *(Double_t d, const LDComplex & c)
      {return LDComplex(d*c.fRe,d*c.fIm);}
   friend LDComplex operator +(Double_t d, const LDComplex & c)
      {return LDComplex(d+c.fRe, c.fIm);}
   friend LDComplex operator /(Double_t d, const LDComplex & c)
      {return LDComplex(d*c.fRe,-d*c.fIm)/c.Rho2();}
   friend LDComplex operator -(Double_t d, const LDComplex & c)
      {return LDComplex(d-c.fRe, -c.fIm);}

   // Convertors
   operator Double_t () const {return fRe;}
   operator Float_t  () const {return static_cast<Float_t>(fRe);}
   operator Int_t    () const {return static_cast<Int_t>(fRe);}

   // TMath:: extensions
   static LDComplex Sqrt(const LDComplex &c)
      {return LDComplex(TMath::Sqrt(c.Rho()),0.5*c.Theta(),kTRUE);}

   static LDComplex Exp(const LDComplex &c)
      {return LDComplex(TMath::Exp(c.fRe),c.fIm,kTRUE);}
   static LDComplex Log(const LDComplex &c)
      {return LDComplex(0.5*TMath::Log(c.Rho2()),c.Theta());}
   static LDComplex Log2(const LDComplex &c)
      {return Log(c)/TMath::Log(2);}
   static LDComplex Log10(const LDComplex &c)
      {return Log(c)/TMath::Log(10);}

   static LDComplex Sin(const LDComplex &c)
      {return LDComplex(TMath::Sin(c.fRe)*TMath::CosH(c.fIm),
                       TMath::Cos(c.fRe)*TMath::SinH(c.fIm));}
   static LDComplex Cos(const LDComplex &c)
      {return LDComplex(TMath::Cos(c.fRe)*TMath::CosH(c.fIm),
                       -TMath::Sin(c.fRe)*TMath::SinH(c.fIm));}
   static LDComplex Tan(const LDComplex &c)
      {LDComplex cc=Cos(c); return Sin(c)*Conjugate(cc)/cc.Rho2();}

   static LDComplex ASin(const LDComplex &c)
      {return -I()*Log(I()*c+TMath::Sign(1.,c.Im())*Sqrt(1.-c*c));}
   static LDComplex ACos(const LDComplex &c)
      {return -I()*Log(c+TMath::Sign(1.,c.Im())*Sqrt(c*c-1.));}
   static LDComplex ATan(const LDComplex &c)
      {return -0.5*I()*Log((1.+I()*c)/(1.-I()*c));}

   static LDComplex SinH(const LDComplex &c)
      {return LDComplex(TMath::SinH(c.fRe)*TMath::Cos(c.fIm),
                       TMath::CosH(c.fRe)*TMath::Sin(c.fIm));}
   static LDComplex CosH(const LDComplex &c)
      {return LDComplex(TMath::CosH(c.fRe)*TMath::Cos(c.fIm),
                       TMath::SinH(c.fRe)*TMath::Sin(c.fIm));}
   static LDComplex TanH(const LDComplex &c)
      {LDComplex cc=CosH(c); return SinH(c)*Conjugate(cc)/cc.Rho2();}

   static LDComplex ASinH(const LDComplex &c)
      {return Log(c+TMath::Sign(1.,c.Im())*Sqrt(c*c+1.));}
   static LDComplex ACosH(const LDComplex &c)
      {return Log(c+TMath::Sign(1.,c.Im())*Sqrt(c*c-1.));}
   static LDComplex ATanH(const LDComplex &c)
      {return 0.5*Log((1.+c)/(1.-c));}

   static Double_t Abs(const LDComplex &c)
      {return c.Rho();}

   static LDComplex Power(const LDComplex& x, const LDComplex& y)
      {Double_t lrho=TMath::Log(x.Rho());
       Double_t theta=x.Theta();
       return LDComplex(TMath::Exp(lrho*y.Re()-theta*y.Im()),
                       lrho*y.Im()+theta*y.Re(),kTRUE);}
   static LDComplex Power(const LDComplex& x, Double_t y)
      {return LDComplex(TMath::Power(x.Rho(),y),x.Theta()*y,kTRUE);}
   static LDComplex Power(Double_t x, const LDComplex& y)
      {Double_t lrho=TMath::Log(TMath::Abs(x));
       Double_t theta=(x>0)?0:TMath::Pi();
       return LDComplex(TMath::Exp(lrho*y.Re()-theta*y.Im()),
                       lrho*y.Im()+theta*y.Re(),kTRUE);}
   static LDComplex Power(const LDComplex& x, Int_t y)
      {return LDComplex(TMath::Power(x.Rho(),y),x.Theta()*y,kTRUE);}

   static Int_t Finite(const LDComplex& c)
      {return TMath::Min(TMath::Finite(c.Re()),TMath::Finite(c.Im()));}
   static Int_t IsNaN(const LDComplex& c)
      {return TMath::Max(TMath::IsNaN(c.Re()),TMath::IsNaN(c.Im()));}

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

   ClassDef(LDComplex,1)  //Complex Class
};

#endif
