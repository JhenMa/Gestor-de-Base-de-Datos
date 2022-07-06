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
        Database(std::string name){
            std::ofstream newfile;
            name+="_directory.txt";
            newfile.open(name,std::ios::app);
        };
        void useDatabase(std::string name){
            this->databaseName=name;
        }
        void createTable(std::string name){
            std::ofstream newfile;
            name+=".csv";
            newfile.open(name,std::ios::app);
        }
        void createTable(std::string name,std::vector<std::pair<std::string,std::string>> parametros){
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
        void addColumnTable(std::string nameTable,std::string nameColumn,std::string typeColumn){
            
        }
        void alterTable(){

        }
        //formato Guardado
        //header
        void insertIntoTable(std::string tableName, std::vector<std::string> parameters, std::vector<std::string> values){
            std::fstream file;
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
        void selectTable(std::string tableName){
            
        }
};
#endif