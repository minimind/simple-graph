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

#ifndef graph_constedgeiterator_h
#define graph_constedgeiterator_h

#include <list>

namespace SimpleGraph {

template< typename N, typename E > class  ConstNodeIterator;
template< typename N, typename E > struct SimpleEdge;
template< typename N, typename E > class  AllEdges;
template< typename N, typename E > class  EdgeIterator;

template< typename N, typename E >
class ConstEdgeIterator
{
public:
  ConstNodeIterator< N, E > left()  const;
  ConstNodeIterator< N, E > right() const;

  const E&            operator *()                           const;
  const E            *operator->()                           const;
  bool                operator==( const EdgeIterator<N,E>& ) const;
  bool                operator==( const ConstEdgeIterator& ) const;
  bool                operator!=( const EdgeIterator<N,E>& ) const;
  bool                operator!=( const ConstEdgeIterator& ) const;
  ConstEdgeIterator&  operator++();
  ConstEdgeIterator   operator++( int );
  ConstEdgeIterator&  operator--();
  ConstEdgeIterator   operator--( int );

//private:
  friend class AllEdges<N,E>;

  typename std::list< boost::shared_ptr< SimpleEdge<N,E> > >::const_iterator m_iterator;

  ConstEdgeIterator( const typename std::list< boost::shared_ptr< SimpleEdge<N,E> > >::const_iterator& );
  ConstEdgeIterator( const EdgeIterator<N,E>& );
};

} // namespace SimpleGraph

#endif // graph_constedgeiterator_h
