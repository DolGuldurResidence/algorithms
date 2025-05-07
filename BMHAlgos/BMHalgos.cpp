#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

int boyerMooreSearch(const string& sentence, const string& word) {
    unordered_set<char> uniqeSymbols;
    int lenWord = word.size();
    unordered_map<char, int> shiftTable;

    for (int i = lenWord - 2; i >= 0; --i) {
        if (uniqeSymbols.find(word[i]) == uniqeSymbols.end()) {
            shiftTable[word[i]] = lenWord - i - 1;
            uniqeSymbols.insert(word[i]);
        }
    }

    if (uniqeSymbols.find(word.back()) == uniqeSymbols.end()) {
        shiftTable[word.back()] = lenWord;
    }
    shiftTable['*'] = lenWord;

    int lenSentence = sentence.size();
    if (lenSentence >= lenWord) {
        int i = lenWord - 1;

        while (i < lenSentence) {
            int index = 0;
            bool mismatch = false;

            for (int j = lenWord - 1; j >= 0; --j) {
                if (sentence[i - index] != word[j]) {
                    int offset = (j == lenWord - 1)
                        ? (shiftTable.count(sentence[i]) ? shiftTable[sentence[i]] : shiftTable['*'])
                        : shiftTable[word[j]];

                    i += offset;
                    mismatch = true;
                    break;
                }
                index++;
            }

            if (!mismatch) {
                return i - index + 1; 
            }
        }
    }

    return -1; 
}

int main() {

    setlocale(LC_ALL, "Russian");

    // Тест 1
    string text1 = "метеоданные";
    string pattern1 = "данные";
    int result1 = boyerMooreSearch(text1, pattern1);
    cout << "Тест 1: "
        << (result1 != -1 ? to_string(result1) : "не найден")
        << endl;

    // Тест 2
    string text2 = "большие метеоданные";
    string pattern2 = "данные";
    int result2 = boyerMooreSearch(text2, pattern2);
    cout << "Тест 2: "
        << (result2 != -1 ? to_string(result2) : "не найден")
        << endl;

    // Тест 3 (отрицательный)
    string text3 = "программирование";
    string pattern3 = "данные";
    int result3 = boyerMooreSearch(text3, pattern3);
    cout << "Тест 3: "
        << (result3 != -1 ? to_string(result3) : "не найден")
        << endl;

    return 0;
}