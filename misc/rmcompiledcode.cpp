#include <filesystem>
#include <iostream>
namespace fs = std::filesystem;

bool checkObjorExe(const fs::path filepath)
{   
    return
    (filepath.extension() == ".exe" || filepath.extension() == ".obj")
        &&
        !(filepath.filename() == "rmcompiledcode.exe")
    ;   
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    const fs::path cwd{ fs::current_path() };

    for (const auto& file : fs::directory_iterator(cwd))
        if (checkObjorExe(file.path()))
        {   
            std::cout << "Removing: " << file.path().filename() << '\n';
            fs::remove(file.path());
        }
    return 0;
}