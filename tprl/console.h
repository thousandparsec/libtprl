//
// C++ Interface: console
//
// Description:
//
//
// Author: Lee Begg <llnz@paradise.net.nz>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef TPRL_CONSOLE_H
#define TPRL_CONSOLE_H

#include <string>
#include <set>
#include <tprl/rlcommand.h>

namespace tprl
{

  /**
  Singleton object that represents the console, and deals with the low level details of readline.
   
  	@author Lee Begg <llnz@paradise.net.nz>
  */
  class Console
  {
  public:
    static Console* getConsole();
    
    ~Console();
    
    void setUseHistory(bool on);
    void setPrompt(const std::string np);
    void setCommandSet(std::set<RLCommand*> *set);
    
    void readLine();
    
    void readLine_nb_start();
    void readLine_nb_inputReady();
    void readLine_nb_stop();
    
    bool lastLineWasNull() const;
    
    //internal public stuff
    void finishedReadingLine(char* line);
    char** wordCompletion(const char* text, int start, int end);
    char* commandCompleter(const char* text, int state);

  private:
    Console();
    static Console* instance;
    bool nonblocking;
    bool usehistory;
    bool lastlinewasnull;
    std::string prompt;
    std::set<RLCommand*> *commands;

  };

}

#endif
