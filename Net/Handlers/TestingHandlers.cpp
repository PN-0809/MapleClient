//////////////////////////////////////////////////////////////////////////////////
//	This file is part of the continued Journey MMORPG client					//
//	Copyright (C) 2015-2019  Daniel Allendorf, Ryan Payton						//
//																				//
//	This program is free software: you can redistribute it and/or modify		//
//	it under the terms of the GNU Affero General Public License as published by	//
//	the Free Software Foundation, either version 3 of the License, or			//
//	(at your option) any later version.											//
//																				//
//	This program is distributed in the hope that it will be useful,				//
//	but WITHOUT ANY WARRANTY; without even the implied warranty of				//
//	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the				//
//	GNU Affero General Public License for more details.							//
//																				//
//	You should have received a copy of the GNU Affero General Public License	//
//	along with this program.  If not, see <https://www.gnu.org/licenses/>.		//
//////////////////////////////////////////////////////////////////////////////////
#include "TestingHandlers.h"

#include "../../Gameplay/Stage.h"
#include "../../IO/UI.h"

#include "../../IO/UITypes/UILoginNotice.h"

namespace ms
{
	void CheckSpwResultHandler::handle(InPacket& recv) const
	{
		int reason = recv.read_byte();

		if (reason == 0)
			UI::get().emplace<UILoginNotice>(UILoginNotice::Message::INCORRECT_PIC);
		else
			std::cout << "[CheckSpwResultHandler]: Unknown reason: [" << reason << "]" << std::endl;

		UI::get().enable();
	}

	void LatestConnectedWorldHandler::handle(InPacket& recv) const
	{
		uint32_t latestConnectedWorldID = recv.read_int();
		// CUIWorldSelect::SetFocusWorld
		if (latestConnectedWorldID < 254 || latestConnectedWorldID > 255) {
			//SetFocusWorld(CUIWorldSelect *this, int nWorldID);
		}
	}

	void FieldEffectHandler::handle(InPacket& recv) const
	{
		int rand = recv.read_byte();

		// Effect
		if (rand == 3)
		{
			std::string path = recv.read_string();

			Stage::get().add_effect(path);

			return;
		}

		std::cout << "[FieldEffectHandler]: Unknown value: [" << rand << "]" << std::endl;
	}

	void AdminResultHandler::handle(InPacket& recv) const
	{
		uint8_t type = recv.read_byte();
		switch (type) {
		case 0x04:
		case 0x05:
		case 0x06:
		case 0x10:
		case 0x1E:
		case 0x12:
			recv.read_byte();
			break;
		case 0x13:
			bool map = recv.read_bool();
			if (map) {
				recv.read_int();
			}
			else {
				recv.read_byte();
			}
		}
	}

	void QuickslotKeyMappedManHandler::handle(InPacket& recv) const
	{
		if (recv.read_bool()) {
			for (uint8_t i = 0; i < recv.length(); i++) {
				recv.read_int();
			}
		}
	}

	void sendAutoHpPotHandler::handle(InPacket& recv) const
	{
		recv.read_int();
	}

	void updateInventorySlotLimitHandler::handle(InPacket& recv) const
	{
		recv.read_byte();
		recv.read_byte();
	}

	void sendAutoMpPotHandler::handle(InPacket& recv) const
	{
		recv.read_int();
	}
}