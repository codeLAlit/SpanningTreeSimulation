#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include "bridge.h"
using namespace std;
#define inf 1000000


void bridge::dropPorts(){
        cout<<"B"<<id+1<<": ";
        map<int, string>::iterator itr;
        for(itr=portmap.begin(); itr!=portmap.end(); ++itr){
            cout<<char('A'+itr->first)<<"-"<<itr->second<<" ";
        }
        cout<<endl;
    }

void bridge::dropTable(){
        cout<<"B"<<id+1<<":"<<endl;
        cout<<"HOST ID | FORWARDING PORT"<<endl;
        sort(routTable.begin(), routTable.end());
        for(int i=0; i<routTable.size();  i++){
            cout<<"H"<<routTable[i].first<<" | "<<char(routTable[i].second+'A')<<endl;
        }
    }

void bridge::addPort(char P){
        portDef.push_back(P);
        ports+=1;
    }

void bridge::addRoute(int H, int P){
        routTable.push_back(make_pair(H, P));
        routMap[H]=P;
    }

int bridge::DestPort(int H){
        return routMap[H];
    }