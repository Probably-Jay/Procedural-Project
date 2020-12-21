#include "Chord.h"


const std::map<Chord::Note, float> Chord::pitches = {
				  {Note::A,		440 * powf(2, 0 / 12.f)	 }
				, {Note::As,	440 * powf(2, 1 / 12.f)	 }
	//			, {Note::Bb,	440 * powf(2, 1 / 12.f)	 }
				, {Note::B,		440 * powf(2, 2 / 12.f)	 }
				, {Note::C,		440 * powf(2, 3 / 12.f)	 }
				, {Note::Cs,	440 * powf(2, 4 / 12.f)	 }
	//			, {Note::Db,	440 * powf(2, 4 / 12.f)	 }
				, {Note::D,		440 * powf(2, 5 / 12.f)	 }
				, {Note::Ds,	440 * powf(2, 6 / 12.f)	 }
	//			, {Note::Eb,	440 * powf(2, 6 / 12.f)	 }
				, {Note::E,		440 * powf(2, 7 / 12.f)	 }
				, {Note::F,		440 * powf(2, 8 / 12.f)	 }
				, {Note::Fs,	440 * powf(2, 9 / 12.f)	 }
	//			, {Note::Gb,	440 * powf(2, 9 / 12.f)	 }
				, {Note::G,		440 * powf(2, 10 / 12.f) }
				, {Note::Gs,	440 * powf(2, 11 / 12.f) }
	//			, {Note::Ab,	440 * powf(2, 11 / 12.f) }
};



const std::map<Chord::Chords, std::vector<float>> Chord::chords = {

			  {Chords::AMaj,{
					  {pitches.at(Note::A)	}
					, {pitches.at(Note::Cs)	}
					, {pitches.at(Note::E)	}
				}
			}
			, {Chords::BMin,{
					  {pitches.at(Note::B)	}
					, {pitches.at(Note::D)	}
					, {pitches.at(Note::Fs)	}
				}
			}
			, {Chords::CsMin,{
					  {pitches.at(Note::Cs)	}
					, {pitches.at(Note::E)	}
					, {pitches.at(Note::Gs)	}
				}
			}
			, {Chords::DMaj,{
					  {pitches.at(Note::D)	}
					, {pitches.at(Note::Fs)	}
					, {pitches.at(Note::A)	}
				}
			}
			, {Chords::EMaj,{
					  {pitches.at(Note::E)	}
					, {pitches.at(Note::Gs)	}
					, {pitches.at(Note::B)	}
				}
			}
			, {Chords::FsMin,{
					  {pitches.at(Note::Fs)	}
					, {pitches.at(Note::A)	}
					, {pitches.at(Note::Cs)	}
				}
			}
			, {Chords::GsDim,{
					  {pitches.at(Note::Gs)	}
					, {pitches.at(Note::B)	}
					, {pitches.at(Note::D)	}
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
