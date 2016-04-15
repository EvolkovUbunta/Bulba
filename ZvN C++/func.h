#include <cstring>
using namespace std;
class control;

class pla
{
  private:
    string name; // название планеты 
    float roz; // расстояние от звезды (в млн. км.)
    float pvvo; // период вращения вокруг оси (в земных сутках)
    float rad; // радиус планеты (в км.) 
    float srpl; // средняя плотность (в кг/м^3)
    string nstr; // имя звезды, к которой принадлежит планета 
    string nsoz; // имя созвездия, к которому принадлежит планета 
    string ngal; // имя галактики, к которой принадлежит планета 
  public:
    pla *next;
    string giv_name();
    float giv_roz();
    float giv_pvvo();
    float giv_rad();
    float giv_srpl();
    string giv_nstr();
    string giv_nsoz();
    string giv_ngal();
    void show_info();
    int get_info(control &ctrl);
    void get_file(string pl_name,float pl_roz,float pl_pvvo,float pl_rad,float pl_srpl,string pl_nstr,string pl_nsoz,string pl_ngal);
};

class sta
{
  private:
    string name; // название звезды
    string spkl; // спектральный класс
    string cvet; // видимый цвет звезды
    float temp; // температура звезды в млн. градусов Фаренгейта
    float mass; // масса звезды в эквиваленте масс Солнца
    float zvvl; // звездная величина ^m
    float razm; // размеры звезды в радиусах солнца
    string nsoz; // имя созвездия, к которому принадлежит звездa
    string ngal; // имя галактики, к которой принадлежит звезда
  public:
    sta *next;
    string giv_name();
    string giv_spkl();
    string giv_cvet();
    float giv_temp();
    float giv_mass();
    float giv_zvvl();
    float giv_razm();
    string giv_nsoz();
    string giv_ngal();
    void show_info();
    int get_info(control &ctrl);
    void get_file(string st_name,string st_spkl, string st_cvet,float st_temp,float st_mass,float st_zvvl,float st_razm,string st_nsoz,string st_ngal);
};

class soz
{
  private:
    string name; // название созвездия 
    string lnaz; // латинское название 
    float plos; // площадь cозвездия в квадратных градусах 
    int chzv; // число звезд ярче 6.0^m
    string sokr; // сокращение лат. названия
    string ngal; // имя галактики, к которой принадлежит созвездие
  public:
    soz *next;
    string giv_name();
    string giv_lnaz();
    float giv_plos();
    int giv_chzv();
    string giv_sokr();
    string giv_ngal();
    void show_info();
    int get_info(control &ctrl);
    void get_file(string so_name,string so_lnaz,float so_plos,int so_chzv,string so_sokr,string so_ngal);
};

class gal
{
  private:
    string name; // название галактики 
    string vgal; // вид галактики 
    float diam; // диаметр галактики в световых годах 
    float mass; // масса галактики в эквиваленте масс Солнца *10^12 
    float ktm; // кол-во черной материи в процентах 
  public:
    gal *next;
    string giv_name();
    string giv_vgal();
    float giv_diam();
    float giv_mass();
    float giv_ktm();
    void show_info();
    int get_info();
    void get_file(string ga_name,string ga_vgal,float ga_diam,float ga_mass,float ga_ktm);
}; 

class control
{
  public:
      gal *gal_beg;
      gal *gal_end;
      soz *soz_beg;
      soz *soz_end;
      sta *sta_beg;
      sta *sta_end;
      pla *pla_beg;
      pla *pla_end;
      control();
};
    
int input_gala(control *ctrl);
int input_sozv(control *ctrl);
int input_star(control *ctrl);
int input_plan(control *ctrl);
int find_gala(const control &ctrl);
int find_sozv(const control &ctrl);
int find_star(const control &ctrl);
int find_plan(const control &ctrl);
int delete_gala(control *ctrl);
int delete_star(control *ctrl);
int delete_sozv(control *ctrl);
int delete_plan(control *ctrl);
int save_base(const control &ctrl,char* file1,char* file2,char* file3,char* file4);
int load_base(control *ctrl,char* file1,char* file2,char* file3,char* file4);
int print_base(const control &ctrl);