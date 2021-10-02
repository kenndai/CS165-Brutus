#include <iostream>
#include "md5.h"
#include <chrono>
//TODO #include md5 library

using namespace std;

const string salt = "4fTgjp6q";
const string magic = "$1$";
const string hash = "CxWQeLPwIdqToYNk5yDoS.";

const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

void generateString(int);
string sixBytes(string);
string MD5Crypt(string);

// To check a password, you’d read the hash from /etc/shadow, extract the salt, run the algorithm (crypt()?)
// on this salt and the candidate password, and then see if the resulting hash matches what you have.

//TODO 1. Alternate Sum: md5(salt + pass + salt)
//TODO 2.


int main() {
//    auto start = chrono::steady_clock::now();
//    generateString(26);
//    auto end = chrono::steady_clock::now();
//    cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " sec";
    return 0;
}

void generateString(int stringLength) {
    string generatedString;
    for (int i = 0; i < stringLength; i++)
        for (int j = 0; j < stringLength; j++)
            for (int k = 0; k < stringLength; k++)
                for (int x = 0; x < stringLength; x++)
                    for (int y = 0; y < stringLength; y++)
                        for (int z = 0; z < stringLength; z++) {
                            generatedString = alphabet[i] + alphabet[j] + alphabet[k] + alphabet[x] + alphabet[y] + alphabet[z];
                            // if (hash(generatedString) == hashedPassword) return generatedString
                            cout << generatedString << endl;
                        }
}

string sixBytes(string password) {
    string saltPassSalt = salt + password + salt;
    return saltPassSalt;
}

string MD5Crypt() {
//    for (int i = 0; i < 1000; i++) {
//
//    }
    return "hi";
}