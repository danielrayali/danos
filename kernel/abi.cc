__extension__ typedef int __guard __attribute__((mode(__DI__)));

extern "C" int __cxa_guard_acquire (__guard *) {
    return 0;
}

extern "C" void __cxa_guard_release (__guard *) {
    
}

extern "C" void operator delete(void*) {

}