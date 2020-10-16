#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
#define inf 1000000
#ifndef BRIDGE
#define BRIDGE 

class bridge{
    public:
    int id=0;
    int ports=0;
    int parent=0;
    int rootDistance=inf;
    vector<int> portDef;
    map<int, string> portmap;
    vector<pair<int, int>> routTable;
    map<int, int> routMap;

    void dropPorts();

    void dropTable();

    void addPort(char P);

    void addRoute(int H, int P);

    int DestPort(int H);

    
};


#endif