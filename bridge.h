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

    void dropPorts(){
        cout<<"B"<<id+1<<": ";
        map<int, string>::iterator itr;
        for(itr=portmap.begin(); itr!=portmap.end(); ++itr){
            cout<<char('A'+itr->first)<<"-"<<itr->second<<" ";
        }
        cout<<endl;
    }

    void dropTable(){
        cout<<"B"<<id+1<<":"<<endl;
        cout<<"HOST ID | FORWARDING PORT"<<endl;
        sort(routTable.begin(), routTable.end());
        for(int i=0; i<routTable.size();  i++){
            cout<<"H"<<routTable[i].first<<" | "<<char(routTable[i].second+'A')<<endl;
        }
    }

    void addPort(char P){
        portDef.push_back(P);
        ports+=1;
    }

    void addRoute(int H, int P){
        routTable.push_back(make_pair(H, P));
        routMap[H]=P;
    }

    int DestPort(int H){
        return routMap[H];
    }

    
};


#endif