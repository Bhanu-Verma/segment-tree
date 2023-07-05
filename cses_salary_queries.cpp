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
int Stree[4*N], arr[10000000];

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
    Stree[node] = Stree[2*node] + Stree[2*node+1];
}

int query(int node, int ss, int se, int qs, int qe){
    //here segment lies completely in the given range
    if(ss>=qs && se<=qe){
        return Stree[node];
    }
    //here segment lies completely outside the given range
    if(ss>qe || se<qs){
        return 0;
    }
    int mid=ss+(se-ss)/2;
    return query(2*node,ss,mid,qs,qe)+query(2*node+1,mid+1,se,qs,qe);
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
    int n;
    cin>>n;
    int s[n];
    for(int i=0; i<n; i++){
        cin>>s[i];
        if(s[i]%100==0){
            arr[s[i]/100-1]+=1;

        }else{
            arr[s[i]/100]+=1;
        }

    }

    
    return 0;
}