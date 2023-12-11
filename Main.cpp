// author kerin patel
// date 12/10/2023
// project 3 
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdlib>
#include <sstream>
#include <limits>
using namespace std;


void print_menu (){
    // print main menu with all of the options
    cout << "\t Main Menu" << endl;
    cout << "[1] Loop an item (Enter a word)" << endl;
    cout << "[2] Print frequency of all items" << endl;
    cout << "[3] Print Volume of all items" << endl;
    cout << "[4] Exit" << endl;
}

// Function to trim leading and trailing spaces from a string
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    if (string::npos == first) {
        return "";
    }
    size_t last = str.find_last_not_of(" \t");
    return str.substr(first, (last - first + 1));
}
void check_for_memory_file(){
    ifstream inFS; 
    ofstream outFS;
    string fileName = "Memory.txt";
    //open the memory file
    inFS.open(fileName);
    if (!inFS.is_open()) {
        //cout << "Could not open file wordFile.txt." << endl;

        // create and open the output file for writing
        outFS.open(fileName);
        // Check if the file is successfully opened
        if (!outFS.is_open()) {
            cout << "Error opening " << fileName << " for writing." << endl;
            exit(1); // Exit the program with an error code
        }
        
    }

    inFS.close();
    outFS.close();
}
void check_for_storage_file(){
    ifstream inFS; 
    ofstream outFS;
    string fileName = "Storage.txt";
    //open the memory file
    inFS.open(fileName);
    if (!inFS.is_open()) {
        cout << "Could not open file wordFile.txt." << endl;

        // create and open the output file for writing
        outFS.open(fileName);
        // Check if the file is successfully opened
        if (!outFS.is_open()) {
            cout << "Error opening " << fileName << " for writing." << endl;
            exit(1); // Exit the program with an error code
        }
        else {
            cout << "file " << fileName<< " created" << endl;
        }
    }
    else {
        //cout << "file created" << endl;
    }

    inFS.close();
    outFS.close();
}
void Sort_file(string fileName){
    ifstream inFS; // input file stream
    ofstream outFS; // output file stream
    // Open the input file
    inFS.open(fileName);
    //open the memory file
    outFS.open("Memory.txt");

    
    if (inFS.is_open() && outFS.is_open()) {
        // Vector to store the lines of the file
        vector < string > lines;
        string line;

        // Read each line from the input file and store it in the vector
        while (getline(inFS, line)) {
        lines.push_back(line);
        }

        // Sort the lines in alphabetical order
        sort(lines.begin(), lines.end());

        // Write the sorted lines to the output file
        copy(lines.begin(), lines.end(), ostream_iterator < string > (outFS, "\n"));


        inFS.close();
        outFS.close();

        //cout << "\nLines sorted successfully.\n" << std::endl;
    } else {
        //cout << "\nFailed to open the files." << std::endl;
    }

}
void Add_frequency(){
    ifstream inFS; 
    ofstream outFS;
    string fileName = "Memory.txt";
    // Open the input file
    inFS.open("Memory.txt");
    //open the storage file
    outFS.open("Storage.txt");
    if (inFS.is_open() && outFS.is_open()) {
        string currentItem;
        int currentFrequency = 0;
        string line;

        // Read each line from the input file
        while (getline(inFS, line)) {
            line = trim(line); // Trim leading and trailing spaces

            if (line == currentItem) {
                // If the line matches the current item, increment the frequency
                currentFrequency++;
            } 
            else {
                // If the line doesn't match, write the current item and frequency to the output file
                if (!currentItem.empty()) {
                    outFS << currentItem << " " << currentFrequency << "\n";
                }

                // Set the current item to the new line and reset the frequency to 1
                currentItem = line;
                currentFrequency = 1;
            }
        }

        // Write the last item and frequency to the output file
        if (!currentItem.empty()) {
            outFS << currentItem << " " << currentFrequency << "\n";
        }

        inFS.close();
        outFS.close();

       // cout << "\nItems and their frequencies written successfully.\n" << std::endl;
    } else {
        //cout << "\nFailed to open the files." << std::endl;
    }
}


void LookUpWord(const string& wordToFind) {
    ifstream storageFile("Storage.txt"); // storage file is named Storage.txt
    if (storageFile.is_open()) {
        string itemName;
        int frequency;
        bool found = false;

        //cout << "Looking up word: " << wordToFind << endl;

        // Read each line from the storage file
        while (storageFile >> itemName >> frequency) {
            //cout << "Read from file: " << itemName << " " << frequency << endl;
            // Check if the current item matches the word to find
            if (itemName == wordToFind) {
                found = true;
                cout << "Item: " << itemName << "\nFrequency: " << frequency << endl;
                break;  // Exit the loop once the item is found
            }
        }

        if (!found) {
            cout << "Item not found in the storage file." << endl;
        }

        storageFile.close();
    } else {
        cout << "Failed to open the storage file." << endl;
    }
}
void PrintAllItems() {
    ifstream storageFile("Storage.txt");
    if (storageFile.is_open()) {
        string itemName;
        int frequency;

       // Read the first line outside the loop to handle potential empty files
        while (storageFile >> itemName >> frequency) {
            cout << itemName << " " << frequency << endl;
        }

        if (storageFile.fail() && !storageFile.eof()) {
            cout << "Error reading from the storage file." << endl;
        } else {
            cout << "End of file reached." << endl;
        }

        storageFile.close();
    } else {
        cout << "Failed to open the storage file." << endl;
    }
}
void PrintAllItemsVolume() {
    ifstream storageFile("Storage.txt"); // Assuming your storage file is named Storage.txt
    if (storageFile.is_open()) {
        string itemName;
        int frequency;

        // Read each line from the storage file and print the items and frequencies
        while (storageFile >> itemName >> frequency) {
            cout << itemName << " " ;
            // Print vertical bars based on the frequency
            for (int i = 0; i < frequency; ++i) {
                cout << "|";
            }
            cout << endl;
        }

        storageFile.close();
    } else {
        cout << "Failed to open the storage file." << endl;
    }
}
int main(){
    string fileName;
    fileName = "CS210_Project_Three_Input_File.txt";
    check_for_memory_file();
    check_for_storage_file();
    Sort_file(fileName);
    Add_frequency();

    // Attempt to delete the file
    if (remove("Memory.txt") != 0) {
        perror("Error deleting file");
    }
    
    print_menu();

    while(true){
        cout << "Enter your choice (1, 2, 3, or 4): ";

        int choice;
        cin >> choice;

        // Check if the input is a valid integer
        if (cin.good()) {
            // Input is a valid integer
            if (choice >= 1 && choice <= 4) {
                // Valid choice, exit the loop
                if (choice == 1) {
                    string wordToFind;
                    cout << "Enter the word to look up: ";
                    cin >> wordToFind;
                    LookUpWord(wordToFind);
                    print_menu();
                    
                }
                else if (choice == 2) {
                    PrintAllItems();
                    print_menu();
        
                }
                else if (choice == 3) {
                    PrintAllItemsVolume();
                    print_menu();
                }
                else if (choice == 4) {
                    cout << "Goodbye" << endl;
                    break;
                }
                else {
                cout << "Invalid choice." << endl;
                print_menu();
                cout << "Choice :-";
                cin >> choice;
                }
            }
            else {
                cout << "Invalid choice. Please enter 1, 2, 3, or 4." << endl;
            }
        }
    }


    return 0;
}
