#include<bits/stdc++.h>
using namespace std;

//Assumption---here we assume that the arrays have 1-based indexing
//1) we can process a range sum query
//2) also we can update a value  both in O(log n)

//implementation--
//let p(k) denotes the largest power of 2 that divides k
//tree[k]=sum(k-p(k)+1,k)
//examples of p(k)
//p(2)=2, p(6)=2, p(odd)=1, p(8)=8, p(12)=4
//value of p(k) can be calculated using p(k)=k & -k

//answering range sum queries---
//we always divide the range in log n parts and their sum is stored in the array
//s(1,7)=s(1,4)+s(5,6)+s(7,7)
//s(a,b)=s(1,b)-s(1,a-1)
//we can calculate s(1,b) and s(1,a-1) in O(log n) so total T.C. O(log n)


int getSum(int BITree[], int index)
{
    int sum = 0; // Initialize result
  
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;
  
    // Traverse ancestors of BITree[index]
    while (index>0)
    {
        // Add current element of BITree to sum
        sum += BITree[index];
  
        // Move index to parent node in getSum View
        index -= index & (-index);
    }
    return sum;
}
  
// Updates a node in Binary Index Tree (BITree) at given index
// in BITree. The given value 'val' is added to BITree[i] and 
// all of its ancestors in tree.
void updateBIT(int BITree[], int n, int index, int val)
{
    // index in BITree[] is 1 more than the index in arr[]
    index = index + 1;
  
    // Traverse all ancestors and add 'val'
    while (index <= n)
    {
    // Add 'val' to current node of BI Tree
    BITree[index] += val;
  
    // Update index to that of parent in update View
    index += index & (-index);
    }
}
  
// Constructs and returns a Binary Indexed Tree for given
// array of size n.
int *constructBITree(int arr[], int n)
{
    // Create and initialize BITree[] as 0
    int *BITree = new int[n+1];
    for (int i=1; i<=n; i++)
        BITree[i] = 0;
  
    // Store the actual values in BITree[] using update()
    for (int i=0; i<n; i++)
        updateBIT(BITree, n, i, arr[i]);
  
    // Uncomment below lines to see contents of BITree[]
    //for (int i=1; i<=n; i++)
    //     cout << BITree[i] << " ";
  
    return BITree;
}
  
  
// Driver program to test above functions
int main()
{
    int freq[] = {2, 1, 1, 3, 2, 3, 4, 5, 6, 7, 8, 9};
    int n = sizeof(freq)/sizeof(freq[0]);
    int *BITree = constructBITree(freq, n);
    cout << "Sum of elements in arr[0..5] is "
        << getSum(BITree, 5);
  
    // Let use test the update operation
    freq[3] += 6;
    updateBIT(BITree, n, 3, 6); //Update BIT for above change in arr[]
  
    cout << "\nSum of elements in arr[0..5] after update is "
        << getSum(BITree, 5);
  
    return 0;
}

