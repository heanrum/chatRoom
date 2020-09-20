#include "ThreadPool.h"
#include <iostream>
#include <unistd.h>

using namespace std;
using namespace chat::base;

void f1(int a,int b){
    cout<<a+b<<endl;
}

int main(){
    ThreadPool tp(10);
    tp.start();
    for(int i=0;i<20;++i)
        tp.run(bind(f1, i, i+1));
    sleep(2);
}