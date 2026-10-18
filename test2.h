#pragma once
#include <string>
#include <iostream>
#include <conio.h>   
#include <windows.h>
#include <regex>
#include <fstream>
#include <limits>
#include <time.h>
using namespace std;

int sum(int a, int b);
struct Route;
struct Airport{
    string name;
    string city;
    string country;
    string code;

    Route* routes;

    Airport* next_airport;
};

struct Route{
    Airport* dep_airport_ptr;
    Airport* arr_airport_ptr;
    string distance;
    string flight_time;
    Route* next_route;
};

inline Airport* main_ptr;
void search_route(Airport* departure, Airport* arrival);
int choice_menu(string page_choice[], string message, int size);
int count_of_Airport();
void print_Airport(Airport* current);
bool is_direct_route(Airport* departure, Airport* arrival);
Airport* find_Airport(string code);
Route* create_route(Airport* dep, Airport* arr, string distance, string flight_time, bool silent = false);
void create_airport(string name, string city, string country, string code, bool silent = false);
void file_mode();
bool create_route_mode(Airport* dep_airport_ptr, Airport* arr_airport_ptr);
void print_routes(Airport* dep_airport);
void create_airport_mode();
void create_airport_mode(Airport* &temp);
bool delete_route(Airport* dep_airport, Airport* arr_airport = nullptr, bool silent = false);
void delete_airport(Airport* name_airport);
bool is_valid_word( string& word);
bool is_valid_digit(string& word);
bool is_valid_code(string& code);
string good_scan(bool (*is_valid)(string&));
void delete_airplane_mode();
void download_from_file();
void print_all_airports();
void print_all_routes();
void route_mode(int code);
Airport* input_airport(const string& prompt);
void upload_to_file();
bool edit_route(Airport* dep, Airport* arr);
bool duplicate_airport(Airport* current);
bool duplicate_route(Airport* dep_airport_ptr, Airport* arr_airport_ptr);
void edit_airport(Airport* current) ;
void edit_airport_mode();
void print_one_route(Airport* dep_airport, Airport* arrival = nullptr);
string choose_data_file();
