# MomodoraRUtM_Copy_Practice
This project for Game Copy Practice


Using WinAPI/C++ (start at 2023/02/20)

# Week 1~2(2/20 ~ 3/04)
* make Engin
    * make Frame
        * Application 
        * Scene
        * Layer
        * GameObject
        * Component
    * Double Buffering
        * Create Main buffer and Back buffer to use Double Buffering
    * Math
        * Vector2
        * Input (x , y)
    * Memory Release
        * Free memory in the order of Scene, Game Object, and Layer
    * Load Resources
        * Create the code to Load Resources 
        * Load Image and add BackGround the Scene
    * Rendering Scene
        * Create Title Scene and Play Scene
        * Swap Scene between Title and play Scene
    * Component System
        * Create Component System
        * Create Animation Component
            * Animation
            * Animator
            * SpriteSheet
        * Create Collider Component
        * Create Transform Component
    * FSM
        * Using FSM to control Animation and Gameobject
# Week 3(3/6 ~ 3/12)
* Create Camera
    * Convert to screen coordinate system
    * Calcuate Resolutuin and Look position
* Create Animation Event
    * Start Animation Event
        * the event is called Before the animation starts
    * Complete Animation Event
        * After the animation ends, the event is called
    * End Animation Event
        * An event is called between the previous and changed animations.
* Create CollsionManager
    * Handling collisions between colliders
    * Cheak Intersect
* Create Rotation
    * Caluate Math 
        * x = x * cosf(radian) - y * sinf(radian);
        * y = x * sinf(radian) + y * cosf(radian);
* Player
    * To manage player separately, split into three part
        * Manage part
            * Sync transform between Human and Cat
            * Swap Human and Cat
        * Human part
            * FSM
            * Added Some Event
        * Cat part
            * FSM
    * Create Arrow
* Create Enemy (Randomly moving but using FSM)
    * Monster
        * Sheld Imp
    * Boss
        * Arsonist
* BackGround Rendering
    * Pre-render in another buffer and bring it into the main render
* Catch memory leak
* Add Sprite Sheet Resources (Boss, Imp, Player,BackGround, UI, Effect, etc.)
* Fix some Bug
# Week 4(3/13 ~ 3/19)
* Create Rigidbody Component
    * F = Ma
    * Calculate Accelation(a)
        * a = F/M
    * Calculate Velocity(v)
        * v = v + a * time
    * Apply Gravity
        * v = v - gravity * Dot(v,gravity)
    * Add Speed limit
* Add Dot Product , Cross Product
    * Dot( v1 , v2 ) = v1.x * v2.x + v1.y * v2.y
    * Cross( v1, v2 ) = v1.x * v2.y - v1.y * v2.x
* AlphaBlending
    * Create Fade-IN, Fade-Out
    * Reset Fade
* Create Player Enum class
    * To share the current state with each other 
* Player
    * FSM
        * Add Roll State
        * Add Crouch State and Crouch Event
    * Change Manage part
        * Change to getting objects from the scene without dynamic allocation
    * Sync between Human and Cat
* Fix Some Bug
    * Collider
    * Rigidbody
    * CollsionManager
    * Player
        * Cat
    * etc.
# Week5 (3/20 ~ 3/26)
* Create Tile Tool
    * Tile palatte
    * Tile
    * Create Tile Tool Scene
        * Grid
        * Input mouse pos
        * Save data
            * Save Image as text file
* Add Jump
    * Add Ground
        * player stand at ground
    * Now We Can Jump!
* Ground
    * Check collision with Gameobject 
* Player
    * change Rendering
        * Transbitblt to Alphablending
    * Manage part
        * Fix Swap Bug 
    * Human part
        * Add Some Event
        * Add Fall FSM Stat
        * Change WASD Key To Arrow Key
        * Shooting Arrow
            * Player Object Create Arrow Object
        * Add Dash
            * While player on air, player can Dash
    * Cat part
        * Add Rigidbody Component
        * Dash
        * Air Attack
    * Both part
        * Knock Back
        * Blink Animation
            * Control Alpha to Blink
                * Uing sin
        * Add Hurt FSM
    * Resource edit Alpha
# Week 6 (3/27~ 4/2)
* Create Frame Event
    * Make events happen naturally by calling them on every frame
* Create Melee Attack Effect
    * Create Effect Animation
        * Human Attack Effect
        * Cat Attack Effect
    * Rendering Effect
        * Render on a specific frame when the player attacks
    * Collider
        * Adding a collider component to specific frames in an effect to determine collisions
        * Position Set
    * Sync Position with Player Position
* Add Resources
    * Charge Effect
    * Lupiar Boss Sprite Sheet
    * Magnolia Boss Arrow type Sprite Sheet
    * Magnolia Boss Knife type Sprite Sheet
* Tile Tool
    * Create File Load System
    * When Load Tile specific tile will Create Ground collider
* Scene
    * Load Scene With tile tool
* Player
    * Both part
        * Double Jump
* Enemy
    * Sheld Imp
        * Creat Simple AI
        * Create Hurt, Death, Defence FSM
* Add Resources
    * Monster
        * Monkey
    * NPC
        * Cath
    * Tile Map
    * Font
# Week 7 (4/4 ~ 4/9)
* Create Portal
    * Creating Portal Objects to make natural changes to other scene
* Create other scene
* Player
    * manage part
        * Setting the camera to the transitioned object whenever the character switches.
    * Both part
        * Add UseItem FSM
            * Added animations and event FSMs that use items
* Ground
    * Removed ground colliders because they were too buggy
    * Changed ground collision to pixel collision
* Add Resources
    * Stage2 BackGround
    * Stage Pixel Collision
* Fix Bug
    * Melee Attack Effect Bug Fix
        * Fixed a bug that prevented player objects from being received properly
# Week 8 (4/10 ~ 4/ 16)
* Create UI
    * Added Hpbar UI
* Player
    * Both Part
        * Made the player move slightly while attacking
        * Changed hit determination
        * Change the movement speed value from a constant to a variable
        * Do not Hit While Rolling
    * Human Part
        * Now Can Shooting Arrow Right Position
    * Cat Part
        * Added the ability to dash while falling
* Monster
    * Added a Monkey Monster
        * Add a basic FSM
        * Made the player recognize and attack when they come within a certain range.
        * Add Rigidbody Component
        * Add Hp and Hurt FSM
    * Sheld Imp
        * Change to FSM
        * Add Hp and Hurt FSM
        * Keep the player at a certain distance and have them attack at certain times
    * Knife Imp
        * just Rendering
    * Bomb Imp
        * just Rendering
* Boss
    * Added a Lupiar Boss
        * Rendered but not yet doing anything
    * Added a Magnolia Boss
        * Rendered but not yet doing anything
* Npc
    * Added a Cath Npc
        * Rendered but not yet doing anything
* Ground
    * Collision handling for walls and ceilings is now available
    * Added collision handling so monsters can now be affected by gravity as well
* Arrow
    * add Collider
    * added pixel collision to the arrows so that they have a different animation when they hit something other than an enemy. 
    * Changed the layer to a throws
* Mon Melee Attack
    * An object that can be used by enemies to make melee attacks.
* Add Resources
    * edit Charge Effect
    * Arrow Destroy Animation
    * Item Box UI
    * Imp Knife Sprite Sheet
    * Imp Bomb Sprite Sheet
    * Knife and bomb
    * hit Effect Sprite Sheet
 # Week 9 (4/17~ 4/23)
 * 