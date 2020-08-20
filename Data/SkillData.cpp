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
#include "SkillData.h"

#include "../Character/SkillId.h"
#include "../Data/BulletData.h"
#include "../Util/Misc.h"
#include"../Net/OutPacket.h"
#ifdef USE_NX
#include <nlnx/nx.hpp>
#endif

namespace ms
{
	SkillData::SkillData(int32_t id)
	{
		/// Locate sources
		std::string strid = string_format::extend_id(id, 7);
		std::string jobid = strid.substr(0, 3);
		nl::node src = nl::nx::skill[jobid + ".img"]["skill"][strid];
		nl::node strsrc = nl::nx::string["Skill.img"][strid];

		/// Load icons
		icons = { src["icon"], src["iconDisabled"], src["iconMouseOver"] };

		/// Load strings
		name = strsrc["name"];
		desc = strsrc["desc"];

		for (int32_t level = 1; nl::node sub = strsrc["h" + std::to_string(level)]; level++)
			levels.emplace(level, sub);

		/// Load stats
		nl::node levelsrc = src["level"];

		for (auto sub : levelsrc)
		{
			float damage = (float)sub["damage"] / 100;
			int32_t matk = sub["mad"];
			int32_t fixdamage = sub["fixdamage"];
			int32_t mastery = sub["mastery"];
			uint8_t attackcount = (uint8_t)sub["attackCount"].get_integer(1);
			uint8_t mobcount = (uint8_t)sub["mobCount"].get_integer(1);
			uint8_t bulletcount = (uint8_t)sub["bulletCount"].get_integer(1);
			int16_t bulletcost = (int16_t)sub["bulletConsume"].get_integer(bulletcount);
			int32_t hpcost = sub["hpCon"];
			int32_t mpcost = sub["mpCon"];
			float chance = (float)sub["prop"].get_real(100.0) / 100;
			float critical = 0.0f;
			float ignoredef = 0.0f;
			float hrange = (float)sub["range"].get_real(100.0) / 100;
			Rectangle<int16_t> range = sub;
			int32_t level = string_conversion::or_default<int32_t>(sub.name(), -1);

			stats.emplace(
				std::piecewise_construct,
				std::forward_as_tuple(level),
				std::forward_as_tuple(damage, matk, fixdamage, mastery, attackcount, mobcount, bulletcount, bulletcost, hpcost, mpcost, chance, critical, ignoredef, hrange, range)
			);
		}


		element = src["elemAttr"];

		if (jobid == "900" || jobid == "910")
			reqweapon = Weapon::Type::NONE;
		else
			reqweapon = Weapon::by_value(100 + (int32_t)src["weapon"]);

		masterlevel = static_cast<int32_t>(stats.size());
		passive = (id % 10000) / 1000 == 0;
		flags = flags_of(id);
		invisible = src["invisible"].get_bool();

		/// Load required skills
		nl::node reqsrc = src["req"];

		for (auto sub : reqsrc)
		{
			int32_t skillid = string_conversion::or_default<int32_t>(sub.name(), -1);
			int32_t reqlv = sub.get_integer();

			reqskills.emplace(skillid, reqlv);
		}
	}

	int32_t SkillData::flags_of(int32_t id) const
	{
		static const std::unordered_map<int32_t, int32_t> skill_flags =
		{
			// Beginner
			{ SkillId::THREE_SNAILS, CLOSE },
			// Warrior
			{ SkillId::POWER_STRIKE, CLOSE },
			{ SkillId::SLASH_BLAST, CLOSE },
			// Fighter
			//{ SkillId::FA_SWORD_FIGHTER, CLOSE },
			//{ SkillId::FA_AXE_FIGHTER, CLOSE },
			// Page
			// Crusader
			{ SkillId::PANIC_SWORD, CLOSE },
			{ SkillId::PANIC_AXE, CLOSE },
			{ SkillId::COMA_SWORD, CLOSE },
			{ SkillId::COMA_AXE, CLOSE },
			// Hero
			{ SkillId::RUSH_HERO, CLOSE },
			{ SkillId::BRANDISH, CLOSE },
			// Page
			// White Knight
			{ SkillId::CHARGED_BLOW, CLOSE },
			// Paladin
			{ SkillId::RUSH_PALADIN, CLOSE },
			{ SkillId::BLAST, CLOSE },
			{ SkillId::HEAVENS_HAMMER, CLOSE },
			// Spearman
			// Dragon Knight
			{ SkillId::DRAGON_FURY_PA, CLOSE },
			{ SkillId::DRAGON_FURY_SPEAR, CLOSE },
			{ SkillId::PA_CRUSHER, CLOSE },
			{ SkillId::SPEAR_CRUSHER, CLOSE },
			{ SkillId::SACRIFICE, CLOSE },
			{ SkillId::DRAGON_ROAR, CLOSE },
			// Dark Knight
			{ SkillId::RUSH_DK, CLOSE },
			{ SkillId::BEHOLDER, CLOSE },
			// Magician
			{ SkillId::ENERGY_BOLT, CLOSE},
			{ SkillId::MAGIC_CLAW, CLOSE},
			// Fire/Poison Wizard
			{ SkillId::SLOW_FP, CLOSE },
			{ SkillId::FIRE_ARROW, CLOSE },
			{ SkillId::POISON_BREATH, CLOSE },
			// Fire/Poison Mage 
			{ SkillId::EXPLOSION, CLOSE },
			{ SkillId::POISON_BREATH, CLOSE },
			{ SkillId::SEAL_FP, CLOSE },
			{ SkillId::ELEMENT_COMPOSITION_FP, CLOSE },
			// Fire/Poison Archmage
			{ SkillId::FIRE_DEMON, CLOSE },
			{ SkillId::PARALYZE, CLOSE },
			{ SkillId::BIG_BANG_FP, CLOSE },
			{ SkillId::METEOR_SHOWER, CLOSE },
			// Ice/Lightning Wizard
			{ SkillId::SLOW_IL, CLOSE },
			{ SkillId::COLD_BEAM, CLOSE },
			{ SkillId::THUNDER_BOLT, CLOSE },
			// Ice/Lightning Mage
			{ SkillId::ICE_SCRIKE, CLOSE },
			{ SkillId::THUNDER_SPEAR, CLOSE },
			{ SkillId::SEAL_IL, CLOSE },
			{ SkillId::ELEMENT_COMPOSITION_IL, CLOSE },
			// Ice/Lightning Archmage
			{ SkillId::BIG_BANG_IL, CLOSE },
			{ SkillId::ICE_DEMON, CLOSE },
			{ SkillId::CHAIN_LIGHTNING, CLOSE },
			{ SkillId::BLIZZARD, CLOSE },
			// Cleric 
			{ SkillId::HEAL_CLERIC, CLOSE },
			{ SkillId::HOLY_ARRORW, CLOSE },
			// Priest
			{ SkillId::SHINING_RAY, CLOSE },
			{ SkillId::DOOM, CLOSE },
			// Bishop
			{ SkillId::BIG_BANG_BISHOP, CLOSE },
			{ SkillId::ANGEL_RAY, CLOSE },
			{ SkillId::GENESIS, CLOSE },
			//Archer
			{ SkillId::ARROW_BLOW, CLOSE },
			{ SkillId::DOUBLE_SHOT, CLOSE },
			//Hunter
			{ SkillId::ARROW_BOMB_BOW, CLOSE },
			{ SkillId::POWER_KNOCK_BACK_HUNTER, CLOSE },
			//Ranger
			{ SkillId::INFERNO_BOWMASTER, CLOSE },
			{ SkillId::STRAFE_RANGER, CLOSE },
			{ SkillId::ARROW_RAIN, CLOSE },
			//BowMaster
			{ SkillId::HURRICANE, CLOSE },
			{ SkillId::HAMSTRING, CLOSE },
			{ SkillId::DRAGONS_BREATH_BOWMASTER, CLOSE },
			//CrossBowman
			{ SkillId::POWER_KNOCK_BACK_CROSSBOWMAN, CLOSE },
			{ SkillId::IRON_ARROW_CROSSBOW, CLOSE },
			//Sniper
			{ SkillId::BLIZZARD_SNIPER, CLOSE },
			{ SkillId::ARROW_ERUPTON, CLOSE },
			{ SkillId::STRAFE_SNIPER, CLOSE },
			{ SkillId::MORTAL_BLOW_SNIPER, CLOSE },
			//Marksman
			{ SkillId::PIERCING_ARROW, CLOSE },
			{ SkillId::SNIPE, CLOSE },
			{ SkillId::DRAGONS_BREATH_MARKSMAN, CLOSE },
			//Rogue
			{ SkillId::DOUBLE_STAB, CLOSE },
			{ SkillId::LUCKY_SEVEN, CLOSE },
			//Assasin
			{ SkillId::DRAIN, CLOSE },
			//Hermit
			{ SkillId::SHADOW_WEB, CLOSE },
			{ SkillId::SHADOW_MESO, CLOSE },
			{ SkillId::AVENGER, CLOSE },
			//Night Lord
			{ SkillId::TAUNT_NL, CLOSE },
			{ SkillId::NINJA_AMBUSH_NL, CLOSE },
			{ SkillId::TRIPLE_THROW,  RANGED },
			{ SkillId::NINJA_STORM, CLOSE },
			//Bandit
			{ SkillId::STEAL, CLOSE },
			{ SkillId::SAVAGE_BLOW, CLOSE },
			//Chief Bandit
			{ SkillId::ASSAULTER, CLOSE },
			{ SkillId::BAND_OF_THIEVES, CLOSE },
			{ SkillId::MESO_EXPLOSION, CLOSE },
			//Shadower
			{ SkillId::SHADOW_SHIFTER, CLOSE},
			{ SkillId::ASSASSINATE, CLOSE },
			{ SkillId::TAUNT_SHADOWER, CLOSE },
			{ SkillId::NINJA_AMBUSH_SHADOWER, CLOSE },
			{ SkillId::BOOMERANG_STEP, CLOSE },
			//Pirate
			{ SkillId::FLASH_FIST, CLOSE },
			{ SkillId::SOMMERSAULT_KICK, CLOSE },
			{ SkillId::DOUBLE_SHOT_PIRATE, CLOSE },
			//Brawler
			{ SkillId::BACKSPIN_BLOW, CLOSE },
			{ SkillId::DOUBLE_UPPERCUT, CLOSE },
			{ SkillId::CORKSCREW_BLOW, CLOSE }
			//Marauder
			//Buccaneer
			//Gunslinger
			//Outlaw
			//Consair






		};

		auto iter = skill_flags.find(id);

		if (iter == skill_flags.end())
			return NONE;

		return iter->second;
	}

	bool SkillData::is_passive() const
	{
		return passive;
	}

	bool SkillData::is_attack() const
	{
		return !passive && (flags & CLOSE);
	}

	bool SkillData::is_invisible() const
	{
		return invisible;
	}

	int32_t SkillData::get_masterlevel() const
	{
		return masterlevel;
	}

	Weapon::Type SkillData::get_required_weapon() const
	{
		return reqweapon;
	}
	

	const SkillData::Stats& SkillData::get_stats(int32_t level) const
	{
		auto iter = stats.find(level);

		if (iter == stats.end())
		{
			static constexpr Stats null_stats = Stats(0.0f, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, Rectangle<int16_t>());
			return null_stats;
		}

		return iter->second;
	}

	const std::string& SkillData::get_name() const
	{
		return name;
	}

	const std::string& SkillData::get_desc() const
	{
		return desc;
	}

	const std::string& SkillData::get_level_desc(int32_t level) const
	{
		auto iter = levels.find(level);

		if (iter == levels.end())
		{
			static const std::string null_level = "Missing level description.";

			return null_level;
		}
		else
		{
			return iter->second;
		}
	}

	const Texture& SkillData::get_icon(Icon icon) const
	{
		return icons[icon];
	}

	const std::unordered_map<int32_t, int32_t>& SkillData::get_reqskills() const
	{
		return reqskills;
	}
}
