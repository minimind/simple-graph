#ifndef agents_arachnidutils_graph_edgeiterator_h
#define agents_arachnidutils_graph_edgeiterator_h

#include <list>

namespace SimpleGraph {

template< typename N, typename E > class  NodeIterator;
template< typename N, typename E > class  ConstNodeIterator;
template< typename N, typename E > struct SimpleEdge;
template< typename N, typename E > class  AllEdges;

template< typename N, typename E >
class EdgeIterator
{
public:
  NodeIterator< N, E > left();
  NodeIterator< N, E > right();

  ConstNodeIterator< N, E > left()  const;
  ConstNodeIterator< N, E > right() const;

  E&            operator *();
  const E&      operator *()                      const;
  E            *operator->();
  const E      *operator->()                      const;
  bool          operator==( const EdgeIterator& ) const;
  bool          operator!=( const EdgeIterator& ) const;
  EdgeIterator& operator++();
  EdgeIterator  operator++( int );
  EdgeIterator& operator--();
  EdgeIterator  operator--( int );

//private:
  friend class AllEdges<N,E>;

  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_iterator;

  EdgeIterator( const typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator& );
  EdgeIterator();
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_edgeiterator_h
