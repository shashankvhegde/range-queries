#include<bits/stdc++.h>
using namespace std;
void print(int fenwickTree[], int n){
    for(int i = 0;i<n;i++){
        cout << fenwickTree[i] << " ";
    }
    cout << endl;
}
int p(int i){
    return (i+1)&(i^(i+1));
}
void buildFT(int fenwickTree[], int arr[], int n){
    
    int prefix[n];
    fenwickTree[0] = prefix[0] = arr[0];
    for(int i = 1;i<n;i++){
        prefix[i] = arr[i]+prefix[i-1];
    }
    
    for(int i = 1;i<n;i++){
        fenwickTree[i] = prefix[i]-prefix[i-p(i)+1]+arr[i-p(i)+1];
    }
    
}


int sum(int fenwickTree[], int n, int i){
    int retval = 0;
    if(i >= 0){
        int index = i;
        while(index >= 0){
            retval += fenwickTree[index];
            index = index-p(index);
        }
    }
    return retval;
}

int query(int fenwickTree[], int n, int l, int r){
    return (sum(fenwickTree, n, r) - sum(fenwickTree, n, l-1));
}


int update(int fenwickTree[], int arr[], int n, int i, int x){
    
    int index = i;
    
    while(index < n){
        fenwickTree[index] += (x-arr[i]);
        index += p(index);
    }
    arr[i] = x;
}

int main(){
    
    
    int n;
    cin >> n;
    
    int arr[n];
    for(int i = 0;i<n;i++){
        cin >> arr[i];
    }
    
    
    int fenwickTree[n];
    buildFT(fenwickTree, arr, n);
    
    print(fenwickTree, n);
    
    
    int q;
    cin >> q;
    
    while(q--){
        int ind, x;
        
        cin >> ind >> x;
        
        cout << update(fenwickTree, arr, n, ind, x) << endl;
        print(fenwickTree, n);
    }
    return 0;
}