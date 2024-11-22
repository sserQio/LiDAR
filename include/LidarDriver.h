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
        int counter; // Contatore per tenere traccia dello scan più nuovo
        int size; // Contatore per vedere se il buffer è pieno
        std::vector<std::vector<double>> total_scans;

    public:
        LidarDriver(int bufferSize, double angRis); // Costruttore con parametri BUFFER_DIM e ris_ang

        int get_BUFFER_DIM(); // Metodo per ottenere BUFFER_DIM
        double get_ris_ang(); // Metodo per ottenere ris_ang
        
        // Organizzando le scan in matrice usiamo coordinate x e y per navigare. La coordinata x indica una colonna.
        // Una colonna comprende tutte le letture. Una colonna è quindi una scan. Fornendo il parametro y possiamo quindi
        // scegliere quale lettura stampare 
        void print_lettura(int x, int y); // Metodo per stampare una singola lettura
        void print_scan(int x); // Metodo per stampare uno scan
        void print_all_scans(); // Metodo per stampare la matrice con tutti gli scan
        void remove_scan(int x); // Rimuove una scan (colonna) a scelta all'indice x
        
        void new_scan(std::vector<double>& scan); // Accetta una nuova scansione e lo memorizza nel buffer
                                                  // e sovrascrive la meno recente se il buffer è pieno
        std::vector<double>& get_scan(); // Fornisce uno scan contenente la più vecchia e la rimuove dal buffer
        void clear_buffer(); // Elimina tutte le scansioni salvate
        double get_distance(double angolo); // Accetta un angolo e ritorna la lettura corrispondente a tale angolo
                                            // nella scansione più recente. Se non esiste tale angolo ritorna
                                            // il valore di angolo più vicino
};

// Overload operatore
std::ostream &operator<<(std::ostream& os, const std::vector<double>& scan);

#endif // "LIDARDRIVER_H"