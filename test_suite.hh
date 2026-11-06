/*! 
 * Test suite for the CS225 entity-component framework assigment.
 *
 * Contains the combined collection of tests for the assignment. 
 * Use this if you find it convenient to work with a single file that contains all the driver code.
 *
 * Modifications to this file are allowed only for development convenience (e.g. commenting out code
 * that fails to compile). This file will be used as provided during the grading process, so make sure
 * that your solution does not rely on any modification done on this file.
 *
 * If you want to disable a test, just comment it out. Bear in mind that the `TEST` macro makes it 
 * necessary to compile and run the test code, so both compilation and run time errors should
 * be taken into account.
 */
#include "test_helper.hh"
#include "testing.hh" // testing framework (ASSERT_THAT, etc.)
#include <chrono>
#include <thread>

using namespace testing;

#include <string>       // std::string
#include <exception>    // std::exception
#include <stdexcept>    // std::out_of_range, std::invalid_argument
#include <typeinfo>     // std::bad_cast

// ===========================================================================
// ===========================================================================
// ===========================================================================

// Object pooling
#include "pool_item.hh"
#include "object_pool.hh" 

/*********************************************************************
 *                        Test for Object Pooling                    *
 *********************************************************************/

namespace Tests 
{ 
    namespace STLObjectPool
    {

        #ifdef ENABLE_TEST1      
        // [ Test #1 ] -------------------------------------------------------
        TEST( "ObjectPool and PoolItem class",
            "An instance of an ObjectPool and a PoolItem can be created" )
        {        
            printf("TEST1 Object Pool and PoolItem class\n");
            
            ObjectPool pool;            
            PoolItem item("Dummy", false);

            ASSERT_THAT(&pool != nullptr);
            ASSERT_THAT(&item != nullptr);

            printf("TEST1 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_TEST2
      
        // [ Test #2 ] -------------------------------------------------------
        TEST( "Items can be added to the object pool",
            "An item can be added to the object pool" )
        {        
             printf("TEST2 Items can be added to the object pool\n");
            ObjectPool pool;          
           
            PoolItem dummy("Dummy",false);        
            pool.add(dummy);

            printf("TEST2 Succeed!\n");
            SUCCEED();
        }
        #endif

        #ifdef ENABLE_TEST3

        // [ Test #3 ] -------------------------------------------------------
        TEST( "Number of items in the pool",
            "Count the number of items in the pool" )
        {        
            printf("TEST3 Number of items in the pool \n");

            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", false);                     

            pool.add(item1);
            pool.add(item2);

            ASSERT_THAT( pool.count() == 2);

            printf("TEST3 Succeed!\n");
            SUCCEED();
        }
        
        #endif

        #ifdef ENABLE_TEST4

        // [ Test #4 ] -------------------------------------------------------
        TEST( "Number of active items in the pool",
            "Count the number of active entities in the pool" )
        {        
            printf("TEST4 Number of active items in the pool\n");

            ObjectPool pool;          
           
            PoolItem item1("Dummy1", true);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy3", true);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            ASSERT_THAT(pool.countActive() == 2);

            printf("TEST4 Succeed!\n");
            SUCCEED();
        }
        
        #endif
       
        #ifdef ENABLE_TEST5

        // [ Test #5 ] -------------------------------------------------------
        TEST( "Items can be activated by its name",
            "Find an item in the pool by their name activate it" )
        {        
            printf("Items can be found by its name \n");

            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy3", false);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            ASSERT_THAT( pool.findByName("Dummy2") != nullptr);
            ASSERT_THAT( pool.findByName("Dummy2")->name == "Dummy2");

            // Testing an item that not exists    
            ASSERT_THAT( pool.findByName("DummyX") == nullptr);

            printf("TEST5 Succeed!\n");
            SUCCEED();
        }
        
        #endif  
        
        #ifdef ENABLE_TEST6

        // [ Test #6 ] -------------------------------------------------------
        TEST( "Items can be found using a reference object",
            "Find an item in the container using a reference object, if the item is not found must return nullptr")
        {        
            printf("TEST6 Items can be found using a reference object\n");

            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy3", false);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            ASSERT_THAT( pool.findByRef(item2) != nullptr);
            ASSERT_THAT( pool.findByRef(item2)->name == "Dummy2");

            PoolItem itemX("DummyX", false);                     
            ASSERT_THAT( pool.findByRef(itemX) == nullptr);

            printf("TEST6 Succeed!\n");
            SUCCEED();
        }
        
        #endif  

        #ifdef ENABLE_TEST7

        // [ Test #7 ] -------------------------------------------------------
        TEST( "Items can be activate by its name",
            "Find an item in the pool by its name and activate it" )
        {        
            printf("TEST7 Items can be activated by its name \n");

            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy3", false);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            pool.activate("Dummy2");

            ASSERT_THAT(pool.findByName("Dummy1")->active == false);
            ASSERT_THAT(pool.findByName("Dummy2")->active == true);
            ASSERT_THAT(pool.findByName("Dummy3")->active == false);

            printf("TEST7 Succeed!\n");
            SUCCEED();
        }
        
        #endif  
        
        #ifdef ENABLE_TEST8

        // [ Test #8 ] -------------------------------------------------------
        TEST( "Items can be deactivate by its name",
            "Find an item in the pool by its name and deactivate it" )
        {        
            printf("TEST8 Items can be deactivated by its name \n");

            ObjectPool pool;          
           
            PoolItem item1("Dummy1", true);                     
            PoolItem item2("Dummy2", true);                     
            PoolItem item3("Dummy3", true);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            pool.deactivate("Dummy2");

            ASSERT_THAT(pool.findByName("Dummy1")->active == true);
            ASSERT_THAT(pool.findByName("Dummy2")->active == false);
            ASSERT_THAT(pool.findByName("Dummy3")->active == true);

            printf("TEST8 Succeed!\n");
            SUCCEED();
        }
        
        #endif 

        #ifdef ENABLE_TEST9

         // [ Test #9 ] -------------------------------------------------------
        TEST( "Calling the update method in the pool, updates all its items",
            "Call the update method int the pool, updates each item in the pool (calls PoolItem update method)")
        {        
            printf("TEST9 Calling the update method in the pool, updates all its items \n");
 
            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy3", false);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            pool.updateAll();

            ASSERT_THAT(updateCounter == 3);

            printf("TEST9 Succeed!\n");
            
            SUCCEED();
        }
        
        #endif

        #ifdef ENABLE_TEST10

         // [ Test #10 ] -------------------------------------------------------
        TEST( "Calling the draw method in the pool, draws all its items",
            "Call the draw method int the pool, draws each item in the pool (calls PoolItem draw method")
        {        
            printf("TEST10 Calling the draw method in the pool, draws all its items \n");
 
            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy3", false);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            pool.drawAll();

            ASSERT_THAT(drawCounter == 3);

            printf("TEST10 Succeed!\n");
            
            SUCCEED();
        }
        
        #endif

        #ifdef ENABLE_TEST11

         // [ Test #11 ] -------------------------------------------------------
        TEST( "Updating only the active items in the pool",
            "Calling updateActive() only updates the active items in the pool")
        {        
            printf("TEST11 Updating only the active items in the pool \n");
 
            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", true);                     
            PoolItem item3("Dummy3", true);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            pool.updateActive();

            ASSERT_THAT(updateCounter == 5);

            printf("TEST11 Succeed!\n");
            
            SUCCEED();
        }
        
        #endif        

        #ifdef ENABLE_TEST12

         // [ Test #12 ] -------------------------------------------------------
        TEST( "Drawing only the active items in the pool",
            "Calling drawActive() only draws the active items in the pool")
        {        
            printf("TEST12 Drawing only the active items in the pool \n");
 
            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", true);                     
            PoolItem item3("Dummy3", true);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);

            pool.drawActive();

            ASSERT_THAT(drawCounter == 5);

            printf("TEST12 Succeed!\n");
            
            SUCCEED();
        }
        
        #endif    

        #ifdef ENABLE_TEST13

         // [ Test #13 ] -------------------------------------------------------
        TEST( "Items can be removed from the pool by its name",
            "Remove an item by its name from the container and releases their memory")
        {        
            printf("TEST13 Items can be removed from the pool by its name \n");
 
            ObjectPool pool;          
           
            PoolItem item1("Dummy1", false);                     
            PoolItem item2("Dummy2", true);                     
            PoolItem item3("Dummy2", true);
            PoolItem item4("Dummy3", true);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);
            pool.add(item4);
            
            pool.removeByName("Dummy2");

            ASSERT_THAT(pool.count() == 2);
            ASSERT_THAT(pool.findByName("Dummy2") == nullptr);

            printf("TEST13 Succeed!\n");
            
            SUCCEED();
        }
        
        #endif        

        #ifdef ENABLE_TEST14

        // [ Test #14 ] -------------------------------------------------------
        TEST( "Removing all inactive items in the pool",
            "Remove all inactive items in the container and releases their memory")
        {        
            printf("TEST14 Removing all inactive items in the pool \n");
 
            ObjectPool pool;          
           
            PoolItem item1("Dummy1", true);                     
            PoolItem item2("Dummy2", false);                     
            PoolItem item3("Dummy2", false);
            PoolItem item4("Dummy3", true);                     

            pool.add(item1);
            pool.add(item2);
            pool.add(item3);
            pool.add(item4);
            
            pool.removeInactive();

            ASSERT_THAT(pool.count() == 2);
            ASSERT_THAT(pool.findByName("Dummy2") == nullptr);

            printf("TEST14 Succeed!\n");
            
            SUCCEED();
        }
        
        #endif        
    } 


} // namespace Test::STLObjectPool


