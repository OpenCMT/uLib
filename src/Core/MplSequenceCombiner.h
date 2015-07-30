#ifndef U_CORE_MPLSEQUENCECOMBINER_H
#define U_CORE_MPLSEQUENCECOMBINER_H

#include <boost/mpl/unpack_args.hpp>
#include <boost/mpl/back.hpp>
#include <boost/mpl/pop_back.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/zip_view.hpp>
#include <boost/mpl/prior.hpp>

#include <Core/Mpl.h>


namespace uLib {
namespace mpl {


////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template <class Seq, class ItrSeq>
class SequenceCombiner {
    template < class _Seq = mpl::vector<int_<1> > >
    struct StateSeq {
        typedef typename pop_front<_Seq>::type sequence;
        typedef typename mpl::at< _Seq, int_<0> >::type state;
        typedef _Seq type;
    };

    template < class _Seq, class _State >
    struct set_state {
        typedef StateSeq< typename push_front<_Seq, _State >::type > type;
    };

    struct NextOp {

        template < typename Out, typename In, typename Enable = typename Out::state >
        class apply {
            typedef typename Out::sequence seq;
            typedef typename Out::state new_state;
            typedef typename mpl::at<In,int_<0> >::type in_seq;
            typedef typename mpl::at<In,int_<1> >::type in_itr;

            typedef typename mpl::push_back<seq, in_itr >::type new_seq;
        public:
            typedef typename set_state<new_seq, int_<0> >::type type;
        };

        template < typename Out, typename In >
        class apply<Out,In,mpl::int_<1> > {
            typedef typename Out::sequence seq;
            typedef typename Out::state state;
            typedef typename mpl::at<In,int_<0> >::type in_seq;
            typedef typename mpl::at<In,int_<1> >::type in_itr;

            typedef typename mpl::begin<in_seq>::type Itr_begin;
            typedef typename mpl::next<in_itr>::type  Itr_next;
            typedef typename mpl::end<in_seq>::type   Itr_end;

            typedef typename mpl::if_< boost::is_same<Itr_next,Itr_end>,
                                       typename mpl::push_back<seq,Itr_begin>::type,
                                       typename mpl::push_back<seq,Itr_next>::type
                                     >::type
            new_seq;

            typedef typename mpl::if_< boost::is_same<Itr_next,Itr_end>,
                                       mpl::int_<1>,
                                       mpl::int_<0>
                                     >::type
            new_state;
        public:
            typedef typename set_state<new_seq, new_state>::type type;
        };
    };

    typedef typename mpl::fold< typename mpl::zip_view< mpl::vector<Seq, ItrSeq > >::type,
                                StateSeq<>,
                                NextOp
                              >::type
    StateResult;

public:

    typedef typename mpl::if_< boost::is_same< typename StateResult::state, int_<1> >,
                               typename mpl::transform< Seq, mpl::end<_1> >::type,
                               typename StateResult::sequence 
                             >::type
    next;
};





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


template < typename Seq, typename Itrs >
struct combine_iterator {
    typedef mpl::forward_iterator_tag category;
    typedef Seq  seq;

    typedef typename transform <
        Itrs,
        deref<_1>
      >::type
    type;
};



////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

template < class Seq >
class combine_view {
    typedef typename mpl::transform<Seq, mpl::begin<_1> >::type Itrs_begin;
    typedef typename mpl::transform<Seq, mpl::end<_1> >::type   Itrs_end;
public:
    typedef combine_iterator<Seq, Itrs_begin> begin;
    typedef combine_iterator<Seq, Itrs_end>  end;

    typedef combine_view type;
};



} // mpl
} // uLib




////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


namespace boost {
namespace mpl {

template <class Seq, class Pos>
struct next< uLib::mpl::combine_iterator<Seq, Pos> > {
    typedef typename uLib::mpl::SequenceCombiner<Seq,Pos>::next next_Pos;
    typedef uLib::mpl::combine_iterator< Seq, next_Pos > type;
};

} // mpl
} // boost





#endif // MPLSEQUENCECOMBINER_H
