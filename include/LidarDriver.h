// Progetto di Barison, Castellini, Petenazzo

#ifndef LIDARDRIVER_H
#define LIDARDRIVER_H

#include <vector>

class LidarDriver {
    private:
        // Ricordiamo la differenza tra lettura e scansione:
        // Il termine lettura identifica la singola misurazione di distanza a un dato angolo, mentre il termine
        // scansione identifica l’insieme di tutte le letture ai diversi angoli, acquisite in sequenza dal sensore.
        
        const int BUFFER_DIM; // Numero di scansioni
        const int angolo; // Angolo totale da spaziare, questo valore è fisso a 180 gradi
        const double ris_ang; // Angolo che separa le letture consecutive
        std::vector<std::vector<double>> letture;

};

#endif // "LIDARDRIVER_H"