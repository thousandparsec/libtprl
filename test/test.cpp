//
// C++ Implementation: test
//
// Description: 
//
//
// Author: Lee Begg <llnz@paradise.net.nz>, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <tprl/rlcommand.h>
#include <tprl/commandalias.h>
#include <tprl/commandcategory.h>
#include <tprl/console.h>

using namespace tprl;

bool timetoend;

class QuitCommand : public RLCommand{
  public:
    QuitCommand() : RLCommand(){
      name = "quit";
      help = "Quit and shutdown the server.";
    }
    void action(const std::string& cmdline){
      timetoend = true;
    }
};

int main(int argc, char** argv){
  timetoend = false;
  Console *console = Console::getConsole();
  
  std::set<RLCommand*> commands;
  
  RLCommand* quit = new QuitCommand();
  commands.insert(quit);
  CommandAlias* alias = new CommandAlias("exit");
  alias->setTarget(quit);
  commands.insert(alias);
  
  console->setCommandSet( &commands);
  
  while(!timetoend){
    console->readLine();
  }

  delete console;
  
  return 0;
}
