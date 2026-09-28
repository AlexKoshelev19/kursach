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

Airport* create_airport(string name, string city, string country, string code)
{
    Airport* new_node = new Airport;
    new_node->name = name;
    new_node->city = city;
    new_node->country = country;
    new_node->code = code;
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
    return new_node;
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

    Airport* temp = departure;
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
        if(temp = arrival)
        {
            end_index = i;
        }

        temp = temp->next_airport;
    }

    dist[start_index] = 0;


    /*
    берем начальный узел, у него дистанция 0
    у остальных дистанция бесконечность
    смотрим на соседей узла 
        складываем текущую дистанцию и путь до соседа
        сравниваем суммарную дистанцию и текущую дистанцию узла

    */
}