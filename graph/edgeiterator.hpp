#ifndef EDGE_ITERATOR_HPP
#define EDGE_ITERATOR_HPP

#include "edgeiterator.h"
#include "nodeiterator.h"

namespace SimpleGraph {

template< typename N, typename E >
EdgeIterator<N,E>::EdgeIterator( const typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator& i )
  : m_iterator( i )
{
}

template< typename N, typename E >
EdgeIterator<N,E>::EdgeIterator()
{
}

template< typename N, typename E >
NodeIterator< N, E > EdgeIterator<N,E>::left()
{
  return ( *m_iterator )->m_left;
}

template< typename N, typename E >
NodeIterator< N, E > EdgeIterator<N,E>::right()
{
  return ( *m_iterator )->m_right;
}

template< typename N, typename E >
ConstNodeIterator< N, E > EdgeIterator<N,E>::left() const
{
  return ( *m_iterator )->m_left;
}

template< typename N, typename E >
ConstNodeIterator< N, E > EdgeIterator<N,E>::right() const
{
  return ( *m_iterator )->m_right;
}

template< typename N, typename E >
E& EdgeIterator<N,E>::operator *()
{
  return ( *m_iterator )->m_object;
}

template< typename N, typename E >
const E& EdgeIterator<N,E>::operator *() const
{
  return ( *m_iterator )->m_object;
}

template< typename N, typename E >
E *EdgeIterator<N,E>::operator->()
{
  return &( ( *m_iterator )->m_object );
}

template< typename N, typename E >
const E *EdgeIterator<N,E>::operator->() const
{
  return &( ( *m_iterator )->m_object );
}

template< typename N, typename E >
bool EdgeIterator<N,E>::operator==( const EdgeIterator& n ) const
{
  return m_iterator == n.m_iterator;
}

template< typename N, typename E >
bool EdgeIterator<N,E>::operator!=( const EdgeIterator& n ) const
{
  return m_iterator != n.m_iterator;
}

template< typename N, typename E >
EdgeIterator<N,E>& EdgeIterator<N,E>::operator++()
{
  ++m_iterator;
  return *this;
}

template< typename N, typename E >
EdgeIterator<N,E> EdgeIterator<N,E>::operator++( int )
{
  EdgeIterator toReturn( *this );
  ++( *this );
  return toReturn;
}

template< typename N, typename E >
EdgeIterator<N,E>& EdgeIterator<N,E>::operator--()
{
  --m_iterator;
  return *this;
}

template< typename N, typename E >
EdgeIterator<N,E> EdgeIterator<N,E>::operator--( int )
{
  EdgeIterator toReturn( *this );
  --( *this );
  return toReturn;
}

} // namespace SimpleGraph

#endif // EDGE_ITERATOR_HPP

