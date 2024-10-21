#include <algorithm>
#include <iostream>
#include <unordered_set>
#include<vector>
#include<cmath>
struct cord {
    int x;
    int y;

    cord(int xCoord, int yCoord) : x(xCoord), y(yCoord) {}
};
using namespace std;
int main(){
    vector<cord> Agent;
    unordered_set<int> Watched;
    int n = 0;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x, y;
        char junk;
        cin >> x >>junk >> y;
        Agent.push_back(cord(x, y));
        Watched.insert(i);
    }
    for(int i = 0; i<Agent.size(); i++){
        double minDistance = 100000000;
        int watching=0;
        double x1 = Agent[i].x;
        double y1 = Agent[i].y;
        for(int j = 0; j<Agent.size(); j++){
            if(j == i) continue;
            double dis = sqrt(pow((x1 - Agent[j].x),2) + pow((y1 - Agent[j].y),2));
            if(dis < minDistance){
                minDistance = dis;
                watching = j;
            }

        }
        Watched.erase(watching);

    }
    vector<int> result;
    for(auto i : Watched){
        result.push_back(i);
            }
            sort(result.begin(),result.end());
            for(auto i : result){
                cout << i << ",";
            }
        }