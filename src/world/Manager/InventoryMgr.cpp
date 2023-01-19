#include "InventoryMgr.h"

#include <Common.h>
#include "Actor/Player.h"
#include "Inventory/ItemContainer.h"
#include "Inventory/HousingItem.h"
#include "Manager/ItemMgr.h"
#include <Network/PacketDef/Zone/ServerZoneDef.h>
#include <Network/GamePacket.h>

#include <Database/DatabaseDef.h>
#include <Exd/ExdData.h>
#include <Service.h>

#include "WorldServer.h"
#include "Session.h"
#include "Network/GameConnection.h"

using namespace Sapphire;
using namespace Sapphire::World::Manager;
using namespace Sapphire::Network;
using namespace Sapphire::Network::Packets;
using namespace Sapphire::Network::Packets::WorldPackets::Server;

void InventoryMgr::sendInventoryContainer( Entity::Player& player, ItemContainerPtr container )
{
  auto& server = Common::Service< World::WorldServer >::ref();
  auto pSession = server.getSession( player.getCharacterId() );

  auto sequence = player.getNextInventorySequence();
  auto pMap = container->getItemMap();

  for( auto & itM : pMap )
  {
    if( !itM.second )
      return;

    if( container->getId() == Common::InventoryType::Currency || container->getId() == Common::InventoryType::Crystal )
    {
      auto currencyInfoPacket = makeZonePacket< FFXIVIpcGilItem >( player.getId() );
      currencyInfoPacket->data().contextId = sequence;
      currencyInfoPacket->data().item.catalogId = itM.second->getId();
      currencyInfoPacket->data().item.subquarity = 1;
      currencyInfoPacket->data().item.stack = itM.second->getStackSize();
      currencyInfoPacket->data().item.storageId = container->getId();
      currencyInfoPacket->data().item.containerIndex = 0;

      server.queueForPlayer( player.getCharacterId(), currencyInfoPacket );
    }
    else
    {
      auto itemInfoPacket = makeZonePacket< FFXIVIpcNormalItem >( player.getId() );
      itemInfoPacket->data().contextId = sequence;
      itemInfoPacket->data().item.storageId = container->getId();
      itemInfoPacket->data().item.containerIndex = itM.first;
      itemInfoPacket->data().item.stack = itM.second->getStackSize();
      itemInfoPacket->data().item.catalogId = itM.second->getId();
      itemInfoPacket->data().item.durability = itM.second->getDurability();
//      itemInfoPacket->data().spiritBond = itM->second->getSpiritbond();
//      itemInfoPacket->data().reservedFlag = itM->second->getReservedFlag();
      // todo: not sure if correct flag?
      itemInfoPacket->data().item.flags = static_cast< uint8_t >( itM.second->isHq() ? 1 : 0 );
      itemInfoPacket->data().item.stain = static_cast< uint8_t >( itM.second->getStain() );

      server.queueForPlayer( player.getCharacterId(), itemInfoPacket );
    }
  }

  auto itemSizePacket = makeZonePacket< FFXIVIpcItemSize >( player.getId() );
  itemSizePacket->data().contextId = sequence;
  itemSizePacket->data().size = container->getEntryCount();
  itemSizePacket->data().storageId = container->getId();

  server.queueForPlayer( player.getCharacterId(), itemSizePacket );
}

ItemPtr InventoryMgr::createItem( Entity::Player& player, uint32_t catalogId, uint32_t quantity )
{
  auto& pExdData = Common::Service< Data::ExdData >::ref();
  auto& itemMgr = Common::Service< ItemMgr >::ref();
  auto itemInfo = pExdData.getRow< Excel::Item >( catalogId );

  if( !itemInfo )
    return nullptr;

  auto item = make_Item( itemMgr.getNextUId(), catalogId );

  item->setStackSize( std::max< uint32_t >( 1, quantity ) );

  saveItem( player, item );

  return item;
}

void InventoryMgr::saveHousingContainer( Common::LandIdent ident, ItemContainerPtr container )
{
  auto u64ident = *reinterpret_cast< uint64_t* >( &ident );

  for( auto& item : container->getItemMap() )
  {
    saveHousingContainerItem( u64ident, container->getId(), item.first, item.second->getUId() );
  }
}

void InventoryMgr::removeItemFromHousingContainer( Common::LandIdent ident, uint16_t containerId, uint16_t slotId )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::LAND_INV_DEL );

  auto u64ident = *reinterpret_cast< uint64_t* >( &ident );

  stmt->setUInt64( 1, u64ident );
  stmt->setUInt( 2, containerId );
  stmt->setUInt( 3, slotId );

  db.directExecute( stmt );
}

void InventoryMgr::saveHousingContainerItem( uint64_t ident, uint16_t containerId, uint16_t slotId, uint64_t itemId )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::LAND_INV_UP );
  // LandIdent, ContainerId, SlotId, ItemId, ItemId

  stmt->setUInt64( 1, ident );
  stmt->setUInt( 2, containerId );
  stmt->setUInt( 3, slotId );
  stmt->setUInt64( 4, itemId );

  // see query, we have to pass itemid in twice
  // the second time is for the ON DUPLICATE KEY UPDATE condition
  stmt->setUInt64( 5, itemId );

  db.directExecute( stmt );
}

void InventoryMgr::updateHousingItemPosition( Inventory::HousingItemPtr item )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::LAND_INV_UP_ITEMPOS );
  // ItemId, PosX, PosY, PosZ, Rotation, PosX, PosY, PosZ, Rotation

  auto pos = item->getPos();

  auto posX = static_cast< uint32_t >( pos.x );
  auto posY = static_cast< uint32_t >( pos.y );
  auto posZ = static_cast< uint32_t >( pos.z );

  auto rot = static_cast< int32_t >( item->getRot() );

  stmt->setUInt64( 1, item->getUId() );

  stmt->setUInt( 2, posX );
  stmt->setUInt( 3, posY );
  stmt->setUInt( 4, posZ );
  stmt->setInt( 5, rot );

  stmt->setUInt( 6, posX );
  stmt->setUInt( 7, posY );
  stmt->setUInt( 8, posZ );
  stmt->setInt( 9, rot );

  db.execute( stmt );
}

void InventoryMgr::removeHousingItemPosition( Inventory::HousingItem& item )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();

  auto stmt = db.getPreparedStatement( Db::LAND_INV_DEL_ITEMPOS );

  stmt->setUInt64( 1, item.getUId() );

  db.directExecute( stmt );
}

void InventoryMgr::saveItem( Entity::Player& player, ItemPtr item )
{
  auto& db = Common::Service< Db::DbWorkerPool< Db::ZoneDbConnection > >::ref();
  auto stmt = db.getPreparedStatement( Db::CHARA_ITEMGLOBAL_INS );

  stmt->setUInt( 1, player.getId() );
  stmt->setUInt64( 2, item->getUId() );
  stmt->setUInt( 3, item->getId() );
  stmt->setUInt( 4, item->getStackSize() );

  db.directExecute( stmt );
}
