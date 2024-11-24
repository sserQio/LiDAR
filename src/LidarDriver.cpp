// Progetto di Barison, Castellini e Petenazzo

#include <iostream>
#include "../include/LidarDriver.h"

LidarDriver::LidarDriver(int BufferSize, double angRis){
    BUFFER_DIM = BufferSize;
    ris_ang = angRis;
    angolo = 180;
    counter = 0;
    size = BUFFER_DIM; // DA MODIFICARE
    for (int x = 0; x < BUFFER_DIM; x++){
        increment_counter();
        total_scans.push_back(std::vector<double>());
        for (int y = 0; y < static_cast<int>(180/ris_ang); y++){
            total_scans.at(x).push_back(10*x + y);
        }
    }
    increment_counter();
};

int LidarDriver::get_BUFFER_DIM() const{
    return BUFFER_DIM;
}

double LidarDriver::get_ris_ang() const{
    return ris_ang;
}

int LidarDriver::get_counter() {
    return counter;
}

const std::vector<std::vector<double>>& LidarDriver::get_total_scans() const {
    return total_scans;
}

void LidarDriver::print_lettura(int x, int y){
    if (total_scans.size() < BUFFER_DIM){
        if (x >= counter){
            throw std::out_of_range("Indice x (numero scan) -> Fuori Range");
        }
    }
    else {
    std::cout << "La lettura del valore a coordinate x: " << x << ", y: " << y << " dello scan è " << LidarDriver::total_scans[x][y] << std::endl;
    }
}

void LidarDriver::print_scan(int x){
    std::cout << "Lo scan richiesto, ad indice " << x << ", è: " << std::endl;
    for (int y = 0; y < static_cast<int>(180/get_ris_ang()); y ++) {
        std::cout << LidarDriver::total_scans[x][y] << std::endl;
    }
}

void LidarDriver::print_all_scans(){
    if (size != 0){
        int nLetture = static_cast<int>(angolo / ris_ang);
        for (int y = 0; y < nLetture; y++){
            for (int x = 0; x < BUFFER_DIM; x++){
                std::cout << total_scans[x][y];std::cout<<" ";
            }
            std::cout<<std::endl;
        }
    } else {
        std::cout << "Errore: Il Buffer è vuoto" << std::endl;
    }
}

/*
void LidarDriver::remove_scan(int x){
    if (size == 0) std::cout << "Errore: Il Buffer è vuoto" << std::endl;
    if (size < BUFFER_DIM) { // Caso in cui il buffer non pieno
        if (x < counter){ // Controllo sull'indice
            int nLetture = static_cast<int>(angolo / ris_ang);
            for (int y = 0; y < nLetture; y++){
                total_scans[x][y].erase(total_scans.begin() + x); // Elimina lo scan a indice x e sposta tutti i successivi a sinistra di 1
            }
            size--;
            counter--;
        } else {
            throw std::out_of_range("Indice x (numero scan) -> Fuori Range");
        }
    }
    if (size == BUFFER_DIM){ // Caso in cui il buffer è pieno
        if (x < BUFFER_DIM){ 
            total_scans.erase(total_scans.begin() + x); // Elimina lo scan a indice x e sposta tutti i successivi a sinistra di 1
            size--;
            counter--;
        } else {
            throw std::out_of_range("Indice x (numero scan) -> Fuori Range");

        } 
    }
}
*/

// se il buffer è pieno il vecchio è sempre counter + 1
void LidarDriver::new_scan(std::vector<double>& scan){
        total_scans.insert(total_scans.begin() + counter, scan); // Caso in cui il buffer è pieno
        increment_counter();
        if (size < BUFFER_DIM) size++;
}

std::vector<double> LidarDriver::get_scan(){
    std::cout << "Questo è lo scan che si vuole eliminare. ";
    if(size==BUFFER_DIM){
        LidarDriver::print_scan(counter);
        std::cout << "E' stato eliminato lo scan" << std::endl;
        std::vector<double> eliminato;
         eliminato = total_scans[counter];
    }
    else{
        LidarDriver::print_scan(counter - 1);
        std::cout << "E' stato eliminato lo scan" << std::endl;
        std::vector<double> eliminato; // Vettore ausiliario per il return
        eliminato = total_scans[counter - 1]; // Quando l'indice è zero, il counter è 1...

    }
    total_scans.pop_back(); // Eliminiamo l'ultima colonna da total_scans
    total_scans.push_back(std::vector<double>());    
    decrement_counter(); 
    return eliminato;
}

void LidarDriver::clear_buffer(){
    while (!total_scans.empty()) { // Usiamo il ciclo while altrimenti con il ciclo for, usando indice che va da 0 a DIM_BUFFER - 1
        total_scans.pop_back();    // in realtà dopo ogni pop_back ci troviamo sempre in posizione 0 (è come se fosse uno shift)
    }
    for(int i = 0; i < BUFFER_DIM; i++){
        total_scans.push_back(std::vector<double>()); // Inseriamo vettori vuoti
    }
    counter = 0;
    size = 0;
    
}

void LidarDriver::increment_counter(){
    if (counter == BUFFER_DIM) counter = 0;
    else counter++;
}

void LidarDriver::decrement_counter(){
    if (counter != 0) counter--;
}

std::ostream& operator<<(std::ostream& os, const LidarDriver& d){
    const std::vector<std::vector<double>>& appoggio = d.get_total_scans();
    const std::vector<double>& app = appoggio.back(); // Reference all'ultima colonna
    os << app; 
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::vector<double>& v){
    for (int i = 0; i < v.size(); i++){
        os << v[i];
    }
    return os;
}
