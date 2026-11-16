#include <iostream>
using namespace std;

int main() {
    int n, f;
    int pages[100], frame[100], freq[100], time[100];

    int pageFaults = 0;
    int currentTime = 0;

    cout << "Enter number of pages: ";
    cin >> n;

    cout << "Enter page reference string: ";
    for(int i = 0; i < n; i++) {
        cin >> pages[i];
    }

    cout << "Enter number of frames: ";
    cin >> f;

    for(int i = 0; i < f; i++) {
        frame[i] = -1;
        freq[i] = 0;
        time[i] = 0;
    }

    for(int i = 0; i < n; i++) {
        currentTime++;
        bool found = false;

        // Check whether page is already present
        for(int j = 0; j < f; j++) {
            if(frame[j] == pages[i]) {
                freq[j]++;
                time[j] = currentTime;
                found = true;
                break;
            }
        }

        // Page fault
        if(!found) {
            pageFaults++;

            int pos = -1;

            // Find an empty frame
            for(int j = 0; j < f; j++) {
                if(frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty frame, find LFU page
            if(pos == -1) {
                pos = 0;

                for(int j = 1; j < f; j++) {
                    if(freq[j] < freq[pos] ||
                      (freq[j] == freq[pos] && time[j] < time[pos])) {
                        pos = j;
                    }
                }
            }

            frame[pos] = pages[i];
            freq[pos] = 1;
            time[pos] = currentTime;
        }

        cout << "Frames: ";
        for(int j = 0; j < f; j++) {
            if(frame[j] == -1)
                cout << "- ";
            else
                cout << frame[j] << " ";
        }

        cout << endl;
    }

    cout << "\nTotal Page Faults: " << pageFaults;

    return 0;
}