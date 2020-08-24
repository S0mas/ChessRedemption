#pragma once
#include <cstdint>
#include <vector>
#include <iostream>

class Position {
	char letter_;
	uint8_t number_;
	
public:
	template<char LETTER, uint8_t NUMBER>
	static Position createPosition() noexcept {
		static_assert((LETTER >= 'A' && LETTER <= 'H') || (LETTER >= 'a' && LETTER <= 'h'), "Wrong letter for position param specified.");
		static_assert(NUMBER >= 1 && NUMBER <= 8, "Wrong number for position param specified");
		return Position(LETTER, NUMBER);
	}

	template<const char STR[3]>
	static Position createPosition() noexcept {
		static_assert((STR[0] >= 'A' && STR[0] <= 'H') || (STR[0] >= 'a' && STR[0] <= 'h'), "Wrong letter for position param specified.");
		static_assert(STR[1] >= '1' && STR[1] <= '8', "Wrong number for position param specified");
		static_assert(STR[2] == '\0', "STR param for position should be of size 2 + null termination sign.");
		return Position(STR[0], STR[1]);
	}

	Position(char letter, uint8_t number) noexcept : letter_(letter), number_(number) {}

	bool isLastRow() const noexcept {
		return number_ == 1 || number_ == 8;
	}

	uint8_t number() const noexcept {
		return number_;
	}

	char letter() const noexcept {
		return letter_;
	}


	friend bool operator==(Position const& lhs, Position const& rhs) noexcept;
	friend bool operator<(Position const& lhs, Position const& rhs) noexcept;
};

inline bool operator==(Position const& lhs, Position const& rhs) noexcept {
	return lhs.letter_ == rhs.letter_ && lhs.number_ == rhs.number_;
}

inline bool operator<(Position const& lhs, Position const& rhs) noexcept {
	return lhs.letter_ != rhs.letter_ ? lhs.letter_ < rhs.letter_ : lhs.number_ < rhs.number_;
}