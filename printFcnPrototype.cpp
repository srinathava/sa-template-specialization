#include <stdio.h>

using namespace std;

/// Print a leaf type
template <typename T>
struct PrintType
{
    static void doit();
};

template <typename T>
struct PrintType<T*>
{
    static void doit()
    {
        PrintType<T>::doit();
        printf("*");
    }
};

template <>
struct PrintType<int>
{
    static void doit()
    {
        printf("int");
    }
};

template <>
struct PrintType<double>
{
    static void doit()
    {
        printf("double");
    }
};

/// Print a list of types
template<typename... T>
struct PrintTypes;

template<typename F, typename... R>
struct PrintTypes<F, R...>
{
    static void doit()
    {
        PrintType<F>::doit();
        printf(", ");
        PrintTypes<R...>::doit();
    }
};

template<typename T>
struct PrintTypes<T>
{
    static void doit() 
    {
        PrintType<T>::doit();
    }
};

/// print a function type
template<typename R, typename... A>
struct PrintType<R (*)(A...)>
{
    static void doit()
    {
        printf("(");
        PrintTypes<A...>::doit();
        printf(") --> (");
        PrintType<R>::doit();
        printf(")");
    }
};

template <typename T>
void printFcn(T arg, const char* fcnName)
{
    printf("%s: ", fcnName);
    PrintType<T>::doit();
}

#define PRINT_FCN(fcn) \
    printFcn(&fcn, #fcn)

typedef int (*BinOp)(int, int);

typedef int (*FcnPtrType)(int, BinOp);

FcnPtrType dummy(int*, double)
{return nullptr;}

int main()
{
    //PrintTypes<int*,int>::doit();

    //PrintFcnType<int (*)(int, int*)>::doit();

    //PrintFcnType<decltype(&dummy)>::doit();

    // Prints the following:
    //  dummy: (int*, double) --> ((int, (int, int) --> (int)) --> (int))
    PRINT_FCN(dummy);

    return 0;
}

