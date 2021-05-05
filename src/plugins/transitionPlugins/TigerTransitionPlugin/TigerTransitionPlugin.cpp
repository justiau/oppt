#include "oppt/plugin/Plugin.hpp"
#include "oppt/opptCore/Distribution.hpp"

namespace oppt
{
class TigerTransitionPlugin: public TransitionPlugin
{
public:
    TigerTransitionPlugin():
        TransitionPlugin() {
    }

    virtual ~TigerTransitionPlugin() = default;

    virtual bool load(const std::string& optionsFile) override {
        debug::show_message("load called from transition plugin");
        return true;
    }

    virtual PropagationResultSharedPtr propagateState(const PropagationRequest* propagationRequest) const override {
        PropagationResultSharedPtr propagationResult(new PropagationResult());
        VectorFloat actionVec = propagationRequest->action->as<VectorAction>()->asVector();
        debug::show_message("propagate state called from transition plugin");
        VectorFloat resultingState(propagationRequest->currentState->as<VectorState>()->asVector());
        if (actionVec[0] < 3) resultingState[0] = 3.0;
        propagationResult->previousState = propagationRequest->currentState.get();
        propagationResult->nextState =
            std::make_shared<oppt::VectorState>(resultingState);
        return propagationResult;
    }

};

OPPT_REGISTER_TRANSITION_PLUGIN(TigerTransitionPlugin)

}
