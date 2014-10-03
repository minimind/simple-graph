#ifndef agents_arachnidutils_graph_graphcopyfunctor_h
#define agents_arachnidutils_graph_graphcopyfunctor_h

#include "graph.h"

//namespace SimpleGraph {

template< typename N, typename E >
class GraphCopyFunctor
{
public:
  typedef N node_type;
  typedef E edge_type;

  node_type operator()( const typename Graph<N,E>::const_node_iterator& n )
  {
    return *n;
  }

  edge_type operator()( const typename Graph<N,E>::const_edge_iterator& e,
                        const typename Graph<N,E>::const_node_iterator& n1,
                        const typename Graph<N,E>::const_node_iterator& n2 )
  {
    return *e;
  }
};

//} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_graphcopyfunctor_h
