#include<bits/stdc++.h>
using namespace std;

int main(){
    int arr[]={1,2,3,4,5,6};
    int n=sizeof(arr)/sizeof(int);
    for(int i=1;i<n;i++){
        arr[i]+=arr[i-1];
    }
    cout<<"give indices to calculate sum b/w:\n";
    int l,r;
    cin>>l>>r;
    if(l==1){
        cout<<arr[r-1]<<endl;       //considering 1 based indexing
    }
    cout<<arr[r-1]-arr[l-2];
    return 0;
}