/*********************************************************************
 * @filename object_pool.hh
 * @brief Declares the object pool and its item management operations
 * @author Alvaro Zurinaga
 *********************************************************************/

#pragma once
#include "pool_item.hh"
#include <cstddef>
#include <vector>
#include <string>

class ObjectPool
{
public:
    /**
     * @brief Adds a copy of an item to the pool
     */
    void add(const PoolItem& item);

    /**
     * @brief Returns the total number of items in the pool
     */
    std::size_t count() const;

    /**
     * @brief Returns the number of active items in the pool
     */
    std::size_t countActive() const;

    /**
     * @brief Returns the first item with the given name or nullptr
     */
    PoolItem* findByName(const char* name);

    /**
     * @brief Finds the first item with the same name as the given item
     */
    PoolItem* findByRef(const PoolItem& item);

    /**
     * @brief Sets the first item with the given name to active
     */
    void activate(const char* name);

    /**
     * @brief Sets the first item with the given name to inactive
     */
    void deactivate(const char* name);

    /**
     * @brief Updates every item in the pool
     */
    void updateAll();

    /**
     * @brief Draws every item in the pool
     */
    void drawAll();

    /**
     * @brief Updates only the active items in the pool
     */
    void updateActive();

    /**
     * @brief Draws only the active items in the pool
     */
    void drawActive();

    /**
     * @brief Removes all items with the given name
     */
    void removeByName(const char* name);

    /**
     * @brief Removes all inactive items from the pool
     */
    void removeInactive();

private:
    std::vector<PoolItem> items;
};
