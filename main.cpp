#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "dataBase.h"
using namespace std;

int main(){
    
    vector<pair<string,string>> parametros;//(clave,valor)
    parametros.push_back(pair<string,string>("id_paciente","int"));
    parametros.push_back(pair<string,string>("nombre","varchar(20)"));
    parametros.push_back(pair<string,string>("edad","int"));
    parametros.push_back(pair<string,string>("telefono","int"));
    parametros.push_back(pair<string,string>("direcion","varchar(50)"));
    vector<string> v1;
    vector<string> v2{"1","Luciana","15","919191","Av. Los Olivos"};
    vector<string> v3{"2","Maria","18","747474","Av. Los Charcos"};
    vector<string> v4{"3","josefa","35","919191","Av. Los Cerros"};


    Database dbms("Hospital");
    dbms.useDatabase("Hospital");
    dbms.createTable("Paciente",parametros);

    dbms.insertIntoTable("Paciente",v1,v2 );
    dbms.insertIntoTable("Paciente",v1,v3 );
    dbms.insertIntoTable("Paciente",v1,v4 );
    return 0;
}
