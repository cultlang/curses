
#pragma once
#include "curses/common.h"


namespace cultlang {
namespace curses 
{
  extern craft::lisp::BuiltinModuleDescription BuiltinCurses;

  CULTLANG_CURSES_EXPORTED void make_bindings(craft::instance<craft::lisp::Module> ret);

  class Window
	  : public craft::types::Object
  {
	  CULTLANG_CURSES_EXPORTED CRAFT_OBJECT_DECLARE(cultlang::curses::Window);

  public:
	  void* data;

  public:
	  Window(void* window);
  };

}}  

