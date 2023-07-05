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

struct vertex{
    ll sum;
    ll prefix;
};

const int N=2e5+2;
vertex Stree[4*N];
ll arr[N];

void update(int node,int s, int e, int idx, ll val){
    if(s==e){
        Stree[node].prefix=Stree[node].sum=val;
        arr[s]=val;
        return;
    }
    int mid = s+(e-s)/2;
    if(idx <= mid){
        update(2*node, s, mid, idx, val);
    }else{
        update(2*node+1,mid+1,e,idx,val);
    }
    Stree[node].sum = Stree[2*node].sum+Stree[2*node+1].sum;
    Stree[node].prefix = max(Stree[2*node].prefix,Stree[2*node+1].prefix+Stree[2*node].sum);
}

vertex query(int node, int ss, int se, int qs, int qe){
    //here segment lies completely in the given range
    if(ss>=qs && se<=qe){
        return Stree[node];
    }
    //here segment lies completely outside the given range
    if(ss>qe || se<qs){
        vertex n;
        n.prefix=n.sum=0;
        return n;
    }
    int mid=ss+(se-ss)/2;
    vertex q1=query(2*node,ss,mid,qs,qe);
    vertex q2=query(2*node+1,mid+1,se,qs,qe);
    vertex q;
    q.prefix = max(q1.prefix,q1.sum+q2.prefix);
    q.sum = q1.sum+q2.sum;
    return q;
}



void print_tree(int n){
    for(int i=1; i<n; i++){
        cout<<Stree[i].sum<<" "<<Stree[i].prefix<<endl;
    }
    cout<<endl;
}

void buildTree(int node,int s, int e){
    if(s==e){
        Stree[node].prefix=Stree[node].sum=arr[s];
        return;
    }
    int mid = s+(e-s)/2;
    buildTree(2*node,s,mid);
    buildTree(2*node+1,mid+1,e);
    Stree[node].sum = Stree[2*node].sum+Stree[2*node+1].sum;
    Stree[node].prefix = max(Stree[2*node].prefix,Stree[2*node+1].prefix+Stree[2*node].sum);
}



int main(){
    int n,q;
    cin>>n>>q;
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    buildTree(1,0,n-1);
    //print_tree(4*n);
    for(int i=0; i<q; i++){
        int type;
        cin>>type;
        if(type==1){
            int k;
            ll u;
            cin>>k>>u;
            update(1,0,n-1,k-1,u);
        }else{
            int a,b;
            cin>>a>>b;
            if(a==b){
                cout<<max(query(1,0,n-1,a-1,b-1).prefix,0ll)<<endl;
            }else{
            cout<<query(1,0,n-1,a-1,b-1).prefix<<endl;
            }
            
        }
    }
    return 0;
}