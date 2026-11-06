/*********************************************************************
 * @filename object_pool.cc
 * @brief Implements item searches, updates, drawing and removal
 * @author Alvaro Zurinaga
 *********************************************************************/

#include "object_pool.hh"
#include <algorithm>

/**
 * @brief Checks whether a pool item is active
 */
struct IsActive
{
    bool operator()(const PoolItem& item) const
    {
        return item.active;
    }
};

/**
 * @brief Checks whether a pool item is inactive
 */
struct IsInactive
{
    bool operator()(const PoolItem& item) const
    {
        return !item.active;
    }
};

/**
 * @brief Checks whether a pool item has the stored name
 */
struct HasName
{
    std::string name;
    bool operator()(const PoolItem& item) const
    {
        return item.name == name;
    }
};

/**
 * @brief Calls update on a pool item
 */
struct UpdateItem
{
    void operator()(PoolItem& item) const
    {
        item.update();
    }
};

/**
 * @brief Calls draw on a pool item
 */
struct DrawItem
{
    void operator()(PoolItem& item) const
    {
        item.draw();
    }
};

/**
 * @brief Updates a pool item only when it is active
 */
struct UpdateActivateItem
{
    void operator()(PoolItem& item) const
    {
        if (item.active)
        {
            item.update();
        }
    }
};

/**
 * @brief Draws a pool item only when it is active
 */
struct DrawActivateItem
{
    void operator()(PoolItem& item) const
    {
        if (item.active)
        {
            item.draw();
        }
    }
};

void ObjectPool::add(const PoolItem& item)
{
    items.push_back(item);
}

std::size_t ObjectPool::count() const
{
    return items.size();
}

std::size_t ObjectPool::countActive() const
{
    // Count only the items accepted by the predicate
    return std::count_if(items.begin(), items.end(), IsActive{});
}

PoolItem* ObjectPool::findByName(const char* name)
{
    // The search returns end() when no item matches the name
    auto it = std::find_if(items.begin(), items.end(), HasName{name});
    if (it == items.end())
    {
        return nullptr;
    }
    // Dereference the iterator before taking the stored item's address
    return &(*it);
}

PoolItem* ObjectPool::findByRef(const PoolItem& item)
{
    // Use the name because the stored item is a copy of the original object
    return findByName(item.name.c_str());
}

void ObjectPool::activate(const char* name)
{
    PoolItem* item = findByName(name);

    if (item != nullptr)
    {
        item->active = true;
    }
}

void ObjectPool::deactivate(const char* name)
{
    PoolItem* item = findByName(name);

    if (item != nullptr)
    {
        item->active = false;
    }
}

void ObjectPool::updateAll()
{
    // Call the update functor once for each stored item
    std::for_each(items.begin(), items.end(), UpdateItem{});
}

void ObjectPool::drawAll()
{
    // Call the draw functor once for each stored item
    std::for_each(items.begin(), items.end(), DrawItem{});
}

void ObjectPool::updateActive()
{
    // Visit every item and let the functor skip inactive ones
    std::for_each(items.begin(), items.end(), UpdateActivateItem{});
}

void ObjectPool::drawActive()
{
    // Visit every item and let the functor skip inactive ones
    std::for_each(items.begin(), items.end(), DrawActivateItem{});
}

void ObjectPool::removeByName(const char* name)
{
    // Move the items to keep to the front without changing the vector size
    auto newEnd = std::remove_if(items.begin(), items.end(), HasName{name});

    // Erase the remaining tail to update the size and destroy its objects
    items.erase(newEnd, items.end());
}

void ObjectPool::removeInactive()
{
    // Move active items to the front without changing the vector size
    auto newEnd = std::remove_if(items.begin(), items.end(), IsInactive{});

    // Erase the remaining tail to update the size and destroy its objects
    items.erase(newEnd, items.end());
}
