#include "Commands.h"
#include <dpp/dpp.h>

// This is the Ban command to PERMANENTLY ban a user from the server
// For unban (why would you want to unban someone?), use the build-in Discord settings ban list
namespace Commands {
	dpp::task<void> Ban(const dpp::slashcommand_t& event) {
		// We need more information about the user and it's permissions
		dpp::role userPerm;

		// Check if the user has the BAN_MEMBERS permission
		if (userPerm.has_ban_members() == false) {
			dpp::message msg = dpp::message(event.command.channel_id, "You don't have the permission to ban members.");
			event.reply(msg);
			co_return;
		}
		else {
			event.reply("You have the permission to ban members.");
			co_return;
		}
	}

	/*dpp::task<void> CheckPermissions(const dpp::slashcommand_t& event) {
		dpp::snowflake userID = std::get(event.get_parameter("user"));
		dpp::permissions userPermissions = event.command.get_resolved_permission(userID);

		if (!event.command.app_permissions.can(dpp::p_ban_members)) {
			event.reply("Sorry, I can't do this because you are not authorized to do so.");
			co_return;
		}
	}*/
}