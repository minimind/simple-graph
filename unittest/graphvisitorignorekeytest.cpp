#include "catch.hpp"
#include "graphvisitorignorekeytest.h"
#include "../graph/graph.h"
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>
#include <set>

namespace {

struct NodeVisitor
{
  void operator()( const Graph< std::string, std::string >::node_iterator& left,
                   const Graph< std::string, std::string >::node_iterator& right,
                   const Graph< std::string, std::string >::edge_iterator& edge )
  {
    m_nodesVisited.insert( *left  );
    m_nodesVisited.insert( *right );
  }

  std::set< std::string > m_nodesVisited;
};

void runTest( struct NodeVisitor&                                                              nodeVisitor,
              const unsigned long                                                              nodeNo,
              const std::string&                                                               nodeToIgnore,
              const std::map< std::string, Graph< std::string, std::string >::node_iterator >& stringToIterators )
{
  std::stringstream nodeName;
  nodeName << "node " << nodeNo;

  std::map< std::string, Graph< std::string, std::string >::node_iterator >::const_iterator k = stringToIterators.find( nodeName.str() );
  REQUIRE( k != stringToIterators.end() );

  std::map< std::string, Graph< std::string, std::string >::node_iterator >::const_iterator m = stringToIterators.find( nodeToIgnore );
  REQUIRE( m != stringToIterators.end() );

  visit_edges_depth_first_ignore_key( k->second, nodeVisitor, m->second.key() );

  /*{ // DEBUG block
    std::set< std::string >::const_iterator j;
    for ( j = nodeVisitor.m_nodesVisited.begin(); j != nodeVisitor.m_nodesVisited.end(); ++j )
    {
      fprintf( stderr, "%s\n", j->c_str() );
    }
  }*/
}

} // namespace

TEST_CASE( "Graph with visit node ignore key" )
{
  // We have 6 nodes, connected in a kind of bow tie shape. We'll visit all of them, starting from different nodes,
  // but set to ignore one of the nodes in the centre of the bow tie.
  Graph< std::string, std::string > basicGraph;
  Graph< std::string, std::string >::node_iterator node4 = basicGraph.add_node( std::string( "node 4" ) );
  Graph< std::string, std::string >::node_iterator node0 = basicGraph.add_node( std::string( "node 0" ) );
  Graph< std::string, std::string >::node_iterator node3 = basicGraph.add_node( std::string( "node 3" ) );
  Graph< std::string, std::string >::node_iterator node1 = basicGraph.add_node( std::string( "node 1" ) );
  Graph< std::string, std::string >::node_iterator node5 = basicGraph.add_node( std::string( "node 5" ) );
  Graph< std::string, std::string >::node_iterator node2 = basicGraph.add_node( std::string( "node 2" ) );

  std::map< std::string, Graph< std::string, std::string >::node_iterator > stringToIterators;
  stringToIterators.insert( std::make_pair( "node 0", node0 ) );
  stringToIterators.insert( std::make_pair( "node 1", node1 ) );
  stringToIterators.insert( std::make_pair( "node 2", node2 ) );
  stringToIterators.insert( std::make_pair( "node 3", node3 ) );
  stringToIterators.insert( std::make_pair( "node 4", node4 ) );
  stringToIterators.insert( std::make_pair( "node 5", node5 ) );

  basicGraph.add_edge( std::string( "edge 1..2" ), node1, node2 );
  basicGraph.add_edge( std::string( "edge 4..3" ), node4, node3 );
  basicGraph.add_edge( std::string( "edge 0..2" ), node0, node2 );
  basicGraph.add_edge( std::string( "edge 3..5" ), node3, node5 );
  basicGraph.add_edge( std::string( "edge 3..2" ), node3, node2 );

  for ( int i = 0; i < 3; ++i )
  {
    NodeVisitor nodeVisitor;
    REQUIRE( nodeVisitor.m_nodesVisited.size() == 0 );
    
    runTest( nodeVisitor, i, "node 3", stringToIterators );
    
    REQUIRE( nodeVisitor.m_nodesVisited.size() == 3 );
    REQUIRE( nodeVisitor.m_nodesVisited.find( "node 0" ) != nodeVisitor.m_nodesVisited.end() );
    REQUIRE( nodeVisitor.m_nodesVisited.find( "node 1" ) != nodeVisitor.m_nodesVisited.end() );
    REQUIRE( nodeVisitor.m_nodesVisited.find( "node 2" ) != nodeVisitor.m_nodesVisited.end() );
  }

  for ( int i = 3; i < 6; ++i )
  {
    NodeVisitor nodeVisitor;
    runTest( nodeVisitor, i, "node 2", stringToIterators );

    REQUIRE( nodeVisitor.m_nodesVisited.size() == 3 );

    REQUIRE( nodeVisitor.m_nodesVisited.find( "node 3" ) != nodeVisitor.m_nodesVisited.end() );
    REQUIRE( nodeVisitor.m_nodesVisited.find( "node 4" ) != nodeVisitor.m_nodesVisited.end() );
    REQUIRE( nodeVisitor.m_nodesVisited.find( "node 5" ) != nodeVisitor.m_nodesVisited.end() );
  }
}

void ensureGraphVisitorIgnoreKeyTestLink()
{
}
