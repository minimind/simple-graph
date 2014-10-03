#ifndef agents_arachnidutils_graph_simplenode_h
#define agents_arachnidutils_graph_simplenode_h

#include <boost/shared_ptr.hpp>
#include <list>

namespace SimpleGraph {

template< typename N, typename E > struct SimpleEdge;

template< typename N, typename E >
struct SimpleNode
{
  SimpleNode( const N& object, const unsigned long key )
    : m_object( object )
    , m_key(    key    )
  {
  }

  N                                                              m_object;
  unsigned long                                                  m_key;
  std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > > m_edges;
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_simplenode_h
