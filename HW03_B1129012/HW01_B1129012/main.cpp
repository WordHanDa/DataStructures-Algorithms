//
//  main.cpp
//  HW01_B1129012
//
//  Created by macbook pro on 2024/3/23.
//  reference:https://youtu.be/j-DqQcNPGbE?si=NSkyNE8goWyP_HEX
//            https://alrightchiu.github.io/SecondRound/comparison-sort-merge-sorthe-bing-pai-xu-fa.html
//            https://alrightchiu.github.io/SecondRound/comparison-sort-quick-sortkuai-su-pai-xu-fa.html

#include<bits/stdc++.h>
#define mp make_pair
#define pr pair<int,int>
using namespace std;

int main(){
    int n = 5; //五個點
    int m = 5; //五個邊
    vector<vector<int>> graph(n); //長度為5，資料型態為vector<int>的陣列
    pr edge[5] = {mp(0,1),mp(0,2),mp(1,3),mp(3,4),mp(4,2)}; //x與y
    for(int i = 0; i < m; i++){
        int x,y;
        x = edge[i].first;
        y = edge[i].second;
        graph[x].push_back(y); //雙向連通，將x當成索引，放入y點
        graph[y].push_back(x); //雙向連通，降y當成索引，放入x點
    }
}
