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


//��ʼ�����ս�������ս����
char V[MAXSIZE];
int V_len = 0;
char T[MAXSIZE];
int T_len = 0;
void init_TV(){
    T[0] = '(';T[1] = ')';T[2] = '+';T[3] = '-';T[4] = '*';T[5] = '/';T[6] = 'i';T[7] = '#';
    T_len = 8;
    V[0] = 'E';V[1] = 'T';V[2] = 'F';
    V_len = 3;
}

//���ӻ�״̬ջ
Stack viewState;
charStack viewChar;

void showVLC(char* s){
    cout<<"ʣ���ַ���: ";
    for (int i = vlc; i < strlen(s); ++i) {
        cout<<s[i];
    }
}


//��ʼ������ʽ��
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

//����ת��
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

//SLR��������
void SLR_Driver() {
    stack<int> s_state;
    stack<char> s_char;
    int i = 0, pos, state/*��ǰ״̬*/, code_line = 1, ju = 10;
    char result; //�����
    double cd;//�¸�����
    int count = 1;
    char c;
    char s[N];
    init_TV();
    init_products();
    init_action();
    init_goto();
    s_state.push(0);//��ʼ״̬��ջ
    viewState.inStack(0);
    //��ȡ��һ���ַ�
    c = theQueue.front();
    theQueue.pop();
    cout<<endl<<endl<<endl;
    while (1) {
        cout<<"���� "<<count<<":"<<endl;
        state = s_state.top();
//        cout<<"[INFO] ��ǰ״̬: "<<state<<endl;
        pos = changIndex(c);
//        cout<<"[INFO] pos: "<<pos<<endl;
        result = _action[state][pos];
        viewState.show();//״̬ջ
        viewChar.show();
        showVLC(viewLeftChars);
//        cout<<"����c: "<<c<<endl;
//        cout<<"[INFO] result: "<<result<<endl;
        switch (result) {
            case 's': {
                cout<<" ����: S"<<_goto[state][pos]<<endl;
                s_state.push(_goto[state][pos]);
                viewState.inStack(_goto[state][pos]);
//                cout<<_goto[state][pos]<<" ��״̬ջ"<<endl;
                s_char.push(c);
                viewChar.push(c);
                vlc++;
//                cout<<c<<" �����ջ"<<endl;
                c = theQueue.front();
                theQueue.pop();
                count++;
            }
                break;
            case 'r': {
                if (products[_goto[state][pos]].right[0] != '#'){
                    for (int i = 0; i < products[_goto[state][pos]].length; i++) {
//                        cout<<s_state.top()<<" ��ջ"<<endl;
                        s_state.pop();
                        viewState.outStack();
                        s_char.pop();
                        viewChar.pop();
                    }

                }
                cout<<" ����: R"<<_goto[state][pos]<<endl;
                s_char.push(products[_goto[state][pos]].left);//�󲿽�ջ
                viewChar.push(products[_goto[state][pos]].left);
//                cout<<products[_goto[state][pos]].left<<" �������ջ"<<endl;
//                cout<<_goto[s_state.top()][changIndex(s_char.top())]<<" ���ֵ"<<" ջ���� "<<s_state.top()<<" ��: "<<changIndex(s_char.top())<<endl;
                int temp = _goto[s_state.top()][changIndex(s_char.top())];
                s_state.push(temp); //״̬ջ����
                viewState.inStack(temp);
//                s_state.push(_goto[s_state.top()][changIndex(s_char.top())]); //״̬ջ����
//                viewState.inStack(_goto[s_state.top()][changIndex(s_char.top())]);
//                cout<<s_state.top()<<" "<<viewState.getTop()<<endl;
//                cout<<_goto[s_state.top()][changIndex(s_char.top())]<<" ����״̬ջ"<<endl;
                count++;
            }
                break;
            case 'a': {
                cout<<" ����: acc"<<endl;
                //accept
                cout<<"[INFO] �����ɹ��� ����"<<endl;
                count++;
                return;
            }
            default:{
                cout<<endl;
                cout<<"[ERROR] ���ִ���!"<<endl;
                cout<<"[INFO] ������Ϣ: state: "<<state<<" result: "<<result<<" position: "<<pos<<" c: "<<c<<endl;
                count++;
                return;
            }
        }
    }

}