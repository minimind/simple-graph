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

#ifndef graph_nodeiterator_hpp
#define graph_nodeiterator_hpp

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

#endif // graph_nodeiterator_hpp
