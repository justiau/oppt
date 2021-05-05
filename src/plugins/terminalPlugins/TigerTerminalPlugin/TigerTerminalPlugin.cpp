/**
 * Copyright 2017
 * 
 * This file is part of On-line POMDP Planning Toolkit (OPPT).
 * OPPT is free software: you can redistribute it and/or modify it under the terms of the 
 * GNU General Public License published by the Free Software Foundation, 
 * either version 2 of the License, or (at your option) any later version.
 * 
 * OPPT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with OPPT. 
 * If not, see http://www.gnu.org/licenses/.
 */
#include "oppt/plugin/Plugin.hpp"

namespace oppt
{
class TigerTerminalPlugin: public TerminalPlugin
{
public:
    TigerTerminalPlugin():
        TerminalPlugin() {
    }

    virtual ~TigerTerminalPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        debug::show_message("load called from terminal plugin");
        return true;
    }

    virtual ValidityReportSharedPtr isValid(const PropagationResultSharedPtr& propagationResult) override {
        debug::show_message("isvalid called from terminal plugin");
        ValidityReportSharedPtr vr(new ValidityReport(propagationResult->nextState));        
        VectorFloat stateVec = propagationResult->nextState->as<VectorState>()->asVector();
        vr->isValid = true;
        return vr;
    }

    virtual bool isTerminal(const PropagationResultSharedPtr& propagationResult) override {
        debug::show_message("isterminal called from observation plugin");
        if (!isValid(propagationResult)->isValid) {
            debug::show_message("1");
            return true;        
        }
        VectorFloat stateVec = propagationResult->nextState->as<VectorState>()->asVector();
        if (stateVec[0] > 2) {
            debug::show_message("2");
            return true;
        }
        debug::show_message("3");
        return false;
    }
    
};

OPPT_REGISTER_TERMINAL_PLUGIN(TigerTerminalPlugin)
}
