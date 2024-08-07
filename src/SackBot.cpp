#include "SackBot.h"
#include <dpp/dpp.h>

const std::string BOT_TOKEN = "TOKEN"; // Fucking. Unsafe. Method

int main()
{
	// Create the bot cluster
	dpp::cluster bot(BOT_TOKEN);

	// Create the logs
	bot.on_log(dpp::utility::cout_logger());

	// Create the slash commands
	bot.on_ready([&bot](const dpp::ready_t& event) {
		// Wrap command registration in run_once to make sure it doesnt run on every full reconnection
		if (dpp::run_once<struct register_bot_commands>()) {
			std::vector<dpp::slashcommand> commands {
				{ 
					"joshua", "Hello, v38armageddon.", bot.me.id 
				}
			};

			bot.global_bulk_command_create(commands);
		}
	});

	// Handle slash command with the most recent addition to D++ features, coroutines!
	bot.on_slashcommand([](const dpp::slashcommand_t& event) -> dpp::task<void> {
		if (event.command.get_command_name() == "joshua") {
			co_await event.co_reply("Hello, v38armageddon.!");
		}
		co_return;
	});

	// Start the bot
	bot.start(dpp::st_wait);

	return 0;
}
