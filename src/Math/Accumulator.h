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



#ifndef U_DATABINNING_H
#define U_DATABINNING_H

#include <vector>

#include "Dense.h"


namespace uLib {



// TODO: USE BOOST ACCUMULATORS //


template <typename T>
class Accumulator_Mean {
    typedef std::pair<T,unsigned long> Tmean;
public:
    Accumulator_Mean() {
        m_Means.push_back( Tmean(0,0) );
    }

    void operator()(const T data) {
        T tmp = 0;
        //        for(typename std::vector<Tmean>::iterator it = m_Means.begin(); it < m_Means.back(); ++it)
        //        tmp += it->first/it->second;
        for(int i=0; i<m_Means.size()-1;++i)
            tmp += m_Means[i].first / m_Means[i].second;
        m_Means.back().first += data - tmp;
        m_Means.back().second += 1;
    }

    T operator()() const {
        T mean = 0;
        //        for(typename std::vector<Tmean>::iterator it = m_Means.begin(); it < m_Means.end(); ++it) {
        //            mean += it->first/it->second; }
        for(int i=0; i<m_Means.size();++i)
            mean += m_Means[i].first / m_Means[i].second;
        return mean;
    }

    void AddPass() { m_Means.push_back( Tmean(0,0) ); }

private:
    std::vector< Tmean > m_Means;
};




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// accumulator Trim //

template < typename T, int subsample_size=200 >
class Accumulator_ABTrim {

public:
    Accumulator_ABTrim() :
        m_Avg(0),
        m_InternalCount(0),
        m_SizeA(0),
        m_SizeB(0),
        m_IdA(0),
        m_IdB(0)
    {}

    Accumulator_ABTrim(const Accumulator_ABTrim &c) {
#       pragma omp critical
        {
            m_Avg = c.m_Avg;
            m_InternalCount = c.m_InternalCount;
            m_SizeA = c.m_SizeA;
            m_SizeB = c.m_SizeB;
            m_IdA = c.m_IdA;
            m_IdB = c.m_IdB;
            memcpy (m_Av, c.m_Av, sizeof (m_Av));
        }
    }

    void operator += (T value) {
        if(m_InternalCount > subsample_size) {
            //  array complete and counter over subsample //
            if( m_SizeA > 0 && value < m_ValA ) {
               ;// m_Avg += m_ValA;
            }
            else if (m_SizeB > 0 && value > m_ValB)
            {
               ;// m_Avg += m_ValB;
            }
            else
            {
                m_Avg += value;
                m_InternalCount++;
            }
        }
        else if(m_InternalCount >=0) {
            // array complete
            if(m_SizeA > 0 && value < m_ValA)
            {
                m_Avg += m_ValA;
                m_Av[m_IdA] = value;
                for (unsigned int i=0; i < m_SizeA; i++)
                    if(m_Av[i] > m_Av[m_IdA])
                    { m_IdA = i; m_ValA = m_Av[i]; }
            }
            else if(m_SizeB > 0 && value > m_ValB)
            {
                m_Avg += m_ValB;
                m_Av[m_IdB] = value;
                for (unsigned int i=m_SizeA; i < m_SizeA+m_SizeB; i++)
                    if(m_Av[i] < m_Av[m_IdB])
                    { m_IdB = i; m_ValB = m_Av[i]; }
            }
            else {
                m_Avg += value;
            }
            m_InternalCount++;
        }
        else { // m_InternalCount < 0
                // array is not fullfilled
                m_Av[m_SizeA+m_SizeB+m_InternalCount] = value;
                m_InternalCount++;
                if(m_InternalCount == 0) {
                    std::sort(m_Av,m_Av+m_SizeA+m_SizeB);
                    if(m_SizeA > 0) {
                        m_IdA = m_SizeA-1;
                        m_ValA = m_Av[m_IdA];
                    }
                    if(m_SizeB > 0) {
                        m_IdB = m_SizeA;
                        m_ValB = m_Av[m_SizeA];
                    }
                }
        }
    }

    T operator()() {
        if(m_InternalCount <= 0) {
            std::sort(m_Av, m_Av+m_SizeA+m_SizeB+m_InternalCount);
            return m_Av[ (m_SizeA+m_SizeB+m_InternalCount) / 2]; // median value //
        }
        else {
//            return (m_Avg + m_ValA * m_SizeA + m_ValB * m_SizeB) /
//                    (m_InternalCount + m_SizeA + m_SizeB);
            return (m_Avg) / m_InternalCount;
        }
    }

    void SetABTrim(int a, int b) {
            if(a+b > subsample_size/2) {
                m_SizeA = a/(a+b) * subsample_size/2;
                m_SizeB = b/(a+b) * subsample_size/2;
            }
            else {
                m_SizeA = a;
                m_SizeB = b;
            }
            m_Avg = 0;
            m_InternalCount = -m_SizeA-m_SizeB;
    }


private:
    T    m_Av[subsample_size/2];
    T    m_Avg,  m_ValA,  m_ValB;
    int  m_IdA,  m_IdB,   m_InternalCount;
    int  m_SizeA, m_SizeB;
};









////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Clip Accumulator //

template < typename T, int subsample_size=200 >
class Accumulator_ABClip {

public:
    Accumulator_ABClip() :
        m_Avg(0),
        m_InternalCount(0),
        m_SizeA(0),
        m_SizeB(0),
        m_IdA(0),
        m_IdB(0)
    {}

    Accumulator_ABClip(const Accumulator_ABClip &c) {
#       pragma omp critical
        {
            m_Avg = c.m_Avg;
            m_InternalCount = c.m_InternalCount;
            m_SizeA = c.m_SizeA;
            m_SizeB = c.m_SizeB;
            m_IdA = c.m_IdA;
            m_IdB = c.m_IdB;
            memcpy (m_Av, c.m_Av, sizeof (m_Av));
        }
    }

    void operator += (T value) {
        if(m_InternalCount > subsample_size) {
            //  array complete and counter over subsample //
            if( m_SizeA > 0 && value < m_ValA ) {
               m_Avg += m_ValA;
            }
            else if (m_SizeB > 0 && value > m_ValB) {
               m_Avg += m_ValB;
            }
            else {
                m_Avg += value;
            }
            m_InternalCount++;
        }
        else if(m_InternalCount >=0) {
            // array complete
            if(m_SizeA > 0 && value < m_ValA)
            {
                m_Avg += m_ValA;
                m_Av[m_IdA] = value;
                for (unsigned int i=0; i < m_SizeA; i++)
                    if(m_Av[i] > m_Av[m_IdA])
                    { m_IdA = i; m_ValA = m_Av[i]; }
            }
            else if(m_SizeB > 0 && value > m_ValB)
            {
                m_Avg += m_ValB;
                m_Av[m_IdB] = value;
                for (unsigned int i=m_SizeA; i < m_SizeA+m_SizeB; i++)
                    if(m_Av[i] < m_Av[m_IdB])
                    { m_IdB = i; m_ValB = m_Av[i]; }
            }
            else {
                m_Avg += value;
            }
            m_InternalCount++;
        }
        else { // m_InternalCount < 0
                // array is not fullfilled
                m_Av[m_SizeA+m_SizeB+m_InternalCount] = value;
                m_InternalCount++;
                if(m_InternalCount == 0) {
                    std::sort(m_Av,m_Av+m_SizeA+m_SizeB);
                    if(m_SizeA > 0) {
                        m_IdA = m_SizeA-1;
                        m_ValA = m_Av[m_IdA];
                    }
                    if(m_SizeB > 0) {
                        m_IdB = m_SizeA;
                        m_ValB = m_Av[m_SizeA];
                    }
                }
        }
    }

    T operator()() {
        if(m_InternalCount <= 0) {
            std::sort(m_Av, m_Av+m_SizeA+m_SizeB+m_InternalCount);
            return m_Av[ (m_SizeA+m_SizeB+m_InternalCount) / 2]; // median value //
        }
        else {
            return (m_Avg + m_ValA * m_SizeA + m_ValB * m_SizeB) /
                    (m_InternalCount + m_SizeA + m_SizeB);
        }
    }

    void SetABTrim(int a, int b) {
            if(a+b > subsample_size/2) {
                m_SizeA = a/(a+b) * subsample_size/2;
                m_SizeB = b/(a+b) * subsample_size/2;
            }
            else {
                m_SizeA = a;
                m_SizeB = b;
            }
            m_Avg = 0;
            m_InternalCount = -m_SizeA-m_SizeB;
    }


private:
    T    m_Av[subsample_size/2];
    T    m_Avg,  m_ValA,  m_ValB;
    int  m_IdA,  m_IdB,   m_InternalCount;
    int  m_SizeA, m_SizeB;
};





} // uLib




#endif // U_DATABINNING_H
