#include "test2.h"

void download_from_file()
{
    cout << "Введите имя входного файла: ";
    string file_name;
    getline(cin, file_name);

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
            create_airport(fields[0], fields[1], fields[2], fields[3], true);
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
            create_airport(fields[0], "NULL", "NULL", "NULL", true);
            temp_dep = find_Airport(fields[0]);
        }

        Airport* temp_arr = find_Airport(fields[1]);
        if (temp_arr == nullptr) {
            create_airport(fields[1], "NULL", "NULL", "NULL", true);
            temp_arr = find_Airport(fields[1]);
        }
        create_route(temp_dep, temp_arr, fields[2], fields[3], true);
    }
    fin.close();
    cout << "Данные успешно загружены.\n нажмите любую кнопку";
    getch();
    system("cls"); return;
}


void upload_to_file()
{
    cout << "Введите имя выходного файла: ";
    string file_name;
    getline(cin, file_name);

    ofstream fout(file_name);
    if (!fout.is_open()) {
        cout << "Ошибка открытия файла для записи!\n";
        return;
    }


    fout << "NODES\n";

    Airport* temp = main_ptr;
    if (temp == nullptr) {
        cout << "Список аэропортов пуст!\n";
    }

    while (temp != nullptr) {
        fout << temp->name << ","
             << temp->city << ","
             << temp->country << ","
             << temp->code << "\n";
        temp = temp->next_airport;   // ← обязательно!
    }

    fout << "EDGES\n";
    temp = main_ptr;
    while (temp != nullptr) {
        Route* r = temp->routes;
        while (r != nullptr) {
            fout << r->dep_airport_ptr->name << ","
                 << r->arr_airport_ptr->name << ","
                 << r->distance << ","
                 << r->flight_time << "\n";
            r = r->next_route;
        }
        temp = temp->next_airport;
    }

    fout.close();
    cout << "Данные успешно сохранены в \"" << file_name << "\".\n";
}

























