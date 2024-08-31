#include "SackBot.h"
#include "Commands/Commands.h"
#include <dpp/dpp.h>

// This is the Joshua command.
// It will reply with a message to the user who issued the command.
// This is like a simple ping command.
static dpp::task<void> Joshua(const dpp::slashcommand_t& event) {
	std::string username = event.command.get_issuing_user().username;
	co_await event.co_reply("Hello, " + username + ".\How about a nice game of chess?");
}