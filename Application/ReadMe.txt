Sonic The Hedgehog Game Scene
- A Temple Run Like Game with Entity Management.

Controls:

Controls (Main Scene) (First Person Camera)
W  - Move Forward based on Camera Position
S  - Move Backward based on Camera Position
A  - Move LeftWay based on Camera Position
D  - Move RightWay based on Camera Position
UP ARROW - Camera Look Up
DOWN ARROW - Camera Look Down
LEFT ARROW - Camera Look Left
RIGHT ARROW - Camera Look Right

Controls (Running Scene) (Third Person Camera)
A - Move Left
D - Move Right

Interaction Buttons
E - For Most Interactions
T - For Purchasing Items from Shop

Interactions:
- Start Race Interaction
- Talk to Eggman Interaction
- Talk to Tails Interaction
- Buy Items from the Shop Interaction

World Text:
- At the Start Race Area
- At the Shop to buy Upgrades

UI Text:
- Coins Collected
- Time Taken for Race
- Notification Message
- Chat Interactin with NPCs

Misc
=========================

Objects Imported: 8 Unique Objects
Total Objects Used: Way over 10.
Used own Skybox, Moves with Player

Code Designs:
- MeshHandler Class (So no double loading since there's Multiple Scenes)
- EntityManager Class
- Entity Class
- HitBox Class
- Box Struct
- Interaction Struct
- EntityData Struct

Animations:
Hair animation (always on by default)
Walking animation (played in Running Scene)

=========================