//
// Created by bagatelle on 6/2/22.
//

#ifndef ALLWPILIB_DATA_H
#define ALLWPILIB_DATA_H

#include <string>
#include <filesystem>
#include <map>
#include <utility>
#include <vector>

#include "wpi/DataLogReader.h"

class LogData {
  public:
    bool LoadWPILog(std::string filename);
};

#endif  // ALLWPILIB_DATA_H
