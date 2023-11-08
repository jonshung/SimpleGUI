# SimpleGUI
> C++ CLI interface

A simple CLI interface written in C++ compatible with Linux and Windows 10+ offering dynamic controls over interactivity and response!
# Building
CMake: Specify your project configuration in the root's `CMakeLists.txt`\
\
Setting project's name and output:
```cmake
...
# Set this to your project name.
set(_BuildProject "ExampleProgram")
# Optional: change this if you want to specify the name of the outputting executable.
set(_OutExecutable ${_BuildProject})
...
```
Add your source files
```cmake
...
# Specify your project's source file here.
set(_ProjectBuildPaths "${_BuildProject}/main.cpp"
                       "${_BuildProject}/Foo.cpp"
                       "${_BuildProject}/Bar.cpp"
    )
...
```
Then, link your header files directory:
```cmake
...
target_include_directories(BuildingTarget PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/ExampleProject")
...
```
# Usage

It is recommended that you implement your own derived MenuManager class as it allows full control over language configuration as well as action handling.\
An example has been provided in the `VendingMachine` folder.\
\
## Initialize a MenuManager instance:
```c++
...
// Here, for control over memory management, it is recommended to use pointer for all instances of MenuManager objects.
std::shared_ptr<MenuManager> menuHandler = std::make_shared<MenuManager>();
...
```
The building blocks of every MenuManager object are Page(s). Page provide a list of Selectable (that is, we can move the user current selection to that item), support for Unselectable items will be added shortly.\
Each Selectable will also contain a SelectableAction, which is a wrapper class holding the action module. An action module is simply a function pointer that accepts a MenuManager object pointer that currently holding this Selectable, and return void.\
\
## Initialize a Page instance and render:
By default, a Page is rendered through the `loadPage()` method pipeline. Though currently simple, i'm intended to extend the use of this pipeline, allowing more control over how a Page is rendered.\
Page object are associated inside a Menu in the form of a `std::shared_pointer`. To create a page and populate it with items:
```c++
...
// By default, this will be printed as the first line of the page. This can be changed by overriding the render() method inside a MenuManager class.
std::string pageLabel = "Example page";
std::vector<Selectable> items;

// push some Selectable items into the list
// Selectable's constructor accept the first parameter as the displaying label of the selectable, the second parameter as an address of an action module function.
// Selectable will be covered shortly after.
items.push_back(Selectable("Item1", &MenuManager::doNothing));
items.push_back(Selectable("Item2", &MenuManager::doNothing));
items.push_back(Selectable("Item3", &MenuManager::doNothing));

// Finally, initialize the page with the corresponding components.
// Page's constructor accept the first parameter as the label of the Page. the second parameter as the list of Selectables.
std::shared_ptr<Page> pPtr(std::make_shared<Page>(pageLabel, items));

// To signal a loadPage() render pipeline, we first tell the MenuManager instance to render the next frame by setting the direct target. 
//By default, MenuManager doesn't render frames every clock run to save resources and maintain control over user interface.
menuManager->setDirectTarget(pPtr);
// then, we initiate the loading sequence.
this->loadPage();
```
This is the basic steps of constructing a MenuManager objects as well as displaying your first Page.\
By extending the action module of each item in a Page, we can direct the user to another page with the same procedure:\
\
## The Selectable Object
> To be deprecated.

A Selectable is an item on a Page that user can select and interact with. By default, after interacting with every Selectable, the current Page will be re-rendered. Though this behavior can be changed by signaling the renderer that this selectable is a redirect component to another Page. This will be covered shortly.\
Selectable exists as pure object on a Page so dynamically managing it is not necessary, though this will be changed in the future.\
```c++
...
void action1(MenuManager* menuManager) {
    menuManager()->IOHandler()->print("Enter a number: ");
    int n;
    std::cin >> n;

    // GeneralUtils.h, concatenateString method will be improved, allowing automatic stringify in the future.
    menuManager()->IOHandler()->print( concatenateString({ "You entered: ", std::to_string(n) }) );
    // stop the interface from exiting this action module immediately
    menuManager()->IOHandler()->print(Enter a key to continue...);
    menuManager->IOHandler()->getChar();
}
...
// Selectable( std::string, (void (*)(MenuManager*)) )
std::string label = "Example";
void (*actionModule)(MenuManager*) = &action1;
Selectable item1 = Selectable(label, actionModule);
```
An action module is a function pointer that accepts a MenuManager pointer as it's only parameter and return void.