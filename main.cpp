#include<iostream>
#include<bits/stdc++.h>
#include"head.h"

using namespace std;

int main(int argc, char const *argv[])
{
    time_t start, end; 
    int mode,n,m,time;
    cin>>mode>>n>>m>>time;
    cerr<<mode;
    char X;
    if(mode==1)
        X='B';
    else X='W';

    vector<vector<char>> board{{'T','W','T','W','T','W','T','W'},
                                {'~','W','~','W','~','W','~','W'},
                                {'~','W','~','W','~','W','~','W'},
                                {'~','~','~','~','~','~','~','~'},
                                {'~','~','~','~','~','W','~','~'},
                                {'B','~','B','~','B','~','B','~'},
                                {'B','~','B','~','B','~','B','~'},
                                {'B','G','B','G','B','G','B','G'}};

    //assigning soldiers
    vector<pair<int,int>> vector_soldiers;
    for(int i=0; i<board.size();i++){
        for(int j=0; j<board[0].size(); j++){
            if(board[i][j]==X) {
                pair <int, int> temp (i,j);
                vector_soldiers.push_back(temp);
                // cout<<temp.first<<temp.second<<endl;
            }
        }
    }

    //assigning cannons
    vector < vector < pair<int,int> > > cannon_vector;
    for(int k=0; k<vector_soldiers.size(); k++){
        int i=vector_soldiers[k].first;
        int j=vector_soldiers[k].second;
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

    cannon_state current_state(board,vector_soldiers,X,cannon_vector);

    /*if(mode==2){
        //taking move form user
        string a,b,c,d,e,f;
        //cin.ignore();
        //getline (cin, opponentMov);
        cin>>a>>b>>c>>d>>e>>f;
        
        string opponentMov=a+" "+c+" "+b+" "+d+" "+f+" "+e;
        current_state = UserexecuteMov(current_state,opponentMov);
        // char temp1=opponentMov[2];
        // opponentMov[2]=opponentMov[4];
        // opponentMov[4]=temp1;
        // char temp2=opponentMov[8];
        // opponentMov[8]=opponentMov[10];
        // opponentMov[10]=temp2;
        //displayBoard(current_state.board);
    }*/
    
    if(mode==1){
        for (int i = 0; i < 100; i++){
            
            
            
            // displayBoard(current_state.board);
            // cout<<"-------------------------------------------------------------------------"<<endl;
            //clock_t time_req;
            pair<cannon_state,string> p = systemMov(current_state,X);
            
            //time_req = clock() - time_req;
            current_state = p.first;

            // vector < vector < pair<int,int> > > cannonVec = current_state.cannon_vector;
            // for (int l = 0; l < cannonVec.size(); l++){
            //     vector < pair<int,int> > convoc = cannonVec[l];
            //     for (int h = 0; h < convoc.size(); h++){
            //         cout<<"("<<convoc[h].first<<","<<convoc[h].second<<"),";
            //     }
            //     cout<<endl;
            // }
            
            string sysMov = p.second;
            //displayBoard(current_state.board);
            char temp3=sysMov[2];
            sysMov[2]=sysMov[4];
            sysMov[4]=temp3;
            char temp4=sysMov[8];
            sysMov[8]=sysMov[10];
            sysMov[10]=temp4;
            cout<<sysMov<<endl;
            for(int i=0; i<current_state.sol_vector.size();i++){
                cerr<<current_state.sol_vector[i].first<<current_state.sol_vector[i].second<<endl;
            }
            for(int i=0;i<current_state.cannon_vector.size();i++){
                for(int j=0;j<current_state.cannon_vector[0].size();j++){
                    cerr<<current_state.cannon_vector[i][j].first<<current_state.cannon_vector[i][j].second<<" ";
                }
                cerr<<endl;
            }
            cerr<<"hello";
            string a,b,c,d,e,f;
            //cin.ignore();
            //getline (cin, opponentMov);
            cin>>a>>b>>c>>d>>e>>f;
            
            string opponentMov=a+" "+c+" "+b+" "+d+" "+f+" "+e;
            //current_state = SystemExecuteMov(current_state,opponentMov);
            //cerr<<"user move : ";
            
            
            current_state = UserexecuteMov(current_state,opponentMov);
            //displayBoard(current_state.board);
            //cout<<"system mov : "<<sysMov<<" ,time_req : "<<(double)time_req/CLOCKS_PER_SEC<<" sec"<<endl;
            //displayBoard(current_state.board);
            // cout<<"-------------------------------------------------------------------------"<<endl;
        }
    }
    else {
        for (int i = 0; i < 100; i++){
            
            
            string a,b,c,d,e,f;
            //cin.ignore();
            //getline (cin, opponentMov);
            cin>>a>>b>>c>>d>>e>>f;
            
            string opponentMov=a+" "+c+" "+b+" "+d+" "+f+" "+e;
            //current_state = SystemExecuteMov(current_state,opponentMov);
            //cerr<<"user move : ";
            
            
            current_state = UserexecuteMov(current_state,opponentMov);
            // displayBoard(current_state.board);
            // cout<<"-------------------------------------------------------------------------"<<endl;
            //clock_t time_req;
            pair<cannon_state,string> p = systemMov(current_state,X);
            
            //time_req = clock() - time_req;
            current_state = p.first;

            // vector < vector < pair<int,int> > > cannonVec = current_state.cannon_vector;
            // for (int l = 0; l < cannonVec.size(); l++){
            //     vector < pair<int,int> > convoc = cannonVec[l];
            //     for (int h = 0; h < convoc.size(); h++){
            //         cout<<"("<<convoc[h].first<<","<<convoc[h].second<<"),";
            //     }
            //     cout<<endl;
            // }
            
            string sysMov = p.second;
            //displayBoard(current_state.board);
            char temp3=sysMov[2];
            sysMov[2]=sysMov[4];
            sysMov[4]=temp3;
            char temp4=sysMov[8];
            sysMov[8]=sysMov[10];
            sysMov[10]=temp4;
            cout<<sysMov<<endl;
            for(int i=0; i<current_state.sol_vector.size();i++){
                cerr<<current_state.sol_vector[i].first<<current_state.sol_vector[i].second<<endl;
            }
            for(int i=0;i<current_state.cannon_vector.size();i++){
                for(int j=0;j<current_state.cannon_vector[0].size();j++){
                    cerr<<current_state.cannon_vector[i][j].first<<current_state.cannon_vector[i][j].second<<" ";
                }
                cerr<<endl;
            }
            cerr<<"hello";
            
            //displayBoard(current_state.board);
            //cout<<"system mov : "<<sysMov<<" ,time_req : "<<(double)time_req/CLOCKS_PER_SEC<<" sec"<<endl;
            //displayBoard(current_state.board);
            // cout<<"-------------------------------------------------------------------------"<<endl;
        }
    }
    return 0;
}