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

map<int, int> dpmap;
void createSpanningTree(vector<bridge> & bm, vector<vector<int>> & pm){
    bool vis[bm.size()]={false}; // visit flag
    bm[0].rootDistance=0;   // Choosing root
    bm[0].parent=0;
    vis[0]=true;
    queue<int> q;
    q.push(0);
    while(!q.empty()){ //bfs
        int parent=q.front();
        q.pop();
        for(int i=0; i<bm[parent].ports; i++){
            for(int j=0; j<pm[bm[parent].portDef[i]].size(); j++){ // checking bridges connected to the lan connected to parent
                int att=pm[bm[parent].portDef[i]][j];
                if(vis[att]){
                    if(bm[parent].rootDistance+1 < bm[att].rootDistance){ // if bridge previously visited see if the distance is less or not
                        bm[att].parent=parent;
                    }
                    else if(bm[parent].rootDistance+1 == bm[att].rootDistance){ // if distance equal then update parent required for root port.
                        if(bm[att].parent>parent) bm[att].parent=parent;
                    }
                }
                else{   // if not visited put in queue
                    vis[att]=true;
                    bm[att].rootDistance=bm[parent].rootDistance+1;
                    bm[att].parent=parent;
                    q.push(att);
                }
            }
        }
    }    

}

void updatePorts(vector<bridge> & bm, vector<vector<int>> pm, vector<vector<int>> & upm){

    for(int i=0; i<pm.size(); i++){
        if(pm[i].size()!=0){
            bool assigned=false;
            for(int j=0; j<pm[i].size(); j++){
                int att=pm[i][j];
                int par=bm[att].parent;
                for(int k=0; k<pm[i].size(); k++){
                    if(pm[i][k]==par){
                        assigned=true;
                        bm[att].portmap[i]="RP";
                        bm[par].portmap[i]="DP";
                        upm[i][par]=1;
                        upm[i][att]=1;
                    }
                }
            }
            if(!assigned){ // LAN is still not assigned. Assign to lowest id bridge. 
                int minID=pm[i][0];
                for(int j=0; j<pm[i].size(); j++){
                    if(pm[i][j]<minID) minID=pm[i][j];
                }
                bm[minID].portmap[i]="DP";
                
                upm[i][minID]=1;
            }
        }
        
    }
    // Remaining ports of each bridge is of no use
    for(int i=0; i<bm.size(); i++){
        for(int j=0; j<bm[i].portDef.size(); j++){
            if(bm[i].portmap.find(bm[i].portDef[j])==bm[i].portmap.end()){
                bm[i].portmap[bm[i].portDef[j]]="NP";
            }
        }
    }
}

vector<int> stripHostNum(string a){ // Stripping the numbers from the string input
    vector<int> res;
    int idx=a.find(':');
    for(int j=idx+2; j<a.length(); j=j+2){
            int hn=0;
            if(a[j]=='H'){
                    if(j+2==a.length()){
                        hn=a[j+1]-'0';
                        j=j+1;
                    }
                    else if(a[j+2]==' '){
                        hn=a[j+1]-'0';
                        j=j+1;
                    }
                    else if(isdigit(a[j+2])){
                        hn=(a[j+1]-'0')*10+(a[j+2]-'0');
                        j=j+2;
                    }                
            }
            else{
                continue;
            }
            res.push_back(hn);
        }
    return res;
}

int lanNum(int h, vector<LANHosts> l){ // Return lan number of the lan with with host is connected
    for(int i=0; i<l.size(); i++){
        for(int j=0; j<l[i].hosts.size(); j++){
            if(h==l[i].hosts[j]) return i;
        }
    }
}

void movePacket(int s, vector<vector<int>> upm, vector<bridge> & bm, int host, int dest){ // move packet in the tree and update the table
    bool vis[upm.size()]={false};
    bool visb[bm.size()]={false};
    queue<int> q;
    q.push(s);
    while(!q.empty()){
        int from=q.front();
        vis[from]=true;
        q.pop();
        for(int i=0; i<upm[from].size(); i++){
            if(upm[from][i]!=0 && !visb[i]){
                if(bm[i].routMap.find(host)==bm[i].routMap.end()){
                    bm[i].addRoute(host, from);
                }
                visb[i]=true;
                if(bm[i].routMap.find(dest)==bm[i].routMap.end()){
                    map<int, string>::iterator itr;
                    for(itr=bm[i].portmap.begin(); itr!=bm[i].portmap.end(); ++itr){
                        if(itr->second !="NP"){
                            if(vis[itr->first]){

                            }
                            else{
                                q.push(itr->first);
                            }
                        }
                    }
                }
                else{
                    int pd=bm[i].routMap[dest];
                    if(vis[pd]){

                    }
                    else{
                        q.push(pd);
                    }
                }
            }
        }
    }
}

void dropAllTables(vector<bridge> bm){ // Print all the routing tables available on the network
    for(int i=0; i<bm.size(); i++){
        bm[i].dropTable();
    }
    cout<<endl;
}
#endif

