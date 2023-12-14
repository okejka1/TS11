#include <iostream>
#include <string>
#include <fstream>
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




}
void run() {
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


        switch (option) {
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

            case 4: {
                TabuSearch::apply(graph, endConditionInSeconds, neighbourhoodMethod, 200000000);
                break;
            }
            case 5: { // AUTO TESTS;
                cout << "Choose your method to define neighbours that you want to conduct test on\n";
                cout << "1.Swap two Cities\n";
                cout << "2.2-opt method\n";
                cout << "3.Hybrid of previous two methods\n";
                cin >> neighbourhoodMethod;
                cin.clear();
                cin.ignore();
                ofstream file((R"(..\output\results_)" + fileName + "_" + to_string(neighbourhoodMethod) + ".csv"));
                if (file.is_open()) {
                    if (fileName == "ftv47.atsp") {
                        endConditionInSeconds = 120;
                        optimalCost = 1776;
                    } else if (fileName == "ftv170.atsp") {
                        endConditionInSeconds = 240;
                        optimalCost = 2755;
                    } else if (fileName == "rbg403.atsp") {
                        endConditionInSeconds = 360;
                        optimalCost = 2465;
                    }
                    file << "cost;" << "time;" << "% error;" << optimalCost << "\n";

                    Solution testSolution;
                    testSolution.cost = INT_MAX;
                    int numOfTests = 10;
                    for (int i = 0; i < numOfTests; i++) {
                        pair<Solution, long> resultOfTest = TabuSearch::apply(graph, endConditionInSeconds,
                                                                              neighbourhoodMethod, 200000000);
                        int actualCost = resultOfTest.first.cost;
                        int percentageError = static_cast<int>(((actualCost - optimalCost) * 100.0) / optimalCost);

                        file << actualCost << ";" << resultOfTest.second << ";" << percentageError << "%" << ";"
                             << optimalCost << endl;
                        if (resultOfTest.first.cost < testSolution.cost) {
                            testSolution = resultOfTest.first;
                        }
                    }
                    file << "path of best solution" << endl;
                    for (int item: testSolution.path)
                        file << item <<"->";
                    file << testSolution.path[0] << endl;
                    file.close();
                }
                break;
            }
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
