#include<iostream>
#include<map>
#include<vector>
#include "bridge.h"
#include<string>
#include<stack>
#include<queue>
#ifndef BRIDGESIM
#define BRIDGESIM 

using namespace std;

class LANHosts{
    public:
    int id;
    vector<int> hosts;
    int dp=0;
    void addHosts(vector<int> a){
        for(int i=0; i<a.size(); i++) hosts.push_back(a[i]);
    }
};


void createSpanningTree(vector<bridge> & bm, vector<vector<int>> & pm);

void updatePorts(vector<bridge> & bm, vector<vector<int>> pm, vector<vector<int>> & upm);

vector<int> stripHostNum(string a);

int lanNum(int h, vector<LANHosts> l);

void movePacket(int s, vector<vector<int>> upm, vector<bridge> & bm, int host, int dest);

void dropAllTables(vector<bridge> bm);
#endif

