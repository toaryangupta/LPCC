#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<regex>
#include <unordered_map>

#include<vector>

using namespace std;

bool macroStart=false;
int macroCount=0;
int mdtLineCount=0;

struct macroDetail{

    string name;
    int parameters=0;
    unordered_map<string,string> paramName;
    int mdtStartingLine;
}macroD[10];

vector<string>mdtTable;

void readFile();
void processFile(fstream &inFile);

int main() //main funcition
{
    readFile();

    return 0;
}


void readFile() //read input
{

    fstream inputFile;
    inputFile.open("sampleProgram.asm",ios::in);

    if(inputFile.is_open()){
        std::cout<<"\n Input read successfully";
        processFile(inputFile); //start processing
    }
    else{
        std::cout<<"\n Failed to read input file";
    }
    inputFile.close();
}

void processFile(fstream &inFile)
{
    string line,token;
    istringstream iss;
    vector<string> words;

    fstream intermediateFile;
    fstream expandedCode;
    fstream mntFile;
    fstream mdtFile;
    fstream formalVsPostional;
    fstream actualVsPositonal;

    int lineInMacro=0;

    //various file for output
    intermediateFile.open("intermediate.asm",ios::out);
    expandedCode.open("expandedCode.asm",ios::out);
    mntFile.open("mntFile.txt",ios::out);
    mdtFile.open("mdtFile.txt",ios::out);
    formalVsPostional.open("formalVsPostional.txt",ios::out);
    actualVsPositonal.open("actualVsPositonal.txt",ios::out);
   


    //loop though each line
    while(!inFile.eof())
    {
        
        vector<string> words;

        getline(inFile,line);
       
        iss.clear();
        iss.str(line);
        while(iss>>token)
        {
            words.push_back(token);
        }
        
        if(words[0]=="MACRO") //if macro defination occurs
        {
            macroStart=true;
            string macroName =words[1];
            for(int k=0;k<macroCount;k++)
            {
                if(macroD[k].name==macroName) //if duplicate then error
                {
                    std::cout<<"\n ERROR: duplicate macro name "<<macroName<<" \n";
                    break;
                }
            }
            macroD[macroCount].name=macroName; //add to macroDetails
           
            int paramCount=0;
         
            for(int i=2;i<words.size();i++) //check for parameters
            {
                if(words[i]==",")
                {
                    continue;
                }
                else if(words[i]==";")
                {
                    break;
                }
                else
                {
                    words[i]=words[i].substr(0,words[i].find(",",0));
                    macroD[macroCount].paramName[words[i]]=("#"+to_string(paramCount+1));
                    if(i==2)
                    {
                        formalVsPostional<<"....."<<macroName<<"....."<<"\n";
                    }
                    formalVsPostional<<words[i]<<" #"<<(paramCount+1)<<"\n";
                    paramCount++;
                }

            }
              mntFile<<macroName<<" "<<paramCount<<" "<<mdtLineCount+1<<"\n";
             macroD[macroCount].parameters=paramCount;
             macroD[macroCount].mdtStartingLine=mdtLineCount;
            macroCount++;
           continue;
        }
        else if(words[0]=="MEND")
        {
            macroStart=false;
            mdtFile<<words[0]<<"\n";
            mdtTable.push_back(words[0]);
           
            mdtLineCount++;
            continue;
        }

        if(macroStart==true) //process statements before mend
        {
           
            int macroCall=false;
            int mdtStartingPos;
            //checking for another micro call
            for(int k=0;k<macroCount;k++){
                if(macroD[k].name==words[0])
                {
                    macroCall=true;
                    mdtStartingPos=macroD[k].mdtStartingLine;
                    break;
                }
            }
            if(macroCall) //call within defination
            {
               
                istringstream istream;
                string token;
                actualVsPositonal<<"...."<<words[0]<<"....\n";

                //adding to actual vs postional for micro call
                for(int j=1;j<words.size();j++)
                {
                     
                     words[j]=words[j].substr(0,words[j].find(",",0));

                     actualVsPositonal<<words[j]<<" #"<<j<<"\n";

                }
                //copying things from mdt for macro call 
                for(int g=mdtStartingPos;g<mdtLineCount;g++)
                {
                    string thisLine="";
                    if(mdtTable[g]=="MEND")
                    {
                        break;
                    }
                    else
                    {
                        istream.clear();
                        istream.str(mdtTable[g]);
                        while(istream>>token)
                        {
                           
                            if(token[0]=='#')
                            {
                                
                                //getting positional parameter and putting actual parameter
                                token.erase(remove(token.begin(), token.end(), '#'), token.end()); 
                                int p=stoi(token);
                                 
                              words[p]=words[p].substr(0,words[p].find(",",0));
                                
                                mdtFile<<words[p]<<" ";
                               thisLine.append(words[p]+" ");
                                
                            }
                            else
                            {
                                mdtFile<<token<<" ";
                                 thisLine.append(token+" ");
                            }
                        }
                    }
                     mdtFile<<"\n";
                     mdtLineCount++;
                     mdtTable.push_back(thisLine);
                     
                }
            }
            else{ //add lines to mdt

                string thisLine="";
                for(int i=0;i<words.size();i++)
                {
                   
                    if(words[i]==";")
                    {
                        break;
                    }
                    else{
                        if(macroD[macroCount-1].paramName.find(words[i]) !=macroD[macroCount-1].paramName.end())
                        {
                            mdtFile<<macroD[macroCount-1].paramName[words[i]]<<" ";
                            thisLine.append((macroD[macroCount-1].paramName[words[i]])+" ");
                        }
                        else
                        {
                            mdtFile<<words[i]<<" ";
                            thisLine.append(words[i]+" ");
                        }
                    }
                }
                mdtLineCount++;
                mdtTable.push_back(thisLine);
                mdtFile<<"\n";
            }
          
        }
        else{       //if outside macro

            intermediateFile<<line<<"\n";
            bool presentInMnt=false;
            int startLineInMDT;

            for(int k=0;k<macroCount;k++)
            {
                if(macroD[k].name==words[0])
                {
                    presentInMnt=true; 
                    startLineInMDT=macroD[k].mdtStartingLine; 
                    break;
                }
            }

            if(presentInMnt)
            {
                int totalword=words.size();
                istringstream istream;
                //adding to  actual vs positional
                actualVsPositonal<<"...."<<words[0]<<"....\n";
                for(int j=1;j<words.size();j++)
                {
                     
                     words[j]=words[j].substr(0,words[j].find(",",0));

                     actualVsPositonal<<words[j]<<" #"<<j<<"\n";

                }

                for(int g=startLineInMDT;g<mdtLineCount;g++)
                {
                    if(mdtTable[g]=="MEND")
                    {
                        break;
                    }
                    else
                    {
                          istream.clear();
                        istream.str(mdtTable[g]);
                        while(istream>>token)
                        {
                           
                            if(token[0]=='#')
                            {
                                
                                token.erase(remove(token.begin(), token.end(), '#'), token.end()); 
                                int p=stoi(token);
                                // cout<<"p"<<p;
                                // cout<<"  word  "<<words[p];
                                 
                              words[p]=words[p].substr(0,words[p].find(",",0));
                                
                                expandedCode<<words[p]<<" ";
                            }
                            else
                            {
                                expandedCode<<token<<" ";
                            }
                        }   
                    }
                    expandedCode<<"\n";
                }

            }
            else
            {
                expandedCode<<line<<"\n";
            }

           

        }
        

    }

    intermediateFile.close();
    mntFile.close();
    mdtFile.close();
    expandedCode.close();
    formalVsPostional.close();
    actualVsPositonal.close();

    // cout<<"   thing in mdt \n";
    // cout<<mdtLineCount<<"  ----  "<<mdtTable.size()<<endl;
    // for(int g=0;g<mdtTable.size();g++)
    // {
    //     cout<<mdtTable[g]<<endl;
    // }


}