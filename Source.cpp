#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif // !#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

int Count(char* s)
{
    char* t = s;
    int k = 0;

    while ((t = strpbrk(t, "no")) != NULL)
    {
        if ((t[0] == 'n' && t[1] == 'o') || (t[0] == 'o' && t[1] == 'n')) {
            k++;
        }
        t++;
    }

    return k;
}

int ProcessCount(char* fname)
{
    int pos = 0;
    char s[128];
    int k = 0;
    FILE* f;

    if ((f = fopen(fname, "r")) != NULL)
    {
        while (!feof(f)) {
            if ((fgets(s, 128, f)) != NULL) {
                k += Count(s);
            }
        }
        fclose(f);
    }

    return k;
}

int Exists(char* s)
{
    char* t = s;

    while ((t = strpbrk(t, "no")) != NULL)
    {
        if ((t[0] == 'n' && t[1] == 'o') || (t[0] == 'o' && t[1] == 'n')) {
            return 1;
        }
    }

    return 0;
}

int ProcessExists(char* fname)
{
    char s[128];
    FILE* f;

    if ((f = fopen(fname, "r")) != NULL)
    {
        while (!feof(f)) {
            if ((fgets(s, 128, f)) != NULL) {
                if (Exists(s) > 0) {
                    return 1;
                }
            }
        }
        fclose(f);
    }

    return 0;
}

void CreateTXT(char* fname)
{
    char ch;
    char s[128];
    FILE* f;

    if ((f = fopen(fname, "w")) != NULL)
    {
        do {
            cin.get();
            cin.sync();
            cout << "enter line: "; cin >> s;
            strcat(s, "\n");
            fputs(s, f);
            cout << "continue? (y/n): "; cin >> ch;
        } while (ch == 'y' || ch == 'Y');
        fclose(f);
    }

    cout << endl;
}

void PrintTXT(char* fname)
{
    char s[128];
    FILE* f;

    cout << "Context of " << fname << " : " << endl << endl;
    if ((f = fopen(fname, "r")) != NULL)
    {
        while (!feof(f)) {
            if (fgets(s, 128, f)) {
                cout << s;
            }
        }
        fclose(f);
    }

    cout << endl;
}

int main()
{
    char fname[128] = "t.txt";
    cout << "enter file name: "; cin >> fname;

    CreateTXT(fname);
    PrintTXT(fname);

    cout << "Found " << ProcessCount(fname) << " symbols 'no' or 'on' in " << fname << endl << endl;

    return 0;
}
