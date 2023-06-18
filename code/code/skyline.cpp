//
//  Skyline.cpp
//  Code
//
//  Created by Pranavi Manthena on 9/9/21.
//

#include <iostream>
using namespace std;
 struct building
{
     float left;
     float right;
     float height;
 };
class point
{
    public :
    float left;
    float height;
    point (float l=0 ,float h=0)
    {
        left = l;
        height = h;
    }
};
class skyline
{
    public :
    point* arr;
    skyline(int len)
    {
        arr = new point[len];
        n_ = 0;
    }
   void append(point* p)
   {
       if (n_ > 0 && arr[n_ - 1].height == p->height)
           return;
       if (n_ > 0 && arr[n_ - 1].left == p->left) {
           arr[n_ - 1].height = max(arr[n_ - 1].height, p->height);
           return;
       }
 
       arr[n_] = *p;
       n_++;
   }
//testing purpose
  void print()
    {
        for (int i = 0; i < n_; i++) {
            cout << " (" << arr[i].left << ", "
                 << arr[i].height << "), ";
        }
  }
    int n_;

};

skyline* Mergeskylines(skyline* S1, skyline* S2)
{
    skyline* sol = new skyline(
        S1->n_ + S2->n_);
    float h1_coord = 0, h2_coord = 0;
    int i = 0, j = 0;
    while (i < S1->n_ && j < S2->n_) {
        if (S1->arr[i].left < S2->arr[j].left) {
            float l_coord = S1->arr[i].left;
            h1_coord = S1->arr[i].height;
  
            float h_coord = max(h1_coord, h2_coord);
  
            sol->append(new point(l_coord,h_coord));
            i++;
        }
        else {
            float l_coord = S2->arr[j].left;
            h2_coord = S2->arr[j].height;
            float h_coord = max(h1_coord, h2_coord);
            sol->append(new point(l_coord,h_coord));
            j++;
        }
    }

    while (i < S1->n_) {
        sol->append(&S1->arr[i]);
        i++;
    }
    while (j < S2->n_) {
        sol->append(&S2->arr[j]);
        j++;
    }
    return sol;
}
skyline* MakeSkylineRec(building arr[],int a, int b)
{
    if (a == b) {
        skyline* sol = new skyline(2);
        sol->append(
            new point(
                arr[a].left, arr[a].height));
        sol->append(
            new point(
                arr[a].right, 0));
        return sol;
    }
    int midpt=(a+b)/2;
    skyline* s_left = MakeSkylineRec(
        arr, a, midpt);
    skyline* s_right =MakeSkylineRec(
        arr, midpt + 1, b);
    skyline* sol = Mergeskylines(s_left,s_right);
  

    return sol;
}
skyline* MakeSkyline(building arr[])
{
    float num = *(&arr + 1) - arr;
    skyline* ptr = MakeSkylineRec(arr,0,num-1);
   //testing
    ptr->print();
    return 0;
}


//testing purpose
int main()
{
    building arr[] ={
{1.8,2.3,10.0}, {1.5,2.1,8.0},{0.5,0.8,4.0}, {2.0,2.5,9.0},{3.0,4.0,11.0}, {3.5,4.2,8.0},{3.9,4.4,7.0}, {4.1,4.3,13.0},{4.5,5.2,6.0}, {4.6,5.0,10.0},{2.1,4.7,5.0},{2.2,3.8,6.0},{1.1,1.6,7.0},{4.9,5.7,13.0},{5.3,6.0,6.0},{5.4,5.9,10.0}
        
    };
    MakeSkyline(arr);
};
