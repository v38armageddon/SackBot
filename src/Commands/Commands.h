#ifndef COMMANDS_H
#define COMMANDS_H
#include <dpp/dpp.h>

namespace Commands {
	dpp::task<void> About(const dpp::slashcommand_t& event);
	//dpp::task<void> Ban(const dpp::slashcommand_t& event, dpp::snowflake userID, const std::string& reason);
	dpp::task<void> Clear(const dpp::slashcommand_t& event);
	dpp::task<void> Help(const dpp::slashcommand_t& event);
	dpp::task<void> Joshua(const dpp::slashcommand_t& event);
	dpp::task<void> Kick(const dpp::slashcommand_t& event);
	dpp::task<void> ServerInfo(const dpp::slashcommand_t& event);
	dpp::task<void> Update(const dpp::slashcommand_t& event);
};

#endif // COMMANDS_H