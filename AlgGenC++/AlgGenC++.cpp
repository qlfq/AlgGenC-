#include <iostream>
#include <vector>
#include <ctime>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <cmath>


//Aplicatia implementează un algoritm genetic pentru a rezolva problema de optimizare a funcției f(x) = x ^ 2 în intervalul[MinInterval, MaxInterval]. Scopul este de a găsi valoarea lui x care maximizează funcția f(x).
//
//Algoritmul genetic funcționează prin crearea unei populații de soluții inițiale și apoi îmbunătățirea acestei populații prin încrucișarea și mutația soluțiilor de - a lungul mai multor generații.În timp ce rulează, aplicația afișează cea mai bună soluție și valoarea fitness - ului pentru fiecare generație.
//
//La sfârșitul execuției, aplicația afișează cea mai bună soluție găsită global(adică din toate generațiile) și valoarea fitness - ului corespunzător.Aceasta arată cum algoritmul a evoluat în timp și a ajuns la o soluție apropiată de optimul global pentru funcția f(x).


using namespace std;

const int Populatie = 1000; // dimensiunea populației. 
const int MaxGeneratii = 50; // definește numărul maxim de generații pentru care algoritmul va rula.
const double RataIncrucisare = 0.75; // rata de încrucișare, care reprezintă probabilitatea ca doi părinți să se încrucișeze și să formeze copii.
const double RataMutatie = 0.05; // rata de mutație, care reprezintă probabilitatea ca o soluție să sufere o mutație.
const int MinInterval = 0; // limita inferioară a intervalului în care funcția f(x) = x^2 este evaluată.
int MaxInterval; // limita superioară a intervalului.

// Funcția de fitness: f(x) = x^2
int fitness(int x) {
    return x * x;
}

// Funcție pentru a genera numere întregi aleatorii într-un interval
int getRandomInt(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Funcție de încrucișare între doi "părinți"
void crossover(int& a, int& b) {
    if (rand() / double(RAND_MAX) < RataIncrucisare) {
        int NrBitMax = ceil(log2(MaxInterval - MinInterval + 1));
        int point = getRandomInt(0, NrBitMax - 1);
        int mask = (1 << point) - 1;
        int temp_a = (a & mask) | (b & ~mask);
        int temp_b = (b & mask) | (a & ~mask);

        if (temp_a <= MaxInterval && temp_b <= MaxInterval) {
            a = temp_a;
            b = temp_b;
        }
    }
}

// Funcție de mutație a unei soluții
void mutate(int& x) {
    if (rand() / double(RAND_MAX) < RataMutatie) {
        int NrBitMax = ceil(log2(MaxInterval - MinInterval + 1));
        int point = getRandomInt(0, NrBitMax - 1);
        int mutated_x = x ^ (1 << point);

        if (mutated_x <= MaxInterval) {
            x = mutated_x;
        }
    }
}

int main() {

    //new seed
    srand(time(0));

    cout << "Dati limita superioara a intervalului: ";
    cin >> MaxInterval;
    cout << endl;

    //Calcul numar biti MaxInterval
    int NrBitMax = ceil(log2(MaxInterval - MinInterval + 1));
    cout << "NR BITI = " << NrBitMax << endl;
    cout << "=======================" << endl;

    // Crearea populației inițiale
    vector<int> population(Populatie);
    for (int i = 0; i < Populatie; ++i) {
        population[i] = getRandomInt(MinInterval, MaxInterval);
    }

    int global_best_solution = 0;
    int global_best_fitness = 0;

    // Iterarea prin generații
    for (int generation = 0; generation < MaxGeneratii; ++generation) {
        vector<int> new_population;

        // Crearea noii populații prin încrucișare și mutație
        for (int i = 0; i < Populatie; i += 2) {
               int parent1 = population[getRandomInt(0, Populatie - 1)];
               int parent2 = population[getRandomInt(0, Populatie - 1)];

               crossover(parent1, parent2);

               mutate(parent1);
               mutate(parent2);

               new_population.push_back(parent1);
               new_population.push_back(parent2);    
        }

        population = new_population;

        // Sortarea populației în funcție de valoarea fitness
        for (int i = 0; i < population.size(); i++) {
            for (int j = i + 1; j < population.size(); j++) {
                if (fitness(population[i]) < fitness(population[j])) {
                    swap(population[i], population[j]);
                }
            }
        }


        // Afișarea celei mai bune soluții din generația curentă
        int best_solution = population[0];
        int best_fitness = fitness(best_solution);

        // Actualizare soluție globală
        if (best_fitness > global_best_fitness) {
            global_best_solution = best_solution;
            global_best_fitness = best_fitness;
        }

        cout << "In generatia " << generation + 1 << " avem solutia: f(" << best_solution << ") cu fitness-ul: " << best_fitness << endl;
        cout << "=======================" << endl;

        // Dacă soluția optimă a fost găsită, se întrerupe algoritmul
        if (best_solution == MaxInterval) {
            break;
        }
    }

    cout << "\n+++++++++++++++++++++++" << endl;
    cout << "Cea mai buna solutie globala: f(" << global_best_solution << ") = " << global_best_fitness << endl;
    cout << endl;
    system("pause");
}


