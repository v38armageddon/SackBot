#include "SackBot.h"
#include "Commands/Commands.h"
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

void initToken() {
    // Check if the TOKEN.conf file exists
    std::string filePath;
#if defined(__linux__)
    filePath = std::string(std::getenv("HOME")) + "/.config/SackBot/TOKEN.conf";
#else
    filePath = std::string(std::getenv("APPDATA")) + "\\SackBot\\TOKEN.conf";
#endif
    std::filesystem::path tokenFile(filePath);

    std::cout << filePath << std::endl;

    if (std::filesystem::exists(tokenFile)) {
        // We look at the value of TOKEN = [TOKEN] and set it as a string
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
        std::cout << "DEBUG: Token: " << token << std::endl; // Uncomment this line to see the token in the console, but use it just for debugging.
    }
    else {
        // Create the SackBot directory
        std::filesystem::create_directories(
#if defined(__linux__)
            std::string(std::getenv("HOME")) + "/.config/SackBot"
#else
            std::string(std::getenv("APPDATA")) + "\\SackBot"
#endif
        );

        // Create the config file and return 1 for an invalid token.
        std::ofstream TokenFile(tokenFile); // TokenFile is not the same as tokenFile!
        TokenFile << "# Here you can set the token of your bot.\n";
        TokenFile << "# For security reasons, DO NOT PUT INTO YOUR C++ FILE!\n";
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
    std::cout << "SackBot, by v38armageddon.\nSACKBOT: Init SIGINT..." << std::endl;

    // Register the signal handler
    std::signal(SIGINT, signal_handler);

    std::cout << "SACKBOT: SIGINT Initialized!\nSACKBOT: Init TOKEN.conf file..." << std::endl;

    // Init the TOKEN.conf file
    initToken();
    
    std::cout << "SACKBOT: Bot token Initialized!\nSACKBOT: Init the bot, I pass the relay to D++." << std::endl;

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
					dpp::slashcommand("about", "Get information about the bot.", bot.me.id),
					dpp::slashcommand("ban", "MODERATOR: Ban someone.", bot.me.id),
                    dpp::slashcommand("clear", "MODERATOR: Clear the chat.", bot.me.id),
                    dpp::slashcommand("dnd", "OWNER: Set the bot to Do Not Disturb.", bot.me.id),
                    dpp::slashcommand("help", "Get all commands from the bot.", bot.me.id),
                    dpp::slashcommand("idle", "OWNER: Set the bot to Idle.", bot.me.id),
                    dpp::slashcommand("joshua", "Hello.", bot.me.id),
					dpp::slashcommand("kick", "MODERATOR: Kick someone.", bot.me.id),
					dpp::slashcommand("offline", "OWNER: Set the bot to Offline.", bot.me.id),
                    dpp::slashcommand("online", "OWNER: Set the bot to Online.", bot.me.id),
					dpp::slashcommand("serverinfo", "Get information about the current server.", bot.me.id),
					dpp::slashcommand("update", "See what's new!", bot.me.id)
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
    bot.on_slashcommand([](const dpp::slashcommand_t& event) -> dpp::task<void> {
        // DPP DOESN'T SUPPORT SWITCH STATEMENT SO IF HELL IS HERE!
		if (event.command.get_command_name() == "about") {
			Commands::About(event);
			co_return;
		}
        if (event.command.get_command_name() == "help") {
            Commands::Help(event);
            co_return;
        }
        if (event.command.get_command_name() == "joshua") {
            Commands::Joshua(event);
            co_return;
        }
		if (event.command.get_command_name() == "serverinfo") {
			Commands::ServerInfo(event);
			co_return;
		}
    });

    // Start the bot
    bot.start(dpp::st_wait);

    // Wait for the signal
    while (!g_signal_received) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
