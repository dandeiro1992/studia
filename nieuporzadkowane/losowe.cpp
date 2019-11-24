#include <iostream>
#include <cstdlib>
#include <ctime>
int main()
{
    srand( time( NULL ) );
    std::cout << "Wylosowanie pierwsze: " << std::rand() << std::endl;
    int liczba = std::rand();
    std::cout << "Wylosowanie drugie: " << liczba << std::endl;
    liczba = std::rand();
    std::cout << "Wylosowanie trzecie: " << liczba << std::endl;
    return 0;
}
