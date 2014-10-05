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

#include "catch.hpp"
#include "graphconstructiontest.h"
#include "../graph/graph.h"
#include <string>
#include <vector>

TEST_CASE( "Graph with construction 1" )
{
  Graph< std::string, std::string > basicGraph;
  Graph< std::string, std::string >::node_iterator node1 = basicGraph.add_node( std::string( "node 1" ) );
  Graph< std::string, std::string >::node_iterator node2 = basicGraph.add_node( std::string( "node 2" ) );
  Graph< std::string, std::string >::node_iterator node3 = basicGraph.add_node( std::string( "node 3" ) );

  basicGraph.add_edge( std::string( "edge 1" ), node1, node2 );
  basicGraph.add_edge( std::string( "edge 2" ), node1, node3 );

  // First we'll check the nodes ///////////////////////////////////////////////////////////
  REQUIRE( basicGraph.nodes.size() == 3 );
  REQUIRE( !basicGraph.nodes.empty() );

  // First a basic test - do all the nodes exists?
  REQUIRE( node1.size() == 2 );
  REQUIRE( node2.size() == 1 );
  REQUIRE( node3.size() == 1 );

  // We'll iterate
  Graph< std::string, std::string >::node_iterator i = basicGraph.nodes.begin();
  REQUIRE( *i == "node 1" );

  ++i;
  REQUIRE( *i == "node 2" );

  i++;
  REQUIRE( *i == "node 3" );

  ++i;
  REQUIRE( i == basicGraph.nodes.end() );

  // Now we'll check the edge iterators /////////////////////////////////
  REQUIRE( basicGraph.edges.size() == 2 );
  REQUIRE( !basicGraph.edges.empty() );

  Graph< std::string, std::string >::edge_iterator j = basicGraph.edges.begin();
  REQUIRE( *j == "edge 1" );

  ++j;
  REQUIRE( *j == "edge 2" );

  j++;
  REQUIRE( j == basicGraph.edges.end() );

  // Now we'll test the 'find' command...
  const unsigned long key = node2.key();
  Graph< std::string, std::string >::node_iterator k = basicGraph.nodes.find( key );
  REQUIRE( *k == "node 2" );

  Graph< std::string, std::string >::node_iterator m = basicGraph.nodes.find( 10 );
  REQUIRE( m == basicGraph.nodes.end() );

  // Let's try the remove_node method. The first one should fail
  Graph< std::string, std::string >::node_iterator n = basicGraph.nodes.find( 0 );
  REQUIRE( n != basicGraph.nodes.end() );
  REQUIRE_THROWS( basicGraph.remove_node( n ) );

  { // Now delete the edge
    REQUIRE( basicGraph.edges.size() == 2 );

    Graph< std::string, std::string >::node_iterator n = basicGraph.nodes.find( 1 );
    REQUIRE( n.size() == 1 );
    REQUIRE( *n == "node 2" );

    Graph< std::string, std::string >::edge_iterator edgeToDelete = n.begin();
    Graph< std::string, std::string >::edge_iterator e = basicGraph.remove_edge( edgeToDelete );

    REQUIRE( basicGraph.edges.size() == 1 );

    REQUIRE( *( e.left() ) == "node 1" );
    REQUIRE( *( e.right() ) == "node 3" );
    REQUIRE( basicGraph.nodes.size() == 3 );

    Graph< std::string, std::string >::node_iterator nextNode = basicGraph.remove_node( n );

    REQUIRE( basicGraph.nodes.size() == 2 );
    REQUIRE( *nextNode == "node 3" );
  }
}

TEST_CASE( "Graph with construction 2" )
{
  boost::shared_ptr<const Graph< std::string, std::string > > basicGraph;

  {
    std::auto_ptr< Graph< std::string, std::string > > tempBasicGraph( new Graph< std::string, std::string >() );

    Graph< std::string, std::string >::node_iterator node1 = tempBasicGraph->add_node( std::string( "node 1" ) );
    Graph< std::string, std::string >::node_iterator node2 = tempBasicGraph->add_node( std::string( "node 2" ) );
    Graph< std::string, std::string >::node_iterator node3 = tempBasicGraph->add_node( std::string( "node 3" ) );

    tempBasicGraph->add_edge( std::string( "edge 1" ), node1, node2 );
    tempBasicGraph->add_edge( std::string( "edge 2" ), node1, node3 );

    basicGraph.reset( tempBasicGraph.release() );
  }

  // We'll iterate
  Graph< std::string, std::string >::const_node_iterator i = basicGraph->nodes.begin();
  REQUIRE( *i == "node 1" );

  ++i;
  REQUIRE( *i == "node 2" );

  i++;
  REQUIRE( *i == "node 3" );

  ++i;
  REQUIRE( i == basicGraph->nodes.end() );

  // Now we'll check the edge iterators /////////////////////////////////
  REQUIRE( basicGraph->edges.size() == 2 );
  REQUIRE( !basicGraph->edges.empty() );

  Graph< std::string, std::string >::const_edge_iterator j = basicGraph->edges.begin();
  REQUIRE( *j == "edge 1" );

  ++j;
  REQUIRE( *j == "edge 2" );

  j++;
  REQUIRE( j == basicGraph->edges.end() );

  // Now we'll test the 'find' command...
  const unsigned long key = 1;
  Graph< std::string, std::string >::const_node_iterator k = basicGraph->nodes.find( key );
  REQUIRE( *k == "node 2" );

  Graph< std::string, std::string >::const_node_iterator m = basicGraph->nodes.find( 10 );
  REQUIRE( m == basicGraph->nodes.end() );
}

TEST_CASE( "Graph with construction 3" )
{
  boost::shared_ptr< Graph< std::string, std::string > > basicGraph( new Graph< std::string, std::string >() );

  Graph< std::string, std::string >::node_iterator node1 = basicGraph->add_node( std::string( "node 1" ) );
  Graph< std::string, std::string >::node_iterator node2 = basicGraph->add_node( std::string( "node 2" ) );
  Graph< std::string, std::string >::node_iterator node3 = basicGraph->add_node( std::string( "node 3" ) );

  basicGraph->add_edge( std::string( "edge 1" ), node1, node2 );
  basicGraph->add_edge( std::string( "edge 2" ), node1, node3 );

  // Now we test the two parameter version of add_node
  Graph< std::string, std::string >::node_iterator node4 = basicGraph->add_node( std::string( "node 4" ), 1000 );
  REQUIRE( node4.key() == 1000 );

  Graph< std::string, std::string >::node_iterator node5 = basicGraph->add_node( std::string( "node 5" ) );
  REQUIRE( node5.key() == 1001 );

  REQUIRE_THROWS( basicGraph->add_node( std::string( "node 6" ), 1001 ) );
}

TEST_CASE( "Graph with construction 4" )
{
  // We'll check that we can easily replace nodes and edges.
  Graph< std::string, std::string > basicGraph;

  Graph< std::string, std::string >::node_iterator node1 = basicGraph.add_node( std::string( "node 1" ) );
  Graph< std::string, std::string >::node_iterator node2 = basicGraph.add_node( std::string( "node 2" ) );
  Graph< std::string, std::string >::node_iterator node3 = basicGraph.add_node( std::string( "node 3" ) );

  {
    Graph< std::string, std::string >::node_iterator i = basicGraph.nodes.begin();
    ++i;
    REQUIRE( *i == "node 2" );

    *i = "new node";
  }

  {
    Graph< std::string, std::string >::node_iterator i = basicGraph.nodes.begin();
    ++i;
    REQUIRE( *i == "new node" );
  }

  basicGraph.add_edge( std::string( "edge 1" ), node1, node2 );
  basicGraph.add_edge( std::string( "edge 2" ), node1, node3 );

  {
    Graph< std::string, std::string >::edge_iterator i = basicGraph.edges.begin();
    ++i;
    REQUIRE( *i == "edge 2" );

    *i = "new edge";
  }

  {
    Graph< std::string, std::string >::edge_iterator i = basicGraph.edges.begin();
    ++i;
    REQUIRE( *i == "new edge" );
  }
}

void ensureGraphConstructionTestLink()
{
}
