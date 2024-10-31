#include "Commands.h"
#include <dpp/dpp.h>

// This is the Ban command to PERMANENTLY ban a user from the server
// For unban (why would you want to unban someone?), use the build-in Discord settings ban list
namespace Commands {
	//dpp::task<void> Ban(const dpp::slashcommand_t& event) {
	//	// Check if the user has the BAN_MEMBERS permission
	//	if (!event.command.get_issuing_user()) { // TODO: Remake this if statement
	//		dpp::message msg = dpp::message(event.command.channel_id, "You don't have the permission to ban members.");
	//		event.reply(msg);
	//		co_return;
	//	}
	//}
}