#ifndef agents_arachnidutils_graph_simpleedge_h
#define agents_arachnidutils_graph_simpleedge_h

#include <boost/shared_ptr.hpp>
#include <list>

namespace SimpleGraph {

template< typename N, typename E > class NodeIterator;

template< typename N, typename E >
struct SimpleEdge
{
  SimpleEdge( const E& object, NodeIterator<N,E>& left, NodeIterator<N,E>& right )
    : m_object( object )
    , m_left(   left   )
    , m_right(  right  )
  {
  }

  E                                                                                 m_object;
  NodeIterator<N,E>                                                                 m_left;
  NodeIterator<N,E>                                                                 m_right;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_mainIterator;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_leftIterator;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_rightIterator;
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_simpleedge_h
