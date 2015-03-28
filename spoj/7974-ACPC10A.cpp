#include<iostream>
int main(){
    int a,b,c;    
    std::cin>>a>>b>>c;
    while(a|b|c){
        if(c-b==b-a)
            std::cout<<"AP "<<2*c-b;
        else
            std::cout<<"GP "<<c*c/b;
        std::cout<<std::endl;
        std::cin>>a>>b>>c;
    }
}