#include "Commands.h"
#include <dpp/dpp.h>

static dpp::task<void> Help(const dpp::slashcommand_t& event) {
    dpp::embed embed = dpp::embed()
        .set_color(dpp::colors::dark_blue)
        .set_title("Help for SackBot")
        .set_author("v38armageddon", "https://github.com/v38armageddon/SackBot", "https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
        .set_description("Here you can find all commands for SackBot.")
        .set_image("https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
        .add_field("joshua", "A simple test command", true)
        .set_footer(
            dpp::embed_footer()
            .set_text("SackBot is created by v38armageddon | v0.2")
            .set_icon("https://cdn.discordapp.com/avatars/1270782508036001895/8f6e97bbe782e2da4a5b5319da553106.webp?size=128")
        )
        .set_timestamp(time(0));

    // Create the message with the embed
    dpp::message msg = dpp::message(event.command.channel_id, embed);

    event.reply(msg);
}