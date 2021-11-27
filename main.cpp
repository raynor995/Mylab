#include <iostream>
#include <fstream>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include "Grammar.h"
using namespace std;
int main(){
    //首先开始定义获取字符的函数，是从文件中读取的
    //设计一个大型自动机 然后状态从S0开始
    //得到状态和字母 然后通过矩阵进行相关的操作 进入下一个状态
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
