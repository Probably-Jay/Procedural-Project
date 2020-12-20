#pragma once
#include <map>

struct Chord
{
	enum class NotesEnum
	{
		  A		= 0
		, As	= 1
		, Bb	= 1
		, B		= 2
		, C		= 3
		, Cs	= 4
		, Db	= 4
		, D		= 5
		, Ds	= 6
		, Eb	= 6
		, E		= 7
		, F		= 8
		, Fs	= 9
		, Gb	= 9
		, G		= 10
		, Gs	= 11
		, Ab	= 11
	};

	std::map<NotesEnum,float> pitches = {
				  {NotesEnum::A,	440 * powf(2, 0 / 12.f)	 }
				, {NotesEnum::As,	440 * powf(2, 1 / 12.f)	 }
				, {NotesEnum::Bb,	440 * powf(2, 1 / 12.f)	 }
				, {NotesEnum::B,	440 * powf(2, 2 / 12.f)	 }
				, {NotesEnum::C,	440 * powf(2, 3 / 12.f)	 }
				, {NotesEnum::Cs,	440 * powf(2, 4 / 12.f)	 }
				, {NotesEnum::Db,	440 * powf(2, 4 / 12.f)	 }
				, {NotesEnum::D,	440 * powf(2, 5 / 12.f)	 }
				, {NotesEnum::Ds,	440 * powf(2, 6 / 12.f)	 }
				, {NotesEnum::Eb,	440 * powf(2, 6 / 12.f)	 }
				, {NotesEnum::E,	440 * powf(2, 7 / 12.f)	 }
				, {NotesEnum::F,	440 * powf(2, 8 / 12.f)	 }
				, {NotesEnum::Fs,	440 * powf(2, 9 / 12.f)	 }
				, {NotesEnum::Gb,	440 * powf(2, 9 / 12.f)	 }
				, {NotesEnum::G,	440 * powf(2, 10 / 12.f) }
				, {NotesEnum::Gs,	440 * powf(2, 11 / 12.f) }
				, {NotesEnum::Ab,	440 * powf(2, 11 / 12.f) }
		};





};
//
//std::vector<float> notes = {
//		  440 * powf(2, 0 / 12.f)
//		, 440 * powf(2, 2 / 12.f)
//		, 440 * powf(2, 4 / 12.f)
//		, 440 * powf(2, 5 / 12.f)
//		, 440 * powf(2, 7 / 12.f)
//		, 440 * powf(2, 9 / 12.f)
//		, 440 * powf(2, 11 / 12.f)
//};
//
//enum class NoteEnum
//{
//	A = 0,
//	B,
//	Cs,
//	D,
//	E,
//	Fs,
//	G,
//};
//
//enum class ChordsEnum {
//	A,
//	D,
//	E,
//};
//
//std::vector<NoteEnum> penta = {
//	NoteEnum::A,
//	NoteEnum::B,
//	NoteEnum::Cs,
//	NoteEnum::E,
//	NoteEnum::Fs,
//};
//
//std::vector<NoteEnum> spicy = {
//	NoteEnum::D,
//	NoteEnum::G
//};
//
//std::vector<std::vector<float>> chords = {
//	{notes[(int)NoteEnum::A],	notes[(int)NoteEnum::Cs],	notes[(int)NoteEnum::E]},
//	{notes[(int)NoteEnum::D],	notes[(int)NoteEnum::Fs],	notes[(int)NoteEnum::A]},
//	{notes[(int)NoteEnum::E],	notes[(int)NoteEnum::G],	notes[(int)NoteEnum::B]},
//};
//
//std::vector<ChordsEnum> Amaj = {
//	ChordsEnum::A,
//	ChordsEnum::D,
//	ChordsEnum::E,
//};