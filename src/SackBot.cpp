#include "SackBot.h"
#include <dpp/dpp.h>
#include <csignal>
#include <filesystem>
#include <iostream>
#include <cstdlib>

std::string BOT_TOKEN; // The token of the bot will define in the TOKEN.conf file
volatile std::sig_atomic_t g_signal_received = false;

// Initialize the signal handler for SIGINT
void signal_handler(int signal) {
    if (signal == SIGINT)
    {
        g_signal_received = true;
    }
}

// Initialize the token of the bot
// PS: Do not ask me again to perform with files and directories in C++. C# is really better for that. - Florian
void initToken() {
    // Check if the TOKEN.conf file exist
    std::string filePath;
#if defined(__linux__)
    filePath = std::string(getenv("HOME")) + "/.config/SackBot/TOKEN.conf";
#else
    filePath = std::string(getenv("APPDATA")) + "\\SackBot\\TOKEN.conf";
#endif
    std::filesystem::path tokenFile(filePath);

    if (std::filesystem::exists(tokenFile)) {
        // We look at the value of TOKEN = [TOKEN] and set as a string
        std::ifstream TokenFile(tokenFile);
        std::string line;
        std::string token;
        while (std::getline(TokenFile, line)) {
            if (line.find("TOKEN = ") != std::string::npos) {
                token = line.substr(line.find("TOKEN = ") + 8);
                BOT_TOKEN = token;
                break;
            }
        }
        TokenFile.close();
		std::cout << "DEBUG: Token: " << token << std::endl; // Uncomment this line to see the token in the console, but use just for debugging.
    }
    else {
		// Create the SackBot directory
		std::filesystem::create_directories(
#if defined(__linux__)
			std::string(getenv("HOME")) + "/.config/SackBot"
#else
			std::string(getenv("APPDATA")) + "\\SackBot"
#endif
        );

        // Create the config file and return 1 for invalid token.
        std::ofstream TokenFile(tokenFile); // TokenFile is not the same as tokenFile!
        TokenFile << "# Here you can set the token of your bot.\n";
        TokenFile << "# For security reason, DO NOT PUT INTO YOUR C++ FILE!\n";
        TokenFile << "# Or you will have a very bad day!\n";
        TokenFile << "TOKEN = [INSERT_TOKEN_HERE]";

		// Close the file and exit the program
		TokenFile.close();

		std::cout << "ERROR: Bot token not found.\nPlease insert your bot token into the TOKEN.conf file.\n\n" << std::endl;
		std::cout << "You can find the TOKEN.conf file at: " << filePath << std::endl;

		std::abort();
    }
}

int main() {
    std::cout << "SackBot, by v38armageddon.\nSACKBOT: Init SIGINIT..." << std::endl;

    // Register the signal handler
    std::signal(SIGINT, signal_handler);

    std::cout << "SACKBOT: SIGINT Initialised!\nSACKBOT: Init TOKEN.conf file..." << std::endl;

    // Init the TOKEN.conf file
    initToken();
    
    std::cout << "SACKBOT: Bot token Initialised!\nSACKBOT: Init the bot, I pass the relay to D++." << std::endl;

    // Create the bot cluster
    dpp::cluster bot(BOT_TOKEN);

    // Create the logs
    bot.on_log(dpp::utility::cout_logger());

    // Create the slash commands
    bot.on_ready([&bot](const dpp::ready_t& event) {
        // Wrap command registration in run_once to make sure it doesn't run on every full reconnection
        if (dpp::run_once<struct register_bot_commands>()) {
            std::vector<dpp::slashcommand> commands {
                {
                    dpp::slashcommand("joshua", "Hello.", bot.me.id),
                    dpp::slashcommand("help", "Get all commands from the bot.", bot.me.id)
                }
            };

            bot.global_bulk_command_create(commands);

            // Print the registered commands
            for (const auto& command : commands) {
                std::cout << "SACKBOT: Command Name: " << command.name << std::endl;
                std::cout << "SACKBOT: Command Description: " << command.description << std::endl;
            }
        };
    });

    // Handle slash command with the most recent addition to D++ features, coroutines!
	// TODO: Separate the functions on commands to avoid a big mess.
    bot.on_slashcommand([](const dpp::slashcommand_t& event) -> dpp::task<void> {
        if (event.command.get_command_name() == "joshua") {
            std::string username = event.command.get_issuing_user().username;
            co_await event.co_reply("Hello, " + username + ".");
        }
        if (event.command.get_command_name() == "help") {
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
        co_return;
    });

    // Start the bot
    bot.start(dpp::st_wait);

    // Wait for the signal
    while (!g_signal_received) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
