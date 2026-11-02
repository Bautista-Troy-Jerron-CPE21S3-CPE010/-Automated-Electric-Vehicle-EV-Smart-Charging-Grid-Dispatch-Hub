// Account Billing Table
#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include<iostream>
#include<string>
#include<fstream>

struct TableNode{
    std::string plate_num;
    std::string driver_name;
    double accBalance;
    TableNode* next;
};

class HashTable{
private:
    static const int size = 10;
    TableNode* table[size];

    int hashFunc(const std::string& plate){
        int sum = 0;
        for (int i = 0; i < plate.length(); i++){
    		char c = plate[i];
    		sum += c;
		}
        return sum % size;
    }
    
    void loadHash(){
        std::ifstream file("data/accounts.txt");
        if(!file.is_open()) return;
        std::string plate, name;
        double balance;

        while(file >> plate >> name >> balance){
            int index = hashFunc(plate);
            TableNode* newNode = new TableNode{plate, name, balance, table[index]};
            table[index] = newNode;
        }
        file.close();
    }

public:
    HashTable(){
        for (int i = 0; i < size; ++i){
            table[i] = nullptr;
        }
        loadHash();
    }

    ~HashTable(){
        for (int i = 0; i < size; ++i){
            TableNode* current = table[i];
            while (current){
                TableNode* temp = current;
                current = current->next;
                delete temp;
            }
        }
    }

    void insertAcc(const std::string& plate, const std::string& name, double balance){
        int index = hashFunc(plate);
        TableNode* newNode = new TableNode{plate, name, balance, table[index]};
        table[index] = newNode;
        std::cout << "Account for plate " << plate << " registered.\n";
    }

    bool searchAcc(const std::string& plate, std::string& name, double& balance){
        int index = hashFunc(plate);
        TableNode* current = table[index];
        
        while(current){
            if(current->plate_num == plate){
                name = current->driver_name;
                balance = current->accBalance;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void dispTable(){
        std::cout << "\nDrive Accounts Table\n";
        for(int i = 0; i < size; ++i){
            std::cout << "Bucket " << i << ": ";
            TableNode* current = table[i];
            if(!current){
				std::cout << "Empty";
			}
			
            while(current){
                std::cout << "[" << current->plate_num 
				          << " (" << current->driver_name << "," 
						  << current->accBalance << ")]";
						  
                current = current->next;
            }
            std::cout << "\n";
        }
    }
};
#endif
