#include <bits/stdc++.h>
using namespace std;
#define ll long long

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
        arr[s]=0;
        Stree[node]=0;
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
    if(ss == se){
        return ss;
    }
    int mid = ss+(se-ss)/2;
    if(k<Stree[2*node]){
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

void display(int arr[],int n){
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int main(){
    int n;
    cin>>n;
    vector<int> a(n);
    vector<int> an;
    for(int i=0; i<n; i++){
        arr[i]=1;
    }
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    buildTree(1,0,n-1);
   // print_tree(4*n);
   int y=n;
    for(int i=n-1; i>=0; i--){
        int x = a[i];
        int ans = query(1,0,n-1,y-x-1) + 1;
        //cout<<"index="<<y-x<<endl;
        an.push_back(ans);
        //cout<<ans<<" ";
        update(1,0,n-1,ans-1);
        //display(arr,n);
        y--;
       
    }
    reverse(an.begin(),an.end());
    for(int i=0; i<n; i++){
        cout<<an[i]<<" ";
    }
    cout<<endl;
    return 0;
}
