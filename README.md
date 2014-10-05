# Graph

## Introduction

The `graph` project is a straightforward C++ graph template class with all
the usual STL-style iterators. It compiles on recent versions of GNU c++,
clang, XCode, and Visual C++.

To install, simply copy the `graph` directory somewhere on your `include` path.

To compile and run on a UNIX-style machine, do:

```bash
make
./test_graph
```
If all goes well, you should get back:

```bash
====================================================
All tests passed (123 assertions in 8 test cases)
```

## Usage

### Construction

You create a graph by specifying the node and edge type.

```c++
#include "graph/graph.h"

...

// create a graph whose nodes and edges are strings
Graph< std::string, std::string > basicGraph;

// add some nodes
Graph< std::string, std::string >::node_iterator node1 = basicGraph.add_node( std::string( "node 1" ) );
Graph< std::string, std::string >::node_iterator node2 = basicGraph.add_node( std::string( "node 2" ) );
Graph< std::string, std::string >::node_iterator node3 = basicGraph.add_node( std::string( "node 3" ) );

// add two edges connecting the nodes
basicGraph.add_edge( std::string( "edge 1" ), node1, node2 );
basicGraph.add_edge( std::string( "edge 2" ), node1, node3 );
```

### Utility functions

```c++
const size_t noOfNodes = basicGraph.nodes.size();
const size_t noOfEdges = basicGraph.edges.size();

```

### Iterating through the nodes and edges

```c++
// visit all the nodes
for ( Graph< std::string, std::string >::node_iterator i = basicGraph.nodes.begin();
      i != basicGraph.nodes.end();
      ++i )
{
  cout << "Node is " << *i
       << " and has " << (*i)->size() << " edges. "
       << std::endl;
}

// visit all the edges
for ( Graph< std::string, std::string >::edge_iterator j = basicGraph.edges.begin();
      j != basicGraph.edges.end();
      ++j )
{
  cout << "Edge connects nodes "
       << *((*j)->left)
       << " and "
       << *((*j)->right)
       << std::endl;
}
```

### Visitor classes

```c++
struct NodeVisitor
{
  void operator()( const Graph< std::string, std::string >::node_iterator& left,
                   const Graph< std::string, std::string >::node_iterator& right,
                   const Graph< std::string, std::string >::edge_iterator& edge )
  {
    cout << "Connection between " << *left << " and " << *right << std::endl;
  }
} nodeVisitor;

visit_edges_depth_first( basicGraph.nodes.begin(), nodeVisitor );
```

## MIT License

The MIT License (MIT)

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

