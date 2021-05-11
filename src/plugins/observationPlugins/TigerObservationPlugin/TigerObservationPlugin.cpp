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
        long binNumber = 0;
        if (actionVec[0] < 2.25) {
            observationVec[0] = 0.0;
        } else {
            FloatType probability = 1.0 - observationError_;
            bool obsMatches =
                std::bernoulli_distribution(
                    probability)(*(robotEnvironment_->getRobot()->getRandomEngine().get()));
            int stateInt = (int) stateVec[0] + 0.25;
            if (obsMatches) {
                observationVec[0] = stateInt;
            } else {
                // xor obs vec with 3 will convert 1 -> 2 and 2 - > 1
                observationVec[0] = stateInt^3;
            }
            binNumber = (int) observationVec[0] + 0.25;
        }
        auto observationSpace = robotEnvironment_->getRobot()->getObservationSpace();
        ObservationSharedPtr observation = std::make_shared<DiscreteVectorObservation>(observationVec);
        observation->as<DiscreteVectorObservation>()->setBinNumber(binNumber);
        observationResult->observation = observation;
        observationResult->errorVector = observationRequest->errorVector;
        return observationResult;
    }

private:
    FloatType observationError_;
};

OPPT_REGISTER_OBSERVATION_PLUGIN(TigerObservationPlugin)

}
