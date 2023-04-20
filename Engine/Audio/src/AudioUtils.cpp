#include "AudioUtils.h"

namespace Bambo
{
	bool GetFormat(int channels, int bps, ALenum& format)
	{
		format = AL_INVALID_ENUM;

		if (channels == 1 && bps == 8)
			format = AL_FORMAT_MONO8;
		else if (channels == 1 && bps == 16)
			format = AL_FORMAT_MONO16;
		else if (channels == 2 && bps == 8)
			format = AL_FORMAT_STEREO8;
		else if (channels == 2 && bps == 16)
			format = AL_FORMAT_STEREO16;

		return format != AL_INVALID_ENUM;

	}

}