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
#ifndef _TIGER_INITIAL_STATE_SAMPLER_PLUGIN_HPP_
#define _TIGER_INITIAL_STATE_SAMPLER_PLUGIN_HPP_
#include "oppt/plugin/Plugin.hpp"
#include "TigerInitialBeliefOptions.hpp"

namespace oppt
{
class TigerInitialBeliefPlugin: public InitialBeliefPlugin
{
public:
    TigerInitialBeliefPlugin():
        InitialBeliefPlugin() {
    }

    virtual ~TigerInitialBeliefPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        parseOptions_<TigerInitialBeliefOptions>(optionsFile);        
        return true;
    }

    virtual RobotStateSharedPtr sampleAnInitState() override {
        auto options = static_cast<TigerInitialBeliefOptions*>(options_.get());
        VectorFloat initStateVec = options->initialStateVec;
        unsigned int stateDimension = robotEnvironment_->getRobot()->getStateSpace()->getNumDimensions();
        if (initStateVec.size() != stateDimension)
            debug::show_message()
            debug::show_message(debug::to_string(initStateVec.size()));
            debug::show_message("test");
            debug::show_message(debug::to_string(stateDimension));
            ERROR("Init state size doesnt fit");
        std::uniform_int_distribution<unsigned int> d(0, 1);
        auto randomGenerator = robotEnvironment_->getRobot()->getRandomEngine();

        // Tiger is behind doors with equal probability
        for (size_t i = 0; i != stateDimension; ++i) {
            initStateVec[i] = (FloatType)d(*(randomGenerator.get()));
        }

        RobotStateSharedPtr initState(new VectorState(initStateVec));
        return initState;
    }
};

OPPT_REGISTER_INITIAL_BELIEF_PLUGIN(TigerInitialBeliefPlugin)

}

#endif
