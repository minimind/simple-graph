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

#ifndef graph_constnodeiterator_h
#define graph_constnodeiterator_h

#include <set>
#include <map>
#include <boost/shared_ptr.hpp>

namespace SimpleGraph {

template< typename N, typename E > class  ConstEdgeIterator;
template< typename N, typename E > struct SimpleNode;
template< typename N, typename E > class  AllNodes;
template< typename N, typename E > class  Graph;

template< typename N, typename E >
class ConstNodeIterator
{
public:
  ConstEdgeIterator< N, E > begin();
  ConstEdgeIterator< N, E > end();
  unsigned long             key()                           const;
  size_t                    size()                          const;
  bool                      empty()                         const;

  const N&           operator *()                           const;
  const N           *operator->()                           const;
  bool               operator==( const NodeIterator<N,E>& ) const;
  bool               operator==( const ConstNodeIterator& ) const;
  bool               operator!=( const NodeIterator<N,E>& ) const;
  bool               operator!=( const ConstNodeIterator& ) const;
  ConstNodeIterator& operator++();
  ConstNodeIterator  operator++( int );
  ConstNodeIterator& operator--();
  ConstNodeIterator  operator--( int );

//private:
  friend class Graph< N, E >;
  friend class AllNodes< N, E >;

  typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::const_iterator m_iterator;

  ConstNodeIterator( const typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::const_iterator& );
  ConstNodeIterator( const NodeIterator<N,E>& );
  ConstNodeIterator();
};

} // namespace SimpleGraph

#endif // graph_constnodeiterator_h
