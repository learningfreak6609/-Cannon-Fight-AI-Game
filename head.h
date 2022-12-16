#include<iostream>
#include<math.h>
#include<string.h>
#include<map>
#include<bits/stdc++.h>
#include"moves.h"
// #include"state.h"
using namespace std;

vector<char> splitString(string str){
    vector<char> output;
    for (int i = 0; i < str.length(); i++){
        if(str[i] != ' ') {
            output.push_back(str[i]);
        }
    }
    return output;
}
bool isSoldierMov(vector<char> v){
    int v11 = v[1],v22 = v[2],v44 = v[4],v55 = v[5];
    int v1 = v11-48,v2= v22 - 48,v4= v44 - 48,v5= v55 - 48;
    // (v1,v2) -> (v4,v5)
    for (int i = v1-1; i <= v1+1; i++){
        for (int j = v2-1; j <= v2+1; j++){
            if(i == v4 && j == v5) return true;
        }
    }
    if(v4 == v1-2 && v5 == v2-2) return true;
    else if(v4 == v1-2 && v5 == v2+2) return true;
    else if(v4 == v1+2 && v5 == v2-2) return true;
    else if(v4 == v1+2 && v5 == v2+2) return true;
    else if((v4 == v1 && v5 == v2+2) || (v4 == v1 && v5 == v2-2)) return true;
    else if((v4 == v1-2 && v5 == v2) || (v4 == v1+2 && v5 == v2)) return true;

    return false;
}

cannon_state UserexecuteMov(cannon_state present,string cmd){
    //cannon_state output;
    vector<char> v = splitString(cmd);
    vector<vector<char>> board = present.board;
    vector < vector < pair<int,int> > > cannon_vector = present.cannon_vector;
    char comp_color=present.current_player;
    int v11 = v[1],v22 = v[2],v44 = v[4],v55 = v[5];
    int v1 = v11-48,v2= v22 - 48,v4= v44 - 48,v5= v55 - 48; 

    vector<string> posMov, connonMovs;
    bool correctCmd = true;
    vector<pair<int,int>> soldiers=present.sol_vector;
    //this block only updates ht e board according to the command string
    if(correctCmd){
        //deleteing soldier form the vector when its captired or shot
        if(board[v4][v5]==comp_color) {
            pair<int,int> temp(v4,v5);
            for(int i=0; i<soldiers.size(); i++){
                if(temp==soldiers[i]){
                    soldiers.erase(soldiers.begin()+i);
                    cerr<<"in here";
                }
            }
        }
        //deleting cannons which were disruptured
        if(board[v4][v5]==comp_color){
            pair<int,int> temp(v4,v5);
            cerr<<temp.first<<temp.second<<"remode";
            for(int i=0; i<cannon_vector.size(); i++){
                for(int j=0; j<cannon_vector[0].size();j++){
                    if(temp==cannon_vector[i][j]){
                        cannon_vector.erase(cannon_vector.begin()+i);
                        break;
                    }
                }
            }
        }
        //updating the board
        if(v[3] == 'M'){
            board[v4][v5] = board[v1][v2];
            board[v1][v2] = '~';
        }
        else{
            board[v4][v5] = '~';
        }
    }
    else{
        cerr<<"invalid move type again : ";
        string tA;
        getline (cin, tA);
        present = UserexecuteMov(present,tA);
    }
    cannon_state out(board,soldiers,comp_color,cannon_vector);
    return out;
}

cannon_state SystemExecuteMov(cannon_state present,string cmd){
    vector<vector<char>> board=present.board;
    vector<char> v = splitString(cmd);
    char X =present.current_player;
    int v11 = v[1],v22 = v[2],v44 = v[4],v55 = v[5];
    int v1 = v11-48,v2= v22 - 48,v4= v44 - 48,v5= v55 - 48;
    // (v1,v2) -> (v4,v5)
    vector<pair<int,int>> soldiers=present.sol_vector;
    vector < vector < pair<int,int> > > cannon_vector;
    
    if(v[3] == 'M'){
        board[v4][v5] = board[v1][v2];
        board[v1][v2] = '~';
        pair<int,int> temp(v1,v2);
        for(int i=0; i<soldiers.size(); i++){
            if(temp==soldiers[i]){
                pair<int,int> rep(v4,v5);
                soldiers[i]=rep;
            }
        }
        //check for deleltion of ac annon
        for(int k=0; k<soldiers.size(); k++){
            int i=soldiers[k].first;
            int j=soldiers[k].second;
            //check if its possible to be a middle piece of cannon
            if(i>=1 && i<=6 && j>=1 && j<=6) {
            //vertical
                
                //prime diagonal
                if(board[i-1][j+1]==X && board[i+1][j-1]==X) {
                    vector < pair<int,int> > temp;
                    temp.push_back(pair<int,int>(i-1,j+1));
                    temp.push_back(pair<int,int>(i,j));
                    temp.push_back(pair<int,int>(i+1,j-1));
                    cannon_vector.push_back(temp);
                }
                //second diagonal
                if(board[i-1][j-1]==X && board[i+1][j+1]==X) {
                    vector < pair<int,int> > temp;
                    temp.push_back(pair<int,int>(i-1,j-1));
                    temp.push_back(pair<int,int>(i,j));
                    temp.push_back(pair<int,int>(i+1,j+1));
                    cannon_vector.push_back(temp);
                }
            } 
            if(i>=1 && i<=6)
            {
                //vertical
                if(board[i-1][j]==X && board[i+1][j]==X) {
                    vector < pair<int,int> > temp;
                    temp.push_back(pair<int,int>(i-1,j));
                    temp.push_back(pair<int,int>(i,j));
                    temp.push_back(pair<int,int>(i+1,j));
                    cannon_vector.push_back(temp);
                }
            }
            if(j>=1 && j<=6) {
                //horizontal
                if(board[i][j-1]==X && board[i][j+1]==X) {
                    vector < pair<int,int> > temp;
                    temp.push_back(pair<int,int>(i,j-1));
                    temp.push_back(pair<int,int>(i,j));
                    temp.push_back(pair<int,int>(i,j+1));
                    cannon_vector.push_back(temp);
                }
            }
        }
    }
    else{
        board[v4][v5] = '~';
        //return board;
    }
    cannon_state out(board,soldiers,present.current_player,cannon_vector);
    return out;
}

int utilityFunction(cannon_state present , char X){
    vector<vector<char>> board=present.board;
    char opTH = (X != 'W')? 'T':'G';
    char opS = (X != 'W') ? 'W':'B';
    char TH = (X == 'W')? 'T':'G';
    vector<string> connonMovs = connons_moves(present,X);
    int connonAttack = 0;
    int Tattack = 0;
    for (int k = 0; k < connonMovs.size(); k++){
        if(connonMovs[k][6] == 'B'){
            vector<char> v = splitString(connonMovs[k]);
            int v11 = v[1],v22 = v[2],v44 = v[4],v55 = v[5];
            int v1 = v11-48,v2= v22 - 48,v4= v44 - 48,v5= v55 - 48; 
            if(board[v4][v5] != '~') connonAttack++;
            if(board[v4][v5] == opTH) Tattack++;
        }
    }
    int SoldierAttack = 0;
    int possbileSoldierMove = 0;
    int num_soldiers = 0;
    int num_opp_soldiers = 0;
    int num_townhalls = 0;
    int num_opp_townhalls = 0;
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            if(board[i][j] == X){
                num_soldiers++;
                vector<string> posMov =(X == 'W')? white_Soldier_moves(i,j,board):black_Soldier_moves(i,j,board);
                for (int k = 0; k < posMov.size(); k++){
                    if(posMov[k][6] == 'B'){
                        vector<char> v = splitString(posMov[k]);
                        int v11 = v[1],v22 = v[2],v44 = v[4],v55 = v[5];
                        int v1 = v11-48,v2= v22 - 48,v4= v44 - 48,v5= v55 - 48; 
                        if(board[v4][v5] == opTH) Tattack++; 
                        SoldierAttack++;                       
                    } 
                    possbileSoldierMove++;
                }
            }
            if(board[i][j]==opS)
                num_opp_soldiers++;
            if(board[i][j]==TH) 
                num_townhalls++;
            if(board[i][j]==opTH) 
                num_opp_townhalls++;
        }
    }
    int result = (connonAttack+SoldierAttack)*2+Tattack*5+connonMovs.size()+possbileSoldierMove+
    (num_soldiers-num_opp_soldiers)*10+(num_townhalls-num_opp_townhalls)*20;
    return  result;
}

vector<cannon_state> possibleMoves(cannon_state present,char X){
    vector<cannon_state> output;
    vector<vector<char>> board=present.board;
    vector<pair<int,int>> soldiers=present.sol_vector;

    vector<string> connonMovs = connons_moves(present,X);
    for (int k = 0; k < connonMovs.size(); k++){
        cannon_state temp = SystemExecuteMov(present,connonMovs[k]);
        temp.past_move=connonMovs[k];
        output.push_back(temp);
        // output.push_back(SystemExecuteMov(present,connonMovs[k]));
    }
    
    /*for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            if(board[i][j] == X){
                vector<string> posMov = (X == 'W')? white_Soldier_moves(i,j,board):black_Soldier_moves(i,j,board);
                for (int k = 0; k < posMov.size(); k++){
                    output.push_back(SystemExecuteMov(board,posMov[k]));
                }
            }   
        }
    }*/
    for(int i=0; i<soldiers.size();i++){
        vector<string> posMov = (X == 'W')? white_Soldier_moves(soldiers[i].first,soldiers[i].second,board)
        :black_Soldier_moves(soldiers[i].first,soldiers[i].second,board);
        for (int k = 0; k < posMov.size(); k++){
            //pair< vector<vector<char>>,string > p(SystemExecuteMov(present,posMov[k]),posMov[k]);
            cannon_state temp = SystemExecuteMov(present,posMov[k]);
            temp.past_move=posMov[k];
            output.push_back(temp);
        }
    }
    return output;
}

vector<cannon_state> posMovWithString(cannon_state present, char X){
    vector<vector<char>> board=present.board;
    //char X=present.current_player;
    vector<pair<int,int>> soldiers=present.sol_vector;
    //vector<pair< vector<vector<char>>,string > > output;
    vector<cannon_state> output;

    vector<string> connonMovs = connons_moves(present,X);
    for (int k = 0; k < connonMovs.size(); k++){
        cannon_state temp = SystemExecuteMov(present,connonMovs[k]);
        temp.past_move=connonMovs[k];
        output.push_back(temp);
    }
    /*for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[0].size(); j++){
            if(board[i][j] == X){
                vector<string> posMov = (X == 'W')? white_Soldier_moves(i,j,board):black_Soldier_moves(i,j,board);
                for (int k = 0; k < posMov.size(); k++){
                    pair< vector<vector<char>>,string > p(SystemExecuteMov(board,posMov[k]),posMov[k]);
                    output.push_back(p);
                }
            }
        }
    }*/
    
    for(int i=0; i<soldiers.size();i++){
        vector<string> posMov = (X == 'W')? white_Soldier_moves(soldiers[i].first,soldiers[i].second,board)
        :black_Soldier_moves(soldiers[i].first,soldiers[i].second,board);
        for (int k = 0; k < posMov.size(); k++){
            //pair< vector<vector<char>>,string > p(SystemExecuteMov(present,posMov[k]),posMov[k]);
            cannon_state temp = SystemExecuteMov(present,posMov[k]);
            temp.past_move=posMov[k];
            output.push_back(temp);
        }
    }
    return output;
}
int minimax(cannon_state present,int depth,bool isMaximizingPlayer,int alpha,int beta,char X){
    if(depth == 3) return utilityFunction(present,X);
    else if (isMaximizingPlayer){
        int bestVal = -1000000;
        vector<cannon_state> children = possibleMoves(present,X);
        for (int i = 0; i < children.size(); i++){
            int value = minimax(children[i], depth+1, false, alpha, beta,X);
            bestVal = max( bestVal, value);
            alpha = max( alpha, bestVal);
            if(beta <= alpha) break;
        }
        return bestVal;
    }
    else{
        int bestVal = 1000000;
        vector<cannon_state> children = possibleMoves(present,X);
        for (int i = 0; i < children.size(); i++){
            int value = minimax(children[i], depth+1, true, alpha, beta,X);
            bestVal = min( bestVal, value);
            beta = min( beta, bestVal);
            if(beta <= alpha) break;
        }
        return bestVal;
    }
}

pair<cannon_state,string> systemMov(cannon_state present,char X){
    // vector<vector<vector<char>>> children = possibleMoves(board);
    vector<vector<char>> board=present.board;
    //vector<pair< vector<vector<char>>,string > > children = posMovWithString(board,X);
    vector<cannon_state> children = posMovWithString(present,X);
    //cout<<"hulu"<<endl;
    string movment;
    if(children.size() == 0){
        // cout<<"stalemate condition has been imposed"<<endl;
        pair<cannon_state,string> p(present,present.past_move);
        return p;
    }
    int maxVal = 0,ind = 0;
    // cout<<"children num:"<<children.size()<<endl;
    // bottleneck step here
    for (int i = 0; i < children.size(); i++){
        int value = minimax(children[i],0,true,-1000000,1000000, X);
        // cout<<i<<" "<<value<<endl;
        // cout<<i<<": ("<<children[i].past_move<<")  ";
        // if(i%6 == 0){cout<<endl;}
        if(maxVal <= value){
            ind = i;
            movment = children[i].past_move;
            maxVal = value;
        }
    }
    // cout<<endl;
    // cout<<"system move : "<<movment<<endl;
    pair<cannon_state,string> p(children[ind],movment);
    return p;
}