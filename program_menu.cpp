#include "test2.h"
void create_airport_mode();
using namespace std;

void draw_menu(int index, string page_choice[], int size) {
    // Очищаем экран перед каждым выводом, чтобы меню не дублировалось
    for (int i = 0; i < size; i++) {
        if (i == index)
            cout << "> " << page_choice[i] << endl;
        else
            cout << "  " << page_choice[i] << endl; // Добавили пробелы для выравнивания
    }
}

int choice_menu(string page_choice[], string message, int size)
{
 
    int index = 0;
    cout << message << endl << endl;
    draw_menu(index, page_choice, size);
    int c; 
    do{
        
        c = getch();
        system("cls");
        if (c == 224 || c == 0) {
            cout << message << endl << endl;
            c = getch();
            
            if (c == 72) { // Стрелка ВВЕРХ
                index = (index - 1 + size) % size;
                draw_menu(index, page_choice, size);
            }
            else if (c == 80) { 
                index = (index + 1) % size;
                draw_menu(index, page_choice, size);
            }
            else {
                draw_menu(index, page_choice, size); }
        }
        else if(c == 13)
        {
            return index;
        }
        else {
            cout << message <<endl<<endl;
            draw_menu(index, page_choice, size); }
    }
    while (c != 27);
    return -1;
}





void greeting_menu(){
    string page_choice[] = {"Create plane", "Create route", "Загрузить данные из файла ", "Delete airplane", "Delete route"};
    int size = sizeof(page_choice) / sizeof(page_choice[0]);
    string message = "Здравствуйте!\n Данная программа позволяет создавать транспортную сеть аэропортов. Вы можете создать отдельно аэропорты и соединять их маршрутами. При первом запуске программе, рекомендую ознакомиться с инструкцией и далее следовать сообщениям на экране.";
    int index=0;
    do{
        index = choice_menu(page_choice, message, size);
        switch (index){
            case 0: create_airport_mode(); break;
            case 1: create_route_mode(); break;
            case 2: file_mode(); break;
            case 3: page_choice[index]; break;
            case 4: page_choice[index]; break;
            case -1: break;
            default: continue;
        }
        
    } while(index != -1);
    return; 
}












void file_mode()
{
    string page_choice[] = {"Загрузить данные из файла", "Выйти в главное меню"};
    int size = sizeof(page_choice) / sizeof(page_choice[0]);
    string message = "Для загрузки транспортной сети убедитесь в наличии файла transport_net.txt в директории программы.";
    int index=0;
    do
    {
        index = choice_menu(page_choice, message, size);
        switch (index)
        {
            case 0: system("cls"); cout << "Здесь будет работа с файлами"; break;
            case 1:  return;
            case -1: break;
            default: continue;
        }
   } while(index != -1);
    return; 
}






void create_airport_mode(Airport* &temp)
{   char c;
    do {

        string message = "Для создания аэропорта вам необходимо ввести данные в следующие поля: Код аэропорта, название, город, страну ";
        cout << message << endl;

        cout << endl << " Введите название аэропорта: ";
        string name_airport;
        getline(cin, name_airport);

        cout << endl << " Введите код аэропорта: ";
        string code_airport;
        getline(cin, code_airport);

        cout << endl << " Введите город аэропорта: ";
        string city_airport;
        getline(cin, city_airport);

        cout << endl << " Введите страну аэропорта: ";
        string country_airport;
        getline(cin, country_airport);

        create_airport(name_airport, city_airport, country_airport, code_airport);

        temp = find_Airport(name_airport);
        print_Airport(temp);
        cout << "нажмите любую клавишу чтобы добавить новый аэропорт" << endl;
        c = getch();
    } while (c !=27 );
}


void create_airport_mode()
{
    Airport* local_temp = nullptr;
    create_airport_mode(local_temp);
}





void create_route_mode()
{
    char c;
    string message = "Для создания маршрута вам необходимо ввести данные об аэропортах отправления и назначения, продолжительность полета и расстояние. ";
    cout << message << endl;
    do {
        string dep_airport;
        cout << endl << "Введите название аэропорта отправления: ";
        getline(cin, dep_airport);
        Airport* dep_airport_ptr = find_Airport(dep_airport);


        if (dep_airport_ptr == nullptr) {
            // cout << "Аэропорта с данным названием нет, желаете создать аэропорт?" << endl;
            string page_choice[] = {"Создать аэропорт ", "Выйти в главное меню"};
            int size = sizeof(page_choice) / sizeof(page_choice[0]);
            string message = "Аэропорта с названием " + dep_airport + " нет, желаете создать аэропорт?.";
            int index=0;
            do{
                index = choice_menu(page_choice, message, size);
                switch (index){
                    case 0: system("cls"); create_airport_mode(dep_airport_ptr); getch(); index = -1; break;
                    case 1:  return;
                    case -1: break;
                     default: continue;
                }
            } while(index != -1);
        }

        cout << endl << "Введите название аэропорта назначения: ";
        string arr_airport;
        getline(cin, arr_airport);
        Airport* arr_airport_ptr = find_Airport(arr_airport);


        if (arr_airport_ptr == nullptr) {

            string page_choice[] = {"Создать аэропорт ", "Выйти в главное меню"};
            int size = sizeof(page_choice) / sizeof(page_choice[0]);
            string message = "Аэропорта с названием " + dep_airport + " нет, желаете создать аэропорт?.";
            int index=0;
            do{
                index = choice_menu(page_choice, message, size);
                switch (index){
                    case 0: system("cls"); create_airport_mode(arr_airport_ptr); getch(); index = -1; break;
                    case 1:  return;
                    case -1: break;
                    default: continue;
                }
            } while(index != -1);
        }



        cout << dep_airport_ptr << endl;
        cout << endl << "Введите расстояние между аэропортами: ";
        int distance;
        cin >> distance;

        cout << endl << "Введите продолжительность полета: ";
        int flight_time;
        cin >> flight_time;

        Route* temp = create_route(dep_airport, arr_airport, distance, flight_time, dep_airport_ptr, arr_airport_ptr);
        cout << "Маршрут создан!" << endl;
        print_route(dep_airport_ptr);

        cout << "желаете ввести новый маршрут?(esc - выйти в главное меню)";
        c = getch();
        system("cls");
    } while (c!=27);
    return;
}


void delete_airplane_mode() {
    cout << "Введите название аэропорта, который вы хотите удалить: ";
    string airport_name;
    cin >> airport_name;
    Airport* temp = find_Airport(airport_name);
    if (temp == nullptr) {
        cout << "Введите заново: ";
    }
    else
    {
        delete_airport(temp);
    }

}







void route_mode(int code) {
    string message = "Для удаления маршрута введите: ";
    cout << message << endl;
    cout << endl << "Введите название аэропорта отправления: ";
    string dep_airport;
    getline(cin, dep_airport);
    Airport* dep_airport_ptr = find_Airport(dep_airport);

    cout << endl << "Введите название аэропорта назначения: ";
    string arr_airport;
    getline(cin, arr_airport);
    Airport* arr_airport_ptr = find_Airport(arr_airport);
    switch (code) {
        case 1:break; //удаление маршрута
        case 2:break; //определение прямого маршрута между аэропортами
        case 3:break; //определение маршрута между аэропортами с пересадками
        case 4:break;
            //вывод
    }
    // если все проверки пройдены, запихнуть функцию удаления маршрута
}






void work_transport_net()
{
    string page_choice[] = {"удалить аэропорт", "удалить маршрут", "редактировать информацию об аэропорте", "вывести все маршруты для выбранного аэропорта",  "	определить наличие прямого маршрута между двумя аэропортами", "определить возможность добраться из одного аэропорта в другой с пересадками"};
    int size = sizeof(page_choice) / sizeof(page_choice[0]);
    string message = "В данном разделе вы можете: ";
    int index=0;
    do{
        index = choice_menu(page_choice, message, size);
        switch (index){
            case 0: system("cls"); cout << "Здесь будет удаление аэропорта"; break;
            case 1: system("cls"); cout << "Здесь будет удаление маршрута"; break;
            case 2: system("cls"); cout << "Здесь будет редактирование"; break;
            case 3: system("cls"); cout << "Здесь будет определение прямого маршрута"; break;
            case 4: system("cls"); cout << "Здесь будет определение маршрута с пересадками"; break;
            case 5: system("cls"); cout << "Здесь будет вывод всех маршрутов"; break;break;
            case -1: break;
            default: continue;
        }
    } while(index != -1);
    return;
}






void print_routes(int code){


    cout << endl << "Введите название аэропорта отправления: ";
    string dep_airport;
    getline(cin, dep_airport);
    Airport* dep_airport_ptr = find_Airport(dep_airport);

    cout << endl << "Введите название аэропорта назначения: ";
    string arr_airport;
    getline(cin, arr_airport);
    Airport* arr_airport_ptr = find_Airport(arr_airport);

    switch (code)
    {
        case 1: break;
        case 2: break;
        case 3: break;
    }
}




int main() {
   
    SetConsoleOutputCP(65001); 
    SetConsoleCP(65001);
    char c;
    do{
    cout << "Проба пера " << endl;
    c = getch();
    if(c == 27)  break; 
    greeting_menu();
    } while(c != 27);
    return 0;
}
