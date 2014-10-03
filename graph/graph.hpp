#ifndef SIMPLE_GRAPH_HPP
#define SIMPLE_GRAPH_HPP

#include "graph.h"
#include "simpleedge.h"
#include "simplenode.h"
#include "nodeiterator.h"
#include "graphcopyfunctor.h"
#include <stack>
#include <map>
#include <stdexcept>

template< typename N, typename E >
Graph<N,E>::Graph()
  : m_counter( 0 )
{
}

template< typename N, typename E >
Graph<N,E>::Graph( const Graph<N,E>& originalGraph )
{
  GraphCopyFunctor<N,E> copyFunctor;
  hidden_copy_topology( *this, originalGraph, copyFunctor );
}

template< typename N, typename E >
Graph<N,E>& Graph<N,E>::operator=( const Graph<N,E>& originalGraph )
{
  if ( this != &originalGraph )
  {
    clear();

    GraphCopyFunctor<N,E> copyFunctor;
    hidden_copy_topology( *this, originalGraph, copyFunctor );
  }

  return *this;
}

template< typename N, typename E >
typename Graph<N,E>::node_iterator Graph<N,E>::add_node( const N& n )
{
  return hidden_add_node( n, m_counter++ );
}

template< typename N, typename E >
typename Graph<N,E>::node_iterator Graph<N,E>::add_node( const N& n, const unsigned long key )
{
  if ( nodes.m_nodes.find( key ) != nodes.m_nodes.end() )
  {
    throw std::runtime_error( "Key already exists in graph" );
  }
  else if ( key >= m_counter )
  {
    m_counter = key + 1;
  }

  return hidden_add_node( n, key );
}

template< typename N, typename E >
typename Graph<N,E>::node_iterator Graph<N,E>::hidden_add_node( const N& n, const unsigned long key )
{
  std::pair< typename std::map< unsigned long, boost::shared_ptr< SimpleGraph::SimpleNode<N,E> > >::iterator, bool > toReturn =
    nodes.m_nodes.insert( std::make_pair( key, boost::shared_ptr< SimpleGraph::SimpleNode<N,E> >( new SimpleGraph::SimpleNode<N,E>( n, key ) ) ) );

  return SimpleGraph::NodeIterator<N,E>( toReturn.first );
}

template< typename N, typename E >
void Graph<N,E>::add_edge( const E& e, typename Graph<N,E>::node_iterator& left, typename Graph<N,E>::node_iterator& right )
{
  if ( left.key() == right.key() )
  {
    throw std::runtime_error( "Cannot add_edge linking a node to itself" );
  }

  boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > newEdge( new SimpleGraph::SimpleEdge<N,E>( e, left, right ) );

  edges.m_edges.push_back( newEdge );
  newEdge->m_mainIterator = edges.m_edges.end();
  --( newEdge->m_mainIterator );

  left.m_iterator->second->m_edges.push_back( newEdge );
  newEdge->m_leftIterator = left.m_iterator->second->m_edges.end();
  --( newEdge->m_leftIterator );

  right.m_iterator->second->m_edges.push_back( newEdge );
  newEdge->m_rightIterator = right.m_iterator->second->m_edges.end();
  --( newEdge->m_rightIterator );
}

template< typename N, typename E >
typename Graph<N,E>::node_iterator Graph<N,E>::remove_node( typename Graph<N,E>::node_iterator& n )
{
  // You can only remove a node it it has no edges in it
  if ( !n.m_iterator->second->m_edges.empty() )
  {
    throw std::runtime_error( "Cannot remove a node if it is still connected by an edge" );
  }

  typename Graph<N,E>::node_iterator toReturn = n;
  ++toReturn;

  nodes.m_nodes.erase( n.m_iterator );
  return toReturn;
}

template< typename N, typename E >
typename Graph<N,E>::edge_iterator Graph<N,E>::remove_edge( typename Graph<N,E>::edge_iterator& e )
{
  typename boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> >& simpleEdge( *( e.m_iterator ) );
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator mainIterator  = simpleEdge->m_mainIterator;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator leftIterator  = simpleEdge->m_leftIterator;
  typename std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >::iterator rightIterator = simpleEdge->m_rightIterator;

  bool leftAndRightTheSame = &( *leftIterator ) == &( *rightIterator );
  bool leftAndMainTheSame  = &( *mainIterator ) == &( *leftIterator  );
  bool rightAndMainTheSame = &( *mainIterator ) == &( *rightIterator );

  typename Graph<N,E>::edge_iterator toReturn( mainIterator );
  ++toReturn;

  std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >& eLeftIteratorEdges  = e.left().m_iterator->second->m_edges;
  std::list< boost::shared_ptr< SimpleGraph::SimpleEdge<N,E> > >& eRightIteratorEdges = e.right().m_iterator->second->m_edges;

  eLeftIteratorEdges.erase( leftIterator );

  if ( !leftAndRightTheSame )
  {
    eRightIteratorEdges.erase( rightIterator );
  }

  if ( !leftAndMainTheSame && !( rightAndMainTheSame && !leftAndRightTheSame ) )
  {
    edges.m_edges.erase( mainIterator );
  }

  return toReturn;
}

template< typename N, typename E >
void Graph<N,E>::clear()
{
  nodes.m_nodes.clear();
  edges.m_edges.clear();
  m_counter = 0;
}

template< typename I, typename J >
void add_edges_to_stack( typename std::stack< std::pair< unsigned long, J > >& nodeKeysToVisit,
                         I&                                                    node,
                         const unsigned long                                   keyToIgnore )
{
  for ( J i = node.begin(); i != node.end(); ++i )
  {
    if ( i.left().key() != keyToIgnore && i.right().key() != keyToIgnore )
    {
      nodeKeysToVisit.push( std::make_pair( node.key(), i ) );
    }
  }
}

template< typename F, typename I, typename J >
void visit_edges_depth_first_hidden( I head, F& visitor, const unsigned long keyToIgnore )
{
  if ( head.key() == keyToIgnore )
  {
    return;
  }

  std::set< unsigned long >                            visitedNodes;
  typename std::stack< std::pair< unsigned long, J > > nodeKeysToVisit;

  add_edges_to_stack( nodeKeysToVisit, head, keyToIgnore );
  visitedNodes.insert( head.key() );

  while ( !nodeKeysToVisit.empty() )
  {
    std::pair< unsigned long, J > currentEdge = nodeKeysToVisit.top();
    nodeKeysToVisit.pop();

    const unsigned long currentNodeKey = currentEdge.first;
    I realLeft  = currentEdge.second.left();
    I realRight = currentEdge.second.right();

    if ( realLeft.key() != currentNodeKey )
    {
      std::swap( realLeft, realRight );
    }

    // Might need to visit the real right node...
    if ( visitedNodes.find( realRight.key() ) == visitedNodes.end() &&
         realLeft.key()  != keyToIgnore                             &&
         realRight.key() != keyToIgnore )
    {
      // We do have to visit this node...
      // Actually perform the user code
      visitor( realLeft, realRight, currentEdge.second );
      visitedNodes.insert( currentNodeKey );
      add_edges_to_stack( nodeKeysToVisit, realRight, keyToIgnore );
    }
  }
}

template< typename N, typename E, typename F >
void visit_edges_depth_first( SimpleGraph::NodeIterator<N,E> head, F& visitor )
{
  visit_edges_depth_first_hidden< F, SimpleGraph::NodeIterator<N,E>, SimpleGraph::EdgeIterator<N,E> >( head, visitor, -1 );
}

template< typename N, typename E, typename F >
void visit_edges_depth_first( SimpleGraph::ConstNodeIterator<N,E> head, F& visitor )
{
  visit_edges_depth_first_hidden< F, SimpleGraph::ConstNodeIterator<N,E>, SimpleGraph::ConstEdgeIterator<N,E> >( head, visitor, -1 );
}

template< typename N, typename E, typename F >
void visit_edges_depth_first_ignore_key( SimpleGraph::NodeIterator<N,E> head, F& visitor, const unsigned long keyToIgnore )
{
  visit_edges_depth_first_hidden< F, SimpleGraph::NodeIterator<N,E>, SimpleGraph::EdgeIterator<N,E> >( head, visitor, keyToIgnore );
}

template< typename N, typename E, typename F >
void visit_edges_depth_first_ignore_key( SimpleGraph::ConstNodeIterator<N,E> head, F& visitor, const unsigned long keyToIgnore )
{
  visit_edges_depth_first_hidden< F, SimpleGraph::ConstNodeIterator<N,E>, SimpleGraph::ConstEdgeIterator<N,E> >( head, visitor, keyToIgnore );
}

template< typename N, typename E, typename F >
void hidden_copy_topology( Graph< typename F::node_type, typename F::edge_type >& toReturn,
                           const Graph<N,E>&                                      originalGraph,
                           F&                                                     creator )
{
  // We need to go through all the nodes and edges, using the function to copy them.
  for ( typename SimpleGraph::ConstNodeIterator<N,E> i = originalGraph.nodes.begin();
        i != originalGraph.nodes.end();
        ++i )
  {
    toReturn.nodes.m_nodes.insert( std::make_pair(
        i.key(),
        boost::shared_ptr< SimpleGraph::SimpleNode< typename F::node_type, typename F::edge_type > >
          ( new SimpleGraph::SimpleNode< typename F::node_type, typename F::edge_type >( creator( i ), i.key() ) )
      )
    );
  }

  for ( typename SimpleGraph::ConstEdgeIterator<N,E> j = originalGraph.edges.begin();
        j != originalGraph.edges.end();
        ++j )
  {
    typename SimpleGraph::NodeIterator< typename F::node_type, typename F::edge_type > left = toReturn.nodes.find( j.left().key() );
    if ( left == toReturn.nodes.end() )
    {
      throw std::runtime_error( "Cannot copy graph as cannot find left node" );
    }

    typename SimpleGraph::NodeIterator< typename F::node_type, typename F::edge_type > right = toReturn.nodes.find( j.right().key() );
    if ( right == toReturn.nodes.end() )
    {
      throw std::runtime_error( "Cannot copy graph as cannot find right node" );
    }

    toReturn.add_edge( creator( j, left, right ), left, right );
  }

  toReturn.m_counter = originalGraph.m_counter;
}

template< typename N, typename E, typename F >
Graph< typename F::node_type, typename F::edge_type > *copy_topology( const Graph<N,E>& originalGraph, F& creator )
{
  // We need to go through all the nodes and edges, using the function to copy them.
  std::auto_ptr< Graph< typename F::node_type, typename F::edge_type > > toReturn( new Graph< typename F::node_type, typename F::edge_type >() );

  hidden_copy_topology( *toReturn, originalGraph, creator );

  return toReturn.release();
}

template< typename N, typename E, typename F >
void copy_topology_to_local( Graph< typename F::node_type, typename F::edge_type >& newGraph,
                             const Graph<N,E>&                                      originalGraph,
                             F&                                                     creator )
{
  newGraph.clear();
  hidden_copy_topology( newGraph, originalGraph, creator );
}

template< typename N, typename E >
void add( Graph<N,E>& a, const Graph<N,E>& b, const bool keepSameKeys )
{
  const unsigned long keyAdd = keepSameKeys ? 0 : a.m_counter;

  // The problem here is that the keys might change. So we need to create new keys and hence new node iterators in the edges.
  // We do this by going through all the nodes and edges and adding a.m_counter to all the keys.
  for ( typename SimpleGraph::ConstNodeIterator<N,E> i = b.nodes.begin();
        i != b.nodes.end();
        ++i )
  {
    if ( a.nodes.m_nodes.find( i.key() + keyAdd ) != a.nodes.m_nodes.end() )
    {
      throw std::runtime_error( "Cannot add node as key already exists" );
    }

    a.nodes.m_nodes.insert( std::make_pair(
      i.key() + keyAdd,
      boost::shared_ptr< SimpleGraph::SimpleNode<N,E> >( new SimpleGraph::SimpleNode<N,E>( *i, i.key() + keyAdd ) ) ) );
  }

  // Now we copy the edges
  for ( typename SimpleGraph::ConstEdgeIterator<N,E> j = b.edges.begin();
        j != b.edges.end();
        ++j )
  {
    typename SimpleGraph::NodeIterator<N,E> left = a.nodes.find( j.left().key() + keyAdd );
    if ( left == a.nodes.end() )
    {
      throw std::runtime_error( "Cannot copy graph as cannot find left node" );
    }

    typename SimpleGraph::NodeIterator<N,E> right = a.nodes.find( j.right().key() + keyAdd );
    if ( right == a.nodes.end() )
    {
      throw std::runtime_error( "Cannot copy graph as cannot find right node" );
    }

    a.add_edge( *j, left, right );
  }

  if ( keepSameKeys )
  {
    if ( a.m_counter < b.m_counter )
    {
      a.m_counter = b.m_counter;
    }
  }
  else
  {
    a.m_counter += b.m_counter;
  }
}

#endif // SIMPLE_GRAPH_HPP
