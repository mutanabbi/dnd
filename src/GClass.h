#pragma once

#include "IDefence.h"
#include <string>

struct GClass : IDefenceModifiers
{
  /// @todo bonuses to abilities
  virtual unsigned short get_start_hp() const = 0;
  virtual unsigned short get_per_lvl_hp() const = 0;
  virtual std::string get_name() const = 0;
/// @todo armor porficiency
/// @todo weapon porficiency
/// @todo HP per level granted
/// @todo Healing surges
/// @todo build options
/// @todo class features
/// @todo trained skills
};

/// @todo Generate these classes using static @c boost::mpl based table
struct GCFighter : GClass
{
  unsigned short get_start_hp() const override { return 15; }
  unsigned short get_per_lvl_hp() const override { return 6; };

  short get_ac_mod() const override { return 0; }
  short get_fort_mod() const override { return 2; };
  short get_refl_mod() const override { return 0; };
  short get_will_mod() const override { return 0; };

  std::string get_name() const override { return "Fighter"; }
/// @todo weapon prof: simple melee, military melee, simple ranged, military ranged
/// @todo armor prof: cloth, leather, hide, chainmail, scale; light shield, heavy shield
};

struct GCRogue : GClass
{
  unsigned short get_start_hp() const override { return 12; }
  unsigned short get_per_lvl_hp() const override { return 5; };

  short get_ac_mod() const override { return 0; }
  short get_fort_mod() const override { return 0; };
  short get_refl_mod() const override { return 2; };
  short get_will_mod() const override { return 0; };

  std::string get_name() const override { return "Rogue"; }
/// @todo weapon prof: dagger, hand crossbow, shuriken, sling, short sword
/// @todo armor prof: cloth, leather
};

static GCFighter fighter;
static GCRogue rogue;
