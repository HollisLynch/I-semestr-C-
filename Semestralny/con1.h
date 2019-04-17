// con1.hpp
// Connie UltraLite by Kuvshinov D.R.
// version alpha 12
// Interface part.
#ifndef CON1_HPP_INCLUDED_2V3U3C
#define CON1_HPP_INCLUDED_2V3U3C

#ifndef CON1_HEADER_ONLY
#define CON1_HEADER_ONLY 1
#endif

#if CON1_HEADER_ONLY && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <string>
#include <iostream>
#include <limits>

#if CON1_HEADER_ONLY
#define CON1_API_INLINE inline
#else
#define CON1_API_INLINE
#endif


namespace con1
{
	//
	// Std/std-based facilities.
	//

	using std::size_t;
	using std::ptrdiff_t;

	using std::cin;
	using std::cout;
	using std::cerr;
	using std::clog;

	using std::wcin;
	using std::wcout;
	using std::wcerr;
	using std::wclog;

	using std::endl;
	using std::string;
	using std::wstring;
	using std::getline;

	/// Extract the current input buffer of cin.
	/// After this call cin buffer will be empty.
	inline string input()
	{
		cin.clear();
		static const ptrdiff_t max_string_size = std::numeric_limits<ptrdiff_t>::max() / 4; // arbitrary constant, may be still too big
		const std::streamsize available = cin.rdbuf()->in_avail(); // streamsize is signed
		string result(available <= max_string_size ? static_cast<ptrdiff_t>(available) : max_string_size, ' ');
		cin.read(&result[0], result.size());
		return result;
	}

	/// Extract the current input buffer of cin.
	/// After this call cin buffer will be empty.
	inline wstring winput()
	{
		wcin.clear();
		static const ptrdiff_t max_string_size = std::numeric_limits<ptrdiff_t>::max() / (4 * sizeof(wchar_t));
		const std::streamsize available = cin.rdbuf()->in_avail();
		wstring result(available <= max_string_size ? static_cast<ptrdiff_t>(available) : max_string_size, L' ');
		wcin.read(&result[0], result.size());
		return result;
	}


	//
	// Simple facilities: cls, sleep, delay, etc.
	//

	/// Clear the screen (with the current color attributes).
	void cls();

	/// Wait for given milliseconds of time.
	void sleep(unsigned ms);

	/// Wait until a key hit.
	void delay();

	/// Get the time elapsed from the first call to this function.
	double seconds();

	/// Setup console cursor: make it visible or invisible.
	void cursor_visible(bool visible);

	/// Setup console input echo: make input character visible or invisible.
	void input_echo(bool enabled);


	//
	// Screen size and cursor position.
	//

	/// Get the console screen width in characters.
	int width();

	/// Get the console screen height in characters.
	int height();

	/// Get the current cursor x position.
	int at_x();

	/// Get the current cursor y position.
	int at_y();

	/// Set the current cursor position.
	void at(int x, int y);


	//
	// Colors.
	//

	/// Possible color values.
	namespace color
	{
		enum : unsigned
		{
			blue_bit = 1,
			green_bit = 2,
			red_bit = 4,
			bright_bit = 8
		};

		/// 16 possible colors: all combinations of 4 bits.
		enum : unsigned
		{
			black = 0,
			dark_grey = bright_bit,

			dark_blue = blue_bit,
			dark_green = green_bit,
			dark_red = red_bit,
			dark_cyan = blue_bit | green_bit,
			dark_magenta = blue_bit | red_bit,
			dark_yellow = green_bit | red_bit,
			grey = red_bit | green_bit | blue_bit,

			blue = blue_bit | bright_bit,
			green = green_bit | bright_bit,
			red = red_bit | bright_bit,
			cyan = blue_bit | green_bit | bright_bit,
			magenta = blue_bit | red_bit | bright_bit,
			yellow = green_bit | red_bit | bright_bit,
			white = red_bit | green_bit | blue_bit | bright_bit
		};


		/// Extract ink (foreground) value of color attribute.
		inline unsigned ink_of(unsigned attr)
		{
			return attr & 0xF;
		}

		/// Extract paper (background) value of color attribute.
		inline unsigned paper_of(unsigned attr)
		{
			return (attr >> 4) & 0xF;
		}

		/// Construct color attribute from ink and paper values (of Type constants).
		inline unsigned attr(unsigned ink, unsigned paper)
		{
			return (ink & 0xF) | ((paper & 0xF) << 4);
		}


		// Palette works.

		/// Construct an RGB palette element.
		inline std::uint32_t palette_color
		(
			std::uint_fast8_t red_intensity,
			std::uint_fast8_t green_intensity,
			std::uint_fast8_t blue_intensity
		)
		{
			return red_intensity |
				((std::uint32_t)green_intensity << 8) |
				((std::uint32_t)blue_intensity << 16);
		}

		/// Get the current palette values.
		void get_palette(std::uint32_t palette[16]);

		/// Set the current palette values.
		void set_palette(const std::uint32_t palette[16]);

		/// Restore default palette.
		void restore_default_palette();

		/// Palette was borrowed from here:
		/// http://color.smyck.org/
		void set_smyck_palette();
	}


	/// Set current ink (foreground color) value.
	void ink(unsigned);

	/// Set current paper (background color) value.
	void paper(unsigned);

	/// Set current ink and paper simultaneously.
	void ink_paper(unsigned i, unsigned p);


	//
	// Keyboard input.
	// Delay function might have been here but it is declared above (among simple facilities).
	//

	/// Discard any input events pending.
	void discard_input();

	/// Different mode names.
	namespace mode
	{
		enum Input
		{
			async_input, ///< Asynchronous input: input is read on each check.
			sync_input   ///< Synchronous input: input is read only on sync_input() function call.
		};
	}

	/// Set the current input mode.
	void set_input_mode(mode::Input);

	/// Read the input.
	void sync_input();


	/// Possible keys.
	/// ASCII codes map to the corresponding keys.
	namespace key
	{
		enum : unsigned
		{
			// Stateful controls.
			none,
			numlock_on,   // 1
			scrolllock_on,
			capslock_on,
			numlock,
			scroll,
			capslock,     // 6

			// ASCII
			backspace = '\b',  // 8
			tab = '\t',        // 9
			return_key = '\n', // 10
			escape = 27,
			space = ' ',       // 32

			grave = '`',   // both ` and ~
			dash = '-',   // both - and _
			equals = '=',   // both = and +
			open_bracket = '[', // both [ and {
			close_bracket = ']', // both ] and }
			semicolon = ';',   // both ; and :
			quote = '\'',  // both ' and "
			comma = ',',   // both , and <
			period = '.',   // both . and >
			slash = '/',   // both / and ?
			backslash = '\\',  // both \ and |

			delete_key = 127,

			// Other controls.
			right_ctrl,        // 128
			left_ctrl,
			left_shift,
			right_shift,
			left_alt,          // "menu"
			right_alt,
			left_win,
			right_win,
			applications,      // context menu

			// Other.
			left,
			up,
			right,
			down,
			pause,
			page_up,
			page_down,
			end,
			home,
			print_scr,
			insert,
			numpad_0,
			numpad_1,
			numpad_2,
			numpad_3,
			numpad_4,
			numpad_5,
			numpad_6,
			numpad_7,
			numpad_8,
			numpad_9,
			numpad_asterisk,
			numpad_plus,
			numpad_minus,
			numpad_slash,
			numpad_separator,
			numpad_decimal,
			F1,
			F2,
			F3,
			F4,
			F5,
			F6,
			F7,
			F8,
			F9,
			F10,
			F11,
			F12,
			F13,
			F14,
			F15,
			F16,
			F17,
			F18,
			F19,
			F20,
			F21,
			F22,
			F23,
			F24,
		};

		/// Retrieve the name of a key code.
		/// This name is either the name of the constant above, or 0-9, A-Z,
		/// or (code), where "code" is hex representation of the code.
		const char * get_name(unsigned);
	}


	/// Get the last key pressed and released.
	/// Clear it. Zero (key::none) is returned if no key was pressed.
	unsigned get_last_key();

	/// Check if the button is down.
	/// Accepts constants from key:: and ASCII codes.
	bool is_pressed(unsigned key_code);

	/// Reset a key status.
	void reset_key(unsigned key_code, bool pressed = false);

	/// Reset all keys.
	void reset_all_keys();


	//
	// More advanced facilities.
	//

	/// A wide character with color attribute.
	class Achar
	{
		using Binary = std::uint32_t;
		Binary binary;
		static const Binary
			code_mask = 0xFFFFu,
			attr_mask = ~code_mask;

		static Binary c2b(char ch) { return Binary(static_cast<unsigned char>(ch)); }
		static Binary c2b(wchar_t ch) { return Binary(ch) & code_mask; }

	public:
		static const unsigned
			default_ink = 0xF0Fu,
			default_paper = 0xF0F0u,
			default_colors = default_ink | default_paper;

		Achar() : binary(0) {}
		explicit Achar(char code, unsigned attr = default_colors)
			: binary(c2b(code) | (attr << 16)) {}

		explicit Achar(wchar_t code, unsigned attr = default_colors)
			: binary(c2b(code) | (attr << 16)) {}

		Achar(char code, unsigned ink, unsigned paper)
			: binary(c2b(code) | (color::attr(ink, paper) << 16)) {}

		Achar(wchar_t code, unsigned ink, unsigned paper)
			: binary(c2b(code) | (color::attr(ink, paper) << 16)) {}

		// Getters.
		unsigned code() const { return binary & code_mask; }
		unsigned attr() const { return binary >> 16; }
		unsigned ink() const { return color::ink_of(attr()); }
		unsigned paper() const { return color::paper_of(attr()); }

		// Setters.
		Achar& code(char ch)
		{
			binary = (binary & attr_mask) | c2b(ch);
			return *this;
		}

		Achar& code(wchar_t ch)
		{
			binary = (binary & attr_mask) | c2b(ch);
			return *this;
		}

		Achar& code(unsigned ch)
		{
			binary = (binary & attr_mask) | (ch & code_mask);
			return *this;
		}

		Achar& attr(unsigned a)
		{
			binary = (binary & code_mask) | (a << 16);
			return *this;
		}

		Achar& attr(unsigned ink, unsigned paper)
		{
			return attr(color::attr(ink, paper));
		}

		Achar& ink(unsigned i)
		{
			return attr((attr() & ~default_ink) | (i & default_ink));
		}

		Achar& paper(unsigned p)
		{
			return attr((attr() & ~default_paper) | ((p << 4) & default_paper));
		}

		/// Change the ink and the paper to the given ones if ink or paper are "default".
		Achar& override_default_attr(unsigned i, unsigned p)
		{
			const bool
				chi = (attr() & default_ink) == default_ink,
				chp = (attr() & default_paper) == default_paper;
			return attr((chi ? i : ink()), (chp ? p : paper()));
		}

		Achar& operator=(char ch) { return code(ch); }
		Achar& operator=(wchar_t ch) { return code(ch); }

		friend inline bool operator==(Achar a, Achar b)
		{
			return a.binary == b.binary;
		}
	};

	inline bool operator!=(Achar a, Achar b)
	{
		return !(a == b);
	}


	/// A rectangular block within rectangular array of Achars.
	class Achar_block
	{
		size_t _rows, _cols, _stride;
		Achar *_begin;

	public:
		/// Get rows in the block.
		size_t rows() const { return _rows; }
		/// Get columns in the block.
		size_t cols() const { return _cols; }

		/// Create an empty block.
		Achar_block() : _rows(0), _cols(0), _stride(0), _begin(nullptr) {}
		/// Create a block from an array of given extents.
		Achar_block(Achar *packed_array, size_t array_rows, size_t array_cols)
			: _rows(array_rows), _cols(array_cols), _stride(array_cols), _begin(packed_array) {}
		/// Create a block from a static array.
		template <size_t R, size_t C>
		Achar_block(Achar(&static_array)[R][C])
			: Achar_block(&static_array[0][0], R, C) {}

		/// Create a block from an array of given extents and set the upper-left corner and size of the block.
		Achar_block(size_t block_top_row, size_t block_left_col, size_t block_rows, size_t block_cols,
			Achar *packed_array, size_t array_rows, size_t array_cols)
			: _rows(block_rows), _cols(block_cols), _stride(array_cols),
			_begin(packed_array + block_left_col + block_top_row * array_cols)
		{
			assert(block_top_row < array_rows);
			assert(block_left_col < array_cols);
			assert(block_rows <= array_rows - block_top_row);
			assert(block_cols <= array_cols - block_left_col);
			assert(packed_array != nullptr);
		}

		/// Create a block from a static array of given extents and set the upper-left corner and size of the block.
		template <size_t R, size_t C>
		Achar_block(size_t block_top_row, size_t block_left_col, size_t block_rows, size_t block_cols, Achar(&static_array)[R][C])
			: Achar_block(block_top_row, block_left_col, block_rows, block_cols, &static_array[0][0], R, C) {}

		/// Access a row by index.
		Achar* operator[](size_t row)
		{
			assert(row < rows());
			return _begin + row * _stride;
		}

		const Achar* operator[](size_t row) const
		{
			assert(row < rows());
			return _begin + row * _stride;
		}

		/// Access an element in the block by x-y coordinates.
		Achar& xy(size_t x, size_t y)
		{
			assert(x < cols() && y < rows());
			return (*this)[y][x];
		}

		const Achar& xy(size_t x, size_t y) const
		{
			assert(x < cols() && y < rows());
			return (*this)[y][x];
		}

		/// Make a subrange.
		Achar_block subrange(size_t sub_top_row, size_t sub_left_col, size_t sub_rows, size_t sub_cols)
		{
			return Achar_block(sub_top_row, sub_left_col, sub_rows, sub_cols, _begin, _rows, _stride);
		}

		/// Copy all the data of the block in a packed array of the same extents as the block itself.
		/// @return the end position, just behind the last Achar written
		Achar* copy_to(Achar *a) const
		{
			Achar_block ab(a, rows(), cols());
			return copy_to(ab);
		}

		/// Copy all the data to the array viewed through another block.
		Achar* copy_to(Achar_block &other) const
		{
			auto from = _begin;
			auto to = other._begin;
			const auto from_stride = _stride,
				to_stride = other._stride,
				rows = _rows < other._rows ? _rows : other._rows,
				cols = _cols < other._cols ? _cols : other._cols;

			for (size_t r = 0; r < rows; ++r)
			{
				for (size_t i = 0; i < cols; ++i)
					to[i] = from[i];

				from += from_stride;
				to += to_stride;
			}

			return to;
		}
	};


	/// Draw a rectangular subrange of a Achar packed array (a block).
	void draw(const Achar_block&);

	/// Draw Achar rectangular packed array at the position set by the last at() call (or (0, 0)).
	inline void draw(const Achar block[], unsigned rows, unsigned cols)
	{
		draw(Achar_block(const_cast<Achar*>(block), rows, cols));
	}

	/// Draw static rectangular Achar array at the position set by the last at() call (or (0, 0)).
	template <unsigned H, unsigned W> inline
		void draw(const Achar(&block)[H][W])
	{
		return draw(block[0], H, W);
	}
}


#if CON1_HEADER_ONLY
#include "con1.cpp"
#endif

#endif//CON1_HPP_INCLUDED_2V3U3C