#include "test2.h"

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
        }
        else if(c == 13)
        {
            return index;
        }
    }
    while (c != 27);
    return -1;
}

void greeting_menu(){
    string page_choice[] = {"Create plane", "Create route", "Delete airplane", "Delete route"};
    int size = sizeof(page_choice) / sizeof(page_choice[0]);
    string message = "Здравствуйте!\n Данная программа позволяет создавать транспортную сеть аэропортов. Вы можете создать отдельно аэропорты и соединять их маршрутами. При первом запуске программе, рекомендую ознакомиться с инструкцией и далее следовать сообщениям на экране.";
    int index=0;
    do{
        index = choice_menu(page_choice, message, size);
        switch (index){
            case 0: page_choice[index]; break;
            case 1:page_choice[index]; break;
            case 2:page_choice[index]; break;
            case 3:page_choice[index]; break;
            case -1: break;
        }
        
    } while(index != -1);
    return; 
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
