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

#ifndef graph_edgeiterator_hpp
#define graph_edgeiterator_hpp

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

#endif // graph_edgeiterator_hpp
