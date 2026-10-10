#include "test2.h"

void download_from_file()
{
    cout << "Введите имя входного файла: ";
    string file_name;

    ifstream fin;
    fin.open(file_name);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!";
        return;
    }
    string line;
    do {
        getline(fin, line);
        string fields[4];
        int i =0;

        size_t start = 0;
        size_t end = line.find(',');
        while (end!=string::npos) {
            fields[i] = line.substr(start, end);
            start= end+1;
            end = line.find(',', start);
            i++;
        }
        create_airport(fields[0],fields[1],fields[2],fields[3]);

    }while (line != "EDGES\n");
    while (getline(fin, line)) {
        getline(fin, line);
        string fields[4];
        int i =0;

        size_t start = 0;
        size_t end = line.find(',');
        while (end!=string::npos) {
            fields[i] = line.substr(start, end);
            start= end+1;
            end = line.find(',', start);
            i++;
        }
        Airport* temp_dep;
        Airport* temp_arr;
        if (find_Airport(fields[0]) == nullptr) {
            create_airport(fields[0], "NULL", "NULL","NULL");
        }
        temp_dep = find_Airport(fields[0]);
        if (find_Airport(fields[1]) == nullptr) {
            create_airport(fields[1], "NULL", "NULL","NULL");
        }
        temp_arr = find_Airport(fields[1]);
        Route* temp_route = create_route(fields[0], fields[1], fields[2], fields[3], temp_dep, temp_arr );
    }
}

