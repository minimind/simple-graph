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
#include "graphvisitortest.h"
#include "../graph/graph.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace {

struct NodeVisitor
{
  void operator()( const Graph< std::string, std::string >::node_iterator& left,
                   const Graph< std::string, std::string >::node_iterator& right,
                   const Graph< std::string, std::string >::edge_iterator& edge )
  {
    m_listOfLeftVisitedNodes.push_back(  *left  );
    m_listOfRightVisitedNodes.push_back( *right );
    m_listOfVisitedEdges.push_back(      *edge  );
  }

  std::vector< std::string > m_listOfLeftVisitedNodes;
  std::vector< std::string > m_listOfRightVisitedNodes;
  std::vector< std::string > m_listOfVisitedEdges;
};

} // namespace

TEST_CASE( "Graph with visit nodes" )
{
  Graph< std::string, std::string > basicGraph;
  Graph< std::string, std::string >::node_iterator nodeF = basicGraph.add_node( std::string( "node F" ) );
  Graph< std::string, std::string >::node_iterator nodeA = basicGraph.add_node( std::string( "node A" ) );
  Graph< std::string, std::string >::node_iterator nodeC = basicGraph.add_node( std::string( "node C" ) );
  Graph< std::string, std::string >::node_iterator nodeI = basicGraph.add_node( std::string( "node I" ) );
  Graph< std::string, std::string >::node_iterator nodeD = basicGraph.add_node( std::string( "node D" ) );
  Graph< std::string, std::string >::node_iterator nodeE = basicGraph.add_node( std::string( "node E" ) );
  Graph< std::string, std::string >::node_iterator nodeH = basicGraph.add_node( std::string( "node H" ) );
  Graph< std::string, std::string >::node_iterator nodeB = basicGraph.add_node( std::string( "node B" ) );
  Graph< std::string, std::string >::node_iterator nodeG = basicGraph.add_node( std::string( "node G" ) );

  basicGraph.add_edge( std::string( "edge C..D" ), nodeC, nodeD );
  basicGraph.add_edge( std::string( "edge C..E" ), nodeC, nodeE );
  basicGraph.add_edge( std::string( "edge F..G" ), nodeF, nodeG );
  basicGraph.add_edge( std::string( "edge F..I" ), nodeF, nodeI );
  basicGraph.add_edge( std::string( "edge A..B" ), nodeA, nodeB );
  basicGraph.add_edge( std::string( "edge A..C" ), nodeA, nodeC );
  basicGraph.add_edge( std::string( "edge H..F" ), nodeH, nodeF );
  basicGraph.add_edge( std::string( "edge A..C" ), nodeA, nodeC );
  basicGraph.add_edge( std::string( "edge B..F" ), nodeB, nodeF );

  { // We'll start from node B
    NodeVisitor nodeVisitor;
    visit_edges_depth_first( nodeB, nodeVisitor );

    REQUIRE( nodeVisitor.m_listOfLeftVisitedNodes.size() == nodeVisitor.m_listOfRightVisitedNodes.size() );
    REQUIRE( nodeVisitor.m_listOfLeftVisitedNodes.size() == nodeVisitor.m_listOfVisitedEdges.size() );
    REQUIRE( !nodeVisitor.m_listOfLeftVisitedNodes.empty() );

    /*{ // DEBUG block
      fprintf( stderr, "\n\n" );
      std::vector< std::string >::const_iterator l, r, e;
      for ( l = nodeVisitor.m_listOfLeftVisitedNodes.begin(), r = nodeVisitor.m_listOfRightVisitedNodes.begin(), e = nodeVisitor.m_listOfVisitedEdges.begin();
            l != nodeVisitor.m_listOfLeftVisitedNodes.end();
            ++l, ++r, ++e )
      {
        fprintf( stderr, "%s\t%s\t%s\n", l->c_str(), e->c_str(), r->c_str() );
      }
    }*/

    std::vector< std::string > predictedLeftNodeOrder;
    predictedLeftNodeOrder.push_back(  std::string( "node B" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node B" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node A" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node C" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node C" ) );

    std::vector< std::string > predictedRightNodeOrder;
    predictedRightNodeOrder.push_back( std::string( "node F" ) );
    predictedRightNodeOrder.push_back( std::string( "node H" ) );
    predictedRightNodeOrder.push_back( std::string( "node I" ) );
    predictedRightNodeOrder.push_back( std::string( "node G" ) );
    predictedRightNodeOrder.push_back( std::string( "node A" ) );
    predictedRightNodeOrder.push_back( std::string( "node C" ) );
    predictedRightNodeOrder.push_back( std::string( "node E" ) );
    predictedRightNodeOrder.push_back( std::string( "node D" ) );

    std::vector< std::string > predictedEdgeOrder;
    predictedEdgeOrder.push_back(      std::string( "edge B..F" ) );
    predictedEdgeOrder.push_back(      std::string( "edge H..F" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..I" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..G" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..B" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..C" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..E" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..D" ) );

    REQUIRE( predictedLeftNodeOrder == nodeVisitor.m_listOfLeftVisitedNodes );
    REQUIRE( predictedRightNodeOrder == nodeVisitor.m_listOfRightVisitedNodes );
    REQUIRE( predictedEdgeOrder == nodeVisitor.m_listOfVisitedEdges );
  }

  { // We'll start from node D
    NodeVisitor nodeVisitor;
    visit_edges_depth_first( nodeD, nodeVisitor );

    REQUIRE( nodeVisitor.m_listOfLeftVisitedNodes.size() == nodeVisitor.m_listOfRightVisitedNodes.size() );
    REQUIRE( nodeVisitor.m_listOfLeftVisitedNodes.size() == nodeVisitor.m_listOfVisitedEdges.size() );
    REQUIRE( !nodeVisitor.m_listOfLeftVisitedNodes.empty() );

    /*{ // DEBUG block
      fprintf( stderr, "\n\n" );
      std::vector< std::string >::const_iterator l, r, e;
      for ( l = nodeVisitor.m_listOfLeftVisitedNodes.begin(), r = nodeVisitor.m_listOfRightVisitedNodes.begin(), e = nodeVisitor.m_listOfVisitedEdges.begin();
            l != nodeVisitor.m_listOfLeftVisitedNodes.end();
            ++l, ++r, ++e )
      {
        fprintf( stderr, "%s\t%s\t%s\n", l->c_str(), e->c_str(), r->c_str() );
      }
    }*/

    std::vector< std::string > predictedLeftNodeOrder;
    predictedLeftNodeOrder.push_back(  std::string( "node D" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node C" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node A" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node B" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node C" ) );

    std::vector< std::string > predictedRightNodeOrder;
    predictedRightNodeOrder.push_back( std::string( "node C" ) );
    predictedRightNodeOrder.push_back( std::string( "node A" ) );
    predictedRightNodeOrder.push_back( std::string( "node B" ) );
    predictedRightNodeOrder.push_back( std::string( "node F" ) );
    predictedRightNodeOrder.push_back( std::string( "node H" ) );
    predictedRightNodeOrder.push_back( std::string( "node I" ) );
    predictedRightNodeOrder.push_back( std::string( "node G" ) );
    predictedRightNodeOrder.push_back( std::string( "node E" ) );

    std::vector< std::string > predictedEdgeOrder;
    predictedEdgeOrder.push_back(      std::string( "edge C..D" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..C" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..B" ) );
    predictedEdgeOrder.push_back(      std::string( "edge B..F" ) );
    predictedEdgeOrder.push_back(      std::string( "edge H..F" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..I" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..G" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..E" ) );

    REQUIRE( predictedLeftNodeOrder == nodeVisitor.m_listOfLeftVisitedNodes );
    REQUIRE ( predictedRightNodeOrder == nodeVisitor.m_listOfRightVisitedNodes );
    REQUIRE( predictedEdgeOrder == nodeVisitor.m_listOfVisitedEdges );
  }
}

void ensureGraphVisitorTestLink()
{
}
