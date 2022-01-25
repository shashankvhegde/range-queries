#include <bits/stdc++.h>
using namespace std;

void print(vector<vector<int>>& table){
    int m = table.size();
    int n = table[0].size();
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            cout << table[i][j] << " ";
        }
        cout << endl;
    }
}

void buildSparseTable(vector<vector<int>>& table, int arr[]){
    
    int n = table.size();
    for(int i = 0;i<n;i++){
        table[i][0] = arr[i];
    }
    int x = floor(log2(n));
    int limit = (1 << x);
    
    for(int col = 1;(1 << col) <= n;col++){
        int range = (1 << col);
        for(int row = 0; row<(n-range+1);row++){
            int low = row;
            int high = row+range-1;
            int mid = (low+high)/2;
            table[row][col] = min(table[low][col-1], table[mid+1][col-1]);
        }
    }
    
}

bool isPowerofTwo(int n){
    return (floor(log2(n)) == ceil(log2(n)));
}
int query(vector<vector<int>>& table, int a, int b){
    int range = b-a+1;
    int retval;
    int w = floor(log2(range));
    if(isPowerofTwo(range)){
        retval =  table[a][w];
    }
    else{
        int power = pow(2, floor(log2(range)));
        retval = min(table[a][w], table[b-power+1][w]);
    }
    return retval;
}

int main(){
    
    int n;
    cin >> n;
    
    int arr[n];
    
    for(int i = 0;i<n;i++){
        cin >> arr[i];
    }
    
    vector<vector<int>> table(n);
    int colSize = 1+floor(log2(n));
    for(int i = 0;i<n;i++){
        table[i].resize(colSize);
    }
    
    buildSparseTable(table, arr);
    
    print(table);
    
    
    int q;
    cin >> q;
    
    while(q--){
        
        int l, r;
        
        cin >> l >> r;
        
        cout << query(table, l, r) << endl;
    }
    
    return 0;
}