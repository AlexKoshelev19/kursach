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
    int distance;
    int flight_time;

    Airport* dep_airport_ptr;
    Airport* arr_airport_ptr;

    Route* next_route;
};

Airport* main_ptr;

void create_airport(string name, string city, string country, string code)
{
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

Route* create_route(string departure, string arrival, int distance, int flight_time, Airport* dep_airport_ptr, Airport* arr_airport_ptr)
{
    Route* new_edge = new Route;
    new_edge->departure = departure;
    new_edge->arrival = arrival;
    new_edge->distance = distance;
    new_edge->flight_time = flight_time;
    new_edge->dep_airport_ptr = dep_airport_ptr;
    new_edge->arr_airport_ptr = arr_airport_ptr;
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

Airport* find_Airport(string code)
{
    Airport* temp = main_ptr;
    while(temp != nullptr)
    {
        if(temp->code == code)
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
            return true;
        }
        temp_route = temp_route->next_route;
    }
    return false;
}

void print_Airport(Airport* current)
{
    cout << current->name << endl;
    cout << current->code << endl;
    cout << current->city << endl;
    cout << current->country << endl;
    cout << endl;

    cout << "Аэропорты назначения: " << endl;

    Route* temp = current->routes;
    if(temp == nullptr) cout << "\tОтсутстуют" << endl;
    while(temp->next_route != nullptr)
    {
        cout << '\t' << temp->departure << endl;
    }

    cout << endl;
}

void print_route(Airport* dep_airport) {
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
    int n = count_of_Airport();
    Airport** vercities   = new Airport*[n];
    bool* visited = new bool[n];
    int* dist = new int[n];

    Airport* temp = main_ptr;
    int start_index = -1;
    int end_index = -1;
    int inf = 100000000;

    for(int i = 0; i < n; i ++){ //инициализация вспомогательных массивов
        vercities[i] = temp;
        dist[i] = inf;
        visited[i] = false;
  
        if(temp == departure) 
        {
            start_index = i;
        }
        if(temp == arrival)
        {
            end_index = i;
        }
    }

    dist[start_index] = 0;
    int u = - 1;
    while (true) {
        int v = -1;
        int min_dist = inf;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && dist[i] < min_dist) {
                v = i;
                visited[i] = true;
                min_dist = dist[i];
            }
        }
        if (vercities[v] == arrival) break;

        if (v == -1 || dist[v] == inf) break;

        Route* temp_route = vercities[v]->routes;
        
        if (temp_route == nullptr) return;
        
        while (temp_route != nullptr)
        {
            Airport* neibour = temp_route->arr_airport_ptr;
            
            for (int i = 0; i < n; i++ ) {
                if (neibour->name == vercities[i]->name) {
                    u = i;
                    break;
                }
            }
            if (u!=-1 && visited[u] == false) {
                if (dist[v] + temp_route->distance < dist[u]) {
                    dist[u] = dist[v]+temp_route->distance;
                }
            }
            visited[u] = true;//
            temp_route = temp_route->next_route;
        }
    }

   

    Route* current_route = vercities[u]->routes;
    while(current_route != nullptr){
        Airport* neighbour = current_route->arr_airport_ptr;
        int v = -1;
        for(int i = 0; i<n; i++)
        {
            if(vercities[i] == neighbour)
            {
                v = i;
                break;
            }
        }
        if (v != -1 && !visited[v]) {
                // Если путь через текущий аэропорт 'u' короче, чем то, что записано у соседа 'v'
                if (dist[u] + current_route->distance < dist[v]) {
                    dist[v] = dist[u] + current_route->distance;
                }
            }
            current_route = current_route->next_route; // Переходим к следующему рейсу
        }
    }
