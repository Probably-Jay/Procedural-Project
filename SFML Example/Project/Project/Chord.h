#pragma once
#include <map>

#include <vector>
#include <string>

struct Chord
{
	enum class Note
	{
		A = 0
		, As = 1
		//	, Bb	= 1
		, B = 2
		, C = 3
		, Cs = 4
		//	, Db	= 4
		, D = 5
		, Ds = 6
		//	, Eb	= 6
		, E = 7
		, F = 8
		, Fs = 9
		//	, Gb	= 9
		, G = 10
		, Gs = 11
		//	, Ab	= 11
	};

	enum class Chords
	{
		AMaj
		, BMin
		, CsMin
		, DMaj
		, EMaj
		, FsMin
		, GsDim

	};

	enum class Key
	{
		AMaj
	};

	enum class Function
	{
		I
		, ii
		, iii
		, IV
		, V
		, vi
		, viidim
	};

	static const std::map<Note, float> pitches;

	static const std::map<Chords, std::vector<float>> chords;

	static const std::map<Function, Chords> functionalAMajor;

	/*static inline std::vector<float> const& ChordFromFunction(Chord::Key key,  Chord::Function function) {
		switch (key)
		{
		case Chord::Key::AMaj:
			return
			break;
		default:
			break;
		}
	};*/

	static std::string PrintChord(Chords chord) {

		switch (chord)
		{
		case Chord::Chords::AMaj:
			return "AMaj";
			break;
		case Chord::Chords::BMin:
			return "BMin";
			break;
		case Chord::Chords::CsMin:
			return "CsMin";
			break;
		case Chord::Chords::DMaj:
			return "DMaj";
			break;
		case Chord::Chords::EMaj:
			return "EMaj";
			break;
		case Chord::Chords::FsMin:
			return "FsMin";
			break;
		case Chord::Chords::GsDim:
			return "GsDim";
			break;
		default:
			return "error";
			break;
		}
	}

};
