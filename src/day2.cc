#include <ranges>
#include <iostream>
#include <limits>
#include <tuple>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

enum class Direction {
    forward, 
    down,
    up
};

int main(int argc, char** argv){
    unordered_map<string, Direction> enumMap {{"forward", Direction::forward}, {"down", Direction::down}, {"up", Direction::up}};
    vector<tuple<Direction, int>> input;

    while(cin){       
        string directionString {};
        int distance {};
        cin >> directionString >> distance;
        input.push_back(make_tuple(enumMap[directionString], distance));
    }

    {
        int position {};
        int depth {};
        for(auto [direction, distance] : input){
            switch(direction){
                case Direction::forward:
                    position += distance;
                break;
                case Direction::down:
                    depth += distance;
                break;
                case Direction::up:
                    depth -= distance;
                break;
            }
        }

        cout << position * depth << endl;
    }

    {
        int horizontalPos {};
        int depth {};
        int aim {};
        for(auto [direction, distance] : input){
            switch(direction){
                case Direction::forward:
                    horizontalPos += distance;
                    depth += aim * distance;
                break;
                case Direction::down:
                    aim += distance;
                break;
                case Direction::up:
                    aim -= distance;
                break;
            }
        }

        cout << horizontalPos * depth << endl;
    }


}
