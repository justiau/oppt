#include "oppt/plugin/Plugin.hpp"
#include "oppt/opptCore/Distribution.hpp"
#include "plugins/pomdpxUtils/PomdpxUtils.hpp"

namespace oppt
{
class PomdpxTransitionPlugin: public TransitionPlugin
{
public:
    PomdpxTransitionPlugin():
        TransitionPlugin() {
    }

    virtual ~PomdpxTransitionPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        parseOptions_<PomdpxOptions>(optionsFile);
        PomdpxOptions* generalOptions = static_cast<PomdpxOptions*>(options_.get());
        // load action space discretizer here

        
        return true;
    }

    virtual PropagationResultSharedPtr propagateState(const PropagationRequest* propagationRequest) const override {
        PropagationResultSharedPtr propagationResult(new PropagationResult());
        VectorFloat actionVec = propagationRequest->action->as<VectorAction>()->asVector();
        VectorFloat resultingState(propagationRequest->currentState->as<VectorState>()->asVector());
        if (actionVec[0] < 2.25) resultingState[0] = 3.0;
        propagationResult->previousState = propagationRequest->currentState.get();
        propagationResult->nextState =
            std::make_shared<oppt::VectorState>(resultingState);
        return propagationResult;
    }

};

OPPT_REGISTER_TRANSITION_PLUGIN(PomdpxTransitionPlugin)

}
