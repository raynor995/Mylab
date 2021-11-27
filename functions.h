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
            cout << "ջΪ��ջ!" << endl;
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
            cout << "��ջΪ���쳣" << endl;
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

//��������
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
    cout << "ת���ɹ�!" << endl;
    S0.show();
}

bool Judge(char *s) {
    //�ú��������жϸ��ַ����Ƿ�Ϊ�����֣�����ǣ��򷵻�true
    string target[6];
    target[0] = "begin";
    target[1] = "end";
    target[2] = "if";
    target[3] = "else";
    target[4] = "switch";
    target[5] = "case";

    for (auto &j: target) {
        if (strlen(s) == j.size()) {
            //���ַ�����target����ƥ���ʱ��Ҫ���ַ����ȳ��ſ�ʼƥ��
            int i;
            for (i = 0; i < strlen(s); i++) {
                if (s[i] != j[i]) {
                    break;
                }
            }
            if (i == strlen(s)) {
                cout << "[INFO] " << s << "ƥ��ɹ�!" << endl;
                return true;
            }
        }

    }
//    cout<<"ƥ��ʧ��"<<endl;
    return false;
}

char Mygetchar(int *n) {
    char c;
    ifstream in("test.txt");
    in.unsetf(ios::skipws); //����ʶ��ո�����⴦��
    in.seekg(*n);
    while (in >> c) {
        cout << "n: " << *n << endl;
        if (reRollFlag[*n] != 1) {
            if (c == '\n') {
                reRollFlag[*n] = 1;
                reRollFlag[*n + 1] = 1;
                theLine++;
                cout << "������: " << theLine << endl;
            }
        }
        if (c == '\n') {
            //���ʶ���˻��з�
            *n = *n + 1;
            Mygetchar(n);
        }
//        cout<<"[DEBUG] ��ȡnֵ: "<<*n<<endl;
//        cout<<"[DEBUG] ��ȡ�ַ�c: |"<<c<<"|"<<endl;
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
        //�Ǳ����ֵĻ�ֱ�Ӿ����ַ���s
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
        //д���ʱ����Զ���дβ�ַ�
    }


    //д����Ҫ�����ַ���������
    switch (type) {
        case -1:
            //����
            outfile << "ERROR" << endl;
        case 8: {
            //����
            //׷��д��
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
            //ʵ��
            float f = toFloat(s);
            theQueue.push('i');
            viewLeftChars[vlc] = 'i';
            vlc++;
            StackT.push(str);
            outfile << "(REAL," << f << ")" << endl;
        }
            break;
        case 23:
            //ʵ�Ͷ���
            theQueue.push('i');
            viewLeftChars[vlc] = 'i';
            vlc++;
            StackT.push(str);
            outfile << "(REAL," << str << ")" << endl;
            break;
        case 1:
            //������
            StackT.push(str);
            outfile << "(" << str << ", )" << endl;
            break;
        case 7:
            //��ʶ��
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
    cout << "[INFO] ����״̬:" << state << endl;
    //ͨ���Զ���
    int x = 0;
    int t = *n - 1;
    char c = Mygetchar(n);
    if (c == '$') {
        c = Mygetchar(n);
    }

    cout << "[INFO] ��ȡ�ַ�c: |" << c << "|" << "  ASCII: " << int(c) << endl;

    //**********�ַ���ƴ�ӿ�ʼ
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
//    cout<<"[INFO] �ַ���: "<<s<<endl;
    free(news);
    //***********�ַ���ƴ�ӽ���

    if (c == '#') {
        //��ȡ��ĩβ��
        switch (state) {
            case 1:
                //��1״̬�¶�ȡ�������Ǳ����ֻ��߱�ʶ��
                if (Judge(s)) {
                    //����ǵĻ�ֱ�Ӿ���������ֵ�
                    Writing(1, s, true);
                    cout << "[INFO] д�뱣����" << endl;
                } else {
                    //���Ǳ����֣���ô���Ǳ�ʶ��
                    Writing(7, s, false);
                    *n = *n - 1;
                    cout << "[INFO] д���ʶ��" << endl;
                }
                break;
            case 3:
                //������״̬�µ�ĩβ
                Writing(8, s, false);
                *n = *n - 1;
                cout << "[INFO] д������" << endl;
                break;
            case 5:
                //ʵ�ͽ�β
                Writing(23, s);
                *n = *n - 1;
                cout << "[INFO] д��ʵ��" << endl;
                break;
            case 7:
                //��7״̬����ĩβ
                Writing(9, s, false);
                *n = *n - 1;
                cout << "[INFO] д��ʵ��" << endl;
                break;
            case 9:
                //��9״̬����ĩβ
                Writing(10, s);
                cout << "[INFO] д��С�ں�" << endl;
                break;
            case 10:
                //10��ĩβ
                Writing(11, s);
                cout << "[INFO] д��С�ڵ��ں�" << endl;
                break;
            case 11:
                //�Ⱥŵ�ĩβ
                Writing(12, s);
                cout << "[INFO] д��Ⱥ�" << endl;
                break;
            case 12:
                //������
                Writing(13, s);
                cout << "[INFO] д�벻�Ⱥ�" << endl;
                break;
            case 13:
                //���ں�
                Writing(14, s);
                cout << "[INFO] д����ں�" << endl;
                break;
            case 14:
                //���ڵ���
                Writing(15, s);
                cout << "[INFO] д����ڵ��ں�" << endl;
                break;
            case 15:
                cout << "[ERROR] ��: ����ĩβ ��������" << endl;
                break;
            case 16:
                //��ֵ
                Writing(16, s);
                cout << "[INFO] д�븳ֵ" << endl;
                break;
            case 18:
                //+
                Writing(17, s);
                cout << "[INFO] д��Ӻ�" << endl;
                break;
            case 19:
                //-
                Writing(18, s);
                cout << "[INFO] д�����" << endl;
                break;
            case 20:
                //*
                Writing(19, s);
                cout << "[INFO] д��˺�" << endl;
                break;
            case 21:
                ///
                Writing(20, s);
                cout << "[INFO] д�����" << endl;
                break;
        }
        return 0;
    }

    if (c == '(') {
        //С����
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
        //˵���Ǹ�����d
        x = 2;
    } else if (c >= 65 && c <= 122) {
        //˵���Ǹ���ĸ
        x = 1;
    } else if (c == '<') {
        //˵����С�ں� 3
        x = 3;
    } else if (c == '=') {
        //�ǵ��ں� 4
        x = 4;
    } else if (c == '>') {
        //�Ǵ��ں� 5
        x = 5;
    } else if (c == ':') {
        //��ð�� 6
        x = 6;
    } else if (c == '+') {
        //�ǼӺ�7
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
        //˵���Ǹ�����d
        y = 2;
    } else if (c >= 65 && c <= 122) {
        //˵���Ǹ���ĸ
        y = 1;
    } //y���������඼��0


    switch (state) {
        case 0:
            //0״̬
            switch (x) {
                case 0:
                    //����״̬����
                    cout << "[ERROR]��" << *n << "λ�ó����˴���,�������ʶ�ȡʧ��" << endl;
                    Writing(-1, s);
                    return -1;
                    break;
                case 1:
                    //0״̬��ĸ
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 1 << endl;
                    cout << endl;
                    excute(n, 1, s);
                    break;
                case 2:
                    //0״̬����
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 3 << endl;
                    cout << endl;
                    excute(n, 3, s);
                    break;
                case 3:
                    //С�ں�
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 9 << endl;
                    cout << endl;
                    excute(n, 9, s);
                    break;
                case 4:
                    //���ں� һ�����ս�̬
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 11 << endl;
                    cout << endl;
                    excute(n, 11, s);
                    break;
                case 5:
                    //���ں�
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 13 << endl;
                    cout << endl;
                    excute(n, 13, s);
                    break;
                case 6:
                    //ð��
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 15 << endl;
                    cout << endl;
                    excute(n, 15, s);
                    break;
                case 7:
                    //�Ӻ�
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 18 << endl;
                    cout << endl;
                    excute(n, 18, s);
                    break;
                case 8:
                    //����
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 19 << endl;
                    cout << endl;
                    excute(n, 19, s);
                    break;
                case 9:
                    //�˺�
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 20 << endl;
                    cout << endl;
                    excute(n, 20, s);
                    break;
                case 10:
                    //����
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 21 << endl;
                    cout << endl;
                    excute(n, 21, s);
                    break;
                case 11:
                    //�Ǹ�.
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
            //״̬1
            switch (y) {
                case 1:
                    //��ĸ
                    if (Judge(s)) {
                        //����Ѿ�����˱����ֵ�ƥ��
                        Writing(1, s, true);
                        //�������Ҫ�ع�
                        cout << "[INFO] ���������" << endl;
                    } else {
                        cout << endl;
                        cout << "[INFO] " << state << " --" << c << "--> " << 1 << endl;
                        cout << endl;
                        excute(n, 1, s);
                    }
                    break;
                case 2:
                    //����
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 17 << endl;
                    cout << endl;
                    excute(n, 17, s);
                    break;
                case 0:
                    //'<'
                    if (Judge(s)) {
                        //����ǵĻ�ֱ�Ӿ���������ֵ�
                        Writing(1, s, true);
                        cout << "[INFO] ���������" << endl;
                    } else {
                        //���ǵĻ������Ѿ������� �Ǳ�ʶ��
                        Writing(7, s, false);
                        *n = *n - 1;
                        cout << "[INFO] �����ʶ��" << endl;
                    }
                    break;
            }
            break;
        case 3:
            //3״̬�¸��������ֲ���.�ͽ�����
            if (y == 2) {
                //����
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
                //������  ���Խ���
                //ִ��д�뺯��
                Writing(8, s, false);
                *n = *n - 1;
            }
            break;
        case 4:
            if (x == 2) {
                //������
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 5 << endl;
                cout << endl;
                excute(n, 5, s);
            } else {
                cout << "[ERROR]��" << *n << "λ�ó����˴���,�������ʶ�ȡʧ��" << endl;
                Writing(-1, s);
                return -1;
            }
            break;
        case 5:
            if (c == 'E') {
                //��E
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 6 << endl;
                cout << endl;
                excute(n, 6, s);
            } else if (x == 2) {
                //������
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
                //�Ǹ���
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 8 << endl;
                cout << endl;
                excute(n, 8, s);
            } else if (x == 2) {
                //������
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 7 << endl;
                cout << endl;
                excute(n, 7, s);
            } else {
                cout << "[ERROR]��" << *n << "λ�ó����˴���,�������ʶ�ȡʧ��" << endl;
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
                //�������̬
                Writing(9, s, false);
                *n = *n - 1;
                cout << "[INFO] д��ʵ��" << endl;
            }
            break;
        case 8:
            if (x == 2) {
                //����
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 7 << endl;
                cout << endl;
                excute(n, 7, s);
            } else {
                cout << "[ERROR]��" << *n << "λ�ó����˴���,�������ʶ�ȡʧ��" << endl;
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
                //����С�ںŵĽ���̬
                Writing(10, s, false);
                cout << "[INFO] д��С�ں�" << endl;
                *n = *n - 1;
            }
            break;
        case 10:
            //С�ڵ��ڵ�״̬
            Writing(11, s, false);
            cout << "[INFO] д��С�ڵ��ں�" << endl;
            *n = *n - 1;
            break;
        case 11:
            // '='
            Writing(12, s, false);
            *n = *n - 1;
            cout << "[INFO] д����ں�" << endl;
            break;
        case 12:
            //'<>'
            Writing(13, s, false);
            *n = *n - 1;
            cout << "[INFO] д�벻���ں�" << endl;
            break;
        case 13:
            //'>'
            if (c == '=') {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 14 << endl;
                cout << endl;
                excute(n, 14, s);
            } else {
                //����״̬
                Writing(14, s, false);
                cout << "[INFO] д����ں�" << endl;
                *n = *n - 1;
            }
            break;
        case 14:
            //'>='
            Writing(15, s, false);
            *n = *n - 1;
            cout << "[INFO] д����ڵ��ں�" << endl;
            break;
        case 15:
            //':'
            if (c != '=') {
                //ð�Ų����Ⱥžͱ���
            } else {
                cout << endl;
                cout << "[INFO] " << state << " --" << c << "--> " << 16 << endl;
                cout << endl;
                excute(n, 16, s);
            }
            break;
        case 16:
            //16״̬���ǽ���̬
            Writing(16, s, false);
            *n = *n - 1;
            cout << "[INFO] д�븳ֵ" << endl;
            break;
        case 17:
            switch (y) {
                case 2:
                    //�Ǹ�����
                    cout << endl;
                    cout << "[INFO] " << state << " --" << c << "--> " << 17 << endl;
                    cout << endl;
                    excute(n, 17, s);
                    break;
                case 1:
                    Writing(7, s, false);
                    *n = *n - 1;
                    cout << "[INFO] �����ʶ��" << endl;
                    break;
                case 0:
                    Writing(7, s, false);
                    *n = *n - 1;
                    cout << "[INFO] �����ʶ��" << endl;
                    break;
            }
        case 18:
            //����̬������Ӻ�
            Writing(17, s, false);
            *n = *n - 1;
            cout << "[INFO] ����Ӻ�" << endl;
            break;
        case 19:
            //����̬���������
            Writing(18, s, false);
            *n = *n - 1;
            cout << "[INFO] �������" << endl;
            break;
        case 20:
            //����̬������˺�
            Writing(19, s, false);
            *n = *n - 1;
            cout << "[INFO] ����˺�" << endl;
            break;
        case 21:
            //����̬���������
            Writing(20, s, false);
            *n = *n - 1;
            cout << "[INFO] �������" << endl;
            break;
    }
}
