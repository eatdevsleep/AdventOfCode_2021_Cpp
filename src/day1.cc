#include <ranges>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// cd build
// cmake ..
// cmake --build .  
// cat ../src/day1input.txt | ./day1

int main(int argc, char** argv){
    int previousInt = numeric_limits<int>::max();
    int answer = 0;
    vector<int> input; 

    for (auto value : ranges::istream_view<int>(std::cin)) {
        input.push_back(value);
    }

    for (auto value : input) {
        if(previousInt < value)
            answer++;
        previousInt = value;
    }
    cout << answer << endl;

    answer = 0;
    int iterationLength = input.size() - 3;
    for(int i = 0; i < iterationLength; ++i)
    {
        auto a = input[i];
        auto b = input[i+1];
        auto c = input[i+2];
        auto d = input[i+3];

        auto window1 = a+b+c;
        auto window2 = b+c+d;

        if(window2 > window1)
            answer++;
    }

    cout << answer << endl;

    return 0;
}
