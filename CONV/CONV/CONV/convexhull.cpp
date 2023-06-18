//
//  Convex Hull.cpp
//  Codes
//
//  Created by Pranavi Manthena on 9/12/21.
//

#include <iostream>
#include<vector>
#include<cmath>
using namespace std;
struct point
{
    float x;
    float y;
};

int findside(point p1 , point p2, point p3)
{
    int z = (p3.y - p1.y) * (p2.x - p1.x) -
                  (p2.y - p1.y) * (p3.x - p1.x);
      
        if (z > 0)
            return 1;
        if (z < 0)
            return -1;
        return 0;
}
int distance(point p1, point p2, point p3)
{
    int d = (abs ((p2.x - p1.x) * (p1.y - p3.y) -
               (p1.x - p3.x) * (p2.y - p1.y))/sqrt(pow((p2.x-p1.x),2)+pow((p2.y-p1.y),2)));
    return d;
}
std::vector<point> ConvexHull(std::vector<point> pts, point p1 ,point p2,int side)
{
    int max = 0;
    int temp = -1;
    for (int i=0; i<pts.size(); i++)
    {
        int t = distance(p1, p2, pts[i]);
        if (t > max && findside(p1, p2, pts[i]) == side)
        {
           
            max = t;
            temp = i;
        }
    }
    if ( temp == -1 ){
        return {};
    }
    std::vector<point> hull;
    hull.push_back(pts[temp]);
    
    std::vector<point> section_1 = ConvexHull(pts, p1 ,pts[temp], side);
    std::vector<point> section_3 = ConvexHull(pts, pts[temp] ,p2, side);
    
    hull.insert(hull.end(),section_1.begin(),section_1.end());
    hull.insert(hull.end(),section_3.begin(),section_3.end());
    return hull;
}

std::vector<point> FindHull(std::vector<point> pts){
    int min_x = 0, max_x = 0;
    for (int i=1; i< pts.size(); i++){
        if (pts[i].x < pts[min_x].x)
               min_x = i;
        if (pts[i].x > pts[max_x].x)
               max_x = i;
    }
    std::vector<point> hull;
    hull.push_back(pts[min_x]);
    hull.push_back(pts[max_x]);
    
    std::vector<point> upper_hull = ConvexHull(pts, pts[min_x] ,pts[max_x], 1);
    std::vector<point> lower_hull = ConvexHull(pts, pts[min_x] ,pts[max_x], -1);

    hull.insert(hull.end(),upper_hull.begin(),upper_hull.end());
    hull.insert(hull.end(),lower_hull.begin(),lower_hull.end());
    return hull;
}
//testing
int main()
{
    std::vector<point> inputs = FindHull({{152,202},{549,234},{266,342},{274,245},{329,155},{253,112},
        {409,69},{499,203},{441,330},{375,378},{362,267},{330,369},{485,333},{188,304},{287,279},{356,311},{431,282},{375,228},{217,296},{237,177},{275,78},{203,107},{462,137},{379,167},{365,88},{509,114}});
    
    for ( int i = 0 ; i < inputs.size(); i ++ ){
        cout << inputs[i].x << "," << inputs[i].y << "\n";
    }
}

