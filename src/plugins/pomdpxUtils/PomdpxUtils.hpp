// Author: Justin Au
#ifndef _POMDPX_UTILS_HPP_
#define _POMDPX_UTILS_HPP_
#include "oppt/plugin/PluginOptions.hpp"

namespace oppt
{

class PomdpxOptions: public PluginOptions
{
public:
    PomdpxOptions() = default;

    virtual ~PomdpxOptions() = default;

    // path to the pomdpxFile
    std::string pomdpxPath;

    // upperbound and lowerbound for initial belief values
    VectorFloat upperBound;
    VectorFloat lowerBound;

    // observation error
    FloatType observationError;

    // reward options
    FloatType stepPenalty;
    FloatType exitReward;
    FloatType illegalMovePenalty;



    static std::unique_ptr<options::OptionParser> makeParser() {
        std::unique_ptr<options::OptionParser> parser =
            PluginOptions::makeParser();
        addPomdpxPluginOptions(parser.get());
        return std::move(parser);
    }

    static void addPomdpxPluginOptions(options::OptionParser* parser) {
        /*** Initial belief options ***/
        // Lower starting bound
        parser->addOption<VectorFloat>("initialBeliefOptions",
                                       "lowerBound",
                                       &PomdpxOptions::lowerBound);
        // Upper starting bound
	    parser->addOption<VectorFloat>("initialBeliefOptions",
                                       "upperBound",
                                       &PomdpxOptions::upperBound);

        /*** Observation options ***/
        parser->addOption<FloatType>("observationPluginOptions",
                                     "observationError",
                                     &PomdpxOptions::observationError);

        /*** Reward Plugin options ***/
        parser->addOption<FloatType>("rewardPluginOptions",
                                         "stepPenalty",
                                         &PomdpxOptions::stepPenalty);

        parser->addOption<FloatType>("rewardPluginOptions",
                                         "exitReward",
                                         &PomdpxOptions::exitReward);

        parser->addOption<FloatType>("rewardPluginOptions",
                                         "illegalMovePenalty",
                                         &PomdpxOptions::illegalMovePenalty);

    }
    
};

}

#endif