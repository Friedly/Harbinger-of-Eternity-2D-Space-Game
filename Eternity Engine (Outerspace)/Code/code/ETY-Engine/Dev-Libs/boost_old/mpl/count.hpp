
#ifndef BOOST_MPL_COUNT_HPP_INCLUDED
#define BOOST_MPL_COUNT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id: count.hpp 3 2013-07-17 10:04:05Z Trout-31 $
// $Date: 2013-07-17 12:04:05 +0200 (Mi, 17 Jul 2013) $
// $Revision: 3 $

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/count_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct count
    : count_impl< typename sequence_tag<Sequence>::type >
        ::template apply<Sequence,T>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, count)

}}

#endif // BOOST_MPL_COUNT_HPP_INCLUDED
