#include <iostream>
#include "func.h"
#include <stdlib.h>
using namespace std;
void menu();
void menu1();
void menu2();
void menu3();

void recin()
{
  cin.clear();
  while(cin.get()!='\n') continue;
  cout<<"Некорректный ввод, попробуйте еще раз"<<endl;
}
      

int main_menu(char* file1,char* file2,char* file3,char* file4)
{
  int a,b,go;
  system("clear");
  control ctrl;
  if (load_base(&ctrl,file1,file2,file3,file4)==1) cout<<"АВТОЗАГРУЗКА БД ЗАВЕРШЕНА"<<endl;
  while(1)
  {
    menu();
    while(!(cin>>a)) recin();
    switch (a)
    {	
      case 1:
        go=1;
        while(go!=0)
        {	
          menu1();
          while(!(cin>>b)) recin();
          switch (b)
          {	
            case 1:	
              if (find_plan(ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                          
            case 2:
              if (find_star(ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                          
            case 3:
              if (find_sozv(ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;
            case 4:
              if (find_gala(ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                         
            case 5: 
              go=0;
              break;                         
            default:
              cout<<"Некорректная команда"<<endl;                          
          }
        }
        break;          	
      case 2:
        go=1;
        while(go!=0)
        {	
          menu2();
          while(!(cin>>b)) recin();
          switch (b)
          {	
            case 1:
              if (input_plan(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                         
            case 2:
              if (input_star(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                         
            case 3:
              if (input_sozv(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                          
            case 4:
              if (input_gala(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                          
            case 5: 
              go=0;
              break;                           
            default:
              cout<<"Некорректная команда"<<endl;                         
          }
        }
        break;          	
      case 3:
        go=1;
        while(go!=0)
        {
          menu3();
          while(!(cin>>b)) recin();
          switch (b)
          {	
            case 1:
              if (delete_plan(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                          
            case 2:
              if (delete_star(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                         
            case 3:
              if (delete_sozv(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                          
            case 4:
              if (delete_gala(&ctrl)==0) cout<<"Некорректный ввод"<<endl;
              break;                         
            case 5: 
              go=0;
              break;                          
            default:
              cout<<"Некорректная команда"<<endl;
          }
        }
        break;          	
      case 4:
        save_base(ctrl,file1,file2,file3,file4);
        break;
      case 5: 
        if (print_base(ctrl)==0) cout<<"Список пуст"<<endl;
        break;
      case 6:
        sort_gala(&ctrl);
        sort_sozv(&ctrl);
        sort_star(&ctrl);
        sort_plan(&ctrl);
        break;
      case 7: 
        cout<<"Выключение интерфейса"<<endl;
        return 1;
      default:
        cout<<"Некорректная команда"<<endl;
    }                
  }
return 1;
}

void menu(void)
{
  cout<<"======  Главное меню  ====== "<<endl;
  cout<<"Введите 1 для поиска информации"<<endl<<"Введите 2 для добавления элемента"<<endl;
  cout<<"Введите 3 для удаления элемента"<<endl<<"Введите 4 для сохрания базы данных в файл"<<endl;
  cout<<"Введите 5 для вывода содержимого БД"<<endl<<"Введите 6 для сортировки по названию"<<endl;
  cout<<"Введите 7 для выхода из программы"<<endl;
}
 
void menu1(void)
{
  cout<<"======  Меню поиска  ======"<<endl;       
  cout<<"Введите 1 для поиска планет"<<endl<<"Введите 2 для поиска звезд"<<endl;
  cout<<"Введите 3 для поиска созвездий"<<endl<<"Введите 4 для поиска галактик"<<endl;
  cout<<"Введите 5 для возврата в главное меню"<<endl;
}
 
void menu2(void)
{
  cout<<"======  Меню добавления  ======"<<endl;
  cout<<"Введите 1 для добавления планеты"<<endl<<"Введите 2 для добавления звезды"<<endl;
  cout<<"Введите 3 для добавления созвездия"<<endl<<"Введите 4 для добавления галактики"<<endl;
  cout<<"Введите 5 для возврата в главное меню"<<endl;
}
 
void menu3(void)
{
  cout<<"======  Меню удаления  ======"<<endl;
  cout<<"Введите 1 для удаления планеты"<<endl<<"Введите 2 для удаления звезды"<<endl;
  cout<<"Введите 3 для удаления созвездия"<<endl<<"Введите 4 для удаления галактики"<<endl;
  cout<<"Введите 5 для возврата в главное меню"<<endl;
}