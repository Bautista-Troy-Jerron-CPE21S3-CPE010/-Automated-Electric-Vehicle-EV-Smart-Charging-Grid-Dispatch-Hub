// Transaction Sorter
#ifndef QUICK_SORT_H
#define QUICK_SORT_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

struct Trans{
    std::string plate_num;
    double kWh_used;
    double total;
};

class QuickSort{
private:
    int partition(std::vector<Trans>& arr, int low, int high){
        double pivot = arr[high].kWh_used;
        int i = (low-1);

        for (int j = low; j <= high-1; j++){
            if (arr[j].kWh_used < pivot){
                i++;
                Trans temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
        Trans temp = arr[i+1];
        arr[i+1] = arr[high];
        arr[high] = temp;

        return (i+1);
    }

    void quickSort(std::vector<Trans>& arr, int low, int high){
        if (low < high){
            int piv = partition(arr, low, high);
            quickSort(arr, low, piv-1);
            quickSort(arr, piv+1, high);
        }
    }

    void loadQuick(std::vector<Trans>& arr){
        std::ifstream file("data/transactions.txt");
        if(!file.is_open()) return;
        Trans transaction;

        while(file >> transaction.plate_num >> transaction.kWh_used >> transaction.total){
            arr.push_back(transaction);
        }
        file.close();
    }
    
    void saveQuick(const std::vector<Trans>& arr){
        std::ofstream file("data/transactions.txt");
        if(!file.is_open()){
            std::cout << "Error saving transactions.\n";
            return;
        }
        
        for(const Trans& transaction : arr){
            file << transaction.plate_num << " " << transaction.kWh_used << " " << transaction.total << "\n";
        }
        file.close();
    }

public:
    void loadTrans(std::vector<Trans>& arr){
        loadQuick(arr);
    }
    
    void saveTrans(const std::vector<Trans>& arr){
        saveQuick(arr);
    }

    void sortTrans(std::vector<Trans>& arr){
        if (!arr.empty()){
            quickSort(arr, 0, arr.size()-1);
        }
    }
};

#endif
