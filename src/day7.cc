#include <ranges>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
#include <iomanip>
//#include <format>

using namespace std;

// cd build
// cmake ..
// cmake --build .  
// cat ../src/day7input.txt | ./day7

int main(int argc, char** argv){
    vector<int> crabs {};

    while (cin) {
        string s;
        getline(cin, s, ',');
        //cout << "input: " << s << endl;
        if(s.size() > 0)
            crabs.push_back(stoi(s));
    }

    auto minIt = min_element(begin(crabs), end(crabs));
    auto maxIt = max_element(begin(crabs), end(crabs));

    int min = *minIt;
    int max = *maxIt;
    int maxDistance = abs(max-min);

    vector<int> distance(maxDistance);
    distance.push_back(0);
    for(int i = 1; i <= maxDistance; ++i){
        distance[i] = i + distance[i-1];
    }

    auto calcDistanceV1 = [&](int point){
        int totalFuel {0};
        for(auto crab: crabs){
            auto fuel = abs(crab-point);
            totalFuel += fuel;
            //cout << "crab: " << crab << " point: " << point << " fuel: " << fuel << endl; 
        }
        //cout << endl;
        return totalFuel;
    };

    auto calcDistanceV2 = [&](int point){
        int totalFuel {0};
        for(auto crab: crabs){
            auto fuel = distance[abs(crab-point)];
            totalFuel += fuel;
            //cout << "crab: " << crab << " point: " << point << " fuel: " << fuel << endl; 
        }
        //cout << endl;
        return totalFuel;
    };

    {

        int minTotalDistance {numeric_limits<int>::max()};
        int pivot {0};
        for(int i = min; i <= max; ++i){
            auto totalDistance = calcDistanceV1(i);
            if(totalDistance < minTotalDistance){
                minTotalDistance = totalDistance;
                pivot = i;
                //cout << "Pivot: " << setw(2) << pivot << " Fuel: " << minTotalDistance << endl;
            }          
        }

        cout << "Pivot: " << pivot << " Fuel: " << minTotalDistance << endl;
    }

    {
        int minTotalDistance {numeric_limits<int>::max()};
        int pivot {0};
        for(int i = min; i <= max; ++i){
            auto totalDistance = calcDistanceV2(i);
            if(totalDistance < minTotalDistance){
                minTotalDistance = totalDistance;
                pivot = i;
                //cout << "Pivot: " << setw(2) << pivot << " Fuel: " << minTotalDistance << endl;
            }          
        }

        cout << "Pivot: " << pivot << " Fuel: " << minTotalDistance << endl;
    }

    // gcc11 doesn't implement format
    //cout << format("After {0} days, there are {1} fishes", daysToSimulate, fishes.size()) << endl;

    exit(EXIT_SUCCESS);
}