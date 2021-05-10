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
class TigerRewardPlugin: public RewardPlugin
{
public:
    TigerRewardPlugin():
        RewardPlugin() {

    }

    virtual ~TigerRewardPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        return true;
    }

    virtual FloatType getReward(const PropagationResultSharedPtr& propagationResult) const override {
        VectorFloat previousStateVector = propagationResult->previousState->as<VectorState>()->asVector();
        VectorFloat currentStateVector = propagationResult->nextState->as<VectorState>()->asVector();
        VectorFloat actionVec = propagationResult->action->as<VectorAction>()->asVector();

        // If we moved out of the right side of the map, return reward 10
        // if (currentStateVector[0] > 7.5) {
        //     return 10.0;
        // } else if (currentStateVector[0] < 0.5 || currentStateVector[0] > 8.5 || currentStateVector[1] < 0.5 || currentStateVector[1] > 7.5) {
        //     // Illegal move => return penalty
        //     return -10.0;
        // }

        // switch ((unsigned int)(actionVec[0] + 0.25)) {
        // case 5: return sampleRockAtCurrentLocation(previousStateVector, currentStateVector, actionVec);
        //     break;
        // default: return 0.0;
        //     break;
        // }
        return -1.0;
    }

    virtual std::pair<FloatType, FloatType> getMinMaxReward() const override {
        return std::make_pair(-10.0, 10.0);
    }

};

OPPT_REGISTER_REWARD_PLUGIN(TigerRewardPlugin)
}
