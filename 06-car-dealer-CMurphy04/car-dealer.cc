/**
 *   @file: car-dealer.cc
 * @author: Collin Haggerty-Murphy
 *   @date: 4/4/2023
 *  @brief: User interfacce for a car dealership
 */

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


int displayMenu(string model, double modelPrice, vector<string> selectedOptions) { //function to display all the various parts of the menu 
    cout << endl;
    if (model == "") {
        cout << "NO MODEL SELECTED";
    } else {
        cout << "Model: " << model << ", $" << modelPrice << ", Options: ";
        if (selectedOptions.size() == 0) {
            cout << "None" << endl;
        } else {
            for (int i = 0; i < selectedOptions.size(); i++) {
                if (i != selectedOptions.size() - 1)
                    cout << selectedOptions.at(i) << ", ";
                else
                    cout << selectedOptions.at(i);
            }


        }

    }

    cout << endl;
    cout << endl;

    cout << "1. Select a model (E, L, X)" << endl;
    cout << "2. Display available options and prices" << endl;
    cout << "3. Add an option" << endl;
    cout << "4. Remove an option" << endl;
    cout << "5. Cancel order" << endl;
    cout << "6. Quit" << endl;
    cout << "Enter choice: ";

    string choice;
    getline(cin,choice);
    while (choice != "1" and choice != "2" and choice != "3" and choice != "4" and choice != "5" and choice != "6") {
        cout << "This is invalid choice.  Please enter a number between 1 and 6: ";
        getline(cin,choice);
    }



    return stoi(choice);

}

string toLower(string in) {//string function to turn a string to lower case
    string result = "";
    for (char c: in) {
        if (c <= 'Z' && c >= 'A')
            result += c - ('Z' - 'z');
        else
            result += c;
    }

    return result;
}

string toUpper(string in) {//string function to turn a string to upper case
    string result = "";
    for (char c: in) {
        if (c <= 'z' && c >= 'a')
            result += c + ('Z' - 'z');
        else
            result += c;
    }

    return result;
}

string selectModel() { //function to get the input for the model type
    string model = "";
    cout << "Enter the model (E, L, X): ";
    getline(cin, model);
    while (toLower(model) != "e" and toLower(model) != "l" and toLower(model) != "x") {
        cout << "This is invalid choice.  Enter the model (E, L, X): ";
        getline(cin, model);
    }

    return toUpper(model);
}

void displayOptions(vector<string> vOptions, vector<int> vPrices) { //function to display the various options available
    cout << "Prices for model E, L, & X: $10000.00, $12000.00, $18000.00" << endl;
    cout << "Available Options" << endl << endl;
    for (int i = 0; i < vOptions.size(); i++) {
        string opt = vOptions.at(i) + " ($" + to_string(vPrices.at(i)) + ")";
        cout << setw(25) << left << opt << "\t";
        if (i % 3 == 2) cout << endl;
    }

    cout << endl << endl;

}

int posInVector(string option, vector<string> vOptions) { //int function to retrieve the position of an option in a vector, returns -1 if not in vector
    for (int i = 0; i < vOptions.size(); i++) {
        if (toLower(vOptions.at(i)) == toLower(option)) return i;
    }

    return -1;
}

int addOption(vector<string> vOptions, vector<string> &selectedOptions) { //function to add an option to the vector, returns the position where option was added, returns -1 if nothing added
    if (selectedOptions.size() >= 6) {
        cout << "The maximum number of options(6) were already selected." << endl;
        return -1;
    }

    string opt;
    cout << "Enter option: ";
    getline(cin, opt);
    while (posInVector(opt, vOptions) == -1 and toLower(opt) != "cancel") {
        cout << "This is not a valid option.  Please enter a valid option or cancel: ";
        getline(cin, opt);
    }

    if (toLower(opt) == "cancel") {
        return -1;
    }

    if (posInVector(opt, selectedOptions) != -1) {
        cout << "This option was already selected." << endl;
        return -1;
    }

    int pos = posInVector(opt, vOptions);
    selectedOptions.push_back(vOptions.at(pos));
    return pos;

}

int removeOption(vector<string> vOptions, vector<string> &selectedOptions) { //function to remove an option from the vector, returns the position in the vector from which the option was removed - return -1 if nothing removed
    string opt;
    cout << "Enter option: ";
    getline(cin, opt);
    int pos = posInVector(opt, selectedOptions);
    if (pos != -1) {
        selectedOptions.erase(selectedOptions.begin() + pos);
        return posInVector(opt, vOptions);
    }

    return -1;
}


int main() {
    ifstream optionsFile("options.txt");
    vector<string> vOptions;
    vector<int> vPrices;
    string line;
    while (getline(optionsFile, line)) {//read in information for options
        istringstream iss(line);
        int price;
        string option;
        iss >> price;
        getline(iss, option);
        vOptions.push_back(option.substr(1, option.size() - 1));
        vPrices.push_back(price);
        // cout << option << "\t" << price << endl;
    }


    string model = "";
    double modelPrice = 0;
    vector<string> selectedOptions;
    int choice;
    string buffer;
    while (true) { //display the menu ready for user interaction
        choice = displayMenu(model, modelPrice, selectedOptions);

        if (choice == 1) {
            model = selectModel();
            if (toLower(model) == "e") modelPrice = 10000;
            if (toLower(model) == "l") modelPrice = 12000;
            if (toLower(model) == "x") modelPrice = 18000;

        } else if (model == "" and choice != 6 and choice != 2) {
            continue;
        }

        if (choice == 2) {
            displayOptions(vOptions, vPrices);
        }

        if (choice == 3) {
            int pos = addOption(vOptions, selectedOptions);

            if (pos != -1) {

                modelPrice = modelPrice + vPrices.at(pos);
            }
        }

        if (choice == 4) {
            int pos = removeOption(vOptions, selectedOptions);
            if (pos != -1) {

                modelPrice = modelPrice - vPrices.at(pos);
            }
        }

        if (choice == 5) {
            model = "";
            modelPrice = 0;
            selectedOptions.clear();
        }

        if (choice == 6) {
            break;
        }

    }


}