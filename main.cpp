#include <iostream>
#include <string>

using namespace std;

void run(){
    cout << "\nTABU SEARCH -- ATSP\n";
    int option;
    string fileName;
    do {
        cout << "1.Load graph from file\n";
        cout << "2.Test tabu search\n";
        cout << "3.Change stop condition\n";
        cout << "4.Chose neighbourhood\n";
        cout << "5.Automatic tester\n";
        cout << "6.Exit\n";
        cout << "Choose an option:";


        cin >> option;
        cin.clear(); //This corrects the stream.
        cin.ignore(); //This skips the left over stream data.


        switch(option){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            default:
                cout << "Invalid input\n\n";
                break;

        }

    }while(option != 6);

}
int main() {
    run();
}
