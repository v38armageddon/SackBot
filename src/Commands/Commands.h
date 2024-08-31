#ifndef COMMANDS_H
#define COMMANDS_H
#include <dpp/dpp.h>

namespace Commands {
	dpp::task<void> Joshua(const dpp::slashcommand_t& event);
	dpp::task<void> Help(const dpp::slashcommand_t& event);
	dpp::task<void> About(const dpp::slashcommand_t& event);
};

#endif // COMMANDS_H