#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include "Renderer.h"


void onError(int error_code, const char *description);

int main() {


#if __cplusplus == 202002L
    std::cout << "Using C++20\n";
#elif __cplusplus == 201703L
    std::cout << "Using C++17\n";
#elif __cplusplus == 201402L
    std::cout << "Using C++14\n";
#else
    std::cout << "Using unknown or older standard\n";
#endif


    glfwSetErrorCallback(onError);

    std::unique_ptr<Renderer> renderer = std::make_unique<Renderer>();
    return 0;
}

void onError(int error_code, const char *description) {
    printf("%d -- %s\n", error_code, description);
}
