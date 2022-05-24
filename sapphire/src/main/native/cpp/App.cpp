// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "App.h"

#include <memory>
#include <string_view>

#define IMGUI_DEFINE_MATH_OPERATORS

#include <glass/Context.h>
#include <glass/MainMenuBar.h>
#include <glass/Storage.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <wpigui.h>

#include "Selector.h"

namespace gui = wpi::gui;

const char* GetWPILibVersion();

bool gShutdown = false;

static float gDefaultScale = 1.0;

void SetNextWindowPos(const ImVec2& pos, ImGuiCond cond, const ImVec2& pivot) {
  if ((cond & ImGuiCond_FirstUseEver) != 0) {
    ImGui::SetNextWindowPos(pos * gDefaultScale, cond, pivot);
  } else {
    ImGui::SetNextWindowPos(pos, cond, pivot);
  }
}

void SetNextWindowSize(const ImVec2& size, ImGuiCond cond) {
  if ((cond & ImGuiCond_FirstUseEver) != 0) {
    ImGui::SetNextWindowSize(size * gDefaultScale, cond);
  } else {
    ImGui::SetNextWindowPos(size, cond);
  }
}

static void DisplayMenuBar() {
  ImGui::BeginMainMenuBar();

  static glass::MainMenuBar mainMenu;
  mainMenu.WorkspaceMenu();
  gui::EmitViewMenu();

  bool about = false;
  if(ImGui::BeginMenu("Info")) {
    if(ImGui::MenuItem("About")) {
      about = true;
    }
    ImGui::EndMenu();
  }

  ImGui::EndMainMenuBar();

  if(about) {
    ImGui::OpenPopup("About");
  }
  if(ImGui::BeginPopupModal("About")) {
    ImGui::Text("Sapphire");
    ImGui::Separator();
    ImGui::Text("v%s", GetWPILibVersion());
    ImGui::Separator();
    ImGui::Text("Save location: %s", glass::GetStorageDir().c_str());
    if(ImGui::Button("Close")) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }
}

static void DisplayGui() {
  DisplayMenuBar();
  DisplayLogSelector();
}

void Application(std::string_view saveDir) {
  gui::CreateContext();
  glass::CreateContext();

  glass::SetStorageName("sapphire");
  glass::SetStorageDir(saveDir.empty() ? gui::GetPlatformSaveFileDir()
                                       : saveDir);

  gui::AddWindowScaler([](float scale) { gDefaultScale = scale; });
  gui::AddLateExecute(DisplayGui);
  gui::Initialize("Sapphire", 925, 510);

  gui::Main();

  gShutdown = true;
  glass::DestroyContext();
  gui::DestroyContext();
}
