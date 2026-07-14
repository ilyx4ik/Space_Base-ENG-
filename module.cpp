#include "module.h"
#include <vector>
#include <memory>
#include <fstream>
#include <sstream>

void checkEnergyBalance(const vector<unique_ptr<SpaceModule>>& space) {
    int totalGeneration = 0;
    int totalConsumption = 0;
    for (size_t i = 0; i < space.size(); i++) {
        totalConsumption += space[i]->getEC();

        PowerModule* PowerMod = dynamic_cast<PowerModule*>(space[i].get());

        if (PowerMod != nullptr) {
            totalGeneration += PowerMod->getEnergyProduction();
        }
    }

    cout << "\n=== STATION ENERGY BALANCE ===" << endl;
    cout << "Total Generation:  " << totalGeneration << " kW" << endl;
    cout << "Total Consumption: " << totalConsumption << " kW" << endl;

    if (totalGeneration >= totalConsumption) {
        cout << "[STATUS]: Power grid is stable. Surplus: " 
             << (totalGeneration - totalConsumption) << " kW." << endl;
    } else {
        cout << "[CRITICAL WARNING]: Station Blackout! Deficit: " 
             << (totalConsumption - totalGeneration) << " kW!" << endl;
    }
    cout << "=============================" << endl;
}

int main() {
    vector<unique_ptr<SpaceModule>> space;
    
    ifstream inFile("station.txt");
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            char type;
            string name;
            int energy;
            ss >> type;
            ss >> name >> energy;
            if (type == 'L') {
                int capacity;
                ss >> capacity;
                space.push_back(make_unique<LivingModule>(name, energy, capacity));
            } else if (type == 'S') {
                string research;
                ss >> research;
                space.push_back(make_unique<ScienceModule>(name, energy, research));
            } else if (type == 'P') {
                int energyProduction;
                ss >> energyProduction;
                space.push_back(make_unique<PowerModule>(name, energy, energyProduction));
            }
        }
        inFile.close();
        cout << "[System]: Station data successfully loaded!" << endl;
    }

    int choice;
    while (true) {
        cout << "\n============ MENU ============" << endl;
        cout << "1. Show System Report & Energy Balance" << endl;
        cout << "2. Add New Module" << endl;
        cout << "3. Assign Crew members" << endl;
        cout << "4. Save & Exit" << endl;
        cout << "Your choice: ";
        
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\n--- CURRENT MODULE REPORT ---" << endl;
                for (size_t i = 0; i < space.size(); i++) {
                    cout << "[" << i << "] ";
                    space[i]->report();
                    cout << "---------------------------------------" << endl;
                }
                checkEnergyBalance(space);
                break;
                
            case 2: {
                char choiceModule;
                cout << "Select Module Type (L - Living, S - Science, P - Power Generator): ";
                cin >> choiceModule;
                choiceModule = toupper(choiceModule); 

                string name;
                int energy;
                cout << "Enter module name: ";
                cin >> name;
                cout << "Enter energy consumption (kW): ";
                cin >> energy;

                if (choiceModule == 'L') {
                    int capacity;
                    cout << "Enter crew capacity: ";
                    cin >> capacity;
                    space.push_back(make_unique<LivingModule>(name, energy, capacity));
                    cout << "[Success]: Living Module added successfully!" << endl;
                } else if (choiceModule == 'S') {
                    string research;
                    cout << "Enter research specialization: ";
                    cin >> research;
                    space.push_back(make_unique<ScienceModule>(name, energy, research));
                    cout << "[Success]: Science Module added successfully!" << endl;
                } else if (choiceModule == 'P') {
                    int energyProduction;
                    cout << "Enter power generation output (kW): ";
                    cin >> energyProduction;
                    space.push_back(make_unique<PowerModule>(name, energy, energyProduction));
                    cout << "[Success]: Power Module added successfully!" << endl;
                } else {
                    cout << "[Error]: Invalid module type selection!" << endl;
                }
                break;
            }
            
            case 3: {
                cout << "Select module index (0 to " << space.size() - 1 << ") to assign crew: ";
                size_t index;
                cin >> index;

                if (index >= space.size()) {
                    cout << "[Error]: Module index out of bounds!" << endl;
                } else {
                    cout << "How many astronauts to add?: ";
                    int count;
                    cin >> count;

                    LivingModule* living = dynamic_cast<LivingModule*>(space[index].get());

                    if (living != nullptr) {
                        try {
                            living->addCrew(count);
                        }
                        catch (const runtime_error& e) {
                            cout << "[SAFETY ALARM]: " << e.what() << endl;
                        }
                    } else {
                        cout << "[Error]: Cannot assign crew to \"" 
                             << space[index]->getName() << "\". It is not a living module!" << endl;
                    }
                }
                break;
            }
            
            case 4: {
                ofstream outFile("station.txt");
                if (outFile.is_open()) {
                    for (size_t i = 0; i < space.size(); i++) {
                        space[i]->save(outFile); 
                    }
                    outFile.close();
                    cout << "[System]: All configurations saved successfully. Powering down..." << endl;
                } else {
                    cout << "[Error]: Failed to open station.txt for writing!" << endl;
                }
                return 0; 
            }
            
            default:
                cout << "[Error]: Invalid menu option selected!" << endl;
                break;
        }
    }
    return 0;
}