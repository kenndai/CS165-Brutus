#include <iostream>
#include <sstream>
#include <string>
#include "md5.h"
#include <chrono>

using namespace std;

unsigned char* getDigest(const string &); //takes in string from hexdigest and produces digest
string altSixBytes(string);
string MD5_Crypt(string);
string crack();

const string salt = "4fTgjp6q";
const string magic = "$1$";
const string hashedPassword = "CxWQeLPwIdqToYNk5yDoS.";
const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

int main() {
    unsigned char* digest;

    MD5 grapes = MD5("grapes");
    cout << "digest from class: " << grapes.digest << endl;
    digest = getDigest(grapes.hexdigest());
    cout << "digest from function: " << digest << endl;

    MD5 oranges = MD5("oranges");
    cout << "digest from class: " << oranges.digest << endl;
    digest = getDigest(oranges.hexdigest());
    cout << "digest from function: " << digest << endl;

    return 0;
}

unsigned char* getDigest(const string &hexdigest) {
    string buffer, hef1, hef2;

    for (int i = 0; i < 32; i += 2) {
        hef1 = hexdigest[i];
        hef2 = hexdigest[i + 1];
        buffer += hef1.append(hef2).append(" ");
    }

    static unsigned char hexes[16];

    istringstream hex_chars_stream(buffer);
    unsigned int temp;
    for (int j = 0; j < 16; j++) {
        hex_chars_stream >> hex >> temp;
        hexes[j] = temp;
    }
    return hexes;
}


string altSixBytes(string password) {
    string passSaltPass = password + salt + password;

    //digest is the hash represented with 16 hex values, each one byte
    string sixBytes;
    for (int i = 0; i < 6; i++)
        sixBytes.push_back(MD5(passSaltPass).digest[i]); //possibly losing data through implicit conversion to char
    return sixBytes;
}

string MD5_Crypt(string password) {
    string concat = password + magic + salt + altSixBytes(password) + password[0] + "\0" + "\0";

    string zeroSum;
    for (unsigned char i : MD5(concat).digest) {
        zeroSum.push_back(i);
    }
    for (int i = 0; i < 1000; i++) {
        string nextSum;
        if (i % 2 == 0) nextSum += zeroSum;
        if (i % 2 != 0) nextSum += password;
        if (i % 3 != 0) nextSum += salt;
        if (i % 7 != 0) nextSum += password;
        if (i % 2 == 0) nextSum += password;
        if (i % 2 != 0) nextSum += zeroSum;

        for (unsigned char j : MD5(nextSum).digest) {
            zeroSum.push_back(j);
        }
    }

    char replacement[] = {
            zeroSum[11], zeroSum[4], zeroSum[10], zeroSum[5],
            zeroSum[3], zeroSum[9], zeroSum[15], zeroSum[2],
            zeroSum[8], zeroSum[14], zeroSum[1],zeroSum[7],
            zeroSum[13], zeroSum[0], zeroSum[6], zeroSum[12], '\0'
    };

    // TODO Final/Bit Manip
    const string crypt64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    string final;
    // md5() gives output in hex

//    for (int j = 31; j >= 0; j++) {
//
//    }

    // 1. Grab each 6 bit group starting from the LSB
    // 2. Convert binary into a decimal number and covert to corresponding crypt64 character

    return final;
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
    return "hi";
}
