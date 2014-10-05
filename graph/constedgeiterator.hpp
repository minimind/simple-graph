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

#ifndef graph_constedgeiterator_hpp
#define graph_constedgeiterator_hpp

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

#endif // graph_constedgeiterator_hpp
