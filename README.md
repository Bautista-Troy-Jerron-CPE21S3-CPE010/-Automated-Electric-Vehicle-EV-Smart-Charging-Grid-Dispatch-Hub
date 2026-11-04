# Automated Electric Vehicle (EV) Smart Charging & Grid Dispatch Hub
A C++ console program that simulates how an EV charging station runs: serving emergency vehicles first, sharing power across charging bays, booking reservations, looking up driver accounts, and letting operators undo their last recorded action.

Final project for **CPE010 (Data Structures and Algorithms)**, Technological Institute of the Philippines, Quezon City.

---
## Features and Data Structures
| Menu | Feature | Data Structure / Algorithm |
|:---:|---|---|
| 1 | Vehicle Line (emergency vehicles served first) | Two linked-list queues (priority and regular) |
| 2 | Reservation List | AVL tree |
| 3 | Charging Bays (power allocation and rotation) | Circular queue (array-based) |
| 4 | Account Billing (lookup by plate number) | Hash table with chaining |
| 5 | Transaction Sorter (sort by kWh) | Quick sort |
| 6 | Operator Action Recorder (record and undo) | Stack (array-based) |
| 7 | Exit | - |

---
## Poject Files
| File | Contents |
|---|---|
| `main.cpp` | Main menu and program flow |
| `circularQueue.h` | Charging bays and power rotation |
| `vehicularQueue.h` | Priority and regular vehicle queues |
| `avlTree.h` | Reservation AVL tree |
| `hashTable.h` | Driver account hash table |
| `stackArray.h` | Operator action stack |
| `quickSort.h` | Transaction sorting |
| `data/` | Text files where the program saves and loads its records |

---
## How to Compile and Run
You need a C++ compiler such as g++ with C++17 support. All code is in header files, so only `main.cpp` is compiled.
```
g++ -std=c++17 -O2 main.cpp -o ev
```

Run it **from the project folder**, so the program can find the `data/` folder:
- **Windows:** `ev.exe`
- **Linux / macOS:** `./ev`

---
## Sample Input
Type each value on its own line. Do not use spaces in names or time slots (for example, use `08:00-09:00`).

| Task | Input (menu, sub-menu, values) |
|---|---|
| Add a regular vehicle | `1`, `1`, `REG001`, `R`, `60` |
| Add an emergency vehicle | `1`, `1`, `PRI001`, `P`, `15` |
| Display queues | `1`, `3` |
| Dispatch next vehicle | `1`, `2` |
| Book a reservation | `2`, `1`, `30`, `Ana`, `08:00-09:00` |
| Search a reservation | `2`, `2`, `30` |
| Display all reservations | `2`, `3` |
| Assign a bay | `3`, `1`, `1`, `ABC123`, `22` |
| Rotate grid power | `3`, `2` |
| Display bays | `3`, `3` |
| Register an account | `4`, `1`, `ABC123`, `Juan`, `500` |
| Search an account | `4`, `2`, `ABC123` |
| Display accounts | `4`, `3` |
| Sort transactions | `5` |
| Record an action | `6`, `1`, `0`, `1`, `ABC123`, `12.5` |
| Undo the last action | `6`, `2` |
| Display actions | `6`, `3` |
| Exit | `7` |

Option 5 reads `data/transactions.txt`, with one record per line as `plate kWh total`:
```
ABC123 35.5 497
XYZ789 12 168
CBA123 48.2 675.5
DEF456 20 280
```

---
## Group 1 Members
| Name | Student No. | Role | Data Structure |
|---|---|---|---|
| Bautista, Troy Jerron A. | 2515417 | Data Presenter, Code Repository, Compiler | AVL tree |
| Fabonan, Kurt Lorenz C. | 2511545 | Full Stack Developer | Quick sort |
| Geronimo, Joncel Zairho G. | 2512591 | Backend Developer | Stack |
| Salcedo, Lance Cristopher S. | 2515528 | Frontend Developer | Circular queue |
| Santos, Paterno Miguel R. | 2515538 | Project Leader, Full Stack Developer | Queues and hash table |
