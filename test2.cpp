#include "test2.h"

int sum(int a, int b) {
    return a + b;
}

struct Airport{
    string name;
    string city;
    string country;
    string code;

    Route* routes;

    Airport* next_airport;
};

struct Route{
    string departure;
    string arrival;
    string distance;
    string flight_time;

    Airport* dep_airport_ptr;
    Airport* arr_airport_ptr;

    Route* next_route;
};

Airport* main_ptr;

wstring utf8_to_wstring(const string& str) {
    if (str.empty()) return L"";
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), nullptr, 0);
    wstring result(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), (int)str.size(), &result[0], size);
    return result;
}

string wstring_to_utf8(const wstring& wstr) {
    if (wstr.empty()) return "";
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), nullptr, 0, nullptr, nullptr);
    string result(size, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.size(), &result[0], size, nullptr, nullptr);
    return result;
}


bool is_valid_code(const string& code) {
    if (code == "exit") return true;
    wstring w_code = utf8_to_wstring(code);
    static const wregex name_regex(LR"(^[A-Z]{3}$)");
    if (regex_match(w_code, name_regex)) {
        return true;
    }
    else {
        cout << "Ошибка! Строка должна содержать три заглавных латинских буквы! Повторите попытку: ";
        return false;
    }
}


bool is_valid_word(const string& word) {
    if (word == "exit") return true;
    wstring w_word = utf8_to_wstring(word);
    static const wregex name_regex(LR"(^[А-ЯЁа-яё\s-]{1,30}$)");
    if (regex_match(w_word, name_regex)) {
        return true;
    }
    else {
        cout << "Ошибка! Строка должна содержать кириллические буквы (до 30 симв.)! Повторите попытку: ";
        return false;
    }
}

bool is_valid_digit(const string& digit) {
    if(digit == "exit") return true;
    wstring w_digit = utf8_to_wstring(digit);
    static const wregex name_regex(LR"(^[0-9]{1,30}$)");
    if (regex_match(w_digit, name_regex)) {
        return true;
    }
    else {
        cout << "Ошибка! Строка должна содержать цифры (до 30 симв.)! Повторите попытку: ";
        return false;
    }
}



string good_scan(bool (*is_valid)(const string&)) {
    string temp;
    do {
        getline(cin, temp);
    } while (!is_valid(temp)); // Передаем строку в функцию проверки
    return temp;
}

void create_airport(string name, string city, string country, string code)
{
    Airport* temp = main_ptr;
    while (temp != nullptr) {
        if (temp->name == name) {
            cout << "Ошибка: аэропорт с названием \"" << name << "\" уже существует!\n";
            return;
        }
        if (temp->code == code) {
            cout << "Ошибка: аэропорт с кодом \"" << code << "\" уже существует!\n";
            return;
        }
        temp = temp->next_airport;
    }

    Airport* new_node = new Airport;
    new_node->name = name;
    new_node->city = city;
    new_node->country = country;
    new_node->code = code;
    new_node->routes = nullptr;
    new_node->next_airport = nullptr;
    if(main_ptr == nullptr)
    {
        main_ptr = new_node;
    }
    else 
    {
        Airport* temp = main_ptr;
        while (temp->next_airport != nullptr)
        {
            temp = temp->next_airport;
        }
        temp->next_airport = new_node;
    }
    return ;
}

Route* create_route(Airport* dep_airport_ptr, Airport* arr_airport_ptr, string distance, string flight_time)
{
    Route* new_edge = new Route;
    new_edge->dep_airport_ptr = dep_airport_ptr;
    new_edge->arr_airport_ptr = arr_airport_ptr;
    new_edge->departure = dep_airport_ptr->name;
    new_edge->arrival = arr_airport_ptr->name;
    new_edge->distance = distance;
    new_edge->flight_time = flight_time;
    
    new_edge->next_route= nullptr;
    // добавить проверку на наличие маршрута, если уже создан, просто вывести информацию о маршруте
    if(dep_airport_ptr != nullptr && arr_airport_ptr != nullptr)
    {
        if(dep_airport_ptr->routes == nullptr)
            dep_airport_ptr->routes = new_edge;
        else 
        {
            Route* temp = dep_airport_ptr->routes;
            while(temp->next_route != nullptr)
                temp = temp->next_route;
            temp->next_route = new_edge;
        }
    }
    return new_edge;
}

Airport* find_Airport(string name)
{
    Airport* temp = main_ptr;
    while(temp != nullptr)
    {
        if(temp->name == name)
            break;
        temp = temp->next_airport;
    }
    return temp;
}

bool is_direct_route(Airport* departure, Airport* arrival) //true - yes
{
    Route* temp_route = departure->routes;
    while(temp_route != nullptr)
    {
        if(temp_route->arrival == arrival->name)
        {
            cout << " " << temp_route->departure << endl;
            cout << " " << temp_route->arrival << endl;
            cout << " " << temp_route->distance << endl;
            cout << " " << temp_route->flight_time << endl;
            return true;
        }
        temp_route = temp_route->next_route;
    }
    cout << "Прямой маршрут не найден, попробуйте найти маршрут с пересадками";
    return false;
}

void print_Airport(Airport* current) {
    cout << current->name << endl;
    cout << current->code << endl;
    cout << current->city << endl;
    cout << current->country << endl;
    cout << endl;

    cout << "Аэропорты назначения: " << endl;

    Route* temp = current->routes;

    if(temp == nullptr)
        cout << "\tОтсутстуют" << endl;
    else {
        while(temp != nullptr)
        {
            cout << '\t' << temp->arrival << endl;
            temp = temp->next_route;
        }
    }
    cout << endl;
}

void print_all_airports()
{
    Airport* temp = main_ptr;
    if (temp == nullptr) {
        cout << "Список аэропортов пуст.\n";
        return;
    }
    cout << "-------------------------------------------------------" << endl;
    while(temp != nullptr)
    {
        print_Airport(temp);
        cout << "-------------------------------------------------------" << endl;
        temp = temp->next_airport;
    }
    getch();
}

void print_routes(Airport* dep_airport) {
    //считаем что указатели прошли проверки(такие аэропорты существуют
    Route * temp = dep_airport->routes;
    while (temp != nullptr) {
        cout << " " << temp->departure << endl;
        cout << " " << temp->arrival << endl;
        cout << " " << temp->distance << endl;
        cout << " " << temp->flight_time << endl;
        temp = temp->next_route;
    }
}

int count_of_Airport()
{
    Airport* temp= main_ptr;
    if(temp == nullptr)
        return 0;
    int n=0;
    while(temp != nullptr)
    {   
        n++;
        temp = temp->next_airport;
    }

    return n;
}

void search_route(Airport* departure, Airport* arrival)
{
    if (departure == nullptr || arrival == nullptr) {
        cout << "Аэропорт не найден!\n";
        return;
    }

    int n = count_of_Airport();
    if (n == 0) return;

    Airport** vertices = new Airport*[n];
    bool* visited = new bool[n];
    int* dist = new int[n];
    int* parent = new int[n];          // для восстановления пути (опционально)

    const int INF = 1000000000;

    // ---------- Инициализация ----------
    Airport* temp = main_ptr;
    int start_index = -1;
    int end_index = -1;

    for (int i = 0; i < n; i++) {
        vertices[i] = temp;
        dist[i] = INF;
        visited[i] = false;
        parent[i] = -1;

        if (temp == departure) start_index = i;
        if (temp == arrival)   end_index = i;

        temp = temp->next_airport;     
    }

    if (start_index == -1 || end_index == -1) {
        cout << "Один из аэропортов не найден в списке!\n";
        delete[] vertices;
        delete[] visited;
        delete[] dist;
        delete[] parent;
        return;
    }

    dist[start_index] = 0;

    // ---------- Основной цикл Дейкстры ----------
    for (int iter = 0; iter < n; iter++) {
        // 1. Находим непосещённую вершину с минимальным dist
        int v = -1;
        int min_dist = INF;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                min_dist = dist[i];
                v = i;
            }
        }

        if (v == -1) break;            // больше нет достижимых вершин
        if (v == end_index) break;     // уже нашли путь до цели

        visited[v] = true;             

        // 2. Релаксация рёбер
        Route* route = vertices[v]->routes;
        while (route != nullptr) {
            // ищем индекс соседа
            int u = -1;
            for (int i = 0; i < n; i++) {
                if (vertices[i] == route->arr_airport_ptr) {
                    u = i;
                    break;
                }
            }

            if (u != -1 && !visited[u]) {
                int weight = stoi(route->distance);
                if (dist[v] + weight < dist[u]) {
                    dist[u] = dist[v] + weight;
                    parent[u] = v;     // запоминаем, откуда пришли
                }
            }
            route = route->next_route;
        }
    }

    // ---------- Вывод результата ----------
    if (dist[end_index] == INF) {
        cout << "Путь не найден.\n";
    } else {
        cout << "Кратчайшее расстояние: " << dist[end_index] << endl;

        // Восстановление пути (по желанию)
        cout << "Путь: ";
        vector<string> path;
        for (int cur = end_index; cur != -1; cur = parent[cur]) {
            path.push_back(vertices[cur]->name);
        }
        reverse(path.begin(), path.end());

        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << endl;
    }

    // ---------- Освобождение памяти ----------
    delete[] vertices;
    delete[] visited;
    delete[] dist;
    delete[] parent;
}


void delete_route(Airport* dep_airport, Airport* arr_airport = nullptr)
{
    if (dep_airport == nullptr) return;

    // Удаляем ВСЕ маршруты
    if (arr_airport == nullptr) {
        Route* temp = dep_airport->routes;
        while (temp != nullptr) {
            Route* deleted = temp;
            temp = temp->next_route;
            delete deleted;
        }
        dep_airport->routes = nullptr;
        return;
    }

    // Удаляем ОДИН конкретный маршрут
    Route* temp = dep_airport->routes;
    Route* prev = nullptr;

    while (temp != nullptr) {
        if (temp->arr_airport_ptr == arr_airport) {
            if (prev == nullptr) {
                dep_airport->routes = temp->next_route;   // удаляем первый
            } else {
                prev->next_route = temp->next_route;     // удаляем из середины/конца
            }
            delete temp;
            return;
        }
        prev = temp;
        temp = temp->next_route;
    }


    cout << "Маршрута не существует." << endl;
    
}


void delete_airport(Airport* name_airport)
{
    if (name_airport == nullptr) return;

    // Удаляем все исходящие маршруты
    delete_route(name_airport);   // arr_airport по умолчанию = nullptr

    // Удаляем аэропорт из списка
    if (main_ptr == name_airport) {
        main_ptr = name_airport->next_airport;
    } else {
        Airport* pred_ptr = main_ptr;
        while (pred_ptr != nullptr && pred_ptr->next_airport != name_airport) {
            pred_ptr = pred_ptr->next_airport;
        }
        if (pred_ptr != nullptr) {
            pred_ptr->next_airport = name_airport->next_airport;
        }
    }
    cout << "Аэропорт " << name_airport->name << " успешно удален!" << endl;
    cout << "для выхода нажмите любую клавишу";
    delete name_airport;
    getch(); 
    system("cls");
}