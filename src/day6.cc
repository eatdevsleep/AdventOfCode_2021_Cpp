#include <ranges>
#include <iostream>
#include <limits>
#include <vector>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
//#include <format>

using namespace std;

// cd build
// cmake ..
// cmake --build .  
// cat ../src/day6input.txt | ./day6

void print(const array<long,9> &fishes, int day){
    long fishCount = accumulate(fishes.begin(), fishes.end(), 0L);
    cout << "After " << day << " days, there are " << fishCount << " fishes [";
    cout << fishes[0] << ",";
    cout << fishes[1] << ",";
    cout << fishes[2] << ",";
    cout << fishes[3] << ",";
    cout << fishes[4] << ",";
    cout << fishes[5] << ",";
    cout << fishes[6] << ",";
    cout << fishes[7] << ",";
    cout << fishes[8] << "]";
    cout <<  endl;
}

int main(int argc, char** argv){
    array<long, 9> fishes {0L};

    // load with regex
    while (cin) {
        string s;
        getline(cin, s, ',');
        if(s.size() > 0)
            fishes[stoi(s)]++;
    }

    const int daysToSimulate = 256;    

    print(fishes, 0);

    for(int d = 0; d < daysToSimulate; ++d)
    {
        long tempEndLife = fishes[0];
        for(int i = 1; i < 9; ++i){
            fishes[i-1] = fishes[i];
        }
        fishes[8] = tempEndLife;
        fishes[6] += tempEndLife;

        print(fishes,d+1);
    }

    // gcc11 doesn't implement format
    //cout << format("After {0} days, there are {1} fishes", daysToSimulate, fishes.size()) << endl;

    exit(EXIT_SUCCESS);
}