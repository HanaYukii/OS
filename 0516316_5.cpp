#include<bits/stdc++.h>
using namespace std;

int main(){
    int now=0;
    int add;
    set<int>exist;
    map<int,int>pos;
    map<int,int>cont;
    int hit=0,miss=0;
    while(cin>>add){
        if(exist.find(add)==exist.end()){
            miss++;
            pos[add]=now;
            cont[now++]=add;
            exist.insert(add);
            while(exist.size()>128){
                int del=cont.begin()->second;
                int mdel=cont.begin()->first;
                cont.erase(mdel);
                exist.erase(del);
            }
        }
        else{
            hit++;
            int del=pos[add];
            pos[add]=now;
            cont[now]=add;
            cont.erase(del);
            now++;
        }
        
    }
    cout<<hit<<' '<<miss<<endl;
}