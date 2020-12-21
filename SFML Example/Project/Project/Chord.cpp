#include "Chord.h"

// notes are all expressed in terms of this base frequency
constexpr auto BaseFrequency = 440.0;
// twelve tone equal temperament frequency function
//constexpr float Frequency(double n) { return BaseFrequency * std::pow(2, n / 12.0); };
#define Frequency(n) BaseFrequency * powf(2, n / 12.0)

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
