#include "reloadable_library.hpp"

#include <windows.h>

#include <chrono>
#include <filesystem>
#include <print>
#include <thread>

std::filesystem::path getNewestLibraryPath() {
  namespace fs = std::filesystem;
  fs::path aPath{"reloadable_library_a.dll"};
  fs::path bPath{"reloadable_library_b.dll"};

  const bool aExists = fs::exists(aPath);
  const bool bExists = fs::exists(bPath);

  std::println("aExists: {}, bExists: {}", aExists, bExists);
  if (!aExists && !bExists)
    return {};

  if (aExists && !bExists)
    return aPath;
  
  if (!aExists && bExists)
    return bPath;

  const fs::file_time_type aTime = fs::last_write_time(aPath);
  const fs::file_time_type bTime = fs::last_write_time(bPath);

  return (aTime > bTime) ? aPath : bPath;
}

int main() {
  std::println("Hello, Hot Reload!");

  HMODULE libraryHandle{};

  while(true) {
    const auto newestPath = getNewestLibraryPath();
    if (newestPath.empty()) {
      std::println("No library found. Exiting...");
      return 0;
    }
    std::println("Newest library: {}", newestPath.string());

    HMODULE newlibraryHandle = LoadLibraryA(newestPath.string().c_str());
    if (!newlibraryHandle) {
        std::println("Failed to load library. Will continue with existing version.");
    }
    else {
      if (libraryHandle)
        FreeLibrary(libraryHandle);
      libraryHandle = newlibraryHandle;
    }

    if (!libraryHandle) {
      std::println("Failed to load library. Exiting...");
      return 0;
    }
    auto calculate = (CalculateFunc)GetProcAddress(libraryHandle, "calculate");
    if (!calculate) {
      std::println("Failed to get function address");
      FreeLibrary(libraryHandle);
      return 0;
    }

    const int result = calculate(2, 3);
    std::println("calculate(2, 3) = {}", result);

    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  if (libraryHandle)
    FreeLibrary(libraryHandle);
  return 0;
}