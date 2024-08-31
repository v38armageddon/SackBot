#include <dpp/dpp.h>
#ifndef COMMANDS_H
#define COMMANDS_H

class Commands {
public:
    static dpp::task<void> Joshua(const dpp::slashcommand_t& event);
	static dpp::task<void> Help(const dpp::slashcommand_t& event);
};

#endif // COMMANDS_H