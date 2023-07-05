/*prob--given an array of size n queries of two types-
* 1 i v --- change the value at index i to v
* 2 x -- find min index j such that jth ele is greater than or equal to x
*/

/*logic--
*   using binary search we can find the index--
    find max from low to mid say it is y-
    if y<x:
        => from low to high we'll not get ans
    else:
        => we got one ele in low to mid so mid to high is useless
    mid may be a candidate for answer    


*   now problem is how can we find maximum and how to do updates
    as all know we can do this by segment tree

*/

#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9+7;
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
    Stree[node] = max(Stree[2*node],Stree[2*node+1]);
}

int query(int node, int ss, int se, int qs, int qe){
    //here segment lies completely in the given range
    if(ss>=qs && se<=qe){
        return Stree[node];
    }
    //here segment lies completely outside the given range
    if(ss>qe || se<qs){
        return -mod;
    }
    int mid=ss+(se-ss)/2;
    return max(query(2*node,ss,mid,qs,qe),query(2*node+1,mid+1,se,qs,qe));
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
    Stree[node] = max(Stree[2*node],Stree[2*node+1]);
}


int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0; i<n;i++){
        cin>>arr[i];
    }
    buildTree(1,0,n-1);
    print_tree(4*n);
    while(m--){
        int type;
        cin>>type;
        if(type==1){
            int idx,val;
            cin>>idx>>val;
            update(1,0,n-1,idx,val);
        }else{
            int x;
            cin>>x;
            int lo=0, hi=n-1;
            int ans = n;
            
            
            while(lo<=hi){
                int mid = lo + (hi-lo)/2;
                int y=query(1,0,n-1,lo,mid);
                if(y<x){
                    lo = mid+1;
                }else{
                    hi = mid -1;
                    ans = min(ans,mid);
                }
            }

            if(ans == n){
                cout<<-1<<endl;
            }else{
                cout<<ans<<endl;
            }
        }
        }
    return 0;
}
