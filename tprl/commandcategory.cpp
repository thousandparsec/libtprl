/* ReadLine Command - c++ wrapper around categories for readline
 *  Copyright (C) 2006  Lee Begg and the Thousand Parsec Project
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */
#include <iostream>
#include <algorithm>
#include <cctype>

#include "commandcategory.h"

namespace tprl{

CommandCategory::CommandCategory(const std::string& catname, const std::string& cathelp): RLCommand(), commands(){
    name = catname;
    help = cathelp;
}


CommandCategory::~CommandCategory()
{}


void CommandCategory::action(const std::string& cmdstring){
    std::string cmdlower = cmdstring;
    std::transform(cmdlower.begin(), cmdlower.end(), std::inserter(cmdlower, cmdlower.begin()), tolower);
    bool handled = false;
    for(std::set<RLCommand*>::iterator itcurr = commands.begin(); itcurr != commands.end(); ++itcurr){
        if(cmdlower.find((*itcurr)->getName()) == 0){
            handled = true;
            if((*itcurr)->getName().length() + 1 < cmdstring.length()){
              (*itcurr)->action(cmdstring.substr((*itcurr)->getName().length() + 1, cmdstring.npos));
            }else{
              (*itcurr)->action("");
            }
        }
    }
    if(!handled){
        std::cout << "\"" << name << " " << cmdstring << "\" is not a command, see \"help " << name 
            << "\" for commands in this category" << std::endl;
    }
}

void CommandCategory::add(RLCommand *cmd){
    commands.insert(cmd);
}

}
