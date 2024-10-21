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
        int minDistance = 100000000;
        int watching=0;
        int x1 = Agent[i].x;
        int y1 = Agent[i].y;
        for(int j = 0; j<Agent.size(); j++){
            if(j == i) continue;
            int dis = sqrt((x1 - Agent[j].x)*(x1 - Agent[j].x) + (y1 - Agent[j].y)*(y1 - Agent[j].y));
            if(dis < minDistance){
                minDistance = dis;
                watching = j;
            }

        }
        Watched.erase(watching);

    }
    cout << Watched.size() << endl;
    for(auto i: Watched){
        cout << i << " ";}
        }