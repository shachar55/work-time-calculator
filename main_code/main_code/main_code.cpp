#include <iostream>
#include <string>
#include <fstream>
#include <utility>
#include <stdexcept>
#include <sstream>
#include <vector>
#include "convert.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;


string RemoveChar(string str, vector<char> chars)
{
    
    for (int i = 0; i < chars.size(); i++)
        if (chars[i] == ' ')
        {
            str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
        }
        else
        {
            str.erase(remove(str.begin(), str.end(), chars[i]), str.end());
        }
    return str;
}

int main()
{
    string strMin;
    string strHor;
    int min;
    int tMin = 0;
    int hor;
    int tHor = 0;
    vector<string> Times;

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
        // taking the amount of days
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
                cout << "Type a vaild number(0x1)" << endl;
                strDays = "0";
            }
        }
        // taking the inputted time
        for (int i = 0; i < days; i++)
        {
            try
            {
                cout << "Please type the time in this format: " << endl << "Hours:Minutes" << endl;
                cin >> time;
                Times.push_back(time);

                strHor = Times[i].substr(0, Times[i].find(":"));
                strMin = Times[i].substr(time.find(":") + 1);


                min = stoi(strMin);

                hor = stoi(strHor);



                cout << endl;

            }
            catch (...)
            {
                cout << "Wrong Value/Format(0x2)" << endl << endl;
                i--;
                continue;
            }
            minutes.push_back(min);
            hours.push_back(hor);


        }
    }
    else if (ans == 'y') // opening and reading CSV file
    {
        int keep = 0;
        while (keep == 0)
        {
            string filePath;
            // opening the file and checking if its ok
            cout << "Type the file path" << endl;
            cin >> filePath;
            try
            {
                ifstream file(filePath);                    // opening file
                if (!file.is_open()) {
                    cout << "Check if the file is in a right format/layout" << endl;
                    cout << "Failed to open(0x3)" << endl;
                    Sleep(5000);
                    return 0;
                }
                else {
                   
                    cout << "Opened OK" << endl;
                    while (file.good())
                    {
                        string line;
                        getline(file, line, '\n');
                        Times.push_back(line);
                    }
                    // converting vector Times to minutes and hours and adding them to their vectors
                    for (int i = 0; i < Times.size(); i++)
                    {
                        cout << Times[i] << endl;
                        strHor = Times[i].substr(0, Times[i].find(":"));

                        strMin = Times[i].substr(Times[i].find(":") + 1);


                        min = stoi(strMin);
                        minutes.push_back(min);

                        hor = stoi(strHor);
                        hours.push_back(hor);


                    }
                    file.close();                           // closing file
                    keep = 1;
                }

            }
            catch(...)
            {
                cout << "Check if the file is in a right format/layout(0x4)" << endl;
            }
        }
        



    }
    // calculating total time, average and earnings
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
            try
            {
                avg = result / days;
                cout << avg << endl;
                ans = 0;
            }
            catch (...)
            {
                cout << "Something went wrong(0x5)" << endl;
                Sleep(5000);
                return 0;
            }
        }
        cout << "Do you want to see the earnings? " << endl << "(y/n)" << endl;
        cin >> ans;

        if (ans == 'y')
        {
            try
            {
                cout << "How much do you earn per hour?" << endl;
                cin >> ern;
                ern = ern * result;
                cout << "You earned: " << ern << endl;
            }
            catch (...)
            {
                cout << "Something went wrong(0x6)" << endl;
                Sleep(5000);
                return 0;
            }
        }
        cout << "Do you want to export to CSV? " << endl << "(y/n)" << endl;
        cin >> ans;
        // exporting to CSV file
        if (ans == 'y')
        {
            try
            {
                string preName;
                cout << "Enter the file name:" << endl;
                cin >> preName;
                vector<char> nameVerf;
                char c[15] = { '"',',',';','/','\\','?','%','*',':','|','<','>','.','=' };
                for (int i = 0; i < 15; i++)
                {
                    nameVerf.push_back(c[i]);
                }
                string name = RemoveChar(preName, nameVerf);
                string csv = ".csv";
                name.append(csv);
                fstream expo;
                expo.open(name, ios::out);
                for (int i = 0; i < Times.size(); i++)
                {
                    expo << Times[i] << "\n";
                }
                expo << "\n" << "\n";
                expo << "Your total time:" << "," << result << "\n";
                if (avg != 0)
                {
                    expo << "Your average time per day: " << "," << avg << "\n";
                }
                if (ern != 0)
                {
                    expo << "Your earnings: " << "," << ern;
                }
            }
            catch (...)
            {
                cout << "An Error occurred please try again(0x7)" << endl;
                Sleep(5000);
                return 0;
            }
            
        }



    }

    return 0;
}
