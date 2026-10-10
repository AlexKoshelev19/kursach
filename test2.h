#pragma once
#include <string>
#include <iostream>
#include <conio.h>   
#include <windows.h>
#include <regex>
#include <fstream>
using namespace std;

int sum(int a, int b);
struct Route;
struct Airport;
void search_route(Airport* departure, Airport* arrival);
int count_of_Airport();
void print_Airport(Airport* current);
bool is_direct_route(Airport* departure, Airport* arrival);
Airport* find_Airport(string code);
Route* create_route( Airport* dep_airport_ptr, Airport* arr_airport_ptr, string distance, string flight_time);
void create_airport(string name, string city, string country, string code);
void file_mode();
void create_route_mode();
void print_route(Airport* dep_airport);
void create_airport_mode();
void create_airport_mode(Airport* &temp);
void delete_route(Airport* dep_airport, Airport* arr_airport = nullptr);
void delete_airport(Airport* name_airport);
bool is_valid_word(const string& word);
bool is_valid_digit(const string& word);
bool is_valid_code(const string& code);
string good_scan(bool (*is_valid)(const string&));