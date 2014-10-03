#ifndef CONST_NODE_ITERATOR_HPP
#define CONST_NODE_ITERATOR_HPP

#include "constnodeiterator.h"
#include "constedgeiterator.h"
#include "nodeiterator.h"

namespace SimpleGraph {

template< typename N, typename E >
ConstNodeIterator<N,E>::ConstNodeIterator( const typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::const_iterator& i )
  : m_iterator( i )
{
}

template< typename N, typename E >
ConstNodeIterator<N,E>::ConstNodeIterator( const NodeIterator<N,E>& i )
  : m_iterator( i.m_iterator )
{
}

template< typename N, typename E >
ConstNodeIterator<N,E>::ConstNodeIterator()
{
}

template< typename N, typename E >
ConstEdgeIterator< N, E > ConstNodeIterator<N,E>::begin()
{
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::const_iterator i = m_iterator->second->m_edges.begin();
  return ConstEdgeIterator< N, E >( i );
}

template< typename N, typename E >
ConstEdgeIterator< N, E > ConstNodeIterator<N,E>::end()
{
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::const_iterator i = m_iterator->second->m_edges.end();
  return ConstEdgeIterator< N, E >( i );
}

template< typename N, typename E >
unsigned long ConstNodeIterator<N,E>::key() const
{
  return m_iterator->first;
}

template< typename N, typename E >
size_t ConstNodeIterator<N,E>::size() const
{
  return m_iterator->second->m_edges.size();
}

template< typename N, typename E >
bool ConstNodeIterator<N,E>::empty() const
{
  return m_iterator->second->m_edges.empty();
}

template< typename N, typename E >
const N& ConstNodeIterator<N,E>::operator *() const
{
  return m_iterator->second->m_object;
}

template< typename N, typename E >
const N *ConstNodeIterator<N,E>::operator->() const
{
  return &( m_iterator->second->m_object );
}

template< typename N, typename E >
bool ConstNodeIterator<N,E>::operator==( const NodeIterator<N,E>& n ) const
{
  return m_iterator == n.m_iterator;
}

template< typename N, typename E >
bool ConstNodeIterator<N,E>::operator==( const ConstNodeIterator& n ) const
{
  return m_iterator == n.m_iterator;
}

template< typename N, typename E >
bool ConstNodeIterator<N,E>::operator!=( const NodeIterator<N,E>& n ) const
{
  return m_iterator != n.m_iterator;
}

template< typename N, typename E >
bool ConstNodeIterator<N,E>::operator!=( const ConstNodeIterator& n ) const
{
  return m_iterator != n.m_iterator;
}

template< typename N, typename E >
ConstNodeIterator<N,E>& ConstNodeIterator<N,E>::operator++()
{
  ++m_iterator;
  return *this;
}

template< typename N, typename E >
ConstNodeIterator<N,E> ConstNodeIterator<N,E>::operator++( int )
{
  ConstNodeIterator toReturn( *this );
  ++( *this );
  return toReturn;
}

template< typename N, typename E >
ConstNodeIterator<N,E>& ConstNodeIterator<N,E>::operator--()
{
  --m_iterator;
  return *this;
}

template< typename N, typename E >
ConstNodeIterator<N,E> ConstNodeIterator<N,E>::operator--( int )
{
  ConstNodeIterator toReturn( *this );
  --( *this );
  return toReturn;
}

} // namespace SimpleGraph

#endif // CONST_NODE_ITERATOR_HPP
