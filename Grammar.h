//
// Created by 86133 on 2021/11/19.
//

#ifndef LAB1_GRAMMAR_H
#define LAB1_GRAMMAR_H

#endif //LAB1_GRAMMAR_H

#include <cmath>
#include <vector>
#include <stack>
#include "functions.h"
#include "util.h"
#include <stdlib.h>
#include <sstream>

//初始化非终结符集和终结符集
char V[MAXSIZE];
int V_len = 0;
char T[MAXSIZE];
int T_len = 0;
int resultT = 1; //T1 T2 T3

void init_TV(){
    T[0] = '(';T[1] = ')';T[2] = '+';T[3] = '-';T[4] = '*';T[5] = '/';T[6] = 'i';T[7] = '#';
    T_len = 8;
    V[0] = 'E';V[1] = 'T';V[2] = 'F';
    V_len = 3;
}

//可视化状态栈
Stack viewState;
charStack viewChar;

void showVLC(char* s){
    cout<<"剩余字符串: ";
    for (int i = vlc; i < strlen(s); ++i) {
        cout<<s[i];
    }
}


//初始化产生式集
product products[MAXSIZE];
void init_products(){
    products[0].left = 'S';products[0].right = "E";products[0].length = 1;
    products[1].left = 'E';products[1].right = "E+T";products[1].length = 3;
    products[2].left = 'E';products[2].right = "E-T";products[2].length = 3;
    products[3].left = 'E';products[3].right = "T";products[3].length = 1;
    products[4].left = 'T';products[4].right = "T*F";products[4].length = 3;
    products[5].left = 'T';products[5].right = "T/F";products[5].length = 3;
    products[6].left = 'T';products[6].right = "F";products[6].length = 1;
    products[7].left = 'F';products[7].right = "(E)";products[7].length = 3;
    products[8].left = 'F';products[8].right = "i";products[8].length = 1;
}

//索引转换
int changIndex(char c) {
    for (int i = 0; i < T_len; i++) {
        if (T[i] == c)return i;
    }
    for (int i = 0; i < V_len; i++) {
        if (V[i] == c)return T_len + i;
    }
    return -1;
}

//void coutCharstack

//SLR驱动程序
void SLR_Driver() {
    stack<int> s_state;
    stack<char> s_char;
    int i = 0, pos, state/*当前状态*/, code_line = 1, ju = 10;
    char result; //查表结果
    double cd;//下个符号
    int count = 1;
    char c;
    char s[N];
    init_TV();
    init_products();
    init_action();
    init_goto();
    s_state.push(0);//初始状态入栈
    viewState.inStack(0);
    //获取第一个字符
    c = theQueue.front();
    theQueue.pop();
    cout<<endl<<endl<<endl;
    while (1) {
        cout<<"步骤 "<<count<<":"<<endl;
        state = s_state.top();
//        cout<<"[INFO] 当前状态: "<<state<<endl;
        pos = changIndex(c);
//        cout<<"[INFO] pos: "<<pos<<endl;
        result = _action[state][pos];
        viewState.show();//状态栈
        viewChar.show();
        showVLC(viewLeftChars);
//        cout<<"符号c: "<<c<<endl;
//        cout<<"[INFO] result: "<<result<<endl;
        switch (result) {
            case 's': {
                cout<<" 动作: S"<<_goto[state][pos]<<endl;
                s_state.push(_goto[state][pos]);
                viewState.inStack(_goto[state][pos]);
//                cout<<_goto[state][pos]<<" 入状态栈"<<endl;
                s_char.push(c);
                viewChar.push(c);
                vlc++;
//                cout<<c<<" 入符号栈"<<endl;
                c = theQueue.front();
                theQueue.pop();
                count++;
            }
                break;
            case 'r': {
                if (products[_goto[state][pos]].right[0] != '#'){
                    for (int i = 0; i < products[_goto[state][pos]].length; i++) {
//                        cout<<s_state.top()<<" 出栈"<<endl;
                        s_state.pop();
                        viewState.outStack();
                        s_char.pop();
                        viewChar.pop();
                    }

                }
                cout<<" 动作: R"<<_goto[state][pos]<<endl;
                //插入子程序
                switch (_goto[state][pos]) {
                    case 1:
                    {
                        //+的子程序
                        string a,b;
                        a = Stack3.pop();
                        b = Stack2.pop();
                        stringstream stream1;
                        stream1 << "T"<<resultT;
                        resultT++;
                        string temp;
                        stream1>>temp;
                        Stack3.push(temp);
                        string str = "(+,"+a+","+b+","+temp+")";
                        WriteIntoOut2(str);
                    }break;
                    case 2:{
                        //-的子程序
                        string a,b;
                        a = Stack3.pop();
                        b = Stack2.pop();
                        stringstream stream1;
                        stream1 << "T"<<resultT;
                        resultT++;
                        string temp;
                        stream1>>temp;
                        Stack3.push(temp);
                        string str = "(-,"+a+","+b+","+temp+")";
                        WriteIntoOut2(str);
                    }break;
                    case 3:{
                        //r3是T规约为E 从2号栈中拿出到3号栈
                        string temp =Stack2.pop();
                        Stack3.push(temp);
                        cout<<"[INFO] 从2号栈拿出1个 "+temp+" 到3号栈"<<endl;
                    }break;
                    case 4:{
                        //r4是乘法 (*,a,b,result)
                        string a,b;
                        a = Stack2.pop();
                        b = Stack1.pop();
                        stringstream stringstream1;
                        stringstream1<<"T"<<resultT;
                        resultT++;
                        string temp;
                        stringstream1>>temp;
                        Stack2.push(temp);
                        string str = "(*,"+a+","+b+","+temp+")";
                        WriteIntoOut2(str);
                    }break;
                    case 5:{
                        //r4是乘法 (/,a,b,result)
                        string a,b;
                        a = Stack2.pop();
                        b = Stack1.pop();
                        stringstream stringstream1;
                        stringstream1<<"T"<<resultT;
                        resultT++;
                        string temp;
                        stringstream1>>temp;
                        Stack2.push(temp);
                        string str = "(/,"+a+","+b+","+temp+")";
                        WriteIntoOut2(str);
                    }break;
                    case 6:{
                        //F规约为T
                        Stack2.push(Stack1.pop());
                        Stack1.show();
                        Stack2.show();
                        cout<<"[INFO] 从1到2"<<endl;
                    }break;
                    case 7:{
                        //(E) 到 F 就是 E 到F
                        Stack1.push(Stack3.pop());
                        cout<<"[INFO] 从3到1"<<endl;
                    }break;
                    case 8:{
                        //字符规约为F
                        Stack1.push(Stack0.pop());
                        Stack0.show();
                        Stack1.show();
                        cout<<"[INFO] 从0到1"<<endl;
                    }break;
                }
                s_char.push(products[_goto[state][pos]].left);//左部进栈
                viewChar.push(products[_goto[state][pos]].left);
//                cout<<products[_goto[state][pos]].left<<" 进入符号栈"<<endl;
//                cout<<_goto[s_state.top()][changIndex(s_char.top())]<<" 这个值"<<" 栈顶： "<<s_state.top()<<" 列: "<<changIndex(s_char.top())<<endl;
                int temp = _goto[s_state.top()][changIndex(s_char.top())];
                s_state.push(temp); //状态栈更新
                viewState.inStack(temp);
//                s_state.push(_goto[s_state.top()][changIndex(s_char.top())]); //状态栈更新
//                viewState.inStack(_goto[s_state.top()][changIndex(s_char.top())]);
//                cout<<s_state.top()<<" "<<viewState.getTop()<<endl;
//                cout<<_goto[s_state.top()][changIndex(s_char.top())]<<" 进入状态栈"<<endl;
                count++;
            }
                break;
            case 'a': {
                cout<<" 动作: acc"<<endl;
                //accept
                cout<<"[INFO] 分析成功！ 结束"<<endl;
                count++;
                return;
            }
            default:{
                cout<<endl;
                cout<<"[ERROR] 出现错误!"<<endl;
                cout<<"[INFO] 出错信息: state: "<<state<<" result: "<<result<<" position: "<<pos<<" c: "<<c<<endl;
                count++;
                return;
            }
        }
    }

}