#include "Commands.h"
#include <dpp/dpp.h>

// About command to show information about the bot
// Like the version, the creator, and the GitHub repository
namespace Commands {
	dpp::task<void> About(const dpp::slashcommand_t& event) {
		dpp::embed embed = dpp::embed()
			.set_color(dpp::colors::dark_blue)
			.set_title("About SackBot")
			.set_author("v38armageddon", "https://github.com/v38armageddon/SackBot", "https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
			.set_description("SackBot is a simple Discord bot to make common tasks easier.")
			.add_field("Creator:", "v38armageddon", true)
			.add_field("Version:", "v0.3", true)
			.add_field("License:", "MS-PL", true)
			.add_field("Source code:", "https://github.com/v38armageddon/SackBot", true)
			.add_field("Commands:", "Type /help to see all commands.", true)
			.set_footer(
				dpp::embed_footer()
				.set_text("Credits to Win's INFO and Win's BOT for the inspiration.")
				.set_icon("https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
			)
			.set_timestamp(time(0));

		// Create the message with the embed
		dpp::message msg = dpp::message(event.command.channel_id, embed);

		event.reply(msg);
		co_return;
	}
}