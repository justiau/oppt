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
#ifndef _POMDPX_INITIAL_STATE_SAMPLER_PLUGIN_HPP_
#define _POMDPX_INITIAL_STATE_SAMPLER_PLUGIN_HPP_
#include "oppt/plugin/Plugin.hpp"
#include "plugins/pomdpxUtils/PomdpxUtils.hpp"

namespace oppt
{
class PomdpxInitialBeliefPlugin: public InitialBeliefPlugin
{
public:
    PomdpxInitialBeliefPlugin():
        InitialBeliefPlugin(){
    }

    virtual ~PomdpxInitialBeliefPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        parseOptions_<PomdpxOptions>(optionsFile);
        PomdpxOptions* generalOptions = static_cast<PomdpxOptions*>(options_.get());
        lowerBound = generalOptions->lowerBound;
        upperBound = generalOptions->upperBound;
        // unsigned int numDimensions = robotEnvironment_->getRobot()->getStateSpace()->getNumDimensions();
        // if (options->lowerBound.size() != numDimensions)
        //     ERROR("Lower bound for the uniform distribution doesn't match state space dimension");
        // if (options->upperBound.size() != numDimensions)
        //     ERROR("Upper bound for the uniform distribution doesn't match state space dimension");
        // for (size_t i = 0; i != options->lowerBound.size(); ++i) {
        //     if (options->lowerBound[i] > options->upperBound[i])
        //         ERROR("Lower bound for initial belief must be smaller than upper bound");
        // }
        return true;
    }

    virtual RobotStateSharedPtr sampleAnInitState() override {
        std::uniform_int_distribution<unsigned int> dist(lowerBound[0],upperBound[0]);
        auto randomGenerator = robotEnvironment_->getRobot()->getRandomEngine();
        VectorFloat initStateVec = VectorFloat({dist(*(randomGenerator.get()))});
        unsigned int stateDimension = robotEnvironment_->getRobot()->getStateSpace()->getNumDimensions();
        if (initStateVec.size() != stateDimension)
            ERROR("Init state size doesnt fit");
        RobotStateSharedPtr initState(new VectorState(initStateVec));
        return initState;
    }

private:
    VectorFloat lowerBound;
    VectorFloat upperBound;
};

OPPT_REGISTER_INITIAL_BELIEF_PLUGIN(PomdpxInitialBeliefPlugin)

}

#endif
