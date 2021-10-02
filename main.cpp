#include <iostream>
#include <string>
#include "md5.h"
#include <chrono>

using namespace std;

string altSixBytes(string);
string MD5_Crypt(string);
string crack();

const string salt = "4fTgjp6q";
const string magic = "$1$";
const string hashedPassword = "CxWQeLPwIdqToYNk5yDoS.";
const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

int main() {
//    cout << "crack() goes here" << endl;
    string zeroSum = "0123456789ABCDEF";
    char replacement[] = {
            zeroSum[11], zeroSum[4], zeroSum[10], zeroSum[5],
            zeroSum[3], zeroSum[9], zeroSum[15], zeroSum[2],
            zeroSum[8], zeroSum[14], zeroSum[1],zeroSum[7],
            zeroSum[13], zeroSum[0], zeroSum[6], zeroSum[12], '\0'
    };
    cout << replacement << endl;
    return 0;
}

string altSixBytes(string password) {
    string passSaltPass = password + salt + password;
    return md5(passSaltPass.substr(0, 6));
}

string MD5_Crypt(string password) {
    string concat = password + magic + salt + altSixBytes(password) + password[0] + "\0" + "\0";
    string zeroSum = md5(concat);
    for (int i = 0; i < 1000; i++) {
        string intermediate;
        if (i % 2 == 0) intermediate += zeroSum;
        if (i % 2 != 0) intermediate += password;
        if (i % 3 != 0) intermediate += salt;
        if (i % 7 != 0) intermediate += password;
        if (i % 2 == 0) intermediate += password;
        if (i % 2 != 0) intermediate += zeroSum;
        zeroSum = md5(intermediate);
    }

    // Pick out the 16 bytes in this order: 11 4 10 5 3 9 15 2 8 14 1 7 13 0 6 12.
    char replacement[] = {
            zeroSum[11], zeroSum[4], zeroSum[10], zeroSum[5],
            zeroSum[3], zeroSum[9], zeroSum[15], zeroSum[2],
            zeroSum[8], zeroSum[14], zeroSum[1],zeroSum[7],
            zeroSum[13], zeroSum[0], zeroSum[6], zeroSum[12], '\0'
    };

    return "hi";
}

string crack() {
    string generatedString;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
                for (int x = 0; x < 26; x++)
                    for (int y = 0; y < 26; y++)
                        for (int z = 0; z < 26; z++) {
                            generatedString = alphabet[i] + alphabet[j] + alphabet[k] + alphabet[x] + alphabet[y] + alphabet[z];
                            if (MD5_Crypt(generatedString) == hashedPassword) return generatedString;
                        }
}
