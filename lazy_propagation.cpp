#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define vi vector<int>
#define vll vector<long long>

/*If we want to update the values in a range using segment tree
then this concept comes in*/
 
const int N=2e5;
int Stree[4*N], arr[N];
int lazy[4*N];

void updaterange(int node, int ss, int se, int us, int ue, int diff){
    if(lazy[node]!=0){
        Stree[node] += (se-ss+1)*lazy[node];
        if(ss!=se){
            lazy[2*node] += lazy[node];
            lazy[2*node+1]+=lazy[node];
        }
        lazy[node]=0;
    }
    //completely outside
    if(ss>ue || se<us){
        return;
    }
    //completely inside
    if(ss>=us && se<=ue){
        Stree[node] += (se-ss+1)*diff;
        if(ss!=se){
            lazy[node*2] += diff;
            lazy[node*2+1] += diff;
        }
        return;
    }
    //if overlapping 
    int mid = ss+(se-ss)/2;
    updaterange(2*node,ss,mid,us,ue,diff);
    updaterange(2*node+1,mid+1,se,us,ue,diff);
    Stree[node] = Stree[2*node] + Stree[2*node+1];
}


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
    //pehle lazy ko dekh le
    if(lazy[node]!=0){
        Stree[node] += (se-ss+1)*lazy[node];
        if(ss!=se){
            lazy[2*node]+=lazy[node];
            lazy[2*node+1]+=lazy[node];
        }
        lazy[node] = 0;
    }

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
    int n=8;
    for(int i=0; i<8; i++){
        arr[i]=i+1;
    }
    buildTree(1,0,n-1);
    print_tree(2*n+1);
    updaterange(1,0,n-1,2,5,4);
    print_tree(2*n+1);
  return 0;
}