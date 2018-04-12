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






#include "Core/Archives.h"

//#define BOOST_ARCHIVE_SOURCE
#include <boost/archive/detail/archive_serializer_map.hpp>

// explicitly instantiate for this type of xml stream
#include <boost/archive/impl/archive_serializer_map.ipp>

#include <boost/archive/impl/basic_xml_oarchive.ipp>
#include <boost/archive/impl/xml_oarchive_impl.ipp>

#include <boost/archive/impl/basic_xml_grammar.hpp>

#include <boost/archive/impl/basic_xml_iarchive.ipp>
#include <boost/archive/impl/xml_iarchive_impl.ipp>

#include <boost/archive/impl/basic_text_oarchive.ipp>
#include <boost/archive/impl/text_oarchive_impl.ipp>

#include <boost/archive/impl/basic_text_iarchive.ipp>
#include <boost/archive/impl/text_iarchive_impl.ipp>

#include <boost/archive/polymorphic_xml_oarchive.hpp>
#include <boost/archive/polymorphic_text_oarchive.hpp>


namespace boost {
namespace archive {



template class detail::archive_serializer_map <uLib::Archive::xml_oarchive> ;
template class basic_xml_oarchive             <uLib::Archive::xml_oarchive> ;
template class xml_oarchive_impl              <uLib::Archive::xml_oarchive> ;

template class detail::archive_serializer_map <uLib::Archive::xml_iarchive> ;
template class basic_xml_iarchive             <uLib::Archive::xml_iarchive> ;
template class xml_iarchive_impl              <uLib::Archive::xml_iarchive> ;

template class detail::archive_serializer_map <uLib::Archive::text_oarchive> ;
template class basic_text_oarchive             <uLib::Archive::text_oarchive> ;
template class text_oarchive_impl              <uLib::Archive::text_oarchive> ;

template class detail::archive_serializer_map <uLib::Archive::text_iarchive> ;
template class basic_text_iarchive             <uLib::Archive::text_iarchive> ;
template class text_iarchive_impl              <uLib::Archive::text_iarchive> ;

template class detail::archive_serializer_map <uLib::Archive::hrt_oarchive> ;
template class basic_text_oarchive             <uLib::Archive::hrt_oarchive> ;
template class text_oarchive_impl              <uLib::Archive::hrt_oarchive> ;

template class detail::archive_serializer_map <uLib::Archive::hrt_iarchive> ;
template class basic_text_iarchive             <uLib::Archive::hrt_iarchive> ;
template class text_iarchive_impl              <uLib::Archive::hrt_iarchive> ;

template class detail::archive_serializer_map <uLib::Archive::log_archive> ;
template class basic_xml_oarchive             <uLib::Archive::log_archive> ;
template class xml_oarchive_impl              <uLib::Archive::log_archive> ;



////////////////////////////////////////////////////////////////////////////////
//  XML GRAMMAR STUBS  /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// WARNING: this stubs were added because misteriously the implementation of
// this templated methods are missing....
//
//
template<class CharType>
bool basic_xml_grammar<CharType>::parse_start_tag(basic_xml_grammar::IStream &is)
{}
//
template<class CharType>
bool basic_xml_grammar<CharType>::parse_end_tag(basic_xml_grammar::IStream &is)
const {}
//
template<class CharType>
bool basic_xml_grammar<CharType>::parse_string(basic_xml_grammar::IStream &is, basic_xml_grammar::StringType &s)
{}
//
template<class CharType>
void basic_xml_grammar<CharType>::init(basic_xml_grammar::IStream &is)
{}
//
template<class CharType>
bool basic_xml_grammar<CharType>::windup(basic_xml_grammar::IStream &is)
{}
//
template<class CharType>
basic_xml_grammar<CharType>::basic_xml_grammar()
{}
//
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////



} // namespace archive
} // namespace boost



