//
// Created by bagatelle on 5/21/22.
//

#include "Selector.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_stdlib.h>
#include <portable-file-dialogs.h>
#include <wpi/DataLogReader.h>
#include <ostream>
#include <iostream>

#include "App.h"

static wpi::log::DataLogReader m_currentDatalog;

static wpi::log::DataLogReader LoadDataLog(std::string_view filename) {
  std::error_code ec;
  auto buf = wpi::MemoryBuffer::GetFile(filename, ec);
  std::string fn{filename};
  if (ec) {
  }

  wpi::log::DataLogReader reader{std::move(buf)};
  if (!reader.IsValid()) {
    std::cout << "Data log invalid" << std::endl;
  }

  return reader;
}

void DisplayLogSelector() {
  static std::string logFile = "";
  static std::unique_ptr<pfd::open_file> logFileSelector;

  SetNextWindowPos(ImVec2{0, 20}, ImGuiCond_FirstUseEver);
  SetNextWindowSize(ImVec2{500, 100}, ImGuiCond_FirstUseEver);
  if (ImGui::Begin("Input Logs")) {
    if(ImGui::Button("Load Log")) {
      logFileSelector = std::make_unique<pfd::open_file>(
          "Select Data Log", "",
          std::vector<std::string>{"DataLog Files", "*.wpilog"},
          pfd::opt::none);
    }
    ImGui::SameLine();
    ImGui::TextUnformatted(logFile.c_str());

    if(ImGui::Button("Load Video")) {

    }
  }
  ImGui::End();

  if(logFileSelector && logFileSelector->ready(0)) {
    logFile = logFileSelector->result()[0];
    m_currentDatalog = LoadDataLog(logFileSelector->result()[0]);
    logFileSelector.reset();
  }
}