// Charging Bays & Power Dispatch Dual Queues
#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H
#include <iostream>
#include <string>
#include <fstream>

struct Charging{
    int bay_id;
    std::string v_plate;
    double power_Kw;
    bool isActive;
};

class CircleQ{
private:
    int cap;
    int front;
    int rear;
    int size;
    Charging* bays;

    void loadCircleQ(){
        std::ifstream file("data/charging_bays.txt");
        if(!file.is_open()) return;

        int id;
        std::string plate;
        double power;
        bool active;
        size = 0;

        while(file >> id >> plate >> power >> active){
            if(id >= 1 && id <= cap){
                int x = id - 1;
                bays[x].v_plate = plate;
                bays[x].power_Kw = power;
                bays[x].isActive = active;
                if(active){
                    size++;
                }
            }
        }
        file.close();
    }

    void saveCircleQ(){
        std::ofstream file("data/charging_bays.txt");
        if(!file.is_open()){
            std::cout << "Error saving charging bay records.\n";
            return;
        }

        for(int i = 0; i < cap; ++i){
            file << bays[i].bay_id << " "
                 << bays[i].v_plate << " "
                 << bays[i].power_Kw << " "
                 << bays[i].isActive << "\n";
        }

        file.close();
    }

public:
    CircleQ(int n = 5){
        cap = n;
        front = 0;
        rear = -1;
        size = 0;
        bays = new Charging[cap];

        for (int i = 0; i < cap; ++i) {
            bays[i] = {i + 1, "Empty", 0.0, false};
        }
        loadCircleQ();
    }

    ~CircleQ(){
        delete[] bays;
    }

    bool isFull()const{
        return size == cap;
    }

    bool isEmpty()const{
        return size == 0;
    }

    bool assign(int bay_id, const std::string& plate, double power){
        if (bay_id < 1 || bay_id > cap) return false;

        int x = bay_id - 1;

        if(!bays[x].isActive){
            size++;
        }

        bays[x].v_plate = plate;
        bays[x].power_Kw = power;
        bays[x].isActive = true;

        saveCircleQ();

        return true;
    }

    void rotateGrid(){
        std::cout << "\nRotating power grid pulses across active bays.\n";
        for(int i = 0; i < cap; ++i){
            if(bays[i].isActive){
                bays[i].power_Kw += 5.0;

                if(bays[i].power_Kw > 50.0){
                    bays[i].power_Kw = 25.0;
                }

                std::cout << "Bay " << bays[i].bay_id << "\n"
                          << "Plate: " << bays[i].v_plate << "\n"
                          << "Active Power Allocation: " << bays[i].power_Kw << " kW\n";
            }
            else{
                std::cout << "Bay " << bays[i].bay_id << " is available.\n";
            }
        }

        saveCircleQ();
    }
    
    void dispBays()const{
        std::string stat;
        std::cout << "\nCharging Bay Power Status:\n";

        for (int i = 0; i < cap; ++i){
            if (bays[i].isActive){
                stat = "Occupied";
            }
            else{
                stat = "Available";
            }

            std::cout << " | Bay " << bays[i].bay_id
                      << " | Status: " << stat
                      << " | Plate: " << bays[i].v_plate
                      << " | Power: " << bays[i].power_Kw << " kW\n";
        }
    }

    void dispAvailable() const{
        int availCount = cap - size;

        std::cout << std::endl;
        std::cout << "Available slots: " << availCount << std::endl;

        if (isFull()){
            std::cout << "All bays are occupied." << std::endl;
            std::cout << "Please find another station." << std::endl;
            return;
        }
    }
};

#endif
