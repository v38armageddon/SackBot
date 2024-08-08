#include "SackBot.h"
#include <dpp/dpp.h>
#include <csignal>

const std::string BOT_TOKEN = "TOKEN"; // Fucking. Unsafe. Method
volatile std::sig_atomic_t g_signal_received = false;

void signal_handler(int signal)
{
    if (signal == SIGINT)
    {
        g_signal_received = true;
    }
}

int main()
{
    std::cout << "SackBot, by v38armageddon.\nInit SIGINIT..." << std::endl;

    // Register the signal handler
    std::signal(SIGINT, signal_handler);

    std::cout << "SACKBOT: SIGINT Initialised! Now starting the bot..." << std::endl;

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

    std::cout << "SACKBOT: Bot started!" << std::endl;

    // Start the bot
    bot.start(dpp::st_wait);

    // Wait for the signal
    while (!g_signal_received) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    return 0;
}
