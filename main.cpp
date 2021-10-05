#include <iostream>
#include <sstream>
#include <string>
#include "md5.h"
#include <chrono>

using namespace std;

unsigned char* getDigest(const string &); //takes in string from hexdigest and produces digest, 16 hex values
string sixBytes(const string &);
string convert(unsigned long, const int &);
string triplets(unsigned char*);
string MD5_Crypt(const string &);
string crack();

const string salt = "hfT7jp2q";
const string magic = "$1$";
const string hashedPassword = "rhb3sPONC2VlUS2CG4JFe0";
const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
const string crypt64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main() {
//    string password = "czormg";
//    string resultHash = MD5_Crypt(password);
//
//    if (resultHash == hashedPassword)
//        cout << "CONGRATULATIONS!!!" << endl;

    crack()

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
    MD5 md5psp = MD5(passSaltPass);
    unsigned char* altSum = getDigest(md5(passSaltPass));

    string sixBytes;
    // push back 6 hex values
    // possibly losing data through implicit conversion to chars
    for (int i = 0; i < 6; i++)
        sixBytes.push_back(altSum[i]);

    return sixBytes;
}

string convert(unsigned long triplet, const int &iterations) {
    string partial;
    for (int i = 0; i < iterations; i++) {
        partial += crypt64[triplet & 0x3F];
        triplet >>= 6;
    }
    return partial;
}

string triplets(unsigned char* hexValues) {
    // triplet can hold 3 8-bit strings, total 24 bits, divisible by 6 bits
    // bit shift hex values into triplet, fitting 3 hex values into triplet
    // a full triplet produces 4 converted values
    // in total, 22 converted values
    unsigned long triplet;
    string converted;

    triplet = (hexValues[13] << 16) | (hexValues[14] << 8) | hexValues[15]; // LSB
    converted += convert(triplet, 4);

    triplet = (hexValues[10] << 16) | (hexValues[11] << 8) | hexValues[12];
    converted += convert(triplet, 4);

    triplet = (hexValues[7] << 16) | (hexValues[8] << 8) | hexValues[9];
    converted += convert(triplet, 4);

    triplet = (hexValues[4] << 16) | (hexValues[5] << 8) | hexValues[6];
    converted += convert(triplet, 4);

    triplet = (hexValues[1] << 16) | (hexValues[2] << 8) | hexValues[3];
    converted += convert(triplet, 4);

    triplet = hexValues[0]; // MSB
    converted += convert(triplet, 2);

    return converted;
}

string MD5_Crypt(const string &password) {
    string concat = password + magic + salt + sixBytes(password) + password[0] + '\0' + '\0';
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
        inter = "";
        digest = getDigest(md5(nextInter));
        for (int j = 0; j < 16; j++) {
            inter.push_back(digest[j]);
        }
    }

    // shuffle around final hex values
    unsigned char replacement[] = {
            digest[11], digest[4], digest[10], digest[5], digest[3], digest[9], digest[15], digest[2],
            digest[8], digest[14], digest[1],digest[7], digest[13], digest[0], digest[6], digest[12]};

    // TODO Final/Bit Manip
    string final = triplets(replacement);

    return final;
}

string crack() {
    string generatedPassword;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 26; k++)
                for (int x = 0; x < 26; x++)
                    for (int y = 0; y < 26; y++)
                        for (int z = 0; z < 26; z++) {
                            generatedPassword = alphabet[i] + alphabet[j] + alphabet[k] + alphabet[x] + alphabet[y] + alphabet[z];
                            if (MD5_Crypt(generatedPassword) == hashedPassword) {
                                cout << "congratulations!!!" << endl;
                                cout << generatedPassword << endl;
                                return generatedPassword;
                            }
                        }
}