

#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "convert.h"

using namespace std;




int main()
{
    string strMin;
    string strHor;
    int min;
    int tMin = 0;
    int hor;
    int tHor = 0;

    string strDays = "0";
    int days;
    double result;
    char ans;

    string time;

    vector<int> hours;
    vector<int> minutes;

    cout << "Do you want to import a CSV file? (y/n) " << endl;
    cin >> ans;
    cout << endl;
    if (ans == 'n')
    {
        while (strDays == "0")
        {
            try
            {
                cout << "Please enter the amount of days" << endl;
                cin >> strDays;
                days = stoi(strDays);
            }
            catch (...)
            {
                cout << "Type a vaild number" << endl;
                strDays = "0";
            }
        }

        for (int i = 0; i < days; i++)
        {
            try
            {
                cout << "Please type the time in this format: " << endl << "Hours:Minutes" << endl;
                cin >> time;
                strHor = time.substr(0, time.find(":"));

                strMin = time.substr(time.find(":") + 1);


                min = stoi(strMin);

                hor = stoi(strHor);



                cout << endl;

            }
            catch (...)
            {
                cout << "Wrong Value/Format" << endl << endl;
                i--;
                continue;
            }
            minutes.push_back(min);
            hours.push_back(hor);


        }
    }
    else if (ans == 'y')
    {
        int keep = 0;
        while (keep == 0)
        {
            string filePath;

            cout << "Type the file path" << endl;
            cin >> filePath;
            ifstream file(filePath);       // note no mode needed
            if (!file.is_open()) {
                cout << " Failed to open" << endl;
                return 0;
            }
            else {
                keep = 1;
                cout << "Opened OK" << endl;
                vector<string> Times;
                while (file.good())
                {
                    string line;
                    getline(file, line, '\n');
                    Times.push_back(line);
                }
                cout << Times.size() << endl;
                for (int i = 0; i < Times.size(); i++)
                {
                    cout << Times[i] << endl;
                    strHor = Times[i].substr(0, Times[i].find(":"));

                    strMin = Times[i].substr(Times[i].find(":") + 1);


                    min = stoi(strMin);
                    cout << min << endl;
                    minutes.push_back(min);

                    hor = stoi(strHor);
                    cout << hor << endl;
                    hours.push_back(hor);


                }
            }
        }



    }
    days = minutes.size();
    for (int i = 0; i < minutes.size(); i++)
    {
        tMin += minutes[i];
        tHor += hours[i];
    }
    convertor c;
    {
        int tMinutes;
        double avg;
        double ern;
        tMinutes = c.convert(tHor, tMin);
        result = tMinutes / 60.0;

        cout << "The result is: " << result << endl;

        cout << "Do you want to see the average? " << endl << "(y/n)" << endl;
        cin >> ans;
        if (ans == 'y')
        {
            avg = result / days;
            cout << avg << endl;
            ans = 0;
        }
        cout << "Do you want to see the earnings? " << endl << "(y/n)" << endl;
        cin >> ans;

        if (ans == 'y')
        {
            cout << "How much do you earn per hour?" << endl;
            cin >> ern;
            ern = ern * result;
            cout << "You earned: " << ern << endl;
        }
        cout << "Do you want to export to CSV? " << endl << "(y/n)" << endl;
        cin >> ans;

        if (ans == 'y')
        {

        }



    }

    return 0;
}
