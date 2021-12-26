// gcc does not support modules 
#include <algorithm>
#include <ranges>
#include <iostream>
#include <limits>
#include <vector>
#include <cmath>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std;

// https://stackoverflow.com/questions/9158150/colored-output-in-c
#define RESET   "\033[0m"
#define GREEN   "\033[32m"      /* Green */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */

// cd build
// cmake ..
// cmake --build .  
// cat ../src/day4input.txt | ./day4

struct matchLocation {
    int boardIndex;
    int rowIndex;
    int columnIndex;
};
const int boardDim = 5;
struct matches {
    bool isMatched {0};
    array<array<bool,boardDim>,boardDim> ticks;
    array<int,boardDim> rowMatches {0};
    array<int,boardDim> columnMatches {0};
};

int main(int argc, char** argv){
    

    // first load the number sequence
    vector<int> bingoSequence; 
    {
        string sequenceString;
        getline(cin, sequenceString);
        istringstream strStream(sequenceString); //create string stream from the string
        while(strStream.good()) {
            string substr;
            getline(strStream, substr, ','); //get first string delimited by comma
            bingoSequence.push_back(stoi(substr));
        }
        getline(cin, sequenceString);
    }

    vector<array<array<int, boardDim>, boardDim>> boards;
    multimap<int, matchLocation> matchMap;
    vector<matches> boardState;
    {
        int boardIndex {0};
        // load the boards
        while(cin){
            {
                string line;
                
                boards.push_back(array<array<int, boardDim>, boardDim>{});
                
                for(int i =0; i < boardDim; i++){
                    for(int j =0; j < boardDim; j++){
                        cin >> boards[boardIndex][i][j];
                        matchMap.insert(make_pair(
                            boards[boardIndex][i][j], 
                            matchLocation{.boardIndex = boardIndex, .rowIndex = i, .columnIndex = j}));
                    }
                }
                
                boardState.push_back(matches{{0},{0}});
                boardIndex++;
                getline(cin, line);
            }
        }
    }

    // find all matches
    int matches = 0;
    for(int bingoNumber : bingoSequence){
        cout << "bingo number: " << bingoNumber << endl;
        auto boardMatches = matchMap.equal_range(bingoNumber);
        for (auto i = boardMatches.first; i != boardMatches.second; ++i)
        {
            auto& matchLocation = i->second;
            if(boardState[matchLocation.boardIndex].isMatched) continue; //don't check bpards already matched
            boardState[matchLocation.boardIndex].ticks[matchLocation.rowIndex][matchLocation.columnIndex] = true;
            bool rowMatch = (++(boardState[matchLocation.boardIndex].rowMatches[matchLocation.rowIndex]))==boardDim;
            bool columnMatch = (++(boardState[matchLocation.boardIndex].columnMatches[matchLocation.columnIndex]))==boardDim;
            if(rowMatch | columnMatch)
            {
                cout << ++matches << " boards matched, index " << matchLocation.boardIndex << endl;
                boardState[matchLocation.boardIndex].isMatched = true;
                for(int i =0; i < boardDim; i++){
                    for(int j =0; j < boardDim; j++){
                        if(!boardState[matchLocation.boardIndex].ticks[i][j])
                            cout << "(" << setw(2) << boards[matchLocation.boardIndex][i][j] << ") ";
                        else{
                            if((rowMatch && matchLocation.rowIndex == i) || (columnMatch && matchLocation.columnIndex == j))
                                cout << BOLDGREEN << "[" << setw(2) << boards[matchLocation.boardIndex][i][j] << "] " << RESET;
                            else
                                cout << GREEN << "[" << setw(2) << boards[matchLocation.boardIndex][i][j] << "] " << RESET;
                        }
                            
                    }
                    cout << endl;
                }

                // sum board
                int sum {0};
                for(int i =0; i < boardDim; i++){
                    for(int j =0; j < boardDim; j++){
                        if(!boardState[matchLocation.boardIndex].ticks[i][j])
                            sum += boards[matchLocation.boardIndex][i][j];
                    }
                }
                cout << sum * bingoNumber << endl;
            }    

        }
    }





    exit(EXIT_SUCCESS);
}
