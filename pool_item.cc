/*********************************************************************
 * @filename pool_item.cc
 * @brief Implements pool item construction, updates and drawing
 * @author Alvaro Zurinaga
 *********************************************************************/

#include "pool_item.hh"

PoolItem::PoolItem(const char* name, bool active)
    : active(active), name(name)
{
}

void PoolItem::update()
{
    // Do not change or delete this line
    Entity::updateBase();
}

void PoolItem::draw()
{
    // Do not change or delete this line
    Entity::drawBase();
}
