#include <cstdio>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int main(){
 int n1, n2, s;  
 scanf("%d", &n1);
 scanf("%d", &n2);
 s = (n2 - n1) * (n2 - n1 + 1) / 2;
 printf("%d\n", s);
}