// gcc does not support modules 
#include <algorithm>
#include <ranges>
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>

using namespace std;

// cd build
// cmake ..
// cmake --build ..  
// cat ../src/day3input.txt | ./day3

vector<int> GetBinaryCount(vector<string>& strings){
   int size = strings[0].size();
    vector<int> counts(size, 0);

    for(auto value : strings){
        for(int i = 0; i < size; ++i){
            switch(value[i]){
                case '1':
                counts[i]++;
                break;
                case '0':
                counts[i]--;
                break;
            }
        }
    }
    return counts;
}

int main(int argc, char** argv){
    vector<string> input; 

    for (auto value : ranges::istream_view<string>(cin)) {
        input.push_back(value);
    }


    auto counts = GetBinaryCount(input);
    int size = input[0].size();


    cout << "Size: " << size << endl;
    for(int i = 0; i < size; ++i){
        cout << counts[i] << "_";    
    }
    cout << endl;
    

    long gamma {0}, epsilon {0};
    for(long i = 0; i < size; ++i){
        long factor = size - 1 - i;
        long power = pow(2L, factor);
        if(counts[i] > 0){
            cout << "gamma add: " << power << endl;
            gamma += power;
        }
        else{
            cout << "epsilon add: " << power << endl;
            epsilon += power;
        }
    }

    cout << "gamma: "s << gamma << endl;
    cout << "epsilon: "s << epsilon << endl;

    cout << gamma * epsilon << endl;

    vector<string> oxygenStore;
    ranges::copy(input, back_inserter(oxygenStore));

    for(int i = 0; i < size; ++i){
        vector<string> temp;
        auto counts = GetBinaryCount(oxygenStore);
        ranges::copy_if(oxygenStore, back_inserter(temp), 
            [&counts, i](const string& n){return ((n[i] == '1' && counts[i] >= 0) || (n[i] == '0' && counts[i] < 0));});
        oxygenStore = temp;
        cout << "oxygen Store size: " << oxygenStore.size() << endl;
        if(oxygenStore.size() == 1)
            break;
    }

    vector<string> co2Store;
    ranges::copy(input, back_inserter(co2Store));

    for(int i = 0; i < size; ++i){
        vector<string> temp;
        auto counts = GetBinaryCount(co2Store);
        ranges::copy_if(co2Store, back_inserter(temp), 
            [&counts, i](const string& n){return ((n[i] == '0' && counts[i] >= 0) || (n[i] == '1' && counts[i] < 0));});
        co2Store = temp;
        cout << "CO2 Store size: " << co2Store.size() << endl;
        if(co2Store.size() == 1)
            break;
    }
    
    string oxygenString = oxygenStore[0];
    string co2String = co2Store[0];

    cout << "oxygen: " << oxygenString << endl;
    cout << "CO2: " << co2String << endl;

    long oxygen {0}, co2 {0};
    for(long i = 0; i < size; ++i){
        long factor = size - 1 - i;
        long power = pow(2L, factor);
        if(oxygenString[i] == '1'){
            cout << "oxygen add: " << power << endl;
            oxygen += power;
        }
        if(co2String[i] == '1'){
            cout << "CO2 add: " << power << endl;
            co2 += power;
        }
    }

    cout << oxygen << endl;
    cout << co2 << endl;

    cout << oxygen*co2 << endl;

    return 0;
}
