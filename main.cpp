#include <iostream>
#include <fstream>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include "Grammar.h"
using namespace std;
int main(){
    //���ȿ�ʼ�����ȡ�ַ��ĺ������Ǵ��ļ��ж�ȡ��
    //���һ�������Զ��� Ȼ��״̬��S0��ʼ
    //�õ�״̬����ĸ Ȼ��ͨ�����������صĲ��� ������һ��״̬
    int n=0;
    int switch_note = 0;
    while (true){
        if (Mygetchar(&n) == '#')
            break;
        n = n-1;
        char* s = (char*)malloc(sizeof(char));
        s[0] = '\0';
        excute(&n,0,s);
    }
    theQueue.push('#');
    viewLeftChars[vlc] = '#';
    vlc = 0;
    SLR_Driver();
}
