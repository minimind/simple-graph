#ifndef agents_arachnidutils_graph_constedgeiterator_h
#define agents_arachnidutils_graph_constedgeiterator_h

#include <list>

namespace SimpleGraph {

template< typename N, typename E > class  ConstNodeIterator;
template< typename N, typename E > struct SimpleEdge;
template< typename N, typename E > class  AllEdges;
template< typename N, typename E > class  EdgeIterator;

template< typename N, typename E >
class ConstEdgeIterator
{
public:
  ConstNodeIterator< N, E > left()  const;
  ConstNodeIterator< N, E > right() const;

  const E&            operator *()                           const;
  const E            *operator->()                           const;
  bool                operator==( const EdgeIterator<N,E>& ) const;
  bool                operator==( const ConstEdgeIterator& ) const;
  bool                operator!=( const EdgeIterator<N,E>& ) const;
  bool                operator!=( const ConstEdgeIterator& ) const;
  ConstEdgeIterator&  operator++();
  ConstEdgeIterator   operator++( int );
  ConstEdgeIterator&  operator--();
  ConstEdgeIterator   operator--( int );

//private:
  friend class AllEdges<N,E>;

  typename std::list< boost::shared_ptr< SimpleEdge<N,E> > >::const_iterator m_iterator;

  ConstEdgeIterator( const typename std::list< boost::shared_ptr< SimpleEdge<N,E> > >::const_iterator& );
  ConstEdgeIterator( const EdgeIterator<N,E>& );
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_constedgeiterator_h
