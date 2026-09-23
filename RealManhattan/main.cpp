#include <bits/stdc++.h>
#include <cmath>
#include <cstdlib>

using namespace std;

double planeDis(double x_1, double y_1, double x_2, double y_2) {
  return sqrt(pow((x_1 - x_2), 2) + pow((y_1 - y_2), 2));
}
double manDis(double x_1, double y_1, double x_2, double y_2) {
  return (fabs(x_1 - x_2) + fabs(y_1 - y_2));
}

int main() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    double mini;
    int bx1, by1, bx2, by2, x1, x2, y1, y2;
    cin >> bx1 >> by1 >> bx2 >> by2 >> x1 >> y1 >> x2 >> y2;

    // we need m and b of broadway
    double m = (double)((double)(by2 - by1) / (bx2 - bx1));
    // we then need b
    double b = (double)(by1 - m * bx1);
    // broadway is a segment, so we need its x range
    double loX = min(bx1, bx2);
    double hiX = max(bx1, bx2);
    // first we calc the manhatten distance since it's our target to beat
    mini = manDis(x1, y1, x2, y2);

    // 2 cases for x1 y1.
    // first case we go vertical
    double x1_1 = x1;
    double y1_1 = m * (x1_1) + b;
    // if we go horizontal
    double y1_2 = y1;
    double x1_2 = (y1_2 - b) / m;

    // same thing for point 2
    // first case we go vertical
    double x2_1 = x2;
    double y2_1 = m * (x2_1) + b;
    // if we go horizontal
    double y2_2 = y2;
    double x2_2 = (y2_2 - b) / m;

    // candidate points on broadway for each trip point:
    // the vertical hit, the horizontal hit, and both endpoints of broadway
    double px1[4] = {x1_1, x1_2, (double)bx1, (double)bx2};
    double py1[4] = {y1_1, y1_2, (double)by1, (double)by2};
    double px2[4] = {x2_1, x2_2, (double)bx1, (double)bx2};
    double py2[4] = {y2_1, y2_2, (double)by1, (double)by2};

    // try every pair, skipping points that fall off the segment
    for (int a = 0; a < 4; a++) {
      if (px1[a] < loX - 1e-9 || px1[a] > hiX + 1e-9)
        continue;
      for (int c = 0; c < 4; c++) {
        if (px2[c] < loX - 1e-9 || px2[c] > hiX + 1e-9)
          continue;
        double dis = manDis(x1, y1, px1[a], py1[a]) +
                     planeDis(px1[a], py1[a], px2[c], py2[c]) +
                     manDis(px2[c], py2[c], x2, y2);
        mini = min(mini, dis);
      }
    }
    printf("%.15f\n", mini);
  }
}
