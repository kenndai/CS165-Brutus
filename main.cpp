#include <iostream>
#include <string>
#include "md5.h"
#include <chrono>

using namespace std;

string convert(unsigned long, const int &);
string triplets(unsigned char*);
string MD5_Crypt(const string &);
void crack();

const string salt = "hfT7jp2q";
const string magic = "$1$";
const string hashedPassword = "rhb3sPONC2VlUS2CG4JFe0";
const string crypt64 = "./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int main() {

//    auto start = chrono::steady_clock::now();
//    for (int i = 0; i < 10000; i++)
//        MD5_Crypt("rhb3sP");
//    auto end = chrono::steady_clock::now();
//    cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(end - start).count() << "sec";

    char cstring[] = "czormg";
    if (MD5_Crypt(cstring) == hashedPassword) cout << "congratulations" << endl;

    return 0;
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
    unsigned char* altSum = MD5(password + salt + password).digest;

    string sixBytes;
    for (int i = 0; i < 6; i++)
        sixBytes.push_back(altSum[i]);
    string concat = password + magic + salt + sixBytes + password[0] + '\0' + '\0';

    unsigned char* digest = MD5(concat).digest;

    string inter;
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
        digest = MD5(nextInter).digest;
        for (int j = 0; j < 16; j++) {
            inter.push_back(digest[j]);
        }
    }

    // shuffle around final hex values
    unsigned char replacement[] = {
            digest[11], digest[4], digest[10], digest[5], digest[3], digest[9], digest[15], digest[2],
            digest[8], digest[14], digest[1],digest[7], digest[13], digest[0], digest[6], digest[12]};

    return triplets(replacement);
}

void crack() {
    char generatedPassword[7] = {'\0'};
    for (char i = 97; i < 123; i++)
        for (char j = 97; j < 123; j++)
            for (char k = 97; k < 123; k++)
                for (char x = 97; x < 123; x++)
                    for (char y = 97; y < 123; y++)
                        for (char z = 97; z < 123; z++) {
                            generatedPassword[0] = i;
                            generatedPassword[1] = j;
                            generatedPassword[2] = k;
                            generatedPassword[3] = x;
                            generatedPassword[4] = y;
                            generatedPassword[5] = z;
                            cout << generatedPassword << endl;
                            if (MD5_Crypt(generatedPassword) == hashedPassword) {
                                cout << "congratulations!!!" << endl;
                                cout << generatedPassword << endl;
                            }
                        }
}

