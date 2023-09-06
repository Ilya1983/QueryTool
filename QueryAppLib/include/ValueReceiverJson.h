#pragma once

#include "ValueReceiver.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class ValueReceiverJson : public ValueReceiver {
public:
	ValueReceiverJson(json json_values);
	~ValueReceiverJson();

	SpecificValue receive_value(std::string name) const override;
	
private:
	json values;
};
