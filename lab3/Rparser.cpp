#include "Rparser.h"

int resCount = 0;
int maxNodeNumber = 0;
int maxResistors = 0;

Node *nodeArray = NULL;
Resistor *resistorArray = NULL;

int num_maxValCalled = 0;

void parser() 
{
    string inputLine, command;

    // Prompt and get input from standard input
    cout << "> ";
    getline(cin, inputLine);

    // Removes leading and trailing whitespaces from a string
    string whitespaces (" \t");

    size_t found = inputLine.find_last_not_of (whitespaces);
    if ( found != string::npos )
        inputLine.erase (found + 1);

    else
        inputLine.clear (); 
    
    // If the first set of input is not EOF, start parsing it. Keep parsing until EOF.
    while ( !cin.eof() )
    {    
        // Put the line in a linestream for parsing
        stringstream lineStream (inputLine);
        lineStream >> command;
             
        if (command == "maxVal") 
        {
            parse_maxVal (lineStream);
        }
        
        else if (command == "insertR") 
        {
            parse_insertR (lineStream);
        }
        
        else if (command == "modifyR") 
        {
            parse_modifyR (lineStream);
        }

        else if (command == "printR") 
        {
            parse_printR (lineStream);   
        }

        else if (command == "printNode") 
        {
            parse_printNode (lineStream);
        }
        
        else if (command == "deleteR")
        {
            parse_deleteR (lineStream);
        }
		
        // The command does not match one of the valid commands
        else
            cout << "Error: invalid command" << endl;

        // Prompt for next input
        cout << "> ";
        getline(cin, inputLine);

        // Removes leading and trailing whitespace from a string 
        string whitespaces (" \t");
		
        std::size_t found = inputLine.find_last_not_of (whitespaces);
        if ( found != string::npos )
            inputLine.erase (found + 1);

        else
            inputLine.clear (); 
    }
    
    delete[] nodeArray;
    delete[] resistorArray;
}

/*
 * All the parse_<command> functions parse the arguments for the given command. Extracts the arguments from lineStream which 
 * is passed in by reference. As the function parse arguments from left to right they print an error message if any error 
 * occurs, and immediately return to prevent any further error messages from being printed. If it passes all the error 
 * checking functions, the line is valid and prints the appropriate output for that command.
*/
void parse_maxVal (stringstream &lineStream)
{
    lineStream >> maxNodeNumber;
    if(!isValidMaxValue(lineStream, maxNodeNumber))
        return;
    
    lineStream >> maxResistors;
    if(!isValidMaxValue(lineStream, maxResistors))
        return;
    
    if(num_maxValCalled < 1)
    {
        nodeArray = new Node[maxNodeNumber + 1];
        resistorArray = new Resistor[maxResistors];
    
        cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl;
        num_maxValCalled++;
    }
    
    else
    {
        resetAll();
        
        nodeArray = new Node[maxNodeNumber + 1];
        resistorArray = new Resistor[maxResistors];
        
        cout << "New network: max node number is " << maxNodeNumber << "; max resistors is " << maxResistors << endl;
        num_maxValCalled++;
    }
}

void parse_insertR (stringstream &lineStream) 
{
    string name;
    double resistance;
    int nodeid_1, nodeid_2;
    int nodeIDs[2];
    
    lineStream >> name >> resistance >> nodeid_1 >> nodeid_2;
    
    nodeIDs[0] = nodeid_1;
    nodeIDs[1] = nodeid_2;

    if(resCount < maxResistors)
    {
        *(resistorArray + resCount) = Resistor(resCount, name, resistance, nodeIDs);

        cout << std::fixed;
        cout << "Inserted: resistor " << name << " ";
        cout << std::setprecision(2) << resistance << " Ohms " << nodeid_1 << " -> " << nodeid_2 << endl;

        resCount++;
    }

    else
        cout << "Error: resistor array is full" << endl;


    if(!((nodeArray + nodeid_1)->addResistor(resCount)) || !((nodeArray + nodeid_2)->addResistor(resCount)))
        cout << "Error: node is full" << endl;

}


void parse_modifyR (stringstream &lineStream) 
{    
    string resName;
    double resistance;

    lineStream >> resName >> resistance;  
    
    int index = 0;
               
    if(!foundResistor(resName, index))
        cout << "Error: resistor " << resName << " not found" << endl;
               
    else
    {            
        cout << fixed;
        cout << "Modified: resistor " << resName << " from ";           
        cout << setprecision(2) << (resistorArray + index)->getResistance() << " to ";
        cout << setprecision(2) << resistance << " Ohms" << endl;

        (resistorArray + index)->setResistance(resistance);
    }
}


void parse_printR (stringstream &lineStream)
{
    string resName;
    
    lineStream >> resName;  
    if (isKeyword(lineStream, resName))
    {      
        cout << "Print:" << endl;
        for(int i = 0; i < resCount; i++)
            (resistorArray + i)->print();
    }
    
    else
    {   
        int index = 0;

        if(!foundResistor(resName, index))
            cout << "Error: resistor " << resName << " not found" << endl;

        else
        {
            cout << "Print:" << endl;
            (resistorArray + index)->print();
        }
    }
}

// Checks and returns 'true' if the given string type parameter is consists of only digits '0-9' or '-' sign; otherwise 'false'
bool is_digits (const string &str)
{
    return str.find_first_not_of("-0123456789") == string::npos;
}

void parse_printNode (stringstream &lineStream)
{
    int nodeid;
    string argument;
    
    lineStream >> argument;
    if (!is_digits(argument))
    {
        if( isKeyword(lineStream, argument) )
        {       
            cout << "Print:" << endl;
            for(int i = 0; i <= maxNodeNumber; i++)
                nodeArray[i].print(i);   
        }
        
        else
            cout << "Error: invalid argument" << endl;
    }
    
    else
    {
        istringstream (argument) >> nodeid;
        if (isValidNodeID(lineStream, nodeid))
        {
            cout << "Print:" << endl;
            (nodeArray + nodeid)->print(nodeid);
        }     
    }
}

void parse_deleteR (stringstream &lineStream)
{
    string arg;
    
    lineStream >> arg;  
        
    resetAll();
    cout << "Deleted: all resistors" << endl;
}

bool isValidMaxValue (stringstream &lineStream, int maxValue)
{
    if (maxValue < 0)
    {
        cout << "Error: maxVal arguments must be greater than 0" << endl;
        return false;
    }
    
    return true;
}

// Parse the 'nodeid' argument. If there is an error, print an error message and returns 'false'; Otherwise 'true'
bool isValidNodeID (stringstream &lineStream, int nodeid)
{    
    if (nodeid < MIN_NODE_NUMBER || nodeid > maxNodeNumber)
    {
        cout << "Error: node " << nodeid << " is out of permitted range " << MIN_NODE_NUMBER << "-" << maxNodeNumber << endl;
        return false;
    }

    return true;
}

// Checks the argument where the keyword 'all' is expected. Validates whether the given string parameter is missing or not a
// keyword and returns 'false'; returns 'true' if the keyword is found
bool isKeyword (stringstream &lineStream, string arg) 
{
    if (arg != KEYWORD)
        return false;
    
    return true;
}

bool foundResistor (string resName, int &index)
{
   while(index < resCount && ((resistorArray + index)->getName()).compare(resName) != 0)
       index++;
               
   return (index == resCount) ? false : true;
}

void resetAll()
{
    delete[] nodeArray;
    delete[] resistorArray;

    nodeArray = NULL;
    resistorArray = NULL;

    resCount = 0;
    maxNodeNumber = 0;
    maxResistors = 0;
}