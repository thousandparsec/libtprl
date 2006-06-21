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
#ifndef COMMANDCATEGORY_H
#define COMMANDCATEGORY_H

#include <rlcommand.h>

#include <string>
#include <set>

/**
	@author Lee Begg <llnz@paradise.net.nz>
*/
class CommandCategory : public RLCommand
{
public:
    CommandCategory(const std::string& catname, const std::string& cathelp);
    virtual ~CommandCategory();
    
    virtual void action(const std::string& cmdstring);
    
    void add(RLCommand* cmd);
    
private:
    std::set<RLCommand*> commands;

};

#endif
