#pragma once
#include <string>
#include <iostream>
#include <iostream>
#include <string>
#include <conio.h>   
#include <windows.h> 
using namespace std;

int sum(int a, int b);
struct Route;
struct Airport;
void search_route(Airport* departure, Airport* arrival);
int count_of_Airport();
void print_Airport(Airport* current);
bool is_direct_route(Airport* departure, Airport* arrival);
Airport* find_Airport(string code);
Route* create_route(string departure, string arrival, int distance, int flight_time, Airport* dep_airport_ptr, Airport* arr_airport_ptr);
void create_airport(string name, string city, string country, string code);