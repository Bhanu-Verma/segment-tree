#include <bits/stdc++.h>
using namespace std;
#define ll long long 

struct vertex{
    int value;
    int index;
};


const int N=2e5;
vertex Stree[4*N];
int arr[N];


int query(int node, int ss, int se, int x){
    if(Stree[node].value < x){
        return 0;
    }
    if(ss == se){
        Stree[node].value -= x; 
        return Stree[node].index;
    }
    int mid=ss+(se-ss)/2;
    if(Stree[2*node].value >= x){
        int idx = query(2*node,ss,mid,x);
        if(Stree[2*node].value>=Stree[2*node+1].value){
        Stree[node]=Stree[2*node];
        }else if(Stree[2*node].value<Stree[2*node+1].value){
            Stree[node]=Stree[2*node+1];
        }
        return idx;
    }else{
        int idx=query(2*node+1,mid+1,se,x);
        if(Stree[2*node].value>=Stree[2*node+1].value){
        Stree[node]=Stree[2*node];
        }else if(Stree[2*node].value<Stree[2*node+1].value){
            Stree[node]=Stree[2*node+1];
        }
        return idx;
    }

    

}



void print_tree(int n){
    for(int i=1; i<n; i++){
        cout<<Stree[i].value<<" "<<Stree[i].index<<endl;
    }
    cout<<endl;
}

void buildTree(int node,int s, int e){
    if(s==e){
        Stree[node].value = arr[s];
        Stree[node].index = s+1;
        return;
    }
    int mid = s+(e-s)/2;
    buildTree(2*node,s,mid);
    buildTree(2*node+1,mid+1,e);
    if(Stree[2*node].value>=Stree[2*node+1].value){
        Stree[node]=Stree[2*node];
    }else if(Stree[2*node].value<Stree[2*node+1].value){
        Stree[node]=Stree[2*node+1];
    }
}


int main(){
    int n,m;
    cin>>n>>m;
   ///int h[n];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    buildTree(1,0,n-1);
    //print_tree(4*n);
    for(int i=0; i<m; i++){
        int x;
        cin>>x;
        cout<<query(1,0,n-1,x)<<" ";
    }
    cout<<endl;
    return 0;
}