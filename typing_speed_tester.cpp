#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <limits>

using namespace std;

class Score
{
public:
    string name;
    double wpm;
    double accuracy;
};

bool compareScores(Score a, Score b)
{
    return a.wpm > b.wpm;
}

class TypingTest
{
private:
    vector<string> paragraphs =
    {
        "Programming is the art of telling another human what one wants the computer to do.",

        "Data structures and algorithms are important for problem solving and coding interviews.",

        "Consistency and daily practice are the keys to becoming a great software developer.",

        "Typing speed improves with regular practice and proper finger placement on the keyboard.",

        "C plus plus is a powerful programming language used in competitive programming and development."
    };

public:

    void startTest()
    {
        srand(time(0));

        int randomIndex = rand() % paragraphs.size();

        string originalText = paragraphs[randomIndex];

        cout << "\n====================================";
        cout << "\n        TYPING SPEED TESTER";
        cout << "\n====================================\n";

        cout << "\nType The Following Paragraph:\n\n";

        cout << originalText << "\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string userInput;

        cout << "\nStart Typing Below:\n\n";

        time_t startTime = time(0);

        getline(cin, userInput);

        time_t endTime = time(0);

        double timeTaken = difftime(endTime, startTime);

        calculateResult(originalText, userInput, timeTaken);
    }

    void calculateResult(string original, string typed, double seconds)
    {
        int correctCharacters = 0;
        int mistakes = 0;

        int minLength = min(original.length(), typed.length());

        for (int i = 0; i < minLength; i++)
        {
            if (original[i] == typed[i])
            {
                correctCharacters++;
            }
            else
            {
                mistakes++;
            }
        }

        mistakes += abs((int)original.length() - (int)typed.length());

        double accuracy =
            ((double)correctCharacters / original.length()) * 100;

        int wordCount = 0;

        for (int i = 0; i < typed.length(); i++)
        {
            if (typed[i] == ' ')
            {
                wordCount++;
            }
        }

        wordCount++;

        double minutes = seconds / 60.0;

        double wpm = wordCount / minutes;

        cout << "\n====================================";
        cout << "\n              RESULTS";
        cout << "\n====================================\n";

        cout << fixed << setprecision(2);

        cout << "\nTime Taken   : " << seconds << " seconds";
        cout << "\nWords Typed  : " << wordCount;
        cout << "\nMistakes     : " << mistakes;
        cout << "\nAccuracy     : " << accuracy << "%";
        cout << "\nTyping Speed : " << wpm << " WPM\n";

        saveScore(wpm, accuracy);
    }

    void saveScore(double wpm, double accuracy)
    {
        string username;

        cout << "\nEnter Your Name: ";

        getline(cin, username);

        if (username.empty())
        {
            cout << "\nInvalid Name!\n";
            return;
        }

        ofstream file("leaderboard.txt", ios::app);

        if (file.is_open())
        {
            file << username << "|"
                 << wpm << "|"
                 << accuracy << endl;

            file.close();

            cout << "\nScore Saved Successfully!\n";
        }
        else
        {
            cout << "\nError Opening File!\n";
        }
    }

    void showLeaderboard()
    {
        ifstream file("leaderboard.txt");

        vector<Score> leaderboard;

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            string name;
            string wpmStr;
            string accuracyStr;

            getline(ss, name, '|');
            getline(ss, wpmStr, '|');
            getline(ss, accuracyStr, '|');

            Score temp;

            temp.name = name;
            temp.wpm = stod(wpmStr);
            temp.accuracy = stod(accuracyStr);

            leaderboard.push_back(temp);
        }

        file.close();

        sort(leaderboard.begin(),
             leaderboard.end(),
             compareScores);

        cout << "\n====================================";
        cout << "\n            LEADERBOARD";
        cout << "\n====================================\n";

        if (leaderboard.size() == 0)
        {
            cout << "\nNo Scores Available!\n";
            return;
        }

        cout << left
             << setw(20) << "Name"
             << setw(15) << "WPM"
             << setw(15) << "Accuracy"
             << endl;

        cout << "-------------------------------------------------\n";

        for (int i = 0; i < leaderboard.size(); i++)
        {
            cout << left
                 << setw(20) << leaderboard[i].name
                 << setw(15) << fixed << setprecision(2)
                 << leaderboard[i].wpm
                 << setw(15)
                 << leaderboard[i].accuracy << "%"
                 << endl;
        }
    }
};

int main()
{
    TypingTest test;

    int choice;

    while (true)
    {
        cout << "\n====================================";
        cout << "\n             MAIN MENU";
        cout << "\n====================================\n";

        cout << "1. Start Typing Test\n";
        cout << "2. Show Leaderboard\n";
        cout << "3. Exit\n";

        cout << "\nEnter Your Choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            test.startTest();
            break;

        case 2:
            test.showLeaderboard();
            break;

        case 3:
            cout << "\nThank You For Using The Program!\n";
            return 0;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }
    }

    return 0;
}