
// DialogAppTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define NOMINMAX
#include <Windows.h>
#include <limits>
using namespace std;

void coutColor(string inputString, WORD colorCode);
class Dialogue {
public:
    class Decision {
    public:
        Decision();
        Decision(string decision, string response);
        ~Decision();
        string decision;
        string response;        
    };

    Dialogue();
    Dialogue(string speaker, string text, vector<Decision> decisions);
    ~Dialogue();
    string speaker;
    string text;
    vector<Decision> decisions;
};

int main()
{
    //This is where your dialog data will be stored. It would be best practice to put it in a seperate class and file, but for the sake of
    //simplicity and jessie's small brain it will go in here.
    vector<Dialogue> dialogueData;
    Dialogue dialog;
    string speaker = "";
    string text = "";
    vector<Dialogue::Decision> decisions;

    //Person that is going to be speaking... the name is used for display purposes only
    //EX:(Bob: dialog here...)
    speaker = "bob"; 
    //This is the dialog the speaker is going to say.
    text = "Hi my name is bob!";
    //Clear the decision array from the previous dialog.
    decisions.clear();
    //If there are any decisions that need to be made with this dialog then put them here
    //otherwise this SHOULD be empty! Empty is what tells the program to not run any of
    //the logic assosiated with decision dialogs.
    decisions = vector<Dialogue::Decision>{
        //A decision contains two parts; the actual decision, and the response that will be given if that
        //decision is made.
        Dialogue::Decision("decision here","response if i made that decision"),
        Dialogue::Decision("decision here","response if i made that decision"),
        Dialogue::Decision("decision here","response if i made that decision"),
        Dialogue::Decision("decision here","response if i made that decision"),
    };
    //Make a new dialog with the properties we declared above...
    dialog = Dialogue(speaker, text, decisions);
    //Finally we store the dialog...
    dialogueData.push_back(dialog);

    //This is how it will look without comments MUCH SIMPLER
    //Just Copy and paste from here------
    speaker = "bob";
    text = "How are you doing today!";
    decisions.clear();
    decisions = vector<Dialogue::Decision>{
        Dialogue::Decision("Not good.","I feel that man, but, hey, I hope it gets better."),
        Dialogue::Decision("Its going great!","That's Awesome to hear."),
        Dialogue::Decision("I'm doing alright.","Hey can't always have a good day."),
        Dialogue::Decision("Sorry, but you kinda smell...","ughhh.. We good man? I was just trying to talk."),
    };
    dialog = Dialogue(speaker, text, decisions);
    dialogueData.push_back(dialog);
    //To here------------------------------ ...and change it to your liking.

    //Go through each piece of dialog and display it. 
    for (Dialogue d: dialogueData) {
        //Display dialog
        coutColor(d.speaker + ": " + d.text + "\n",10);
        //If we have no decisions to make then skip the
        //decision logic!
        if (d.decisions.empty() == false) {
            //-1 means they didn't answer which would probably mean something went wrong..
            int decisionMade = -1;
            //Display the decisions to the user
            for (int j = 0; j < d.decisions.size();j++) {
                cout << j << ": " << d.decisions[j].decision << "\n";
            }
            //Tell the user to type a decision
            cout << "Type in the a number to respond ";
            cin >> decisionMade;
            //Check for invalid inputs
            while (cin.fail() || decisionMade > d.decisions.size()-1 || decisionMade < 0)
            {
                //Clear the input
                cin.clear();
                //Tells cin to ignore all the input on this line
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                coutColor("Invalid Entry Type in a number! ",12);
                cin >> decisionMade;
            }

            //If get here that means we have put in a valid input
            coutColor(d.speaker + ": " + d.decisions.at(decisionMade).response + "\n", 10);
        }
    }
#pragma region Forloop version if thats better for you
    /*for (int i = 0; i < dialogData.size(); i++) {
        cout << dialogData[i].speaker << ": " << dialogData[i].text << "\n";
        if (dialogData[i].decisions.empty() == false) {
            for (int j = 0; j < dialogData[i].decisions.size(); j++) {
                cout << dialogData[i].decisions[j] << "\n";
            }
        }
    }*/
#pragma endregion

    cout << "\n============================================\n";
    coutColor("End of our program no more dialog!\n",12);
}

Dialogue::Dialogue()
{
    Dialogue::speaker = "";
    Dialogue::text = "";
}

Dialogue::Dialogue(string speaker, string text, vector<Decision> decisions)
{
    Dialogue::speaker = speaker;
    Dialogue::text = text;
    Dialogue::decisions = decisions;
}

Dialogue::~Dialogue()
{
}

Dialogue::Decision::Decision()
{
}

Dialogue::Decision::Decision(string decision, string response)
{
    Decision::decision = decision;
    Decision::response = response;
}

Dialogue::Decision::~Decision()
{
}
//Takes in ANSCII code for the color and writes the input string in that color
//The Console color gets reset back to the original color
#pragma region COLORCODES
//10 = LIMEGREEN
//11 = CYAN
//12 = RED
//13 = MAGENTA
//14 = YELLOW
//15 = WHITE
#pragma endregion
void coutColor(string inputString, WORD colorCode)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;

    //If we couldn't get screen buffer info the BAIL!
    if (!GetConsoleScreenBufferInfo(hConsole, &info))return;
    
    //Store the previous color in a variable 
    short prevColor = info.wAttributes;

    //Write the input text
    SetConsoleTextAttribute(hConsole, colorCode);
    cout << inputString;
    //Reset the color...
    SetConsoleTextAttribute(hConsole, prevColor);
}
