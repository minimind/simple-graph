#ifndef CONST_EDGE_ITERATOR_HPP
#define CONST_EDGE_ITERATOR_HPP

#include "constedgeiterator.h"
#include "constnodeiterator.h"
#include "edgeiterator.h"

namespace SimpleGraph {

template< typename N, typename E >
ConstEdgeIterator<N,E>::ConstEdgeIterator( const typename std::list< boost::shared_ptr< SimpleEdge<N,E> > >::const_iterator& i )
  : m_iterator( i )
{
}

template< typename N, typename E >
ConstEdgeIterator<N,E>::ConstEdgeIterator( const EdgeIterator<N,E>& i )
  : m_iterator( i.m_iterator )
{
}

template< typename N, typename E >
ConstNodeIterator< N, E > ConstEdgeIterator<N,E>::left() const
{
  return ( *m_iterator )->m_left;
}

template< typename N, typename E >
ConstNodeIterator< N, E > ConstEdgeIterator<N,E>::right() const
{
  return ( *m_iterator )->m_right;
}

template< typename N, typename E >
const E& ConstEdgeIterator<N,E>::operator *() const
{
  return ( *m_iterator )->m_object;
}

template< typename N, typename E >
const E *ConstEdgeIterator<N,E>::operator->() const
{
  return &( ( *m_iterator )->m_object );
}

template< typename N, typename E >
bool ConstEdgeIterator<N,E>::operator==( const EdgeIterator<N,E>& n ) const
{
  return m_iterator == n.m_iterator;
}

template< typename N, typename E >
bool ConstEdgeIterator<N,E>::operator==( const ConstEdgeIterator& n ) const
{
  return m_iterator == n.m_iterator;
}

template< typename N, typename E >
bool ConstEdgeIterator<N,E>::operator!=( const EdgeIterator<N,E>& n ) const
{
  return m_iterator != n.m_iterator;
}

template< typename N, typename E >
bool ConstEdgeIterator<N,E>::operator!=( const ConstEdgeIterator& n ) const
{
  return m_iterator != n.m_iterator;
}

template< typename N, typename E >
ConstEdgeIterator<N,E>& ConstEdgeIterator<N,E>::operator++()
{
  ++m_iterator;
  return *this;
}

template< typename N, typename E >
ConstEdgeIterator<N,E> ConstEdgeIterator<N,E>::operator++( int )
{
  ConstEdgeIterator toReturn( *this );
  ++( *this );
  return toReturn;
}

template< typename N, typename E >
ConstEdgeIterator<N,E>& ConstEdgeIterator<N,E>::operator--()
{
  --m_iterator;
  return *this;
}

template< typename N, typename E >
ConstEdgeIterator<N,E> ConstEdgeIterator<N,E>::operator--( int )
{
  ConstEdgeIterator toReturn( *this );
  --( *this );
  return toReturn;
}

} // namespace SimpleGraph

#endif // CONST_EDGE_ITERATOR_HPP
