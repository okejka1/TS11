#include <iostream>
#include <string>
#include "structures/Graph.h"
#include "algorithm/TabuSearch.h"


using namespace std;

void test() {
    Graph graph(1);
    string fileName;
    int fileOption;

    cout << "Choose a file that you want to conduct a test on\n";
    cout << "1. ftv47.atsp\n";
    cout << "2. ftv170.atsp\n";
    cout << "3. rbg403.atsp\n";

    cin >> fileOption;
    cin.clear();
    cin.ignore();

    switch (fileOption) {
        case 1:
            fileName = "ftv47.atsp";
            break;
        case 2:
            fileName = "ftv170.atsp";
            break;
        case 3:
            fileName = "rbg403.atsp";
            break;
        default:
            cout << "Invalid input\n\n";
            return;
    }

    graph.readGraphDirected(fileName);
    TabuSearch ts(graph);
    ts.TSSolver(60, 20000000, 2);


}
void run(){
    cout << "\nTABU SEARCH -- ATSP\n";
    int option;

    int optimalCost;
    // initial options
    string fileName = "rbg403.atsp";
    int neighbourhoodMethod = 3;
    int endConditionInSeconds = 120;
    Graph graph(1);  // Create a new graph object
    graph.readGraphDirected(fileName);


    do {

        cout << "1.Load graph from file\n";
        cout << "2.Change stop condition\n";
        cout << "3.Chose neighbourhood\n";
        cout << "4.Tabu search\n";
        cout << "5.Automatic tester\n";
        cout << "6.Exit\n";
        cout << "Choose an option:";


        cin >> option;
        cin.clear(); //This corrects the stream.
        cin.ignore(); //This skips the left over stream data.


        switch(option) {
            case 1: {

                do {

                    cout << "Choose a file that you want to conduct test on\n";
                    cout << "1.ftv47.atsp\n";
                    cout << "2.ftv170.atsp\n";
                    cout << "3.rbg403.atsp\n";
                    cin >> option;
                    cin.clear();
                    cin.ignore();

                } while (option < 1 || option > 3);

                if (option == 1) {
                    fileName = "ftv47.atsp";
                    optimalCost = 1776;
                }
                if (option == 2) {
                    fileName = "ftv170.atsp";
                    optimalCost = 2755;
                }
                if (option == 3) {
                    fileName = "rbg403.atsp";
                    optimalCost = 2465;
                }
                graph.readGraphDirected(fileName);
                break;
            }
            case 2:
                cout << "Enter your stop criteria (time in seconds):\n";
                cin >> endConditionInSeconds;
                cin.clear();
                cin.ignore();
                break;
            case 3:
                cout << "Choose your method to define neighbours\n";
                cout << "1.Swap two Cities\n";
                cout << "2.2-opt method\n";
                cout << "3.Hybrid of previous two methods\n";
                cin >> neighbourhoodMethod;
                cin.clear();
                cin.ignore();
                break;

            case 4:{
                TabuSearch ts(graph);
                ts.TSSolver(endConditionInSeconds,20000000,neighbourhoodMethod);
                break;
            }
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
//    test();

    return 0;
}
