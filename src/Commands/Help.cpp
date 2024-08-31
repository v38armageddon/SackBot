#include "Commands.h"
#include <dpp/dpp.h>

// Help command to show help for the bot
// Be sure to add the new commands to the help command
namespace Commands {
    dpp::task<void> Help(const dpp::slashcommand_t& event) {
        dpp::embed embed = dpp::embed()
            .set_color(dpp::colors::dark_blue)
            .set_title("Help for SackBot")
            .set_author("v38armageddon", "https://github.com/v38armageddon/SackBot", "https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
            .set_description("Here you can find all commands for SackBot.")
            .set_image("https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
			.add_field("about", "Get information about SackBot.", true)
			.add_field("ban", "MODERATOR: Ban someone.", true)
			.add_field("clear", "MODERATOR: Clear the chat.", true)
			.add_field("dnd", "OWNER: Set the bot to Do Not Disturb.", true)
			.add_field("help", "This help!", true)
			.add_field("idle", "OWNER: Set the bot to Idle.", true)
            .add_field("joshua", "A simple command", true)
			.add_field("kick", "MODERATOR: Kick someone.", true)
			.add_field("offline", "OWNER: Set the bot to Offline.", true)
			.add_field("online", "OWNER: Set the bot to Online.", true)
			.add_field("serverinfo", "Get information about the current server.", true)
			.add_field("update", "See what's new!", true)
            .set_footer(
                dpp::embed_footer()
                .set_text("SackBot is created by v38armageddon | v0.3")
                .set_icon("https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
            )
            .set_timestamp(time(0));

        // Create the message with the embed
        dpp::message msg = dpp::message(event.command.channel_id, embed);

        event.reply(msg);
		co_return;
    }
}