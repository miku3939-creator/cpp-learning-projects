#include<iostream>
using namespace std;
#define maxsize 100
/*const int maxsize=100;*/
template<typename T>
class csqQueue{
    public:
     T*data;
     int front ,rear;

     csqQueue(){
        data=new T [maxsize];
        front=rear=0;
     }
     ~csqQueue(){
      delete []data;
     }
     bool empty(){
      return (front==rear);
     }
     bool push(T e){
      if((rear+1)%maxsize==front)
      return false;
      rear=(rear+1)%maxsize;
      data[rear]=e;
      return true;
     }
     bool pop(T&e){
      if(front==rear)
      return false;
      front=(front+1)%maxsize;
      //front 是空的
      e=data[front];
      return true;
     }
     bool gethead(T&e){
      if(front==rear)
      return false;
     int head=(front+1)%maxsize;
      //front 是空的
      e=data[head];
      return true;
     }
     int getlength(){
      return (rear-front+maxsize)%maxsize;
     }
};
