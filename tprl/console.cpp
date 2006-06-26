//
// C++ Implementation: console
//
// Description:
//
//
// Author: Lee Begg <llnz@paradise.net.nz>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <readline/readline.h>
#include <readline/history.h>

#include <iostream>
#include <iomanip>

#include "console.h"

namespace tprl
{

  Console* Console::instance = NULL;
  
static void linecomplete(char* line){
  Console::getConsole()->finishedReadingLine(line);
}

static char** word_completion(const char* text, int start, int end){
  return Console::getConsole()->wordCompletion(text, start, end);
}

static char* command_generator(const char* text, int state){
  return Console::getConsole()->commandCompleter(text, state);
}

  Console::Console() : prompt(""){
    nonblocking = false;
    usehistory = false;
    lastlinewasnull = false;
    rl_attempted_completion_function = word_completion;
  }


  Console::~Console(){
    if(nonblocking){
      readLine_nb_stop();
    }
  }

  Console* Console::getConsole(){
    if(instance == NULL)
      instance = new Console();
    return instance;
  }
  
  void Console::setUseHistory(bool on){
    usehistory = on;
  }
  
  void Console::setPrompt(const std::string np){
    prompt = np;
  }

  void Console::setCommandSet(std::set<RLCommand*>* set){
    commands = set;
  }
  
  void Console::readLine(){
    char* cmd = readline(prompt.c_str());
    finishedReadingLine(cmd);
  }
  
  void Console::readLine_nb_start(){
    nonblocking = true;
    rl_callback_handler_install(prompt.c_str(), linecomplete);
  }
  
  void Console::readLine_nb_inputReady(){
    rl_callback_read_char();
  }
  
  void Console::readLine_nb_stop(){
    rl_callback_handler_remove();
    nonblocking = false;
  }
  
  bool Console::lastLineWasNull() const{
    return lastlinewasnull;
  }
  
  void Console::finishedReadingLine(char* line){
    if(line != NULL){
      if(usehistory){
        add_history(line);
      }
      
      if(commands != NULL){
        std::string cmdstring = line;
        std::string cmdlower = cmdstring;
        std::transform(cmdlower.begin(), cmdlower.end(), std::inserter(cmdlower, cmdlower.begin()), tolower);
        bool handled = false;
        if(cmdlower.find("help") == 0){
          if(cmdstring.length() <= 5){
            uint32_t maxColWidth = 0;
            for(std::set<RLCommand*>::iterator itcurr = commands->begin(); itcurr != commands->end(); ++itcurr){
              if((*itcurr)->getName().length() > maxColWidth){
                maxColWidth = (*itcurr)->getName().length();
              }
            }
            for(std::set<RLCommand*>::iterator itcurr = commands->begin(); itcurr != commands->end(); ++itcurr){
              std::cout << std::setw(maxColWidth) << (*itcurr)->getName() << std::setw(0) << "\t" << (*itcurr)->getHelp() << std::endl;
            }
            std::cout << std::setw(maxColWidth) << "help" << std::setw(0) << "\t" << "Prints out the help for this program" << std::endl;
          }else{
            cmdstring = cmdstring.substr(5, cmdstring.npos);
            std::string cmdlower = cmdstring;
            std::transform(cmdlower.begin(), cmdlower.end(), std::inserter(cmdlower, cmdlower.begin()), tolower);
            for(std::set<RLCommand*>::iterator itcurr = commands->begin(); itcurr != commands->end(); ++itcurr){
              if(cmdlower.find((*itcurr)->getName()) == 0){
                handled = true;
                if((*itcurr)->getName().length() + 1 < cmdstring.length()){
                  //sub items?
                  std::cout << (*itcurr)->getHelp() << std::endl;
                }else{
                  std::cout << (*itcurr)->getHelp() << std::endl;
                }
              }
            }
            if(!handled){
              if(cmdlower.find("help") == 0){
                std::cout << "Prints out the help for this program" << std::endl;
              }else{
                uint32_t maxColWidth = 0;
                for(std::set<RLCommand*>::iterator itcurr = commands->begin(); itcurr != commands->end(); ++itcurr){
                  if((*itcurr)->getName().length() > maxColWidth){
                    maxColWidth = (*itcurr)->getName().length();
                  }
                }
                for(std::set<RLCommand*>::iterator itcurr = commands->begin(); itcurr != commands->end(); ++itcurr){
                  std::cout << std::setw(maxColWidth) << (*itcurr)->getName() << std::setw(0) << "\t" << (*itcurr)->getHelp() << std::endl;
                }
              }
            }
          }
        }else{
          for(std::set<RLCommand*>::iterator itcurr = commands->begin(); itcurr != commands->end(); ++itcurr){
            if(cmdlower.find((*itcurr)->getName()) == 0){
              handled = true;
              if((*itcurr)->getName().length() + 1 < cmdstring.length()){
                (*itcurr)->action(cmdstring.substr((*itcurr)->getName().length() + 1, cmdstring.npos));
              }else{
                (*itcurr)->action("");
              }
            }
          }
        }
        if(!handled){
          //TODO
        }
      
      }
      
      free(line);
      lastlinewasnull = false;
    }else{
      lastlinewasnull = true;
    }
  }
  
  char** Console::wordCompletion(const char* text, int start, int end){
    char** rtv = NULL;
    if(commands != NULL){
      //TODO
    }
    return rtv;
  }
  
  char* Console::commandCompleter(const char* text, int state){
    //TODO
  }
  
}
