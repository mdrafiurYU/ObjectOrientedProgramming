/* 
 * File:   Rparser.h
 * Author: rashidmd
 *
 * Created on October 31, 2013, 3:11 AM
 */

/* 
 * File:   Rparser.h
 * Author: rashidmd
 *
 * Created on August 19, 2013, 11:33 AM
 */

#ifndef RPARSER_H
#define	RPARSER_H

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <cstddef>
#include <cmath>

#include "Node.h"
#include "Resistor.h"
#include "NodeList.h"
#include "ResistorList.h"
#include "easygl.h"

using namespace std;

#define NODEID_ARRAY_SIZE 2

// Keyword for 'printR', 'printNode' and 'deleteR' command
#define KEYWORD "all"

#define MIN_ITERATION_CHANGE 0.0001

#define INITIAL_NODE_VOLTAGE 0

#define VOLTAGE_KNOWN true

#define VOLTAGE_UNKNOWN false

extern easygl window;
extern NodeList* g_NodeListPtr;

// Functions for parsing each command 
void parse_insertR (stringstream &lineStream, NodeList &listHead);
void parse_setV (stringstream &lineStream, NodeList &listHead);
void parse_unsetV (stringstream &lineStream, NodeList &listHead);
void parse_modifyR (stringstream &lineStream, NodeList &listHead);
void parse_printR (stringstream &lineStream, NodeList &listHead);
void parse_printNode (stringstream &lineStream, NodeList &listHead);
void parse_deleteR (stringstream &lineStream, NodeList &listHead);
void solveNetwork (NodeList &listHead);
void parse_draw (NodeList &listHead);

#endif	/* RPARSER_H */

