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

#ifndef graph_allnodes_hpp
#define graph_allnodes_hpp

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

#endif // graph_allnodes_hpp
