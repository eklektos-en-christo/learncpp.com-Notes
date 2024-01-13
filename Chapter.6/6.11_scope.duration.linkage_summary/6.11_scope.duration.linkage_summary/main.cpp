//
//  main.cpp
//  6.11_scope.duration.linkage_summary
//
//  Created by εκλεγμένοι εν Χριστώ on 11/22/22.
//

/*
 --------------------------------SCOPE SUMMARY----------------------------------
 An identifier's scope : determines where the identifier can be accessed within the source code
 
 VARIABLES WITH BLOCK/LOCAL SCOPE:
 can only be accessed within the block in which they are declared(this includes nested blocks)
 this includes:
 local variables
 function parameters
 user defined type definitions like enums and classes declared inside a block
 
 VARIABLES WITH FILE/GLOBAL SCOPE:
 can be accessed from the point of declaration until the end of the file
 this includes:
 global variables
 functions
 user defiend type definitions like enums and classes declared inside a namespace or in the global
 scope
 ------------------------------------------------------------------------
 
 ------------------------------------DURATION SUMMARY----------------------------
 A variable's duration : determines when it is created and destroyed
 
 VARIABLES WITH AUTOMATIC DURATION:
 created at the point of definition and destroyed at the end of the block they are part of, when the
 block is exited.
 this includes:
 _local variables
 _function parameters
 
 VARIABLES WITH STATIC DURATION:
 created when program begins and destroyed when the program ends.
 this includes:
 _global variables
 _static local variables
 
 VARIABLES WITH DYNAMIC DURATION:
 are created and destroyed by programmer request.
 this includes:
 _dynamically allocated variables, like with new keyword in the heap
 ------------------------------------------------------------------------
 
 ------------------------------------LINKAGE SUMMARY----------------------------
 An identifier's linkage : determines whether multiple declarations of an identifier refer to the
 same entity (entity/object/function/reference etc) or not.
 
 IDENTIFIERS WITH NO LINKAGE:
 means the identifier only refers to itself.
 this includes:
 _local variables
 _user defined type definitions like enums and classes declared inside a block
 
 AN IDENTIFIER WITH INTERNAL LINKAGE:
 can be accessed anywhere within the file it is declared.
 this includes:
 _static global variables(initialized/uninitialized)
 _static functions
 _const global variables
 _functions declared inside an unnamed namespace
 _user defined type definitions like enums and classes declared inside a namespace
 
 AN IDENTIFIER WITH EXTERNAL LINKAGE:
 can be accessed anywhere within the file it is declared, or other files (via forward declaration)
 this includes:
 functions
 non-const global variables(initialized/uninitialized)
 extern const global variables
 inline const global variables
 user defined type definitions like enums and classes declared insdie a namespace or in the global
 scope
 ------------------------------------------------------------------------
 
 
 FUNCTIONS : have external linkage by default, can be made internal using the static keyword
 
 --------------------SUMMARIZATION OF VARIABLE'S SCOPE, DURATION AND LINKAGE-------------------------
 
 +--------------------------------------------------------------------------------------------------+
 TYPE                       EXAMPLE                 SCOPE       DURATION        LINKAGE     NOTES
 +--------------------------------------------------------------------------------------------------+
 local variable             int x;                  block       automatic       none
 static local variable      static int s_x;         block       static          none
 dynamic variable           int* x{new int{}};      block       dynamic         none
 function parameter         void foo(int x)         block       automatic       none
 external non const global  int g_x;                file        static          external    init/uni.
 internal non const global  static int g_x;         file        static          internal    init/uni.
 internal const global      constexpr int g_x{1};   file        static          internal    must be i
 external const global      extern const int g_x{1};     file   static          external    must be i
 inline const global C++17  inline constexpr int g_x{1}; file  static          external    must be i
 +--------------------------------------------------------------------------------------------------+
 
 init - for initialized
 uni. - for uninitialized
 must be i - must be initialized

 ----------------------------SUMMARIZATION OF FORWARD DECLARATION----------------------------------
 FORWARD DECLARATION : to access a function or variable in another file, scope of the declared
 variable is as per usual (file scope - globals, block scope - locals)
 +--------------------------------------------------------------------------------------------------+
 TYPE                               EXAMPLE                         NOTES
 +--------------------------------------------------------------------------------------------------+
 function foward declaration        void foo(int x);                prototype only, no body
 non-const variable fwd. decl.      extern int g_x;                 must be uninitialized
 const variable fwd. declaration    extern const int g_x;           must be uninitialized
 constexpr variable fwd. decl.      extern constexpr int g_x;       not allowed, can't be fwd. decld.
 +--------------------------------------------------------------------------------------------------+
 
 
 STORAGE CLASS SPECIFIER:
 they set the storage duration and linkage of the identifier.
 
 4 active storage class specifiers:
 +--------------------------------------------------------------------------------------------------+
 SPECIFIER                               MEANING                         NOTE
 +--------------------------------------------------------------------------------------------------+
 extern                             static duration, external linkage
 static                             static duration, internal linkage
 thread_local                       thread storage duration
 mutable                            object modification allowed, even if containing class is const
 auto                               automatic storage duration          deprecated in C++11
 register                           auto. duration with hit to the compiler to place in a register
                                    deprecated in C++17
 +--------------------------------------------------------------------------------------------------+
 */
