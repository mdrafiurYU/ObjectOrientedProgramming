/* 
 * File:   main.cpp
 * Author: rashidmd
 *
 * Created on October 31, 2013, 3:06 AM
 */

#include "Rparser.h"

int main() {

    NodeList listHead;
    string inputLine, command;

    // Prompt and get input from standard input
    cout << "> ";
    getline(cin, inputLine);
   
    // If the first set of input is not EOF, start parsing it. Keep parsing until EOF.
    while ( !cin.eof() )
    {    
        // Put the line in a linestream for parsing
        stringstream lineStream (inputLine);
        lineStream >> command;
       
        if (command == "insertR") 
        {
            parse_insertR (lineStream, listHead);
        }
        
        else if (command == "setV") 
        {
            parse_setV (lineStream, listHead);
        }
        
        else if (command == "unsetV") 
        {
            parse_unsetV (lineStream, listHead);
        }
        
        else if (command == "solve") 
        {
            solveNetwork (listHead);
        }
        
        else if (command == "modifyR") 
        {
            parse_modifyR (lineStream, listHead);
        }

        else if (command == "printR") 
        {
            parse_printR (lineStream, listHead);   
        }

        else if (command == "printNode") 
        {
            parse_printNode (lineStream, listHead);
        }
       
        else if (command == "deleteR")
        { 
            parse_deleteR (lineStream, listHead);
        }

        else if (command == "draw")
        {
            parse_draw (listHead);
        }
        
        // The command does not match one of the valid commands
        else
            cout << "Error: invalid command" << endl;

        // Prompt for next input
        cout << "> ";
        getline(cin, inputLine);
    }
   
   return 0;
}
