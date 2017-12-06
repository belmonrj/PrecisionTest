// @(#)root/mathcore:$Id$
// Author: Federico Carminati   22/04/2004

/*************************************************************************
 * Copyright (C) 1995-2004, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// LDComplex                                                            //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

// --- modified by Ron Belmont to use long double instead of Double_t, 06 Dec 2017

#include "LDComplex.h"
#include "Riostream.h"


//ClassImp(LDComplex)

////////////////////////////////////////////////////////////////////////////////
/// Standard constructor

LDComplex::LDComplex(long double re, long double im, Bool_t polar) : fRe(re), fIm(im)
{
   if (polar) {
      if(re<0) {
         ::Warning("LDComplex::ctor","Modulo of a complex number should be >=0, taking the abs");
         re=-re;
      }
      fRe=re*TMath::Cos(im);
      fIm=re*TMath::Sin(im);
   }
}

////////////////////////////////////////////////////////////////////////////////

LDComplex::~LDComplex()
{

}

////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& out, const LDComplex& c)
{
   out << "(" << c.fRe << "," << c.fIm << "i)";
   return out;
}

////////////////////////////////////////////////////////////////////////////////

std::istream& operator>>(std::istream& in, LDComplex& c)
{
   in >> c.fRe >> c.fIm;
   return in;
}
