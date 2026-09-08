#include <iostream>
#include <thread>
#include <fstream>
#include <sstream>
#include <mutex>
#include <cstdlib>

using namespace std;

const int divide = 16;
long long global_cool = 0;
mutex xtx;

void fibonacci(int n) {
    long long a = 0, b = 1;
    for (int i = 0; i < n; i++) {
        cout << a << " ";
        long long next = a + b;
        a = b;
        b = next;
    }
    cout << endl;
}

long long Sort(int* v, int g, int h) {
	long long local_cool = 0; //v is the array, i is the index, and j is the size.
	//xtx.lock();
	//global_array = global_array + 1;
	//xtx.unlock();
    for (int i = 0; i < h - 1; i++) {
        for (int j = 0; j < h - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
				local_cool++;
            }

        }
    }
xtx.lock();
global_cool = global_cool + local_cool;
xtx.unlock();
cout << "Process " << g << " swap count:" << local_cool << endl;
return local_cool;
}

int* MergeArray(int* a, int* b, int m, int n) {
int* out = new int[m + n];
  int i = 0;
 int j = 0;
 int k = 0;
    while (i < m && j < n) {
        if (a[i] <= b[j]) out[k++] = a[i++];
        else out[k++] = b[j++];
    }
    while (i < m) out[k++] = a[i++];
    while (j < n) out[k++] = b[j++];

    return out;
}

int main(int argc, char *argv[]) {
	fibonacci(20);
	if (argc != 3 && argc != 4) {
	cout << "Usage: ./mysort inputfile outputfile [-test]" << endl;
	return 0;
}
 //   int threads = atoi(argv[1]); //
 //   int size = atoi(argv[2]);
 //   int** dy = new int*[threads]; //Makes it so that you can create many arrarys
 //   thread* t = new thread[threads]; //similar function to make many new threads
int THE = 1000000;
if (argc == 4 && string(argv[3]) == "-test") {
	THE = 10000;
}


int see = 0;
ifstream fin(argv[1]);
	if (!fin) {
	cout << "Unable to open file" << endl;
return 0;
}


int count = 0;
string line;
while (getline(fin, line))
count++;
fin.clear();
fin.seekg(0);

if(count != THE){
	cout << "Error: expected " << THE << " numbers, found " << count << endl;
fin.close();
return 0;
}

if (count % divide != 0){
cout << "Error 2" << endl;
fin.close();
return 0;
}

int* numbers = new int[count];
int b = 0;
while (getline(fin, line)) {
stringstream ss(line);
ss >> numbers[b++];
} fin.close();


int segment_size = count / divide;

int** segments = new int*[divide];
for (int i=0; i<divide; i++){
	segments[i] = new int[segment_size];
	for (int j=0; j<segment_size; j++){
		segments[i][j] = numbers[i * segment_size + j];
}
}

thread t[divide];
for (int j=0; j<divide; j++){
 t[j] = thread(Sort, segments[j], j, segment_size);
}
for (int i=0; i<divide; i++){
 t[i].join();
}

int* merged = MergeArray(segments[0], segments[1], segment_size, segment_size);
int merged_size = segment_size * 2;

for (int j=2; j<divide; j++){
 int* newMerged = MergeArray(merged, segments[j], merged_size, segment_size);
	delete[] merged;
	merged = newMerged;
	merged_size += segment_size;
}
 ofstream fout(argv[2]);
if (!fout){
cout << "Unable to open file" << endl;
delete [] merged;
for (int i=0; i<divide; i++){
delete[] segments[i];
}
delete[] segments;
delete[] numbers;
return 0;
}
for (int j=0; j<merged_size; j++){
fout << merged[j] << endl;
} fout.close();

cout << "Total Swaps: "<< global_cool << endl;


   for (int i=0; i<divide; i++){
        delete[] segments[i];
}
	delete[] segments;
	delete[] merged;
delete[] numbers;
    return 0;
}