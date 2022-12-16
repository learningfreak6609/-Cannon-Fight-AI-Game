#include<iostream>
#include<bits/stdc++.h>

using namespace std;

class cannon_state {
    public:
    vector<vector<char>> board;
    vector<pair< int , int >> sol_vector;
    vector<pair< int , int >> opp_sol_vector;
    vector < vector < pair<int,int> > > cannon_vector;
    vector < vector < pair<int,int> > > opp_cannon_vector;
    char current_player;
    char opp_player;
    string past_move;
    vector<string> next_cannon_moves;
    vector<string> mext_soldier_moves;

    cannon_state(vector<vector<char>> boardA,
    vector<pair< int , int >> sol_vectorA, char ch, vector < vector < pair<int,int> > > cannon_vectorA) {
        board=boardA;
        sol_vector=sol_vectorA;
        current_player=ch;
        cannon_vector=cannon_vectorA;
        
    }
};