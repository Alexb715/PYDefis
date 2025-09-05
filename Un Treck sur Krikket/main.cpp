#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
vector<vector<int>> load_image_to_matrix(string path){
        // Load grayscale image
    cv::Mat img = cv::imread(path, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        vector<vector<int>> tmp;
        cerr << "Error: Could not open or find the image." << endl;
        return tmp;
    }

    // Create a 2D vector of the same size as the image
    vector<vector<int>> matrix(img.rows, vector<int>(img.cols));

    // Fill it with pixel values
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            matrix[i][j] = static_cast<int>(img.at<uchar>(i, j));
        }
    }
    return matrix;
}




int main() {
    //djikstra setup
    auto grid = load_image_to_matrix("map_krikket.png");
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>, greater<tuple<int,int,int>>> pq;
    pq.push(tuple(0,0,0)); //(cost,row,col)
    vector<vector<int>> dist(512,vector<int>(512,1e9));
    dist[0][0] = 0;
    tuple<int,int,string> parent[512][512];
    tuple<int,int,int> cur;
    while(pq.empty()!= true){
        cur = pq.top();
        int cost = get<0>(cur);
        int row = get<1>(cur);
        int col = get<2>(cur);
        pq.pop();
        if(row == 511 && col == 511){
            break;
        }
        if(cost > dist[row][col]){
            continue;
        }
        if(col + 1 < 512){  //east
            int sCost = max(0,grid[row][col+1]-grid[row][col]);
            int nCost = sCost + dist[row][col];
            if(nCost < dist[row][col+1]){
                dist[row][col+1] = nCost;
                
            }
             
        }
        if(row + 1 < 512){  //south

        }
        if(col -1 > -1){    //west

        } 
        if(row -1 > -1){    //north

        }
    }


    return 0;
}
