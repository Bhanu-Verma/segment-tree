#include<bits/stdc++.h>
using namespace std;

const int N=2e5;
int Stree[4*N], arr[N];

void update(int node,int s, int e, int idx, int val){
    if(s==e){
        Stree[node]=val;
        arr[s]=val;
        return;
    }
    int mid = s+(e-s)/2;
    if(idx <= mid){
        update(2*node, s, mid, idx, val);
    }else{
        update(2*node+1,mid+1,e,idx,val);
    }
    Stree[node] = min(Stree[2*node],Stree[2*node+1]);
}

int query(int node, int ss, int se, int qs, int qe){
    //here segment lies completely in the given range
    if(ss>=qs && se<=qe){
        return Stree[node];
    }
    //here segment lies completely outside the given range
    if(ss>qe || se<qs){
        return INT_MAX;
    }
    int mid=ss+(se-ss)/2;
    return min(query(2*node,ss,mid,qs,qe),query(2*node+1,mid+1,se,qs,qe));
}



void print_tree(int n){
    for(int i=1; i<n; i++){
        cout<<Stree[i]<<" ";
    }
    cout<<endl;
}

void buildTree(int node,int s, int e){
    if(s==e){
        Stree[node]=arr[s];
        return;
    }
    int mid = s+(e-s)/2;
    buildTree(2*node,s,mid);
    buildTree(2*node+1,mid+1,e);
    Stree[node] = min(Stree[2*node],Stree[2*node+1]);
}

int main(){
    int n,q;
    cin>>n>>q;
    //int arr[n];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }

    buildTree(1,0,n-1);
  //  print_tree(4*n);
    while(q--){
        int a,b;
        cin>>a>>b;
        cout<<query(1,0,n-1,a-1,b-1)<<endl;
    }
    return 0;
}