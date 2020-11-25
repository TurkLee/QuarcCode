#pragma once
#include "backend/editor/editor.h"

#include "frontend/libraries/imgui/imgui.h"
#define DIRECTINPUT_VERSION 0x0800

inline DropManager dm;
inline TextEditor editor;
inline ImFont* tahomabig;
inline ImFont* firacode;
inline int _selectedtab = -1;
inline bool _dragndrop = false;