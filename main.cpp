#include<iostream>
#include<map>
#include<vector>
#include<stack>
#include<queue>
#include "bridge.h"
#include "bridgesim.h"
#include<string>
#include<set>
using namespace std;



int main(){
    int flag;
    cin>>flag;
    int numBridges;
    cin>>numBridges;
    vector<bridge> bm(numBridges);
    vector<vector<int>> pm(26, vector<int>());
    set<int> lans;
    string a;
    cin>>ws;
    for(int i=0; i<numBridges; i++){
        getline(cin, a);
        int idx=a.find(':');
        bm[i].id=i;
        for(int j=idx+2; j<a.length(); j=j+2){
            bm[i].addPort(a[j]-'A');            
            pm[a[j]-'A'].push_back(i);
            lans.insert(a[j]-'A');
        }
    }
    

    vector<LANHosts> lanhosts(lans.size());
    cin>>ws;
    for(int i=0; i<lans.size(); i++){
        getline(cin, a);
        lanhosts[i].id=a[0]-'A';
        lanhosts[i].addHosts(stripHostNum(a));
    }

    vector<vector<int>> upm(lans.size(), vector<int>(numBridges));
    createSpanningTree(bm, pm); 

    updatePorts(bm, pm, upm);

    for(int i=0; i<numBridges; i++){
        bm[i].dropPorts();
    }

    int reqs=0;
    cin>>reqs;
    cin>>ws;
    for(int i=0; i<reqs; i++){
        getline(cin, a);
        vector<int> hh=stripHostNum(": "+a);
        int s=lanNum(hh[0], lanhosts);
        movePacket(s, upm, bm, hh[0], hh[1]);

        dropAllTables(bm);
    }
    
    

}