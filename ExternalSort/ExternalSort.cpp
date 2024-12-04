#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>  // Для использования stringstream

using namespace std;

// Функция для сортировки данных в файле
void sort_and_write(const string& filename, int block_size) {
    ifstream infile(filename);  // Открытие файла в текстовом режиме
    vector<int> data(block_size);
    int block_index = 0;

    // Чтение данных блоками, сортировка и запись в отдельные файлы
    while (infile) {
        int i = 0;
        // Чтение блока данных
        while (i < block_size && infile >> data[i]) {
            i++;
        }

        // Сортировка блока
        sort(data.begin(), data.begin() + i);

        // Формирование имени для файла блока
        stringstream ss;
        ss << "block" << block_index++ << ".txt";
        string block_filename = ss.str();

        // Запись отсортированных данных в отдельный файл
        ofstream outfile(block_filename);  // Открытие для записи
        for (int j = 0; j < i; ++j) {
            outfile << data[j] << " ";  // Запись чисел с пробелами
        }
        outfile << endl;
    }
}

// Многофазная сортировка: Слияние блоков
void external_merge(int num_blocks, const string& output_file) {
    ofstream outfile(output_file);  // Открытие выходного файла

    // Используем кучу (priority_queue) для слияния
    priority_queue<int, vector<int>, greater<int>> min_heap;
    vector<ifstream> input_files(num_blocks);

    // Открытие всех файлов блоков и добавление первого элемента в очередь
    for (int i = 0; i < num_blocks; ++i) {
        stringstream ss;
        ss << "block" << i << ".txt";  // Формирование имени файла блока
        input_files[i].open(ss.str());

        int value;
        if (input_files[i] >> value) {
            min_heap.push(value);  // Добавление в очередь с приоритетом
        }
    }

    // Слияние данных из кучи в итоговый файл
    while (!min_heap.empty()) {
        int min_val = min_heap.top();
        min_heap.pop();
        outfile << min_val << " ";  // Запись в файл

        // Чтение следующего элемента из того же блока, если он есть
        for (int i = 0; i < num_blocks; ++i) {
            int value;
            if (input_files[i] >> value) {
                min_heap.push(value);
                break;  // Прерываем, чтобы не читать все блоки сразу
            }
        }
    }
}

// Основная функция
int main() {
    string input_file = "input.txt";  // Входной файл (с данными)
    string output_file = "output.txt";  // Выходной файл для результата
    int block_size = 1024;  // Размер блока для сортировки

    // Сначала сортируем и записываем блоки
    sort_and_write(input_file, block_size);

    // Затем сливаем отсортированные блоки в итоговый файл
    external_merge(10, output_file);  // Здесь указываем количество блоков

    return 0;
}