//
// Created by 86133 on 2021/11/19.
//

#ifndef LAB1_UTIL_H
#define LAB1_UTIL_H
#define N 10
#endif //LAB1_UTIL_H

class Stack{
public:
    int value[MAXSIZE];
    int top = 0;
    Stack(){
    }
    void show(){
        cout<<"状态栈: ";
        for (int i = 1; i <= top; ++i) {
            cout<<value[i-1];
        }
        cout<<" ";
    }
    void inStack(int state){
        value[top] = state;
        top++;
    }
    void outStack(){
        if (top<=0){
            //栈为空
            cout<<"栈为空 出错啦！"<<endl;
        } else{
            top--;
        }
    }
    int getTop(){
        return value[top-1];
    }
};

//action、goto 分析表
char _action[MAXSIZE][MAXSIZE];
int _goto[MAXSIZE][MAXSIZE];

//初始化action表
void init_action() {
    for (int i = 0; i < MAXSIZE; ++i) {
        for (int j = 0; j < MAXSIZE; ++j) {
            _action[i][j] = 'e';
            //默认是error
        }
    }
    //手动初始化
    _action[0][0] = 's';
    _action[0][6] = 's';
    _action[1][2] = 's';
    _action[1][3] = 's';
    _action[1][7] = 'a';
    _action[2][1] = 'r';
    _action[2][2] = 'r';
    _action[2][3] = 'r';
    _action[2][4] = 's';
    _action[2][5] = 's';
    _action[2][7] = 'r';
    _action[3][1] = 'r';
    _action[3][2] = 'r';
    _action[3][3] = 'r';
    _action[3][4] = 'r';
    _action[3][5] = 'r';
    _action[3][7] = 'r';
    _action[4][0] = 's';
    _action[4][6] = 's';
    _action[5][1] = 'r';
    _action[5][2] = 'r';
    _action[5][3] = 'r';
    _action[5][4] = 'r';
    _action[5][5] = 'r';
    _action[5][7] = 'r';
    _action[6][0] = 's';
    _action[6][6] = 's';
    _action[7][0] = 's';
    _action[7][6] = 's';
    _action[8][0] = 's';
    _action[8][6] = 's';
    _action[9][0] = 's';
    _action[9][6] = 's';
    _action[10][1] = 's';
    _action[10][2] = 's';
    _action[10][3] = 's';
    _action[11][1] = 'r';
    _action[11][2] = 'r';
    _action[11][3] = 'r';
    _action[11][4] = 's';
    _action[11][5] = 's';
    _action[11][7] = 'r';
    _action[12][1] = 'r';
    _action[12][2] = 'r';
    _action[12][3] = 'r';
    _action[12][4] = 's';
    _action[12][5] = 's';
    _action[12][7] = 'r';
    _action[13][1] = 'r';
    _action[13][2] = 'r';
    _action[13][3] = 'r';
    _action[13][4] = 'r';
    _action[13][5] = 'r';
    _action[13][7] = 'r';
    _action[14][1] = 'r';
    _action[14][2] = 'r';
    _action[14][3] = 'r';
    _action[14][4] = 'r';
    _action[14][5] = 'r';
    _action[14][7] = 'r';
    _action[15][1] = 'r';
    _action[15][2] = 'r';
    _action[15][3] = 'r';
    _action[15][4] = 'r';
    _action[15][5] = 'r';
    _action[15][7] = 'r';

}

//初始化goto表
void init_goto() {
    for (int i = 0; i < MAXSIZE; ++i) {
        for (int j = 0; j < MAXSIZE; ++j) {
            _goto[MAXSIZE][MAXSIZE] = -1;
        }
    }
    //手动初始化
    _goto[0][0] = 4;
    _goto[0][6] = 5;
    _goto[0][8] = 1;
    _goto[0][9] = 2;
    _goto[0][10] = 3;
    _goto[1][2] = 6;
    _goto[1][3] = 7;
    _goto[2][1] = 3;
    _goto[2][2] = 3;
    _goto[2][3] = 3;
    _goto[2][4] = 8;
    _goto[2][5] = 9;
    _goto[2][7] = 3;
    _goto[3][1] = 6;
    _goto[3][2] = 6;
    _goto[3][3] = 6;
    _goto[3][4] = 6;
    _goto[3][5] = 6;
    _goto[3][7] = 6;
    _goto[4][0] = 4;
    _goto[4][6] = 5;
    _goto[4][8] = 10;
    _goto[4][9] = 2;
    _goto[4][10] = 3;
    _goto[5][1] = 8;
    _goto[5][2] = 8;
    _goto[5][3] = 8;
    _goto[5][4] = 8;
    _goto[5][5] = 8;
    _goto[5][7] = 8;
    _goto[6][0] = 4;
    _goto[6][6] = 5;
    _goto[6][9] = 11;
    _goto[6][10] = 3;
    _goto[7][0] = 4;
    _goto[7][6] = 5;
    _goto[7][9] = 12;
    _goto[7][10] = 3;
    _goto[8][0] = 4;
    _goto[8][6] = 5;
    _goto[8][10] = 13;
    _goto[9][0] = 4;
    _goto[9][6] = 5;
    _goto[9][10] = 14;
    _goto[10][1] = 15;
    _goto[10][2] = 6;
    _goto[10][3] = 7;
    _goto[11][1] = 1;
    _goto[11][2] = 1;
    _goto[11][3] = 1;
    _goto[11][4] = 8;
    _goto[11][5] = 9;
    _goto[11][7] = 1;
    _goto[12][1] = 2;
    _goto[12][2] = 2;
    _goto[12][3] = 2;
    _goto[12][4] = 8;
    _goto[12][5] = 9;
    _goto[12][7] = 2;
    _goto[13][1] = 4;
    _goto[13][2] = 4;
    _goto[13][3] = 4;
    _goto[13][4] = 4;
    _goto[13][5] = 4;
    _goto[13][7] = 4;
    _goto[14][1] = 5;
    _goto[14][2] = 5;
    _goto[14][3] = 5;
    _goto[14][4] = 5;
    _goto[14][5] = 5;
    _goto[14][7] = 5;
    _goto[15][1] = 7;
    _goto[15][2] = 7;
    _goto[15][3] = 7;
    _goto[15][4] = 7;
    _goto[15][5] = 7;
    _goto[15][7] = 7;
}


//产生式
class product{
public:
    char left;
//    char right[N]; //产生式最多三个符号
    string  right;
    int length; //产生式右部长度
};


//字符串比对函数
bool mystrcmp(char *s,char *p){
    int i=0,j=0;
    while(s[i]!='\0' && p[j]!='\0' && s[i]==p[j]){++i;++j;}
    if(s[i]=='\0' && p[j]=='\0')return true;
    else return false;
}

//判断是否为操作符
bool is_operate(char c){
    char op[4] = {'+','-','*','/'};
    int i =0;
    while (op[i] != '\0'){
        if(op[i] == c)
            return true;
        i++;
    }
    return false;
}