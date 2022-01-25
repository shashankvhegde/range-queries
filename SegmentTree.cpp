#include<bits/stdc++.h>
using namespace std;

void print(vector<int>& st){
    for(int i = 0;i<st.size();i++){
        cout << st[i] << " " ;
    }
    cout << endl;
}
int getPaddedSize(int n){
    int x = ceil(log2(n));
    int size = (int)pow(2, x);
    return size;
}

int parent(int i){
    return ((i==0)?-1:(i/2));
}

void buildUtil(vector<int>& st, int arr[], int low, int high, int index){
    
    if(low == high){
        st[index] = arr[low]; 
    }
    else{
        int mid = (low+high)/2;
        int l = 2*index+1;
        int r = l+1;
        buildUtil(st, arr, low, mid, l);
        buildUtil(st, arr, mid+1, high, r);
        st[index] = st[l]+st[r];
    }
}

vector<int> build(int arr[], int n){
    
    int N = getPaddedSize(n);
    int size = 2*N-1;
    
    vector<int> st(size, 0);
    
     
    int newInput[N] = {0};
    for(int i = 0;i<n;i++){
        newInput[i] = arr[i];
    }
    buildUtil(st, newInput, 0, N-1, 0);

    return st;
}

int query(vector<int>& st, int low, int high, int a, int b, int index){
    
    int retval;
    int mid = (low+high)/2;
    int l = 2*index+1;
    int r = l+1;
    if(low == a && high == b){
        retval = st[index];
    }
    else if(a<=mid && b>mid){
        int left = query(st, low, mid, a, mid, l);
        int right = query(st, mid+1, high, mid+1, b, r);
        
        retval = left+right;
    }
    else if(a<=mid){
        retval = query(st, low, mid, a, b, l);
    }
    else{
        retval = query(st, mid+1, high, a, b, r);
    }   
    return retval;
}

void update(vector<int>& st, int arr[], int i, int x){
    int size = st.size();
    int N = size/2;
    
    int index = i+N;
    while(index != -1){
        
        st[index] += (x-arr[i]);
        index = parent(index);
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
    vector<int> st = build(arr, n);
    
    int N = getPaddedSize(n);
    print(st);
    
    int q;
    
    cin >> q;
    
    while(q--){
        int i, x;
        
        cin >> i >> x;
        
        update(st, arr, i, x);
        print(st);
        
    }
    

    return 0;
}