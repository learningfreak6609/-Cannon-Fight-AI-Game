#include<iostream>
#include<math.h>
#include<string.h>
#include<map>
#include<bits/stdc++.h>
#include"state.h"
using namespace std;
int timety = 0;

void displayBoard(vector<vector<char>> board){
    int n = board.size();
    int m = board[0].size();
    cerr<<endl<<endl<<"  0 1 2 3 4 5 6 7"<<endl;
    for (int i = 0; i < n; i++){
        cerr<<i<<" ";
        for (int j = 0; j < m; j++){
            cout<<board[i][j]<<" ";
        }
        cerr<<endl;
    }
    cout<<endl;
}

bool operator == (const pair<int,int>& lhs, const pair<int,int>& rhs)
{ return lhs.first==rhs.first && lhs.second==rhs.second; }

string strForm(int v1,int v2,string v3,int v4,int v5){
    string v11= to_string(v1);
    string v12= to_string(v2);
    string v14= to_string(v4);
    string v15= to_string(v5);
    return "S "+v11+" "+v12+" "+v3+" "+v14+" "+v15;
}
// slightly update function to protect same team player from each other*****************************************
vector<string> black_Soldier_moves(int i,int j,vector<vector<char>> board){
    vector<string> output;
    if(j>1){
        if(j<6){ // j:2 3 4 5
            if(i!=0){
                if(i<6){
                    bool bkmov = false;
                    if(board[i-1][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j-1));}
                    else if(board[i-1][j-1] != 'B') { output.push_back(strForm(i,j,"M",i-1,j-1));}
                    if(board[i-1][j] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j));}
                    else if(board[i-1][j] != 'B') { output.push_back(strForm(i,j,"M",i-1,j));}
                    if(board[i-1][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j+1));}
                    else if(board[i-1][j+1] != 'B') { output.push_back(strForm(i,j,"M",i-1,j+1));}
                    if(board[i][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                    if(board[i][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}

                    if(bkmov){ // I am doing that soldier can kill enemy while retreating
                        if(board[i+2][j-2] != 'B' && board[i+2][j-2] != 'G') { output.push_back(strForm(i,j,"M",i+2,j-2));}
                        if(board[i+2][j] != 'B' && board[i+2][j] != 'G') { output.push_back(strForm(i,j,"M",i+2,j));}
                        if(board[i+2][j+2] != 'B' && board[i+2][j+2] != 'G') { output.push_back(strForm(i,j,"M",i+2,j+2));}
                    }
                }
                else{ 
                    if(board[i-1][j-1] == 'W' || board[i-1][j-1] != 'B') { output.push_back(strForm(i,j,"M",i-1,j-1));}
                    if(board[i-1][j] == 'W' || board[i-1][j] != 'B') { output.push_back(strForm(i,j,"M",i-1,j));}
                    if(board[i-1][j+1] == 'W' || board[i-1][j+1] != 'B') { output.push_back(strForm(i,j,"M",i-1,j+1));}
                    if(board[i][j-1] == 'W'){ output.push_back(strForm(i,j,"M",i,j-1));}
                    if(board[i][j+1] == 'W'){ output.push_back(strForm(i,j,"M",i,j+1));}
                }
            }
            else{ // i assumed here that if an soldier near to townHall it still can retreat its path;
                bool bkmov = false;
                if(board[i][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
                if(board[i][j-1] == 'T'){ output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j+1] == 'T'){ output.push_back(strForm(i,j,"M",i,j+1));}
                if(bkmov){
                    if(board[i+2][j-2] != 'B'){ output.push_back(strForm(i,j,"M",i+2,j-2));}
                    if(board[i+2][j] != 'B') { output.push_back(strForm(i,j,"M",i+2,j));}
                    if(board[i+2][j+2] != 'B'){ output.push_back(strForm(i,j,"M",i+2,j+2));}
                }
            }
        }
        else{
            if(i!=0){
                if(i<6){
                    bool bkmov = false;
                    if(board[i-1][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j-1));}
                    else if(board[i-1][j-1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j-1));}
                    if(board[i-1][j] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j));}
                    else if(board[i-1][j] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j));}
                    if(board[i][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}

                    if(j!=7){
                        if(board[i-1][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j+1));}
                        else if(board[i-1][j+1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j+1));}
                        if(board[i][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
                    }
                    
                    if(bkmov){ // I am doing that soldier can kill enemy while retreating
                        if(board[i+2][j-2] != 'B' && board[i+2][j-2] != 'G'){ output.push_back(strForm(i,j,"M",i+2,j-2));}
                        if(board[i+2][j] != 'B' && board[i+2][j] != 'G'){ output.push_back(strForm(i,j,"M",i+2,j));}
                    }
                }
                else{
                    if(board[i-1][j-1] != 'B') { output.push_back(strForm(i,j,"M",i-1,j-1));}
                    if(board[i-1][j] != 'B') { output.push_back(strForm(i,j,"M",i-1,j));}
                    if(board[i][j-1] == 'W'){ output.push_back(strForm(i,j,"M",i,j-1));}
                    if(j!=7){
                        if(board[i-1][j+1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j+1));}
                        if(board[i][j+1] == 'W'){ output.push_back(strForm(i,j,"M",i,j+1));}
                    }
                }
            }
            else{
                bool bkmov = false;
                if(board[i][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j-1] == 'T'){ output.push_back(strForm(i,j,"M",i,j-1));}
                if(j!=7){
                    if(board[i][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
                    if(board[i][j+1] == 'T'){ output.push_back(strForm(i,j,"M",i,j+1));}
                }

                if(bkmov){ // I am doing that soldier can kill enemy while retreating
                    if(board[i+2][j-2] != 'B') { output.push_back(strForm(i,j,"M",i+2,j-2));}
                    if(board[i+2][j] != 'B') { output.push_back(strForm(i,j,"M",i+2,j));}
                }
            } 
        }
    }
    else{
        if(i!=0){
            if(i<6){
                bool bkmov = false;
                if(board[i-1][j] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j));}
                else if(board[i-1][j] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j));}
                if(board[i-1][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i-1,j+1));}
                else if(board[i-1][j+1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j+1));}
                if(board[i][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}

                if(j!=0){
                    if(board[i-1][j-1] == 'W'){bkmov = true; output.push_back(strForm(i,j,"M",i-1,j-1));}
                    else if(board[i-1][j-1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j-1));}
                    if(board[i][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                }

                if(bkmov){ // I am doing that soldier can kill enemy while retreating
                    if(board[i+2][j] != 'B' && board[i+2][j] != 'G'){ output.push_back(strForm(i,j,"M",i+2,j));}
                    if(board[i+2][j+2] != 'B' && board[i+2][j+2] != 'G'){ output.push_back(strForm(i,j,"M",i+2,j+2));}
                }
            }
            else{
                if(board[i-1][j] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j));}
                if(board[i-1][j+1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j+1));}
                if(board[i][j+1] == 'W'){ output.push_back(strForm(i,j,"M",i,j+1));}
                if(j!=0){
                    if(board[i-1][j-1] != 'B'){ output.push_back(strForm(i,j,"M",i-1,j-1));}
                    if(board[i][j-1] == 'W'){ output.push_back(strForm(i,j,"M",i,j-1));}
                }
            }
        }
        else{
            bool bkmov = false;
            if(board[i][j+1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
            if(board[i][j+1] == 'T'){ output.push_back(strForm(i,j,"M",i,j+1));}
            if(j!=0){
                if(board[i][j-1] == 'W'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j-1] == 'T'){ output.push_back(strForm(i,j,"M",i,j-1));}
            }
            if(bkmov){
                if(board[i+2][j] != 'B'){ output.push_back(strForm(i,j,"M",i+2,j));}
                if(board[i+2][j+2] != 'B'){ output.push_back(strForm(i,j,"M",i+2,j+2));}
            }
        }
    }
    return output;
}

vector<string> white_Soldier_moves(int i,int j,vector<vector<char>> board){
    vector<string> output;
    if(j>1){
        if(j<6){
            if(i!=7){
                if(i>1){
                    bool bkmov = false;
                    if(board[i+1][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j-1));}
                    else if(board[i+1][j-1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j-1));}
                    if(board[i+1][j] == 'B' ){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j));}
                    else if(board[i+1][j] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j));}
                    if(board[i+1][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j+1));}
                    else if(board[i+1][j+1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j+1));}
                    if(board[i][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                    if(board[i][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}

                    if(bkmov){ // I am doing that soldier can kill enemy while retreating
                        if(board[i-2][j-2] != 'W' && board[i-2][j-2] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j-2));}
                        if(board[i-2][j] != 'W' && board[i-2][j] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j));}
                        if(board[i-2][j+2] != 'W' && board[i-2][j+2] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j+2));}
                    }
                }
                else{
                    if(board[i+1][j-1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j-1));}
                    if(board[i+1][j] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j));}
                    if(board[i+1][j+1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j+1));}
                    if(board[i][j-1] == 'B'){ output.push_back(strForm(i,j,"M",i,j-1));}
                    if(board[i][j+1] == 'B'){ output.push_back(strForm(i,j,"M",i,j+1));}
                }
            }
            else{
                bool bkmov = false;
                if(board[i][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
                if(board[i][j-1] == 'G'){output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j+1] == 'G'){output.push_back(strForm(i,j,"M",i,j+1));}
                if(bkmov){
                    if(board[i-2][j-2] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j-2));}
                    if(board[i-2][j] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j));}
                    if(board[i-2][j+2] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j+2));}
                }
            }
        }
        else{
            if(i!=7){
                if(i>1){
                    bool bkmov = false;
                    if(board[i+1][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j-1));}
                    else if(board[i+1][j-1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j-1));}
                    if(board[i+1][j] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j));}
                    else if(board[i+1][j] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j));}
                    if(board[i][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}

                    if(j!=7){
                        if(board[i+1][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j+1));}
                        else if(board[i+1][j+1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j+1));}
                        if(board[i][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
                    }

                    if(bkmov){ // I am doing that soldier can kill enemy while retreating
                        if(board[i-2][j-2] != 'W' && board[i-2][j-2] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j-2));}
                        if(board[i-2][j] != 'W' && board[i-2][j] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j));}
                    }
                }
                else{
                    if(board[i+1][j-1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j-1));}
                    if(board[i+1][j] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j));}
                    if(board[i][j-1] == 'B'){ output.push_back(strForm(i,j,"M",i,j-1));}
                    if(j!=7){
                        if(board[i+1][j+1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j+1));}
                        if(board[i][j+1] == 'B'){ output.push_back(strForm(i,j,"M",i,j+1));}
                    }
                }
            }
            else{
                bool bkmov = false;
                if(board[i][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j-1] == 'G'){ output.push_back(strForm(i,j,"M",i,j-1));}

                if(j!=7){
                    if(board[i][j+1] == 'B'){bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
                    if(board[i][j+1] == 'G'){ output.push_back(strForm(i,j,"M",i,j+1));}
                }
                if(bkmov){
                    if(board[i-2][j-2] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j-2));}
                    if(board[i-2][j] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j));}
                }
            }
        }
    }
    else{
        if(i!=7){
            if(i>1){
                bool bkmov = false;
                if(board[i+1][j] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j));}
                else if(board[i+1][j] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j));}
                if(board[i+1][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j+1));}
                else if(board[i+1][j+1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j+1));}
                if(board[i][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}

                if(j!=0){
                    if(board[i+1][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i+1,j-1));}
                    else if(board[i+1][j-1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j-1));}
                    if(board[i][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                }

                if(bkmov){ // I am doing that soldier can kill enemy while retreating
                    if(board[i-2][j] != 'W' && board[i-2][j] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j));}
                    if(board[i-2][j+2] != 'W' && board[i-2][j+2] != 'T'){ output.push_back(strForm(i,j,"M",i-2,j+2));}
                }
            }
            else{
                if(board[i+1][j] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j));}
                if(board[i+1][j+1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j+1));}
                if(board[i][j+1] == 'B'){ output.push_back(strForm(i,j,"M",i,j+1));}
                if(j!=0){
                    if(board[i+1][j-1] != 'W'){ output.push_back(strForm(i,j,"M",i+1,j-1));}
                    if(board[i][j-1] == 'B'){ output.push_back(strForm(i,j,"M",i,j-1));}
                }
            }
        }
        else{
            bool bkmov = false;
            if(board[i][j+1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j+1));}
            if(board[i][j+1] == 'G'){ output.push_back(strForm(i,j,"M",i,j+1));}
            if(j!=0){
                if(board[i][j-1] == 'B'){ bkmov = true; output.push_back(strForm(i,j,"M",i,j-1));}
                if(board[i][j-1] == 'G'){ output.push_back(strForm(i,j,"M",i,j-1));}            
            }
            if(bkmov){
                if(board[i-2][j] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j));}
                if(board[i-2][j+2] != 'W'){ output.push_back(strForm(i,j,"M",i-2,j+2));}
            }
        }
    }
    return output;
}
vector < vector < pair<int,int> > > XcannonsInThisState(vector<vector<char>> board,char X){
    vector < vector < pair<int,int> > > output;
    int counter = 0;
    map<vector < pair<int,int> >, string > mapVal;

    for (int i = 1; i < board.size()-1; i++){
        for (int j = 1; j < board[0].size()-1; j++){
            // horizontal connon : i constant
            for (int p = i-1; p <= i+1; p++){
                vector < pair<int,int> > tmp(3);
                int q = j-1;
                for (; q <= j+1; q++){if(board[p][q] != X) break;}
                if(q == j+2){
                    tmp[0] = pair<int,int>(p,j-1);
                    tmp[1] = pair<int,int>(p,j);
                    tmp[2] = pair<int,int>(p,j+1);
                    if(mapVal.count(tmp) == 0){
                        mapVal[tmp] = "horizantal";
                    }
                }
            }
            // vertical connon : j constant
            for (int q = j-1; q <= j+1; q++){
                vector < pair<int,int> > tmp(3);
                int p = i-1;
                for (; p <= i+1; p++){if(board[p][q] != X) break;}
                if(p == i+2){
                    tmp[0] = pair<int,int>(i-1,q);
                    tmp[1] = pair<int,int>(i,q);
                    tmp[2] = pair<int,int>(i+1,q);
                    if(mapVal.count(tmp) == 0){
                        mapVal[tmp] = "vertical";
                    }
                }
            }
            // diagonal connon
            if(board[i][j] == X){
                if(board[i-1][j-1] == X && board[i+1][j+1] == X){
                    vector < pair<int,int> > tmp(3);
                        tmp[0] = pair<int,int>(i-1,j-1);
                        tmp[1] = pair<int,int>(i,j);
                        tmp[2] = pair<int,int>(i+1,j+1);
                        if(mapVal.count(tmp) == 0){
                            mapVal[tmp] = "backwordSlash diagonal";
                        }
                    }
                if(board[i-1][j+1] == X && board[i+1][j-1] == X){
                    vector < pair<int,int> > tmp(3);
                    tmp[0] = pair<int,int>(i-1,j+1);
                    tmp[1] = pair<int,int>(i,j);
                    tmp[2] = pair<int,int>(i+1,j-1);
                    if(mapVal.count(tmp) == 0){
                        mapVal[tmp] = "forwardSlash diagonal";
                    }
                }
            }
        }
    }
    map<vector < pair<int,int> >,string>::iterator it = mapVal.begin();
    int count = 0;
    while (it != mapVal.end()){
        // cout<<count<<": "<<it->second;
        output.push_back(it->first);
        // vector < pair<int,int> > connon = it->first;
        // int x1 = connon[0].first,x2=connon[1].first,x3=connon[2].first;
        // int y1=connon[0].second,y2=connon[1].second,y3=connon[2].second;
        // cout<<" "<<X<<" [("<<x1<<","<<y1<<")"<<"("<<x2<<","<<y2<<")"<<"("<<x3<<","<<y3<<")] "<<endl;        
        ++it;count++;
    }
    return output;
}

vector<string> connons_moves(cannon_state present , char X){
    char TH = (X == 'W')? 'T':'G';
    vector<vector<char>> board=present.board;
    vector<string> output;
    vector < vector < pair<int,int> > > allCannons = present.cannon_vector;
    for (int cn = 0; cn < allCannons.size(); cn++){
        vector < pair<int,int> > connon = allCannons[cn];

        int x1 = connon[0].first,x2=connon[1].first,x3=connon[2].first;
        int y1=connon[0].second,y2=connon[1].second,y3=connon[2].second;
        // cout<<cn<<": "<<X<<" [("<<x1<<","<<y1<<")"<<"("<<x2<<","<<y2<<")"<<"("<<x3<<","<<y3<<")] "<<endl;
        if(x1 == x2 && x2 == x3){ //horizantal
            int i = x1;
            int j1= y1,j2=y2,j3=y3;
            if(j3+1<board[0].size()){
                if(board[i][j3+1] == '~'){
                    output.push_back(strForm(i,j1,"M",i,j3+1));
                    if(j3+2<board[0].size()){
                        if(board[i][j3+2] != X && board[i][j3+2] != TH) output.push_back(strForm(i,j2,"B",i,j3+2));
                    }
                    if(j3+3<board[0].size()){
                        if(board[i][j3+3] != X && board[i][j3+3] != TH) output.push_back(strForm(i,j2,"B",i,j3+3));
                    }
                }
            }

            if(0<=j1-1){
                if(board[i][j1-1] == '~'){
                    output.push_back(strForm(i,j3,"M",i,j1-1));
                    if(0<=j1-2){
                        // if(board[i][j1-2] != X && board[i][j1-2] != TH) output.push_back(strForm(i,j3,"B",i,j1-2));
                        if(board[i][j1-2] != X && board[i][j1-2] != TH) output.push_back(strForm(i,j2,"B",i,j1-2));
                        // if(board[i][j1-2] != X && board[i][j1-2] != TH) output.push_back(strForm(i,j1,"B",i,j1-2));
                    }
                    if(0<=j1-3){
                        // if(board[i][j1-3] != X && board[i][j1-3] != TH) output.push_back(strForm(i,j3,"B",i,j1-3));
                        if(board[i][j1-3] != X && board[i][j1-3] != TH) output.push_back(strForm(i,j2,"B",i,j1-3));
                        // if(board[i][j1-3] != X && board[i][j1-3] != TH) output.push_back(strForm(i,j1,"B",i,j1-3));
                    }
                }
            }
        }
        else if(y1 == y2 && y2 == y3){ // vertical
            int j =  y1;
            int i1=x1,i2=x2,i3=x3;
            if(i3+1<board.size()){
                if(board[i3+1][j] == '~'){
                    output.push_back(strForm(i1,j,"M",i3+1,j));
                    if(i3+2<board.size()){
                        if(board[i3+2][j] != X && board[i3+2][j] != TH) output.push_back(strForm(i2,j,"B",i3+2,j));
                    }
                    if(i3+3<board.size()){
                        if(board[i3+3][j] != X && board[i3+3][j] != TH) output.push_back(strForm(i2,j,"B",i3+3,j));
                    }
                }
            }

            if(0<=i1-1){
                if(board[i1-1][j] == '~'){
                    output.push_back(strForm(i3,j,"M",i1-1,j));
                    if(0<=i1-2){
                        // if(board[i1-2][j] != X && board[i1-2][j] != TH) output.push_back(strForm(j,i3,"B",j,i1-2));
                        if(board[i1-2][j] != X && board[i1-2][j] != TH) output.push_back(strForm(i2,j,"B",i1-2,j));
                        // if(board[i1-2][j] != X && board[i1-2][j] != TH) output.push_back(strForm(j,i1,"B",j,i1-2));
                    }
                    if(0<=i1-3){
                        // if(board[i1-3][j] != X && board[i1-3][j] != TH) output.push_back(strForm(j,i3,"B",j,i1-3));
                        if(board[i1-3][j] != X && board[i1-3][j] != TH) output.push_back(strForm(i2,j,"B",i1-3,j));
                        // if(board[i1-3][j] != X && board[i1-3][j] != TH) output.push_back(strForm(j,i1,"B",j,i1-3));
                    }
                }
            }
        }
        else if(x1+y1 == x2+y2 && x2+y2 == x3+y3){ // forward slash
            int i1 = x1,i2=x2,i3=x3;
            int j1= y1,j2=y2,j3=y3;
            if( i3+1 < board.size() && j3-1>=0 ){
                if(board[i3+1][j3-1] == '~'){
                    output.push_back(strForm(i1,j1,"M",i3+1,j3-1));
                    if( i3+2 < board.size() && j3-2>=0 ){
                        if(board[i3+2][j3-2] != X && board[i3+2][j3-2] != TH) output.push_back(strForm(i2,j2,"B",i3+2,j3-2));
                    }
                    if( i3+3 < board.size() && j3-3>=0 ){
                        if(board[i3+3][j3-3] != X && board[i3+3][j3-3] != TH) output.push_back(strForm(i2,j2,"B",i3+3,j3-3));
                    }
                }
            }
            if( i1-1>=0 && j1+1  <  board[0].size() ){
                if(board[i1-1][j1+1] == '~'){
                    output.push_back(strForm(i3,j3,"M",i1-1,j1+1));
                    if( i1-2>=0 && j1+2  <  board[0].size() ){
                        if(board[i1-2][j1+2] != X && board[i1-2][j1+2] != TH) output.push_back(strForm(i2,j2,"B",i1-2,j1+2));
                    }
                    if( i1-3 >=0 && j1+3  <  board[0].size() ){
                        if(board[i1-3][j1+3] != X && board[i1-3][j1+3] != TH) output.push_back(strForm(i2,j2,"B",i1-3,j1+3));
                    }
                }
            }
        }
        else{ //backwardSlash case
            int i1 = x1,i2=x2,i3=x3;
            int j1= y1,j2=y2,j3=y3;
            if( i3+1 < board.size() && j3+1 < board[0].size() ){
                if(board[i3+1][j3+1] == '~'){
                    output.push_back(strForm(i1,j1,"M",i3+1,j3+1));
                    if( i3+2 < board.size() && j3+2 < board[0].size() ){
                        if(board[i3+2][j3+2] != X && board[i3+2][j3+2] != TH) output.push_back(strForm(i2,j2,"B",i3+2,j3+2));
                    }
                    if( i3+3 < board.size() && j3+3 < board[0].size() ){
                        if(board[i3+3][j3+3] != X && board[i3+3][j3+3] != TH) output.push_back(strForm(i2,j2,"B",i3+3,j3+3));
                    }
                }
            }
            if( i1-1>=0 && j1-1 >= 0 ){
                if(board[i1-1][j1-1] == '~'){
                    output.push_back(strForm(i3,j3,"M",i1-1,j1-1));
                    if( i1-2>=0 && j1-2 >= 0 ){
                        if(board[i1-2][j1-2] != X && board[i1-2][j1-2] != TH) output.push_back(strForm(i2,j2,"B",i1-2,j1-2));
                    }
                    if( i1-3 >=0 && j1-3 >= 0 ){
                        if(board[i1-3][j1-3] != X && board[i1-3][j1-3] != TH) output.push_back(strForm(i2,j2,"B",i1-3,j1-3));
                    }
                }
            }
        }
    }
    return output;
}