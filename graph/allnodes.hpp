#ifndef ALL_NODES_HPP
#define ALL_NODES_HPP

#include "allnodes.h"
#include "simplenode.h"
#include "nodeiterator.h"
#include "constnodeiterator.h"

namespace SimpleGraph {

template< typename N, typename E >
size_t AllNodes<N,E>::size() const
{
  return m_nodes.size();
}

template< typename N, typename E >
bool AllNodes<N,E>::empty() const
{
  return m_nodes.empty();
}

template< typename N, typename E >
NodeIterator<N,E> AllNodes<N,E>::begin()
{
  return NodeIterator<N,E>( m_nodes.begin() );
}

template< typename N, typename E >
ConstNodeIterator<N,E> AllNodes<N,E>::begin() const
{
  return ConstNodeIterator<N,E>( m_nodes.begin() );
}

template< typename N, typename E >
NodeIterator<N,E> AllNodes<N,E>::end()
{
  return NodeIterator<N,E>( m_nodes.end() );
}

template< typename N, typename E >
ConstNodeIterator<N,E> AllNodes<N,E>::end() const
{
  return ConstNodeIterator<N,E>( m_nodes.end() );
}

template< typename N, typename E >
NodeIterator< N, E > AllNodes<N,E>::find( unsigned long i )
{
  return NodeIterator< N, E >( m_nodes.find( i ) );
}

template< typename N, typename E >
ConstNodeIterator< N, E > AllNodes<N,E>::find( unsigned long i ) const
{
  return ConstNodeIterator< N, E >( m_nodes.find( i ) );
}

} // namespace SimpleGraph

#endif // ALL_NODES_HPP
