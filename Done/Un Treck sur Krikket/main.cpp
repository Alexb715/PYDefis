#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <queue>
#include<print>
using namespace std;
string getPath(tuple<int, int, char> parent[513][513], int n, int m) {
    string path;
    int current_row = n - 1;
    int current_col = m - 1;

    // Check if a path was found to the destination at all.
    // get<0> gets the parent's row. If it's still -1, it was never reached.
    if (get<0>(parent[current_row][current_col]) == -1) {
        return "No path found to destination.";
    }

    // Loop backwards from the destination to the start
    while (true) {
        // Get the parent data for the current cell
        auto [parent_row, parent_col, move] = parent[current_row][current_col];

        // The starting node's parent is (-1, -1). This is our break condition.
        if (parent_row == -1 && parent_col == -1) {
            break;
        }

        path.push_back(move);

        // --- THIS IS THE FIX ---
        // Update the current row and col to move to the parent cell for the next loop iteration.
        current_row = parent_row;
        current_col = parent_col;
    }

    reverse(path.begin(), path.end());
    return path;
}
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
    vector<vector<int>> dist(513,vector<int>(513,1e9));
    dist[0][0] = 0;
    tuple<int,int,char> parent[513][513];
    tuple<int,int,int> cur;
    for (int i = 0; i < 513; ++i) {
        for (int j = 0; j < 513; ++j) {
            parent[i][j] = {-1, -1, '\0'};
        }
    }
    while(pq.empty()!= true){
        cur = pq.top();
        int cost = get<0>(cur);
        int row = get<1>(cur);
        int col = get<2>(cur);
        pq.pop();
        if(row == 512 && col == 512){
            break;
        }
        if(cost > dist[row][col]){
            continue;
        }
        if(col + 1 < 513){  //east
            int sCost = max(0,grid[row][col+1]-grid[row][col]);
            int nCost = sCost + dist[row][col];
            if(nCost < dist[row][col+1]){
                dist[row][col+1] = nCost;
                parent[row][col+1] = tuple<int,int,char>(row,col,'E');
                pq.push(tuple<int,int,int>(nCost,row,col+1));
            }
             
        }
        if(row + 1 < 513){  //south
            int sCost = max(0,grid[row+1][col]-grid[row][col]);
            int nCost = sCost + dist[row][col];
            if(nCost < dist[row+1][col]){
                dist[row+1][col] = nCost;
                parent[row+1][col] = tuple<int,int,char>(row,col,'S');
                pq.push(tuple<int,int,int>(nCost,row+1,col));
                
            }
        }
        if(col -1 > -1){    //west
            int sCost = max(0,grid[row][col-1]-grid[row][col]);
            int nCost = sCost + dist[row][col];
            if(nCost < dist[row][col-1]){
                dist[row][col-1] = nCost;
                parent[row][col-1] = tuple<int,int,char>(row,col,'O');
                pq.push(tuple<int,int,int>(nCost,row,col-1));
            }
        } 
        if(row -1 > -1){    //north
            int sCost = max(0,grid[row-1][col]-grid[row][col]);
            int nCost = sCost + dist[row][col];
            if(nCost < dist[row-1][col]){
                dist[row-1][col] = nCost;
                parent[row-1][col] = tuple<int,int,char>(row,col,'N');
                pq.push(tuple<int,int,int>(nCost,row-1,col));
            }
        }
    }
    int m = 513;
    int n = 513;
    cout  <<  getPath(parent,m,n);
    return 0;
}