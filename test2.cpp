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
};

Airport* main_ptr;

Airport* create_airport(string name, string city, string country, string code)
{
    Airport* new_node = new Airport;
    new_node->name = name;
    new_node->city = city;
    new_node->country = country;
    new_node->code = code;
    return new_node;
}

Route* create_route(string departure, string arrival, int distance, int flight_time, Airport* dep_airport_ptr, Airport* arr_airport_ptr)
{
    Route* new_node = new Route;
    new_node->departure = departure;
    new_node->arrival = arrival;
    new_node->distance = distance;
    new_node->flight_time = flight_time;
    new_node->dep_airport_ptr = dep_airport_ptr;
    new_node->arr_airport_ptr = arr_airport_ptr;
    return new_node;
}

Airport* find_Airport(string code)
{
    Airport* temp = main_ptr;
    while(temp != nullptr)
    {
        if(temp->code == code){
            break;
        }
        temp = temp->next_airport;
    }
    return temp;
}


