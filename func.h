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
    float get_x() { return x; }
    float get_y() { return y; }
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
    float fuel; // кол-во топлива в баке машины
    coord loc;  // текущее местположение машины
    int type;   // тип машины (1-для взрослого человека, 2- для ребенка, 3 - для пожилых людей)
    int num;    // номер машины ( ее ведь надо как-то идентифицировать)
  public:
    time_t get_time() { return time; }
    float get_fuel() { return fuel; }
    coord get_loc() { return loc; }
    int get_type() { return type; }
    int get_num() { return num; }
    void change(const call &a, int b); /*эта функция передвигает машину в указанную точку, отнимает бензин, добавляет время на дорогу и оказываемую услугу (1-оказать первую помощь, 2-довести до больницы. Если нужно оказать первую помощь, то добавляется время на дорогу и на оказание первой помощи (в среднем 20 минут), а бензин отнимается только на дорогу от точки до точки, координаты меняются на координаты последнего больного. Если больного нужно довести до больницы, то время добавляется на дорогу до больного и дорогу от больного до больницы, бензит тратится, соответственно, на два промежутка пути, координаты машины меняются на местоположение больницы. */
    void refill(); /* эта функция страбатывает, если осталось меньше 10 литров (примерно). Она ищет ближайшую заправку, меняет координаты машины на координаты заправки, тратит бензин на дорогу до заправки и добавляет время на дорогу до заправки и саму заправку. Тут возникает вопрос: что делать если машине не хватает бензина до заправки? Можно добавлять машине 1 час (например) за это время ей доставляют бензин, при этом ее координаты не меняются, а бак становится полным. */
    float def_dis(const coord &a);
    void set_time(time_t a) { time=a; } // использовать конструктор копий
    void set_fuel(float a) { fuel=a; }
    void set_loc(const coord &a) { x=a.get_x(); y=a.get_y(); }
    car();
}

class control
{
  public:
    coord *bbeg;
    coord *bend;
    coord *zbeg;
    coord *zend;
    car *cbeg;
    car *cend;
    control();
}

float car::def_dis(const coord &a) //определение расстояния, аргумент - конечная точка
{
  float x=loc.get_x();
  float y=loc.get_y();
  float k=a.get_x();
  float m=a.get_y();
  float p=pow(pow(k-x,2)+pow(m-y,2),2);
  return p;
} 

void car::change(const call &a, const control &ctrl)
{
  if (a.get_cserv()==1) 
  {
    b=a.get_ctype();
    float sp,fl;
    float dis=def_dis(a.get_cloc());  
    switch(b)
    {
      case 1:
        fl=fl1;
        sp=sp1;
        break;
      case 2:
        fl=fl2;
        sp=sp2;
        break;
      case 3:
        fl=fl3;
        sp=sp3;
        break;
    }
    float dis=def_dis(a.get_cloc());
    set_loc(a.get_cloc());
    set_fuel(fuel-dis*fl);
    set_time(time(NULL)+(dis/sp)*3600+1200);
  }
  if (a.get_cserv()==2) 
  {
    b=a.get_ctype();
    float sp,fl;  
    switch(b)
    {
      case 1:        
        fl=fl1;
        sp=sp1;
        break;
      case 2:
        fl=fl2;
        sp=sp2;
        break;
      case 3:
        fl=fl3;
        sp=sp3;
        break;
    }
    float dis1=def_dis(a.get_cloc());
    set_loc(a.get_cloc());
    float dis2=def_dis((&ctrl)->bbeg); //возможно здесь нужно &
    set_loc((&ctrl)->bbeg);
    coord *rex=(&ctrl)->bbeg->next;
    while(rex!=NULL)
    {
      if (dis2>def_dis(*rex))  //тут тоже  
      {
        dis2=def_dis(*rex);  // и тут
        set_loc(*rex);
      }
      rex=rex->next;
    }    
    set_fuel(fuel-dis1*fl-dis2*fl);
    set_time(time(NULL)+(dis1/sp)*3600+(dis2/sp)*3600+300);
  }
  return;
}

void car::refill(const control &ctrl)
{
  float dis;
  coord *min;
  if ((&ctrl)->zbeg==NULL) 
  {
    cout<<"Машина не может заправиться, т.к. нет заправок"<<endl;
    return;
  }
  dis=def_dis((&ctrl)->zbeg);
  coord *rex=(&ctrl)->zbeg->next;
  while(rex!=NULL)
  {
    if (dis>def_dis(*rex))
    {
      dis=def_dis(*rex);
      min=rex;
    }
    rex=rex->next;
  }
  switch(get_type())
    {
      case 1:
        fl=fl1;
        sp=sp1;
        break;
      case 2:
        fl=fl2;
        sp=sp2;
        break;
      case 3:
        fl=fl3;
        sp=sp3;
        break;
    }
  float a=fuel-dis*fl;
  if (a<0)
  {
    set_time(time(NULL)+3600+300);
    set_fuel(tank);
  }
  else 
  {
    set_loc(*min);
    set_fuel(tank);
    set_time(time(NULL)+(dis/sp)*3600+300);
  }
  return;
}
