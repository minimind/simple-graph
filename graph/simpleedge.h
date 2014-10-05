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

#ifndef graph_simpleedge_h
#define graph_simpleedge_h

#include <boost/shared_ptr.hpp>
#include <list>

namespace SimpleGraph {

template< typename N, typename E > class NodeIterator;

template< typename N, typename E >
struct SimpleEdge
{
  SimpleEdge( const E& object, NodeIterator<N,E>& left, NodeIterator<N,E>& right )
    : m_object( object )
    , m_left(   left   )
    , m_right(  right  )
  {
  }

  E                                                                                 m_object;
  NodeIterator<N,E>                                                                 m_left;
  NodeIterator<N,E>                                                                 m_right;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_mainIterator;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_leftIterator;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_rightIterator;
};

} // namespace SimpleGraph

#endif // graph_simpleedge_h
