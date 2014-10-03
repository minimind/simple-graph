#include "catch.hpp"
#include "graphconstructiontest.h"
#include "../graph/graph.h"
#include <stdexcept>
#include <string>
#include <vector>

namespace {

class CopyFunctor
{
public:
  std::string operator()( const Graph<std::string,std::string>::const_node_iterator& n )
  {
    return *n + "_n2";
  }

  std::string operator()( const Graph<std::string,std::string>::const_edge_iterator& e,
                          const Graph<std::string,std::string>::const_node_iterator& n1,
                          const Graph<std::string,std::string>::const_node_iterator& n2 )
  {
    return *e + "_e2";
  }

  typedef std::string node_type;
  typedef std::string edge_type;
};

class DoubleString
{
public:
  DoubleString()
  {
  }

  DoubleString( const std::string& s1, const std::string& s2 )
    : m_s1( s1 )
    , m_s2( s2 )
  {
  }

  const std::string& s1() const { return m_s1; }
  const std::string& s2() const { return m_s2; }

private:
  std::string m_s1;
  std::string m_s2;
};

inline bool operator==( const DoubleString& d1, const DoubleString& d2 )
{
  return d1.s1() == d2.s1() && d1.s2() == d2.s2();
}

class CopyFunctor2
{
public:
  DoubleString operator()( const Graph< std::string, std::string >::const_node_iterator& n )
  {
    return DoubleString( *n + "_n2", *n + "_n3" );
  }

  std::string operator()( const Graph< std::string,  std::string >::const_edge_iterator&  e,  // this is of the original descriptive type
                          const Graph< DoubleString, std::string >::const_node_iterator& n1, // these both are of the new graph node type, not the old, and don't have to be const.
                          const Graph< DoubleString, std::string >::const_node_iterator& n2 )
  {
    return *e + "_e2";
  }

  typedef DoubleString node_type;
  typedef std::string  edge_type;
};

struct NodeVisitor
{
  void operator()( const Graph<std::string,std::string>::const_node_iterator& left,
                   const Graph<std::string,std::string>::const_node_iterator& right,
                   const Graph<std::string,std::string>::const_edge_iterator& edge )
  {
    m_listOfLeftVisitedNodes.push_back(  *left  );
    m_listOfRightVisitedNodes.push_back( *right );
    m_listOfVisitedEdges.push_back(      *edge  );
  }

  std::vector< std::string > m_listOfLeftVisitedNodes;
  std::vector< std::string > m_listOfRightVisitedNodes;
  std::vector< std::string > m_listOfVisitedEdges;
};

struct NodeVisitor2
{
  void operator()( const Graph<DoubleString, std::string>::const_node_iterator& left,
                   const Graph<DoubleString, std::string>::const_node_iterator& right,
                   const Graph<DoubleString, std::string>::const_edge_iterator&  edge )
  {
    m_listOfLeftVisitedNodes.push_back(  *left  );
    m_listOfRightVisitedNodes.push_back( *right );
    m_listOfVisitedEdges.push_back(      *edge  );
  }

  std::vector< DoubleString > m_listOfLeftVisitedNodes;
  std::vector< DoubleString > m_listOfRightVisitedNodes;
  std::vector< std::string >  m_listOfVisitedEdges;
};

} // namespace

TEST_CASE( "Graph with copy topology" )
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

  { // First test
    CopyFunctor copyFunctor;
    std::auto_ptr< Graph< std::string, std::string > > copiedGraph( copy_topology( basicGraph, copyFunctor ) );

    // Now we have to make sure that the copied graph is exactly what we expect
    NodeVisitor nodeVisitor;
    visit_edges_depth_first( copiedGraph->nodes.begin(), nodeVisitor );

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
    predictedLeftNodeOrder.push_back(  std::string( "node F_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node B_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node A_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node C_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node C_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F_n2" ) );
    predictedLeftNodeOrder.push_back(  std::string( "node F_n2" ) );

    std::vector< std::string > predictedRightNodeOrder;
    predictedRightNodeOrder.push_back( std::string( "node B_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node A_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node C_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node E_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node D_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node H_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node I_n2" ) );
    predictedRightNodeOrder.push_back( std::string( "node G_n2" ) );

    std::vector< std::string > predictedEdgeOrder;
    predictedEdgeOrder.push_back(      std::string( "edge B..F_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..B_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..C_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..E_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..D_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge H..F_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..I_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..G_e2" ) );

    REQUIRE( predictedLeftNodeOrder == nodeVisitor.m_listOfLeftVisitedNodes );
    REQUIRE( predictedRightNodeOrder == nodeVisitor.m_listOfRightVisitedNodes );
    REQUIRE( predictedEdgeOrder == nodeVisitor.m_listOfVisitedEdges );
  }

  { // Test 2
    CopyFunctor2 copyFunctor;
    std::auto_ptr< Graph< DoubleString, std::string > > copiedGraph( copy_topology( basicGraph, copyFunctor ) );

    // Now we have to make sure that the copied graph is exactly what we expect
    NodeVisitor2 nodeVisitor;
    visit_edges_depth_first( copiedGraph->nodes.begin(), nodeVisitor );

    /*{ // DEBUG block
      fprintf( stderr, "\n\n" );
      std::vector< DoubleString >::const_iterator l, r;
      std::vector< std::string  >::const_iterator e;
      for ( l = nodeVisitor.m_listOfLeftVisitedNodes.begin(), r = nodeVisitor.m_listOfRightVisitedNodes.begin(), e = nodeVisitor.m_listOfVisitedEdges.begin();
            l != nodeVisitor.m_listOfLeftVisitedNodes.end();
            ++l, ++r, ++e )
      {
        fprintf( stderr, "%s,%s\t%s\t%s,%s\n",
                 l->s1().c_str(), l->s2().c_str(),
                 e->c_str(),
                 r->s1().c_str(), r->s2().c_str() );
      }
    }*/

    std::vector< DoubleString > predictedLeftNodeOrder;
    predictedLeftNodeOrder.push_back(  DoubleString( "node F_n2", "node F_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node B_n2", "node B_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node A_n2", "node A_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node C_n2", "node C_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node C_n2", "node C_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node F_n2", "node F_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node F_n2", "node F_n3" ) );
    predictedLeftNodeOrder.push_back(  DoubleString( "node F_n2", "node F_n3" ) );

    std::vector< DoubleString > predictedRightNodeOrder;
    predictedRightNodeOrder.push_back( DoubleString( "node B_n2", "node B_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node A_n2", "node A_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node C_n2", "node C_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node E_n2", "node E_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node D_n2", "node D_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node H_n2", "node H_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node I_n2", "node I_n3" ) );
    predictedRightNodeOrder.push_back( DoubleString( "node G_n2", "node G_n3" ) );

    std::vector< std::string > predictedEdgeOrder;
    predictedEdgeOrder.push_back(      std::string( "edge B..F_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..B_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge A..C_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..E_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge C..D_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge H..F_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..I_e2" ) );
    predictedEdgeOrder.push_back(      std::string( "edge F..G_e2" ) );

    REQUIRE( predictedLeftNodeOrder == nodeVisitor.m_listOfLeftVisitedNodes );
    REQUIRE( predictedRightNodeOrder == nodeVisitor.m_listOfRightVisitedNodes );
    REQUIRE( predictedEdgeOrder == nodeVisitor.m_listOfVisitedEdges );
  }
}

void ensureGraphCopyTopologyTestLink()
{
}
