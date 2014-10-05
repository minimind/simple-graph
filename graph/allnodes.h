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

#ifndef graph_allnodes_h
#define graph_allnodes_h

#include <map>
#include <boost/shared_ptr.hpp>
#include "simplenode.h"

template< typename N, typename E > class Graph;

namespace SimpleGraph {

template< typename N, typename E > class NodeIterator;
template< typename N, typename E > class ConstNodeIterator;

template< typename N, typename E >
class AllNodes
{
public:
  size_t                    size()                const;
  bool                      empty()               const;
  NodeIterator< N, E >      begin();
  ConstNodeIterator< N, E > begin()               const;
  NodeIterator< N, E >      end();
  ConstNodeIterator< N, E > end()                 const;
  NodeIterator< N, E >      find( unsigned long );
  ConstNodeIterator< N, E > find( unsigned long ) const;

//private:
  friend class Graph< N, E >;

  typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > > m_nodes;
};

} // namespace SimpleGraph

#endif // graph_allnodes_h
