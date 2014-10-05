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

#ifndef graph_graph_h
#define graph_graph_h

#include "nodeiterator.h"
#include "edgeiterator.h"
#include "constnodeiterator.h"
#include "constedgeiterator.h"
#include "allnodes.h"
#include "alledges.h"

template< typename N, typename E >
class Graph
{
public:
  typedef SimpleGraph::NodeIterator<N,E>      node_iterator;
  typedef SimpleGraph::EdgeIterator<N,E>      edge_iterator;
  typedef SimpleGraph::ConstNodeIterator<N,E> const_node_iterator;
  typedef SimpleGraph::ConstEdgeIterator<N,E> const_edge_iterator;

  Graph();
  Graph( const Graph<N,E>& );
  Graph& operator=( const Graph<N,E>& );

  node_iterator add_node(    const N& );
  node_iterator add_node(    const N&, const unsigned long key );
  void          add_edge(    const E&, node_iterator&, node_iterator& );
  node_iterator remove_node( node_iterator& );
  edge_iterator remove_edge( edge_iterator& );
  void          clear();

  SimpleGraph::AllNodes<N,E> nodes;
  SimpleGraph::AllEdges<N,E> edges;

  unsigned long m_counter;

private:
  SimpleGraph::NodeIterator<N,E> hidden_add_node( const N&, const unsigned long key );
};

template< typename N, typename E, typename F >
void visit_edges_depth_first( SimpleGraph::NodeIterator<N,E>, F& );

template< typename N, typename E, typename F >
void visit_edges_depth_first( SimpleGraph::ConstNodeIterator<N,E>, F& );

template< typename N, typename E, typename F >
void visit_edges_depth_first_ignore_key( SimpleGraph::NodeIterator<N,E>, F&, const unsigned long );

template< typename N, typename E, typename F >
void visit_edges_depth_first_ignore_key( SimpleGraph::ConstNodeIterator<N,E>, F&, const unsigned long );

template< typename N, typename E >
void add( Graph<N,E>&, const Graph<N,E>&, const bool keepSameKeys );

template< typename N, typename E, typename F >
void hidden_copy_topology( Graph< typename F::node_type, typename F::edge_type >&, const Graph<N,E>&, F& );

template< typename N, typename E, typename F >
Graph< typename F::node_type, typename F::edge_type > *copy_topology( const Graph<N,E>&, F& );

template< typename N, typename E, typename F >
void copy_topology_to_local( Graph< typename F::node_type, typename F::edge_type >&, const Graph<N,E>&, F& );

#include "graph.hpp"
#include "nodeiterator.hpp"
#include "edgeiterator.hpp"
#include "constnodeiterator.hpp"
#include "constedgeiterator.hpp"
#include "allnodes.hpp"
#include "alledges.hpp"

#endif // graph_graph_h
