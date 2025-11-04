#include <emscripten/emscripten.h>
#include <emscripten/val.h>
#include <emscripten/bind.h>

// Run Javascript in C++
void Alert(const std::string& msg)
{
    emscripten::val alert = emscripten::val::global("alert");
    alert(msg);
}

int GetLocal(const std::string& key)
{
    emscripten::val localStorage = emscripten::val::global("localStorage");
    emscripten::val item = localStorage.call<emscripten::val>("getItem", key);

    return item.as<int>();
}

void SetLocal(const std::string& key, int value)
{
    emscripten::val localStorage = emscripten::val::global("localStorage");
    emscripten::val item = localStorage.call<emscripten::val>("setItem", key, std::to_string(value));
}

// C++ functions binded and exported into Javascript

int add(int a, int b) {
    return a + b;
}
EMSCRIPTEN_BINDINGS(function_module) {
    emscripten::function("add", &add);
}

int main() {
    Alert("Hello, from C++! :)");

    std::string ITEM = std::to_string(GetLocal("num"));
    Alert(ITEM);
    SetLocal("num", GetLocal("num") + 1);
    std::string NEW_ITEM = "NEW_ITEM: " + std::to_string(GetLocal("num"));
    Alert(NEW_ITEM);
}