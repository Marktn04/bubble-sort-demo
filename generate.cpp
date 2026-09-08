#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

mutex mtx;
int main (int argc, char* argv[]) {

    if (argc != 4) {
        cout << "You must provide exactly 3 arguments!" << endl;
        return 1;
    }

    cout << "argv[0]:" << argv[0] << endl;
    cout << "argv[1]:" << argv[1] << endl;
    cout << "argv[2]:" << argv[2] << endl;
    cout << "argv[3]:" << argv[3] << endl;

    int count = atoi(argv[1]);
    int min = atoi(argv[2]);
    int max = atoi(argv[3]);

    srand(0);
    ofstream file("numbers.dat");
    if (!file.is_open()) {
        cout << "Error 2" << endl;
        return 1;
    }
    for (int i = 0; i < count; i++) {
        int d = rand() % (max - min + 1) + min;
        file << d << endl;
    }
    file.close();

    return 0;
}



