#ifndef agents_arachnidutils_graph_nodeiterator_h
#define agents_arachnidutils_graph_nodeiterator_h

#include <set>
#include <map>
#include <boost/shared_ptr.hpp>

namespace SimpleGraph {

template< typename N, typename E > class  EdgeIterator;
template< typename N, typename E > struct SimpleNode;
template< typename N, typename E > class  AllNodes;
template< typename N, typename E > class  Graph;

template< typename N, typename E >
class NodeIterator
{
public:
  EdgeIterator< N, E > begin();
  EdgeIterator< N, E > end();
  unsigned long        key()                      const;
  size_t               size()                     const;
  bool                 empty()                    const;

  N&            operator *();
  const N&      operator *()                      const;
  N            *operator->();
  const N      *operator->()                      const;
  bool          operator==( const NodeIterator& ) const;
  bool          operator!=( const NodeIterator& ) const;
  NodeIterator& operator++();
  NodeIterator  operator++( int );
  NodeIterator& operator--();
  NodeIterator  operator--( int );

//private:
  friend class Graph< N, E >;
  friend class AllNodes< N, E >;

  typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::iterator m_iterator;

  NodeIterator( const typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::iterator& );
  NodeIterator();
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_nodeiterator_h
