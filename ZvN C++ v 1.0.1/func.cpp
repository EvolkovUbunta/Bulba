#include <iostream>
#include <cstring>
#include <fstream>
#include "func.h"
#include <stdlib.h>
using namespace std;

void inp_clear()	//очистка потока cin от мусора
{
  cin.clear();
  cin.ignore();
}

void reinp()	//используется при неудачном вводе числа
{                         
  cin.clear();
  while(cin.get()!='\n') continue;
}

control::control()	//инициализация указателей на начало и конец
{
  gal_beg=NULL;
  gal_end=NULL;
  soz_beg=NULL;
  soz_end=NULL;
  sta_beg=NULL;
  sta_end=NULL;
  pla_beg=NULL;
  pla_end=NULL;
  cout<<"ИНИЦИАЛИЗАЦИЯ БД ЗАВЕРШЕНА"<<endl;
}

void pla::show_info()	//вывод содержимого объекта класса планета
{
  cout<<name<<"\t"<<roz<<"\t"<<pvvo<<"\t"<<rad<<"\t"<<srpl<<"\t"<<nstr<<"\t"<<nsoz<<"\t"<<ngal<<endl;
}  

void sta::show_info()	//вывод содержимого объекта класса звезда
{
  cout<<name<<"\t"<<spkl<<"\t"<<cvet<<"\t"<<temp<<"\t"<<mass<<"\t"<<zvvl<<"\t"<<razm<<"\t"<<nsoz<<"\t"<<ngal<<endl;
}

void soz::show_info()	//вывод содержимого объекта
{
  cout<<name<<"\t"<<lnaz<<"\t"<<plos<<"\t"<<chzv<<"\t"<<sokr<<"\t"<<ngal<<endl;
}

void gal::show_info()	//вывод содержимого объекта
{
  cout<<name<<"\t"<<vgal<<"\t"<<diam<<"\t"<<mass<<"\t"<<ktm<<endl;
}

int gal::get_info()	//получение информации объектом из терминала
{
  cout<<"Название галактики: ";
  inp_clear();
  getline(cin,name);
  cout<<"Вид галактики: ";
  //inp_clear();  функция cin.ignore() убирает 1 символ из строки вида 
  getline(cin,vgal);   // поэтому сюда только cin.clear(), но и ее можно не ставить, т.к ранее строка
  cout<<"Диаметр галактики в световых годах: ";
  if (cin>>diam==0) 
  {
    reinp();
    return 0;
  }
  cout<<"Масса галактики (в эквиваленте масс Солнца *10^12): ";
  if (cin>>mass==0) 
  {
    reinp();
    return 0;
  }
  cout<<"Кол-во черной материи в процентах: ";
  if (cin>>ktm==0) 
  {
    reinp();
    return 0;
  }
  if ((ktm>100) || (ktm<0)) return 0;
  return 1;
}  

int soz::get_info(control &ctrl)	//получение информации объектом из терминала
{
  cout<<"Название галактики, к которой принадлежит созвездие: "<<endl;
  inp_clear();
  getline(cin,ngal);
  int ch=0;
  gal *rex=(&ctrl)->gal_beg;
  while (rex!=NULL)
  {   
    if (ngal==rex->giv_name())  ch++;
    rex=rex->next;
  }
  if (ch==0)
  { 
    cout<<"ТАКОЙ ГАЛАКТИКИ НЕТ В БАЗЕ ДАННЫХ"<<endl;
    return 0;
  }
  cout<<"Название созвездия: ";
  //inp_clear();
  getline(cin,name);
  cout<<"Латинское название: ";
  //inp_clear();
  getline(cin,lnaz);
  cout<<"Площадь созвездия в квадратных градусах: ";
  if (cin>>plos==0) 
  {
    reinp();
    return 0;
  }
  cout<<"Число звезд, ярче 6,0^m: ";
  if (cin>>chzv==0)
  {
    reinp();
    return 0;
  }
  cout<<"Сокращение латинского названия: ";
  inp_clear();
  getline(cin,sokr);
  return 1;
}

int sta::get_info(control &ctrl)	//получение информации объектом из терминала
{ 
  cout<<"Название созвездия, к которому принадлежит звезда: "<<endl;
  inp_clear();
  getline(cin,nsoz);
  int ch=0;
  soz *rex=(&ctrl)->soz_beg;
  while (rex!=NULL)
  {   
    if (nsoz==rex->giv_name())
    {  
      ngal=rex->giv_ngal(); 
      ch++;
    }
    rex=rex->next;
  }
  if (ch==0)
  { 
    cout<<"ТАКОГО СОЗВЕЗДИЯ НЕТ В БАЗЕ ДАННЫХ"<<endl;
    return 0;
  }
  cout<<"Название звезды: ";
  //inp_clear();
  getline(cin,name);
  cout<<"Спектральный класс: ";
  //inp_clear();
  getline(cin,spkl);
  cout<<"Видимый цвет: ";
  //inp_clear();
  getline(cin,cvet);
  cout<<"Температура звезды в млн. градусов Фаренгейта: ";
  if (cin>>temp==0)
  {
    reinp();
    return 0;
  }
  cout<<"Масса звезды в эквиваленте масс Солнца: ";
  if (cin>>mass==0)
  {
    reinp();
    return 0;
  }
  cout<<"Звездная величина ^m: "; 
  if (cin>>zvvl==0)
  {
    reinp();
    return 0;
  }
  cout<<"Размер звезды в радиусах Солнца: ";
  if (cin>>razm==0)
  {
    reinp();
    return 0;
  }
  return 1;
}

int pla::get_info(control &ctrl)	//получение информации объектом из терминала
{
  cout<<"Название звезды, к которому принадлежит палнета: "<<endl;
  inp_clear();
  getline(cin,nstr);
  int ch=0;
  sta *rex=(&ctrl)->sta_beg;
  while (rex!=NULL)
  {   
    if (nstr==rex->giv_name())
    {  
      ngal=rex->giv_ngal();
      nsoz=rex->giv_nsoz(); 
      ch++;
    }
    rex=rex->next;
  }
  if (ch==0)
  { 
    cout<<"ТАКОЙ ЗВЕЗДЫ НЕТ В БАЗЕ ДАННЫХ"<<endl;
    return 0;
  }
  cout<<"Название планеты: ";
  //inp_clear();
  getline(cin,name);
  cout<<"Расстояние от звезды (в млн. км.): ";
  if (cin>>roz==0)
  {
    reinp();
    return 0;
  }
  cout<<"Период вращения вокруг оси (в земных сутках): ";
  if (cin>>pvvo==0)
  {
    reinp();
    return 0;
  }
  cout<<"Радиус планеты (в км.): ";
  if (cin>>rad==0)
  {
    reinp();
    return 0;
  }
  cout<<"Средняя плотность планеты (в кг/м^3): ";
  if (cin>>srpl==0)
  {
    reinp();
    return 0;
  }
  return 1;
}

int input_gala(control *ctrl)	//добавление галактики
{
  system("clear");
  cout<<"\t=== Добавление галактики ==="<<endl;
  while (1)
  {
    gal *rex=new gal;
    if (rex->get_info()==0)
    {
      delete rex;
      return 0;
    }
    if (ctrl->gal_beg==NULL && ctrl->gal_end==NULL) ctrl->gal_beg=rex;
    else ctrl->gal_end->next=rex;
    ctrl->gal_end=rex;
    ctrl->gal_end->next=NULL;
    cout<<"Хотите ввести еще один элемент? (1-да/2-нет)"<<endl;
    int a;
    if (cin>>a==0)
    {
      reinp();
      return 0;
    }
    if (a==2) break;
  }
  return 1;
}

int input_sozv(control *ctrl)	//добавление созвездия
{
  system("clear");
  cout<<"\t=== Добавление созвездия ==="<<endl;
  while (1)
  {
    soz *rex=new soz;
    if (rex->get_info(*ctrl)==0)
    {
      delete rex;
      return 0;
    }
    if (ctrl->soz_beg==NULL && ctrl->soz_end==NULL) ctrl->soz_beg=rex;
    else ctrl->soz_end->next=rex;
    ctrl->soz_end=rex;
    ctrl->soz_end->next=NULL;
    cout<<"Хотите ввести еще один элемент? (1-да/2-нет)"<<endl;
    int a;
    if (cin>>a==0)
    {
      reinp();
      return 0;
    }
    if (a==2) break;
  }
  return 1;
}

int input_star(control *ctrl)	//добавление звезды
{
  system("clear");
  cout<<"\t=== Добавление звезды ==="<<endl;
  while (1)
  {
    sta *rex=new sta;
    if (rex->get_info(*ctrl)==0)
    {
      delete rex;
      return 0;
    }
    if (ctrl->sta_beg==NULL && ctrl->sta_end==NULL) ctrl->sta_beg=rex;
    else ctrl->sta_end->next=rex;
    ctrl->sta_end=rex;
    ctrl->sta_end->next=NULL;
    cout<<"Хотите ввести еще один элемент? (1-да/2-нет)"<<endl;
    int a;
    if (cin>>a==0)
    {
      reinp();
      return 0;
    }
    if (a==2) break;
  }
  return 1;
}

int input_plan(control *ctrl)	//добавление планеты
{
  system("clear");
  cout<<"\t=== Добавление планеты ==="<<endl;
  while (1)
  {
    pla *rex=new pla;
    if (rex->get_info(*ctrl)==0)
    {
      delete rex;
      return 0;
    }
    if (ctrl->pla_beg==NULL && ctrl->pla_end==NULL) ctrl->pla_beg=rex;
    else ctrl->pla_end->next=rex;
    ctrl->pla_end=rex;
    ctrl->pla_end->next=NULL;
    cout<<"Хотите ввести еще один элемент? (1-да/2-нет)"<<endl;
    int a;
    if (cin>>a==0)
    {
      reinp();
      return 0;
    }
    if (a==2) break;
  }
  return 1;
}
  
int find_plan(const control &ctrl)	//поиск планеты
{
  int a;
  system("clear");
  cout<<"\t=== Меню поиска планет ==="<<endl;
  cout<<"1. Поиск по названию планеты"<<endl;
  cout<<"2. Поиск по расстоянию планеты от звезды"<<endl;
  cout<<"3. Поиск по периоду вращения планеты вокруг оси"<<endl;
  cout<<"4. Поиск по радиусу планеты"<<endl;
  cout<<"5. Поиск по средней плотности планеты"<<endl;
  cout<<"6. Поиск по имени звезды, к которой принадлежит планета"<<endl;
  cout<<"7. Поиск по имени созвездия, к которому принадлежит планета"<<endl;
  cout<<"8. Поиск по имени галактики, к которой принадлежит планета"<<endl;
  cout<<"9. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  pla *rex=(&ctrl)->pla_beg;
  int sp=0;
  string s_name,s_nstr,s_nsoz,s_ngal;
  float s_roz,s_pvvo,s_rad,s_srpl;
  switch(a)
  {
    case 1:
      cout<<"Название планеты: ";
      inp_clear();
      getline(cin,s_name);
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name) 
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 2:
      cout<<"Расстояние планеты от звезды (в млн. км.): ";
      if (cin>>s_roz==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_roz()==s_roz)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 3:
      cout<<"Период вращения планеты вокруг оси (в земных сутках): ";
      if (cin>>s_pvvo==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_pvvo()==s_pvvo)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 4:
      cout<<"Радиус планеты (в км.): ";
      if (cin>>s_rad==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_rad()==s_rad)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 5:
      cout<<"Средняя плотность планеты (в кг/м^3): ";
      if (cin>>s_srpl==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_srpl()==s_srpl)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 6:
      cout<<"Название звезды, к которой принадлежит планета: ";
      inp_clear();
      getline(cin,s_nstr);
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_nstr()==s_nstr)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 7:
      cout<<"Название созвездия, к которому принадлежит планета: ";
      inp_clear();
      getline(cin,s_nsoz);
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_nsoz()==s_nsoz)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 8:
      cout<<"Название галактики, к которой принадлежит планеты: ";
      inp_clear();
      getline(cin,s_ngal);
      cout<<"Найденные планеты:"<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_ngal()==s_ngal)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;     
    case 9: 
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;
}    

int find_star(const control &ctrl)	//поиск звезды
{
  int a;
  system("clear");
  cout<<"\t=== Меню поиска звезд ==="<<endl;
  cout<<"1. Поиск по названию звезды"<<endl;
  cout<<"2. Поиск по спектральному классу звезды"<<endl;
  cout<<"3. Поиск по видимому цвету звезды"<<endl;
  cout<<"4. Поиск по температуре звезды"<<endl;   
  cout<<"5. Поиск по массе звезды"<<endl;
  cout<<"6. Поиск по звездной величине звезды"<<endl;    
  cout<<"7. Поиск по размерам звезды в радиусах солнца"<<endl;
  cout<<"8. Поиск по названию созвездия, к которому принадлежит звезда"<<endl;
  cout<<"9. Поиск по названию галактики, к которой принадлежит звезда"<<endl;
  cout<<"0. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  sta *rex=(&ctrl)->sta_beg;
  int sp=0;
  string s_name,s_spkl,s_cvet,s_nsoz,s_ngal;
  float s_temp,s_mass,s_zvvl,s_razm;
  switch(a)
  {
    case 1:
      cout<<"Название звезды: ";
      inp_clear();
      getline(cin,s_name);
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name) 
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break; 
    case 2:
      cout<<"Спектральный класс планеты: ";
      inp_clear();
      getline(cin,s_spkl);
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_spkl()==s_spkl)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 3:
      cout<<"Видимый цвет звезды: ";
      inp_clear();
      getline(cin,s_cvet);
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_cvet()==s_cvet)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 4:
      cout<<"Температуры звезды (в млн. 'F): ";
      if (cin>>s_temp==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_temp()==s_temp)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 5:
      cout<<"Масса звезды (в экв. масс Солнца): ";
      if (cin>>s_mass==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_mass()==s_mass)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 6:
      cout<<"Звездная величина звезды (в ^m): ";
      if (cin>>s_zvvl==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_zvvl()==s_zvvl)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 7:
      cout<<"Размер звезды (в радиусах Солнца): ";
      if (cin>>s_razm==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_razm()==s_razm)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 8:
      cout<<"Название созвездия, к которому принадлежит звезда: ";
      inp_clear();
      getline(cin,s_nsoz);
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_nsoz()==s_nsoz)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 9:
      cout<<"Название галактики, к которой принадлежит звезда: ";
      inp_clear();
      getline(cin,s_ngal);
      cout<<"Найденные звезды: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_ngal()==s_ngal)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next; 
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 0:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;
}

int find_sozv(const control &ctrl)	//поиск созвездия
{
  int a;
  system("clear");
  cout<<"\t=== Меню поиска созвездий ==="<<endl;
  cout<<"1. Поиск по названию созвездия"<<endl;
  cout<<"2. Поиск по латинскому названию созвездия"<<endl;
  cout<<"3. Поиск по площади созвездия"<<endl;
  cout<<"4. Поиск по числу звезд, ярче 6.0^m"<<endl;   
  cout<<"5. Поиск по сокращению лат. названия"<<endl;
  cout<<"6. Поиск по имени галактики, к которой принадлежит созвездие"<<endl;
  cout<<"7. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  soz *rex=(&ctrl)->soz_beg;
  int sp=0;
  string s_name,s_lnaz,s_sokr,s_ngal;
  float s_plos;
  int s_chzv;
  switch(a)
  {
    case 1:
      cout<<"Название созвездия: ";
      inp_clear();
      getline(cin,s_name);
      cout<<"Найденные созвездия: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 2:
      cout<<"Лат. название созвездия: ";
      inp_clear();
      getline(cin,s_lnaz);
      cout<<"Найденные созвездия: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_lnaz()==s_lnaz)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 3:
      cout<<"Площадь созвездия (в кв. градусах): ";
      if (cin>>s_plos==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные созвездия: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_plos()==s_plos)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 4:
      cout<<"Число звезд ярче 6.0^m: "<<endl;
      if (cin>>s_chzv==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные созвездия: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_chzv()==s_chzv)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 5:
      cout<<"Сокращение лат. названия: ";
      inp_clear();
      getline(cin,s_sokr);
      cout<<"Найденные созвездия: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_sokr()==s_sokr)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 6:
      cout<<"Название галактики, к которой принадлежит созвездие: ";
      inp_clear();
      getline(cin,s_ngal);
      cout<<"Найденные созвездия: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_ngal()==s_ngal)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 7:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;        
}

int find_gala(const control &ctrl)	//поиск галактики
{
  int a;
  system("clear");
  cout<<"\t=== Меню поиска галактик ==="<<endl;
  cout<<"1. Поиск по названию галактики"<<endl;
  cout<<"2. Поиск по виду галактики"<<endl;
  cout<<"3. Поиск по диаметру галактики"<<endl;
  cout<<"4. Поиск по массе галактики"<<endl;   
  cout<<"5. Поиск по кол-ву черной материи"<<endl;
  cout<<"6. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  gal *rex=(&ctrl)->gal_beg;
  int sp=0;
  string s_name,s_vgal;
  float s_diam,s_mass,s_ktm;
  switch(a)
  {	
    case 1:
      cout<<"Название галактики: ";
      inp_clear();
      getline(cin,s_name);
      cout<<"Найденные галактики: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 2:
      cout<<"Вид галактики: ";
      inp_clear();
      getline(cin,s_vgal);
      cout<<"Найденные галактики: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_vgal()==s_vgal)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 3:
      cout<<"Диаметр галактики (в световых годах): "<<endl;
      if (cin>>s_diam==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные галактики: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_diam()==s_diam)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 4:
      cout<<"Масса галактики (в эквиваленте масс Солнца *10^12): ";
      if (cin>>s_mass==0)
      {
        reinp();
        return 0;
      }
      cout<<"Найденные галактики: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_mass()==s_mass)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 5:
      cout<<"Кол-во черной материи (в процентах): ";
      if (cin>>s_ktm==0)
      {
        reinp();
        return 0;
      }
      if ((s_ktm<0) || (s_ktm>100)) return 0;
      cout<<"Найденные галактики: "<<endl;
      while (rex!=NULL)
      {
        if (rex->giv_ktm()==s_ktm)
        {
          rex->show_info();
          sp++;
        }
        rex=rex->next;
      }
      if (sp==0) cout<<"Ничего не найдено"<<endl;
      break;
    case 6:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;     
  }
  return 1;
}

pla* del(pla *rex,control *ctrl)	//работа со списком объектов при удалении планеты
{
  if (rex==ctrl->pla_beg && rex==ctrl->pla_end) //если единственный элемент
  {
    ctrl->pla_beg=NULL;
    ctrl->pla_end=NULL;
    delete rex;
    rex=ctrl->pla_beg;
    return rex;
  }
  if (rex==ctrl->pla_beg) //если первый элемент
  {
    ctrl->pla_beg=ctrl->pla_beg->next;
    delete rex;
    rex=ctrl->pla_beg;
  }
  else	//если не первый
  {
    pla *prev=ctrl->pla_beg;
    while (prev->next!=rex) prev=prev->next;
    if (rex==ctrl->pla_end)	//если последний элемент
    {
      prev->next=NULL;
      ctrl->pla_end=prev;
      delete rex;
      rex=prev->next;
    }
    else	//если элемент где-то в середине
    {
      prev->next=rex->next;
      delete rex;
      rex=prev->next;
    }
  }
return rex;
}

sta* del(sta *rex,control *ctrl)	//работа со списком объектов при удалении звезды
{
  if (rex==ctrl->sta_beg && rex==ctrl->sta_end) //если единственный элемент
  {
    ctrl->sta_beg=NULL;
    ctrl->sta_end=NULL;
    delete rex;
    rex=ctrl->sta_beg;
    return rex;
  }
  if (rex==ctrl->sta_beg) //если первый элемент
  {
    ctrl->sta_beg=ctrl->sta_beg->next;
    delete rex;
    rex=ctrl->sta_beg;
  }
  else	//если не первый
  {
    sta *prev=ctrl->sta_beg;
    while (prev->next!=rex) prev=prev->next;
    if (rex==ctrl->sta_end)	//если последний элемент
    {
      prev->next=NULL;
      ctrl->sta_end=prev;
      delete rex;
      rex=prev->next;
    }
    else	//если элемент где-то в середине
    {
      prev->next=rex->next;
      delete rex;
      rex=prev->next;
    }
  }
return rex;
}

soz* del(soz *rex,control *ctrl)	//работа со списком объектов при удалении созвездия
{
  if (rex==ctrl->soz_beg && rex==ctrl->soz_end) //если единственный элемент
  {
    ctrl->soz_beg=NULL;
    ctrl->soz_end=NULL;
    delete rex;
    rex=ctrl->soz_beg;
    return rex;
  }
  if (rex==ctrl->soz_beg) //если первый элемент
  {
    ctrl->soz_beg=ctrl->soz_beg->next;
    delete rex;
    rex=ctrl->soz_beg;
  }
  else	//если не первый
  {
    soz *prev=ctrl->soz_beg;
    while (prev->next!=rex) prev=prev->next;
    if (rex==ctrl->soz_end)	//если последний элемент
    {
      prev->next=NULL;
      ctrl->soz_end=prev;
      delete rex;
      rex=prev->next;
    }
    else	//если элемент где-то в середине
    {
      prev->next=rex->next;
      delete rex;
      rex=prev->next;
    }
  }
return rex;
}

gal* del(gal *rex,control *ctrl)	//работа со списком объектов при удалении галактики
{
  if (rex==ctrl->gal_beg && rex==ctrl->gal_end) //если единственный элемент
  {
    ctrl->gal_beg=NULL;
    ctrl->gal_end=NULL;
    delete rex;
    rex=ctrl->gal_beg;
    return rex;
  }
  if (rex==ctrl->gal_beg) //если первый элемент
  {
    ctrl->gal_beg=ctrl->gal_beg->next;
    delete rex;
    rex=ctrl->gal_beg;
  }
  else	//если не первый
  {
    gal *prev=ctrl->gal_beg;
    while (prev->next!=rex) prev=prev->next;
    if (rex==ctrl->gal_end)	//если последний элемент
    {
      prev->next=NULL;
      ctrl->gal_end=prev;
      delete rex;
      rex=prev->next;
    }
    else	//если элемент где-то в середине
    {
      prev->next=rex->next;
      delete rex;
      rex=prev->next;
    }
  }
return rex;
}

void del_cont(control *ctrl,sta *rex,pla *cur_pla) //удаление содержимого звезды
{
  while (cur_pla!=NULL)
  {	
    if (cur_pla->giv_nstr()==rex->giv_name()) cur_pla=del(cur_pla,ctrl);
    else cur_pla=cur_pla->next;
  }
}

void del_cont(control *ctrl,soz *rex,sta *cur_sta,pla *cur_pla) //удаление содержимого созвездия
{
  while (cur_pla!=NULL)
  {
    if (cur_pla->giv_nsoz()==rex->giv_name()) cur_pla=del(cur_pla,ctrl);
    else cur_pla=cur_pla->next;
  }
  while (cur_sta!=NULL)
  {
    if (cur_sta->giv_nsoz()==rex->giv_name()) cur_sta=del(cur_sta,ctrl);
    else cur_sta=cur_sta->next;
  }
}

void del_cont(control *ctrl,gal *rex,soz *cur_soz,sta *cur_sta, pla *cur_pla) //удаление содержимого галактики
{
  while (cur_pla!=NULL)
  {
    if (cur_pla->giv_ngal()==rex->giv_name()) cur_pla=del(cur_pla,ctrl);
    else cur_pla=cur_pla->next;
  }
  while (cur_sta!=NULL)
  {
    if (cur_sta->giv_ngal()==rex->giv_name()) cur_sta=del(cur_sta,ctrl);
    else cur_sta=cur_sta->next;
  }
  while (cur_soz!=NULL)
  {
    if (cur_soz->giv_ngal()==rex->giv_name()) cur_soz=del(cur_soz,ctrl);
    else cur_soz=cur_soz->next;
  }  
}

int delete_plan(control *ctrl)	//удаление планеты
{
  int a;
  system("clear");
  cout<<"\t=== Меню удаления планет ==="<<endl;
  cout<<"1. Удаление по названию планеты"<<endl;
  cout<<"2. Удаление по расстоянию планеты от звезды"<<endl;
  cout<<"3. Удаление по периоду вращения планеты вокруг оси"<<endl;
  cout<<"4. Удаление по радиусу планеты"<<endl;   
  cout<<"5. Удаление по средней плотности планеты"<<endl;
  cout<<"6. Удаление по названию звезды, к которой принадлежит планета"<<endl;
  cout<<"7. Удаление по названию созвездия, к которой принадлежит планета"<<endl;
  cout<<"8. Удаление по названию галактики, к которой принадлежит планета"<<endl;
  cout<<"9. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  pla *rex=ctrl->pla_beg;
  int sp=0;
  string s_name,s_nstr,s_nsoz,s_ngal;
  float s_roz,s_pvvo,s_rad,s_srpl;
  switch(a)                   
  {
    case 1:
      cout<<"Название планеты: ";
      inp_clear();
      getline(cin,s_name);
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 2:
      cout<<"Расстояние планеты от звезды (в млн. км.): ";
      if (cin>>s_roz==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_roz()==s_roz)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 3:
      cout<<"Период вращения планеты вокруг оси (в земных сутках): ";
      if (cin>>s_pvvo==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_pvvo()==s_pvvo)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 4:
      cout<<"Радиус планеты (в км.): ";
      if (cin>>s_rad==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_rad()==s_rad)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 5:
      cout<<"Средняя плотность планеты (в кг/м^3): ";
      if (cin>>s_srpl==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_srpl()==s_srpl)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 6:
      cout<<"Название звезды, к которой принадлежит планета: ";
      inp_clear();
      getline(cin,s_nstr);
      while (rex!=NULL)
      {
        if (rex->giv_nstr()==s_nstr)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 7:
      cout<<"Название созвездия, к которому принадлежит планета: ";
      inp_clear();
      getline(cin,s_nsoz);
      while (rex!=NULL)
      {
        if (rex->giv_nsoz()==s_nsoz)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 8:
      cout<<"Название галактики, к которой принадлежит планета: ";
      inp_clear();
      getline(cin,s_ngal);
      while (rex!=NULL)
      {
        if (rex->giv_ngal()==s_ngal)
        {
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 9:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;
}

int delete_star(control *ctrl)	//удаление звезды
{
  int a;
  system("clear");
  cout<<"\t=== Меню удаления звезд ==="<<endl;
  cout<<"1. Удаление по названию звезды"<<endl;
  cout<<"2. Удаление по спектральному классу звезды"<<endl;
  cout<<"3. Удаление по видимому цвету звезды"<<endl;
  cout<<"4. Удаление по температуре звезды"<<endl;   
  cout<<"5. Удаление по массе звезды"<<endl;
  cout<<"6. Удаление по звездной величине"<<endl;
  cout<<"7. Удаление по размеру звезды"<<endl;
  cout<<"8. Удаление по названию созвездия, к которой принадлежит звезда"<<endl;
  cout<<"9. Удаление по названию галактики, к которой принадлежит звезда"<<endl;
  cout<<"0. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  sta *rex=ctrl->sta_beg;
  pla *cur_pla=ctrl->pla_beg;
  int sp=0;
  string s_name,s_spkl,s_cvet,s_nsoz,s_ngal;
  float s_temp,s_mass,s_zvvl,s_razm;
  switch(a)                   
  {
    case 1:
      cout<<"Название звезды: ";
      inp_clear();
      getline(cin,s_name);
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 2:
      cout<<"Спектральный класс звезды: ";
      inp_clear();
      getline(cin,s_spkl);
      while (rex!=NULL)
      {
        if (rex->giv_spkl()==s_spkl)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 3:
      cout<<"Видимый цвет звезды: ";
      inp_clear();
      getline(cin,s_cvet);
      while (rex!=NULL)
      {
        if (rex->giv_cvet()==s_cvet)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 4:
      cout<<"Температура звезды (в млн. 'F): ";
      if (cin>>s_temp==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_temp()==s_temp)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 5:
      cout<<"Масса звезды (в экв. масс Солнца): ";
      if (cin>>s_mass==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_mass()==s_mass)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 6:
      cout<<"Звездная величина (в ^m): ";
      if (cin>>s_zvvl==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_zvvl()==s_zvvl)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 7:
      cout<<"Размер звезды (в радиусах Солнца): ";
      if (cin>>s_razm==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_razm()==s_razm)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 8:
      cout<<"Название созвездия, к которому принадлежит звезда: ";
      inp_clear();
      getline(cin,s_nsoz);
      while (rex!=NULL)
      {
        if (rex->giv_nsoz()==s_nsoz)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 9:
      cout<<"Название галактики, к которой принадлежит звезда: ";
      inp_clear();
      getline(cin,s_ngal);
      while (rex!=NULL)
      {
        if (rex->giv_ngal()==s_ngal)
        {
          del_cont(ctrl,rex,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 0:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;
}

int delete_sozv(control *ctrl)	//удаление созвездия
{
  int a;
  system("clear");
  cout<<"\t=== Меню удаления созвездий ==="<<endl;
  cout<<"1. Удаление по названию созвездия"<<endl;
  cout<<"2. Удаление по латинскому названию созвездия"<<endl;
  cout<<"3. Удаление по площади созвездия"<<endl;
  cout<<"4. Удаление по числу звезд созвездия, ярче 6.0^m"<<endl;   
  cout<<"5. Удаление по сокращению лат. названия созвездия"<<endl;
  cout<<"6. Удаление по названию галактики, к которой принадлежит созвездие"<<endl;
  cout<<"7. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  soz *rex=ctrl->soz_beg;
  sta *cur_sta=ctrl->sta_beg;
  pla *cur_pla=ctrl->pla_beg;
  int sp=0;
  string s_name,s_lnaz,s_sokr,s_ngal;
  float s_plos;
  int s_chzv;
  switch(a)                   
  {
    case 1:
      cout<<"Название созвездия: ";
      inp_clear();
      getline(cin,s_name);
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name)
        {
          del_cont(ctrl,rex,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 2:
      cout<<"Латинское название созвездия: ";
      inp_clear();
      getline(cin,s_lnaz);
      while (rex!=NULL)
      {
        if (rex->giv_lnaz()==s_lnaz)
        {
          del_cont(ctrl,rex,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 3:
      cout<<"Площадь созвездия (в квадратных градусах): ";
      if (cin>>s_plos==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_plos()==s_plos)
        {
          del_cont(ctrl,rex,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 4:
      cout<<"Число звезд созвездия, ярче 6.0^m: ";
      if (cin>>s_chzv==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_chzv()==s_chzv)
        {
          del_cont(ctrl,rex,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 5:
      cout<<"Сокращение лат. названия: ";
      inp_clear();
      getline(cin,s_sokr);
      while (rex!=NULL)
      {
        if (rex->giv_sokr()==s_sokr)
        {
          del_cont(ctrl,rex,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 6:
      cout<<"Название галактики, к которой принадлежит созвездие: ";
      inp_clear();
      getline(cin,s_ngal);
      while (rex!=NULL)
      {
        if (rex->giv_ngal()==s_ngal)
        {
          del_cont(ctrl,rex,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 7:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;
}

int delete_gala(control *ctrl) //удаление галактики
{
  int a;
  system("clear");
  cout<<"\t=== Меню удаления галактик ==="<<endl;
  cout<<"1. Удаление по названию галактики"<<endl;
  cout<<"2. Удаление по виду галактики"<<endl;
  cout<<"3. Удаление по диаметру галактики"<<endl;
  cout<<"4. Удаление по массе галактики"<<endl;   
  cout<<"5. Удаление по кол-ву черной материи галактики"<<endl;
  cout<<"6. Выход в предыдущее меню"<<endl;
  if (cin>>a==0)
  {
    reinp();
    return 0;
  }
  gal *rex=ctrl->gal_beg;
  soz *cur_soz=ctrl->soz_beg;
  sta *cur_sta=ctrl->sta_beg;
  pla *cur_pla=ctrl->pla_beg;
  int sp=0;
  string s_name,s_vgal;
  float s_diam,s_mass,s_ktm;
  switch(a)                   
  {
    case 1:
      cout<<"Название галактики: ";
      inp_clear();
      getline(cin,s_name);
      while (rex!=NULL)
      {
        if (rex->giv_name()==s_name)
        {
          del_cont(ctrl,rex,cur_soz,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 2:
      cout<<"Вид галактики: ";
      inp_clear();
      getline(cin,s_vgal);
      while (rex!=NULL)
      {
        if (rex->giv_vgal()==s_vgal)
        {
          del_cont(ctrl,rex,cur_soz,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 3:
      cout<<"Диаметр галактики (в световых годах): ";
      if (cin>>s_diam==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_diam()==s_diam)
        {
          del_cont(ctrl,rex,cur_soz,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 4:
      cout<<"Масса галактики (в экв. масс Солнца *10^12): ";
      if (cin>>s_mass==0)
      {
        reinp();
        return 0;
      }
      while (rex!=NULL)
      {
        if (rex->giv_mass()==s_mass)
        {
          del_cont(ctrl,rex,cur_soz,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 5:
      cout<<"Кол-во черной материи галактики (в процентах): ";
      if (cin>>s_ktm==0)
      {
        reinp();
        return 0;
      }
      if (s_ktm>100 || s_ktm<0) return 0;
      while (rex!=NULL)
      {
        if (rex->giv_ktm()==s_ktm)
        {
          del_cont(ctrl,rex,cur_soz,cur_sta,cur_pla);
          rex=del(rex,ctrl);
          sp++;
        }
        else rex=rex->next;
      }
      if (sp==0) cout<<"Нечего удалять"<<endl;
      break;
    case 6:
      return 1;
    default:
      cout<<"Некорректная команда"<<endl;
  }
  return 1;    
}
                
int print_base(const control &ctrl)	//Вывод бд на экран
{
  pla *pla_rex=(&ctrl)->pla_beg;
  sta *sta_rex=(&ctrl)->sta_beg;
  soz *soz_rex=(&ctrl)->soz_beg;
  gal *gal_rex=(&ctrl)->gal_beg;
  if ((pla_rex==NULL) && (sta_rex==NULL) && (soz_rex==NULL) && (gal_rex==NULL)) return 0;
  if (pla_rex!=NULL) cout<<"\t ПЛАНЕТЫ:"<<endl;
  while (pla_rex!=NULL)
  {
    pla_rex->show_info();
    pla_rex=pla_rex->next;
  }
  if (sta_rex!=NULL) cout<<"\t ЗВЕЗДЫ:"<<endl;
  while (sta_rex!=NULL)
  {
    sta_rex->show_info();
    sta_rex=sta_rex->next;
  }
  if (soz_rex!=NULL) cout<<"\t СОЗВЕЗДИЯ:"<<endl;
  while (soz_rex!=NULL)
  {
    soz_rex->show_info();
    soz_rex=soz_rex->next;
  }
  if (gal_rex!=NULL) cout<<"\t ГАЛАКТИКИ:"<<endl;
  while (gal_rex!=NULL)
  {
    gal_rex->show_info();
    gal_rex=gal_rex->next;
  }
  return 1;
}

int save_base(const control &ctrl, char* file1, char* file2, char* file3, char* file4)
{	//сохранение бд в файл
  pla *rex_pl=(&ctrl)->pla_beg;
  sta *rex_st=(&ctrl)->sta_beg;
  soz *rex_so=(&ctrl)->soz_beg;
  gal *rex_ga=(&ctrl)->gal_beg;
  ofstream fout_ga(file1);
  if (fout_ga==NULL) 
  {
    cout<<"Не удалось открыть файл со списком галактик"<<endl;
    return 0;
  }
  while (rex_ga!=NULL)
  {
    fout_ga<<rex_ga->giv_name()<<"\t"<<rex_ga->giv_vgal()<<"\t"<<rex_ga->giv_diam()<<"\t"<<rex_ga->giv_mass()<<"\t"<<rex_ga->giv_ktm()<<endl;
    rex_ga=rex_ga->next;
  }
  fout_ga.close();
  ofstream fout_so(file2);
  if (fout_so==NULL)
  {
    cout<<"Не удалось открыть файл со списком созвездий"<<endl;
    return 0;
  }
  while (rex_so!=NULL)
  {
    fout_so<<rex_so->giv_name()<<"\t"<<rex_so->giv_lnaz()<<"\t"<<rex_so->giv_plos()<<"\t"<<rex_so->giv_chzv()<<"\t"<<rex_so->giv_sokr()<<"\t"<<rex_so->giv_ngal()<<endl;
    rex_so=rex_so->next;
  }
  fout_so.close();
  ofstream fout_st(file3);
  if (fout_st==NULL)
  {
    cout<<"Не удалось открыть файл со списком звезд"<<endl;
    return 0;
  }
  while (rex_st!=NULL)
  {
    fout_st<<rex_st->giv_name()<<"\t"<<rex_st->giv_spkl()<<"\t"<<rex_st->giv_cvet()<<"\t"<<rex_st->giv_temp()<<"\t"<<rex_st->giv_mass()<<"\t"<<rex_st->giv_zvvl()<<"\t"<<rex_st->giv_razm()<<"\t"<<rex_st->giv_nsoz()<<"\t"<<rex_st->giv_ngal()<<endl;
    rex_st=rex_st->next;
  }
  fout_st.close();
  ofstream fout_pl(file4);
  if (fout_pl==NULL)
  {
    cout<<"Не удалось открыть файл со списком планет"<<endl;
    return 0;
  }
  while (rex_pl!=NULL)
  {
    fout_pl<<rex_pl->giv_name()<<"\t"<<rex_pl->giv_roz()<<"\t"<<rex_pl->giv_pvvo()<<"\t"<<rex_pl->giv_rad()<<"\t"<<rex_pl->giv_srpl()<<"\t"<<rex_pl->giv_nstr()<<"\t"<<rex_pl->giv_nsoz()<<"\t"<<rex_pl->giv_ngal()<<endl;
    rex_pl=rex_pl->next;
  }
  fout_pl.close();
  cout<<"СОХРАНЕНИЕ БД ЗАВЕРШЕНО"<<endl;
  return 1;
}

void gal::get_file(string ga_name,string ga_vgal,float ga_diam,float ga_mass,float ga_ktm)
{	//копирование в закрытый тип данных объекта класса галактика
  name=ga_name;
  vgal=ga_vgal;
  diam=ga_diam;
  mass=ga_mass;
  ktm=ga_ktm;
}

void soz::get_file(string so_name,string so_lnaz,float so_plos,int so_chzv,string so_sokr,string so_ngal)
{	//копирование в закрытый тип данных объекта класса созвездие
  name=so_name;
  lnaz=so_lnaz;
  plos=so_plos;
  chzv=so_chzv;
  sokr=so_sokr;
  ngal=so_ngal;
}

void sta::get_file(string st_name,string st_spkl, string st_cvet,float st_temp,float st_mass,float st_zvvl,float st_razm,string st_nsoz,string st_ngal)
{	//копирование в закрытый тип данных объекта класса звезда
  name=st_name;
  spkl=st_spkl;
  cvet=st_cvet;
  temp=st_temp;
  mass=st_mass;
  zvvl=st_zvvl;
  razm=st_razm;
  nsoz=st_nsoz;
  ngal=st_ngal;
} 

void pla::get_file(string pl_name,float pl_roz,float pl_pvvo,float pl_rad,float pl_srpl,string pl_nstr,string pl_nsoz,string pl_ngal) 
{	//копирование в закрытый тип данных объекта класса планета
  name=pl_name;
  roz=pl_roz;
  pvvo=pl_pvvo;
  rad=pl_rad;
  srpl=pl_srpl;
  nstr=pl_nstr;
  nsoz=pl_nsoz;
  ngal=pl_ngal;
}
  
int load_base(control *ctrl, char* file1, char* file2, char* file3, char* file4)
{	//загрузка бд из файла
  pla *rex_pl;
  sta *rex_st;
  soz *rex_so;
  gal *rex_ga;
  string ga_name,ga_vgal,so_name,so_lnaz,so_sokr,so_ngal;
  string st_name,st_spkl,st_cvet,st_nsoz,st_ngal,pl_name,pl_nstr,pl_nsoz,pl_ngal;
  char c;
  float ga_diam,ga_mass,ga_ktm,so_plos,st_temp,st_mass,st_zvvl,st_razm;
  float pl_roz,pl_pvvo,pl_rad,pl_srpl;
  int so_chzv;
  ifstream fin_ga(file1);
  if (fin_ga==NULL) 
  {
    cout<<"Не удалось открыть файл со списком галактик"<<endl;
    return 0;
  }     
  while (fin_ga!=NULL)
  {
    c=fin_ga.get();
    if (c==EOF) break;
    else fin_ga.unget();
    rex_ga=new gal;
    getline(fin_ga,ga_name,'\t');
    getline(fin_ga,ga_vgal,'\t');
    fin_ga>>ga_diam>>ga_mass>>ga_ktm;
    rex_ga->get_file(ga_name,ga_vgal,ga_diam,ga_mass,ga_ktm);
    fin_ga.ignore();
    if (ctrl->gal_beg==NULL && ctrl->gal_end==NULL) ctrl->gal_beg=rex_ga;
    else ctrl->gal_end->next=rex_ga;
    ctrl->gal_end=rex_ga;
    ctrl->gal_end->next=NULL;
  }
  fin_ga.close();
  ifstream fin_so(file2);
  if (fin_so==NULL) 
  {
    cout<<"Не удалось открыть файл со списком созвездий"<<endl;
    return 0;
  }     
  while (fin_so!=NULL)
  {
    c=fin_so.get();
    if (c==EOF) break;
    else fin_so.unget();
    rex_so=new soz;
    getline(fin_so,so_name,'\t');
    getline(fin_so,so_lnaz,'\t');
    fin_so>>so_plos>>so_chzv;
    fin_so.ignore();
    getline(fin_so,so_sokr,'\t');
    getline(fin_so,so_ngal,'\n');
    rex_so->get_file(so_name,so_lnaz,so_plos,so_chzv,so_sokr,so_ngal);
    if (ctrl->soz_beg==NULL && ctrl->soz_end==NULL) ctrl->soz_beg=rex_so;
    else ctrl->soz_end->next=rex_so;
    ctrl->soz_end=rex_so;
    ctrl->soz_end->next=NULL;
  }
  fin_so.close();
  ifstream fin_st(file3);
  if (fin_st==NULL) 
  {
    cout<<"Не удалось открыть файл со списком звезд"<<endl;
    return 0;
  }     
  while (fin_st!=NULL)
  {
    c=fin_st.get();
    if (c==EOF) break;
    else fin_st.unget();
    rex_st=new sta;
    getline(fin_st,st_name,'\t');
    getline(fin_st,st_spkl,'\t');
    getline(fin_st,st_cvet,'\t');
    fin_st>>st_temp>>st_mass>>st_zvvl>>st_razm;
    fin_st.ignore();
    getline(fin_st,st_nsoz,'\t');
    getline(fin_st,st_ngal,'\n');
    rex_st->get_file(st_name,st_spkl,st_cvet,st_temp,st_mass,st_zvvl,st_razm,st_nsoz,st_ngal);
    if (ctrl->sta_beg==NULL && ctrl->sta_end==NULL) ctrl->sta_beg=rex_st;
    else ctrl->sta_end->next=rex_st;
    ctrl->sta_end=rex_st;
    ctrl->sta_end->next=NULL;
  }
  fin_st.close();
  ifstream fin_pl(file4);
  if (fin_pl==NULL) 
  {
    cout<<"Не удалось открыть файл со списком звезд"<<endl;
    return 0;
  }     
  while (fin_pl!=NULL)
  {
    c=fin_pl.get();
    if (c==EOF) break;
    else fin_pl.unget();
    rex_pl=new pla;
    getline(fin_pl,pl_name,'\t');
    fin_pl>>pl_roz>>pl_pvvo>>pl_rad>>pl_srpl;
    fin_pl.ignore();
    getline(fin_pl,pl_nstr,'\t');
    getline(fin_pl,pl_nsoz,'\t');
    getline(fin_pl,pl_ngal,'\n');
    rex_pl->get_file(pl_name,pl_roz,pl_pvvo,pl_rad,pl_srpl,pl_nstr,pl_nsoz,pl_ngal);
    if (ctrl->pla_beg==NULL && ctrl->pla_end==NULL) ctrl->pla_beg=rex_pl;
    else ctrl->pla_end->next=rex_pl;
    ctrl->pla_end=rex_pl;
    ctrl->pla_end->next=NULL;
  }
  fin_pl.close();
  return 1;
}

void sort_gala(control *ctrl)	//сортировка списка галактик
{
  if (ctrl->gal_beg==ctrl->gal_end) return;
  int sp;
  while (sp!=1)
  {
    sp=1;
    gal *cur1=ctrl->gal_beg;
    while (cur1!=ctrl->gal_end)
    {
      gal *cur2=cur1->next;
      if (cur1->giv_name()>cur2->giv_name())	//надо поменять местами
      {
        if (cur1==ctrl->gal_beg || cur2==ctrl->gal_end)	//если один элемент стоит первым в списке или второй последним
        {
          if (cur1==ctrl->gal_beg && cur2==ctrl->gal_end)	//если один элемент первый, а второй последним
          {
            cur1->next=NULL;
            cur2->next=cur1;
            ctrl->gal_beg=cur2;
            ctrl->gal_end=cur1;
          }
          else
          {
            if (cur1==ctrl->gal_beg)	//если один элемент первый
            {
              cur1->next=cur2->next;
              cur2->next=cur1;
              ctrl->gal_beg=cur2;
            }
            if (cur2==ctrl->gal_end)	//если другой элемент последний
            {
              gal *cur0=ctrl->gal_beg;
              while (cur0->next!=cur1) cur0=cur0->next;
              cur0->next=cur2;
              cur2->next=cur1;
              cur1->next=NULL;
              ctrl->gal_end=cur1;
            }
          }
        }
        else	//если элементы в середине списка
        {
          gal* cur0=ctrl->gal_beg;
          while(cur0->next!=cur1) cur0=cur0->next; 
          cur0->next=cur2;
          cur1->next=cur2->next;
          cur2->next=cur1;
        }
        sp++;
      }
      else cur1=cur1->next;  
    }
  }
  cout<<"Список галактик отсортирован"<<endl;
}

void sort_sozv(control *ctrl)	//сортировка списка созвездий
{
  if (ctrl->soz_beg==ctrl->soz_end) return;
  int sp=0;
  while (sp!=1)
  {
    sp=1;
    soz *cur1=ctrl->soz_beg;
    while (cur1!=ctrl->soz_end)
    {
      soz *cur2=cur1->next;
      if (cur1->giv_name()>cur2->giv_name())
      {
        if (cur1==ctrl->soz_beg || cur2==ctrl->soz_end)
        {
          if (cur1==ctrl->soz_beg && cur2==ctrl->soz_end)
          {
            cur1->next=NULL;
            cur2->next=cur1;
            ctrl->soz_beg=cur2;
            ctrl->soz_end=cur1;
          }
          else
          {
            if (cur1==ctrl->soz_beg)
            {
              cur1->next=cur2->next;
              cur2->next=cur1;
              ctrl->soz_beg=cur2;
            }
            if (cur2==ctrl->soz_end)
            {
              soz *cur0=ctrl->soz_beg;
              while (cur0->next!=cur1) cur0=cur0->next;
              cur0->next=cur2;
              cur2->next=cur1;
              cur1->next=NULL;
              ctrl->soz_end=cur1;
            }
          }
        }
        else 
        {
          soz* cur0=ctrl->soz_beg;
          while(cur0->next!=cur1) cur0=cur0->next; 
          cur0->next=cur2;
          cur1->next=cur2->next;
          cur2->next=cur1;
        }
        sp++;
      }
      else cur1=cur1->next;  
    }
  }
  cout<<"Список созвездий отсортирован"<<endl;
}

void sort_star(control *ctrl)	//мортировка списка звезд
{
  if (ctrl->sta_beg==ctrl->sta_end) return;
  int sp=0;
  while (sp!=1)
  {
    sp=1;
    sta *cur1=ctrl->sta_beg;
    while (cur1!=ctrl->sta_end)
    {
      sta *cur2=cur1->next;
      if (cur1->giv_name()>cur2->giv_name())
      {
        if (cur1==ctrl->sta_beg || cur2==ctrl->sta_end)
        {
          if (cur1==ctrl->sta_beg && cur2==ctrl->sta_end)
          {
            cur1->next=NULL;
            cur2->next=cur1;
            ctrl->sta_beg=cur2;
            ctrl->sta_end=cur1;
          }
          else
          {
            if (cur1==ctrl->sta_beg)
            {
              cur1->next=cur2->next;
              cur2->next=cur1;
              ctrl->sta_beg=cur2;
            }
            if (cur2==ctrl->sta_end)
            {
              sta *cur0=ctrl->sta_beg;
              while (cur0->next!=cur1) cur0=cur0->next;
              cur0->next=cur2;
              cur2->next=cur1;
              cur1->next=NULL;
              ctrl->sta_end=cur1;
            }
          }
        }
        else 
        {
          sta* cur0=ctrl->sta_beg;
          while(cur0->next!=cur1) cur0=cur0->next; 
          cur0->next=cur2;
          cur1->next=cur2->next;
          cur2->next=cur1;
        }
        sp++;
      }
      else cur1=cur1->next;  
    }
  }
  cout<<"Список звезд отсортирован"<<endl;
}

void sort_plan(control *ctrl)	//сортировка списка планет
{
  if (ctrl->pla_beg==ctrl->pla_end) return;
  int sp=0;
  while (sp!=1)
  {
    sp=1;
    pla *cur1=ctrl->pla_beg;
    while (cur1!=ctrl->pla_end)
    {
      pla *cur2=cur1->next;
      if (cur1->giv_name()>cur2->giv_name())
      {
        if (cur1==ctrl->pla_beg || cur2==ctrl->pla_end)
        {
          if (cur1==ctrl->pla_beg && cur2==ctrl->pla_end)
          {
            cur1->next=NULL;
            cur2->next=cur1;
            ctrl->pla_beg=cur2;
            ctrl->pla_end=cur1;
          }
          else
          {
            if (cur1==ctrl->pla_beg)
            {
              cur1->next=cur2->next;
              cur2->next=cur1;
              ctrl->pla_beg=cur2;
            }
            if (cur2==ctrl->pla_end)
            {
              pla *cur0=ctrl->pla_beg;
              while (cur0->next!=cur1) cur0=cur0->next;
              cur0->next=cur2;
              cur2->next=cur1;
              cur1->next=NULL;
              ctrl->pla_end=cur1;
            }
          }
        }
        else 
        {
          pla* cur0=ctrl->pla_beg;
          while(cur0->next!=cur1) cur0=cur0->next; 
          cur0->next=cur2;
          cur1->next=cur2->next;
          cur2->next=cur1;
        }
        sp++;
      }
      else cur1=cur1->next;  
    }
  }
  cout<<"Список планет отсортирован"<<endl;
}