#include "Commands.h"
#include <dpp/dpp.h>

namespace Commands {
	dpp::task<void> Kick(const dpp::slashcommand_t& event) {
		event.reply("WIP!");
		co_return;
	}
}