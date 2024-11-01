#include "Commands.h"
#include <dpp/dpp.h>

// Know the server where the bot is
namespace Commands {
	dpp::task<void> ServerInfo(const dpp::slashcommand_t& event) {
		dpp::guild guild = event.command.get_guild();
		std::string ownerName = "<@" + std::to_string(guild.owner_id) + ">";

		// Convert creation time to human-readable format
		std::time_t creation_time = static_cast<std::time_t>(guild.get_creation_time());
        std::tm tm_struct;
        std::tm* tm_ptr = &tm_struct;
        gmtime_s(tm_ptr, &creation_time);
		std::stringstream creation_time_ss;
		creation_time_ss << std::put_time(tm_ptr, "%Y-%m-%d %H:%M:%S");

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
			.add_field("Created at:", creation_time_ss.str(), true)
			.set_timestamp(time(0));

		// Create the message with the embed
		dpp::message msg = dpp::message(event.command.channel_id, embed);

		event.reply(msg);
		co_return;
	}
}