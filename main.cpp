#include <iostream>
#include <chrono>

using namespace std;

const string alphabet[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
int numCombinations = 0;

void generateString(int);

int main() {
    auto start = chrono::steady_clock::now();
    generateString(26);
    auto end = chrono::steady_clock::now();
    cout << "Elapsed time in seconds: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " sec";
    return 0;
}


void generateString(int stringLength) {
    string generatedString;
    for (int i = 0; i < stringLength; i++)
        for (int j = 0; j < stringLength; j++)
            for (int k = 0; k < stringLength; k++)
                for (int x = 0; x < stringLength; x++)
                    for (int y = 0; y < stringLength; y++) {
                        generatedString = alphabet[i] + alphabet[j] + alphabet[k] + alphabet[x] + alphabet[y];
                        // if (hash(generatedString) == hashedPassword) return generatedString
                        cout << generatedString << endl;
                        numCombinations++;
                    }
    cout << "number of combinations: " << numCombinations << endl;
}
