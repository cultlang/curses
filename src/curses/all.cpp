
#include "curses/common.h"

#include "all.h"

// Vendor
#include "curses/pdcwin.h"
#include "curses/panel.h"

using namespace craft;
using namespace craft::lisp;
using namespace craft::types;
using namespace cultlang::curses;


#define lMM sem->builtin_implementMultiMethod
#define MoD "curses"


typedef instance<std::string> t_Str;
typedef instance<int8_t> t_I8;
typedef instance<int16_t> t_I16;
typedef instance<int32_t> t_I32;

typedef instance<uint8_t> t_U8;
typedef instance<uint16_t> t_U16;
typedef instance<uint32_t> t_U32;

typedef instance<Window> t_Win;

#ifdef CHTYPE_LONG
# if _LP64
typedef instance<uint32_t> t_Chr;
typedef instance<uint32_t> t_Attr;
# else
typedef instance<uint64_t> t_Chr;
typedef instance<uint64_t> t_Attr;
# endif
#else
typedef instance<uint16_t> t_Chr;
typedef instance<uint16_t> t_Attr;
#endif

CRAFT_DEFINE(Window)
{
	_.defaults();
}

Window::Window(void* d) : data(d) {}

void cultlang::curses::make_bindings(craft::instance<craft::lisp::Module> ret)
{
	auto sem = ret->require<lisp::CultSemantics>();

	lMM(MoD"/setlocale", [](t_Str s) { setlocale(LC_ALL, s->c_str()); });

	lMM(MoD"/char", [](t_Str i) { return t_Chr::make(i->at(0)); });
	lMM(MoD"/string", [](t_I8 i) { return t_Str::make(1, *i); });

	lMM(MoD"/initscr", []() { initscr(); });
	lMM(MoD"/raw", []() { initscr(); });

	lMM(MoD"/keypad", [](instance<bool> b) { keypad(stdscr, int(*b)); });
	lMM(MoD"/keypad", [](t_Win w, instance<bool> b) { keypad((WINDOW*)w->data, int(*b)); });
	lMM(MoD"/noecho", []() { noecho(); });

	//// Info
	//lMM(MoD"/width", []() {
	//	
	//})

	// output
	lMM(MoD"/addch", [](t_Str s) { addch(s->at(0)); });
	lMM(MoD"/addch", [](t_Win w,  t_Str s) { waddch((WINDOW*)w->data, s->at(0)); });

	lMM(MoD"/mvaddch", [](t_I32 x, t_I32 y, t_Str s) { mvaddch(*x, *y, s->at(0)); });
	lMM(MoD"/mvaddch", [](t_Win w, t_I32 x, t_I32 y, t_Str s) { mvwaddch((WINDOW*)w->data, *x, *y, s->at(0)); });

	lMM(MoD"/echochar", [](t_Str s) { echochar(s->at(0)); });
	lMM(MoD"/echochar", [](t_Win w, t_Str s) { wechochar((WINDOW*)w->data, s->at(0)); });

	lMM(MoD"/printw", [](t_Str s) { return t_I32::make(printw(s->c_str())); });
	lMM(MoD"/printw", [](t_Win w, t_Str s) { wprintw((WINDOW*)w->data,  s->c_str()); });

	lMM(MoD"/mvprintw", [](t_I32 x, t_I32 y, t_Str s) { mvprintw(*x, *y, s->c_str()); });
	lMM(MoD"/mvprintw", [](t_Win w, t_I32 x, t_I32 y, t_Str s) { mvwprintw((WINDOW*)w->data, *x, *y, s->c_str()); });


	// input
	lMM(MoD"/getch", []() { return t_I8::make(getch()); });
	lMM(MoD"/keyf", [](t_I8 i) { return t_I8::make(KEY_F0 + *i); });


	 
	lMM(MoD"/color/start-color", []() { return instance<int32_t>::make(start_color()); });
	lMM(MoD"/color/has-color", []() { return instance<bool>::make(has_colors()); });
	lMM(MoD"/color/can-change-color", []() { return instance<bool>::make(can_change_color()); });
	lMM(MoD"/color/init-pair", [](t_I16 pair, t_I16 f, t_I16 b) { return t_I32::make(init_pair(*pair, *f, *b)); });
	lMM(MoD"/color/init-color", [](t_I16 color, t_I16 r, t_I16 g, t_I16 b) { return t_I32::make(init_color(*color, *r, *g, *b)); });

	lMM(MoD"/attr-on", [](t_Attr s) {  t_I32::make(attron(*s)); });
	lMM(MoD"/attr-on", [](t_Win w, t_Attr s) { wattron((WINDOW*)w->data, *s); });

	lMM(MoD"/attr-off", [](t_Attr s) { attroff(*s); });
	lMM(MoD"/attr-off", [](t_Win w, t_Attr s) { wattroff((WINDOW*)w->data, *s); });

	
	lMM(MoD"/refresh", []() { refresh(); });
	lMM(MoD"/endwin", []() { endwin(); });

	lMM(MoD"/attr/normal", []() { return t_Attr::make(A_NORMAL); });
	lMM(MoD"/attr/standout", []() { return t_Attr::make(A_STANDOUT); });
	lMM(MoD"/attr/underline", []() { return t_Attr::make(A_UNDERLINE); });
	lMM(MoD"/attr/reverse", []() { return t_Attr::make(A_REVERSE); });
	lMM(MoD"/attr/blink", []() { return t_Attr::make(A_BLINK); });
	lMM(MoD"/attr/dim", []() { return t_Attr::make(A_DIM); });
	lMM(MoD"/attr/bold", []() { return t_Attr::make(A_BOLD); });
	lMM(MoD"/attr/protect", []() { return t_Attr::make(A_PROTECT); });
	lMM(MoD"/attr/invis", []() { return t_Attr::make(A_INVIS); });
	lMM(MoD"/attr/altcharset", []() { return t_Attr::make(A_ALTCHARSET); });
	lMM(MoD"/attr/italic", []() { return t_Attr::make(A_ITALIC); });
	lMM(MoD"/attr/chartext", []() { return t_Attr::make(A_CHARTEXT); });
	lMM(MoD"/attr/color", []() { return t_Attr::make(A_COLOR); });

	lMM(MoD"/attr/horizontal", []() { return t_Attr::make(WA_HORIZONTAL); });
	lMM(MoD"/attr/left", []() { return t_Attr::make(WA_LEFT); });
	lMM(MoD"/attr/low", []() { return t_Attr::make(WA_LOW); });
	lMM(MoD"/attr/right", []() { return t_Attr::make(WA_RIGHT); });
	lMM(MoD"/attr/top", []() { return t_Attr::make(WA_TOP); });
	lMM(MoD"/attr/vertical", []() { return t_Attr::make(WA_VERTICAL); });

	//lMM(MoD"/window/create", []() { return t_Attr::make(WA_VERTICAL); });
	lMM(MoD"/window/create", [](t_I32 nlines, t_I32 ncols, t_I32 begin_y, t_I32 begin_x) {
		auto data = newwin(*nlines, *ncols, *begin_y, *begin_x);
		return t_Win::make(data);
	});

	lMM(MoD"/window/delete", [](t_Win t) {delwin((WINDOW*)t->data); });
	lMM(MoD"/window/mv", [](t_Win t, t_I32 x, t_I32 y) {mvwin((WINDOW*)t->data, *x, *y); });
	lMM(MoD"/window/sub", [](t_Win t, t_I32 nlines, t_I32 ncols, t_I32 begin_y, t_I32 begin_x) {
		auto data = subwin((WINDOW*)t->data, *nlines, *ncols, *begin_y, *begin_x);
		return t_Win::make(data);
	});
	lMM(MoD"/window/der", [](t_Win t, t_I32 nlines, t_I32 ncols, t_I32 begin_y, t_I32 begin_x) {
		auto data = derwin((WINDOW*)t->data, *nlines, *ncols, *begin_y, *begin_x);
		return t_Win::make(data);
	});
	lMM(MoD"/window/mvder", [](t_Win t, t_I32 par_y, t_I32 par_x) {mvderwin((WINDOW*)t->data, *par_y, *par_x); });
	lMM(MoD"/window/dup", [](t_Win t) {
		auto data = dupwin((WINDOW*)t->data);
		return t_Win::make(data);
	});
	
	lMM(MoD"/border", [](t_Str s) { 
		if (s->size() != 8) throw stdext::exception("Border string must be eight characters ");
		border(s->at(0), s->at(1), s->at(2), s->at(3), s->at(4), s->at(5), s->at(6), s->at(7));
	});

	lMM(MoD"/border", [](t_Win t, t_Str s) {
		if (s->size() != 8) throw stdext::exception("Border string must be eight characters ");
		wborder((WINDOW*)t->data, s->at(0), s->at(1), s->at(2), s->at(3), s->at(4), s->at(5), s->at(6), s->at(7));
	});

	lMM(MoD"/box", [](t_Win t, t_Str s) {
		if (s->size() != 2) throw stdext::exception("Box string must be two characters ");
		box((WINDOW*)t->data, s->at(0), s->at(1));
	});

	lMM(MoD"/hline", [](t_Str ch, t_I32 n) { hline(ch->at(0), *n); });
	lMM(MoD"/hline", [](t_Win t, t_Str ch, t_I32 n) { whline((WINDOW*)t->data, ch->at(0), *n); });

	lMM(MoD"/vline", [](t_Str ch, t_I32 n) { vline(ch->at(0), *n); });
	lMM(MoD"/vline", [](t_Win t, t_Str ch, t_I32 n) { wvline((WINDOW*)t->data, ch->at(0), *n); });

	lMM(MoD"/mvhline", [](t_I32 x, t_I32 y, t_Str ch, t_I32 n) { mvhline(*x, *y, ch->at(0), *n); });
	lMM(MoD"/mvhline", [](t_Win t, t_I32 x, t_I32 y, t_Str ch, t_I32 n) { mvwhline((WINDOW*)t->data, *x, *y, ch->at(0), *n); });

	lMM(MoD"/mvhline", [](t_I32 x, t_I32 y, t_Str ch, t_I32 n) { mvvline(*x, *y, ch->at(0), *n); });
	lMM(MoD"/mvhline", [](t_Win t, t_I32 x, t_I32 y, t_Str ch, t_I32 n) { mvwvline((WINDOW*)t->data, *x, *y, ch->at(0), *n); });

}

BuiltinModuleDescription cultlang::curses::BuiltinCurses("cultlang/curses", cultlang::curses::make_bindings);


#include "types/dll_entry.inc"
