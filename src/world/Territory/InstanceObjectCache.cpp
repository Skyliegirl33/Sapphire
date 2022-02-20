#include "InstanceObjectCache.h"
#include "Exd/ExdData.h"

#include <datReader/DatCategories/bg/pcb.h>
#include <datReader/DatCategories/bg/lgb.h>
#include <datReader/DatCategories/bg/sgb.h>
#include <GameData.h>
#include <File.h>
#include <DatCat.h>
#include <ExdData.h>
#include <ExdCat.h>
#include <Exd.h>

#include <Logging/Logger.h>
#include <Service.h>
#include <Util/UtilMath.h>

Sapphire::InstanceObjectCache::InstanceObjectCache()
{

  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto idList = exdData.getIdList< Excel::TerritoryType >();

  std::map< std::string, uint16_t > found;

  size_t count = 0;
  for( const auto& id : idList )
  {
    // show some loading indication...
    if( count++ % 10 == 0 )
      std::cout << ".";

    auto territoryType = exdData.getRow< Excel::TerritoryType >( id );
    if( !territoryType )
      continue;

    auto path = territoryType->getString( territoryType->data().LVB );

    if( path.empty() )
      continue;

    path = std::string( "bg/" ) + path.substr( 0, path.find( "/level/" ) );

    if( id > 90 && found.find( path ) == found.end() )
      found.emplace( path, id );

    // TODO: it does feel like this needs to be streamlined into the datReader instead of being done here...
    std::string bgLgbPath( path + "/level/bg.lgb" );
    std::string planmapLgbPath( path + "/level/planmap.lgb" );
    std::string planeventLgbPath( path + "/level/planevent.lgb" );
    std::vector< char > bgSection;
    std::vector< char > planmapSection;
    std::vector< char > planeventSection;

    std::unique_ptr< xiv::dat::File > bgFile;
    std::unique_ptr< xiv::dat::File > planmap_file;
    std::unique_ptr< xiv::dat::File > planevent_file;

    try
    {
      bgFile = exdData.getGameData()->getFile( bgLgbPath );
      planmap_file = exdData.getGameData()->getFile( planmapLgbPath );
      planevent_file = exdData.getGameData()->getFile( planeventLgbPath );
    }
    catch( std::runtime_error& )
    {
      // ignore files that aren't found
      continue;
    }

    bgSection = bgFile->access_data_sections().at( 0 );
    planmapSection = planmap_file->access_data_sections().at( 0 );
    planeventSection = planevent_file->access_data_sections().at( 0 );

    std::vector< std::string > stringList;

    uint32_t offset1 = 0x20;

    LGB_FILE bgLgb( &bgSection[ 0 ], "bg" );
    LGB_FILE planmapLgb( &planmapSection[ 0 ], "planmap" );
    LGB_FILE planeventLgb( &planeventSection[ 0 ], "planevent" );

    std::vector< LGB_FILE > lgbList{ bgLgb, planmapLgb, planeventLgb };
    uint32_t max_index = 0;

    for( const auto& lgb : lgbList )
    {
      for( const auto& group : lgb.groups )
      {
        for( const auto& pEntry : group.entries )
        {

          if( pEntry->getType() == LgbEntryType::MapRange )
          {
            auto pMapRange = std::reinterpret_pointer_cast< LGB_MAP_RANGE_ENTRY >( pEntry );
            m_mapRangeCache.insert( id, pMapRange );
          }
          else if( pEntry->getType() == LgbEntryType::ExitRange )
          {
            auto pExitRange = std::reinterpret_pointer_cast< LGB_EXIT_RANGE_ENTRY >( pEntry );
            m_exitRangeCache.insert( id, pExitRange );
          }
          else if( pEntry->getType() == LgbEntryType::PopRange )
          {
            auto pPopRange = std::reinterpret_pointer_cast< LGB_POP_RANGE_ENTRY >( pEntry );
            m_popRangeCache.insert( id, pPopRange );
          }
          else if( pEntry->getType() == LgbEntryType::CollisionBox )
          {
            //auto pEObj = std::reinterpret_pointer_cast< LGB_ENPC_ENTRY >( pEntry );

            //Logger::debug( "CollisionBox {}", pEntry->header.nameOffset );
          }
          else if( pEntry->getType() == LgbEntryType::EventObject )
          {
            auto pEObj = std::reinterpret_pointer_cast< LGB_EOBJ_ENTRY >( pEntry );
            m_eobjCache.insert( 0, pEObj );
          }
          else if( pEntry->getType() == LgbEntryType::EventNpc )
          {
            auto pENpc = std::reinterpret_pointer_cast< LGB_ENPC_ENTRY >( pEntry );
            m_enpcCache.insert( 0, pENpc );
          }
          else if( pEntry->getType() == LgbEntryType::EventRange )
          {
            auto pEventRange = std::reinterpret_pointer_cast< LGB_EVENT_RANGE_ENTRY >( pEntry );
            auto zoneId = found.find( path );
            m_eventRangeCache.insert( zoneId != found.end() ? zoneId->second : id, pEventRange );
          }
          else if( pEntry->getType() == LgbEntryType::FateRange )
          {
            auto pFateRange = std::reinterpret_pointer_cast< LGB_FATE_RANGE_ENTRY >( pEntry );
            m_fateRangeCache.insert( id, pFateRange );
          }
        }
      }
    }
  }
  std::cout << "\n";

  Logger::debug(
    "InstanceObjectCache Cached: MapRange: {} ExitRange: {} PopRange: {} EventNpc: {} EventRange: {} FateRange: {}",
    m_mapRangeCache.size(), m_exitRangeCache.size(), m_popRangeCache.size(), m_enpcCache.size(), m_eventRangeCache.size(), m_fateRangeCache.size()
  );
}

Sapphire::InstanceObjectCache::FateRangePtr
  Sapphire::InstanceObjectCache::getFateRange( uint32_t fateRangeId )
{
  return m_fateRangeCache.get( 0, fateRangeId ).first;
}

Sapphire::InstanceObjectCache::MapRangePtr
  Sapphire::InstanceObjectCache::getMapRange( uint16_t zoneId, uint32_t mapRangeId )
{
  return m_mapRangeCache.get( zoneId, mapRangeId ).first;
}

Sapphire::InstanceObjectCache::ExitRangePtr
  Sapphire::InstanceObjectCache::getExitRange( uint16_t zoneId, uint32_t exitRangeId )
{
  return m_exitRangeCache.get( zoneId, exitRangeId ).first;
}

Sapphire::InstanceObjectCache::PopRangePtr
  Sapphire::InstanceObjectCache::getPopRange( uint32_t popRangeId )
{
  return m_popRangeCache.get( 0, popRangeId ).first;
}

Sapphire::InstanceObjectCache::EObjPtr
  Sapphire::InstanceObjectCache::getEObj( uint32_t eObjId )
{
  return m_eobjCache.get( 0, eObjId ).first;
}

Sapphire::InstanceObjectCache::ENpcPtr
  Sapphire::InstanceObjectCache::getENpc( uint32_t eNpcId )
{
  return m_enpcCache.get( 0, eNpcId ).first;
}

std::pair< Sapphire::InstanceObjectCache::EventRangePtr, uint16_t >
  Sapphire::InstanceObjectCache::getEventRangePair( uint32_t eventRangeId )
{
  return m_eventRangeCache.get( 0, eventRangeId );
}

Sapphire::InstanceObjectCache::EventRangePtr
  Sapphire::InstanceObjectCache::getEventRange( uint32_t eventRangeId )
{
  return m_eventRangeCache.get( 0, eventRangeId ).first;
}

std::shared_ptr< Sapphire::InstanceObjectCache::PopRangeInfo > Sapphire::InstanceObjectCache::getPopRangeInfo( uint32_t popRangeId )
{
  auto popRange = getPopRange( popRangeId );
  if( !popRange )
    return nullptr;

  auto popInfo = std::make_shared< Sapphire::InstanceObjectCache::PopRangeInfo >();

  popInfo->m_pos = Common::FFXIVARR_POSITION3 { popRange->header.transform.translation.x,
                                               popRange->header.transform.translation.y,
                                               popRange->header.transform.translation.z };

  auto targetRot = Common::FFXIVARR_POSITION3 { popRange->header.transform.rotation.x,
                                                popRange->header.transform.rotation.y,
                                                popRange->header.transform.rotation.z };

  popInfo->m_rotation = Common::Util::eulerToDirection( targetRot );

  auto& exdData = Common::Service< Sapphire::Data::ExdData >::ref();
  auto levelData = exdData.getRow< Excel::Level >( popRangeId );
  if( levelData )
    popInfo->m_territoryTypeId = levelData->data().TerritoryType;

  return popInfo;
}
