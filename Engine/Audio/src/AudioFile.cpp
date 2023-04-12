#include "AudioFile.h"
namespace Bambo
{
	AudioFile::AudioFile() :
		m_sampleRate(0),
		m_dataSize(0),
		m_channels(0),
		m_bps(0),
		m_data(nullptr)
	{}

	AudioFile::~AudioFile()
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}
	}

	bool AudioFile::LoadWavFile(const std::string& filename)
	{
		if (m_data != nullptr)
		{
			delete[] m_data;
			m_data = nullptr;
		}

		std::ifstream inStream{ filename, std::ios::binary };
		if (!inStream.is_open())
		{
			Log("LogAudioFile", "Can't open WAV file by path: %s", filename.c_str());
			return false;
		}
		if (!ReadHeaderOfWav(inStream))
		{
			Log("LogAudioFile", "Can't open WAV file by path: %s", filename.c_str());
			return false;
		}
		m_data = new char[m_dataSize];
		inStream.read(m_data, m_dataSize);
		return true;
	}

	bool AudioFile::ReadHeaderOfWav(std::ifstream& file)
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
		m_channels = ConvertToInt(buffer, 2);

		//Sample rate
		if (!file.read(buffer, 4))
		{
			Log("LogAudioFile", "ERROR: could not read sample rate");
			return false;
		}
		m_sampleRate = ConvertToInt(buffer, 4);

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
		m_bps = ConvertToInt(buffer, 2);

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
		m_dataSize = ConvertToInt(buffer, 4);

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

	int AudioFile::ConvertToInt(char* buffer, std::size_t len)
	{
		std::int32_t a = 0;
		if (IsLittleEndian())
		{
			std::memcpy(&a, buffer, len);
		}
		else
		{
			for (std::size_t i = 0; i < len; ++i)
			{
				reinterpret_cast<char*>(&a)[3 - i] = buffer[i];
			}
		}
		return a;
	}

}