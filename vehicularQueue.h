// Priority and Regular Vehicular Dual Separated Queues
#ifndef VEHICULAR_QUEUE_H
#define VEHICULAR_QUEUE_H
#include <iostream>
#include <string>
#include <fstream>

struct QNode{
    std::string plate_num;
    std::string v_Type; // Priority or Regular only (P/p or R/r)
    int battPercent;
    QNode* next;
};

class VehicleQ{
private:
    QNode* p_Front;
    QNode* p_Rear;
    QNode* r_Front;
    QNode* r_Rear;

    void loadV_Q(){
        std::ifstream file("data/vehicles.txt");

        if(!file.is_open()) return;
        std::string plate, type;
        int batt;

        while(file >> plate >> type >> batt){

            QNode* newNode = new QNode{
                plate, type, batt, nullptr
            };

            if(type == "P" || type == "p"){
                if(!p_Rear){
                    p_Front = newNode;
                    p_Rear = newNode;
                }
                else{
                    p_Rear->next = newNode;
                    p_Rear = newNode;
                }
            }
            else if(type == "R" || type == "r"){
                if(!r_Rear){
                    r_Front = newNode;
                    r_Rear = newNode;
                }
                else{
                    r_Rear->next = newNode;
                    r_Rear = newNode;
                }
            }
            else{
                delete newNode;
            }
        }
        file.close();
    }
    
    void saveV_Q(){
        std::ofstream file("data/vehicles.txt");

        if(!file.is_open()){
            std::cout << "Error saving vehicle queues.\n";
            return;
        }
        
        QNode* current = p_Front;

        while(current){
            file << current->plate_num << " "
                 << current->v_Type << " "
                 << current->battPercent << "\n";
            current = current->next;
        }
        current = r_Front;

        while(current){
            file << current->plate_num << " "
                 << current->v_Type << " "
                 << current->battPercent << "\n";
            current = current->next;
        }
        file.close();
    }
    
public:
    VehicleQ(){
        p_Front = nullptr;
        p_Rear = nullptr;
        r_Front = nullptr;
        r_Rear = nullptr;
        loadV_Q();
    }
    
    ~VehicleQ(){
        while(p_Front){
            QNode* temp = p_Front;
            p_Front = p_Front->next;
            delete temp;
        }

        while(r_Front){
            QNode* temp = r_Front;
            r_Front = r_Front->next;
            delete temp;
        }
    }

    void enqueue(const std::string& plate, const std::string& type, int batt){
        if (plate.empty()){
            std::cout << "Plate number can't be empty.\n";
            return;
        }

        if (batt < 0 || batt > 100){
            std::cout << "Battery % must be 0-100.\n";
            return;
        }

        if(type != "P" && type != "p" &&
           type != "R" && type != "r"){
            std::cout << "Invalid vehicle type. Use P/p or R/r.\n";
            return;
        }

        QNode* newNode = new QNode{plate, type, batt, nullptr};

        if(type == "P" || type == "p"){
            if(!p_Rear){
                p_Front = newNode;
                p_Rear = newNode;
            }
            else{
                p_Rear->next = newNode;
                p_Rear = newNode;
            }
            std::cout << "Emergency vehicle " << plate
                      << " added to priority queue.\n";
        }
        else if(type == "R" || type == "r"){
            if(!r_Rear){
                r_Front = newNode;
                r_Rear = newNode;
            }
            else{
                r_Rear->next = newNode;
                r_Rear = newNode;
            }
            std::cout << "Regular vehicle " << plate
                      << " added to regular queue.\n";
        }
        saveV_Q();
    }

    bool getNextV(std::string& plate, std::string& type, int& batt){
        if (p_Front){
            QNode* temp = p_Front;
            plate = temp->plate_num;
            type = temp->v_Type;
            batt = temp->battPercent;
            p_Front = p_Front->next;

            if(!p_Front){
                p_Rear = nullptr;
            }
            delete temp;
            saveV_Q();
            return true;
        }
        else if(r_Front){
            QNode* temp = r_Front;
            plate = temp->plate_num;
            type = temp->v_Type;
            batt = temp->battPercent;
            r_Front = r_Front->next;

            if(!r_Front){
                r_Rear = nullptr;
            }
            delete temp;
            saveV_Q();
            return true;
        }
        return false;
    }
    
    void dispQs()const{
        std::cout << "\nPriority Queue\n";
        if(!p_Front){
            std::cout << "No emergency vehicles waiting.\n";
        }
        else{
            QNode* current = p_Front;
            while(current){
                std::cout << " | Plate: " << current->plate_num
                          << " | Battery: " << current->battPercent << "%\n";

                current = current->next;
            }
        }
        std::cout << "\nRegular Queue\n";

        if(!r_Front){
            std::cout << "No regular vehicles waiting.\n";
        }
        else{
            QNode* current = r_Front;
            while(current){
                std::cout << " | Plate: " << current->plate_num
                          << " | Battery: " << current->battPercent << "%\n";

                current = current->next;
            }
        }
    }
};
#endif
