// ---------------------------------------------------------------
// Programming Assignment:	CIS170C Course Project
// Developer:			    Trenton Denton
// Date Written:			08/20/2021
// Purpose:				    Coffee Punch Ticket System
// ---------------------------------------------------------------
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

//Allowing Const Chars to be Written to File
void tprintf(const char* format)
{
    std::cout << format;
}
template<typename T, typename... Targs>
void tprintf(const char* format, T value, Targs... Fargs) // recursive variadic function
{
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            tprintf(format + 1, Fargs...); // recursive call
            return;
        }
        std::cout << *format;
    }
}
//Open contents of file and display them
void showContents(fstream& file)
{
    string line;
    while (file >> line)
    {
        cout << line << endl;
    }
}


int main()
{
    //Struct used to set values to columns
    struct {
        string name;
        double customer_id;
        int number_of_punches;
    } customerids[] = {
        {"Trenton", 1234, 4},
        {"Joseph", 1235, 1},
        {"Kaldr", 1236, 0},
        {"Koda", 1237, 9},
        {"Kai", 1238, 5},
        {"Nova", 1239, 0}
    };

//Initial Code to Write Array to File.  
/*        fstream outFile;
        outFile.open("customerids0.txt", ios::app | ios::out);

        int i = 0;
        while (i < 6)
        {
            outFile << customerids[i].name << endl;
            outFile << customerids[i].customer_id << endl;
            tprintf("% % % \n", customerids[i].name, customerids[i].customer_id, customerids[i].number_of_punches);
            i++;
        }
        outFile.close();
        return 1;
*/
 

    //Verify that customer entered ID is in list of customer ID's.
    int customerindex = 6;
    char choice = 'y';
    //For loop to iterate through customer ids.
    while (choice == 'y')
    {
        double customerinput;
        cout << "Please enter customer ID: ";
        cin >> customerinput;

        for (int i = 0; i < 6; i++) {
            
            if (customerinput == customerids[i].customer_id)
            {
                customerindex = i;
            }
        }
        char adminYN;
        string password;
        if (customerindex >= 6) {
            cout << "Customer ID Not Found." << endl;
            cout << "Would you like to access the customer list? (y or n): ";
            cin >> adminYN;
            if (adminYN == 'y')
            { 
                cout << "Please enter the admin password: ";
                cin >> password;
                if (password == "adminpass")
                {
                    fstream dataFile;
                    dataFile.open("customerids0.txt", ios::in);
                    showContents(dataFile);
                    dataFile.close();
                    return main();
                }
                if (password != "adminpass")
                {
                    cout << "You have entered an incorrect password." << endl;
                    break;
                }
            }
            if (adminYN == 'n')
            {
                break;
            }
        }

        cout << "Thank you " << customerids[customerindex].name << ". You have " << customerids[customerindex].number_of_punches << " punches." << endl;

        if (customerids[customerindex].number_of_punches >= 5)
        {
            char redeempunch;
            cout << "Would you like to redeem your free coffee for 5 punches?" << endl;
            cout << "Enter y for yes or n for no: " << endl;
            cin >> redeempunch;

            if (redeempunch == 'y')
            {
                cout << "Enjoy your free coffee!" << endl;
                customerids[customerindex].number_of_punches = customerids[customerindex].number_of_punches - 5;
            }
            else
            {
                customerids[customerindex].number_of_punches = customerids[customerindex].number_of_punches + 1;
                cout << "Thank you! You now have " << customerids[customerindex].number_of_punches << endl;
            }
        }

        customerids[customerindex].number_of_punches += 1;
        cout << "You have " << customerids[customerindex].number_of_punches << " punches. Thank you!" << endl;
        cout << "Do you want to enter another customer ID? (y or n): ";
        cin >> choice;
    }

}
