/* 
 * File:   Rparser.h
 * Author: rashidmd
 *
 * Created on October 7, 2013, 1:02 PM
 */

#ifndef RPARSER_H
#define	RPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstddef>

#include "Node.h"
#include "Resistor.h"

// Counts the number of resistors already added
extern int resCount;

// Size for the node array; node indices are from 0 to maxNodeNumber, inclusive
extern int maxNodeNumber;

// size for the resistor array; accommodates exactly maxResistors number of resistors in the program
extern int maxResistors;

extern Node *nodeArray;
extern Resistor *resistorArray;

using namespace std;

// Keyword for 'printR', 'printNode' and 'deleteR' command
#define KEYWORD "all"

void parser();

// Functions for parsing each command 
void parse_maxVal (stringstream &lineStream);
void parse_insertR (stringstream &lineStream);
void parse_modifyR (stringstream &lineStream);
void parse_printR (stringstream &lineStream);
void parse_printNode (stringstream &lineStream);
void parse_deleteR (stringstream &lineStream);

// Helper functions to parse and print error messages for each type of argument
bool isValidMaxValue (stringstream &lineStream, int maxValue);
bool isValidNodeID (stringstream &lineStream, int nodeid);
bool isKeyword (stringstream &lineStream, string arg);
bool foundResistor (string resName, int &index);
void resetAll();

#endif	/* RPARSER_H */
