#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstddef>

using namespace std;

#define MAX_NODE_NUMBER 5000
#define MIN_NODE_NUMBER 0
#define KEYWORD "all"

void parse_insertR (stringstream &lineStream);
void parse_modifyR (stringstream &lineStream);
void parse_printR (stringstream &lineStream);
void parse_printNode (stringstream &lineStream);
void parse_deleteR (stringstream &lineStream);

bool isValidName (stringstream &lineStream, string name);
bool isValidResistance (stringstream &lineStream, double resistance);
bool isValidNodeID (stringstream &lineStream, int nodeid);
bool isSameNodeID(int nodeid_1, int nodeid_2);
bool isExtraArgs (stringstream &lineStream);
bool isKeyword (stringstream &lineStream, string arg, bool &missing_arg);

int main() 
{
    string inputLine, command;

    cout << "> ";
    getline(cin, inputLine);

    std::string whitespaces (" \t\f\v\n\r");

    std::size_t found = inputLine.find_last_not_of (whitespaces);
    if ( found!=std::string::npos )
        inputLine.erase (found + 1);
    else
        inputLine.clear (); 
    
    while ( !cin.eof() )
    {    
        stringstream lineStream (inputLine);
        lineStream >> command;
        
        if (command == "insertR") 
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

        else 
        {
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            cerr << "Error: invalid command" << endl;
        }

        cout << "> ";
        getline(cin, inputLine);
        std::string whitespaces (" \t\f\v\n\r");

        std::size_t found = inputLine.find_last_not_of (whitespaces);
        if ( found!=std::string::npos )
            inputLine.erase (found + 1);
        else
            inputLine.clear (); 
    }
    
    return 0;
}

void parse_insertR (stringstream &lineStream) 
{
    string name;
    double resistance;
    int nodeid_1, nodeid_2;
    
    lineStream >> name;  
    if ( !isValidName (lineStream, name) )
        return;
            
    lineStream >> resistance;   
    if ( !isValidResistance (lineStream, resistance) )
        return;
            
    lineStream >> nodeid_1;
    if ( !isValidNodeID (lineStream, nodeid_1) )
        return;
            
    lineStream >> nodeid_2;
    if ( !isValidNodeID (lineStream, nodeid_2) )
        return;
            
    if( isSameNodeID(nodeid_1, nodeid_2) )
        return;
    
    if ( isExtraArgs (lineStream) )
        return;
          
    std::cout << std::fixed;
    cout << "Inserted: resistor " << name << " ";
    std::cout << std::setprecision(2) << resistance << " Ohms " << nodeid_1 << " -> " << nodeid_2 << endl;
}

void parse_modifyR (stringstream &lineStream) 
{    
    string name;
    double resistance;

    lineStream >> name;   
    if ( !isValidName (lineStream, name) )
        return;
            
    lineStream >> resistance;   
    if ( !isValidResistance (lineStream, resistance) )
        return;
            
    if ( isExtraArgs (lineStream) )
        return;
                
    std::cout << std::fixed;
    cout << "Modified: resistor " << name << " to ";
    std::cout << std::setprecision(2) << resistance << " Ohms" << endl;
}

void parse_printR (stringstream &lineStream)
{
    string resName;
    bool missing_arg = false;
    
    lineStream >> resName;  
    if( isKeyword(lineStream, resName, missing_arg) )
    {       
        if ( isExtraArgs (lineStream) )
            return;
        
        cout << "Print: all resistors" << endl;
    }
    
    else
    {
        if(missing_arg)
            return;
        
        if ( isExtraArgs (lineStream) )
            return;
        
        cout << "Print: resistor " << resName << endl;
    }
}

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789") == std::string::npos;
}

void parse_printNode (stringstream &lineStream)
{
    int nodeid;
    string argument;
    bool missing_arg = false;
    
    lineStream >> argument;
    if( !is_digits(argument) )
    {
        if( isKeyword(lineStream, argument, missing_arg) )
        {       
            if ( isExtraArgs (lineStream) )
                return;

            cout << "Print: all nodes" << endl;   
        }
        
        else
            cerr << "Error: invalid argument" << endl;
    }
    
    else
    {
        if(missing_arg)
            return;
        
        istringstream (argument) >> nodeid;
        if ( isValidNodeID(lineStream, nodeid) )
        {
            if ( isExtraArgs (lineStream) )
                return;
        
            cout << "Print: node " << nodeid << endl;
        }     
    }
}

void parse_deleteR (stringstream &lineStream)
{
    string resName;
    bool missing_arg = false;
    
    lineStream >> resName;  
    if( isKeyword(lineStream, resName, missing_arg) )
    {       
        if ( isExtraArgs (lineStream) )
            return;
        
        cout << "Deleted: all resistors" << endl;
    }
    
    else
    {   
        if(missing_arg)
            return;
        
        if ( isExtraArgs (lineStream) )
            return;
        
        cout << "Deleted: resistor " << resName << endl;
    }
}

bool isValidName (stringstream &lineStream, string name)
{
    bool missing_arg = true;
    
    if (lineStream.fail()) 
    {
        lineStream.clear();
        lineStream.ignore(1000, '\n'); 
        cerr << "Error: too few arguments" << endl;
        return false;
    }
    
    else if( isKeyword(lineStream, name, missing_arg) )
    {
        cerr << "Error: resistor name cannot be the keyword \"all\"" << endl;
        return false;
    }
        
    else
        return true;
}

bool isValidResistance (stringstream &lineStream, double resistance)
{
    if (lineStream.fail()) 
    {
        if (lineStream.eof()) 
        {
            lineStream.clear();
            lineStream.ignore(1000, '\n'); 
            cerr << "Error: too few arguments" << endl;
            return false;
        }

        else
        {
            lineStream.clear();
            lineStream.ignore(1000, '\n'); 
            cerr << "Error: invalid argument" << endl;
            return false;
        }
    }

    else if (resistance < 0.0)
    {
        cerr << "Error: negative resistance" << endl;
        return false;
    }

    else
        return true;
}

bool isValidNodeID (stringstream &lineStream, int nodeid)
{           
    if ( lineStream.fail() ) 
    {
        if ( lineStream.eof() ) 
        {
            lineStream.clear();
            lineStream.ignore(1000, '\n'); 
            cerr << "Error: too few arguments" << endl;
            return false;
        }
                
        else 
        {
            lineStream.clear();
            lineStream.ignore(1000, '\n');
            cerr << "Error: invalid argument" << endl;
            return false;
        }
    }

    else if (nodeid < MIN_NODE_NUMBER || nodeid > MAX_NODE_NUMBER)
    {
        cerr << "Error: node " << nodeid << " is outside permitted range " << MIN_NODE_NUMBER << "-" << MAX_NODE_NUMBER << endl;
        return false;
    }

    else 
        return true;
}

bool isSameNodeID(int nodeid_1, int nodeid_2)
{
    if(nodeid_1 == nodeid_2)
    {
        cerr << "Error: both terminals of resistor connect to node " << nodeid_1 << endl;
        return true;
    }
    
    return false;
}

bool isExtraArgs (stringstream &lineStream)
{
    if ( !lineStream.eof() )
    {
        lineStream.clear();
        lineStream.ignore(1000, '\n'); 
        cerr << "Error: too many arguments" << endl;
        return true;
    }

    return false;
}

bool isKeyword (stringstream &lineStream, string arg, bool &missing_arg) 
{
    if ( lineStream.fail() ) 
    {
        lineStream.clear();
        lineStream.ignore(1000, '\n'); 
        cerr << "Error: too few arguments" << endl;
        missing_arg = true;
        return false;
    }  
    
    if ( arg != KEYWORD )
        return false;
    
    return true;
}
