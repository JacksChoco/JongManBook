//
//  main.cpp
//  JongManbook
//
//  Created by Jack on 2018. 6. 25..
//  Copyright © 2018년 Jack. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#define MAX(a,b) a > b ? a : b

using namespace std;

vector < vector <int> > cache;

int maxPacking(int capacity, int item, vector <int> needs, vector <int> capacities){
    if(capacity == 0 || item >= needs.size()){
        return 0;
    }
    int& temp =cache[capacity][item];
    if(temp != -1){
        return cache[capacity][item];
    }
    
    temp = maxPacking(capacity, item+1, needs, capacities);
    if(capacity - capacities[item] >= 0){
        temp = MAX(temp,maxPacking(capacity - capacities[item], item+1, needs, capacities) + needs[item]);
    }

    return temp;
}

void reconstruct(int capacity, int item, list<int> &picked,vector <int> capacities){
    if(item == cache[0].size() - 1){
        return;
    }
    
    if(cache[capacity][item] == cache[capacity][item+1]){
        reconstruct(capacity, item+1, picked,capacities);
    }
    else{
        picked.push_back(item);
        reconstruct( capacity-capacities[item], item+1, picked,capacities);
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    int T;
    
    cin >> T;
    
    for(int test_case = 0; test_case < T; test_case++){
        int N, W;
        cin >> N >> W;
        
        cache.clear();
        cache.resize(W+1);
        
        for(int i=0; i<W+1; i++){
            vector<int> item;
            item.resize(N,-1);
            cache[i] = item;
        }
        
        vector <string> name;
        name.clear();
        name.resize(N);
        
        vector <int> needs;
        needs.clear();
        needs.resize(N);
        
        vector <int> capacities;
        capacities.clear();
        capacities.resize(N);
        
        list <int> picked;
        
        for(int i=0; i < N; i++){
            cin >> name[i] >> capacities[i] >> needs[i];
        }
        
        int max = maxPacking(W,0,needs,capacities);
        reconstruct(W,0,picked, capacities);
        
        int total = 0;
        
        for (const int& value : picked){
            total++;
        }
        
        cout << max << " " << total << " " << endl;
        
        for (const int& value : picked){
            cout << name[value] << " " << endl;
        }
        
    }
    return 0;
}


