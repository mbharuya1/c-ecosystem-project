# Ecosystem Simulation Project – Predator–Prey Model (C Programming)

This project implements a complete ecosystem simulation modeling interactions between predators and prey on a 2D grid.  
It was developed as part of the **Licence Informatique – C Programming / Ecosystem Modeling coursework at Sorbonne Université**.

The instructor provided base structures and function prototypes in `ecosys.h`.  
All algorithmic implementations were completed by the students inside `ecosys.c`, `main_ecosys.c`, and the test programs.

---

## Project Overview

This project builds a full simulation engine for a predator–prey ecosystem, including:

- Representation of animals (position, direction, energy, linked list structure)
- Movement rules with probabilistic direction changes
- Eating behavior (predators eat prey, prey eat grass)
- Energy management (gain, loss, death when energy ≤ 0)
- Reproduction of animals (probabilistic reproduction)
- Regrowth of grass over time
- ASCII-based visualization of the world grid
- Reading/writing ecosystems to and from text files
- Simulation over discrete time steps producing population statistics

---

## Project Structure

### **ecosys.c**  
Main implementation file.  
Contains all functions for:
- Creating animals  
- Adding/removing animals  
- Movement rules  
- Reproduction  
- Eating  
- Refreshing predators and prey  
- Refreshing the world grid  
- Displaying the ecosystem  

Most of the project logic is implemented here.

### **ecosys.h**  
Header file provided by the instructors.  
Defines:
- The `Animal` struct  
- Global parameters  
- Function prototypes  
- World size constants  
- External simulation variables  

Students use this file but do not modify its structure.

### **main_ecosys.c**  
Main simulation program.  
Initializes predators and prey, runs the full ecosystem loop, updates the world, prints ASCII visualizations, and writes population evolution to `Evol_Pop.txt`.

### **main_tests.c** and **main_tests2.c**  
Test programs used to verify correct behavior for:
- Movement  
- Reproduction  
- File I/O  
- List operations  
- Refresh functions  

### **Evol_Pop.txt**  
Automatically generated during simulation.  
Stores population evolution across all time steps.

### **sys.txt**  
Snapshot file storing an entire ecosystem state, used to test reading and writing ecosystem data.

### **Makefile**  
Build system to compile and run the project:
```bash
make
./ecosys
```

### **a.out**  
Default compiler output (ignored in version control).

---

## Key Implemented Functions

### Animal & List Management
- `creer_animal()` — create an animal  
- `ajouter_animal()` — add an animal to a list  
- `enlever_animal()` — remove an animal  
- `liberer_liste_animaux()` — free all animals  
- `compte_animal_it()` / `compte_animal_rec()` — count animals  

### Simulation Mechanics
- `bouger_animaux()` — random movement  
- `reproduce()` — probabilistic reproduction  
- `rafraichir_proies()` — update prey list  
- `rafraichir_predateurs()` — update predators list  
- `rafraichir_monde()` — regrow grass  

### Ecosystem Display & File I/O
- `afficher_ecosys()` — ASCII visualization  
- `ecrire_ecosys()` — save ecosystem to file  
- `lire_ecosys()` — load ecosystem from file  

All functions were validated through extensive tests and simulations.

