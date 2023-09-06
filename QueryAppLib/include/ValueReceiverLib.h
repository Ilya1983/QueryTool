#pragma once

#include "ValueReceiver.h"
#include <unordered_map>
#include <string>
#include "SpecificValue.h"

class ValueReceiverLib : public ValueReceiver {
public:
	ValueReceiverLib();
	~ValueReceiverLib();

	void add_or_change_value(std::string key, int value);
	void add_or_change_value(std::string key, std::string value);
	void add_or_change_value(std::string key, bool value);

	void remove_value(std::string key);

	SpecificValue receive_value(std::string name) const override;

private:
	std::unordered_map<std::string, SpecificValue> values;
};