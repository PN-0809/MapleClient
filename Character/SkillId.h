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
#pragma once

namespace ms
{
	namespace SkillId
	{
		enum Id : uint32_t
		{
			// Beginner
				FOLLOW_THE_LEAD = 8,
				ANGEL_BLESSING = 12,
				THREE_SNAILS = 1000,
				HEAL = 1001,
				FEATHER = 1002,
				LEGENDARY_SPIRIT = 1003,
				MONSTER_RIDER = 1004,
				ECHO_OF_THE_HERO = 1005,

			//WAR
				// Swordman
					IMPROVED_HP_RECOVERY = 1000000,
					IMPROVED_MAX_HP = 1000001,
					IMPROVED_LADDER_RECOVERY = 1000002,
					IRON_BODY = 1001003,
					POWER_STRIKE = 1001004,
					SLASH_BLAST = 1001005,
				
				// Fighter
					SWORD_MASTERY_FIGHTER = 1100000,
					AXE_MASTERY_FIGHTER = 1100001,
					FA_SWORD_FIGHTER = 1100002,
					FA_AXE_FIGHTER = 1100003,
					SWORD_BOOSTER_FIGHTER = 1101004,
					AXE_BOOSTER_FIGHTER = 1101005,
					RAGE = 1101006,
					POWER_GUARD_FIGHTER = 1101007,

				// Crusader
					IMPROVED_MP_RECOVERY_CRUSADER = 1110000,
					SHIELD_MASTERY_CRUSADER = 1110001,
					COMBO_ATTACK = 1110002,
					PANIC_SWORD = 1111003,
					PANIC_AXE = 1111004,
					COMA_SWORD = 1111005,
					COMA_AXE = 1111006,
					ARMOR_CRASH = 1111007,
					SHOUT = 1111008,

				// Hero
					ADVANCED_COMBO_ATTACK = 1120003,
					ACHILLES_HERO = 1120004,
					GUARDIAN_HERO = 1120005,
					MAPLE_WARRIOR_HERO = 1121000,
					MONSTER_MAGNET_HERO = 1121001,
					POWER_STANCE_HERO = 1121001,
					RUSH_HERO = 1121006,
					BRANDISH = 1121008,
					ENRAGE  = 1121010,
					HEROS_WILL_HERO = 1121011,

				// Page
					SWORD_MASTERY_PAGE = 1200000,
					BW_MASTERY_PAGE = 1200001,
					FA_SWORD_PAGE = 1200002,
					FA_BW_PAGE = 1200003,
					SWORD_BOOSTER_PAGE = 1201004,
					BW_BOOSTER_PAGE = 1201005,
					THREATEN = 1201006,
					POWER_GUARD_PAGE = 1201007,

				// White Knight
					IMPROVED_MP_RECOVERY_WHITE_KNIGHT = 1211000,
					SHIELD_MASTERY_WHITE_KNIGHT = 1211001,
					CHARGED_BLOW = 1211002,
					FIRE_CHARGE_SWORD = 1211003,
					FLAME_CHARGE_BW = 1211004,
					ICE_CHARGE_SWORD = 1211005,
					BLIZZARD_CHARGE_BW = 1211006,
					THUNDER_CHARGE_SWORD= 1211007,
					LIGHTNING_CHARGE_BW= 1211008,
					MAGIC_CRASH= 1211009,
					
				// Paladin
					ACHILLES_PALADIN = 1220005,
					GUARDIAN_PALADIN = 1220006,
					MAPLE_WARRIOR_PALADIN = 1221000,
					MONSTER_MAGNET_PALADIN = 1221001,
					POWER_STANCE_PALADIN = 1221002,
					RUSH_PALADIN = 1221007,
					BLAST = 1221009,
					HOLY_CHARGE_SWORD = 1221003,
					DIVINE_CHARGE_BW = 1221004,
					HEROS_WILL_PALADIN = 1221012,
					ADVANCED_CHARGE = 1220010,
					HEAVENS_HAMMER = 1221011,

				// Spearman
					SPEAR_MASTERY_SPEARMAN = 1300000,
					PA_MASTERY_SPEARMAN = 1300001,
					FA_SPEAR_SPEARMAN = 1300002,
					FA_PA_SPEARMAN = 1300003,
					SPEAR_BOOSTER_SPEARMAN = 1301004,
					PA_BOOSTER_SPEARMAN = 1301005,
					IRON_WILL = 1301006,
					HYPER_BODY = 1301007,

				// Dragon Knight
					ELEMENTAL_RESISTANCE = 1311000,
					SPEAR_CRUSHER = 1311001,
					PA_CRUSHER = 1311002,
					DRAGON_FURY_SPEAR = 1311003,
					DRAGON_FURY_PA = 1311004,
					SACRIFICE = 1311005,
					DRAGON_ROAR = 1311006,
					POWER_CRASH = 1311007,
					DRAGON_BLOOD = 1311008,

				// Dark Knight
					MAPLE_WARRIOR_DK = 1321000,
					RUSH_DK = 1321003,
					AURA_OF_THE_BEHOLDER = 1320008,
					HEROS_WILL_DK = 1321010,
					HEX_OF_THE_BEHOLDER = 1320009,
					POWER_STANCE_DK = 1321002,
					BEHOLDER = 1321007,
					ACHILLES_DK = 1320005,
					BERSERK = 1320006,
					MONSTER_MAGNET_DK = 1321001,
					
					
					
					
					
					
			//MAGE
				// Magician
					IMPROVE_HP_RECOVERY = 2000000,
					IMPROVE_MAX_HP = 2000001,
					MAGIC_GUARD = 2001002,
					MAGIC_ARMOR = 2001003,
					ENERGY_BOLT = 2001004,
					MAGIC_CLAW = 2001005,

				// Fire/Poison Wizard
					MP_EATER_FP = 2100000,
					MEDITATION_FP = 2101001,
					TELEPORT_FP = 2101002,
					SLOW_FP = 2101003,
					FIRE_ARROW = 2101004,
					POISON_BREATH = 2101005,

				// Fire/Poison Mage
					PARTIAL_RESISTANCE_FP = 2110000,
					ELEMENT_AMPLIFICATION_FP = 2110001,
					EXPLOSION = 2111002,
					POISON_MIST = 2111003,
					SEAL_FP = 2111004,
					SPELL_BOOSTER_FP = 2111005,
					ELEMENT_COMPOSITION_FP = 2111006,

				// Fire/Poison Archmage
					FIRE_DEMON = 2121003,
					ELQUINES = 2121005,
					PARALYZE = 2121006,
					METEOR_SHOWER = 2121007,

				// Ice/Lightning Wizard
					IL_TELEPORT = 2201002,
					COLD_BEAM = 2201004,
					MEDITATION = 2201001,
				// I/L Archmage
					ELEMENT_COMPOSITION_IL = 2211006,

				// Ice/Lightning Archmage
					ICE_DEMON = 2221003,
					CHAIN_LIGHTNING = 2221006,
					BLIZZARD = 2121007,

				// Priest
					PRIEST_TELEPORT = 2301001,
					GENESIS = 2321008,
			//THIEF
				// Hermit
					AVENGER = 4111005,
					FLASH_JUMP = 4111006,

				// Night Lord
					TRIPLE_THROW = 4121007,

				// Bandit
					MESO_EXPLOSION = 4211006
		};
	}
}
