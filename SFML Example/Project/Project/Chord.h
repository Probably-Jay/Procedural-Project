#pragma once
#include <map>

#include <vector>
#include <string>

struct Chord
{

	enum class Inversions {
		Root,
		FirstInversion,
		SecondInversion
	};

	enum class Note
	{
		  A		= 0
		, As	= 1
		, B		= 2
		, C		= 3
		, Cs	= 4
		, D		= 5
		, Ds	= 6
		, E		= 7
		, F		= 8
		, Fs	= 9
		, G		= 10
		, Gs	= 11
		
		/*, A1	= 0		+12
		, As1	= 1		+12
		, B1	= 2		+12
		, C1	= 3		+12
		, Cs1	= 4		+12
		, D1	= 5		+12
		, Ds1	= 6		+12
		, E1	= 7		+12
		, F1	= 8		+12
		, Fs1	= 9		+12
		, G1	= 10	+12
		, Gs1	= 11	+12*/
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

	static inline float GetNote(Note note, int octave = 0) { return pow(2, octave) * pitches.at(note); };
	static inline float GetNote(Chords chord, int note, int octave = 0) { return pow(2, octave) * chords.at(chord)[note]; };

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
