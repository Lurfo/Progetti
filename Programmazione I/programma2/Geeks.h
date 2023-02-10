#ifndef GEEKS_H
#define GEEKS_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <list>

using std::string;
using std::vector;
using std::list;
using std::cin;
using std::cout;

class Geeks; 
class Projects;


class Geeks
{
    friend class Projects;

    public:
    
    Geeks(string id, double h_s, int h) : 
    id_geek{id} , hour_salary{h_s} , orePerProgetto{h}
    {
        //empty body
    }

    virtual string toString()
    {
        std::ostringstream out;
        out<<" Id_geek: "<<"\n";
        out<<id_geek<<"\n";
        out<<" Hour_salary: "<<"\n";
        out<<hour_salary<<"\n";
       
        out<<"Il programmatore attualmente e' impegnato in: "<<list_of_projects.size()<< " progetti "<<"\n";
        return out.str();
    }
    
     void addProject(Projects& P)
    {
        list_of_projects.push_front(&P);
    }
   
    void weekly_worked_hours()
    {
        int weeklyHours=2;
        orePerProgetto=orePerProgetto+weeklyHours;
        cout<<"Nuove ore progetto: "<<orePerProgetto<<"\n";
        double total_Salary=orePerProgetto*hour_salary;

        cout<<"Lo stipendio totale del programmatore ora e': "<<total_Salary<<"\n";
        cout<<"Azzero numero di ore. . ."<<"\n";
        cout<<orePerProgetto*0<<"\n";
    }
    

        int orePerProgetto;
        string id_geek;
    

     private:
    
     double hour_salary;
     
     list<Projects*> list_of_projects;
};

class Projects
{
    friend class Geeks;
   
    public:
    
    Projects(int id_p , string p_n , double t_a,int gg, int m, int a ) :
    id_project{id_p} , project_name{p_n} , total_amout{t_a}, giorno{gg}, mese{m} , anno{a} 
    {
        //empty body
    }

     bool operator<(const Projects& P)
    {
        if(giorno == P.giorno)
        return giorno<P.giorno;
        return anno < P.anno;
        return mese < P.mese;
    }



    virtual string toString()
    {
        std::ostringstream out;
        out<<" Id_project: "<<"\n";
        out<<id_project<<"\n";
        out<<" Project_name: "<<"\n";
        out<<project_name<<"\n";
        out<<" Total_amount: "<<"\n";
        out<<total_amout<<"\n";
        out<<" Delivery_date: "<<"\n";
        out<<giorno << "/" << mese << "/ "<< anno <<"\n";
        out<<"Programmatori impegnati nel progetto: "<<list_of_geeks.size()<<"\n";


        return out.str();
    }
    
    void addGeeks(Geeks& G)
    {
        list_of_geeks.push_front(&G);
    }
    

    void assign_geek(Projects& P, Geeks& G){

        cout<<"Il progetto " << P.id_project << " e' assegnato a "<<G.id_geek<<"\n";
        P.addGeeks(G);
        G.addProject(P);

        cout<<"Aggiornamento. . ."<<"\n";
        cout<<"Il progetto e' sviluppato da "<<list_of_geeks.size()<<" programmator* "<<"\n";

        cout<<" Ore dedicate al progetto: "<<G.orePerProgetto<<"\n";

        cout<<"Aggiungo le ''weekly hours'' . . ."<<"\n";
        G.weekly_worked_hours();

    }
    
    
    
    
    private:
    int id_project; //lo interpreto come: 1011.. codice tipo per questo int
    string project_name;
    double total_amout;
    int giorno;
    int mese; //per il delivery date
    int anno; //per il delivery date
    list<Geeks*> list_of_geeks;

};


#endif
