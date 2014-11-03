/*//////////////////////////////////////////////////////////////////////////////
// CMT Cosmic Muon Tomography project //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

  Copyright (c) 2014, Universita' degli Studi di Padova, INFN sez. di Padova
  All rights reserved

  Authors: Andrea Rigoni Garola < andrea.rigoni@pd.infn.it >

  ------------------------------------------------------------------
  This library is free software;  you  can  redistribute  it  and/or
  modify it  under the  terms  of  the  GNU  Lesser  General  Public
  License as published  by  the  Free  Software  Foundation;  either
  version 3.0 of the License, or (at your option) any later version.

  This library is  distributed in  the hope that it will  be useful,
  but  WITHOUT ANY WARRANTY;  without  even  the implied warranty of
  MERCHANTABILITY  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of  the GNU Lesser General  Public
  License along with this library.

//////////////////////////////////////////////////////////////////////////////*/




#include "Ob.h"





namespace uLib {







namespace SignalMock {

class ObPrivate {
public:

    struct Signal {
        GenericMFPtr  sigptr;
        std::string   sigstr;
        SignalBase   *signal;
    };

    Vector<Signal> sigv;


};






Ob::Ob() :
    d(new ObPrivate)
{}


void Ob::PrintSelf(std::ostream &o) const
{
    o << "OBJECT signal Mock: ------------------\n";
    Vector<ObPrivate::Signal>::Iterator itr;
    for(itr = d->sigv.begin(); itr<d->sigv.end(); itr++)
    {
        o << "  signal:[ " << itr->sigstr << " ]\n";
    }
    o << "--------------------------------------\n\n";
}



bool Ob::addSignalImpl(SignalBase *sig, GenericMFPtr fptr, const char *name)
{
    ObPrivate::Signal s = {fptr,std::string(name),sig};
    d->sigv.push_back(s);
}

SignalBase *Ob::findSignalImpl(const GenericMFPtr &fptr)
{
    for(int i=0; i<d->sigv.size(); ++i)
    {
        if(d->sigv[i].sigptr == fptr)
            return d->sigv[i].signal;
    }
    return NULL;
}




}

}

