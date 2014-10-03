#ifndef agents_arachnidutils_graph_alledges_h
#define agents_arachnidutils_graph_alledges_h

#include <list>
#include <boost/shared_ptr.hpp>

template< typename N, typename E> class Graph;

namespace SimpleGraph {

template< typename N, typename E > class  EdgeIterator;
template< typename N, typename E > class  ConstEdgeIterator;
template< typename N, typename E > struct SimpleEdge;

template< typename N, typename E>
class AllEdges
{
public:
  size_t                    size()  const;
  bool                      empty() const;
  EdgeIterator< N, E >      begin();
  ConstEdgeIterator< N, E > begin() const;
  EdgeIterator< N, E >      end();
  ConstEdgeIterator< N, E > end()   const;

//private:
  friend class Graph<N,E>;

  std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > > m_edges;
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_alledges_h
