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

#ifndef graph_edgeiterator_h
#define graph_edgeiterator_h

#include <list>

namespace SimpleGraph {

template< typename N, typename E > class  NodeIterator;
template< typename N, typename E > class  ConstNodeIterator;
template< typename N, typename E > struct SimpleEdge;
template< typename N, typename E > class  AllEdges;

template< typename N, typename E >
class EdgeIterator
{
public:
  NodeIterator< N, E > left();
  NodeIterator< N, E > right();

  ConstNodeIterator< N, E > left()  const;
  ConstNodeIterator< N, E > right() const;

  E&            operator *();
  const E&      operator *()                      const;
  E            *operator->();
  const E      *operator->()                      const;
  bool          operator==( const EdgeIterator& ) const;
  bool          operator!=( const EdgeIterator& ) const;
  EdgeIterator& operator++();
  EdgeIterator  operator++( int );
  EdgeIterator& operator--();
  EdgeIterator  operator--( int );

//private:
  friend class AllEdges<N,E>;

  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator m_iterator;

  EdgeIterator( const typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator& );
  EdgeIterator();
};

} // namespace SimpleGraph

#endif // graph_edgeiterator_h
