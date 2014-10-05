/*
Copyright (c) 2006-2014 Ian Macinnes

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef graph_constnodeiterator_hpp
#define graph_constnodeiterator_hpp

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

#endif // graph_constnodeiterator_hpp
