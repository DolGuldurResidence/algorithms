#include <string>
#include <iostream>
using namespace std;

const long long q = 2147483647; //число мерсена 2^32 - 1;
const int base = 31;

long long gornerSheme(long long base, int exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) 
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return result;
}

long long calculateHash(const string& text, long long mod) {
    long long hash = 0;
    for (char c : text) {
        hash = (hash * base + static_cast<unsigned char>(c)) % mod;
    }
    return hash;
}

int searchText(const string& text, const string& sub_text) {
    int m = sub_text.length();
    int n = text.length();
    if (m == 0) return 0;
    if (n < m) return -1;

    long long subHash = calculateHash(sub_text, q);
    long long currentHash = calculateHash(text.substr(0, m), q);
    long long powBase = gornerSheme(base, m - 1, q);

    for (int i = 0; i <= n - m; ++i) {
        if (subHash == currentHash && text.substr(i, m) == sub_text) {
            return i;
        }
        if (i < n - m) {
            // Вычисляем компонент для удаляемого символа
            long long remove = (static_cast<unsigned char>(text[i]) * powBase) % q;
            // Вычитаем и корректируем отрицательные значения
            currentHash = (currentHash - remove) % q;
            if (currentHash < 0) currentHash += q;
            // Умножаем на базу и добавляем новый символ
            currentHash = (currentHash * base + static_cast<unsigned char>(text[i + m])) % q;
        }
    }
    return -1;
}

int main() {
    string text = "print something";
    string sub_text = "some";
    int index = searchText(text, sub_text);
    cout << index << endl;

    return 0;
} 