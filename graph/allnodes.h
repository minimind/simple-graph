#ifndef agents_arachnidutils_graph_allnodes_h
#define agents_arachnidutils_graph_allnodes_h

#include <map>
#include <boost/shared_ptr.hpp>
#include "simplenode.h"

template< typename N, typename E > class Graph;

namespace SimpleGraph {

template< typename N, typename E > class NodeIterator;
template< typename N, typename E > class ConstNodeIterator;

template< typename N, typename E >
class AllNodes
{
public:
  size_t                    size()                const;
  bool                      empty()               const;
  NodeIterator< N, E >      begin();
  ConstNodeIterator< N, E > begin()               const;
  NodeIterator< N, E >      end();
  ConstNodeIterator< N, E > end()                 const;
  NodeIterator< N, E >      find( unsigned long );
  ConstNodeIterator< N, E > find( unsigned long ) const;

//private:
  friend class Graph< N, E >;

  typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > > m_nodes;
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_allnodes_h
