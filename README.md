# Space Station Manager 🚀

An interactive command-line space station management simulator written in C++.

This project showcases the application of key Object-Oriented Programming (OOP) principles, polymorphism, memory safety using smart pointers, exception handling, and custom file I/O operations.

## 🛠️ Key C++ Features & Concepts Demonstrated

*   **Inheritance & Polymorphism:** Features an abstract base class `SpaceModule` inherited by three distinct derived classes (`LivingModule`, `ScienceModule`, and `PowerModule`).
*   **Virtual Methods:** Employs dynamic dispatch for module-specific behavior, such as printing customized logs via `report()` and exporting configuration data via `save()`.
*   **Smart Pointers (`std::unique_ptr`):** Leverages modern memory management to store polymorphic objects in a vector without risk of memory leaks.
*   **RTTI & Dynamic Casting (`dynamic_cast`):** Performs runtime type checking to safely compute the aggregate energy balance of the station and verify if crew members can be assigned to a specific module.
*   **Exception Handling (`try-catch`):** Guards the program from crashing by throwing a `std::runtime_error` if a living module's maximum crew capacity is exceeded during boarding.
*   **File and String Streams (`fstream`, `stringstream`):** Parses the initial station architecture from `station.txt` on startup and serializes all system changes upon exit.

---

## 🎮 Features & Gameplay

Upon startup, the simulator loads the existing station layout from `station.txt`. Through an interactive CLI menu, you can perform the following actions:

1.  **Show System Report & Energy Balance:** Displays detailed diagnostic info for each module and calculates the total electricity generation vs. consumption. If consumption exceeds generation, the system triggers a blackout warning.
2.  **Add New Module:** Dock a brand-new module with the station in real time. Choose between:
    *   `L` — **Living Module** (consumes power, houses crew members).
    *   `S` — **Science Module** (consumes power, runs specific scientific research).
    *   `P` — **Power Module** (consumes minimal power, generates electricity for the entire station grid).
3.  **Assign Crew Members:** Send astronauts to a designated living module. If you attempt to assign crew to a laboratory or a generator, or exceed the module's maximum capacity, the station's security override blocks the action.
4.  **Save & Exit:** Overwrites `station.txt` with the newly updated station configuration and terminates the application cleanly.

---

## 📦 Project Structure

*   `module.h` — Declares the base `SpaceModule` and its derived classes.
*   `module.cpp` — Contains the implementation of the simulation's main control loop, the energy grid calculations, and overall system logic.
*   `station.txt` — The save file where the current structure of the station is stored.

---

## 🚀 Getting Started

To compile and run this project, you will need a C++ compiler supporting at least C++14.

### Compilation

Compile the project files using `g++` (or any equivalent compiler):

```bash
g++ -std=c++14 module.cpp -o SpaceStation

./SpaceStation