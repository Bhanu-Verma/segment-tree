
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 1e9+7;

int lb_search(ll arr[], int n, ll x){
    int s=0, e=n-1;
    int mid = s+(e-s)/2;
    int ans = n+1;
    while(s<=e){
        if(arr[mid]<x){
            ans = max(ans,mid+1);
            s = mid+1;
        }else if(arr[mid]>=x){
            //ans = min(ans,mid+1);
            e = mid-1;
        }
        mid = s+(e-s)/2;
    }
    return ans;
}


int rb_search(ll arr[], int n, ll x){
    int s=0, e=n-1;
    int mid = s+(e-s)/2;
    int ans = n+1;
    while(s<=e){
        if(arr[mid]<=x){
            ans = mid+1;
            s = mid+1;
        }else if(arr[mid]>x){
            //ans = min(ans,mid+1);
            e = mid-1;
        }else{
            s = mid+1;
        }
        mid = s+(e-s)/2;
    }
    return ans;
}

int main(){
    int n,k;
    cin>>n>>k;
    ll arr[n];
    for(int i=0; i<n; i++){
        cin>>arr[i];
    }
    sort(arr,arr+n);
    
    for(int i=0; i<k; i++){
        int x,y;
        cin>>x>>y;
        cout<<rb_search(arr,n,y)-lb_search(arr,n,x)<<endl;

    }

    return 0;
}