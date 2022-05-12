// DialogAppTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <vector>
#define NOMINMAX
#include <Windows.h>
#include <limits>
#include <thread>
using namespace std;

void coutColor(string inputString, WORD colorCode);
void AnimateMessage(string message, WORD colorCode, int milliseconds);
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

    /// How to use the dialog system
    ////Person that is going to be speaking... the name is used for display purposes only
    ////EX:(Bob: dialog here...)
    //speaker = "bob";
    ////This is the dialog the speaker is going to say.
    //text = "Hi my name is bob!";
    ////Clear the decision array from the previous dialog.
    //decisions.clear();
    ////If there are any decisions that need to be made with this dialog then put them here
    ////otherwise this SHOULD be empty! Empty is what tells the program to not run any of
    ////the logic assosiated with decision dialogs.
    //decisions = vector<Dialogue::Decision>{
    //    //A decision contains two parts; the actual decision, and the response that will be given if that
    //    //decision is made.
    //    Dialogue::Decision("decision here","response if i made that decision"),
    //    Dialogue::Decision("decision here","response if i made that decision"),
    //    Dialogue::Decision("decision here","response if i made that decision"),
    //    Dialogue::Decision("decision here","response if i made that decision"),
    //};
    ////Make a new dialog with the properties we declared above...
    //dialog = Dialogue(speaker, text, decisions);
    ////Finally we store the dialog...
    //dialogueData.push_back(dialog);

    //This is how it will look without comments MUCH SIMPLER
    //Just Copy and paste from here------
    //==========================================================================================
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
    //===============================================================================================
    //To here...and change it to your liking.
    speaker = "bob";
    text = "I wonder what jeffrey is doing?";
    decisions.clear();
    dialog = Dialogue(speaker, text, decisions);
    dialogueData.push_back(dialog);


    const WORD DEFAULT_COLOR = 7;
    const WORD P1COLOR = 10;
    const WORD P2COLOR = 14;
    const WORD ERRORCOLOR = 12;
    const int MAIN_DIALOG_SPEED = 30;
    const int SECONDARY_DIALOG_SPEED = 10;
    //Go through each piece of dialog and display it. 
    for (Dialogue d : dialogueData) {
        //Display dialog
        AnimateMessage(d.speaker + ": " + d.text, P1COLOR, MAIN_DIALOG_SPEED);
        //If we have no decisions to make then skip the
        //decision logic!
        if (d.decisions.empty() == false) {
            //-1 means they didn't answer which would probably mean something went wrong..
            int decisionMade = -1;
            //Display the decisions to the user
            cout << '\n';//skip line...
            for (int j = 0; j < d.decisions.size(); j++) {
                string decision = std::to_string(j) + ": " + d.decisions[j].decision + "\n";
                AnimateMessage(decision, DEFAULT_COLOR, 0);
            }
            //Tell the user to type a decision
            cout << "Type in a number to respond ";
            cin >> decisionMade;
            //Check for invalid inputs
            while (cin.fail() || decisionMade > d.decisions.size() - 1 || decisionMade < 0)
            {
                //get rid of error flag
                cin.clear();
                //ignore everthing on this line and go to a new one
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                AnimateMessage("Invalid Entry Type in a number! ", ERRORCOLOR, SECONDARY_DIALOG_SPEED);
                cin >> decisionMade;
            }
            cout << '\n';
            //If get here that means we have put in a valid input

            //Display the response to the decision we made
            AnimateMessage(d.speaker + ": " + d.decisions.at(decisionMade).response, P1COLOR, MAIN_DIALOG_SPEED);

            //Clear the decision input from the cin...
            cin.ignore();
        }
        //Wait for user to press enter...
        cin.get();
        cout << "\n";
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
    coutColor("End of our program no more dialog!\n", 12);
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
void AnimateMessage(string message, WORD colorCode,int milliseconds)
{
    bool skipMessage = false;
    for (int i = 0; i < message.size(); i++)
    {
        if (GetKeyState(VK_SPACE)) skipMessage = true;//If the user presses enter stop animating the message
        string letter = "";
        if (letter == "\\")
            if (message[i + 1] == 'n')
            {
                cout << "\n";
                i + 2;
                continue;
            }
        letter.push_back(message[i]);
        coutColor(letter, colorCode);

        //If we skip the message then just write out the message with no animations.
        if (skipMessage == true) continue;
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}
