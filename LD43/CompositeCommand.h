#pragma once
#include "Command.h"
#include <vector>

class CompositeCommand :
	public Command
{
public:
	CompositeCommand();
	~CompositeCommand();

	std::vector<Command *> commands;

	void addCommand(Command & c);
	void run();
};



CompositeCommand::CompositeCommand()
{
}


CompositeCommand::~CompositeCommand()
{
}

void CompositeCommand::addCommand(Command & c) {
	CompositeCommand::commands.push_back(&c);
}

void CompositeCommand::run() {

	for (int i = 0; i < commands.size(); i++) {
		commands.at(i)->run();
	}
}
