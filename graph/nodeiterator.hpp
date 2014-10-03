#ifndef NODE_ITERATOR_HPP
#define NODE_ITERATOR_HPP

#include "nodeiterator.h"
#include "edgeiterator.h"

namespace SimpleGraph {

template< typename N, typename E >
NodeIterator<N,E>::NodeIterator( const typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::iterator& i )
  : m_iterator( i )
{
}

template< typename N, typename E >
NodeIterator<N,E>::NodeIterator()
{
}

template< typename N, typename E >
EdgeIterator< N, E > NodeIterator<N,E>::begin()
{
  return EdgeIterator< N, E >( m_iterator->second->m_edges.begin() );
}

template< typename N, typename E >
EdgeIterator< N, E > NodeIterator<N,E>::end()
{
  return EdgeIterator< N, E >( m_iterator->second->m_edges.end() );
}

template< typename N, typename E >
unsigned long NodeIterator<N,E>::key() const
{
  return m_iterator->first;
}

template< typename N, typename E >
size_t NodeIterator<N,E>::size() const
{
  return m_iterator->second->m_edges.size();
}

template< typename N, typename E >
bool NodeIterator<N,E>::empty() const
{
  return m_iterator->second->m_edges.empty();
}

template< typename N, typename E >
N& NodeIterator<N,E>::operator *()
{
  return m_iterator->second->m_object;
}

template< typename N, typename E >
const N& NodeIterator<N,E>::operator *() const
{
  return m_iterator->second->m_object;
}

template< typename N, typename E >
N *NodeIterator<N,E>::operator->()
{
  return &( m_iterator->second->m_object );
}

template< typename N, typename E >
const N *NodeIterator<N,E>::operator->() const
{
  return &( m_iterator->second->m_object );
}

template< typename N, typename E >
bool NodeIterator<N,E>::operator==( const NodeIterator& n ) const
{
  return m_iterator == n.m_iterator;
}

template< typename N, typename E >
bool NodeIterator<N,E>::operator!=( const NodeIterator& n ) const
{
  return m_iterator != n.m_iterator;
}

template< typename N, typename E >
NodeIterator<N,E>& NodeIterator<N,E>::operator++()
{
  ++m_iterator;
  return *this;
}

template< typename N, typename E >
NodeIterator<N,E> NodeIterator<N,E>::operator++( int )
{
  NodeIterator toReturn( *this );
  ++( *this );
  return toReturn;
}

template< typename N, typename E >
NodeIterator<N,E>& NodeIterator<N,E>::operator--()
{
  --m_iterator;
  return *this;
}

template< typename N, typename E >
NodeIterator<N,E> NodeIterator<N,E>::operator--( int )
{
  NodeIterator toReturn( *this );
  --( *this );
  return toReturn;
}

} // namespace SimpleGraph

#endif // NODE_ITERATOR_HPP
