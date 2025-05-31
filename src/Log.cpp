#include "../include/Log.h"
#include <cctype>
#include <sstream>
#include <iomanip>
#include <fstream>

std::string Log::GetLogString() {
  std::ostringstream iss;
  iss << "userId: " << userId;
  iss << ";bikeId: " << bikeId;
  iss << ";timestamp: " << std::put_time(std::localtime(&timestamp), "%Y-%m-%d %H:%M:%S");
  return iss.str();
}

void Log::SaveToFile(std::string path) {
  try {
    std::ofstream outFile;
    outFile.exceptions(std::ofstream::failbit | std::ofstream::badbit);
    outFile.open(path, std::ios::app);
    outFile << GetLogString() << std::endl;
    outFile.close();
  } 
  catch (const std::ofstream::failure& e) {
    throw std::runtime_error(std::string("File write fail at ") + path + ": " + e.what());
  }
}