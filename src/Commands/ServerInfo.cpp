#include "Commands.h"
#include <dpp/dpp.h>

// Know the server where the bot is
namespace Commands {
	d o dpp::task<void> ServerInfo(const dpp::slashcommand_t& event) {
		dpp::guild guild = event.command.get_guild();
		std::string ownerName = "<@" + std::to_string(guild.owner_id) + ">";
		dpp::embed embed = dpp::embed()
			.set_color(dpp::colors::dark_blue)
			.set_title("Server Information")
			.set_author(guild.name, "", guild.get_icon_url())
			.add_field("Server ID:", std::to_string(guild.id), true)
			.add_field("Owner:", ownerName, true)
			.add_field("Members:", std::to_string(guild.member_count), true)
			.add_field("Channels:", std::to_string(guild.channels.size()), true)
			.add_field("Roles:", std::to_string(guild.roles.size()), true)
			.add_field("Verification Level:", std::to_string(guild.verification_level), true)
			.add_field("Created at:", std::to_string(guild.get_creation_time()), true)
			.set_timestamp(time(0));

		// Create the message with the embed
		dpp::message msg = dpp::message(event.command.channel_id, embed);

		event.reply(msg);
		co_return;
	}
}