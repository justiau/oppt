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
#include "oppt/opptCore/Distribution.hpp"
#include "TigerObservationPluginOptions.hpp"

namespace oppt
{
class TigerObservationPlugin: public ObservationPlugin
{
public :
    TigerObservationPlugin():
        ObservationPlugin() {
    }

    virtual ~TigerObservationPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        parseOptions_<TigerObservationPluginOptions>(optionsFile);

        // The observationError parameter acts as the efficiency distance here
        observationError_ =
            static_cast<TigerObservationPluginOptions*>(options_.get())->observationError;
        return true;
    }

    virtual ObservationResultSharedPtr getObservation(const ObservationRequest* observationRequest) const override {
        ObservationResultSharedPtr observationResult = std::make_shared<ObservationResult>();

        // Get the observation
        VectorFloat stateVec = observationRequest->currentState->as<VectorState>()->asVector();
        VectorFloat actionVec = observationRequest->action->as<VectorAction>()->asVector();
        VectorFloat observationVec(robotEnvironment_->getRobot()->getObservationSpace()->getNumDimensions(), 0.0);
        if (actionVec[0] == 3.0) {
            FloatType probability = 1.0 - observationError_;
            bool obsMatches =
                std::bernoulli_distribution(
                    probability)(*(robotEnvironment_->getRobot()->getRandomEngine().get()));
            int binNum;
            tie(observationVec[0], binNum) = getObsFromState(stateVec[0], obsMatches);
            auto observationSpace = robotEnvironment_->getRobot()->getObservationSpace();
            ObservationSharedPtr observation = std::make_shared<DiscreteVectorObservation>(observationVec);
            observation->as<DiscreteVectorObservation>()->setBinNumber(binNum);
            observationResult->observation = observation;
            observationResult->errorVector = observationRequest->errorVector;
        }
        return observationResult;
    }

private:
    FloatType observationError_;

private:
    std::tuple<std::string, int> getObsFromState(double state, bool isMatch) {
        std::string dir = state.substr(state.find("-")+1);
        std::string newDir;
        if (isMatch) {
            newDir = dir;
        } else {
            if (dir == "left") newDir = "right";
            else newDir = "left";
        }
        int bin = (newDir == "left") ? 0 : 1;
        return std::make_tuple("sound-" + newDir, bin);
    }

};

OPPT_REGISTER_OBSERVATION_PLUGIN(TigerObservationPlugin)

}
