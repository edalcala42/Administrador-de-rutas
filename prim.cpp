#include<bits/stdc++.h>
using namespace std;
struct node{
    int start;
    int end;
    int distance;
};
map<int,map<int,int>>graph;



double prim(int n){
    double sum=0;
    struct compareN
    {
        bool operator() (node const &a, node const &b) { return a.distance>b.distance; }
    };
    priority_queue<node,vector<node>,compareN>datos;
    set<int>rec;
    if(!rec.count(n))
        for(auto k:graph[n]){
            node aux;
            aux.start=n;
            aux.end=k.first;
            aux.distance=k.second;
            datos.push(aux);
        }
    rec.insert(n);
    while(datos.size()){
        node aux=datos.top();
        datos.pop();
        if(!rec.count(aux.start) && !rec.count(aux.end)){
            sum+=aux.distance;
            prim(aux.end);
            prim(aux.start);
        }else if(!rec.count(aux.start)){
            sum+=aux.distance;
            prim(aux.end);
        }else if( !rec.count(aux.end)){
            sum+=aux.distance;
            prim(aux.start);
        }
    }
    return sum;
}

int main(){
    int a,b,c,d,e;
    cin>>a>>b;
    while(b--){
        cin>>c>>d>>e;
        graph[c][d]=e;
        graph[d][c]=e;
    }
    cout<<prim(c)<<endl;
}
