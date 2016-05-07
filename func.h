#include <cmath>
#include <string>
#define sp1 80
#define sp2 70
#define sp3 50
#define fl1 0.13
#define fl2 0.11
#define fl3 0.09
#define tank 70

class coord
{
    float x,y;
  public:
    void set_coord(const coord &a) { x=a.get_x(); y=a.get_y(); }
    void set_coord(float a, float b) { x=a; y=b; }
    float get_x() { return x; }
    float get_y() { return y; }
    float def_dis(const coord &a);
}

class call //класс- поступающий звонок
{
    coord cloc; //местоположение больного
    int ctype; //кому нужна помощь (1-взрослому человеку, 2-ребенку, 3-пожилому человеку)
    int cserv; //какая необходима помощь (1-оказать первую помощь, 2-довести до больницы)
  public:
    coord get_cloc() { return cloc; }
    int get_ctype() { return ctype; }
    int get_cserv() { return cserv; }
    call();
}

class car // класс-машина
{
    time_t time; // время, на которое машина занята
    int type;   // тип машины (1-для взрослого человека, 2-для ребенка, 3-для пожилых людей)
    string num;    // номер машины (ее ведь надо как-то идентифицировать)
    float sp; // скорость машины
    float fl; // топливо на км
  public:
    coord loc_st; // точка начала последнего движения
    coord loc_prim; // положение машины по умолчанию
    coord get_loc_cur(); //возвращает текущие координаты машины, использовать только если машина свободна!
    void move(const call &a, const control &ctrl); /*эта функция двигает машину в указанную точку,  добавляет время на дорогу и оказываемую услугу (1-оказать первую помощь, 2-довести до больницы). 
    Если нужно оказать первую помощь, то добавляется время на дорогу и на оказание первой помощи (в среднем 20 минут), loc_st меняются на координаты последнего больного. 
    Если больного нужно довести до больницы, то время добавляется на дорогу до больного и дорогу от больного до больницы, соответственно, loc_st машины меняются на местоположение больницы. */
    time_t get_time() { return time; }
    int get_type() { return type; }
    int get_num() { return num; }
    float get_sp() { return sp; }
    float get_fl() { return fl; }
    void set_time(time_t a) { time=a; }
    car();
}

class control
{
  public:
    coord *bbeg;
    coord *bend;
    car *cbeg;
    car *cend;
    control();
}

float coord::def_dis(const coord &a) //определение расстояния для стационарной точки
{
  float k=a.get_x();
  float m=a.get_y();
  float p=pow(pow(k-x,2)+pow(m-y,2),0.5);
  return p;
}

coord car::get_loc_cur() //функция возвращает текущее положение машины. Её вызывать только если машина свободна!
//если машина занята, и вы вызовете эту функцию, то она вернет обнуленный объект типа коорд
{
  coord back;
  if (time()-time<0) // проверка на корректное использование. здесь можно вызвать экстренную ситуацию
  {
    cout<<"Некорректный вызов функции get_loc_cur()"<<endl;
    back.set_coord(0,0);
    return back;
  }
  float x=loc_st.get_x();
  float y=loc_st.get_y();
  float k=loc_prim.get_x();
  float m=loc_prim.get_y();
  float dis=pow(pow(k-x,2)+pow(m-y,2),0.5);
  if (dis==0) back.set_coord(loc_prim);
  else
  {
    dis1=(time(NULL)-time)*sp/3600;
    if (dis1>dis)
    {
      back.set_coord(loc_prim);
    }
    else
    {
      float q=(dis1/dis)*loc_prim.get_x()+loc_st.get_x()*(1-dis1/dis);
      float r=(dis1/dis)*loc_prim.get_y()+loc_st.get_y()*(1-dis1/dis);
      back.set_coord(q,r);
    }
  }
  return back;
}
  
void car::move(const call &a, const control &ctrl) //функция двигает машину в точку заказа и добавляет время
{
  if (a.get_cserv()==1) // если оказать первую помощь
  {
    coord tab=get_loc_cur();
    float dis=tab.def_dis(a.get_cloc());
    loc_st.set_coord(a.get_cloc());
    time=time(NULL)+dis/sp*3600+1200;
  }
  if (a.get_cserv()==2) // если вести до больницы
  {
    coord tab=get_loc_cur();
    float dis1=tab.def_dis(a.get_cloc());
    coord fol=a.get_cloc();
    float dis2=fol.def_dis((&ctrl)->bbeg); 
    loc_st.set_coord((&ctrl)->bbeg);
    coord *rex=(&ctrl)->bbeg->next;
    while(rex!=NULL)
    {
      if (dis2>fol.def_dis(*rex))  
      {
        dis2=fol.def_dis(*rex); 
        loc_st.set_coord(*rex);
      }
      rex=rex->next;
    }    
    time=time(NULL)+(dis1+dis2)/sp*3600+300;
  }
  return;
}