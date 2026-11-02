#include <iostream>
#include <string>
#include <vector>
#include "avlTree.h"
#include "circularQueue.h"
#include "hashTable.h"
#include "quickSort.h"
#include "stackArray.h"
#include "vehicularQueue.h"

int main() {
    // System Modules
    AVLTree reserve;
    CircleQ bays(5);
    HashTable bill;
    QuickSort transaction;
    Stack<OperatorAction> opStack(10);
    VehicleQ v_Line;

    int choice = 0;
    std::cout << "\033[1;32m"; // For dark green text color.
    	
    while(choice!=7){ // Separated lines for formatting
        std::cout << "\n" 
		          << "+ - - - - - - - - - - - - - - - - - - - - - +\n" 
		          << "    EV CHARGING STATION MANAGEMENT SYSTEM    \n"
				  << "+ - - - - - - - - - - - - - - - - - - - - - +\n"
				  << "| 1. Vehicle Line                           |\n"
				  << "| 2. Reservation List                       |\n"
				  << "| 3. Available Charging Bays                |\n"
				  << "| 4. Billing Table                          |\n"
				  << "| 5. Transaction List                       |\n"
				  << "| 6. Action Record                          |\n"
				  << "| 7. Exit                                   |\n"
				  << "* - - - - - - - - - - - - - - - - - - - - - *\n"
				  << ">  Enter your choice (1-7): ";	  
        std::cin >> choice;
        std::cout << "\n"
		          << "* - - - - - - - - - - - - - - - - - - - - - *\n";

        switch(choice){
            case 1:{
                int one;
                std::cout << "\n"
				          << "v - - - Vehicle Line - - - v\n"
						  << "| 1. Enqueue Vehicle       |\n"
						  << "| 2. Dispatch Next Vehicle |\n"
						  << "| 3. Display Queues        |\n"
						  << "*--------------------------*\n"
						  << "> Enter choice: ";
				std::cin >> one;
				std::cout << "*--------------------------*\n";
                

                if(one == 1){
                    std::string plate, type;
                    int batt;
                    std::cout << "\n"
                              << "*--------------------------------------------------*\n"
					          << "> Enter Plate Number: ";
                    std::cin >> plate;
                    
                    std::cout << "> Enter Type [Priority(P/p) | Regular(R/r)]: ";
                    std::cin >> type;
                    
                    std::cout << "> Enter Battery % (0-100): ";
                    std::cin >> batt;
                    std::cout << "*--------------------------------------------------*\n";
                    v_Line.enqueue(plate, type, batt);
                }
				else if(one == 2){
                    std::string plate, type;
                    int batt;
                    
                    if(v_Line.getNextV(plate, type, batt)){
                        std::cout << "*---------------------------------------------------------------------*\n"
						          << "Dispatched Vehicle -> Plate: " << plate 
								  << ", Type: " << type 
								  << ", Battery: " << batt << "%\n"
								  << "*---------------------------------------------------------------------*\n";
                    }
					else{
                        std::cout << "*-----------------------------*\n"
						          << "No vehicles waiting in queues.\n"
						          << "*-----------------------------*\n";
                    }
                }
				else if(one == 3){
					std::cout << "*---------------------------------------------------------------------*\n";
                    v_Line.dispQs();
                    std::cout << "*---------------------------------------------------------------------*\n";
                }
				else{
                    std::cout << "*--------------*\n"
					          << "Invalid option.\n"
					          << "*--------------*\n";
                }
                break;
            }
			case 2:{
			    int two;
			    std::cout << "\n"
			              << "v - - - Reservation List - - - v\n"
			              << "| 1. Book Reservation          |\n"
			              << "| 2. Search Reservation ID     |\n"
			              << "| 3. Display All Reservations  |\n"
			              << "*------------------------------*\n"
			              << "> Enter choice: ";
			    std::cin >> two;
			    std::cout << "*------------------------------*\n";
			
			    if(two == 1){
			        int id;
			        std::string name, slot;
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Enter Reservation ID: ";
			        std::cin >> id;
			        std::cout << "> Enter Driver Name: ";
			        std::cin >> name;
			        std::cout << "> Enter Time Slot: ";
			        std::cin >> slot;
			        std::cout << "*------------------------------------------*\n";
			        reserve.insertRes(id, name, slot);
			    }
			    else if(two == 2){
			        int id;
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Enter Reservation ID to search: ";
			        std::cin >> id;
			        std::cout << "*------------------------------------------*\n";
			        reserve.searchRes(id);
			    }
			    else if(two == 3){
			        std::cout << "\n"
			                  << "*------------------------------------------*\n";
			        reserve.dispRes();
			        std::cout << "*------------------------------------------*\n";
			    }
			    else{
			        std::cout << "*--------------*\n"
			                  << "Invalid option.\n"
			                  << "*--------------*\n";
			    }
			    break;
			}
			
            case 3:{
			    int three;
			    std::cout << "\n"
			              << "v - - - Charging Bays - - - v\n"
			              << "| 1. Assign Vehicle to Bay  |\n"
			              << "| 2. Rotate Grid Power Pulse|\n"
			              << "| 3. Display Bays Status    |\n"
			              << "*----------------------------*\n"
			              << "> Enter choice: ";
			    std::cin >> three;
			    std::cout << "*----------------------------*\n";
			
			    if(three == 1){
			        int bayId;
			        std::string plate;
			        double power;
			
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Enter Bay ID(1-5): ";
			        std::cin >> bayId;
			        std::cout << "> Enter Vehicle Plate: ";
			        std::cin >> plate;
			        std::cout << "> Enter Power Allocation(kW): ";
			        std::cin >> power;
			        std::cout << "*------------------------------------------*\n";
			
			        if(bays.assign(bayId, plate, power)){
			            std::cout << "Bay " << bayId << " assigned successfully.\n";
			        }
			        else{
			            std::cout << "Invalid Bay ID (1-5).\n";
			        }
			    }
			    else if(three == 2){
			        bays.rotateGrid();
			    }
			    else if(three == 3){
			        std::cout << "\n"
			                  << "*------------------------------------------*\n";
			        bays.dispBays();
			        std::cout << "*------------------------------------------*\n";
			    }
			    else{
			        std::cout << "*--------------*\n"
			                  << "Invalid option.\n"
			                  << "*--------------*\n";
			    }
			    break;
			}
			
            case 4:{
			    int four;
			    std::cout << "\n"
			              << "v - - - Account Billing - - - v\n"
			              << "| 1. Register New Account     |\n"
			              << "| 2. Search Account by Plate  |\n"
			              << "| 3. Display All Accounts     |\n"
			              << "*-----------------------------*\n"
			              << "> Enter choice: ";
			    std::cin >> four;
			    std::cout << "*-----------------------------*\n";
			
			    if(four == 1){
			        std::string plate, name;
			        double balance;
			
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Enter Plate Number: ";
			        std::cin >> plate;
			        std::cout << "> Enter Driver Name: ";
			        std::cin >> name;
			        std::cout << "> Enter Account Balance: ";
			        std::cin >> balance;
			        std::cout << "*------------------------------------------*\n";
			
			        bill.insertAcc(plate, name, balance);
			    }
			    else if(four == 2){
			        std::string plate, name;
			        double balance;
			
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Enter Plate Number to search: ";
			        std::cin >> plate;
			        std::cout << "*------------------------------------------*\n";
			
			        if(bill.searchAcc(plate, name, balance)){
			            std::cout << "Account Found -> Name: " << name << ", Balance: " << balance << "\n";
			        }
			        else{
			            std::cout << "Account with plate " << plate << " not found.\n";
			        }
			    }
			    else if(four == 3){
			        std::cout << "\n"
			                  << "*------------------------------------------*\n";
			        bill.dispTable();
			        std::cout << "*------------------------------------------*\n";
			    }
			    else{
			        std::cout << "*--------------*\n"
			                  << "Invalid option.\n"
			                  << "*--------------*\n";
			    }
			    break;
			}
			
            case 5:{
			    std::cout << "\nv - - - Transaction Sorter - - - v\n";
			
			    std::vector<Trans> transactions = {};
			
			    std::cout << "\n"
			              << "*------------------------------------------*\n"
			              << "> Unsorted Transactions:\n";
			
			    for(const auto& t : transactions){
			        std::cout << " | Plate: " << t.plate_num
			                  << " | kWh: " << t.kWh_used
			                  << " | Total: " << t.total << "\n";
			    }
			
			    transaction.sortTrans(transactions);
			
			    std::cout << "\n> Sorted Transactions by kWh:\n";
			
			    for(const auto& t : transactions){
			        std::cout << " | Plate: " << t.plate_num
			                  << " | kWh: " << t.kWh_used
			                  << " | Total: " << t.total << "\n";
			    }
			
			    std::cout << "*------------------------------------------*\n";
			    break;
			}
			
            case 6:{
			    int six;
			    std::cout << "\n"
			              << "v - - - Operator Action Recorder - - - v\n"
			              << "| 1. Record Operator Action             |\n"
			              << "| 2. Undo Last Action                   |\n"
			              << "| 3. Display Recorded Actions           |\n"
			              << "*---------------------------------------*\n"
			              << "> Enter choice: ";
			    std::cin >> six;
			    std::cout << "*---------------------------------------*\n";
			
			    if(six == 1){
			        int six_if, bayId;
			        std::string plate;
			        double kWh;
			
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Action Type (0: Terminate, 1: Station Locked): ";
			        std::cin >> six_if;
			        std::cout << "> Enter Bay ID: ";
			        std::cin >> bayId;
			
			        OperatorAction act;
			        act.bayId = bayId;
			
			        if(six_if == 0){
			            act.type = ActionType::SESSION_TERMINATED;
			            std::cout << "> Enter Vehicle Plate: ";
			            std::cin >> plate;
			            act.vehiclePlate = plate;
			            std::cout << "> Enter kWh Delivered: ";
			            std::cin >> kWh;
			            act.kWhDelivered = kWh;
			        }
			        else{
			            act.type = ActionType::STATION_LOCKED;
			        }
			
			        std::cout << "*------------------------------------------*\n";
			        opStack.push(act);
			        std::cout << "Action recorded successfully.\n";
			    }
			    else if(six == 2){
			        std::cout << "\n"
			                  << "*------------------------------------------*\n";
			        OperatorAction undone = opStack.pop();
			        std::cout << "Deleted Action: " << undone << "\n"
			                  << "*------------------------------------------*\n";
			    }
			    else if(six == 3){
			        std::cout << "\n"
			                  << "*------------------------------------------*\n"
			                  << "> Recorded Actions:\n";
			        opStack.display(std::cout);
			        std::cout << "*------------------------------------------*\n";
			    }
			    else{
			        std::cout << "*--------------*\n"
			                  << "Invalid option.\n"
			                  << "*--------------*\n";
			    }
			    break;
			}
			
            case 7:
                std::cout << "System Exited\n";
                break;
                
            default:
                std::cout << "Invalid choice. Between 1 and 7 only.\n";
        }
    }
    return 0;
}
