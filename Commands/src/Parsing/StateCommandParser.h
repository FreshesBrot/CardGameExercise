#pragma once
#include "StateIOParser.h"
#include "../../CommandCommon.h"

//the StateCommandParser manages several different states according to an enumerator templated as States
template<typename States>
class StateCommandParser : public StateIOParser<States, IOReader> {
public:
	typedef std::unordered_map<States, Commands> StateMap;

	StateCommandParser(Token&& identifier, StateMap&& allStates = { }) : StateIOParser<States, IOReader>(std::move(identifier), std::move(allStates)) { }
	StateCommandParser() : StateIOParser<States, IOReader>() { }

	StateCommandParser(StateCommandParser&) = delete;
	StateCommandParser(StateCommandParser&& parser) noexcept : StateIOParser<States, IOReader>() {
		*this = std::move(parser);
	}

	StateCommandParser& operator=(StateCommandParser&& parser) noexcept {
		if (this == &parser) return *this;
		StateIOParser<States, IOReader>::operator=(std::move(parser));
		return *this;
	}

};