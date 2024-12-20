// =====================================================================================
// Lambda01.cpp // Lambda Methods
// =====================================================================================

module modern_cpp:lambda;

namespace Lambdas {

    static bool compare (int n1, int n2) {
        std::cout << "C-Funktion compare: " << n1 << ", " << n2 << std::endl;
        return n1 < n2;
    }

    class Comparer
    {
    private:
        bool m_flag;

    public:
        Comparer() : m_flag{ true } {}
        Comparer(bool flag) : m_flag{ flag } {}

        bool operator() (int n1, int n2) const 
        {
            std::cout << "operator(): " << n1 << ", " << n2 << std::endl;

            return (m_flag) ? n1 < n2 : n1 > n2;
        }

        bool operator() (int n1, int n2, int n3) const
        {
            return (m_flag) ? n1 < n2 : n1 > n2;
        }
    };

    // =====================================================================================

    static void test_00()
    {
        Comparer obj{ false };

        bool result = obj (1, 2);

        std::cout << std::boolalpha << result << std::endl;
    }

    // =====================================================================================

    static void test_01()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            compare
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_02()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        Comparer cmp{ false };  // Funktor // Callable Object

        std::sort(
            vec.begin(),
            vec.end(),
            cmp
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================


    static void test_seminar()
    {
        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        bool m_upOrDownwards = true;

        std::sort(
            vec.begin(),
            vec.end(),

            [=] (int n1, int n2) {
                std::cout << "Lambda: " << n1 << ", " << n2 << std::endl;
                return (m_upOrDownwards) ? n1 < n2 : n1 > n2;
            }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    static void test_03()
    {
        //void test_yy() {}

        // local class within function possible
        class LocalComparer
        {
        private:
            bool m_flag;

        public:
            LocalComparer() : m_flag{ true } {}
            LocalComparer(bool flag) : m_flag{ flag } {}

            bool operator() (int n1, int n2) const {
                return (m_flag) ? n1 < n2 : n1 > n2;
            }
        };

        std::vector<int> vec{ 5, 6, 4, 1, 3, 2, 7, 8 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            LocalComparer{}
            // LocalComparer{ false }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_04() {

        std::vector<int> vec{ 50, 90, 10, 30, 70, 80 };

        for (int n : vec) {
            std::cout << n << ' ';
        }
        std::cout << std::endl;

        std::sort(
            vec.begin(),
            vec.end(),
            [] (int n1, int n2) { return n1 < n2; }
        );

        for (int n : vec) {
            std::cout << n << ' ';
        }
    }

    // =====================================================================================

    static void test_05() {

        // shortest lambda on earth: no parameters, capturing and doing nothing
        auto nothing = [] {};
        nothing();

        // c'tor notation
        auto itsOne ([] { return 1; });
        auto itsTwo ([] { return 2; });
        std::cout << itsOne() << ", " << itsTwo() << std::endl;

        // "copy-c'tor" notation
        auto itsFour = [] { return 4; };
        auto itsFive = [] { return 5; };
        std::cout << itsFour() << ", " << itsFive() << std::endl;
    }

    static void test_06() {

        auto lll = [] (int x, int y, int z) -> int {
            return x + y + z;
        };

        lll(1, 2, 3);

        // Signatur
        std::function< int(int, int, int)  > lll2 = [](int x, int y, int z) -> int {
            return x + y + z;
            };

        // defining a lambda without 'auto'
        std::function<int(int, int, int)> lambdaWithThreeParams {
            [] (int x, int y, int z) {
                return x + y + z;
            }
        };

        std::cout << lambdaWithThreeParams(5, 6, 7) << std::endl;
    }

    static void test_07() {

        // defining new variables in the lambda capture:
        // we can declare a new variable that is only visible
        // in the scope of the lambda: We do so by defining a variable
        // in the lambda-capture without specifying its type:

     //   int variable = 10;

        // lambda with variable definition
        auto lambda = [variable = 10] () mutable  {
            
          //  int variable = 10;
            variable++;
            return variable;
        };

      //  variable = 131;

        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
        std::cout << lambda() << std::endl;
        return;









        // Captures default to 'const value':
        // The mutable keyword removes the 'const' qualification from all captured variables
        auto counter = [count = 50] () mutable { 
            ++count; 
            return count;
        };

        for (size_t i{}; i < 5; ++i) {
            std::cout << counter() << " ";
        }
        std::cout << std::endl;
    }

    static void test_08(int n) {   // std::function

     //   int n = 1;
        int m = 2;

        // Capture Clause // Erfassungsliste
        auto l1 = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        auto l2 = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        auto l3 = [&, m] {
            std::cout << "Both:      " << n << " " << m << std::endl;
        };

        auto l4 = [=, &m] {
            std::cout << "More both: " << n << " " << m << std::endl;
        };

        n = 3;
        m = 4;

        l1();
        l2();
        l3();
        l4();
    }

    static auto test_09_helper_a() {

        int n = 1;
        int m = 2;

        auto lambda = [=] {
            std::cout << "Copy:      " << n << " " << m << std::endl;
        };

        // std::thread t{ lambda };  dann bitte nur '=' verwenden.

        return lambda;
    }

    static auto test_09_helper_b() {

        int n = 1;
        int m = 2;

        auto lambda = [&] {
            std::cout << "Reference: " << n << " " << m << std::endl;
        };

        return lambda;                                            // I would't do this never ever :-)
    }

    static void test_09() {

        auto outerLambda1 = test_09_helper_a();
        auto outerLambda2 = test_09_helper_b();

        outerLambda1();
        outerLambda2();
    }

    static void test_10() {

        // demonstrating 'noexcept'
        auto itsOne([] () noexcept { return 1; });
        auto itsTwo = [] () noexcept { return 2; };
        std::cout << itsOne() << ", " << itsTwo() << std::endl;
    }

    static void test_11() {

        // IIFE - Immediately Invoked Functional Expression:
        // Inline-definition and direct invocation of lambda funtion:
        
        std::cout << [](int l, int r) { return l + r; } (11, 12) << std::endl;

        // Use case for IIFE:
        // This kind of expression might be useful when you have
        // a complex initialization of a const  object:

        auto constexpr ConstValue = [] () {
            /* several lines of code ... - "very complex" computation */
            return 123;
        }();

        std::cout << "Const Value: " << ConstValue << std::endl;
    }

    //int init()
    //{
    //    return 123;
    //}

    void test_seminar_02()
    {
        std::vector<int> vec(100);  // L�nge: 100

        // 1, 2, 3, 4, 5

        std::generate(
            vec.begin(),
            vec.end(),   // operator() const
            [value = 0u] () mutable /*-> unsigned int*/ {    
                
                value++;
                std::cout << "generate: " << value << "\n";
                return value;
            }
        );
    }
}

void main_lambdas()
{
    using namespace Lambdas;

   // test_seminar();

    test_seminar_02();

    //test_00();
    //test_01();
    //test_02();
    //test_03();
    //test_04();
    //test_05();
    //test_06();
    test_07();
    //test_08(1);
    //test_09();
    //test_10();
    //test_11();
}

// =====================================================================================
// End-of-File
// =====================================================================================
