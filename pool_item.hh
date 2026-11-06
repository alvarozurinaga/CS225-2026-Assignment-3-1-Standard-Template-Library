/*********************************************************************
 * @filename pool_item.hh
 * @brief Declares a named entity with an active state for the object pool
 * @author Alvaro Zurinaga
 *********************************************************************/

#pragma once
#include "entity.hh"
#include <string>

class PoolItem : public Entity
{
public:
    /**
     * @brief Creates a pool item with the given name and active state
     */
    PoolItem(const char* name, bool active);

    /**
     * @brief Updates the item using the base entity method
     */
    void update() override; // Provided method, do not change

    /**
     * @brief Draws the item using the base entity method
     */
    void draw() override; // Provided method, do not change

    bool active = false;
    std::string name;
};
