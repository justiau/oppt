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
#include "plugins/pomdpxUtils/PomdpxUtils.hpp"

namespace oppt
{
class PomdpxRewardPlugin: public RewardPlugin
{
public:
    PomdpxRewardPlugin():
        RewardPlugin() {
    }

    virtual ~PomdpxRewardPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        parseOptions_<PomdpxOptions>(optionsFile);
        PomdpxOptions* generalOptions = static_cast<PomdpxOptions*>(options_.get());
        stepPenalty = generalOptions->stepPenalty;
        exitReward = generalOptions->exitReward;
        illegalMovePenalty = generalOptions->illegalMovePenalty;
        return true;
    }

    virtual FloatType getReward(const PropagationResultSharedPtr& propagationResult) const override {
        VectorFloat previousStateVector = propagationResult->previousState->as<VectorState>()->asVector();
        VectorFloat currentStateVector = propagationResult->nextState->as<VectorState>()->asVector();
        VectorFloat actionVec = propagationResult->action->as<VectorAction>()->asVector();
        if (actionVec[0] < 2.25) {
            if ((int) actionVec[0] + 0.25 == (int) previousStateVector[0] + 0.25) {
                // opened door with tiger
                return -100.0;
            } else {
                // opened different door
                return 10.0;
            }
        }
        // agent chose to listen
        return -1.0;
    }

    virtual std::pair<FloatType, FloatType> getMinMaxReward() const override {
        return std::make_pair(-100.0, 10.0);
    }

private:
    FloatType stepPenalty;
    FloatType exitReward;
    FloatType illegalMovePenalty;
};

OPPT_REGISTER_REWARD_PLUGIN(PomdpxRewardPlugin)
}
