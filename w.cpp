#include<iostream>
#include<vector>
using namespace std;

class PocketCube{
private:
    char block[6][2][2];
    vector<char>color={'W','O','G','R','B','Y'};
    string get(vector<int>a){
        string ans;
        switch(block[a[0]][a[1]][a[2]]){
            case 'W':ans="\x1b[89m";break;
            case 'O':ans="\x1b[91m";break;
            case 'G':ans="\x1b[32m";break;
            case 'R':ans="\x1b[31m";break;
            case 'B':ans="\x1b[96m";break;
            case 'Y':ans="\x1b[93m";break;
        }
        ans+=block[a[0]][a[1]][a[2]];
        return ans+"\x1b[0m";
    }
    void move(char c){
        switch(c){
            case 'U':
                turn({0,1,0},{0,1,1},{0,0,1},{0,0,0});
                turn({2,0,0},{3,0,0},{4,0,0},{1,0,0});
                turn({2,0,1},{3,0,1},{4,0,1},{1,0,1});
                break;
            case 'L':
                turn({1,0,0},{1,1,0},{1,1,1},{1,0,1});
                turn({0,0,0},{4,1,1},{5,0,0},{2,0,0});
                turn({0,1,0},{4,0,1},{5,1,0},{2,1,0});
                break;
            case 'F':
                turn({2,0,0},{2,1,0},{2,1,1},{2,0,1});
                turn({0,1,0},{1,1,1},{5,0,1},{3,0,0});
                turn({0,1,1},{1,0,1},{5,0,0},{3,1,0});
                break;
            case 'R':
                turn({3,0,0},{3,1,0},{3,1,1},{3,0,1});
                turn({0,0,1},{2,0,1},{5,0,1},{4,1,0});
                turn({0,1,1},{2,1,1},{5,1,1},{4,0,0});
                break;
            case 'B':
                turn({4,0,0},{4,1,0},{4,1,1},{4,0,1});
                turn({0,0,0},{3,0,1},{5,1,1},{1,1,0});
                turn({0,0,1},{3,1,1},{5,1,0},{1,0,0});
                break;
            case 'D':
                turn({5,0,0},{5,1,0},{5,1,1},{5,0,1});
                turn({2,1,0},{1,1,0},{4,1,0},{3,1,0});
                turn({2,1,1},{1,1,1},{4,1,1},{3,1,1});
                break;
        }
    }
public:
    PocketCube(){
        for(int i=0;i<6;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    block[i][j][k]=color[i];
                }
            }
        }
    }
    void print(){
        cout<<"  "<<get({0,0,0})<<get({0,0,1})<<endl;
        cout<<"  "<<get({0,1,0})<<get({0,1,1})<<endl;
        for(int j=0;j<2;j++){
            for(int i=1;i<=4;i++){
                cout<<get({i,j,0})<<get({i,j,1});
            }
            cout<<endl;
        }
        cout<<"  "<<get({5,0,0})<<get({5,0,1})<<endl;
        cout<<"  "<<get({5,1,0})<<get({5,1,1})<<endl;
    }
    bool isSolved(){
        for(int i=0;i<6;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    if(block[i][j][k]!=color[i])return false;
                }
            }
        }
        return false;
    }
    void turn(vector<int>a,vector<int>b,vector<int>c,vector<int>d){
        int temp=block[a[0]][a[1]][a[2]];
        block[a[0]][a[1]][a[2]]=block[b[0]][b[1]][b[2]];
        block[b[0]][b[1]][b[2]]=block[c[0]][c[1]][c[2]];
        block[c[0]][c[1]][c[2]]=block[d[0]][d[1]][d[2]];
        block[d[0]][d[1]][d[2]]=temp;
    }
    void suffle(string cmd){
        for(int i=0;i<cmd.length();i++){
            if(cmd[i]!=' '){
                move(cmd[i]);
                if(i<cmd.length()-1){
                    if(cmd[i+1]=='2'){
                        move(cmd[i]);
                    }
                    else if(cmd[i+1]=='\''){
                        move(cmd[i]);
                        move(cmd[i]);
                    }
                    i++;
                }
            }
        }
    }//輸入轉動指令，範例： "R2 F2 R' F2 R2 U' F'"
};

int main(){

    PocketCube a;
    a.print();
    cout<<endl;

    string c;
    while(true){
        cout<<"command:";
        getline(cin,c);

        a.suffle(c);
        a.print();

        cout<<endl;
    }
    return 0;
}
