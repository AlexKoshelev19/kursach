#include "test2.h"

int sum(int a, int b) {
    return a + b;
}

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


bool is_valid_code(string& code) {
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


bool is_valid_word(string& word)
{
    if (word == "exit") return true;

    // --- пробелы слева ---
    size_t start = 0;
    while (start < word.size() && word[start] == ' ')
        start++;

    // --- пробелы справа ---
    size_t end = word.size();
    while (end > start && word[end - 1] == ' ')
        end--;

    word = word.substr(start, end - start);

    if (word.empty()) {
        cout << "Ошибка! Строка должна содержать кириллические буквы (до 30 симв.)! Повторите попытку: ";
        return false;
    }

    // --- регистр: первая заглавная, остальные строчные ---
    wstring w = utf8_to_wstring(word);
    if (w.empty()) {
        cout << "Ошибка! Строка должна содержать кириллические буквы (до 30 симв.)! Повторите попытку: ";
        return false;
    }

    for (size_t i = 0; i < w.size(); i++) {
        if (i == 0)
            w[i] = (wchar_t)towupper(w[i]);
        else
            w[i] = (wchar_t)towlower(w[i]);
    }

    word = wstring_to_utf8(w);

    static const wregex name_regex(LR"(^[А-ЯЁа-яё\s-]{1,30}$)");
    if (regex_match(utf8_to_wstring(word), name_regex))
        return true;

    cout << "Ошибка! Строка должна содержать кириллические буквы (до 30 симв.)! Повторите попытку: ";
    return false;
}


bool is_valid_digit(string& digit) {
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



string good_scan(bool (*is_valid)(string&))
{
    string temp;
    if (cin.peek() == '\n')
        cin.ignore();
    do {
        getline(cin, temp);
        if (!temp.empty() && temp.back() == '\r')
            temp.pop_back();
        if (temp.empty())
            continue;
    } while (!is_valid(temp));

    return temp;
}
void create_airport(string name, string city, string country, string code, bool silent)
{
    for (Airport* t = main_ptr; t != nullptr; t = t->next_airport) {
        if (t->name == name || t->code == code) {
            if (!silent) {
                if (t->name == name)
                    cout << "\nОшибка: аэропорт \"" << name << "\" уже существует!\n";
                else
                    cout << "\nОшибка: код \"" << code << "\" уже занят!\n";
            }
            return; // дубликат — просто выходим
        }
    }

    Airport* node = new Airport;
    node->name = name;
    node->city = city;
    node->country = country;
    node->code = code;
    node->routes = nullptr;
    node->next_airport = nullptr;

    if (main_ptr == nullptr) {
        main_ptr = node;
    } else {
        Airport* t = main_ptr;
        while (t->next_airport != nullptr)
            t = t->next_airport;
        t->next_airport = node;
    }
}

Route* create_route(Airport* dep, Airport* arr, string distance, string flight_time, bool silent)
{
    
    if (dep == nullptr || arr == nullptr)
        return nullptr;

    for (Route* r = dep->routes; r != nullptr; r = r->next_route) {
        if (r->arr_airport_ptr == arr) {
           return nullptr; // дубликат — пропускаем
        }
    }

    Route* edge = new Route;
    edge->dep_airport_ptr = dep;
    edge->arr_airport_ptr = arr;
    edge->distance = distance;
    edge->flight_time = flight_time;
    edge->next_route = nullptr;

    if (dep->routes == nullptr)
        dep->routes = edge;
    else {
        Route* t = dep->routes;
        while (t->next_route != nullptr)
            t = t->next_route;
        t->next_route = edge;
    }
    return edge;
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
    if (departure == arrival) {
        cout << "Аэропорт назначения и аэропорт отправления совпадают.";

    }
    Route* temp_route = departure->routes;
    while(temp_route != nullptr)
    {
        if(temp_route->arr_airport_ptr == arrival)
        {
            cout << " " << temp_route->dep_airport_ptr->name << endl;
            cout << " " << temp_route->arr_airport_ptr->name << endl;
            cout << " " << temp_route->distance << endl;
            cout << " " << temp_route->flight_time << endl;
            return true;
        }
        temp_route = temp_route->next_route;
    }
    cout << "Прямой маршрут не найден, попробуйте найти маршрут с пересадками\n\n";
    cout << "нажмите любую клавишу для продолжения\n";
    getch();
    return false;
}

void print_Airport(Airport* current) {
    cout << "Название: " << current->name << endl;
    cout << "Код: " << current->code << endl;
    cout << "Город: " <<current->city << endl;
    cout << "Страна: " << current->country << endl;
    cout << endl;

    cout << "Аэропорты назначения: " << endl;

    Route* temp = current->routes;

    if(temp == nullptr)
        cout << "\tОтсутстуют" << endl;
    else {
        while(temp != nullptr)
        {
            cout << '\t' << temp->arr_airport_ptr->name << endl;
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
        getch();
        system("cls");
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
    system("cls");
}

void print_routes(Airport* dep_airport)
{
    if (dep_airport == nullptr) {
        cout << "Аэропорт не найден.\n";
        return;
    }
    cout << "Исходный аэропорт:\n";
    cout << dep_airport->name << endl;
    cout << dep_airport->code << endl;
    cout << dep_airport->city << endl;
    cout << dep_airport->country << endl;
    cout << endl;
    Route* temp = dep_airport->routes;

    if (temp == nullptr) {
        cout << "У аэропорта \"" << dep_airport->name << "\" нет маршрутов.\n";

        return;
    }
    cout << "Маршруты: \n";
    cout << "-------------------------------------------------------" << endl;
    while (temp != nullptr) {
        cout << "Отправление: " << temp->dep_airport_ptr->name << endl;
        cout << "Прибытие: " << temp->arr_airport_ptr->name << endl;
        cout << "Дальность: " << temp->distance << endl;
        cout << "Время полета: " << temp->flight_time << endl;
        cout << "-------------------------------------------------------" << endl;
        temp = temp->next_route;
    }
}



void print_one_route(Airport* dep_airport, Airport* arrival) {
    Route * temp = dep_airport->routes;
    while (temp != nullptr) {
        if ( temp->arr_airport_ptr == arrival || arrival== nullptr ) {
            cout << "Отправление: " << temp->dep_airport_ptr->name << endl;
            cout << "Прибытие: " << temp->arr_airport_ptr->name << endl;
            cout << "Дальность: " << temp->distance << endl;
            cout << "Время полета: " << temp->flight_time << endl;
            cout << "-------------------------------------------------------" << endl;
        }
        temp = temp->next_route;

    }
}


void print_all_routes(){
    Airport* temp = main_ptr;
    bool exist_route = false;
    cout << "-------------------------------------------------------" << endl;
    while(temp != nullptr){
        print_one_route(temp);
        exist_route = true;
        temp = temp->next_airport;
    }
    if (exist_route == false) {
        cout << "Маршрутов не найдено." << endl;
        cout << "-------------------------------------------------------" << endl;
    }
    getch();
    system("cls");
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


bool delete_route(Airport* dep_airport, Airport* arr_airport, bool silent)
{
    if (dep_airport == nullptr) return false;

    // Удаляем ВСЕ маршруты
    if (arr_airport == nullptr) {
        Route* temp = dep_airport->routes;
        while (temp != nullptr) {
            Route* deleted = temp;
            temp = temp->next_route;
            delete deleted;
        }
        dep_airport->routes = nullptr;
        return true;
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
            if (!silent){
                cout << "\nМаршрут: \n";
                cout << "\tОтправление: " << temp->dep_airport_ptr->name << endl;
                cout << "\tПрибытие: " << temp->arr_airport_ptr->name << endl;
                cout << "\tДальность: " << temp->distance << endl;
                cout << "\tВремя полета: " << temp->flight_time << endl;
                cout << "успешно удален!\n";

            }
            delete temp;
            return true;
        }
        prev = temp;
        temp = temp->next_route;
    }
    if (!silent)
    cout << "Маршрута " << dep_airport->name << " - " << arr_airport->name << " не найдено, нажмите любую клавишу для повторения(esc - выход):\n";
    return false;
}

void delete_airport(Airport* name_airport)
{
    if (name_airport == nullptr) return;

    Airport* current = main_ptr;
    while (current != nullptr) {
        if (current != name_airport) {
            bool flag = delete_route(current, name_airport,true);
            // удалить один конкретный маршрут
        }
        current = current->next_airport;
    }

    // Удаляем все исходящие маршруты
    bool flag = delete_route(name_airport,nullptr,true);   // arr_airport по умолчанию = nullptr

    // Удаляем аэропорт из списка
    if (main_ptr == name_airport) {
        main_ptr = name_airport->next_airport;
    }
    else {
        Airport* pred_ptr = main_ptr;
        while (pred_ptr != nullptr && pred_ptr->next_airport != name_airport) {
            pred_ptr = pred_ptr->next_airport;
        }
        if (pred_ptr != nullptr) {
            pred_ptr->next_airport = name_airport->next_airport;
        }
    }
    cout << "Аэропорт \n";
    print_Airport(name_airport);
    cout << " успешно удален!" << endl;
    cout << "для выхода нажмите любую клавишу";
    delete name_airport;
}



bool duplicate_route(Airport* dep_airport_ptr, Airport* arr_airport_ptr) {
    for (Route* r = dep_airport_ptr->routes; r != nullptr; r = r->next_route) {
        if (r->arr_airport_ptr == arr_airport_ptr) {
            cout << "Ошибка: маршрут "
                 << dep_airport_ptr->name << " - " << arr_airport_ptr->name
                 << " уже существует!\n\n";

            cout << "\tОтправление: " << r->dep_airport_ptr->name << endl;
            cout << "\tПрибытие: " << r->arr_airport_ptr->name << endl;
            cout << "\tДальность: " << r->distance << endl;
            cout << "\tВремя полета: " << r->flight_time << endl;

            return false;
        }
    }
    return true;
}

bool duplicate_airport(Airport* current) {
    Airport* temp = main_ptr;
    while (temp != nullptr) {
        if (temp->name == current->name) {

            return false;
        }
        if (temp->code == current->code) {

            return false;
        }
        temp = temp->next_airport;
    }
    return true;
}


bool edit_route(Airport* dep, Airport* arr)
{
    if (dep == nullptr || arr == nullptr)
        return false;

    // --- есть ли маршрут dep → arr? ---
    Route* temp_route = dep->routes;
    while (temp_route != nullptr) {
        if (temp_route->arr_airport_ptr == arr)
            break;
        temp_route = temp_route->next_route;
    }

    if (temp_route == nullptr) {
        cout << "Маршрут " << dep->name << " → " << arr->name
             << " не существует. Нажмите любую клавишу...\n";
        getch();
        return false;
    }

    // --- маршрут найден — можно вводить новые данные ---
    cout << "\nИсходный маршрут:\n";
    print_one_route(dep, arr);

    cout << "\nВведите дистанцию: ";
    string dist = good_scan(is_valid_digit);
    if (dist == "exit") return false;

    cout << "\nВведите время полета: ";
    string time_route = good_scan(is_valid_digit);
    if (time_route == "exit") return false;

    temp_route->distance = dist;
    temp_route->flight_time = time_route;

    cout << "\nМаршрут изменен:\n";
    cout << "-------------------------------------------------------\n";
    cout << "Отправление: " << temp_route->dep_airport_ptr->name << endl;
    cout << "Прибытие: " << temp_route->arr_airport_ptr->name << endl;
    cout << "Дальность: " << temp_route->distance << endl;
    cout << "Время полета: " << temp_route->flight_time << endl;
    cout << "-------------------------------------------------------\n";

    return true;
}
























































