#include <iostream>
#include "menu.h"
using namespace std;

int main(int argc,char* argv[])
{
  if (argc<5)
  {
    cout<<"Некорректное число аргументов"<<endl;
    return 0;
  }
  main_menu(argv[1],argv[2],argv[3],argv[4]);
  return 0;
}