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
    void setCatchSignals(bool on);
    void setCompletionFinished(bool on);
    
    void setCommandSet(std::set<RLCommand*> *set);
    std::set<RLCommand*> * getCommandSet() const;
    
    void redrawLine();
    
    void readLine();
    
    void readLine_nb_start();
    void readLine_nb_inputReady();
    void readLine_nb_stop();
    
    bool lastLineWasNull() const;
    
    //internal public stuff
    friend void linecomplete(char* line);
    friend char** word_completion(const char* text, int start, int end);

  protected:
    void finishedReadingLine(char* line);
    char** wordCompletion(const char* text, int start, int end);
    
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
