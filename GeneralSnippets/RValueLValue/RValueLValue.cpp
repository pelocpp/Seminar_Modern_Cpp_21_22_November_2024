// =====================================================================================
// LValue / RValue
// =====================================================================================

module modern_cpp:rvalue_lvalue;

namespace LValueRValue {

    // lvalue reference
    static void sayHello(std::string& message) {
        std::println("sayHello [std::string&]:  {}", message);
    }

    // rvalue reference
    static void sayHello(std::string&& message) {
        std::println("sayHello [std::string&&]: {}", message);
    }

    static void test01() {

        std::string a = "Hello";

        //std::string&& rvra = "Hello";
        //std::string&& rvra2 = a;

        //std::string& lvra = "Hello";
        //std::string& lvra2 = a;

        std::string b = " World";

        sayHello(a);

        sayHello(a + b);   // Konkatenation: "Hello World"
    }

    // -------------------------------------------------------------------

    static void helper(std::string&& message) {

        sayHello(message);
              // sayHello: std::string&& ==> Gleicher Typ
              // ==> !!! sayHello: std::string& ==> Das Objekt hat einen Namen 
    
        sayHello( std::move (message));
    }

    static void test02() {

        //std::string s{ "adas" };
        //helper(s);

        helper(std::string("Where are we going ..."));
    }

    // -------------------------------------------------------------------

    static void test03() {

        std::string s = "Hello";

        sayHello(s);
        // versus
        sayHello(std::move(s));  // casts an lvalue to an rvalue
    }

    // -------------------------------------------------------------------

    static void test04() {

        // int& i = 2;          // invalid: reference to a constant

        // int a = 2;
        // int b = 3;

        // int& k = a + b;     // invalid: reference to a temporary

        int&& i = 2;           // works: reference to a constant

        int a = 2;
        int b = 3;

        int&& k = a + b;       // works: reference to a temporary
    }
}

void main_rvalue_lvalue()
{ 
    using namespace LValueRValue;
    test01();
    test02();
    test03();
    test04();
}

// =====================================================================================
// End-of-File
// =====================================================================================
