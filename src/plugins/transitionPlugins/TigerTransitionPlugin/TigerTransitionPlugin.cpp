#include "oppt/plugin/Plugin.hpp"
#include "oppt/opptCore/Distribution.hpp"
// #include <iostream>

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
        // std::cout<<*optionsFile;
        debug::show_message("loading");
        return true;
    }

    virtual PropagationResultSharedPtr propagateState(const PropagationRequest* propagationRequest) const override {
        PropagationResultSharedPtr propagationResult(new PropagationResult());
        VectorFloat actionVec = propagationRequest->action->as<VectorAction>()->asVector();
        // std::cout<<actionVec;
        debug::show_message("propagate state called");
        VectorFloat resultingState(propagationRequest->currentState->as<VectorState>()->asVector());
        return propagationResult;
    }

};

OPPT_REGISTER_TRANSITION_PLUGIN(TigerTransitionPlugin)

}
