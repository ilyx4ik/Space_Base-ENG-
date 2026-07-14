#pragma once
#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

class SpaceModule {
protected:
    string name;
    int EC; 

public:
    SpaceModule(string name, int EC) {
        this->name = name;
        this->EC = EC;
    }

    virtual ~SpaceModule() = default;

    string getName() const { return name; }
    int getEC() const { return EC; }
    
    virtual void addCrew(int count) {}
    
    virtual void report() {
        cout << "Module: " << name << " | Energy Consumption: " << EC << " kW" << endl;
    }

    virtual void save(ostream& os) const = 0; 
};

class LivingModule : public SpaceModule {
private:
    int crewCapacity;

public:
    LivingModule(string name, int EC, int crewCapacity) : SpaceModule(name, EC) {
        this->crewCapacity = crewCapacity;
    }

    int getCrewCapacity() const { return crewCapacity; }

    void report() override {
        SpaceModule::report();
        cout << "  ---> Crew Capacity: " << crewCapacity << " astronauts." << endl;
    }

    void addCrew(int count) override {
        if (count > crewCapacity) {
            throw runtime_error("Module overcrowding detected!");
        } else {
            cout << "Successfully assigned " << count << " astronauts." << endl; 
        }
    }

    void save(ostream& os) const override {
        os << "L " << getName() << " " << getEC() << " " << getCrewCapacity() << "\n";
    }
};

class ScienceModule : public SpaceModule {
private:
    string researchType;

public:
    ScienceModule(string name, int EC, string researchType) : SpaceModule(name, EC) {
        this->researchType = researchType;
    }

    string getResearchType() const { return researchType; }

    void report() override {
        SpaceModule::report();
        cout << "  --> Research Field: " << researchType << endl;
    }

    void save(ostream& os) const override {
        os << "S " << getName() << " " << getEC() << " " << getResearchType() << "\n";
    }
};

class PowerModule : public SpaceModule {
protected:
    int energyProduction;

public:
    PowerModule(string name, int EC, int energyProduction) : SpaceModule(name, EC) {
        this->energyProduction = energyProduction;
    }

    int getEnergyProduction() const { return energyProduction; }
    
    void report() override {
        SpaceModule::report();
        cout << " --> Power Grid Contribution: " << energyProduction << " kW" << endl;
    }

    void save(ostream& os) const override {
        os << "P " << getName() << " " << getEC() << " " << getEnergyProduction() << "\n";
    }
};