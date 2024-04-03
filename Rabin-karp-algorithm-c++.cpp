#include <iostream>
#include <fstream>
#include <string>
#include <climits>
using namespace std;

#define d 256

void search(const string& pat, const string& txt, int q) {
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int p = 0;
    int t = 0;
    int h = 1;
    bool found = false;

    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    for (i = 0; i <= N - M; i++) {
        if (p == t) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }
            if (j == M) {
                cout << "Pattern found at index " << i+1<< endl;
                found = true;
            }
        }
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;
            if (t < 0)
                t = (t + q);
        }
    }

    if (!found) {
        cout << "Pattern not found." << endl;
    }
}

int main() {
    ifstream inputFile("input.txt");
    string txt, pat;
    int q = INT_MAX;
    int numTestCases = 4; 

    if (inputFile.is_open()) {
        for (int testCase = 0; testCase < numTestCases; ++testCase) {
            getline(inputFile, txt);
            getline(inputFile, pat);
            cout<<endl;
            cout<<"Output of testcase "<<testCase+1<<":"<<endl;
            search(pat, txt, q);
        }
        inputFile.close();
    } else {
        cout << "Unable to open file." << endl;
    }

    return 0;
}
