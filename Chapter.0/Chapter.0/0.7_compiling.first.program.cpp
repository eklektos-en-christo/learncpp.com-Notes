//
//  0.7_compiling.first.cpp
//  Chapter.0
//
//  Created by Judah's Leon on 7/13/22.
//

/*
 Projects

 To write a C++ program inside an IDE, we typically start by creating a new project (we’ll show you how to do this in a bit). A project is a container that holds all of your source code files, images, data files, etc… that are needed to produce an executable (or library, website, etc…) that you can run or use. The project also saves various IDE, compiler, and linker settings, as well as remembering where you left off, so that when you reopen the project later, the state of the IDE can be restored to wherever you left off. When you choose to compile your program, all of the .cpp files in the project will get compiled and linked.

 Each project corresponds to one program. When you’re ready to create a second program, you’ll either need to create a new project, or overwrite the code in an existing project (if you don’t want to keep it). Project files are generally IDE specific, so a project created for one IDE will need to be recreated in a different IDE.

 Best practice

 Create a new project for each new program you write.
 
 Console projects

 When you create a new project, you’ll generally be asked what type of project you want to create. All of the projects that we will create in this tutorial will be console projects. A console project means that we are going to create programs that can be run from the Windows, Linux, or Mac console.
 
 Workspaces / solutions

 When you create a new project for your program, many IDEs will automatically add your project to a “workspace” or a “solution” (the term varies by IDE). A workspace or solution is a container that can hold one or more related projects. For example, if you were writing a game and wanted to have a separate executable for single player and multiplayer, you’d need to create two projects. It wouldn’t make sense for both of these projects to be completely independent -- after all, they are part of the same game. Mostly likely, each would be configured as a separate project within a single workspace/solution.

 Although you can add multiple projects to a single solution, we generally recommend creating a new workspace or solution for each program, especially while learning. It’s simpler and there’s less chance of something going wrong.
 
 
 */

// first program
#include <iostream>

//int main()
//{
//    std::cout<<"Hello World\n";
//    return 0;
//}
