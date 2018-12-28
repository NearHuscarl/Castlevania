# Castlevania

A remake of Castlevania NES (Block 01) written in C++ and directx 9

## Controls

| Key            | Command              |
|----------------|----------------------|
| <kbd>←</kbd>   | Walk left            |
| <kbd>→</kbd>   | Walk right           |
| <kbd>↑</kbd>   | Go upstairs          |
| <kbd>↓</kbd>   | Go downstairs / Duck |
| <kbd>z</kbd>   | Attack               |
| <kbd>x</kbd>   | Jump                 |
| <kbd>c</kbd>   | Use subweapon        |
| <kbd>Esc</kbd> | Toggle devtool       |

### Devtool Control

#### Keyboard

| Key                 | Command                        |
|---------------------|--------------------------------|
| <kbd>tab</kbd>      | Set category to PLAYER         |
| <kbd>q</kbd>        | Set category to ENEMY          |
| <kbd>w</kbd>        | Set category to CONTAINER      |
| <kbd>e</kbd>        | Set category to POWERUP        |
| <kbd>r</kbd>        | Set category to WEAPON         |
| <kbd>t</kbd>        | Set category to EFFECT         |
| <kbd>g</kbd>        | Toggle drawing grid info       |
| <kbd>home</kbd>     | Next map                       |
| <kbd>end</kbd>      | Previous map                   |
| <kbd>1</kbd>        | Move player to `Checkpoint`    |
| <kbd>2</kbd>        | Move player to `Checkpoint_02` |
| <kbd>3</kbd>        | Move player to `Checkpoint_03` |
| <kbd>4</kbd>        | Move player to `Checkpoint_04` |
| <kbd>5</kbd>        | Move player to `Checkpoint_05` |
| <kbd>6</kbd>        | Move player to `Checkpoint_06` |
| <kbd>8</kbd>        | Add 200 hearts to player       |
| <kbd>9</kbd>        | Set player health to 1 hp      |
| <kbd>0</kbd>        | Set player health to full      |
| <kbd>Numpad -</kbd> | Kill player                    |
| <kbd>Numpad +</kbd> | Add 1 live to player           |
| <kbd>~</kbd>        | Toggle god mode for player     |

#### Mouse

| Mouse button           | Command                              |
|------------------------|--------------------------------------|
| <kbd>Scroll up</kbd>   | Select to next item                  |
| <kbd>Scroll down</kbd> | Select to previous item              |
| <kbd>Left click</kbd>  | Spawn current item at mouse position |
| <kbd>Right click</kbd> | Toggle item facing                   |

## Development Environment

-  Visual Studio 2017
-  C++17
-  [Tiled] - A general purpose tile map editor for all tile-based games

### Libraries

-  [DirectX 9 SDK]
-  [pugixml] - Light-weight, simple and fast XML parser for C++
-  [freetype] - A freely available software library to render fonts
-  [fmt] - A modern formatting library

[sample project]: https://github.com/dungdna2000/gamedev-intro-tutorials/

## References
-  [Castlevania_Block_1]
-  [Castlevania_Inventory]
-  [Block_1 Walkthrough]
-  [Item_Data]
-  [Back to the Basics! Essentials of Modern C++ Style]
-  [Smart pointers need careful programmers]
-  [UIT-SE102-Game-Project ]
-  [Game Programming Patterns]
-  [Swept AABB collision detection]
-  [Evolve Your Heirachy]
-  [Monogame Framework]
-  [Monogame Samples]
   -  [CatapaultWars]
   -  [NetRumble]
   -  [RolePlayingGame]

[native event]: https://msdn.microsoft.com/en-us/library/ee2k0a7d.aspx
[Tiled]: https://www.mapeditor.org/

[Castlevania_Block_1]: http://castlevania.wikia.com/wiki/Castlevania_Block_1
[Castlevania_Inventory]: http://castlevania.wikia.com/wiki/Castlevania_Inventory
[Block_1 Walkthrough]: http://castlevania.wikia.com/wiki/Walkthrough:Castlevania/Block_1
[Item_Data]: http://castlevania.wikia.com/wiki/Vampire_Killer_(whip)/Item_Data

[back to the basics! essentials of modern c++ style]: https://github.com/CppCon/CppCon2014/blob/master/Presentations/Back%20to%20the%20Basics!%20Essentials%20of%20Modern%20C%2B%2B%20Style/Back%20to%20the%20Basics!%20Essentials%20of%20Modern%20C%2B%2B%20Style%20-%20Herb%20Sutter%20-%20CppCon%202014.pdf
[smart pointers need careful programmers]: https://yatb.giacomodrago.com/en/post/11/cpp11-smart-pointers-need-careful-programmers.html
[uit-se102-game-project ]: https://github.com/danhph/UIT-SE102-Game-Project
[game programming patterns]: http://gameprogrammingpatterns.com/contents.html
[Swept AABB collision detection]: https://luuthevinh.me/2016/11/xet-va-xu-ly-va-cham-bang-swept-aabb
[evolve your heirachy]: http://cowboyprogramming.com/2007/01/05/evolve-your-heirachy/
[monogame framework]: https://github.com/MonoGame/MonoGame
[monogame samples]: https://github.com/CartBlanche/MonoGame-Samples
[catapaultwars]: https://github.com/CartBlanche/MonoGame-Samples/tree/master/CatapaultWars
[netrumble]: https://github.com/CartBlanche/MonoGame-Samples/tree/master/NetRumble
[roleplayinggame]: https://github.com/CartBlanche/MonoGame-Samples/tree/master/RolePlayingGame
[directx 9 sdk]: https://www.microsoft.com/en-us/download/details.aspx?id=6812
[pugixml]: https://github.com/zeux/pugixml/
[freetype]: https://github.com/ubawurinna/freetype-windows-binaries
[fmt]: https://github.com/fmtlib/fmt
[create smart pointer from raw pointer]: https://stackoverflow.com/questions/4665266/creating-shared-ptr-from-raw-pointer
[seperate animation and physical bounding box]: http://community.monogame.net/t/examples-of-good-adaptive-code-for-animated-sprites/9569
