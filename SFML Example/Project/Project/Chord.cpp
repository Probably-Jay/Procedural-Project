#include "Chord.h"

// notes are all expressed in terms of this base frequency
constexpr double BASEFREQUENCY = 440.0;
constexpr int NOTESINSCALE = 7;
// twelve tone equal temperament frequency function
//constexpr float Frequency(double n) { return BaseFrequency * std::pow(2, n / 12.0); };
#define Frequency(n) BASEFREQUENCY * powf(2, n / 12.0)

const std::map<Chord::Note, float> Chord::pitches = {
				  {Note::A,		Frequency(0) }
				, {Note::As,	Frequency(1) }
				, {Note::B,		Frequency(2) }
				, {Note::C,		Frequency(3) }
				, {Note::Cs,	Frequency(4) }
				, {Note::D,		Frequency(5) }
				, {Note::Ds,	Frequency(6) }
				, {Note::E,		Frequency(7) }
				, {Note::F,		Frequency(8) }
				, {Note::Fs,	Frequency(9) }
				, {Note::G,		Frequency(10) }
				, {Note::Gs,	Frequency(11) }
};

	//			, {Note::Bb,	440 * powf(2, 1 / 12.f)	 }
	//			, {Note::Db,	440 * powf(2, 4 / 12.f)	 }
	//			, {Note::Eb,	440 * powf(2, 6 / 12.f)	 }
	//			, {Note::Gb,	440 * powf(2, 9 / 12.f)	 }
	//			, {Note::Ab,	440 * powf(2, 11 / 12.f) }


const std::map<Chord::Chords, std::vector<float>> Chord::chords = {

			  {Chords::AMaj,{
					  {pitches.at(Note::A)	}
					, {pitches.at(Note::Cs)	}
					, {pitches.at(Note::E)	}
					, {pitches.at(Note::Gs)	}
				}
			}
			, {Chords::BMin,{
					  {pitches.at(Note::B)	}
					, {pitches.at(Note::D)	}
					, {pitches.at(Note::Fs)	}
					, {pitches.at(Note::A)	}
				}
			}
			, {Chords::CsMin,{
					  {pitches.at(Note::Cs)	}
					, {pitches.at(Note::E)	}
					, {pitches.at(Note::Gs)	}
					, {pitches.at(Note::B)	}
				}
			}
			, {Chords::DMaj,{
					  {pitches.at(Note::D)	}
					, {pitches.at(Note::Fs)	}
					, {pitches.at(Note::A)	}
					, {pitches.at(Note::C)	}
				}
			}
			, {Chords::EMaj,{
					  {pitches.at(Note::E)	}
					, {pitches.at(Note::Gs)	}
					, {pitches.at(Note::B)	}
					, {pitches.at(Note::D)	}
				}
			}
			, {Chords::FsMin,{
					  {pitches.at(Note::Fs)	}
					, {pitches.at(Note::A)	}
					, {pitches.at(Note::Cs)	}
					, {pitches.at(Note::E)	}
				}
			}
			, {Chords::GsDim,{
					  {pitches.at(Note::Gs)	}
					, {pitches.at(Note::B)	}
					, {pitches.at(Note::D)	}
					, {pitches.at(Note::F)	}
				}
			}

};

const std::map<Chord::Function, Chord::Chords> Chord::functionalAMajor = {

	  {Chord::Function::I		, Chord::Chords::AMaj}
	, {Chord::Function::ii		, Chord::Chords::BMin}
	, {Chord::Function::iii		, Chord::Chords::CsMin}
	, {Chord::Function::IV		, Chord::Chords::DMaj}
	, {Chord::Function::V		, Chord::Chords::EMaj}
	, {Chord::Function::vi		, Chord::Chords::FsMin}
	, {Chord::Function::viidim	, Chord::Chords::GsDim}
};

const std::map<Chord::ScaleDegrees, Chord::Note> Chord::AMajorScale = {
	  {Chord::ScaleDegrees::tonic,		Chord::Note::A}
	, {Chord::ScaleDegrees::supertonic,	Chord::Note::B}
	, {Chord::ScaleDegrees::mediant,	Chord::Note::Cs}
	, {Chord::ScaleDegrees::subdominant,Chord::Note::D}
	, {Chord::ScaleDegrees::dominant,	Chord::Note::E}
	, {Chord::ScaleDegrees::submediant, Chord::Note::Fs}
	, {Chord::ScaleDegrees::leading	,	Chord::Note::Gs}
};

// get random note with no previous note, more likley to pick consonant pentatonic notes
Chord::Note Chord::GetRandomNote(Key key)
{
	Chord::ScaleDegrees degree = (Chord::ScaleDegrees)(rand() % NOTESINSCALE);

	// make non-pentatonic notes less common
	if (degree == Chord::ScaleDegrees::subdominant || degree == Chord::ScaleDegrees::leading) {
		degree = (Chord::ScaleDegrees)(rand() % NOTESINSCALE);
	}
	if (degree == Chord::ScaleDegrees::subdominant || degree == Chord::ScaleDegrees::leading) {
		degree = (Chord::ScaleDegrees)(rand() % NOTESINSCALE);
	}

	Chord::Note note;
	switch (key)
	{
	case Chord::Key::AMaj:
		return AMajorScale.at(degree);
		break;
	}
}

// Get a note, either a leap to a random note, or a step to a neighboring note
Chord::Note Chord::GetRandomNote(Key key, Note prevNote)
{
	int leapChance = rand() % 100;

	// leap to new note
	if (leapChance < 50) {
		return Chord::GetRandomNote(key);
	}

	// else, stepwise motion

	auto scale = AMajorScale;

	switch (key)
	{
	case Chord::Key::AMaj:
		scale = AMajorScale;
		break;
	default:
		break;
	}

	Chord::ScaleDegrees function = Chord::ScaleDegrees::tonic;

	
	{// find note's function
		auto itt = scale.begin();
		while (itt != scale.end())
		{
			if (itt->second == prevNote)
				break;
			itt++;
		}
		function = itt->first;
	}

	leapChance = rand() % 100;

	int step = 0;

	if (leapChance < 45) {
		step = 1;
	}
	else if(leapChance < 90){
		step = -1;
	}
	else if (leapChance < 95) {
		step = 2;
	}
	else {
		step = -2;
	}

	
	Chord::ScaleDegrees nextNoteFunction = (Chord::ScaleDegrees)(((int)function + step + NOTESINSCALE) % NOTESINSCALE); // keep within range

	return scale.at(nextNoteFunction);
}
