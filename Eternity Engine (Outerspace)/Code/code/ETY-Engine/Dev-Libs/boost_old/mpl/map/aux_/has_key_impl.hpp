
#ifndef BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: has_key_impl.hpp 3 2013-07-17 10:04:05Z Trout-31 $
// $Date: 2013-07-17 12:04:05 +0200 (Mi, 17 Jul 2013) $
// $Revision: 3 $

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/map/aux_/tag.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>

namespace boost { namespace mpl {

template<>
struct has_key_impl< aux::map_tag >
{
    template< typename Map, typename Key > struct apply
#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)
        : is_not_void_< 
              typename at_impl<aux::map_tag>
                ::apply<Map,Key>::type
            >
#else
        : bool_< ( x_order_impl<Map,Key>::value > 1 ) >
#endif
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_HAS_KEY_IMPL_HPP_INCLUDED
