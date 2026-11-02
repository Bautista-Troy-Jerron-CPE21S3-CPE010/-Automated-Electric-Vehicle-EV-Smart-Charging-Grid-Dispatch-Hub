// Action Recorder Stack
#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>

//Kinds of actions an operator can perform
enum class ActionType {
    SESSION_TERMINATED,
    STATION_LOCKED
};

//One recorded operator action
struct OperatorAction {
    ActionType type = ActionType::SESSION_TERMINATED;
    int bayId = 0;
    std::string vehiclePlate;
    double kWhDelivered = 0.0;
};

//Prints an action in a readable one-line format
inline std::ostream& operator<<(std::ostream& os, const OperatorAction& a) {
    switch (a.type) {
        case ActionType::SESSION_TERMINATED:
            os << " | Session terminated | Bay " << a.bayId
               << " | " << a.vehiclePlate
               << " | " << a.kWhDelivered << " kWh";
            break;
        case ActionType::STATION_LOCKED:
            os << "Station locked | Bay " << a.bayId;
            break;
    }
    return os;
}

//Array-based stack (LIFO) that doubles its capacity when full
template <typename T>
class Stack{
private:
    T* data; //dynamic array holding the items
    std::size_t capacity; //current array size
    std::size_t count; //number of items stored

    void loadStack(){
	    std::ifstream file("data/operator_actions.txt");

	    if (!file.is_open()) return;
	
	    int type, bay;
	    std::string plate;
	    double kWh;
	
	    while(file >> type >> bay >> plate >> kWh){
	        if(type < 0 || type > 1){
	            continue;
	        }
	
	        if(count == capacity){
	            std::size_t newCapacity = capacity * 2;
	            T* bigger = new T[newCapacity];
	
	            for(std::size_t i = 0; i < count; ++i){
	                bigger[i] = data[i];
	            }
	
	            delete[] data;
	            data = bigger;
	            capacity = newCapacity;
	        }
	        OperatorAction action;
			action.type = static_cast<ActionType>(type);
			action.bayId = bay;
			action.vehiclePlate = plate;
			action.kWhDelivered = kWh;
			data[count] = action;
	        ++count;
	    }
	    file.close();
	}
    
    void saveStack(){
        std::ofstream file("data/operator_actions.txt");

        if(!file.is_open()){
            std::cout << "Error saving operator actions.\n";
            return;
        }

        for(std::size_t i = 0; i < count; ++i){
            file << static_cast<int>(data[i].type) << " "
                 << data[i].bayId << " "
                 << data[i].vehiclePlate << " "
                 << data[i].kWhDelivered << "\n";
        }
        file.close();
    }
    
public:
    explicit Stack(std::size_t initialCapacity = 10)
        : data(nullptr), capacity(initialCapacity ? initialCapacity : 1), count(0) {
        data = new T[capacity];
        loadStack();
    }

    //Copying is disabled to avoid double deleting the array
    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    //Frees the array
    ~Stack(){
        delete[] data;
    }

    //True if nothing is stored
    bool isEmpty()const{
        return count == 0;
    }

    //Number of stored items
    std::size_t size()const{
        return count;
    }

    void push(const T& value){
        if(count == capacity){
            std::size_t newCapacity = capacity * 2;
            T* bigger = new T[newCapacity];

            for(std::size_t i = 0; i < count; ++i){
                bigger[i] = data[i];
            }
            delete[] data;
            data = bigger;
            capacity = newCapacity;
        }
        data[count] = value;
        ++count;
        saveStack();
    }

    T pop(){
        if(count == 0){
            throw std::underflow_error("Stack Underflow: nothing to undo");
        }
        T value = data[--count];
        saveStack();
        return value;
    }

    //Returns the top item without removing it (modifiable)
    T& peek(){
        if(count == 0){
            throw std::underflow_error("Stack is empty: no recent action");
        }
        return data[count - 1];
    }

    //Returns the top item without removing it (read-only, for const stacks)
    const T& peek()const{
        if(count == 0){
            throw std::underflow_error("Stack is empty: no recent action");
        }
        return data[count - 1];
    }

    //Prints items from newest to oldest, numbered
    void display(std::ostream& os = std::cout)const{
        if(count == 0){
            os << "  (no operator actions recorded)\n";
            return;
        }
        int n = 1;
        for(std::size_t i = count; i > 0; --i){
            os << "  " << n++ << ". " << data[i - 1] << "\n";
        }
    }
};

#endif
