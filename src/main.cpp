#include <iostream>
#include "../include/LidarDriver.h"

int main() {
    LidarDriver d(5, 10); // Creiamo un oggetto
    d.print_all_scans(); // Stampiamo tutti
    std::cout << std::endl;

    std::cout << "Counter: " << d.get_counter() << std::endl; // 5
    std::cout << "Buffer Dim: " << d.get_BUFFER_DIM() << std::endl; // 5

    try {
        d.print_lettura(1, 2); // output = 12 
        d.print_scan(4); // colonna di indice 4
    } catch (const std::out_of_range& e){
        std::cout << "Errore " << e.what();
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    std::vector<double> test = d.get_scan();

    std::cout << "Counter: " << d.get_counter() << std::endl;
    std::cout << "Buffer Dim: " << d.get_BUFFER_DIM() << std::endl;
    std::cout << "Prova di print_lettura che va in eccezione" << std::endl;
    try {
        d.print_lettura(5, 2); 
    } catch (const std::out_of_range& e){
        std::cout << "Errore: ";std::cout << e.what();
        std::cout << std::endl;
    }

    std::cout << "Counter: " << d.get_counter() << std::endl;
    std::cout << "Buffer Dim: " << d.get_BUFFER_DIM() << std::endl;
    std::cout << std::endl;
    //std::cout << "Rimuoviamo il terzo scan" << std::endl;
    //d.remove_scan(3);
    //d.print_all_scans();

       std::vector<double> test1;
    for (int i = 0; i < 18; i++){
        test1[i] = i;
    }
    std::cout << d.get_counter() << std::endl;
    d.new_scan(test1);
    d.print_all_scans();






















    std::cout << "Eliminiamo tutti gli scan" << std::endl;
    d.clear_buffer();
    std::cout << "BUFFER_DIM: " << d.get_BUFFER_DIM() << std::endl;
    d.print_all_scans();

    return 0;
}