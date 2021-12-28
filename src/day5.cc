#include <ranges>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <regex>
#include <map>
#include <set>

using namespace std;

struct LineRange {
    int x1;
    int y1;
    int x2;
    int y2;
};

struct Point {
    int x;
    int y;

    bool operator<(const Point &ob) const {
        return x < ob.x || (x == ob.x && y < ob.y);
    }
};

// cd build
// cmake ..
// cmake --build .  
// cat ../src/day5input.txt | ./day5

int main(int argc, char** argv){
    regex regex ("^([0-9]+),([0-9]+).->.([0-9]+),([0-9]+)$"s);
    vector<LineRange> lineRanges;

    // load with regex
    while (cin) {
        string line;
        getline(cin, line);
        smatch sm;
        regex_match (line,sm,regex);
        if(sm.size() == 5)
            lineRanges.push_back({.x1 = stoi(sm[1]), .y1 = stoi(sm[2]), .x2 = stoi(sm[3]), .y2 = stoi(sm[4])});
    }


    map<Point,int> points;
    auto insert = [&points] (Point p) {                 
        auto it = points.find(p);
        //cout << "Point: " << p.x << "," << p.y << endl;
        if(it != points.end())
            it->second++;
        else
            points[p] = 1;
    };
    
    // create points
    for(const auto &lineRange  : lineRanges){
        if(lineRange.y1 == lineRange.y2)
        {
            int x1 = min(lineRange.x1, lineRange.x2);
            int x2 = max(lineRange.x1, lineRange.x2);
            for(int x = x1; x <= x2; ++x){
                Point currPoint {x,lineRange.y1};
                insert(currPoint);
            }
        }
        else if(lineRange.x1 == lineRange.x2)
        {
            int y1 = min(lineRange.y1, lineRange.y2);
            int y2 = max(lineRange.y1, lineRange.y2);
            for(int y = y1; y <= y2; ++y){
                Point currPoint {lineRange.x1,y};
                insert(currPoint);
            }
        }
        else if(abs(lineRange.x1 - lineRange.x2) == abs(lineRange.y1 - lineRange.y2)){
            int range = abs(lineRange.x1 - lineRange.x2);
            int xInc{1}, yInc{1};
            if(lineRange.x1 > lineRange.x2)
                xInc = -1;
            if(lineRange.y1 > lineRange.y2)
                yInc = -1;
            int x{lineRange.x1}, y{lineRange.y1};
            for(int i =0; i <= range; ++i){
                Point currPoint {lineRange.x1 + xInc*i, lineRange.y1 + yInc*i};
                insert(currPoint);
            }
        }
    }

    int overlaps = 0;
    for(const auto &point : points){
        if(point.second > 1){
            cout << point.second << " Overlaps. Point: " << point.first.x << "," << point.first.y << endl;
            overlaps++;
        }
    }

    cout << "overlaps: " << overlaps << endl;

    exit(EXIT_SUCCESS);
}