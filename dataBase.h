#ifndef _DATABASE_H_
#define _DATABASE_H_
 
#include <string>
#include <vector>
#include <utility>
#include <fstream>
class Database{
    private:
    std::string databaseName;
    public:
        bool existeTabla(std::string nombre);//verificamos si una tabla esta en la base
        Database(std::string name);
        void useDatabase(std::string name);//
        void createTable(std::string name);
        void createTable(std::string name,std::vector<std::pair<std::string,std::string>> parametros);
        void addColumnTable(std::string nameTable,std::string nameColumn,std::string typeColumn);
        void alterTable();
        //formato Guardado
        //header
        void insertIntoTable(std::string tableName, std::vector<std::string> parameters, std::vector<std::string> values);
        void selectTable(std::string tableName);
};
bool Database::existeTabla(std::string nombre){
    std::ifstream archivo(nombre.c_str());
    return archivo.good();
}
Database::Database(std::string name){
    std::ofstream newfile;
    name+="_directory.txt";
    newfile.open(name,std::ios::app);
}
void Database::useDatabase(std::string name){
    this->databaseName=name;
}
void Database::createTable(std::string name){
    std::ofstream newfile;
    name+=".csv";
    newfile.open(name,std::ios::app);
}
void Database::createTable(std::string name,std::vector<std::pair<std::string,std::string>> parametros){
    //creacion archivo csv
    std::fstream file;
    file.open(name+".csv",std::ios::out);
    file.close();
           
    //añadir al directorio
    file.open(databaseName+"_directory.txt",std::ios::in);
    std::string tmp;
    std::string text="";
    while(getline(file,tmp)){
        text+=(tmp+"\n");
    }
    text+=("Table Name "+name+"\n");
    for(int i=0;i<parametros.size();i++){
        text+=(parametros[i].first+" " +parametros[i].second+"\n");
    }
    file.close();
    file.open(databaseName+"_directory.txt",std::ios::out);
    file<<text;
    file.close();
}
void Database::addColumnTable(std::string nameTable,std::string nameColumn,std::string typeColumn){
             
}
void Database::alterTable(){
 
}
//formato Guardado
//header
void Database::insertIntoTable(std::string tableName, std::vector<std::string> parameters, std::vector<std::string> values){
    std::fstream file;
 
    if(existeTabla(tableName+".csv")){
        //Accedemos a la tabla para insertar datos
        file.open(tableName+".csv",std::ios::in);
        std::string tmp;
        std::string text="";
        while(getline(file,tmp)){
            text+=tmp+'\n';
        }
        text+="header";
        for(int i=0;i<values.size();i++){
            text+=","+values[i];
        }
        file.close();
        file.open(tableName+".csv",std::ios::out);
        file<<text;
        file.close();
    }
    else{
        std::cout<<"La tabla -> "+tableName+" no existe"<<std::endl;
    }
           
}
void Database::selectTable(std::string tableName){
           
}
#endif

