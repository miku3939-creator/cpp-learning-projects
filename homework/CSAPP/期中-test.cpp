#include<iostream>
using namespace std;
struct Stu{
        char gender;
    int age;
    char name[20];
        struct Stu* next;
};
 
int main(){
Stu u;
cout<<sizeof(u.gender)<<sizeof(u.age)<<sizeof(u.next)<<endl;
return 0;}