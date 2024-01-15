#pragma once

#include <ForwardsZone.h>
#include <Common.h>

namespace Sapphire::World::Action
{
  /*!
   * @brief A container for the computed result of an effect on a single actor. Used to apply damage/healing dealt
   * at a later point in time.
   */
  class ActionResult
  {
  public:
    explicit ActionResult( Entity::CharaPtr target );

    void damage( uint32_t amount, Common::CalcResultType hitType, uint8_t hitEffect, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void heal( uint32_t amount, Common::CalcResultType hitType, uint8_t hitEffect, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void restoreMP( uint32_t amount, Common::ActionResultFlag flag = Common::ActionResultFlag::None );
    void startCombo( uint16_t actionId );
    void comboSucceed();
    void applyStatusEffect( uint32_t id, int32_t duration, Entity::Chara& source, uint8_t param, bool shouldOverride );
    void applyStatusEffectSelf( uint32_t id, int32_t duration, uint8_t param, bool shouldOverride );
    void mount( uint16_t mountId );

    Entity::CharaPtr getTarget() const;

    const Common::CalcResultParam& getCalcResultParam() const;
    const Sapphire::StatusEffect::StatusEffectPtr getStatusEffect() const;

    void execute();

  private:
    Entity::CharaPtr m_target;

    Common::CalcResultParam m_result;

    bool m_bOverrideStatus { false };
    Sapphire::StatusEffect::StatusEffectPtr m_pStatus;

  };

  using ActionResultList = std::vector< ActionResultPtr >;
}