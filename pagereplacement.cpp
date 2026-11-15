#include <iostream>
using namespace std;

int main() {
    int n, f, pages[100];

    cout << "Enter number of pages: ";
    cin >> n;

    cout << "Enter reference string: ";
    for(int i = 0; i < n; i++)
        cin >> pages[i];

    cout << "Enter number of frames: ";
    cin >> f;

    int fifo[10], lru[10], opt[10];
    int a = 0, b = 0, c = 0;
    int faults1 = 0, faults2 = 0, faults3 = 0;

    for(int i = 0; i < f; i++)
        fifo[i] = lru[i] = opt[i] = -1;

    // FIFO
    for(int i = 0; i < n; i++) {
        bool hit = false;

        for(int j = 0; j < f; j++)
            if(fifo[j] == pages[i]) hit = true;

        if(!hit) {
            fifo[a] = pages[i];
            a = (a + 1) % f;
            faults1++;
        }
    }

    // LRU
    int last[10] = {0};

    for(int i = 0; i < n; i++) {
        bool hit = false;
        int pos = -1;

        for(int j = 0; j < f; j++)
            if(lru[j] == pages[i]) {
                hit = true;
                pos = j;
            }

        if(hit) {
            last[pos] = i;
        }
        else {
            int index = 0;

            for(int j = 0; j < f; j++)
                if(lru[j] == -1) {
                    index = j;
                    break;
                }

            if(lru[index] != -1) {
                for(int j = 1; j < f; j++)
                    if(last[j] < last[index])
                        index = j;
            }

            lru[index] = pages[i];
            last[index] = i;
            faults2++;
        }
    }

    // Optimal
    for(int i = 0; i < n; i++) {
        bool hit = false;

        for(int j = 0; j < f; j++)
            if(opt[j] == pages[i]) hit = true;

        if(!hit) {
            int index = -1, farthest = -1;

            for(int j = 0; j < f; j++) {
                if(opt[j] == -1) {
                    index = j;
                    break;
                }

                int k;
                for(k = i + 1; k < n; k++)
                    if(opt[j] == pages[k]) break;

                if(k > farthest) {
                    farthest = k;
                    index = j;
                }
            }

            opt[index] = pages[i];
            faults3++;
        }
    }

    cout << "\nFIFO Page Faults: " << faults1;
    cout << "\nLRU Page Faults: " << faults2;
    cout << "\nOptimal Page Faults: " << faults3;

    return 0;
}