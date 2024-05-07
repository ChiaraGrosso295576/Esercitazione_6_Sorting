#include <iostream>
#include <chrono>
#include <unistd.h>
#include <vector>
#include <numeric> //per iota()
#include <algorithm> //per generate()
#include "SortingAlgorithm.hpp"
using namespace SortLibrary;
using namespace std;

//argc = num. argomenti passati dalla command line + 1(path)
//argv contiene gli argomenti passati in input dalla posizione 1 in poi
int main(int argc, char **argv)
{
    double sum_tBubble = 0.0;
    double sum_tMerge = 0.0;
    if (! (argc > 1) ){           //argc contiene solo il path
        std::cerr << "Missing input arguments" << std::endl;
        return 1;
    }
    srand(time(nullptr)); /* ottengo valori diversi ad ogni esecuzione del programma se uso un parametro variabile,
              con un intero fissato "parto sempre dallo stesso punto"
              quindi vettori della stessa lunghezza sarebbero composti dagli stessi elementi*/
    for (unsigned int j=1; j<(argc);j++){ //i parametri effettivi in input sono quelli da argv[1] in poi
        if (stoi(argv[j]) < 0){           //se argv[j] fosse negativo non potrebbe essere la lunghezza di un vettore
            std::cerr << "The length of a vector can't be negative" << std::endl;
            return 2;
        }
        else{
            unsigned int length = stoi(argv[j]); //stoi converte una stringa in un intero
            vector<int> vBubble(length);
            vector<int> vMerge(length);
            for (unsigned int i =0;i<length;i++)
            {
                vBubble[i] = rand()%1000; //così i numeri sono compresi in [0,1000)
                vMerge[i] = vBubble[i]; //creo vMerge come copia in modo da confrontare gli algoritmi su vettori uguali
            }

            cout<<"Length of the vector: "<< stoi(argv[j])<<endl;
            //cronometro quanto impiega ciascun algoritmo di ordinamento per un vettore di lunghezza data
            std::chrono::steady_clock::time_point tBubble_begin=std::chrono::steady_clock::now(); //steady_clock dipende dall'istante in cui ho riavviato il sistema
            BubbleSort(vBubble);
            std::chrono::steady_clock::time_point tBubble_end=std::chrono::steady_clock::now();
            double bubble_duration = std::chrono::duration_cast<std::chrono::microseconds>(tBubble_end-tBubble_begin).count(); //misura una differenza di tempo
            cout<<"BubbleSort time:"<<bubble_duration<<" microseconds"<<endl;
            std::chrono::steady_clock::time_point tMerge_begin=std::chrono::steady_clock::now();
            MergeSort(vMerge);
            std::chrono::steady_clock::time_point tMerge_end=std::chrono::steady_clock::now();
            double merge_duration = std::chrono::duration_cast<std::chrono::microseconds>(tMerge_end-tMerge_begin).count(); //misura una differenza di tempo
            cout<<"MergeSort time:"<<merge_duration<<" microseconds"<<endl<<endl;
            //sommo i tempi per ogni ordinamento effettuato
            sum_tBubble += bubble_duration;
            sum_tMerge += merge_duration;

        }
    }
    //calcolo le medie dei tempi impiegati dai due algoritmi per tutti i vettori
    /*se si volesse confrontare l'efficienza su vettori di lunghezza uguale sarebbe sufficiente passare in input
     * (nella command line) più volte il valore della lunghezza desiderata*/
    double avg_tBubble = sum_tBubble/(argc-1);
    double avg_tMerge = sum_tMerge/(argc-1);
    cout<<"Average time for BubbleSort :"<<avg_tBubble<<" microseconds"<<endl;
    cout<<"Average time for MergeSort :"<<avg_tMerge<<" microseconds"<<endl<<endl;

    return 0;
}


