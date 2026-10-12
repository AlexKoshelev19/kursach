#include "test2.h"

void download_from_file()
{
    cout << "Введите имя входного файла: ";
    string file_name = good_scan(is_valid_word);

    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }

    string line;

    while (getline(fin, line)) {
        if (line == "NODES") continue;
        if (line == "EDGES") break;          // разделитель разделов
        if (line.empty()) continue;

        string fields[4];
        size_t start = 0;
        int i = 0;

        // парсим первые 3 поля
        for (; i < 3; ++i) {
            size_t end = line.find(',', start);
            if (end == string::npos) break;
            fields[i] = line.substr(start, end - start);
            start = end + 1;
        }
        fields[i] = line.substr(start);      // последнее поле

        if (i == 3) {
            create_airport(fields[0], fields[1], fields[2], fields[3]);
        }
    }

    while (getline(fin, line)) {
        if (line.empty()) continue;

        string fields[4];
        size_t start = 0;
        int i = 0;

        for (; i < 3; ++i) {
            size_t end = line.find(',', start);
            if (end == string::npos) break;
            fields[i] = line.substr(start, end - start);
            start = end + 1;
        }
        fields[i] = line.substr(start);

        if (i != 3) continue;                // строка повреждена
        Airport* temp_dep = find_Airport(fields[0]);
        if (temp_dep == nullptr) {
            create_airport(fields[0], "NULL", "NULL", "NULL");
            temp_dep = find_Airport(fields[0]);
        }

        Airport* temp_arr = find_Airport(fields[1]);
        if (temp_arr == nullptr) {
            create_airport(fields[1], "NULL", "NULL", "NULL");
            temp_arr = find_Airport(fields[1]);
        }
        create_route(temp_dep, temp_arr, fields[2], fields[3]);
    }
    fin.close();
    cout << "Данные успешно загружены.\n";
}


void unloading_to_file(){
    cout << "Введите имя входного файла: ";
    string file_name = good_scan(is_valid_word);

    ifstream fin(file_name);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!\n";
        return;
    }



    ofstream fout;
    fout.open(file_name);
    Airport* temp_airport = main_ptr;
    while(temp_airport != nullptr)
    {

    }
    
}
