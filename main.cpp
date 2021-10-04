#include <iostream>
#include <sstream>
#include <string>
#include "md5.h"
#include <chrono>

using namespace std;

unsigned char* getDigest(const string &); //takes in string from hexdigest and produces digest, 16 hex values
string sixBytes(const string &);
string MD5_Crypt(string);
string crack();

const string salt = "4fTgjp6q";
const string magic = "$1$";
const string hashedPassword = "CxWQeLPwIdqToYNk5yDoS.";
const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

int main() {
    unsigned char* digest;
    MD5 grapes = MD5("0000");

    cout << "digest from class: " << grapes.digest << endl;
    digest = getDigest(md5("0000"));
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

string sixBytes(const string &password) {
    string passSaltPass = password + salt + password;

    unsigned char* digest = getDigest(md5(passSaltPass));

    string sixBytes;
    // push back 6 hex values
    // possibly losing data through implicit conversion to chars
    for (int i = 0; i < 6; i++)
        sixBytes.push_back(digest[i]);

    return sixBytes;
}

string MD5_Crypt(string password) {
    string concat = password + magic + salt + sixBytes(password) + password[0] + "\0" + "\0";

    string inter;
    unsigned char* digest = getDigest(md5(concat));
    // move the  16 hex values into inter
    for (int i = 0; i < 16; i++)
        inter.push_back(digest[i]);

    for (int i = 0; i < 1000; i++) {
        string nextInter;
        if (i % 2 == 0) nextInter += inter; // if even
        if (i % 2 != 0) nextInter += password; // if odd
        if (i % 3 != 0) nextInter += salt; // if indivisible by 3
        if (i % 7 != 0) nextInter += password; // if indivisible by 7
        if (i % 2 == 0) nextInter += password; // if even
        if (i % 2 != 0) nextInter += inter; // if odd

        // rehash and push new values into inter
        digest = getDigest(md5(nextInter));
        for (int j = 0; j < 16; j++) {
            inter.push_back(digest[j]);
        }
    }

    char replacement[] = {
            inter[11], inter[4], inter[10], inter[5],
            inter[3], inter[9], inter[15], inter[2],
            inter[8], inter[14], inter[1],inter[7],
            inter[13], inter[0], inter[6], inter[12], '\0'
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
