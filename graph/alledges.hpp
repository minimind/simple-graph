#ifndef ALL_EDGES_HPP
#define ALL_EDGES_HPP

#include "alledges.h"
#include "simpleedge.h"
#include "edgeiterator.h"
#include "constedgeiterator.h"

namespace SimpleGraph {

template< typename N, typename E >
size_t AllEdges<N,E>::size() const
{
  return m_edges.size();
}

template< typename N, typename E >
bool AllEdges<N,E>::empty() const
{
  return m_edges.empty();
}

template< typename N, typename E >
EdgeIterator<N,E> AllEdges<N,E>::begin()
{
  return EdgeIterator<N,E>( m_edges.begin() );
}

template< typename N, typename E >
ConstEdgeIterator<N,E> AllEdges<N,E>::begin() const
{
  return ConstEdgeIterator<N,E>( m_edges.begin() );
}

template< typename N, typename E >
EdgeIterator<N,E> AllEdges<N,E>::end()
{
  return EdgeIterator<N,E>( m_edges.end() );
}

template< typename N, typename E >
ConstEdgeIterator<N,E> AllEdges<N,E>::end() const
{
  return ConstEdgeIterator<N,E>( m_edges.end() );
}

} // namespace SimpleGraph

#endif // ALL_EDGES_HPP
