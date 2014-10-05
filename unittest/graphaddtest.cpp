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
#include "graphaddtest.h"
#include "../graph/graph.h"

TEST_CASE( "Graph with add_node and add_edge" )
{
  // We'll combine two graph and make sure the final graph contains all the elements we expect
  Graph< std::string, std::string > basicGraph;
  {
    Graph< std::string, std::string >::node_iterator node1 = basicGraph.add_node( std::string( "node 1" ) );
    Graph< std::string, std::string >::node_iterator node2 = basicGraph.add_node( std::string( "node 2" ) );
    Graph< std::string, std::string >::node_iterator node3 = basicGraph.add_node( std::string( "node 3" ) );

    basicGraph.add_edge( std::string( "edge 1" ), node1, node2 );
    basicGraph.add_edge( std::string( "edge 2" ), node1, node3 );
  }

  Graph< std::string, std::string > basicGraph2;
  {
    Graph< std::string, std::string >::node_iterator node4 = basicGraph2.add_node( std::string( "node 4" ) );
    Graph< std::string, std::string >::node_iterator node5 = basicGraph2.add_node( std::string( "node 5" ) );

    basicGraph2.add_edge( std::string( "edge 3" ), node4, node5 );
  }

  add( basicGraph2, basicGraph, false );

  // Now does it contain everything we expect?
  REQUIRE( basicGraph2.nodes.size() == 5 );
  REQUIRE( basicGraph2.edges.size() == 3 );

  // Check the nodes
  Graph< std::string, std::string >::node_iterator i = basicGraph2.nodes.begin();
  REQUIRE ( *i == "node 4" );
  REQUIRE ( i.key() == 0 );

  ++i;
  REQUIRE ( *i == "node 5" );
  REQUIRE( i.key() == 1 );

  ++i;
  REQUIRE( *i == "node 1" );
  REQUIRE( i.key() == 2 );

  ++i;
  REQUIRE( *i == "node 2" );
  REQUIRE( i.key() == 3 );

  ++i;
  REQUIRE( *i == "node 3" );
  REQUIRE( i.key() == 4 );

  // Check the edges
  Graph< std::string, std::string >::edge_iterator j = basicGraph2.edges.begin();
  REQUIRE( *j == "edge 3" );
  REQUIRE( j.left().key() == 0);
  REQUIRE( j.right().key() == 1 );

  ++j;
  REQUIRE( *j == "edge 1" );
  REQUIRE( j.left().key() == 2 );
  REQUIRE( j.right().key() == 3 );

  ++j;
  REQUIRE( *j == "edge 2" );
  REQUIRE( j.left().key() == 2 );
  REQUIRE( j.right().key() == 4 );
}

void ensureGraphAddTestLink()
{
}
