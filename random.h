#include <cstdlib>
#include <ctime>

long long int get_random_number() {
    srand(time(0));

    int seed = rand();

    long long int a = (long long int)seed * 15485863;
    return ((a * a % 2038074743));
}