// con1.cpp
// Connie UltraLite by Kuvshinov D.R.
// version alpha 12
// Implementation part.
// Single-threaded for simplicity.
#ifndef CON1_CPP_INCLUDED_2V3U3C
#define CON1_CPP_INCLUDED_2V3U3C

#if !CON1_HEADER_ONLY
#include "con1.h"
#endif

#include <bitset>
#include <memory>
#include <chrono>
#include <cstring>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif


namespace con1
{

	// Uses C++11 Chrono.
	CON1_API_INLINE double seconds()
	{
		using namespace std::chrono;
		const static auto starting_time = high_resolution_clock::now();
		return (duration_cast<nanoseconds>(high_resolution_clock::now() - starting_time)).count() * 1.0e-9;
	}


	CON1_API_INLINE const char * key::get_name(unsigned k)
	{
		static const char * const names[256] =
		{
		  "none",      // 0
		  "numlock_on", // 1
		  "scrolllock_on", // 2
		  "capslock_on", // 3
		  "numlock",    // 4
		  "scroll",     // 5
		  "capslock",   // 6
		  "(07)",       // 7
		  "backspace",  // 8
		  "tab",        // 9
		  "return_key", // 10
		  "(0B)", "(0C)", "(0D)", "(0E)", "(0F)",
		  "(10)", "(11)", "(12)", "(13)", "(14)", "(15)", "(16)", "(17)",
		  "(18)", "(19)", "(1A)",
		  "escape",     // 27
		  "(1C)", "(1D)", "(1E)", "(1F)",
		  "space",      // 32
		  "(21)", "(22)", "(23)", "(24)", "(25)", "(26)",
		  "quote",      // 39
		  "(28)", "(29)", "(2A)", "(2B)",
		  "comma",      // 44
		  "dash",       // 45
		  "period",     // 46
		  "slash",      // 47
		  "0",          // 48
		  "1",          // 49
		  "2",          // 50
		  "3",          // 51
		  "4",          // 52
		  "5",          // 53
		  "6",          // 54
		  "7",          // 55
		  "8",          // 56
		  "9",          // 57
		  "(3A)",
		  "semicolon",  // 59
		  "(3C)",
		  "equals",     // 61
		  "(3E)", "(3F)", "(40)",
		  "A",          // 65
		  "B",          // 66
		  "C",          // 67
		  "D",          // 68
		  "E",          // 69
		  "F",          // 70
		  "G",          // 71
		  "H",          // 72
		  "I",          // 73
		  "J",          // 74
		  "K",          // 75
		  "L",          // 76
		  "M",          // 77
		  "N",          // 78
		  "O",          // 79
		  "P",          // 80
		  "Q",          // 81
		  "R",          // 82
		  "S",          // 83
		  "T",          // 84
		  "U",          // 85
		  "V",          // 86
		  "W",          // 87
		  "X",          // 88
		  "Y",          // 89
		  "Z",          // 90
		  "open_bracket", // 91
		  "backslash",  // 92
		  "close_bracket", // 93
		  "(5E)", "(5F)",
		  "grave",      // 96
		  "(61)", "(62)", "(63)", "(64)", "(65)", "(66)", "(67)",
		  "(68)", "(69)", "(6A)", "(6B)", "(6C)", "(6D)", "(6E)", "(6F)",
		  "(70)", "(71)", "(72)", "(73)", "(74)", "(75)", "(76)", "(77)",
		  "(78)", "(79)", "(7A)", "(7B)", "(7C)", "(7D)", "(7E)",
		  "delete_key",  // 127
		  "right_ctrl",  // 128
		  "left_ctrl",   // 129
		  "left_shift",  // 130
		  "right_shift", // 131
		  "left_alt",    // 132
		  "right_alt",   // 133
		  "left_win",    // 134
		  "right_win",   // 135
		  "applications", // 136
		  "left",        // 137
		  "up",          // 138
		  "right",       // 139
		  "down",        // 140
		  "pause",       // 141
		  "page_up",     // 142
		  "page_down",   // 143
		  "end",         // 144
		  "home",        // 145
		  "print_scr",   // 146
		  "insert",      // 147
		  "numpad_0",    // 148
		  "numpad_1",    // 149
		  "numpad_2",    // 150
		  "numpad_3",    // 151
		  "numpad_4",    // 152
		  "numpad_5",    // 153
		  "numpad_6",    // 154
		  "numpad_7",    // 155
		  "numpad_8",    // 156
		  "numpad_9",    // 157
		  "numpad_asterisk", // 158
		  "numpad_plus", // 159
		  "numpad_minus", // 160
		  "numpad_slash", // 161
		  "numpad_separator", // 162
		  "numpad_decimal",   // 163
		  "F1",    // 164
		  "F2",    // 165
		  "F3",    // 166
		  "F4",    // 167
		  "F5",    // 168
		  "F6",    // 169
		  "F7",    // 170
		  "F8",    // 171
		  "F9",    // 172
		  "F10",   // 173
		  "F11",   // 174
		  "F12",   // 175
		  "F13",   // 176
		  "F14",   // 177
		  "F15",   // 178
		  "F16",   // 179
		  "F17",   // 180
		  "F18",   // 181
		  "F19",   // 182
		  "F20",   // 183
		  "F21",   // 184
		  "F22",   // 185
		  "F23",   // 186
		  "F24",   // 187
		  "(BC)", "(BD)", "(BE)", "(BF)",
		  "(C0)", "(C1)", "(C2)", "(C3)", "(C4)", "(C5)", "(C6)", "(C7)",
		  "(C8)", "(C9)", "(CA)", "(CB)", "(CC)", "(CD)", "(CE)", "(CF)",
		  "(D0)", "(D1)", "(D2)", "(D3)", "(D4)", "(D5)", "(D6)", "(D7)",
		  "(D8)", "(D9)", "(DA)", "(DB)", "(DC)", "(DD)", "(DE)", "(DF)",
		  "(E0)", "(E1)", "(E2)", "(E3)", "(E4)", "(E5)", "(E6)", "(E7)",
		  "(E8)", "(E9)", "(EA)", "(EB)", "(EC)", "(ED)", "(EE)", "(EF)",
		  "(F0)", "(F1)", "(F2)", "(F3)", "(F4)", "(F5)", "(F6)", "(F7)",
		  "(F8)", "(F9)", "(FA)", "(FB)", "(FC)", "(FD)", "(FE)", "(FF)"
		};

		return names[k & 0xFF];
	}


	// Uses Win32 API, but might have been using std::thread::sleep_for instead.
	CON1_API_INLINE void sleep(unsigned ms)
	{
		Sleep(ms);
	}


	namespace impl
	{
		using std::memcpy;

		/// Console controller module, incapsulates all the implementation details.
		class Console
		{
			friend void con1::delay();
			friend void con1::cursor_visible(bool);
			friend void con1::input_echo(bool);
			friend void con1::at(int, int);
			friend int con1::at_x();
			friend int con1::at_y();
			friend int con1::width();
			friend int con1::height();
			friend void con1::ink(unsigned);
			friend void con1::paper(unsigned);
			friend void con1::ink_paper(unsigned, unsigned);
			friend void con1::cls();
			friend bool con1::is_pressed(unsigned);
			friend void con1::discard_input();
			friend void con1::set_input_mode(con1::mode::Input);
			friend void con1::sync_input();
			friend unsigned con1::get_last_key();
			friend void con1::color::get_palette(std::uint32_t palette[16]);
			friend void con1::color::set_palette(const std::uint32_t palette[16]);
			friend void con1::color::restore_default_palette();
			friend void con1::reset_key(unsigned, bool);
			friend void con1::reset_all_keys();
			friend void con1::draw(const con1::Achar_block&);

			// State.
			std::bitset<256> kbd;
			int con_width, con_height, cur_x, cur_y;
			unsigned con_attr;
			unsigned last_key;

			con1::mode::Input input_mode;

			HWND global_con_handle;
			HANDLE global_in, global_out;

			COLORREF palette[16];
			COLORREF default_palette[16];

			// Console is a singleton.
			static Console& object()
			{
				static Console obj;
				return obj;
			}


			// Functionality.
			Console();
			~Console() = default;
			Console(Console&) = delete;

			// Refresh stored console data.
			void refresh();

			// Discard all input.
			void discard_input();

			// Parse input events reported by Windows and change kbd accordingly.
			// Returns -1 if a key was pressed, +1 if a key was released, 0 if no key event happened.
			int parse_input_events();

			// Set the current console cursor position.
			void set_cursor(int x, int y);

			// Set the new current attribute.
			void set_attr(unsigned attr);

			// Clear screen.
			void clear_screen();

			// Set the current palette.
			void set_palette(const COLORREF new_palette[16]);

			// Draw attributed char block.
			void draw_block(const CHAR_INFO *buf, unsigned x, unsigned y, unsigned w, unsigned h);
		};

	}


	CON1_API_INLINE void cursor_visible(bool visible)
	{
		CONSOLE_CURSOR_INFO cursor_info{};
		const auto handle = impl::Console::object().global_out;
		GetConsoleCursorInfo(handle, &cursor_info);
		cursor_info.bVisible = visible;
		SetConsoleCursorInfo(handle, &cursor_info);
	}

	CON1_API_INLINE void input_echo(bool enabled)
	{
		DWORD mode = 0;
		const auto handle = impl::Console::object().global_out;
		GetConsoleMode(handle, &mode);
		if (enabled && !(mode & ENABLE_ECHO_INPUT))
			SetConsoleMode(handle, mode | ENABLE_ECHO_INPUT);
		else if (!enabled && (mode & ENABLE_ECHO_INPUT))
			SetConsoleMode(handle, mode & ~ENABLE_ECHO_INPUT);
	}


	CON1_API_INLINE void at(int x, int y)
	{
		impl::Console::object().set_cursor(x, y);
	}

	CON1_API_INLINE int at_x()
	{
		auto &obj = impl::Console::object();
		obj.refresh();
		return obj.cur_x;
	}

	CON1_API_INLINE int at_y()
	{
		auto &obj = impl::Console::object();
		obj.refresh();
		return obj.cur_y;
	}

	CON1_API_INLINE int width()
	{
		auto &obj = impl::Console::object();
		obj.refresh();
		return obj.con_width;
	}

	CON1_API_INLINE int height()
	{
		auto &obj = impl::Console::object();
		obj.refresh();
		return obj.con_height;
	}

	CON1_API_INLINE void ink(unsigned col)
	{
		auto &obj = impl::Console::object();
		obj.set_attr(color::attr(col, color::paper_of(obj.con_attr)));
	}

	CON1_API_INLINE void paper(unsigned col)
	{
		auto &obj = impl::Console::object();
		obj.set_attr(color::attr(color::ink_of(obj.con_attr), col));
	}

	CON1_API_INLINE void ink_paper(unsigned i, unsigned p)
	{
		impl::Console::object().set_attr(color::attr(i, p));
	}

	CON1_API_INLINE void cls()
	{
		auto &obj = impl::Console::object();
		obj.clear_screen();
		obj.set_cursor(0, 0);
	}

	CON1_API_INLINE bool is_pressed(unsigned key_code)
	{
		auto &obj = impl::Console::object();
		if (obj.input_mode == mode::async_input)
			obj.parse_input_events();
		return obj.kbd[key_code & 0xFF];
	}

	CON1_API_INLINE void reset_key(unsigned key_code, bool pressed)
	{
		impl::Console::object().kbd[key_code & 0xFF] = pressed;
	}

	CON1_API_INLINE void reset_all_keys()
	{
		impl::Console::object().kbd.reset();
	}

	CON1_API_INLINE void discard_input()
	{
		impl::Console::object().discard_input();
	}

	CON1_API_INLINE void set_input_mode(mode::Input in_mode)
	{
		impl::Console::object().input_mode = in_mode;
	}

	CON1_API_INLINE void sync_input()
	{
		impl::Console::object().parse_input_events();
	}

	CON1_API_INLINE unsigned get_last_key()
	{
		auto &obj = impl::Console::object();
		if (obj.input_mode == mode::async_input)
			obj.parse_input_events();

		const auto result = obj.last_key;
		obj.last_key = key::none;

		return result;
	}

	CON1_API_INLINE void delay()
	{
		auto &obj = impl::Console::object();
		obj.parse_input_events();
		// Wait until any key hit.
		do sleep(60);
		while (obj.parse_input_events() == 0);
	}


	CON1_API_INLINE void draw(const Achar_block &block)
	{
		static const unsigned SCR_SIZE = 32768;
		static Achar composite[SCR_SIZE];
		const auto max_rows = SCR_SIZE / block.cols();
		Achar_block composite_view(
			&composite[0],
			(block.rows() < max_rows ? block.rows() : max_rows),
			block.cols());

		block.copy_to(composite_view);

		auto &obj = impl::Console::object();
		const auto
			default_paper = color::paper_of(obj.con_attr),
			default_ink = color::ink_of(obj.con_attr);

		for (size_t iend = composite_view.rows() * composite_view.cols(), i = 0; i < iend; ++i)
			composite[i].override_default_attr(default_ink, default_paper);

		obj.draw_block
		(
			static_cast<const CHAR_INFO*>(static_cast<const void*>(composite)),
			obj.cur_x, obj.cur_y, composite_view.cols(), composite_view.rows()
		);
	}


	namespace color
	{
		CON1_API_INLINE void get_palette(std::uint32_t palette[16])
		{
			std::memcpy(palette,
				static_cast<const std::uint32_t*>(static_cast<void*>(con1::impl::Console::object().palette)),
				sizeof(std::uint32_t) * 16);
		}

		CON1_API_INLINE void set_palette(const std::uint32_t palette[16])
		{
			con1::impl::Console::object().set_palette(
				static_cast<const COLORREF*>(static_cast<const void*>(palette)));
		}

		CON1_API_INLINE void restore_default_palette()
		{
			auto &obj = con1::impl::Console::object();
			obj.set_palette(obj.default_palette);
		}

		CON1_API_INLINE void set_smyck_palette()
		{
			static const std::uint32_t smyck_palette[16] =
			{
			  0x000000, /*black*/
			  0xccb372, /*dark blue*/
			  0x3bb38e, /*dark green*/
			  0x938621, /*dark cyan*/
			  0x4656c7, /*dark red*/
			  0xd1a0c8, /*dark magenta*/
			  0x3cb0d0, /*dark yellow*/
			  0xb0b0b0, /*grey*/

			  0x5d5d5d, /*dark grey*/
			  0xf0d99c, /*blue*/
			  0x69eecd, /*green*/
			  0xd8df77, /*cyan*/
			  0x9096e0, /*red*/
			  0xf9b1fb, /*magenta*/
			  0x77e3ff, /*yellow*/
			  0xf7f7f7  /*white*/
			};

			set_palette(smyck_palette);
		}
	}


	// Console implementation, Windows based
	// The real Windows dependencies are here.
	namespace impl
	{

		CON1_API_INLINE Console::Console()
			: con_width(0), con_height(0), cur_x(0), cur_y(0),
			con_attr(color::attr(color::grey, color::black)),
			last_key(key::none),
			input_mode(con1::mode::async_input),
			global_con_handle(NULL), global_in(NULL), global_out(NULL)
		{
			cout.flush();
			cin.sync();

			global_con_handle = GetConsoleWindow();
			if (global_con_handle == NULL)
			{
				if (/*global_con_owned =*/ (AllocConsole() == TRUE))
					global_con_handle = GetConsoleWindow();
				// else what? currently ignored
			}

			global_in = CreateFileW(L"CONIN$",
				GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			global_out = CreateFileW(L"CONOUT$",
				GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
			//global_in = GetStdHandle(STD_INPUT_HANDLE);
			//global_out = GetStdHandle(STD_OUTPUT_HANDLE);

			refresh();
			memcpy(default_palette, palette, sizeof(palette));
		}


		CON1_API_INLINE void Console::refresh()
		{
			CONSOLE_SCREEN_BUFFER_INFOEX sbi = { sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
			if (GetConsoleScreenBufferInfoEx(global_out, &sbi))
			{
				this->con_attr = sbi.wAttributes;
				this->con_width = sbi.dwMaximumWindowSize.X;
				this->con_height = sbi.dwMaximumWindowSize.Y;
				this->cur_x = sbi.dwCursorPosition.X;
				this->cur_y = sbi.dwCursorPosition.Y;
				memcpy(palette, sbi.ColorTable, sizeof(palette));
			}
			// else what? currently ignored
		}


		CON1_API_INLINE void Console::discard_input()
		{
			FlushConsoleInputBuffer(global_in);
		}


		CON1_API_INLINE int Console::parse_input_events()
		{
			DWORD events = 0;
			int result = 0;

			if (GetNumberOfConsoleInputEvents(global_in, &events) && events > 0)
			{
				std::unique_ptr<INPUT_RECORD[]> input_events(new INPUT_RECORD[events]);
				DWORD ner = 0;
				if (ReadConsoleInputW(global_in, input_events.get(), events, &ner))
					for (DWORD i = 0; i < ner; ++i)
					{
						const auto &e = input_events[i];
						const auto ctrl = e.Event.KeyEvent.dwControlKeyState;
						kbd[key::numlock_on] = (ctrl & 0x0020) != 0;
						kbd[key::scrolllock_on] = (ctrl & 0x0040) != 0;
						kbd[key::capslock_on] = (ctrl & 0x0080) != 0;

						// The following code conflicts with interpreting of KEY_EVENT below.
						//kbd[key::left_alt]   = (ctrl & 0x0002) != 0;
						//kbd[key::right_alt]  = (ctrl & 0x0001) != 0;
						//kbd[key::left_ctrl]  = (ctrl & 0x0008) != 0;
						//kbd[key::right_ctrl] = (ctrl & 0x0004) != 0;

						bool left = false, right = false;
						switch (e.EventType)
						{
						case KEY_EVENT:
						{
							const bool is_down = e.Event.KeyEvent.bKeyDown == TRUE;
							// ignored: e.Event.KeyEvent.uChar.UnicodeChar
							// ignored: e.Event.KeyEvent.wRepeatCount
							// ignored: e.Event.KeyEvent.wVirtualScanCode
							// Parse
							unsigned k = e.Event.KeyEvent.wVirtualKeyCode;
							switch (k)
							{
							case VK_BACK:   k = key::backspace; break;
							case VK_TAB:    k = key::tab; break;
							case VK_RETURN: k = key::return_key; break;

							case VK_SHIFT:  k = key::none;
								left = GetAsyncKeyState(VK_LSHIFT) < 0;
								right = GetAsyncKeyState(VK_RSHIFT) < 0;

								if (kbd[key::left_shift] && !left)
									last_key = key::left_shift;
								else if (kbd[key::right_shift] && !right)
									last_key = key::right_shift;

								kbd[key::left_shift] = left;
								kbd[key::right_shift] = right;
								break;

							case VK_CONTROL: k = key::none;
								left = GetAsyncKeyState(VK_LCONTROL) < 0;
								right = GetAsyncKeyState(VK_RCONTROL) < 0;

								if (kbd[key::left_ctrl] && !left)
									last_key = key::left_ctrl;
								else if (kbd[key::right_ctrl] && !right)
									last_key = key::right_ctrl;

								kbd[key::left_ctrl] = left;
								kbd[key::right_ctrl] = right;
								break;

							case VK_MENU:    k = key::none;
								left = GetAsyncKeyState(VK_LMENU) < 0;
								right = GetAsyncKeyState(VK_RMENU) < 0;

								if (kbd[key::left_alt] && !left)
									last_key = key::left_alt;
								else if (kbd[key::right_alt] && !right)
									last_key = key::right_alt;

								kbd[key::left_alt] = left;
								kbd[key::right_alt] = right;
								break;

							case VK_PAUSE:   k = key::pause; break;
							case VK_CAPITAL: k = key::capslock; break;
								//case VK_KANA:
								//case VK_HANGEUL:
								//case VK_HANGUL:
								//case VK_JUNJA:
								//case VK_FINAL:
								//case VK_HANJA:
								//case VK_KANJI:
							case VK_ESCAPE: k = key::escape; break;
								//case VK_CONVERT:
								//case VK_NONCONVERT:
								//case VK_ACCEPT:
								//case VK_MODECHANGE:
							case VK_SPACE:  k = key::space; break;
							case VK_PRIOR:  k = key::page_up; break;
							case VK_NEXT:   k = key::page_down; break;
							case VK_END:    k = key::end; break;
							case VK_HOME:   k = key::home; break;
							case VK_LEFT:   k = key::left; break;
							case VK_UP:     k = key::up; break;
							case VK_RIGHT:  k = key::right; break;
							case VK_DOWN:   k = key::down; break;
								//case VK_SELECT:
							case VK_PRINT:    // actually doesn't work
							case VK_SNAPSHOT: k = key::print_scr;  break;
								//case VK_EXECUTE:
							case VK_INSERT: k = key::insert; break;
							case VK_DELETE: k = key::delete_key; break;
								//case VK_HELP:
							case VK_LWIN:   k = key::left_win; break;
							case VK_RWIN:   k = key::right_win; break;
							case VK_APPS:   k = key::applications; break;
								//case VK_SLEEP:  k = key::sleep; break;
							case VK_NUMPAD0: k = key::numpad_0; break;
							case VK_NUMPAD1: k = key::numpad_1; break;
							case VK_NUMPAD2: k = key::numpad_2; break;
							case VK_NUMPAD3: k = key::numpad_3; break;
							case VK_NUMPAD4: k = key::numpad_4; break;
							case VK_NUMPAD5: k = key::numpad_5; break;
							case VK_NUMPAD6: k = key::numpad_6; break;
							case VK_NUMPAD7: k = key::numpad_7; break;
							case VK_NUMPAD8: k = key::numpad_8; break;
							case VK_NUMPAD9: k = key::numpad_9; break;
							case VK_MULTIPLY: k = key::numpad_asterisk; break;
							case VK_ADD:     k = key::numpad_plus; break;
							case VK_SEPARATOR: k = key::numpad_separator; break;
							case VK_SUBTRACT: k = key::numpad_minus; break;
							case VK_DECIMAL: k = key::numpad_decimal; break;
							case VK_DIVIDE:  k = key::numpad_slash; break;
							case VK_F1:      k = key::F1; break;
							case VK_F2:      k = key::F2; break;
							case VK_F3:      k = key::F3; break;
							case VK_F4:      k = key::F4; break;
							case VK_F5:      k = key::F5; break;
							case VK_F6:      k = key::F6; break;
							case VK_F7:      k = key::F7; break;
							case VK_F8:      k = key::F8; break;
							case VK_F9:      k = key::F9; break;
							case VK_F10:     k = key::F10; break;
							case VK_F11:     k = key::F11; break;
							case VK_F12:     k = key::F12; break;
							case VK_F13:     k = key::F13; break;
							case VK_F14:     k = key::F14; break;
							case VK_F15:     k = key::F15; break;
							case VK_F16:     k = key::F16; break;
							case VK_F17:     k = key::F17; break;
							case VK_F18:     k = key::F18; break;
							case VK_F19:     k = key::F19; break;
							case VK_F20:     k = key::F20; break;
							case VK_F21:     k = key::F21; break;
							case VK_F22:     k = key::F22; break;
							case VK_F23:     k = key::F23; break;
							case VK_F24:     k = key::F24; break;
							case VK_NUMLOCK: k = key::numlock; break;
							case VK_SCROLL:  k = key::scroll; break;
								//case VK_OEM_NEC_EQUAL:
								//case VK_OEM_FJ_JISHO:
								//case VK_OEM_FJ_MASSHOU:
								//case VK_OEM_FJ_TOUROKU:
								//case VK_OEM_FJ_LOYA:
								//case VK_OEM_FJ_ROYA:
							case VK_OEM_1:     k = key::semicolon; break;
							case VK_OEM_PLUS:  k = key::equals; break;
							case VK_OEM_COMMA: k = key::comma; break;
							case VK_OEM_MINUS: k = key::dash; break;
							case VK_OEM_PERIOD: k = key::period; break;
							case VK_OEM_2:     k = key::slash; break;
							case VK_OEM_3:     k = key::grave; break;
							case VK_OEM_4:     k = key::open_bracket; break;
							case VK_OEM_5:     k = key::backslash; break;
							case VK_OEM_6:     k = key::close_bracket; break;
							case VK_OEM_7:     k = key::quote; break;
							default: /*ignore*/;
							}

							if (k)
							{
								kbd[k & 0xFF] = is_down;
								// ASCII only, VK for letters are the capital ones.
								if ('A' <= k && k <= 'Z')
									kbd[k + 0x20] = is_down;

								if (!is_down)
									last_key = k;
							}

							result = is_down ? -1 : +1;
						}

						default:
							/* All other event types are currently ignored. */;
						}
					}
			}

			return result;
		}


		CON1_API_INLINE void Console::set_cursor(int x, int y)
		{
			if (con_width != 0)
				cur_x = x %= con_width;
			if (con_height != 0)
				cur_y = y %= con_height;

			const COORD coord{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
			SetConsoleCursorPosition(global_out, coord);
		}


		CON1_API_INLINE void Console::set_attr(unsigned attr)
		{
			con_attr = attr;
			SetConsoleTextAttribute(global_out, attr);
		}


		CON1_API_INLINE void Console::draw_block(const CHAR_INFO *buf, unsigned x, unsigned y, unsigned w, unsigned h)
		{
			const COORD
				buf_size{ static_cast<SHORT>(w), static_cast<SHORT>(h) },
				buf_coord{ static_cast<SHORT>(x), static_cast<SHORT>(y) };

			SMALL_RECT region
			{
			  buf_coord.X, buf_coord.Y,
			  static_cast<SHORT>(buf_coord.X + buf_size.X), static_cast<SHORT>(buf_coord.Y + buf_size.Y)
			};

			WriteConsoleOutputW(global_out, buf, buf_size, COORD{}, &region);
		}


		CON1_API_INLINE void Console::clear_screen()
		{
			static const unsigned SCR_SIZE = 32768;
			static CHAR_INFO scr[SCR_SIZE];

			unsigned wh = con_width * con_height;
			wh = wh < SCR_SIZE ? wh : SCR_SIZE;

			const CHAR_INFO chi{ {L' '}, static_cast<WORD>(con_attr) };
			for (unsigned i = 0; i < wh; ++i)
				scr[i] = chi;

			draw_block(scr, 0, 0, con_width, wh / con_width);
		}


		CON1_API_INLINE void Console::set_palette(const COLORREF new_palette[16])
		{
			memcpy(palette, new_palette, sizeof(palette));
			CONSOLE_SCREEN_BUFFER_INFOEX sbi{ sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
			if (GetConsoleScreenBufferInfoEx(global_out, &sbi))
			{
				memcpy(sbi.ColorTable, new_palette, sizeof(palette));

				// fixing a Windows error?
				sbi.srWindow.Right++;  //= sbi.dwMaximumWindowSize.X;
				sbi.srWindow.Bottom++; //= sbi.dwMaximumWindowSize.Y;

				SetConsoleScreenBufferInfoEx(global_out, &sbi);
			}
			// else ignored
		}

	}

}

#endif//CON1_CPP_INCLUDED_2V3U3C