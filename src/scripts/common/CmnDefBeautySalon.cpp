// This is an automatically generated C++ script template
// Content needs to be added by hand to make it function
// In order for this script to be loaded, move it to the correct folder in <root>/scripts/

#include <Actor/Player.h>
#include "Manager/EventMgr.h"
#include <ScriptObject.h>
#include <Service.h>

// Script: CmnDefBeautySalon_00148
// Event Name: Summon Aesthetician
// Event ID: 721044
using namespace Sapphire;

class CmnDefBeautySalon : public Sapphire::ScriptAPI::EventScript
{
  private:
    // Basic event information 
    // Entities found in the script data of the event
    static constexpr auto BeautySalonTicket = 7005;
    static constexpr auto LocAction0 = 1012;
    static constexpr auto LocAction1 = 577;
    static constexpr auto LocActor0 = 1005882;
    static constexpr auto LocBgm0 = 191;
    static constexpr auto LocPosFst = 4576993;
    static constexpr auto LocPosIsh = 5878293;
    static constexpr auto LocPosSea = 4576990;
    static constexpr auto LocPosWil = 4576992;
    static constexpr auto LogmsgGilNotEnough = 3901;
    static constexpr auto OtherWorld = 35;
    static constexpr auto Quest = 66746;
    static constexpr auto RegisteringContentFinder = 23;
    static constexpr auto RewardBeautySalon = 26;
    static constexpr auto TerritoryTypeF1T1 = 179;
    static constexpr auto TerritoryTypeR2T1 = 429;
    static constexpr auto TerritoryTypeS1T1 = 177;
    static constexpr auto TerritoryTypeW1T1 = 178;

    enum Payment : uint8_t
    {
      Gil = 1,
      Token = 2
    };

    bool result = false;

  public:
    CmnDefBeautySalon() : Sapphire::ScriptAPI::EventScript( 721044 ){}; 
    ~CmnDefBeautySalon() = default; 

  //////////////////////////////////////////////////////////////////////
  // Event Handlers
  void onTalk( uint32_t eventId, Entity::Player& player, uint64_t actorId ) override
  {
    Scene00000( player );
  }

  void onYield( uint32_t eventId, uint16_t sceneId, uint8_t yieldId, Entity::Player& player, const std::string& resultString, uint64_t resultInt, const std::vector< uint32_t >& results ) override
  {
    if( sceneId == 1 && yieldId == 24 )
      eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 0 } );
    else if( sceneId == 2 )
    {
      switch( yieldId )
      {
        case 25:
        {
          // client sends 1
          // client sends 0
          eventMgr().resumeScene( player, eventId, sceneId, yieldId, { 1 } );
          break;
        }
        case 27:
        {
          auto payment = static_cast< Payment >( results.at( 0 ) );

          switch( payment )
          {
            case Payment::Gil:
            {
              player.removeCurrency( Common::CurrencyType::Gil, 2000 );
              result = true;
              break;
            }
            case Payment::Token:
            {
              // TODO: remove token
              result = true;
              break;
            }
            default:
            {
              result = false;
              break;
            }
          }

          if( result )
          {
            uint8_t i = 0;
            for( auto it = results.begin() + 1; it != results.end(); ++it )
            {
              if( i > 26 )
                break;
              player.setLookAt( i, *it );
              ++i;
            }
          }

          eventMgr().resumeScene( player, eventId, sceneId, yieldId, { result } ); // 0 when failed
          }
          break;
      }
    }
  }

  private:
  //////////////////////////////////////////////////////////////////////
  // Available Scenes in this event, not necessarly all are used
  //////////////////////////////////////////////////////////////////////

  void Scene00000( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 0, HIDE_HOTBAR, bindSceneReturn( &CmnDefBeautySalon::Scene00000Return ) );
  }

  void Scene00000Return( Entity::Player& player, const Event::SceneResult& result )
  {
    if( result.getResult( 0 ) == 1 )
      Scene00001( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00001( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 1, FADE_OUT | HIDE_UI | SET_EOBJ_BASE, bindSceneReturn( &CmnDefBeautySalon::Scene00001Return ) );
  }

  void Scene00001Return( Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00002( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00002( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 2, FADE_OUT | HIDE_UI | SET_EOBJ_BASE, bindSceneReturn( &CmnDefBeautySalon::Scene00002Return ) );
  }

  void Scene00002Return( Entity::Player& player, const Event::SceneResult& result )
  {
    Scene00003( player );
  }

  //////////////////////////////////////////////////////////////////////

  void Scene00003( Entity::Player& player )
  {
    eventMgr().playScene( player, getId(), 3, FADE_OUT | HIDE_UI, { result, result }, bindSceneReturn( &CmnDefBeautySalon::Scene00003Return ) );
  }

  void Scene00003Return( Entity::Player& player, const Event::SceneResult& result )
  {


  }

};

EXPOSE_SCRIPT( CmnDefBeautySalon );