#ifndef agents_arachnidutils_graph_constnodeiterator_h
#define agents_arachnidutils_graph_constnodeiterator_h

#include <set>
#include <map>
#include <boost/shared_ptr.hpp>

namespace SimpleGraph {

template< typename N, typename E > class  ConstEdgeIterator;
template< typename N, typename E > struct SimpleNode;
template< typename N, typename E > class  AllNodes;
template< typename N, typename E > class  Graph;

template< typename N, typename E >
class ConstNodeIterator
{
public:
  ConstEdgeIterator< N, E > begin();
  ConstEdgeIterator< N, E > end();
  unsigned long             key()                           const;
  size_t                    size()                          const;
  bool                      empty()                         const;

  const N&           operator *()                           const;
  const N           *operator->()                           const;
  bool               operator==( const NodeIterator<N,E>& ) const;
  bool               operator==( const ConstNodeIterator& ) const;
  bool               operator!=( const NodeIterator<N,E>& ) const;
  bool               operator!=( const ConstNodeIterator& ) const;
  ConstNodeIterator& operator++();
  ConstNodeIterator  operator++( int );
  ConstNodeIterator& operator--();
  ConstNodeIterator  operator--( int );

//private:
  friend class Graph< N, E >;
  friend class AllNodes< N, E >;

  typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::const_iterator m_iterator;

  ConstNodeIterator( const typename std::map< unsigned long, boost::shared_ptr< SimpleNode<N,E> > >::const_iterator& );
  ConstNodeIterator( const NodeIterator<N,E>& );
  ConstNodeIterator();
};

} // namespace SimpleGraph

#endif // agents_arachnidutils_graph_constnodeiterator_h
