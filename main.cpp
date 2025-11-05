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
void set_text()
{
    emscripten::val document = emscripten::val::global("document");

    emscripten::val p = document.call<emscripten::val>("getElementById", std::string("text_to_change"));
    p.set("innerText", std::string("THIS TEXT HAS BEEN SET BY C++!"));
}

EMSCRIPTEN_BINDINGS(function_module) {
    emscripten::function("add", &add);
    emscripten::function("SetText", &set_text);
}

int main() {
    // Alerting
    Alert("Hello, from C++! :)");

    // Saving local storage
    std::string ITEM = std::to_string(GetLocal("num"));
    Alert(ITEM);
    SetLocal("num", GetLocal("num") + 1);
    std::string NEW_ITEM = "NEW_ITEM: " + std::to_string(GetLocal("num"));
    Alert(NEW_ITEM);

    // Adding items to DOM
    emscripten::val document = emscripten::val::global("document");
    emscripten::val body = document["body"];

    emscripten::val p = document.call<emscripten::val>("createElement", std::string("p"));
    p.set("innerText", std::string("Hello from C++!"));

    body.call<void>("appendChild", p);
}