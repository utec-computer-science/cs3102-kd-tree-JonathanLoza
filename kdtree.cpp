#include <iostream>
#include <vector>
#include <cstdarg>
#define N_DIM 2


template <typename T,int k>
class KdNode{
  public:
    typedef T value_t;
    typedef std::vector<value_t> point; 

    std::size_t dimension;
    

    KdNode():dimension(k){};

    void insert(point container){
    }

    bool find(point val){
      return false;
    }
};

template <typename T,int k>
class KdTree{
  public:
    typedef typename KdNode<T,k>::value_t value_t;
    typedef typename KdNode<T,k>::point point;
  
    KdNode<T,k> *root;

    KdTree(void){
      root = new KdNode<T,k>();
    }
    void insert(value_t val ...){
      point container;
      container.push_back(val);
      va_list args;
      va_start(args,val);
      for(int i=0;i<k;i++){
        container.push_back(va_arg(args,value_t));
      }
      va_end(args);
      root->insert(container);
    }
    bool find(const point val){
      return root.find(val);
    }

    ~KdTree(void){}


};


int main(){
  KdTree<int,N_DIM> tree;
  tree.insert(5,6,7);
  return 0;
};
