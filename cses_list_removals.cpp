#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vll vector<long long>

// When discussing segment trees, we assume that the size of the array is
// a power of two, and zero-based indexing is used, because it is convenient to build a
// segment tree for such an array. If the size of the array is not a power of two, we can
// always append extra elements to it.


//IMPLEMANTATION---
// A convenient way to store the contents of a segment tree is to use
// an array of 2n elements where n is the size of the original array. The tree nodes are
// stored from top to bottom: tree[1] is the top node, tree[2] and tree[3] are its
// children, and so on. Finally, the values from tree[n] to tree[2n − 1] correspond
// to the bottom level of the tree, which contains the values of the original array. Note

const int N=2e5;
int Stree[4*N], arr[N];

void update(int node,int s, int e, int idx){
    if(s==e){
        Stree[node]=0;
        arr[s]=0;
        return;
    }
    int mid = s+(e-s)/2;
    if(idx <= mid){
        update(2*node, s, mid, idx);
    }else{
        update(2*node+1,mid+1,e,idx);
    }
    Stree[node] = Stree[2*node] + Stree[2*node+1];
}

int query(int node, int ss, int se, int k){ 
    //here segment lies completely in the given range
    if(Stree[node]<k){
        return -1;
    }
    if(ss==se){
        return ss;
    }

    int mid = ss+(se-ss)/2;
    if(Stree[2*node]>k){
        return query(2*node,ss,mid,k);
    }else{
        return query(2*node+1,mid+1,se,k-Stree[2*node]);
    }




    
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
    Stree[node] = Stree[2*node]+Stree[2*node+1];
}


int main(){
  ll n;
  cin>>n;
  ll lst[n];
    //int arr[n];
    for(int i=0; i<n; i++){
        arr[i]=1;
    }
    for(int i=0; i<n; i++){
        cin>>lst[i];
    }
    buildTree(1,0,n-1);
    for(int i=0; i<n; i++){
        int x;
        cin>>x;
        int ans_idx = query(1,0,n-1,x-1);
        update(1,0,n-1,ans_idx);
        cout<<lst[ans_idx]<<" ";
    }
    cout<<endl;
  return 0;
}