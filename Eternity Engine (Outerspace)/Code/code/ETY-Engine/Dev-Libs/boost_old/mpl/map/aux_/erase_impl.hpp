
#ifndef BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: erase_impl.hpp 3 2013-07-17 10:04:05Z Trout-31 $
// $Date: 2013-07-17 12:04:05 +0200 (Mi, 17 Jul 2013) $
// $Revision: 3 $

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::map_tag>
            ::apply<Map,typename Pos::type::first>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
