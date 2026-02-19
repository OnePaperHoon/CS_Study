#include <iostream>

class Singleton
{
    public:
        static Singleton& getInstance()
        {
            static Singleton instance;
            return instance;
        }

        void print()
        {
            std::cout << "Hello Singleton" << std::endl;
        }
    private:
        Singleton() { std::cout << "Singleton instance created." << std::endl; }
        ~Singleton() { std::cout << "Singleton instance destroyed." << std::endl; }

        /* 복사/이동 금지 */
        Singleton(const Singleton&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(Singleton&&) = delete;
};

int main()
{
    Singleton& s1 = Singleton::getInstance();
    Singleton& s2 = Singleton::getInstance();

    s1.print();
    s2.print();
    std::cout << (&s1 == &s2) << std::endl;

    return 0;
}