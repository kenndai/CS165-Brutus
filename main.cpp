#include <iostream>
#include <string>
#include "md5.h"
#include <chrono>
//TODO #include md5 library

using namespace std;

void generateString(int);
string sixBytes(string);
string MD5Crypt(string);

// To check a password, you’d read the hash from /etc/shadow, extract the salt, run the algorithm (crypt()?)
// on this salt and the candidate password, and then see if the resulting hash matches what you have.

//TODO 1. Alternate Sum: md5(salt + pass + salt)
//TODO 2.

const string salt = "4fTgjp6q";
const string magic = "$1$";
const string hash = "CxWQeLPwIdqToYNk5yDoS.";
const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

int main() {
    return 0;
}

void generateString() {
    string generatedString;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
                for (int x = 0; x < 26; x++)
                    for (int y = 0; y < 26; y++)
                        for (int z = 0; z < 26; z++) {
                            generatedString = alphabet[i] + alphabet[j] + alphabet[k] + alphabet[x] + alphabet[y] + alphabet[z];
                            // if (MD5Crypt(generatedString) == hashedPassword) return generatedString
                            cout << generatedString << endl;
                        }
}

string altSixBytes(string password) {
    string passSaltPass = password + salt + password;
    return md5(passSaltPass.substr(0, 6));
}

string MD5Crypt(string password) {
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
    return "hi";
}