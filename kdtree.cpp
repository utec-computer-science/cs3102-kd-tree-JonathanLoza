#include <iostream>
#include <vector>
#include <cstdarg>
#define N_DIM 2


template <typename T,int k>
class KdNode{
  public:
    typedef T value_t;
    typedef std::vector<value_t> point; 
    
    point v_point; 
    int dimension;
    KdNode* right;
    KdNode* left;

    KdNode(point _v_point):v_point(_v_point),
      dimension(k),right(nullptr),left(nullptr){};


    bool find(point val,int actualDimension){
      if(equals(val))
        return true;
      KdNode *temp=nullptr;
      if(actualDimension == k) actualDimension=0;
      if(v_point[actualDimension]>val[actualDimension])
        temp=left;  
      else
        temp=right;
      if(!temp)
        return false;
      return temp->find(val,actualDimension++);
    }
    bool equals( point x_point){
      for(int i=0;i<k;i++){
        if(this->v_point[i]!=x_point[i])
          return false;
      }
      return true;
    }

    void printValues(){
      for(value_t val: v_point)
        std::cout<<val<<" ";
      std::cout<<std::endl;
    }
};

template <typename T,int k>
class KdTree{
  public:
    typedef typename KdNode<T,k>::value_t value_t;
    typedef typename KdNode<T,k>::point point;
  
    KdNode<T,k> *root;

    KdTree(void){
      root = nullptr;
    }

    void insert(value_t val ...){
      point container;
      container.push_back(val);
      va_list args;
      va_start(args,val);
      for(int i=1;i<k;i++){
        container.push_back(va_arg(args,value_t));
      }
      va_end(args);
      insert(container);
    }


    void insert(point newPoint){
      if(!root) {
        root = new KdNode<T,k>(newPoint);
        return;
      }
      auto temp= root;
      auto next=root;
      KdNode<T,k>* KdNode<T,k>::*ptr;
      int actualDimension=0;
      while(next){
        temp=next;
        if(temp->v_point[actualDimension]>newPoint[actualDimension]){
            next=temp->left;
            ptr=&KdNode<T,k>::left;
        }else{
            next=temp->right;
            ptr=&KdNode<T,k>::right;
        }
        actualDimension=getNextDimension(actualDimension);
      }
      temp->*ptr=new KdNode<T,k>(newPoint);
    }

    int getNextDimension(int dimension){
      if(dimension+1 == k)
        return 0;
      return dimension+1;
    }


    bool find(value_t val ...){
      point container;
      container.push_back(val);
      va_list args;
      va_start(args,val);
      for(int i=1;i<k;i++){
        container.push_back(va_arg(args,value_t));
      }
      va_end(args);
      return root->find(container,0);
    }

    void print(){
      preOrderPrint(root);
    }

    void preOrderPrint(KdNode<T,k>* node){
      if(!node){
        return;
      }
      node->printValues();
      preOrderPrint(node->left);
      preOrderPrint(node->right);
    }
    ~KdTree(void){}
};


int main(){
  KdTree<int,N_DIM> tree;
  tree.insert(3,6);
  tree.insert(2,7);
  tree.insert(17,15);
  tree.insert(6,12);
  tree.insert(13,15);
  tree.insert(9,1);
  tree.insert(10,19);
  std::cout<<"Search for point (2,7) result: "<<tree.find(2,7)<<std::endl;
  std::cout<<"Search for point (3,7) result: "<<tree.find(3,7)<<std::endl;
  tree.print();
  return 0;
};
