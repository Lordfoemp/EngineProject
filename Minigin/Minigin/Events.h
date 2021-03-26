#pragma once
namespace Helheim
{
	enum class AudioMessages
	{
		PLAYER_DIED = 0,
		SCORE_UP = 1
	};

	struct PlayMessage
	{
		AudioMessages request = AudioMessages::PLAYER_DIED;
		int volume = 64;					// 0 - 128
		bool isPlaying = false;
	};
}

