#include <iostream>
#include <vector>
#include <string>
#include <fstream> //file handling
#include <sstream> // tokenizing word

#include <regex>

using namespace std;

fstream outputFile;

// for pattern searching
std::regex litRegex("='([0-9]+)'");
std::regex alphaRegex("[a-zA-Z]");
std::regex digitRegex("[0-9]+");
std::regex diclareConstantRegex("'[0-9]+'");
std::regex containsPlus("(.+)([/+])(.+)");

std::smatch m;

bool start;
int locationCounter = 0;
int symbolCount = 0;
int literalTableCount = 0;
int poolTableCount = 0;

bool startOccured = false;
bool endOccured = false;
bool originOccured = false;
bool ltorgOccured = false;
bool equOccured = false;
bool dsOccured = false;
bool dcOccured = false;
bool imperativeOccured = false;
bool untilNext = false;

int errorCount = 0;
vector<string> errorLine;

// for mot table
struct motTable
{
    string mnemonic;
    string classType;
    string opcode;
};
struct motTable MOT[29];

//for symbol table
struct symbolTable
{
    string symbol;
    int address;
    //int size; /*ignore*/
} ST[20];

// for literal tale
struct literalTable
{
    string literal;
    int address;
} LT[10];

// for pool table
struct PoolTable
{
    int start;
    int count;
} PT[10];

//various function
void readFile();
void createMOT();
void processFile(fstream &inFile);
bool checkMOT(string word);

void displayError();
void displaySymbolTable();
void displayLiteralTable();
void displayPoolTable();

//main function and working of program
int main()
{

    createMOT();
    readFile();

    displaySymbolTable();
    displayLiteralTable();
    displayPoolTable();
    displayError();

    return 0;
}

// reading a sample program
void readFile()
{
    fstream my_file;
    my_file.open("sampleProgram.asm", ios::in);

    if (my_file.is_open())
    {
        std::cout << "Successfully opened file" << endl;
        processFile(my_file);
    }
    else
    {
        std::cout << "Failed to open file" << endl;
        exit(-1);
    }

    my_file.close();
}

//all the execution happens here
void processFile(fstream &inFile)
{
    string line, token;
    istringstream iss;

    outputFile.open("resultFile.txt", ios::out);

    //read line by line the program
    while (!inFile.eof())
    {
        std::cout << endl;
        vector<string> words;

        // read line by line from the file
        getline(inFile, line);

        //removing comment
        line = line.substr(0, line.find(";", 0));

        // read word by word from the line

        iss.clear(); // clear out state
        iss.str(line);
        std::cout << "\t:- ";
        outputFile << "\n\t:- ";
        //create vector of words of each line
        while (iss >> token)
        {

            std::cout << token << " ";
            outputFile << token << " ";

            words.push_back(token);
        }

        if (!startOccured)
        {
            //checkForStart

            if (words[0] == "START")
            {
                std::cout << "\tLC = " << locationCounter;
                outputFile << "\tLC = " << locationCounter;
                startOccured = true;
            }

            //location counter begins
            locationCounter = stoi(words[1]);
            cout << "\t( C," << locationCounter << " )";
            outputFile << "\t( C," << locationCounter << " )";
        }
        else if (!endOccured && startOccured)
        {
            originOccured = false;
            ltorgOccured = false;
            equOccured = false;
            dsOccured = false;
            dcOccured = false;

            int litLocationFlag = -1;
            int symLocationFlag = -1;
            int constantFlag = -1;

            //it will remain true till no literal occurs after ltorg
            if (untilNext == true && !regex_match(words[0], litRegex))
            {
                untilNext = false;
            }

            // process each word of the line one by one
            for (int i = 0; i < words.size(); i++)
            {

                bool inMOT = false;

                inMOT = checkMOT(words[i]);

                if (ltorgOccured == true)
                {
                    untilNext = true;
                }

                if (dsOccured == true || dcOccured == true) // if ds or dc occured
                {

                    i++;
                    if (regex_match(words[i], digitRegex))
                    {
                        constantFlag = stoi(words[i]);
                        bool flag = false;

                        for (int j = symbolCount - 2; j >= 0; j--)
                        {
                            if (ST[j].symbol == words[0])
                            {

                                flag = true;
                                if (ST[j].address == -1)
                                {
                                    ST[j].address = locationCounter;
                                }
                                else
                                {

                                    symbolCount--;
                                    std::cout << " ERROR: Duplicate Declaration";
                                    outputFile << " ERROR: Duplicate Declaration";
                                    errorLine.push_back("Duplicate Declaration of " + ST[j].symbol + " at location " + to_string(locationCounter));
                                }
                                break;
                            }
                        }
                    }
                }

                if (originOccured == true || equOccured == true)
                {
                    i++;
                    int a, b;

                    if (regex_match(words[i], m, containsPlus)) // eg origin 5+2 or origin a+3
                    {
                        if (regex_match(m.str(1), digitRegex))
                        {

                            a = stoi(m.str(1));
                        }
                        else
                        {
                            for (int j = 0; j < symbolCount; j++)
                            {

                                if (ST[j].symbol == m.str(1))
                                {
                                    a = ST[j].address;
                                    break;
                                }
                            }
                        }

                        if (regex_match(m.str(3), digitRegex))
                        {

                            b = stoi(m.str(3));
                        }
                        else
                        {
                            for (int j = 0; j < symbolCount; j++)
                            {

                                if (ST[j].symbol == m.str(3))
                                {
                                    b = ST[j].address;
                                    break;
                                }
                            }
                        }
                        if (equOccured)
                        {

                            int ans = a + b;
                            for (int k = 0; k < symbolCount; k++)
                            {
                                if (ST[k].symbol == words[0])
                                {
                                    ST[k].address = ans;
                                    break;
                                }
                            }

                        }
                        else
                        {
                            locationCounter = a + b;
                        }
                    }
                    else
                    {
                        // if no arithmataic sign involved
                        if (regex_match(words[i], m, digitRegex))
                        {

                            if (equOccured)
                            {
                                for (int k = 0; k < symbolCount; k++)
                                {
                                    if (ST[k].symbol == words[0])
                                    {
                                        ST[k].address = stoi(words[i]);
                                        break;
                                    }
                                }
                            }
                            else
                            {
                                locationCounter = stoi(words[i]);
                            }
                        }
                        else
                        {

                            for (int j = symbolCount; j >= 0; j--)
                            {
                                
                                if (ST[j].symbol == words[i])
                                {
                                    

                                    if (equOccured == true)
                                    {
                                        for (int k = 0; k < symbolCount; k++)
                                        {
                                            if (ST[k].symbol == words[0])
                                            {
                                                ST[k].address = ST[j].address;
                                                break;
                                            }
                                        }
                                    }
                                    else
                                    {
                                        locationCounter = ST[j].address;
                                    }

                                    break;
                                }
                            }
                        }
                    }
                }


                //if the word is not in mot checking for literal and symbol
                if (!inMOT && untilNext == false)
                {
                    smatch litMatch;
                    if (regex_match(words[i], litMatch, litRegex)) // add to literal 
                    {

                        LT[literalTableCount].literal = words[i];
                        LT[literalTableCount].address = -1;
                        literalTableCount++;
                        litLocationFlag = stoi(litMatch.str(1));
                    }
                    else //add to symbol table 
                    {

                        int symFlag = false;

                        int negativeFlag = false;
                        int k = 0;
                        for (k = 0; k < symbolCount; k++)
                        {
                            if (ST[k].symbol == words[i])
                            {
                                symFlag = true;
                                if (ST[k].address == -1)
                                {
                                    negativeFlag = true;
                                }

                                break;
                            }
                        }
                        if (symFlag)
                        {
                            if (i == 0 && negativeFlag == true)
                            {
                                ST[k].symbol = words[i];
                                ST[k].address = locationCounter;
                            }
                            else if (i == 0 && negativeFlag == false)
                            {

                                std::cout << " Error Case ";
                                outputFile << " Error Case ";
                                ST[symbolCount].symbol = words[i];
                                ST[symbolCount].address = locationCounter;

                                symbolCount++;
                            }
                            else
                            {
                                symLocationFlag = k;
                            }
                        }
                        else if (i == 0)
                        {
                            ST[symbolCount].symbol = words[i];
                            ST[symbolCount].address = locationCounter;
                            symbolCount++;
                        }
                        else
                        {
                            ST[symbolCount].symbol = words[i];
                            ST[symbolCount].address = -1;
                            symLocationFlag = symbolCount;
                            symbolCount++;
                        }
                    }
                }

            }

            // at the end of each line print details of that line
            if (originOccured == true || ltorgOccured == true || untilNext == true || equOccured == true || endOccured == true)
            {
                // std::cout << locationCounter << "  ******** lc value calculated \n";
            }
            else
            {
                std::cout << "---------- *LC = " << locationCounter;
                outputFile << "---------- *LC = " << locationCounter;
                if (symLocationFlag != -1)
                {
                    std::cout << "\t( S," << symLocationFlag + 1 << " )\t";
                    outputFile << "\t( S," << symLocationFlag + 1 << " )\t";
                }
                if (litLocationFlag != -1)
                {

                    std::cout << "\t( L," << litLocationFlag + 1 << " )\t";
                    outputFile << "\t( L," << litLocationFlag + 1 << " )\t";
                }
                if (constantFlag != -1)
                {
                    std::cout << "\t( C," << constantFlag << " )\t";
                    outputFile << "\t( C," << constantFlag << " )\t";
                }
                locationCounter++;
            }
        }
    }
    outputFile.close();
}

// to check if word is in mot
bool checkMOT(string word)
{

    for (int i = 0; i < sizeof(MOT) / sizeof(MOT[0]); i++)
    {
        if (word == MOT[i].mnemonic)
        {
            if (word == "ORIGIN")
            {
                originOccured = true;
            }
            else if (word == "EQU")
            {
                equOccured = true;
            }
            else if (word == "DS")
            {
                dsOccured = true;
            }
            else if (word == "DC")
            {
                dcOccured = true;
            }
            else if (word == "LTORG" || word == "END")
            {
                /*if word is ltorg or end process literal
                of literal table and then pool table */ 
                if (word == "LTORG")
                {
                    ltorgOccured = true;
                }
                else
                {
                    endOccured = true;
                }

                int count = 0;
                int poolFlag = -1;
                for (int j = 0; j < literalTableCount; j++)
                {
                    if (LT[j].address == -1)
                    {

                        LT[j].address = locationCounter;
                        locationCounter++;
                        count++;
                    }

                    if (count == 1)
                    {
                        poolFlag = j + 1;
                    }
                }
                if (poolFlag != -1)
                {
                    PT[poolTableCount].start = poolFlag;
                    PT[poolTableCount].count = count;
                    poolTableCount++;
                }
            }
            else
            {

                imperativeOccured = true;
            }
            std::cout << "\t----";
            std::cout << " (" << MOT[i].classType << "," << MOT[i].opcode << ") ";

            outputFile << "\t----";
            outputFile << " (" << MOT[i].classType << "," << MOT[i].opcode << ") ";

            return true;
        }
    }

    return false;
}

//creating mot table from reading through file
void createMOT() 
{
    string line, token;
    fstream motTableFile;
    istringstream iss;

    motTableFile.open("motTable.txt", ios::in);

    if (motTableFile.is_open())
    {

        int i = 0;
        while (!motTableFile.eof())
        {

            vector<string> words;

            getline(motTableFile, line);

            iss.clear(); // clear out state
            iss.str(line);
            int a = 0;
            while (iss >> token)
            {
                //std::cout<<token<<" ";
                words.push_back(token);
            }

            MOT[i].mnemonic = words[0];
            MOT[i].classType = words[1];
            MOT[i].opcode = words[2];

            i++;
        }
        std::cout << "-> MOT Table Created" << endl;
    }
    motTableFile.close();
}

//display symbol table in terminal and in a file
void displaySymbolTable()
{
    fstream symbolFile;
    symbolFile.open("symbolTableFile.txt", ios::out);
    if (symbolFile.is_open())
    {
        symbolFile << "\n Symbol Table" << endl;
        std::cout << "\n Symbol Table" << endl;
        for (int i = 0; i < symbolCount; i++)
        {
            std::cout << i + 1 << " " << ST[i].symbol << " " << ST[i].address << " " << endl;
            symbolFile << i + 1 << " " << ST[i].symbol << " " << ST[i].address << " " << endl;
        }
    }
    symbolFile.close();
}

//display literal table in terminal and in a file
void displayLiteralTable()
{
    fstream literalFile;
    literalFile.open("literalTableFile.txt", ios::out);
    if (literalFile.is_open())
    {
        literalFile << "\n Literal Table" << endl;
        std::cout << "\n Literal Table" << endl;

        for (int i = 0; i < literalTableCount; i++)
        {
            std::cout << i + 1 << " " << LT[i].literal << " " << LT[i].address << endl;
            literalFile << i + 1 << " " << LT[i].literal << " " << LT[i].address << endl;
        }
    }

    literalFile.close();
}
//display pool table in terminal and in a file
void displayPoolTable()
{
    fstream poolFile;
    poolFile.open("poolTableFile.txt", ios::out);
    if (poolFile.is_open())
    {
        poolFile << "\n Pool Table" << endl;
        std::cout << "\n Pool Table" << endl;

        for (int i = 0; i < poolTableCount; i++)
        {
            std::cout << i + 1 << " " << PT[i].start << " " << PT[i].count << endl;
            poolFile << i + 1 << " " << PT[i].start << " " << PT[i].count << endl;
        }
    }

    poolFile.close();
}

//display error in terminal and in a file
void displayError() 
{

    for (int i = 0; i < symbolCount; i++)
    {
        if (ST[i].address == -1)
        {
            errorCount++;
            errorLine.push_back("No declaration of " + ST[i].symbol);
        }
    }

    fstream errorFile;
    errorFile.open("errorFile.txt", ios::out);
    cout << "\n Error File\n";
    errorFile << "\n Error File\n";
    for (int i = 0; i < errorLine.size(); i++)
    {
        cout << i + 1 << "\t" << errorLine[i] << "\n";
        errorFile << i + 1 << "\t" << errorLine[i] << "\n";
    }
    errorFile.close();
}