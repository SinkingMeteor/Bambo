#include "AudioWavLoader.h"

namespace
{
	constexpr int WAV_HEADER_SIZE = 12;
}

namespace Bambo
{
	bool AudioWavLoader::IsThatFormat(std::ifstream& dataStream) const
	{
		char buffer[WAV_HEADER_SIZE];
		if (dataStream.read(buffer, WAV_HEADER_SIZE).gcount() < WAV_HEADER_SIZE)
			return false;

		return (buffer[0] == 'R') && 
			(buffer[1] == 'I') &&
			(buffer[2] == 'F') && 
			(buffer[3] == 'F') && 
			(buffer[8] == 'W') &&
			(buffer[9] == 'A') && 
			(buffer[10] == 'V') && 
			(buffer[11] == 'E');
	}

	bool AudioWavLoader::LoadAudio(std::ifstream& inStream, RawAudioData& rawData)
	{
		if (!ReadHeaderOfWav(inStream, rawData.SampleRate, rawData.DataSize, rawData.Channels, rawData.Bps))
		{
			Log("LogAudioFile", "Can't open WAV file");
			return false;
		}

		rawData.Data = new char[rawData.DataSize];
		inStream.read(rawData.Data, rawData.DataSize);
		return true;
	}

	bool AudioWavLoader::ReadHeaderOfWav(std::ifstream& file, ALsizei& sampleRate, ALsizei& dataSize, int& channels, int& bps)
	{
		char buffer[4];
		if (!file.is_open())
			return false;

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: Can't read RIFF while loading WAV file");
			return false;
		}

		if (std::strncmp(buffer, "RIFF", 4) != 0)
		{
			Log("LogAudioFile", "ERROR: You're trying to load invalid WAV file");
			return false;
		}

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: Can't read size of WAV file");
			return false;
		}

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read WAVE");
			return false;
		}

		if (std::strncmp(buffer, "WAVE", 4) != 0)
		{
			Log("LogAudioFile", "ERROR: file is not a valid WAVE file (header doesn't contain WAVE)");
			return false;
		}

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read fmt/0");
			return false;
		}

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read the 16");
			return false;
		}

		if (!file.read(buffer, 2))
		{
			Log("LogAudioFile", "ERROR: could not read PCM");
			return false;
		}

		//Channels number
		if (!file.read(buffer, 2))
		{
			Log("LogAudioFile", "ERROR: could not read number of channels");
			return false;
		}
		channels = ConvertToInt(buffer, 2);

		//Sample rate
		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read sample rate");
			return false;
		}
		sampleRate = ConvertToInt(buffer, 4);

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read (sampleRate * bitsPerSample * channels) / 8");
			return false;
		}

		if (!file.read(buffer, 2))
		{
			Log("LogAudioFile", "ERROR: could not read 	(BitsPerSample * Channels) / 8.1 - 8 bit mono2 - 8 bit stereo/16 bit mono4 - 16 bit stereo");
			return false;
		}

		// BPS
		if (!file.read(buffer, 2))
		{
			Log("LogAudioFile", "ERROR: could not read bits per sample");
			return false;
		}
		bps = ConvertToInt(buffer, 2);

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read data chunk header");
			return false;
		}

		if (std::strncmp(buffer, "data", 4) != 0)
		{
			Log("LogAudioFile", "ERROR: file is not a valid WAVE file (doesn't have 'data' tag)");
			return false;
		}

		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read data size");
			return false;
		}
		dataSize = ConvertToInt(buffer, 4);

		if (file.eof())
		{
			Log("LogAudioFile", "ERROR: There is no data in file");
			return false;
		}

		if (file.fail())
		{
			Log("LogAudioFile", "ERROR: fail state set on the file");
			return false;
		}

		return true;
	}
}