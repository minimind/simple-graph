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

#ifndef graph_alledges_hpp
#define graph_alledges_hpp

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

#endif // graph_alledges_hpp
