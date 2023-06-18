//
//  main.cpp
//  HW5
//
//  Created by Pranavi Manthena on 10/25/21.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <utility>
using namespace std;
bool find(vector<pair<string,string>> L, pair<string,string> P){
    for(int i=0;i<L.size();i++)
    {
        if((L[i].first.compare(P.first)==0) && (L[i].second.compare(P.second)==0))
            return true;
    }
    return false;
}
bool solve(vector<pair<string,string>> L,char S[],int start, int end, vector<vector<int>>* arr)
{
    string s1,s2;
    int i = 0,j = 0;
    bool result = false;
    if(start==end)
    {
        (*arr)[start][end] = 0;
        return false;}
    if(start>end){
        return true;
    }
    if((end-start+1)%2!=0){
        (*arr)[start][end] = 0;
        return false;
    }
    
    if ((*arr)[start][end]!=-1){
        return ((*arr)[start][end]==1);
    }
    
    else
    {
        for (i=start;i<=end;i++)
        {
            for (j=start+1;j<=end;j++)
            {   s1=S[i];
                s2=S[j];
                auto p =  make_pair(s1,s2);
                if(find(L,p))
                {
                    result = (solve(L,S,start,i-1,arr) && solve(L,S,i+1,j-1,arr)&&solve(L,S,j+1,end,arr));
                    if (result)
                    {
                        (*arr)[i][j] = 1;
                        return true;
                    }
                }
            
            }
        }
    }
    (*arr)[start][end] = 0;
    return false;
}

int main() {
     int i,j;
    vector<vector<int>> arr;
    bool ans;
    vector<pair<string,string>> L = {{"a","b"},{"b","c"},{"a","a"}};
    char S[] = "baca";
    //(a, a) (a, b), (b, c) aabcaa babaacab baca
    auto size = (int)strlen(S);
    for (i=0;i<strlen(S);i++)
    {
        vector<int> temp;
        for (j=0;j<strlen(S);j++)
        {
         temp.push_back(-1);
        }
        arr.push_back(temp);
    }
    ans = solve(L,S,0,size-1,&arr);
    if(ans==0)
    {
        cout<<"FALSE"<<endl;
    }
    else
    {
        cout<<"TRUE"<<endl;
    }
    return 0;
}
