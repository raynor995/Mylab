//
// Created by 86133 on 2021/10/30.
//
#include <iostream>
#include <fstream>
#include<string.h>
#include <stdlib.h>
#include <math.h>
#include <queue>

#ifndef LAB1_FUNCTIONS_H
#define LAB1_FUNCTIONS_H
#endif //LAB1_FUNCTIONS_H
#define MAXSIZE 20

using namespace std;
queue<char> theQueue;

class charStack {
public:
    char value[MAXSIZE];
    int top = 0;

    void push(char c) {
        value[top] = c;
        top++;
    }

    char pop() {
        char temp = value[top - 1];
        top--;
        return temp;
    }

    void show() {
        for (int i = 0; i < top; ++i) {
            cout << value[i];
        }
        cout << endl;
    }
};

class stringStack {
public:
    string value[MAXSIZE];
    int top = 0;

    void push(string str) {
        value[top] = str;
        top++;
    }

    string pop() {
        if (top <= 0) {
            cout << "栈为空栈!" << endl;
            return "null";
        }
        string temp = value[top - 1];
        top--;
        return temp;
    }

    string getTop() {
        try {
            return value[top - 1];
        } catch (exception e) {
            cout << "堆栈为空异常" << endl;
        }
    }

    void show() {
        for (int i = 0; i < top; ++i) {
            cout << value[i];
        }
        cout << endl;
    }

    bool isEmpty() {
        if (top == 0) {
            return true;
        } else
            return false;
    }
};


stringStack StackT, Stack0, Stack1, Stack2, Stack3;

//设置旗子
int reRollFlag[MAXSIZE];

char viewChars[MAXSIZE];
int vc = 0;
char viewLeftChars[MAXSIZE];
int vlc = 0;
int theLine = 1;

void StackReverse(stringStack ST, stringStack S0) {
    while (true) {
        if (ST.isEmpty())
        {
            break;
        }
        S0.push(ST.pop());
    }
    cout << "转换成功!" << endl;
    S0.show();
}

bool Judge(char *s) {
    //该函数用于判断该字符串是否为保留字，如果是，则返回true
    string target[6];
    target[0] = "begin";
    target[1] = "end";
    target[2] = "if";
    target[3] = "else";
    target[4] = "switch";
    target[5] = "case";

    for (auto &j: target) {
        if (strlen(s) == j.size()) {
            //当字符串与target进行匹配的时候要求字符串等长才开始匹配
            int i;
            for (i = 0; i < strlen(s); i++) {
                if (s[i] != j[i]) {
                    break;
                }
            }
            if (i == strlen(s)) {
                cout << "[INFO] " << s << "匹配成功!" << endl;
                return true;
            }
        }

    }
//    cout<<"匹配失败"<<endl;
    return false;
}

char Mygetchar(int *n) {
    char c;
    ifstream in("test.txt");
    in.unsetf(ios::skipws); //对于识别空格的特殊处理
    in.seekg(*n);
    while (in >> c) {
        cout << "n: " << *n << endl;
        if (reRollFlag[*n] != 1) {
            if (c == '\n') {
                reRollFlag[*n] = 1;
                reRollFlag[*n + 1] = 1;
                theLine++;
                cout << "更新行: " << theLine << endl;
            }
        }
        if (c == '\n') {
            //如果识别了换行符
            *n = *n + 1;
            Mygetchar(n);
        }
//        cout<<"[DEBUG] 读取n值: "<<*n<<endl;
//        cout<<"[DEBUG] 读取字符c: |"<<c<<"|"<<endl;
        cout << "n: " << *n << endl;
        *n = *n + 1;
        if (c == 32) {
            return '$';
        }
        return c;
    }
    *n = *n + 1;
    return '#';
}

float toFloat(char *s) {
    //s:2.6E-2
    float front = 0;
    int behind = 0;
    string s1;
    string s2;
    int flag = 0;
    for (int i = 0; i < strlen(s) - 1; ++i) {
        char c = s[i];
        if (flag == 0) {
            if (c != 'E')
                s1 = s1 + c;
        } else {
            s2 = s2 + c;
        }
        if (c == 'E')
            flag = 1;
    }
    front = stof(s1);
    behind = stoi(s2);
    return front * pow(10, behind);
}

void Writing(int type, char *s, bool keep = false) {
    ofstream outfile;
    outfile.open("out.txt", ios::app);
    char *str;
    if (keep) {
        //是保留字的话直接就是字符串s
        str = (char *) malloc(sizeof(char) * (strlen(s) + 1));
        for (int i = 0; i < strlen(s); ++i) {
            str[i] = s[i] - 32;
        }
        str[strlen(s)] = '\0';
    } else {
        str = (char *) malloc(sizeof(char) * (strlen(s) + 1));
        for (int i = 0; i < strlen(s) - 1; i++) {
            str[i] = s[i];
        }
        str[strlen(s) - 1] = '\0';
        //写入的时候会自动少写尾字符
    }


    //写入需要参数字符串和类型
    switch (type) {
        case -1:
            //出错
            outfile << "ERROR" << endl;
        case 8: {
            //整型
            //追加写入
            int n;
            n = atoi(str);
            int yushu, p = 1, result;
            while (1) {
                yushu = n % 2;
                n /= 2;
                result += yushu * p;
                p *= 10;
                if (n < 2) {
                    result += n * p;
                    break;
                }
            }
            theQueue.push('i');
            viewLeftChars[vlc] = 'i';
            vlc++;
            StackT.push(str);
            outfile << "(INT, " << result << "  " << str << ")" << endl;
        }

            break;
        case 9: {
            //实型
            float f = toFloat(s);
            theQueue.push('i');
            viewLeftChars[vlc] = 'i';
            vlc++;
            StackT.push(str);
            outfile << "(REAL," << f << ")" << endl;
        }
            break;
        case 23:
            //实型二类
            theQueue.push('i');
            viewLeftChars[vlc] = 'i';
            vlc++;
            StackT.push(str);
            outfile << "(REAL," << str << ")" << endl;
            break;
        case 1:
            //保留字
            StackT.push(str);
            outfile << "(" << str << ", )" << endl;
            break;
        case 7:
            //标识符
            theQueue.push('i');
            viewLeftChars[vlc] = 'i';
            vlc++;
            StackT.push(str);
            outfile << "(ID,\'" << str << "\')" << endl;
            break;
        case 10:
            //'<'
            outfile << "(LT,  )" << endl;
            break;
        case 11:
            //'<='
            outfile << "(LE,  )" << endl;
            break;
        case 12:
            //'='
            outfile << "(EQ,  )" << endl;
            break;
        case 13:
            //'<>'
            outfile << "(NE,  )" << endl;
            break;
        case 14:
            //'>'outfile << "(GT,  )" << endl;
            break;
        case 15:
            //'>='
            outfile << "(GE,  )" << endl;
            break;
        case 16:
            //':='
            outfile << "(IS,  )" << endl;
            break;
        case 17:
            //'+'
            theQueue.push('+');
            viewLeftChars[vlc] = '+';
            vlc++;
            outfile << "(PL,  )" << endl;
            break;
        case 18:
            //'-'
            theQueue.push('-');
            viewLeftChars[vlc] = '-';
            vlc++;
            outfile << "(MI,  )" << endl;
            break;
        case 19:
            //'*'
            theQueue.push('*');
            viewLeftChars[vlc] = '*';
            vlc++;
            outfile << "(MU,  )" << endl;
            break;
        case 20:
            //'/'
            theQueue.push('/');
            viewLeftChars[vlc] = '/';
            vlc++;
            outfile << "(DI,  )" << endl;
            break;
        case 21:
            // (
            StackT.push(str);
            outfile << "(" << endl;
            break;
        case 22:
            // )
            StackT.push(str);
            outfile << ")" << endl;
    }

}

int excute(int *n, int state, char *s) {
    cout << "[INFO] 进入状态:" << state << endl;
    //通用自动机
    int x = 0;
    int t = *n - 1;
    char c = Mygetchar(n);
    if (c == '$') {
        c = Mygetchar(n);
    }

    cout << "[INFO] 读取字符c: |" << c << "|" << "  ASCII: " << int(c) << endl;

    //**********字符串拼接开始
    char *news = (char *) malloc(sizeof(char) * (t + 1 + 1));

    for (int i = 0; i < strlen(s); i++) {
        news[i] = s[i];
    }
    news[strlen(s)] = c;
    news[strlen(s) + 1] = '\0';
    s = (char *) realloc(s, (sizeof(char)) * (t + 1 + 1));
    for (int i = 0; i < strlen(news); i++) {
        s[i] = news[i];
    }
    s[strlen(news)] = '\0';
//    cout<<"[INFO] 字符串: "<<s<<endl;
    free(news);
    //***********字符串拼接结束

    if (c == '#') {
        //读取到末尾了
        switch (state) {
            case 1:
                //在1状态下读取结束的是保留字或者标识符
                if (Judge(s)) {
                    //如果是的话直接就输出保留字的
                    Writing(1, s, true);
                    cout << "[INFO] 写入保留字" << endl;
                } else {
                    //不是保留字，那么就是标识符
                    Writing(7, s, false);
                    *n = *n - 1;
                    cout << "[INFO] 写入标识符" << endl;
                }
                break;
            case 3:
                //在数字状态下到末尾
                Writing(8, s, false);
                *n = *n - 1;
                cout << "[INFO] 写入整型" << endl;
                break;
            case 5:
                //实型结尾
                Writing(23, s);
                *n = *n - 1;
                cout << "[INFO] 写入实型" << endl;
                break;
            case 7:
                //在7状态读到末尾
                Writing(9, s, false);
                *n = *n - 1;
                cout << "[INFO] 写入实型" << endl;
                break;
            case 9:
                //在9状态读到末尾
                Writing(10, s);
                cout << "[INFO] 写入小于号" << endl;
                break;
            case 10:
                //10到末尾
                Writing(11, s);
                cout << "[INFO] 写入小于等于号" << endl;
                break;
            case 11:
                //等号到末尾
                Writing(12, s);
                cout << "[INFO] 写入等号" << endl;
                break;
            case 12:
                //不等于
                Writing(13, s);
                cout << "[INFO] 写入不等号" << endl;
                break;
            case 13:
                //大于号
                Writing(14, s);
                cout << "[INFO] 写入大于号" << endl;
                break;
            case 14:
                //大于等于
                Writing(15, s);
                cout << "[INFO] 写入大于等于号" << endl;
                break;
            case 15:
                cout << "[ERROR] 在: 读到末尾 发生错误" << endl;
                break;
            case 16:
                //赋值
                Writing(16, s);
                cout << "[INFO] 写入赋值" << endl;
                break;
            case 18:
                //+
                Writing(17, s);
                cout << "[INFO] 写入加号" << endl;
                break;
            case 19:
                //-
                Writing(18, s);
                cout << "[INFO] 写入减号" << endl;
                break;
            case 20:
                //*
                Writing(19, s);
                cout << "[INFO] 写入乘号" << endl;
                break;
            case 21:
                ///
                Writing(20, s);
                cout << "[INFO] 写入除号" << endl;
                break;
        }
        return 0;
    }

    if (c == '(') {
        //小括号
        if (state == 0) {
            theQueue.push('(');
            viewLeftChars[vlc] = '(';
            vlc++;
            Writing(21, s);
        }

    } else if (c == ')') {
        if (state == 0) {
            theQueue.push(')');
            viewLeftChars[vlc] = ')';
            vlc++;
            Writing(22, s);
        }
    }
    if (c >= 48 && c <= 57) {
        //说明是个数字d
        x = 2;
    } else if (c >= 65 && c <= 122) {
        //说明是个字母
        x = 1;
    } else if (c == '<') {
        //说明是小于号 3
        x = 3;
    } else if (c == '=') {
        //是等于号 4
        x = 4;
    } else if (c == '>') {
        //是大于号 5
        x = 5;
    } else if (c == ':') {
        //是冒号 6
        x = 6;
    } else if (c == '+') {
        //是加好7
        x = 7;
    } else if (c == '-') {
        x = 8;
    } else if (c == '*') {
        x = 9;
    } else if (c == '/') {
        x = 10;
    } else if (c == '.') {
        x = 11;
    } else if (c == '(') {
        x = 12;
    } else if (c == ')') {
        x = 13;
    }
    int y = 0;
    if (c >= 48 && c <= 57) {
        //说明是个数字d
        y = 2;
    } else if (c >= 65 && c <= 122) {
        //说明是个字母
        y = 1;
    } //y的其他种类都是0


    switch (state) {
        case 0:
            //0状态
            switch (x) {
                case 0:
                    //其他状态报错
                    cout << "[ERROR]在" << *n << "位置出现了错误,本个单词读取失败" << endl;
                    Writing(-1, s);
                    return -1;
                    break;
                case 1:
                    //0状态字母
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 1 << endl;
                    cout << endl;
                    excute(n, 1, s);
                    break;
                case 2:
                    //0状态数字
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 3 << endl;
                    cout << endl;
                    excute(n, 3, s);
                    break;
                case 3:
                    //小于号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 9 << endl;
                    cout << endl;
                    excute(n, 9, s);
                    break;
                case 4:
                    //等于号 一定是终结态
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 11 << endl;
                    cout << endl;
                    excute(n, 11, s);
                    break;
                case 5:
                    //大于号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 13 << endl;
                    cout << endl;
                    excute(n, 13, s);
                    break;
                case 6:
                    //冒号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 15 << endl;
                    cout << endl;
                    excute(n, 15, s);
                    break;
                case 7:
                    //加号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 18 << endl;
                    cout << endl;
                    excute(n, 18, s);
                    break;
                case 8:
                    //减号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 19 << endl;
                    cout << endl;
                    excute(n, 19, s);
                    break;
                case 9:
                    //乘号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 20 << endl;
                    cout << endl;
                    excute(n, 20, s);
                    break;
                case 10:
                    //除号
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 21 << endl;
                    cout << endl;
                    excute(n, 21, s);
                    break;
                case 11:
                    //是个.
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 4 << endl;
                    cout << endl;
                    excute(n, 4, s);
                    break;
                case 12:
                    //(
                    break;
                case 13:
                    //)
                    break;
            }
            break;
        case 1:
            //状态1
            switch (y) {
                case 1:
                    //字母
                    if (Judge(s)) {
                        //如果已经完成了保留字的匹配
                        Writing(1, s, true);
                        //这个不需要回滚
                        cout << "[INFO] 输出保留字" << endl;
                    } else {
                        cout << endl;
                        cout << "[INFO] " << state << " --" << c << "--> " << 1 << endl;
                        cout << endl;
                        excute(n, 1, s);
                    }
                    break;
                case 2:
                    //数字
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 17 << endl;
                    cout << endl;
                    excute(n, 17, s);
                    break;
                case 0:
                    //'<'
                    if (Judge(s)) {
                        //如果是的话直接就输出保留字的
                        Writing(1, s, true);
                        cout << "[INFO] 输出保留字" << endl;
                    } else {
                        //不是的话就是已经结束了 是标识符
                        Writing(7, s, false);
                        *n = *n - 1;
                        cout << "[INFO] 输出标识符" << endl;
                    }
                    break;
            }
            break;
        case 3:
            //3状态下个不是数字不是.就结束了
            if (y == 2) {
                //数字
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 3 << endl;
                cout << endl;
                excute(n, 3, s);
            } else if (c == '.') {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 4 << endl;
                cout << endl;
                excute(n, 4, s);
            } else if (c == 'E') {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 6 << endl;
                cout << endl;
                excute(n, 6, s);
            } else {
                //是其他  所以结束
                //执行写入函数
                Writing(8, s, false);
                *n = *n - 1;
            }
            break;
        case 4:
            if (x == 2) {
                //是数字
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 5 << endl;
                cout << endl;
                excute(n, 5, s);
            } else {
                cout << "[ERROR]在" << *n << "位置出现了错误,本个单词读取失败" << endl;
                Writing(-1, s);
                return -1;
            }
            break;
        case 5:
            if (c == 'E') {
                //是E
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 6 << endl;
                cout << endl;
                excute(n, 6, s);
            } else if (x == 2) {
                //是数字
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 5 << endl;
                cout << endl;
                excute(n, 5, s);
            } else {
                Writing(23, s);
                *n = *n - 1;
                return -1;
            }
            break;
        case 6:
            if (c == '-') {
                //是负号
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 8 << endl;
                cout << endl;
                excute(n, 8, s);
            } else if (x == 2) {
                //是整数
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 7 << endl;
                cout << endl;
                excute(n, 7, s);
            } else {
                cout << "[ERROR]在" << *n << "位置出现了错误,本个单词读取失败" << endl;
                Writing(-1, s);
                return -1;
            }
            break;
        case 7:
            if (x == 2) {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 7 << endl;
                cout << endl;
                excute(n, 7, s);
            } else {
                //进入结束态
                Writing(9, s, false);
                *n = *n - 1;
                cout << "[INFO] 写入实型" << endl;
            }
            break;
        case 8:
            if (x == 2) {
                //整数
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 7 << endl;
                cout << endl;
                excute(n, 7, s);
            } else {
                cout << "[ERROR]在" << *n << "位置出现了错误,本个单词读取失败" << endl;
                Writing(-1, s);
                return -1;
            }
            break;
        case 9:
            if (c == '=') {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 10 << endl;
                cout << endl;
                excute(n, 10, s);
            } else if (c == '>') {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 12 << endl;
                cout << endl;
                excute(n, 12, s);
            } else {
                //进入小于号的结束态
                Writing(10, s, false);
                cout << "[INFO] 写入小于号" << endl;
                *n = *n - 1;
            }
            break;
        case 10:
            //小于等于的状态
            Writing(11, s, false);
            cout << "[INFO] 写入小于等于号" << endl;
            *n = *n - 1;
            break;
        case 11:
            // '='
            Writing(12, s, false);
            *n = *n - 1;
            cout << "[INFO] 写入等于号" << endl;
            break;
        case 12:
            //'<>'
            Writing(13, s, false);
            *n = *n - 1;
            cout << "[INFO] 写入不等于号" << endl;
            break;
        case 13:
            //'>'
            if (c == '=') {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 14 << endl;
                cout << endl;
                excute(n, 14, s);
            } else {
                //大于状态
                Writing(14, s, false);
                cout << "[INFO] 写入大于号" << endl;
                *n = *n - 1;
            }
            break;
        case 14:
            //'>='
            Writing(15, s, false);
            *n = *n - 1;
            cout << "[INFO] 写入大于等于号" << endl;
            break;
        case 15:
            //':'
            if (c != '=') {
                //冒号不跟等号就报错
            } else {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 16 << endl;
                cout << endl;
                excute(n, 16, s);
            }
            break;
        case 16:
            //16状态下是结束态
            Writing(16, s, false);
            *n = *n - 1;
            cout << "[INFO] 写入赋值" << endl;
            break;
        case 17:
            switch (y) {
                case 2:
                    //是个数字
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 17 << endl;
                    cout << endl;
                    excute(n, 17, s);
                    break;
                case 1:
                    Writing(7, s, false);
                    *n = *n - 1;
                    cout << "[INFO] 输出标识符" << endl;
                    break;
                case 0:
                    Writing(7, s, false);
                    *n = *n - 1;
                    cout << "[INFO] 输出标识符" << endl;
                    break;
            }
        case 18:
            //结束态，输出加号
            Writing(17, s, false);
            *n = *n - 1;
            cout << "[INFO] 输出加号" << endl;
            break;
        case 19:
            //结束态，输出减号
            Writing(18, s, false);
            *n = *n - 1;
            cout << "[INFO] 输出减号" << endl;
            break;
        case 20:
            //结束态，输出乘号
            Writing(19, s, false);
            *n = *n - 1;
            cout << "[INFO] 输出乘号" << endl;
            break;
        case 21:
            //结束态，输出除号
            Writing(20, s, false);
            *n = *n - 1;
            cout << "[INFO] 输出除号" << endl;
            break;
    }
}
