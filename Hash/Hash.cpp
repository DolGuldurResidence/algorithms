#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using namespace std;

vector<string> read_file(const string& filename) 
{
    ifstream file(filename);
    if (!file.is_open()) 
    {
        throw runtime_error("Не удалось открыть файл для чтения");
    }

    vector<string> words;
    string word;
    while (file >> word)
    {
        words.push_back(word);
    }
    return words;
}

int hash_function(const string& word, int table_size) 
{
    return word.length() % table_size;
}

vector<string> hash_table_with_collision(const vector<string>& words, int table_size) 
{
    vector<string> table(table_size, "");

    for (const auto& word : words) 
    {
        int index = hash_function(word, table_size);
        int original_index = index;

        while (table[index] != "") 
        {
            index = (index + 1) % table_size; 
            if (index == original_index) 
            { 
                throw overflow_error("Таблица переполнена");
            }
        }
        table[index] = word;
    }

    return table;
}

vector<vector<string>> hash_table_with_lists(const vector<string>& words, int table_size)
{
    vector<vector<string>> table(table_size);

    for (const auto& word : words)
    {
        int index = hash_function(word, table_size);
        table[index].push_back(word);
    }

    return table;
}

void write_to_file(const string& filename, const vector<string>& table, const string& method_name) 
{
    ofstream file(filename, ios::app);
    if (!file.is_open()) 
    {
        throw runtime_error("Не удалось открыть файл для записи");
    }

    file << method_name << ":\n";
    for (size_t i = 0; i < table.size(); ++i)
    {
        file << i << ": " << table[i] << "\n";
    }
    file << "\n";
}


void write_to_file(const string& filename, const vector<vector<string>>& table, const string& method_name) 
{
    ofstream file(filename, ios::app);
    if (!file.is_open()) 
    {
        throw runtime_error("Не удалось открыть файл для записи");
    }

    file << method_name << ":\n";
    for (size_t i = 0; i < table.size(); ++i)
    {
        file << i << ": ";
        for (const auto& word : table[i]) 
        {
            file << word << " ";
        }
        file << "\n";
    }
    file << "\n";
}

int main() {
    
    setlocale(LC_ALL, "Russian");

    string input_file = "input.txt";  
    string output_file = "output.txt";

    ifstream file(input_file);
    if (!file.is_open()) 
    {
        cout << "Создайте файл '" << input_file << "' и добавьте туда текст." << endl;
        return 1;
    }

    vector<string> words = read_file(input_file);  
    int table_size = 10;  
    
    vector<string> collision_table = hash_table_with_collision(words, table_size);
    vector<vector<string>> list_table = hash_table_with_lists(words, table_size);

    ofstream out_file(output_file, ios::trunc);
    if (!out_file.is_open()) 
    {
        cerr << "Не удалось открыть файл для записи." << endl;
        return 1;
    }

    write_to_file(output_file, collision_table, "Метод с линейным пробированием");
    write_to_file(output_file, list_table, "Метод со списками");

    return 0;
}
